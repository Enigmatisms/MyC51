#include "display_module.h"
#include "keyboard_module.h"


void main(){
	uint pos, old_pos = 24;
	// ================= �ж����� =====================
	TMOD = 0x01;		// 16λ��ʱ��
	ET0 = 1;			// ��ʱ���ж� �򿪶�ʱ���ж�ET1
	ET1 = 1;			
	EA = 1;
	TR0 = 1;				// ��ʱ����
	
	
	Init();
	sensorInit();
	_mode = SUSPEND;	// ��ʼʱ����
	while(1){
		pos = sweepingScan();
		if (pos != 24 && pos == old_pos){
			continue;
		}
		if (pos  < 24){
			if (tobe_reset == 1 && pos != 5){		// ��������Ͱ���AC����û��Ҫ�����һ��
				allClear();
				tobe_reset = 0;
			}
			if (alarm_time == ALARM_OFF){	// û������ʱ��ÿ���а����¼�����ˢ�¶�ʱ
				now_s = 0;
				now_ms = 0;
			}
			if (sets[1] == 1){
				pressingSound();
			}
			keyboardEvent(pos);
		}
		if (_mode == ALARMING){				
			alarmReset(ALARM_OFF);		// ������ʾ���ܲ���ʹ���ж�ʵ�֣������������⣩
			alarmingEffect();			// ���ӽ������Զ���Ϊ����ģʽ
		}
		else if(_mode == SUSPEND && suspend_lock == 0){
			suspend_lock = 1;
			drawSuspend();
		}
		delayMs(10);
		old_pos = pos;
	}
}