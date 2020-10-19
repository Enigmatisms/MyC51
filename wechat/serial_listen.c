#include "serial_listen.h"

uchar receiveBuffer[20];
uchar buffer_ptr = 0;
bit ready = 0;
bit draw_allow = 0;

void subscriberInit(){
	TMOD = 0x20;                     //设置定时器T1工作于方式2
	SCON = 0x50;                     //串口工作方式1，允许接收数据
	PCON = 0x00;                     //波特率不倍增
	TH1 = 0xf4;                      //波特率为2400b/s
	TL1 = 0xf4;
	TR1 = 1;                         //启动定时器T1
	REN = 1;                         //允许接收数据
	EX0 = 1;						 // 打开外部中断0，作为接收结束标志
	EA = 1;
	IT0 = 1;						 // 下降沿触发
	T0 = 0;
}

void receive() {        	
	uchar i, j, temp;
	for (i = 0; i < 250; i++){		// TIMEOUT时间 250ms
		for (j = 0; j < 110; j++){
			if (RI != 0){
				break;
			}
		}
		if (j < 110){
			break;
		}
	}
	RI = 0;                           				// 接收完毕时清零
	if (buffer_ptr < 20){
		temp = SBUF;         // 将接收缓冲器中的数据存入dat
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

// 接到数据提醒，开始收数据
void receiveStart() interrupt 0
{
	ready = 1;
}