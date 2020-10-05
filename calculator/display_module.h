/**
 * ================= LCD��ʾģ�� ====================
 * @brief LCD 20x4 ���������Լ���غ�
 * @date 2020.10.4
 * @author ��ǧԽ
*/

#ifndef __DISPLAY_MODULE_H__
#define __DISPLAY_MODULE_H__

#include <reg52.h>
#include <intrins.h>
#include "utils.h"

#define DELAY 1

// ================ LCD�� ===================//
#define INITIAL 			0x38
#define CLA 				0x01
#define DISPLAY_START 		0x80

#define CURSOR_BLINK 		0x0f
#define CURSOR_NON_BLINK 	0x0e
#define SHOW_CURSOR 		0x0d
#define NO_CURSOR 			0x0c
#define CURSOR_FORWARD 		0x06
#define CURSOR_BACKWARD 	0x04
#define DISPLAY_LEFT 		0x07
#define DISPLAY_RIGHT 		0x05
#define CURSOR_LEFT 		0x10
#define CURSOR_RIGHT 		0x14
#define ALL_LEFT 			0x18
#define ALL_RIGHT 			0x1c

// =============== ������ ================== //
#define CENTRAL 0
#define LEFT	1
#define RIGHT	2

sbit RS = P2 ^ 0;
sbit RW = P2 ^ 1;
sbit EN = P2 ^ 2;

extern uchar now_row;		// ��ǰ�����
extern uchar now_col;		// ��ǰ�����
extern uchar head_row;		// ��ǰ��Ļ���ַ����ﵽ����
extern uchar head_col;		// ��ǰ��Ļ���ַ����ﵽ����

void Init();
void doPop();				// ��βɾ��
void moveLeft();			// �������
void moveRight();			// �������

void writeCursor(uchar _data);	// ���߽��� + ����
void write(uchar _dat, bit data_flag);		// ��д��
void writeLine(uchar ptr[20], uint line, bit clear, uchar align);		// д����
void setCursor(uchar row, uchar col);
uchar checkBusy();
#endif 	//__DISPLAY_MODULE_H__