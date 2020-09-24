#include <reg52.h>
#include <intrins.h>
#define uint unsigned int
#define uchar unsigned char

/**
需要实现的功能
	使用定时器进行定时
	采用中断的方式进行计数器自增，并且控制锁存器
	得到一个以秒为单位的计数器，最大记录99s
**/

sbit lock = P2 ^ 0;		// 锁存控制位
sbit lcd1 = P2 ^ 1;		// 十位数显示对应的lcd 位选，阴极，lcd高电平则对应lcd不显示
sbit lcd2 = P2 ^ 2;		// 个位显示
int counter = 0;
int ms_counter = 0;		// 毫秒计数器
uint tenth = 0, unit = 0, delay_cycle = 24;		// 十位个位数字
const uchar th0 = (65536 - 50000) / 256, lowt0 = (65536 - 50000) % 256;	// 起始位设置

uchar lcd_table[10] = {
	0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f, 0x6f
};

/// @brief 计时器中断函数 当达到一定时间之后，自动执行：
/// counter 自增，并且进行取模运算
/// 获取十位个位数字，使用位选器进行输出
/// 暂时用不上锁存
void timerT0() interrupt 1
{
	TH0 = th0;
	TL0 = lowt0;
	ms_counter++;
	if (ms_counter > 10){
		counter++;
		unit = counter % 10;
		if (unit == 0){			// 每次个位为0的时候，十位进位，并且区模
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
	TMOD = 0x01;			// 定时器0 M1M0 为 0x01 表示16 位计数器
	TH0 = th0;				
	TL0 = lowt0;
	EA = 1;					// 总中断打开
	ET0 = 1;				// T0计时器打开
	TR0 = 1;				// 启动T0计时器、
	lock = 1;
	while(1){				// 此处可以使用锁存器取代
		lcd1 = 1;
		lcd2 = 0;
		P0 = lcd_table[tenth] ^ 0xff;
		delay(delay_cycle);
		lcd1 = 0;
		lcd2 = 1;
		P0 = lcd_table[unit] ^ 0xff;
		delay(delay_cycle);
		if (counter > 99){
			counter = 0;	// 清零操作
		}
	}
}