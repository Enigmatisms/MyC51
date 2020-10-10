#include "display_module.h"
#include "keyboard_module.h"


void main(){
	uint pos, old_pos = 24;
	Init();
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
			keyboardEvent(pos);
		}
		delayMs(10);
		old_pos = pos;
		
	}
}