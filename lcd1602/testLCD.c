#include <reg52.h>
#include <intrins.h>
#include <string.h>
#define uint unsigned int
#define uchar unsigned char
#define DELAY 1

// ================ �������� ===================//
#define INITIAL 0x38
#define CLA 0x01
#define DISPLAY_START 0x80

#define CURSOR_BLINK 0x0f
#define CURSOR_NON_BLINK 0x0e
#define SHOW_CURSOR 0x0d
#define NO_CURSOR 0x0c
#define CURSOR_FORWARD 0x06
#define CURSOR_BACKWARD 0x04
#define DISPLAY_LEFT 0x07
#define DISPLAY_RIGHT 0x05
#define CURSOR_LEFT 0x10
#define CURSOR_RIGHT 0x14
#define ALL_LEFT 0x18
#define ALL_RIGHT 0x1c

// ��ƫ��
uchar code line_offset[4] = {
	0x00, 0x40, 0x14, 0x54
};

uchar code test[4][20] = {
	"Testing LCD",
	"Hello world",
	"1234567890ABCDEDFXYZ",
	"6/2 = 3,1 + 3*2 = 7",
};

// ===============================================//
	
sbit RS = P2 ^ 0;	// H ���� / L ָ��
sbit RW = P2 ^ 1;	// H �� / L д
sbit EN = P2 ^ 2;	// EN ʹ�� H Enable

void delayMs(uint ms){
	int i, j;
	for (i = 0; i < ms; i++){
		for (j = 0; j < 110; j++){
			;
		}
	}
}

uchar busyCheck()   //æ���
{
  uchar	LCD_Status;
  RS = 0;	 
  RW = 1;	 
  EN = 1;	 
  delayMs(DELAY);
  LCD_Status = P0; 	//����P0���λ״ֵ̬
  EN = 0;
  return LCD_Status;
}

/// д�����ݻ���ָ��
void write(uchar _data, bit data_flag){
	while((busyCheck()&0x80)==0x80);
	RW = 0;
	RS = data_flag;		// data_flagΪ1ʱΪд������
	EN = 0;
	delayMs(DELAY);
	EN = 1;
	P0 = _data;
	delayMs(DELAY);
	EN = 0;				// Լ2 * DELAY ms������
}

/// @todo ���Ӿ��У������ʾ���Ҳ���ʾ��ģʽ
void writeLine(uchar _data[20], uint line){
	uint index = 0;
	write(DISPLAY_START | line_offset[line], 0);	// ������λ��
	while(_data[index] >= 10 && index < 20){
		write(_data[index], 1);
		delayMs(DELAY);
		index ++;
	}
}

//void cursorSetting(uchar com){
//	write(CURSOR_FORWARD, 0);
//}

void Init(){
	write(INITIAL, 0);
	delayMs(DELAY);
	write(CLA, 0);
	delayMs(DELAY);
	write(NO_CURSOR, 0);
	delayMs(DELAY);
	write(CURSOR_FORWARD, 0);
//	write(CURSOR_BLINK, 0);
	RW = 0;
}

void main(){
	uint row;
	Init();
	for (row = 0; row < 4; row ++){
		writeLine(test[row], row);
	}
	while(1);
}


