#include <reg52.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int

uchar lcd_table[10] = {
	0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f, 0x6f
};

sbit pos = P1 ^ 0;
sbit seg = P1 ^ 1;

void delayMs(uint ms){
	int i, j;
	for (i = ms; i > 0; i--){
		for (j = 110; j > 0; j--){
			;
		}
	}
}

void dynamicLights(){
	int i;
	uchar number = 0x01;
	for (i = 0; i < 1000; i++){
		P2 = number;
		number <<= 1;				// 循环左移
		if (number > 0x08){			// 最多移动到0b0000 1000
			number = 0x01;
		}
		P0 = lcd_table[i % 4] ^ 0xff;
		delayMs(5);
	}
}

void main(){
	pos = 1;
	seg = 1;
	dynamicLights();
}