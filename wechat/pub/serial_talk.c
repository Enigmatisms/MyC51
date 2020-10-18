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
	for (buf_ptr = 0; buf_ptr < 20; buf_ptr ++){
		delayMs(80);
		if (testString[3][buf_ptr] <= 10){
			break;
		}
		else{
			SBUF = testString[3][buf_ptr];
			while(TI == 0);                       // �������жϱ�־λû����1(���ڷ�������)���͵ȴ�
			TI = 0;                               // ��������ɣ�TI�Զ���1�������������
		}
	}
	TI = 0;
	TR1 = 0;
	FLAG = 1;
}

void publisherInit(){
	TMOD = 0x20;                         // ��ʱ��T1�����ڷ�ʽ2�����Զ���װ��8λ��ʱ����
	SCON = 0x40;                         // ���ڹ�����ʽ1�����������
	PCON = 0x00;
	TH1 = 0xf4;                          // ������Ϊ2400
	TL1 = 0xf4;
	TR1 = 1;                             // ������ʱ��T1��T1�������ʵķ�������
	FLAG = 1;							 // �ⲿ�ж����½��ش���
}