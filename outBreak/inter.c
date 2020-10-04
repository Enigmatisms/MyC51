#include <reg52.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int
	
sbit lock = P2^0;
sbit sign = P2^1;
bit odd_lights = 1, unlock_state = 1;		// Ϊunlock = 0ʱ��ס

void waitKey(uint ms){
	int i, j;
	for (i = 0; i < ms; i++){
		for (j = 0; j < 110; j++){
			;
		}
	}
}

// ȫ��ѡΪ�½��ش���
// ���ܵ���ģʽ�л�ָʾ INT0
void interrupt0() interrupt 0
{
	odd_lights = ~odd_lights;
	waitKey(15);
}

// ����������ģʽ�л�ָʾ INT1
void interrupt1() interrupt 2
{
	unlock_state = ~unlock_state;
	lock = unlock_state;
	waitKey(10);
}

/**
������()interrupt 0 {} //��Ӧ�ⲿbai��du��0��
������()interrupt 1 {} //��Ӧ��ʱ��zhi/������0�жϣ�
������()interrupt 2 {} //��Ӧ�ⲿ�ж�1��
������()interrupt 3 {} //��Ӧ��ʱ��/������1�жϣ�
������()interrupt 4 {} //��Ӧ�����жϣ�
һ��5���жϣ����ȼ��������¡�
�ô����ж���ţ��ᵼ���޷������ж�
*/

void main(){
	EA = 1;
	EX0 = 1;
	EX1 = 1;
	IT0 = 1;		// �½��ش���
	IT1 = 1;		// �½��ش���
	while(1){
		if (odd_lights == 1){
			P0 = 0x55;
		}
		else{
			P0 = 0xaa;
		}
		sign = unlock_state;		// ������������״̬ʱ������
	}
}