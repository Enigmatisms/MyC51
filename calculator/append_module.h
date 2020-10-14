/**
 * ================= 其余模块 ====================
 * @brief 实现功能有：闹钟设置，45s定时关机
 * @date 2020.10.13
 * @author 何千越
*/
#ifndef __APPEND_MODULE_H__
#define __APPEND_MODULE_H__
#include "utils.h"


#define ALARM_OFF 0xffff
#define TH0_START 76
#define TL0_START 208
#define AUTO_SUSPEND 15

sbit LED_OUTPUT = P2^5;		// LED 灯输出
sbit SPEAKER = P2^3;		// 扬声器

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

