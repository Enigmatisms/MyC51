/// ��Ϣ����
#ifndef __SERIAL_TALK_H__
#define __SERIAL_TALK_H__
#include "utils.h"
#include <intrins.h>

sbit FLAG = P3 ^ 2;

extern uchar sendBuffer[20];
extern uchar buf_ptr;
extern uchar code testString[4][20];
extern uchar test_ptr;

void send();
void bufferInput(uchar dat);	// ��������
void bufferReset();				// ��ջ���
void bufferPop();				// ɾ��һ��ֵ
void messageBuzz();				// ��Ϣ������ʾ��
void publisherInit();

#endif 	//__SERIAL_TALK_H__