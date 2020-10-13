/**
 * ================= �¶ȴ�����ģ�� ====================
 * @brief Temperature Sensor DS018B20 ���������Լ���غ�
 * @date 2020.10.11
 * @author ��ǧԽ
*/
#ifndef __SENSOR_MODULE_H__
#define __SENSOR_MODULE_H__
#include "utils.h"
#include<intrins.h>

sbit Bus=P1 ^ 0;//���ݵ�����

uint getTempResult();				//�������ս��
uint getTemp();						//��ȡ�¶��Ӻ���
bit sensorReset();					//��ʼ���Ӻ���
void initializeSensor();
uchar readFromSensor();				//���ڴ����߶�ֵ
void tempConvert();					//��ʼת���¶�
void writeInSensor(uchar dat);		//����������д����
void delay10us(uint t);				//��ʱ10*t΢��

#endif 	//__SENSOR_MODULE_H__