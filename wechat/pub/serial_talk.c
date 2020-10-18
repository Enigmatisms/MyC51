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
	for (buf_ptr = 0; buf_ptr < 20; buf_ptr ++){
		delayMs(80);
		if (testString[3][buf_ptr] <= 10){
			break;
		}
		else{
			SBUF = testString[3][buf_ptr];
			while(TI == 0);                       // 若发送中断标志位没有置1(正在发送数据)，就等待
			TI = 0;                               // 若发送完成，TI自动置1，这里把它清零
		}
	}
	TI = 0;
	TR1 = 0;
	FLAG = 1;
}

void publisherInit(){
	TMOD = 0x20;                         // 定时器T1工作于方式2（可自动重装的8位定时器）
	SCON = 0x40;                         // 串口工作方式1，不允许接收
	PCON = 0x00;
	TH1 = 0xf4;                          // 波特率为2400
	TL1 = 0xf4;
	TR1 = 1;                             // 启动定时器T1（T1作波特率的发生器）
	FLAG = 1;							 // 外部中断是下降沿触发
}