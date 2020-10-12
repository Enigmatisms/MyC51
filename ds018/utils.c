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
	"45s shutdown:",				// 45 ���Զ��ػ�
	"Press sound:",					// ������
	"LED Light:"					// ���̵�
};

uchar code errors[3][20] = {
	"Syntax Error",
	"Math Error",
	"Stack Error"
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