/**
 * ================= 栈计算模块 ====================
 * @brief 计算器计算功能核心模块
 * @date 2020.10.9
 * @author 何千越
*/
#ifndef __STACK_MODULE_H__
#define __STACK_MODULE_H__

#include "utils.h"
#define MATH_ERROR 0x01
#define SYNTAX_ERROR 0x00

uchar calculate(uchar* buffer, uchar* dst);

#endif  //__STACK_MODULE_H__