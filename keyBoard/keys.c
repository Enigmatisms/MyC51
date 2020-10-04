#include <reg52.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int
// 简单的矩阵键盘检测

//uchar codes[16] = {
//	0xEE, 0xED, 0xEB, 0xE7, 0xDE, 0xDD, 0xDB, 0xD7, 0xBE, 0xBD, 0xBB, 0xB7, 0x7E, 0x7D, 0x7B, 0x77
//};

uchar output[4] = {
	0xfe, 0xfd, 0xfb, 0xf7
};

uchar lcd_table[16] = {
	0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71
};



void delayMs(uint ms){
	uint i, j;
	for (i = 0; i < ms; i++){
		for (j = 0; j < 110; j++){
			;
		}
	}
}

uint sweepingScan(){
	int i, j;
	uchar res = 0x00;
	for (i = 0; i < 4; i++){
		P3 = output[i];
		for (j = 0 ; j < 4; j++){
			res = P3 & 0xf0;				// 只取高四位
			if (res != 0xf0){				// P3 第四位变0后的结果如果为0b1111 0000 说明没有对应键盘响应
				switch (res){
					case 0xe0: return 4 * i;
					case 0xd0: return 4 * i + 1;
					case 0xb0: return 4 * i + 2;
					case 0x70: return 4 * i + 3;
				}
			}
		}
	}
	return 16;			// 没有键盘事件
}

void main(){
	uint resp = 16, old_resp = 0;
	P0 = 0x80;
	while (1){
		resp = sweepingScan();
		if (old_resp == resp){			// 如果按键一直按住不放，old_resp 会持续等于 resp, 此时将会跳过
			continue;
		}
		if (resp < 16){
			P0 = lcd_table[resp];
		}
		else {
			P0 = 0x80;
		}
		old_resp = resp;
		delayMs(10);
	}
}