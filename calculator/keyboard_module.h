/**
 * ================= ����ģ�� ====================
 * @brief LCD 4 * 6 �������ģ��
 * @date 2020.10.5
 * @author ��ǧԽ
*/

#ifndef __KEYBOARD_MODULE_H__
#define __KEYBOARD_MODULE_H__
#include <reg52.h>
#include <intrins.h>
#include "utils.h"

sbit KEY0 = P2^6;
sbit KEY1 = P2^7;

extern uchar code charTable[24];

uint sweepingScan();
void keyboardEvent(uint pos);

#endif 	//__KEYBOARD_MODULE_H__