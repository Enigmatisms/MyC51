#include <reg52.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int
	
sbit lock = P2^0;
sbit sign = P2^1;
bit odd_lights = 1, unlock_state = 1;		// 为unlock = 0时锁住

void waitKey(uint ms){
	int i, j;
	for (i = 0; i < ms; i++){
		for (j = 0; j < 110; j++){
			;
		}
	}
}

// 全部选为下降沿触发
// 接受灯亮模式切换指示 INT0
void interrupt0() interrupt 0
{
	odd_lights = ~odd_lights;
	waitKey(15);
}

// 接受锁存器模式切换指示 INT1
void interrupt1() interrupt 2
{
	unlock_state = ~unlock_state;
	lock = unlock_state;
	waitKey(10);
}

/**
函数名()interrupt 0 {} //对应外部bai中du断0；
函数名()interrupt 1 {} //对应定时器zhi/计数器0中断；
函数名()interrupt 2 {} //对应外部中断1；
函数名()interrupt 3 {} //对应定时器/计数器1中断；
函数名()interrupt 4 {} //对应串口中断；
一共5种中断，优先级自上向下。
用错了中断序号，会导致无法正常中断
*/

void main(){
	EA = 1;
	EX0 = 1;
	EX1 = 1;
	IT0 = 1;		// 下降沿触发
	IT1 = 1;		// 下降沿触发
	while(1){
		if (odd_lights == 1){
			P0 = 0x55;
		}
		else{
			P0 = 0xaa;
		}
		sign = unlock_state;		// 锁存器处于锁状态时，灯灭
	}
}