#include "serial_listen.h"

uchar receiveBuffer[20];
uchar buffer_ptr = 0;
bit ready = 0;
bit draw_allow = 0;

void subscriberInit(){
	TMOD = 0x20;                     //���ö�ʱ��T1�����ڷ�ʽ2
	SCON = 0x50;                     //���ڹ�����ʽ1�������������
	PCON = 0x00;                     //�����ʲ�����
	TH1 = 0xf4;                      //������Ϊ2400b/s
	TL1 = 0xf4;
	TR1 = 1;                         //������ʱ��T1
	REN = 1;                         //�����������
	EX0 = 1;						 // ���ⲿ�ж�0����Ϊ���ս�����־
	EA = 1;
	IT0 = 1;						 // �½��ش���
	T0 = 0;
}

void receive() {        	
	uchar i, j, temp;
	for (i = 0; i < 250; i++){		// TIMEOUTʱ�� 250ms
		for (j = 0; j < 110; j++){
			if (RI != 0){
				break;
			}
		}
		if (j < 110){
			break;
		}
	}
	RI = 0;                           				// �������ʱ����
	if (buffer_ptr < 20){
		temp = SBUF;         // �����ջ������е����ݴ���dat
		if (temp == '#'){
			ready = 0;
			draw_allow = 1;
			return;
		}
		else {
			receiveBuffer[buffer_ptr] = temp;
			buffer_ptr++;
		}
	}
	else {
		ready = 0;
		draw_allow = 1;
	}
}

void bufferReset(){
	for (buffer_ptr = 19; buffer_ptr >= 0; buffer_ptr--){
		receiveBuffer[buffer_ptr++] = '\0';
	}
}

// �ӵ��������ѣ���ʼ������
void receiveStart() interrupt 0
{
	ready = 1;
}