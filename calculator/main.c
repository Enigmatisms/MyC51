#include "display_module.h"



void main(){
	uint i, start_row;
	Init();
	start_row = 0;
	while(1){
		for (i = start_row; i < start_row + 4; i++){
			writeLine(sentences[i % 8], i % 4, 1, RIGHT);
		}	
		start_row ++;
		start_row %= 8;
		delayMs(1000);
	}
}