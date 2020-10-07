#include "display_module.h"
#include "keyboard_module.h"


void main(){
	uint i, start_row, pos, old_pos = 24;
	Init();
	start_row = 0;
	while(1){
		pos = sweepingScan();
		if (pos != 24 && pos == old_pos){
			continue;
		}
		if (pos  < 24){
			keyboardEvent(pos);
		}
		delayMs(10);
		old_pos = pos;
		
	}
}