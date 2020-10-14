#include "display_module.h"
#include "keyboard_module.h"


void main(){
	uint pos, old_pos = 24;
	// ================= 中断设置 =====================
	TMOD = 0x01;		// 16位定时器
	ET0 = 1;			// 定时器中断 打开定时器中断ET1
	ET1 = 1;			
	EA = 1;
	TR0 = 1;				// 定时器打开
	
	
	Init();
	sensorInit();
	_mode = SUSPEND;	// 开始时挂起
	while(1){
		pos = sweepingScan();
		if (pos != 24 && pos == old_pos){
			continue;
		}
		if (pos  < 24){
			if (tobe_reset == 1 && pos != 5){		// 如果本来就按下AC键就没必要再清除一次
				allClear();
				tobe_reset = 0;
			}
			if (alarm_time == ALARM_OFF){	// 没有闹钟时，每次有按键事件都会刷新定时
				now_s = 0;
				now_ms = 0;
			}
			if (sets[1] == 1){
				pressingSound();
			}
			keyboardEvent(pos);
		}
		if (_mode == ALARMING){				
			alarmReset(ALARM_OFF);		// 闹钟显示功能不能使用中断实现（产生复入问题）
			alarmingEffect();			// 闹钟结束后，自动设为计算模式
		}
		else if(_mode == SUSPEND && suspend_lock == 0){
			suspend_lock = 1;
			drawSuspend();
		}
		delayMs(10);
		old_pos = pos;
	}
}