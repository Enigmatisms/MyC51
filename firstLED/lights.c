#include <reg52.h>
#include <intrins.h>
#define uint unsigned int
#define uchar unsigned char

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
	bit intr = 1;
	uchar pos = 0x03;
	P0 = 0xff;
	for (i = 0; i < 200; i++){
		if (intr == 1){
			pos = _crol_(pos, 1);				// ���ú���ʵ�ּ򵥵�ѭ��λ�ƣ����ƵĻ��� _crol_
		}
		else {
			pos <<= 1;									// �Լ����߼�ʵ��
			if (pos == 0){
				pos = 1;		// pow(2, 0) = 1
			}
		}
		P0 = pos;
		delayMs(100);
	}
}	