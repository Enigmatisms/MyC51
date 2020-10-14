#include "utils.h"

uchar _mode = 0;					// 主要模式
bit suspend_lock = 0;				// 挂起绘制锁
uchar sets[3] = {0, 0, 0};			// 设置（45秒自动挂起，按键音，键盘灯）

uchar code line_offset[4] = {
	0x00, 0x40, 0x14, 0x54
};

uchar code menuItems[3][20] = {
	"# Calculation",
	"# Sensors",
	"# Alarm Setting"
};

uchar code settingItems[3][20] = {
	"45s suspend:",					// 45 秒自动挂起
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

uchar code alarm_info[6][20] = {
	"=====Time is Up=====",
	"Press AC to turn off",
	"Song:[So Far Away]",
	"====================",
	"----- NO ALARM -----",
	"----- ALARM ON -----"
};

uchar code alarm_ui[4][20] = {
	"***Set your alarm***",
	"Upper bound: 59m 59s",
	"Set:",
	"********************"
};

uchar code suspend_ui[3][20] = {
	"********************",
	"*    SUSPENDING    *",
	"*   POWER SAVING   *"
};

uchar code FREQH[28] = {
    248, 247, 246, 245, 245, 243, 242,
    252, 252, 251, 251, 250, 250, 249, 249,
    254, 253, 253, 253, 253, 252,   
    255, 254, 254, 254, 254, 254, 254,
};

uchar code FREQL[28] = {
    182, 209, 208, 182, 23, 193, 66,
    143, 91, 233, 104, 216, 140, 225, 33,
    45, 244, 180, 107, 68, 238, 
    22, 250, 218, 182, 162, 119, 71,
};// 音阶频率表 低八位

//uchar code song[75] = {
//         5,1,1, 5,1,1, 6,1,2, 5,1,2, 1,1,2, 5,1,4,
//         5,1,1, 5,1,1, 6,1,2, 5,1,2, 2,1,2, 1,1,4,
//         5,1,1, 5,1,1, 5,0,2, 3,1,2, 1,1,2, 5,1,2, 5,1,2,
//         4,1,1, 4,1,1, 3,1,2, 1,1,2, 2,1,2, 1,1,4
//};

uchar code song[84] = {
	2, 1, 2,	3, 1, 2,	6, 0, 2, 	1, 1, 4,	6, 0, 2, 	5, 1, 2, 	5, 1, 1, 	2, 1, 1, 	
	1, 1, 2, 	5, 1, 2,	5, 1, 1, 	2, 1, 4, 	1, 1, 2, 	6, 0, 1, 	1, 1, 1, 	6, 0, 1,
	2, 1, 2,	3, 1, 2,	6, 0, 2, 	1, 1, 4,	6, 0, 2, 	5, 1, 2, 	5, 1, 1, 	2, 1, 1,
	7, 0, 2, 	6, 0, 1, 	2, 1, 1, 	1, 1, 4
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