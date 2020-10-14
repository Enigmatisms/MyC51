/**
 * ================= ����ģ�� ====================
 * @brief ʵ�ֹ����У��������ã�45s��ʱ�ػ�
 * @date 2020.10.13
 * @author ��ǧԽ
*/
#ifndef __APPEND_MODULE_H__
#define __APPEND_MODULE_H__
#include "utils.h"


#define ALARM_OFF 0xffff
#define TH0_START 76
#define TL0_START 208
#define AUTO_SUSPEND 15

sbit LED_OUTPUT = P2^5;		// LED �����
sbit SPEAKER = P2^3;		// ������

extern bit second_set;
extern uint alarm_time;
extern uint now_s;
extern uchar now_ms;
extern uchar toneLow;
extern uchar toneHigh;

void getAlarmString(uchar* str);
void alarmSet(bit add);
void alarmReset(uint atime);

void melody(uchar time);
void playSound();
void halfBeat(uchar t);

#endif 	//__APPEND_MODULE_H__

