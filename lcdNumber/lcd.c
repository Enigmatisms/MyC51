#include <reg52.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int

uchar lcd_table[10] = {
	0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f, 0x6f
};
sbit seg = P1^0;		// 段选
sbit pos = P1^1;		// 位选

void delayMs(uint ms){
	int i, j;
	for (i = ms; i > 0; i--){
		for (j = 110; j > 0; j--){
			;
		}
	}
}

void main(){
	int i;
	uchar num, lights;
	seg = 1;
	pos = 1;
	lights = 0x1f;
	for (i = 0; i < 1000; i++){
		num = lcd_table[i % 10] ^ 0xff;
		P0 = num;
		lights = _crol_(lights, 1);
		P2 = lights;
		if (i % 10 == 8 || i % 10 == 9){	// 正常时应该 为8之后，9也会由于锁存而显示为8
			seg = 0;
		}
		else {
			seg = 1;
		}
		if (lights == 0x1f || lights == 0x3e){
			pos = 0;
		}
		else{
			pos = 1;
		}
		delayMs(600);
	}
}