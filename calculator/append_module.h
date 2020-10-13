/**
 * ================= ����ģ�� ====================
 * @brief ʵ�ֹ����У��������ã�45s��ʱ�ػ�
 * @date 2020.10.13
 * @author ��ǧԽ
*/
#ifndef __APPEND_MODULE_H__
#define __APPEND_MODULE_H__
#include "utils.h"

#define ALARM_MAX 3599		// ����������59��59��
#define ALARM_OFF 0xffff
#define TH0_START 76
#define TL0_START 208

extern bit second_set;
extern uint alarm_time;
extern uint now_s;
extern uchar now_ms;

void getAlarmString(uchar* str);
void alarmSet(bit add);

#endif 	//__APPEND_MODULE_H__

