#include "serial_talk.h"

uchar sendBuffer[20];
uchar buf_ptr;
uchar code testString[4][20] = {
	"Hello world!#",
	"C51 Regards!#",
	"Let's do this!#",
	"123456789ABXYZ#"
};

void send(){            // 数据发送程序
	TH1 = 0xf4;                          // 波特率为2400
	TL1 = 0xf4;
	TR1 = 1;                             // 启动定时器T1（T1作波特率的发生器）
	FLAG = 0;
	if (buf_ptr >= 20){
		sendBuffer[19] = '#';			// 终止符
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
			while(TI == 0);                       // 若发送中断标志位没有置1(正在发送数据)，就等待
			TI = 0;                               // 若发送完成，TI自动置1，这里把它清零
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
	if (buf_ptr > 0){					// buf 始终指向下一个要填入的位置，和栈类似
		buf_ptr --;
		sendBuffer[buf_ptr] = '\0';
	}
}

void publisherInit(){
	TMOD = 0x20;                         // 定时器T1工作于方式2（可自动重装的8位定时器）
	SCON = 0x40;                         // 串口工作方式1，不允许接收
	PCON = 0x00;
	TH1 = 0xf4;                          // 波特率为2400
	TL1 = 0xf4;
	TR1 = 1;                             // 启动定时器T1（T1作波特率的发生器）
	FLAG = 1;							 // 外部中断是下降沿触发
	T0 = 0;
}