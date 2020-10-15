#ifndef __STACK_MODULE_H__
#define __STACK_MODULE_H__

#include "utils.h"
#define SYNTAX_ERROR 0x00
#define MATH_ERROR 0x01
#define STACK_ERROR 0X02
#define NO_ERROR 0x03
#define LAST_IS_OPRD 0
#define LAST_NOT_OPRD 1

typedef struct Stack{
    uchar static_mem[12];
    uchar top;                            // 栈顶位置
}stack;         

/// @todo C51此处加一个code 存在闪存里
extern uchar code priority[7][7];   

extern stack _oprt;                     // 操作符
extern stack _oprd;                     // 操作数

uchar stackPush(stack* st, uchar _dat);
uchar stackInput(uchar* buffer, uchar* res);
uchar stackGetTop(stack* st);
uchar stackPop(stack* st);
uchar calculate(uchar oprt, uchar a, uchar b);

#endif  //__STACK_MODULE_H__