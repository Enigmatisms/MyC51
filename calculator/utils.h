/**
 * ================= 公用函数以及类型 ====================
 * @date 2020.10.4
 * @author 何千越
*/
#ifndef __UTILS_H__
#define __UTILS_H__

#include <reg52.h>
#define uint unsigned int
#define uchar unsigned char
	
// 行偏移
extern uchar code line_offset[4];

extern uchar code menuItems[3][20];

extern uchar code settingItems[3][20];

extern uchar code errors[3][20];

extern uchar code temp_info[4][20];

extern uchar code describe[4][12];

int strlen(uchar* ptr);

void delayMs(uint ms);

void tempDisplay(uint temp, bit celc, uchar* str);

#endif 	//__UTILS_H__