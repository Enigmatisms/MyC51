#include "utils.h"

uchar code line_offset[4] = {
	0x00, 0x40, 0x14, 0x54
};

uchar code sentences[8][20] = {
	"Testing LCD",
	"Hello world",
	"1234567890ABCDEDFXYZ",
	"6/2 = 3,1 + 3*2 = 7",
	"Rolling...",
	"Sentinel's work",
	"Let's do this!",
	"Where are you?"
};

int strlen(uchar ptr[20]){
	int i = 0;
	while(i < 20){
		if (ptr[i] < 0x0a){
			return i;
		}
		i++;
	}
	return 20;
}

void delayMs(uint ms){
	int i, j;
	for (i = 0; i < ms; i++){
		for (j = 0; j < 110; j++){
			;
		}
	}
}