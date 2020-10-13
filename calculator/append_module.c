#include "append_module.h"


bit second_set = 1;
uint now_s = 0;
uchar now_ms = 0;
uint alarm_time = 15;		// 65534s 为上限 (65535 被留做闹钟关闭指示)

void alarmSet(bit add){
	if (add == 1 && alarm_time < ALARM_MAX){
		alarm_time ++;
	}
	else if (add == 0 && alarm_time > 0){
		alarm_time --;
	}
}

/// @param 输出9位数字 [00]m 00s
void getAlarmString(uchar* str){
	uchar minute, second;
	minute = alarm_time / 60;
	second = alarm_time % 60;
	if (second_set == 1){
		str[0] = ((uchar)(minute / 10) + 48);
		str[1] = minute % 10;
		str[2] = 'm';
		str[3] = ' ';
		str[4] = '[';
		str[5] = ((uchar)(second / 10) + 48);
		str[6] = second % 10;
		str[7] = ']';
		str[8] = 's';
	}
	else{
		str[0] = '[';
		str[1] = ((uchar)(minute / 10) + 48);
		str[2] = minute % 10;
		str[3] = ']';
		str[4] = 'm';
		str[5] = ' ';
		str[6] = ((uchar)(second / 10) + 48);
		str[7] = second % 10;
		str[8] = 's';
	}
}

void timerT0() interrupt 0
{
	TH0 = TH0_START;
	TL0 = TL0_START;
	now_ms ++;
	if (now_ms >= 20){
		now_ms = 0;
		now_s ++;
	}
	if (now_s >= alarm_time){
		;
	}
}