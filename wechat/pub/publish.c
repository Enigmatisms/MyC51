#include "serial_talk.h"
#include "keyboard_module.h"

void main(){
	uint pos, old_pos = 40;
	P1 = 0x00;
	publisherInit();
	while(1) {
		if (T0 == 0){
			pos = sweepingScan();
			if (pos != 40 && pos == old_pos){
				continue;
			}
			if (pos < 40){
				keyboardEvent(pos);
			}
			delayMs(10);
			old_pos = pos;
		}
	}
}