#include "serial_listen.h"
#include "display_module.h"

void main(){
	Init();
	subscriberInit();
	writeLine("Test", 0, 1, CENTRAL);
	while (1){
		if (ready == 1){
			ALE = 1;
			receive();
		}
		else{
			ALE = 0;
		}
		if (draw_allow == 1){
			writeLine(receiveBuffer, 1, 1, LEFT);
			draw_allow = 0;
			bufferReset();
		}
	}
}