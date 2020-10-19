#include "display_module.h"

uchar buffer[20];
uchar oldBuffer[20];
bit self_old = 1;	
bit has_history = 0;
uchar head_col = 0;

void Init(){
	write(INITIAL, 0);
	write(CLA, 0);
	write(SHOW_CURSOR, 0);
	write(CURSOR_FORWARD, 0);
	write(CURSOR_BLINK, 0);
	allClear();
}

uchar busyCheck()   //忙检查
{
  uchar	status;
  RS = 0;	 
  RW = 1;	 
  EN = 1;	 
  delayMs(DELAY);
  status = P1; 	//读出P1最高位状态值
  EN = 0;
  return status;
}

/// 写入数据或者指令
void write(uchar _data, bit data_flag){
	while((busyCheck()&0x80) == 0x80);
	RW = 0;
	RS = data_flag;		// data_flag为1时为写入数据
	EN = 0;
	delayMs(DELAY);
	EN = 1;
	P1 = _data;
	delayMs(DELAY);
	EN = 0;				// 约2 * DELAY ms的脉冲
}

// 在行尾补充
void writeCursor(uchar _data){							// 光标未对齐时只更改当前位置上的字符，不会影响最大长
	if (head_col < 19){
		write(_data, 1);
		buffer[head_col] = _data;
		buffer[head_col] = _data;
		head_col ++;
	}
}

void writeLine(uchar* ptr, uint line, bit clear, uchar align){
	uint index;
	uchar start_pos = 0;
	switch(align){
		case CENTRAL:
			start_pos = (uchar)((20 - strlen(ptr)) / 2); break;
		case LEFT:
			break;
		case RIGHT:
			start_pos = (uchar)(20 - strlen(ptr)); break;
		default:
			break;
	}
	if (clear == 0){
		write(DISPLAY_START + line_offset[line] + start_pos, 0);
		for (index = 0; index < 20 && ptr[index] >= 10 && ptr[index] != '#'; index++){
			write(ptr[index], 1);
		}
	}
	else{
		write(DISPLAY_START | line_offset[line], 0);
		for (index = 0; index < start_pos; index ++){
			write(0x20, 1);
		}
		for (index = 0; index < 20 && ptr[index] >= 0x0a && ptr[index] != '#'; index ++){
			write(ptr[index], 1);
		}
		for (; index < 20 - start_pos; index ++){
			write(0x20, 1);
		}
	}
}

//========================光标移动（包括写入/删除）==========================

void setCursor(uchar row, uchar col){
	write(DISPLAY_START + line_offset[row] + col, 0);
}

/// 编号0 @brief删除行末字符
void doPop(){
	if (head_col > 0){
		head_col --;
		write(CURSOR_LEFT, 0);		// 光标移动到末尾字符上	
		write(' ', 1);				// 清除
		write(CURSOR_LEFT, 0);		// 由于光标一直采取右移的方式，写入以后会右移一位，则需要左移
		buffer[head_col] = 0;		// 删除
	}
}

/// 编号1 @brief AC @todo 此后需要增加：清除栈内所有内容
void allClear(){
	int i;
	write(CLA, 0);
	head_col = 0;
	/// @todo: 此处需要像计算器一样增加一个顶行显示
//	if (alarm_time == ALARM_OFF){
//		writeLine(alarm_info[4], 0, 1, CENTRAL);
//	}
//	else{
//		writeLine(alarm_info[5], 0, 1, CENTRAL);
//	}
	write(SHOW_CURSOR, 0);
	setCursor(3, 0);
	_mode = CHATTING;
	for (i = 0; i < 20; i++){
		*(buffer + i) = 0;
	}
}

void drawSuspend(){
	uchar i;
	for (i = 0; i < 3; i++){
		writeLine(suspend_ui[i], i, 1, CENTRAL);
	}
	writeLine(suspend_ui[0], 3, 1, CENTRAL);
}

void drawIncomingMessage(uchar* buf, bit self){
	uchar i;
	if (has_history == 1){
		if (self_old == 1){
			writeLine(oldBuffer, 1, 1, RIGHT);
		}
		else {
			writeLine(oldBuffer, 1, 1, LEFT);
		}
		if (self == 1){
			writeLine(buf, 2, 1, RIGHT);
		}
		else {
			writeLine(buf, 2, 1, LEFT);
		}
	}
	else{
		if (self == 1){
			writeLine(buf, 1, 1, RIGHT);
		}
		else {
			writeLine(buf, 1, 1, LEFT);
		}
		has_history = 1;
	}
	self_old = self;		// 历史消息是否来自本机键盘响应设置
	for (i = 0; i < 20; i++){
		oldBuffer[i] = buf[i];
	}
	setCursor(3, 0);
	if (self == 0){			// 本次绘制来自对方的输出，那么为自动响应的，需要清除
		draw_allow = 0;
		bufferReset();		// 包含receiveBuffer的重置以及索引重置
	}
	else{
		head_col = 0;		// 自身输入的索引为head_col
	}
}
