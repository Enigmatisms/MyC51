#ifndef __STACK_MODULE_H__
#define __STACK_MODULE_H__

#include <stdio.h>

#define MATH_RANGE 1e41
#define MATH_ERROR 1e60
#define LAST_IS_OPRD 0x10
#define LAST_NOT_OPRD 0x11
typedef unsigned char uchar;
typedef unsigned int uint;
typedef struct Stack{
    float static_mem[16];
    uchar top;                            // 栈顶位置
}stack;         

/// @todo C51此处加一个code 存在闪存里
extern uchar priority[7][7];   
extern uchar dot_counter;               // 小数点计数器         

extern stack _oprt;                     // 操作符
extern stack _oprd;                     // 操作数

uchar oprtMap(uchar ch);
uchar stackPush(stack* st, float data);
void stackInit(stack* st);
void stackInput(uchar* buffer);
float stackGetTop(stack* st);
float stackPop(stack* st);
float calculate(uchar oprt, float a, float b);

#endif  //__STACK_MODULE_H__