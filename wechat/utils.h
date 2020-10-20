/**
 * ================= ���ú����Լ����� ====================
 * @date 2020.10.4
 * @author ��ǧԽ
*/
#ifndef __UTILS_H__
#define __UTILS_H__

#include <reg52.h>
#define uint unsigned int
#define uchar unsigned char
	

#define CENTRAL 0
#define LEFT	1
#define RIGHT	2
#define CHATTING 	0		// ����ģʽ
#define LOCKED		1		// ����
#define FAULTS		2		// �����������3�Σ�

extern uchar _mode;			// 
extern uchar counter;		// ����������
	
// ��ƫ��
extern uchar code line_offset[4];

extern uchar code FREQH[28];

extern uchar code FREQL[28];

extern uchar code message_tone[9];
extern uchar code unlock_tone[9];
extern uchar code error_tone[9];

extern uchar code password[9];

extern uchar code lock_info[3][20];

extern uchar code wechat_info[4][20];

int strlen(uchar* ptr);

void delayMs(uint ms);

#endif 	//__UTILS_H__