#include "display_module.h"

uchar buffer[20];
uchar oldBuffer[20];
bit self_old = 1;	
bit has_history = 0;
uchar head_col = 0;
uchar toneHigh = 1, toneLow = 1;

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
		for (index = 0; index < 20 && ptr[index] >= 10; index++){
			write(ptr[index], 1);
		}
	}
	else{
		write(DISPLAY_START | line_offset[line], 0);
		for (index = 0; index < start_pos; index ++){
			write(0x20, 1);
		}
		for (index = 0; index < 20 && ptr[index] >= 0x0a; index ++){
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
	write(CLA, 0);
	writeLine(wechat_info[0], 0, 1, CENTRAL);
	write(SHOW_CURSOR, 0);
	setCursor(3, 0);
	_mode = CHATTING;
	for (head_col = 0; head_col < 20; head_col++){
		*(buffer + head_col) = 0;
	}
	head_col = 0;
}

void drawSuspend(){
	uchar i;
	for (i = 0; i < 3; i++){
		writeLine(lock_info[i], i, 1, CENTRAL);
	}
	writeLine(lock_info[0], 3, 1, CENTRAL);
	setCursor(2, 5);
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
		buf[i] = 0;
	}
	if (self == 0){			// 本次绘制来自对方的输出，那么为自动响应的，需要清除
		draw_allow = 0;
		bufferReset();		// 包含receiveBuffer的重置以及索引重置
	}
	else{
		writeLine(" ", 3, 1, LEFT);
		head_col = 0;		// 自身输入的索引为head_col
	}
	setCursor(3, 0);
}

void printPassword(uchar pin){
	if (head_col < 9){
		if (head_col > 0){
			write(CURSOR_LEFT, 0);
			write('*', 1);				// 将上一位设置为 *
		}
		writeCursor(pin);
	}
}

void isPasswordRight(){
	uchar i;
	for (i = 0; i < 9; i++){
		if (buffer[i] != password[i]){
			writeLine(wechat_info[1], 1, 1, LEFT);
			writeLine(lock_info[2], 2, 1, LEFT);
			break;
		}
	}
	if (i < 9){
		counter++;
		if (counter >= 3){
			_mode = FAULTS;			// 三次密码失败模式
			writeLine(wechat_info[2], 2, 1, CENTRAL);
			write(NO_CURSOR, 0);
			return;
		}
		for (i = 0; i < 9; i++){
			buffer[i] = 0;
		}
		head_col = 0;
		setCursor(2, 5);
		playSound(error_tone);
	}
	else {		// 通过
		writeLine(wechat_info[3], 1, 1, LEFT);
		playSound(unlock_tone);
		allClear();
	}
}

/// @brief 蜂鸣器方波输出
void rectWave() interrupt 1
{
	TR0 = 0;
	SPEAKER =! SPEAKER;
	TH0 = toneHigh;
	TL0 = toneLow;
	TR0 = 1;
}

void halfBeat(uchar t){
	uchar t1;
	uint t2;
	for(t1 = 0; t1 < t; t1++){
		for(t2 = 0; t2 < 16000; t2++){
			;
        }
	}
	TR0 = 0;
}

void melody(uchar time){
	TR0 = 1;
	halfBeat(time);                      
}

void playSound(uchar* song){
	uchar i, k, time;
	ET0 = 1;
	for (i = 0; i < 9; i += 3){
		k = song[i] + 7 * song[i + 1] - 1;
		toneHigh = FREQH[k];
		toneLow = FREQL[k];
		time = song[i + 2];
		melody(time);
	}
	ET0 = 0;
	TR0 = 0;
}
