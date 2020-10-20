#include "utils.h"

uchar _mode = 0;					// 主要模式
uchar counter = 0;

uchar code line_offset[4] = {
	0x00, 0x40, 0x14, 0x54
};

uchar code wechat_info[4][20] = {
	"**WeChat C51 V 1.0**",
	"* Incorrect input! *",
	" 3 faults. Locked. ",
	"* Device unlocked! *"
};

uchar code lock_info[3][20] = {
	"********************",
	" Password Required: ",
	"*PIN:              *",
};

uchar code password[9] = "123456789";

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

uchar code message_tone[9] = {
	5, 0, 2, 4, 0, 2, 6, 0, 2,
};

uchar code unlock_tone[9] = {
	2, 0, 2, 7, 0, 2, 2, 0, 2
};

uchar code error_tone[9] = {
	2, 0, 2, 3, 0, 2, 4, 0, 2
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