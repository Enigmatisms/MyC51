#include <reg52.h>
#include <intrins.h>
#include "utils.h"
#include "append_module.h"
#include <limits.h>

sbit LED = P1 ^ 1;

uchar lcd_table[10] = {
	0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f, 0x6f
};



/// uint 只显示8位
void dynamicLights(float input){
	float i;
	uchar now, cs = 0x01;
	for (i = 10.0; i > 1e-3; i /= 10.0){
		P2 = cs;
		cs <<= 1;
		if (cs > 0x10){
			cs = 0x01;
		}
		now = (uchar)(input / i) % 10;
		input -= (float)now * i;
		P0 = lcd_table[now] ^ 0xff;		// 共阴极接法
		
		delayMs(6);
	}
}

void main(){
	float temp;
	P2 = 0x00;
	LED = 1;
	temp = getTempResult();
	LED = 0;
	while(1){
		dynamicLights(temp);
	}
}