#include "utils.h"

uchar code line_offset[4] = {
	0x00, 0x40, 0x14, 0x54
};

uchar code menuItems[3][20] = {
	"# Calculation",
	"# Sensors",
	"# Alarm Setting"
};

uchar code settingItems[3][20] = {
	"45s shutdown:",				// 45 秒自动关机
	"Press sound:",					// 按键音
	"LED Light:"					// 键盘灯
};

uchar code errors[3][20] = {
	"Syntax Error",
	"Math Error",
	"Stack Error"
};

uchar code temp_info[4][20] = {
	"Current Temperature",
	"* * * * ** * * * * *",
	"Celcius:",
	"Fahrenheit:"
};

uchar code describe[4][12] = {
	"Damn hot",
	"Suitable",
	"Brisk!",
	"Freezing"
};

int strlen(uchar* ptr){
	int i = 0;
	while(i < 20){
		if (ptr[i] < 0x0a){
			return i;
		}
		i++;
	}
	return 20;
}

void delayMs(uint ms){
	int i, j;
	for (i = ms; i > 0; i--){
		for (j = 110; j > 0; j--){
			;
		}
	}
}

/// str 的长度为4，三位的有效数字 + 一位的华氏度摄氏度指示
void tempDisplay(uint temp, bit celc, uchar* str){
	int i;
	uchar now, cnt = 0;
	if (celc == 0){
		temp = temp * 9 / 5 + 32;		// 转为华氏度
	}
	for (i = 100; i > 0; i /= 10){
		now = temp / i;
		temp -= now * i;
		str[cnt] = (now + 48);
		cnt ++;
	}
	if (celc == 1){
		str[cnt] = 'C';
	}
	else {
		str[cnt] = 'F';
	}
}