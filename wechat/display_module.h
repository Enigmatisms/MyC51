/**
 * ================= LCD显示模块 ====================
 * @brief LCD 20x4 函数定义以及相关宏
 * @date 2020.10.4
 * @author 何千越
*/

#ifndef __DISPLAY_MODULE_H__
#define __DISPLAY_MODULE_H__

#include <reg52.h>
#include "utils.h"
#include "serial_listen.h"

#define DELAY 1

// ================ LCD宏 ===================//
#define INITIAL 			0x38
#define CLA 				0x01
#define DISPLAY_START 		0x80

#define CURSOR_BLINK 		0x0f
#define CURSOR_NON_BLINK 	0x0e
#define SHOW_CURSOR 		0x0d
#define NO_CURSOR 			0x0c
#define CURSOR_FORWARD 		0x06
#define CURSOR_BACKWARD 	0x04
#define DISPLAY_LEFT 		0x07
#define DISPLAY_RIGHT 		0x05
#define CURSOR_LEFT 		0x10
#define CURSOR_RIGHT 		0x14
#define ALL_LEFT 			0x18
#define ALL_RIGHT 			0x1c


sbit RS = P3 ^ 5;
sbit RW = P3 ^ 6;
sbit EN = P3 ^ 7;

extern uchar now_row;		// 当前光标行
extern uchar now_col;		// 当前光标列
extern uchar head_row;		// 当前屏幕上字符最大达到的行
extern uchar head_col;		// 当前屏幕上字符最大达到的列

extern uchar buffer[20];	// 输入缓冲区

/// 设置中包括：是否打开按键与闹钟指示灯？是否静音？是否开启科学计数法显示？（最后一个最难）

void Init();				// 初始化

/// ================== 七个按键函数 =====================
void doPop();				// 行尾删除
void allClear();			// 清空(本行)
void confirm();				// 消息发送(或者密码输入)
void moveLeft();			// 光标左移
void moveRight();			// 光标右移

void writeCursor(uchar _data);	// 光标边界检测 + 输入
void write(uchar _dat, bit data_flag);		// 简单写入
void writeLine(uchar* ptr, uint line, bit clear, uchar align);		// 写入列
void setCursor(uchar row, uchar col);
uchar checkBusy();

void drawSuspend();
#endif 	//__DISPLAY_MODULE_H__