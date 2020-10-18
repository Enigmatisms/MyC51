#include "display_module.h"

uchar now_row = 1;
uchar now_col = 0;
uchar head_row = 1;
uchar head_col = 0;
uint _temp = 25;

uchar buffer[20];

void Init(){
	write(INITIAL, 0);
	write(CLA, 0);
	write(SHOW_CURSOR, 0);
	write(CURSOR_FORWARD, 0);
	write(CURSOR_BLINK, 0);
	allClear();
}

uchar busyCheck()   //æ���
{
  uchar	status;
  RS = 0;	 
  RW = 1;	 
  EN = 1;	 
  delayMs(DELAY);
  status = P1; 	//����P1���λ״ֵ̬
  EN = 0;
  return status;
}

/// д�����ݻ���ָ��
void write(uchar _data, bit data_flag){
	while((busyCheck()&0x80) == 0x80);
	RW = 0;
	RS = data_flag;		// data_flagΪ1ʱΪд������
	EN = 0;
	delayMs(DELAY);
	EN = 1;
	P1 = _data;
	delayMs(DELAY);
	EN = 0;				// Լ2 * DELAY ms������
}

// ����β����
void writeCursor(uchar _data){
	if ((now_row != head_row) || (now_col != head_col)){		// ���ڹ�겻�����λ�ö���ʱ��ֻ�ı䵱ǰλ��
		if (now_col < 19){
			write(_data, 1);
			buffer[(now_row - 1) * 20 + now_col] = _data;
			now_col ++;
		}
		else{
			if (now_row == 1){
				write(_data, 1);
				buffer[(now_row - 1) * 20 + now_col] = _data;
				setCursor(2, 0);		// ���λ�øı䵽��һ��
				now_col = 0;
				now_row = 2;
			}
		}
	}
	else{								// ���δ����ʱֻ���ĵ�ǰλ���ϵ��ַ�������Ӱ�����
		if (head_col < 19){
			write(_data, 1);
			buffer[(head_row - 1) * 20 + head_col] = _data;
			buffer[(head_row - 1) * 20 + head_col] = _data;
			head_col ++;
			now_col = head_col;
		}
		else{
			if (head_row == 1){
				write(_data, 1);
				buffer[(head_row - 1) * 20 + head_col] = _data;
				setCursor(2, 0);		// ���λ�øı䵽��һ��
				head_col = 0;
				head_row = 2;
				now_row = head_row;
				now_col = head_col;
			}
		}
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

//========================����ƶ�������д��/ɾ��/������λ��==========================

void setCursor(uchar row, uchar col){
	write(DISPLAY_START + line_offset[row] + col, 0);
}

/// ���0 @briefɾ����ĩ�ַ�
void doPop(){
	if (_mode){
		return;
	}
	if ((now_row != head_row) || (now_col != head_col)){
		now_row = head_row;
		now_col = head_col;
		setCursor(head_row, head_col);
	}
	if (head_col != 0){
		head_col --;
		now_col --;
		write(CURSOR_LEFT, 0);		// ����ƶ���ĩβ�ַ���	
		write(' ', 1);				// ���
		write(CURSOR_LEFT, 0);		// ���ڹ��һֱ��ȡ���Ƶķ�ʽ��д���Ժ������һλ������Ҫ����
		buffer[(head_row - 1) * 20 + head_col] = 0;
	}
	else{
		if (head_row > 1){
			head_row = 1;
			head_col = 19;
			now_row = head_row;
			now_col = head_col;
			setCursor(1, 19);
			write(' ', 1);
			setCursor(1, 19);		// ����ɾ��ʱ���ɵڶ��е���һ�����˻ع�꣬��ɾ�������ƶ���굽�ڶ�������
			buffer[(head_row - 1) * 20 + head_col] = 0;
		}
	}
}

/// ���1 @brief AC @todo �˺���Ҫ���ӣ����ջ����������
void allClear(){
	int i;
	write(CLA, 0);
	head_row = 1;
	head_col = 0;
	now_row = head_row;
	now_col = head_col;
	/// @todo: �˴���Ҫ�������һ������һ��������ʾ
//	if (alarm_time == ALARM_OFF){
//		writeLine(alarm_info[4], 0, 1, CENTRAL);
//	}
//	else{
//		writeLine(alarm_info[5], 0, 1, CENTRAL);
//	}
	write(SHOW_CURSOR, 0);
	setCursor(1, 0);
	_mode = CHATTING;
	for (i = 0; i < 20; i++){
		*(buffer + i) = 0;
	}
}

/// ���4 @brief �ȺŲ��� ���������Լ����˵��б�ʾȷ�����߸��ģ�
void yieldResult(){
	uchar result, buf[3];
	if (_mode == 0){
		setCursor(head_row, head_col);
		buf[0] = (uchar)(result / 100) + 48;
		buf[1] = (uchar)((result - (buf[0] - 48) * 100) / 10) + 48;
		buf[2] = result % 10 + 48;
		writeLine(buf, 3, 1, RIGHT);
	}
}

/// ���5 @brief �����ƶ���� ���������Լ����˵��б�ʾ���ƣ�
void moveLeft(){
	if (_mode == CHATTING){
		if (now_col > 0){
			now_col --;
			write(CURSOR_LEFT, 0);
		}
		else {
			if (now_row > 1){
				now_row = 1;
				now_col = 19;
				setCursor(1, 19);
			}
		}
	}
	else {
		_mode = (_mode + 1) % 3 + 1;
	}
}

/// ���6 @brief �����ƶ���� ���������Լ����˵��б�ʾ���ƣ�
void moveRight(){
	if (_mode == CHATTING){
		if (now_row == head_row && now_col >= head_col){			// ����������
			return;
		}
		if (now_col < 19){
			now_col ++;
			write(CURSOR_RIGHT, 0);
		}
		else {
			if (now_row < 2){
				now_row = 2;
				now_col = 0;
				setCursor(2, 0);
			}
		}
	}
	else {
		_mode = (_mode) % 3 + 1;
	}
}

void drawSuspend(){
	uchar i;
	for (i = 0; i < 3; i++){
		writeLine(suspend_ui[i], i, 1, CENTRAL);
	}
	writeLine(suspend_ui[0], 3, 1, CENTRAL);
}
