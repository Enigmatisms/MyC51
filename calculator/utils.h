/**
 * ================= ���ú����Լ����� ====================
 * @date 2020.10.4
 * @author ��ǧԽ
*/
#ifndef __UTILS_H__
#define __UTILS_H__

#include <reg52.h>
#include <intrins.h>
#define uint unsigned int
#define uchar unsigned char
	
// ��ƫ��
extern uchar code line_offset[4];

extern uchar code menuItems[3][20];

extern uchar code settingItems[3][20];

int strlen(uchar ptr[20]);

void delayMs(uint ms);

#endif 	//__UTILS_H__