#include "serial_talk.h"

uchar sendBuffer[20];
uchar buf_ptr;
uchar code testString[4][20] = {
	"Hello world!#",
	"C51 Regards!#",
	"Let's do this!#",
	"123456789ABXYZ#"
};

void send(){            // ���ݷ��ͳ���
	TH1 = 0xf4;                          // ������Ϊ2400
	TL1 = 0xf4;
	TR1 = 1;                             // ������ʱ��T1��T1�������ʵķ�������
	FLAG = 0;
	if (buf_ptr >= 20){
		sendBuffer[19] = '#';			// ��ֹ��
	}
	else {
		sendBuffer[buf_ptr] = '#';
	}
	for (buf_ptr = 0; buf_ptr < 20; buf_ptr ++){
		delayMs(80);
		if (sendBuffer[buf_ptr] <= 10){
			break;
		}
		else{
			SBUF = sendBuffer[buf_ptr];
			while(TI == 0);                       // �������жϱ�־λû����1(���ڷ�������)���͵ȴ�
			TI = 0;                               // ��������ɣ�TI�Զ���1�������������
		}
		if (sendBuffer[buf_ptr] == '#'){
			break;
		}
	}
	TI = 0;
	TR1 = 0;
	FLAG = 1;
}

void bufferInput(uchar dat){
	if (buf_ptr < 20){
		sendBuffer[buf_ptr++] = dat;
	}
}

void bufferReset(){
	for (buf_ptr = 0; buf_ptr < 20; buf_ptr ++){
		sendBuffer[buf_ptr] = '\0';
	}
	buf_ptr = 0;
}

void bufferPop(){
	if (buf_ptr > 0){					// buf ʼ��ָ����һ��Ҫ�����λ�ã���ջ����
		buf_ptr --;
		sendBuffer[buf_ptr] = '\0';
	}
}

void publisherInit(){
	TMOD = 0x20;                         // ��ʱ��T1�����ڷ�ʽ2�����Զ���װ��8λ��ʱ����
	SCON = 0x40;                         // ���ڹ�����ʽ1�����������
	PCON = 0x00;
	TH1 = 0xf4;                          // ������Ϊ2400
	TL1 = 0xf4;
	TR1 = 1;                             // ������ʱ��T1��T1�������ʵķ�������
	FLAG = 1;							 // �ⲿ�ж����½��ش���
	T0 = 0;
}