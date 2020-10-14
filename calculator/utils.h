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
	

// =============== 其他宏 ================== //
#define CENTRAL 0
#define LEFT	1
#define RIGHT	2
#define CALC	0			// 系统模式
#define SETS	1			// 1为 指示灯 2为按键音 3为科学计数法显示
#define MENU	4			// 4为计算模式	5为温度显示  6为闹钟设置
#define TEMP_SENSOR	5		// 温度传感器待选
#define ALARM_SET	6		// 闹钟待选
#define IN_SENSOR	7		// 温度传感器界面内部
#define IN_ALARM	8		// 闹钟设置界面内部
#define ALARMING	9		// 闹钟正在响
#define SUSPEND		0xff	// 挂起模式

#define ALARM_MAX 3599		// 最大可以设置59分59秒

extern uchar _mode;			// 当前模式 @todo 普通计算模式，温度/电量显示模式，闹钟设置（计时器中断打开/关闭？）
extern bit suspend_lock;
extern uchar sets[3];		// 设置
	
// 行偏移
extern uchar code line_offset[4];

extern uchar code menuItems[3][20];

extern uchar code settingItems[3][20];

extern uchar code errors[3][20];

extern uchar code temp_info[4][20];

extern uchar code describe[4][12];

extern uchar code alarm_info[6][20];

extern uchar code alarm_ui[4][20];

extern uchar code suspend_ui[3][20];

extern uchar code FREQH[28];

extern uchar code FREQL[28];

extern uchar code song[84];

int strlen(uchar* ptr);

void delayMs(uint ms);

void tempDisplay(uint temp, bit celc, uchar* str);

#endif 	//__UTILS_H__