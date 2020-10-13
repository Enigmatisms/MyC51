/**
 * ================= 温度传感器模块 ====================
 * @brief Temperature Sensor DS018B20 函数定义以及相关宏
 * @date 2020.10.11
 * @author 何千越
*/
#ifndef __SENSOR_MODULE_H__
#define __SENSOR_MODULE_H__
#include "utils.h"
#include<intrins.h>

sbit Bus = P3 ^ 7; // 数据单总线

uint getTempResult();				// 返回最终结果
uint getTemp();						// 获取温度子函数
bit sensorReset();					// 初始化子函数
uchar readFromSensor();				// 用于从总线读值
void sensorInit();					// 初始化，设置精度以及范围
void tempConvert();					// 开始转换温度
void writeInSensor(uchar dat);		// 用于向总线写命令
void delay10us(uint t);				// 延时10*t微秒

#endif 	//__SENSOR_MODULE_H__