#include <reg52.h>
#include <intrins.h>
#define uint unsigned int
#define uchar unsigned char

/**
��Ҫʵ�ֵĹ���
	ʹ�ö�ʱ�����ж�ʱ
	�����жϵķ�ʽ���м��������������ҿ���������
	�õ�һ������Ϊ��λ�ļ�����������¼99s
**/

sbit lock = P2 ^ 0;		// �������λ
sbit lcd1 = P2 ^ 1;		// ʮλ����ʾ��Ӧ��lcd λѡ��������lcd�ߵ�ƽ���Ӧlcd����ʾ
sbit lcd2 = P2 ^ 2;		// ��λ��ʾ
int counter = 0;
int ms_counter = 0;		// ���������
uint tenth = 0, unit = 0, delay_cycle = 24;		// ʮλ��λ����
const uchar th0 = (65536 - 50000) / 256, lowt0 = (65536 - 50000) % 256;	// ��ʼλ����

uchar lcd_table[10] = {
	0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f, 0x6f
};

/// @brief ��ʱ���жϺ��� ���ﵽһ��ʱ��֮���Զ�ִ�У�
/// counter ���������ҽ���ȡģ����
/// ��ȡʮλ��λ���֣�ʹ��λѡ���������
/// ��ʱ�ò�������
void timerT0() interrupt 1
{
	TH0 = th0;
	TL0 = lowt0;
	ms_counter++;
	if (ms_counter > 10){
		counter++;
		unit = counter % 10;
		if (unit == 0){			// ÿ�θ�λΪ0��ʱ��ʮλ��λ��������ģ
			tenth += 1;
			tenth %= 10;
		}
		ms_counter = 0;
	}
}

void delay(uint ms){
	int j;
	for (j = ms; j > 0; j--){
		;
	}
}

void main(){
	TMOD = 0x01;			// ��ʱ��0 M1M0 Ϊ 0x01 ��ʾ16 λ������
	TH0 = th0;				
	TL0 = lowt0;
	EA = 1;					// ���жϴ�
	ET0 = 1;				// T0��ʱ����
	TR0 = 1;				// ����T0��ʱ����
	lock = 1;
	while(1){				// �˴�����ʹ��������ȡ��
		lcd1 = 1;
		lcd2 = 0;
		P0 = lcd_table[tenth] ^ 0xff;
		delay(delay_cycle);
		lcd1 = 0;
		lcd2 = 1;
		P0 = lcd_table[unit] ^ 0xff;
		delay(delay_cycle);
		if (counter > 99){
			counter = 0;	// �������
		}
	}
}