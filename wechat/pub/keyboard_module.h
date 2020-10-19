/**
 * ================= 键盘模块 ====================
 * @brief LCD 4 * 6 矩阵键盘模块
 * @date 2020.10.5
 * @author 何千越
*/

#ifndef __KEYBOARD_MODULE_H__
#define __KEYBOARD_MODULE_H__
#include <reg52.h>
#include "serial_talk.h"

extern bit cap;
extern uchar code charTable[40];
extern uchar code digit2Sign[6];

uint sweepingScan();
void keyboardEvent(uint pos);

#endif 	//__KEYBOARD_MODULE_H__