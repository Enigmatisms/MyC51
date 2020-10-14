#include "append_module.h"

uint now_s = 0;
uchar now_ms = 0;
uchar toneHigh, toneLow;
uint alarm_time = ALARM_OFF;			// ����ʱ��
bit second_set = 1;					// ��������

void alarmReset(uint atime){	// �������ã���ʱ���رգ��жϹرգ��������ã�
	alarm_time = atime;
	now_s = 0;
	now_ms = 0;
	TH0 = TH0_START;
	TL0 = TL0_START;
	second_set = 1;
}

void alarmSet(bit add){
	if (add == 1){
		if (second_set == 0 && alarm_time < ALARM_MAX - 59){
			alarm_time += 60;
		}
		else if(second_set == 1 && alarm_time < ALARM_MAX){
			alarm_time ++;
		}
	}
	else {
		if (second_set == 0 && alarm_time > 59){
			alarm_time -= 60;
		}
		else if(second_set == 1 && alarm_time > 0){
			alarm_time --;
		}
	}
}

/// @param ���10λ���� [00]m 00s(\0)
void getAlarmString(uchar* str){
	uchar minute, second;
	minute = alarm_time / 60;
	second = alarm_time % 60;
	if (second_set == 1){
		str[0] = ((uchar)(minute / 10) + 48);
		str[1] = minute % 10 + 48;
		str[2] = 'm';
		str[3] = ' ';
		str[4] = '[';
		str[5] = ((uchar)(second / 10) + 48);
		str[6] = second % 10 + 48;
		str[7] = ']';
	}
	else{
		str[0] = '[';
		str[1] = ((uchar)(minute / 10) + 48);
		str[2] = minute % 10 + 48;
		str[3] = ']';
		str[4] = 'm';
		str[5] = ' ';
		str[6] = ((uchar)(second / 10) + 48);
		str[7] = second % 10 + 48;
	}
	str[8] = 's';
	str[9] = 0;
}

// ��ʱ���ж�1
void timerT0() interrupt 1
{
	TH0 = TH0_START;
	TL0 = TL0_START;
	now_ms ++;
	if (now_ms >= 20){
		now_ms = 0;
		now_s ++;
	}
	if (now_s > AUTO_SUSPEND && alarm_time == ALARM_OFF && sets[0] == 1){	// ��������ʱ�䣬���������ӣ��Զ���������1
		_mode = SUSPEND;			// �Զ�����
		return;
	}
	if (alarm_time != ALARM_OFF && now_s >= alarm_time){		// ��������ʱ�䣬������������
		_mode = ALARMING;		
	}
}

/// @brief �������������
void rectWave() interrupt 3
{
	TR1 = 0;
	SPEAKER =! SPEAKER;
	TH1 = toneHigh;
	TL1 = toneLow;
	TR1 = 1;
}

void halfBeat(uchar t){
	uchar t1;
	uint t2;
	for(t1 = 0; t1 < t; t1++){
		for(t2 = 0; t2 < 16000; t2++){
			;
        }
	}
	TR1 = 0;
}

void melody(uchar time){
	TR1= 1;
	halfBeat(time);                      
}

void playSound(){
	uchar i, k, time;
	for (i = 0; i < 84; i += 3){
		k = song[i] + 7 * song[i + 1] - 1;
		toneHigh = FREQH[k];
		toneLow = FREQL[k];
		time = song[i + 2];
		melody(time);
	}
	TR1 = 0;
}

void pressingSound(){		// ������
	uchar time;
	toneHigh = 242;
	toneLow = 66;
	time = 3;
	melody(time);
	TR1 = 0;
}