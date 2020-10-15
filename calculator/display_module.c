#include "display_module.h"

uchar now_row = 1;
uchar now_col = 0;
uchar head_row = 1;
uchar head_col = 0;
uint _temp = 25;

bit tobe_reset = 0;
uchar buffer[24];
bit use_cel = 1;			// ʹ�����϶���ʾ

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
  status = P0; 	//����P0���λ״ֵ̬
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
	P0 = _data;
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
	if (alarm_time == ALARM_OFF){
		writeLine(alarm_info[4], 0, 1, CENTRAL);
	}
	else{
		writeLine(alarm_info[5], 0, 1, CENTRAL);
	}
	write(SHOW_CURSOR, 0);
	setCursor(1, 0);
	_mode = CALC;
	for (i = 0; i < 24; i++){
		*(buffer + i) = 0;
	}
	suspend_lock = 0;
}


/// ���2 @brief ��������ģʽ
void settings(){
	allClear();
	write(NO_CURSOR, 0);		// �رչ��
	writeLine("***** Settings *****", 0, 0, LEFT);
	_mode = SETS;
	drawSettings();
}

/// ���3 @brief �������˵�
void mainMenu(){
	allClear();
	write(NO_CURSOR, 0);		// �رչ��
	writeLine("******* Menu *******", 0, 0, LEFT);
	_mode = MENU;
	drawMainMenu();
}

/// ���4 @brief �ȺŲ��� ���������Լ����˵��б�ʾȷ�����߸��ģ�
void yieldResult(){
	uchar result, err, buf[3];
	if (_mode == 0){
		setCursor(head_row, head_col);
		if ((head_row - 1) * 20 + head_col > 21){
			drawError(0x02);			// ջ���
		}
		err = stackInput(buffer, &result);
		if (err != 0x03){
			drawError(err);
		}
		else{
			buf[0] = (uchar)(result / 100) + 48;
			buf[1] = (uchar)((result - (buf[0] - 48) * 100) / 10) + 48;
			buf[2] = result % 10 + 48;
			writeLine(buf, 3, 1, RIGHT);
			tobe_reset = 1;
		}
	}
	else if(_mode < MENU){
		sets[_mode - 1] = 1 - sets[_mode - 1];
		LED_OUTPUT = 1 - sets[2];
		drawSettings();
	}
	else if (_mode < IN_SENSOR){
		
		switch(_mode){
			case MENU: 
				allClear();
				_mode = CALC; break;
			case TEMP_SENSOR:
				allClear();
				write(NO_CURSOR, 0);
				_mode = IN_SENSOR;
				_temp = getTempResult();
				use_cel = 1; 
				drawTemperature(0);
				break;
			case ALARM_SET: 
				_mode = IN_ALARM;
				drawAlarmUI(0);					// 0 ��ʶ�����������г�ʼ���Լ����Ƴ�ʼUI�Ĺ���
			break;								///@todo 
		}
	}
	else if(_mode == IN_ALARM){
		TR0 = 1;
		allClear();								// ���óɹ�
	}
}

/// ���5 @brief �����ƶ���� ���������Լ����˵��б�ʾ���ƣ�
void moveLeft(){
	if (_mode == CALC){
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
	else if (_mode < MENU){
		_mode = (_mode + 1) % 3 + 1;
		drawSettings();
	}
	else if (_mode < IN_SENSOR){
		_mode = (_mode + 1) % 3 + 4;
		drawMainMenu();
	}
	else if (_mode == IN_SENSOR){						// 7 Ϊ�������¶���ʾ	8 Ϊ���ӵ���
		_temp = getTempResult();
		use_cel = !use_cel;			// �л����϶Ȼ��϶�ת��
		drawTemperature(1);
	}
	else {
		second_set = ~second_set;
		drawAlarmUI(1);
	}
}

/// ���6 @brief �����ƶ���� ���������Լ����˵��б�ʾ���ƣ�
void moveRight(){
	if (_mode == CALC){
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
	else if (_mode < MENU){
		_mode = (_mode) % 3 + 1;
		drawSettings();
	}
	else if (_mode < IN_SENSOR){
		_mode = (_mode) % 3 + 4;
		drawMainMenu();
	}
	else if (_mode == IN_SENSOR){
		_temp = getTempResult();
		use_cel = !use_cel;
		drawTemperature(1);
	}
	else {
		second_set = ~second_set;
		drawAlarmUI(1);
	}
}

void drawMainMenu(){
	uint i;
	for (i = 0; i < 3; i++){
		writeLine(menuItems[i], i + 1, 1, LEFT);
		if (i + 4 == _mode){
			writeLine("<<<", i + 1, 0, RIGHT);
		}
	}
}

void drawSettings(){
	uint i;
	for (i = 0; i < 3; i++){
		writeLine(settingItems[i], i + 1, 1, LEFT);
		if (i + 1 == _mode){
			if (sets[i] == 0){
				writeLine(" OFF <<<", i + 1, 0, RIGHT);
			}
			else {
				writeLine(" ON <<<", i + 1, 0, RIGHT);
			}
		}
		else{
			if (sets[i] == 0){
				writeLine(" OFF ", i + 1, 0, RIGHT);
			}
			else {
				writeLine(" ON ", i + 1, 0, RIGHT);
			}
		}
	}
}

void drawError(uchar err){
	allClear();
	writeLine("********************", 0, 0, LEFT);
	writeLine(errors[err], 1, 1, CENTRAL);
	writeLine("********************", 2, 0, LEFT);
	delayMs(1500);
	allClear();
}

void drawTemperature(bit skip){
	uchar temp_str[4];
	if (skip == 0){
		writeLine(temp_info[0], 0, 1, LEFT);
		writeLine(temp_info[1], 3, 1, LEFT);
	}
	if (_temp > 30){
		writeLine(describe[0], 2, 1, CENTRAL);
	}
	else if (_temp > 20){
		writeLine(describe[1], 2, 1, CENTRAL);
	}
	else if (_temp > 10){
		writeLine(describe[2], 2, 1, CENTRAL);
	}
	else {
		writeLine(describe[3], 2, 1, CENTRAL);
	}
	tempDisplay(_temp, use_cel, temp_str);
	if (use_cel == 1){
		writeLine(temp_info[2], 1, 1, LEFT);		// ���϶����
		
	}
	else{
		writeLine(temp_info[3], 1, 1, LEFT);		// ���϶����
	}
	writeLine(temp_str, 1, 0, RIGHT);
}

void drawAlarmUI(bit skip){			// �����������ý��棨skip ����ĳЩ������ƣ�
	uchar i, astr[10];
	if (skip == 0){
		alarmReset(6);
		for (i = 0; i < 4; i++){
			writeLine(alarm_ui[i], i, 1, LEFT);
		}
		TR0 = 0;
	}
	getAlarmString(astr);
	writeLine(astr, 2, 0, RIGHT);
}

void alarmingEffect(){
	uchar i;
	for (i = 0; i < 4; i++){
		writeLine(alarm_info[i], i, 1, CENTRAL);
	}
	/// @todo
	playSound();
	delayMs(2000);
	allClear();
}

void drawSuspend(){
	uchar i;
	for (i = 0; i < 3; i++){
		writeLine(suspend_ui[i], i, 1, CENTRAL);
	}
	writeLine(suspend_ui[0], 3, 1, CENTRAL);
}
