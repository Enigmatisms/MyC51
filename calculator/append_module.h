#ifndef __APPEND_MODULE_H__
#define __APPEND_MODULE_H__
#include "utils.h"
#include<intrins.h>

sbit Bus=P1 ^ 0;//���ݵ�����

uint getTempResult();				//�������ս��
uint getTemp();						//��ȡ�¶��Ӻ���
bit sensorInit();					//��ʼ���Ӻ���
uchar readFromSensor();				//���ڴ����߶�ֵ
void tempConvert();					//��ʼת���¶�
void writeInSensor(uchar dat);		//����������д����
void delay10us(uint t);				//��ʱ10*t΢��

#endif 	//__APPEND_MODULE_H__