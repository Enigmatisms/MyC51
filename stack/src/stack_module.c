#include "../include/stack_module.h"

stack _oprt;
stack _oprd;

uchar dot_counter;

//  +  -  x  /  (  )  =
uchar priority[7][7] = {
    1, 0, 0, 0, 1, 0, 1,    // +
    1, 0, 0, 0, 1, 0, 1,    // -
    1, 1, 1, 0, 1, 0, 1,    // x
    1, 1, 1, 0, 1, 0, 1,    // /
    1, 1, 1, 1, 1, 3, 1,    // (
    0, 0, 0, 0, 2, 3, 3,    // )
    0, 0, 0, 0, 3, 0, 2     // =
};

void stackInit(stack* st){
    int i;
    for (i = 0; i < 16; i++){
        st->static_mem[i] = -1;
    }
    st->top = 0;
}

uchar stackPush(stack* st, float data){
    if (st->top < 16){
        st->static_mem[st->top] = data;
        st->top++;
        return 0x00;
    }
    return 0xff;
}

float stackPop(stack* st){
    float temp;
    if (st->top > 0){
        temp = st->static_mem[st->top - 1];
        st->static_mem[st->top - 1] = -1;
        st->top --;
        return temp;
    }
}

float stackGetTop(stack* st){
    return st->static_mem[st->top - 1];
}

// 最后的输入方式：输入进入一个buffer(buffer保存的是最终的结果) 对buffer进行处理
void stackInput(uchar* buffer){
    float oprd1, oprd2, temp = 0, mtpl = 0.1;                 // 临时结果与乘数
    uint i;
    uchar now, mapped, top, flag;
    dot_counter = 0;
    stackPush(&_oprt, 6);
    for (i = 0; i < 40; i++){
        now = buffer[i];
        if (now >= '0' && now <= '9'){      
            // printf("Operand component found!\n");
            if (dot_counter == 1){
                temp += (float)(now - 48) * mtpl;
                mtpl /= 10;
            }
            else{
                temp *= 10;
                temp += (float)(now - 48);
            }
            flag = LAST_IS_OPRD;                    // flag进行了复用，上一个输入是数字
        }
        else{
            if (now != '.'){
                if (flag == LAST_IS_OPRD){          // 上次输入为数字，本次为操作数，则上次数字入栈
                    if (stackPush(&_oprd, temp) != 0x00){
                        printf("Stack Error.\n");
                        return;
                    }
                    temp = 0.0;
                    mtpl = 0.1;
                }
                dot_counter = 0;                    // 输入操作符可以清空小数点计数器
                mapped = oprtMap(now);
                top = (uchar)stackGetTop(&_oprt);
                flag = priority[mapped][top];       // 优先级判定
                while (flag == 0){                  // 出栈顶
                    top = (uchar)stackPop(&_oprt);
                    if (_oprd.top < 2){
                        printf("Syntax Error: Not enough operands.\n");
                        return;
                    }
                    oprd2 = stackPop(&_oprd);
                    oprd1 = stackPop(&_oprd);
                    oprd2 = calculate(top, oprd1, oprd2);
                    if (oprd2 < MATH_RANGE){
                        if (stackPush(&_oprd, oprd2) != 0x00){
                            printf("Stack Error.\n");
                            return;
                        }
                    }
                    else{
                        printf("Math Error.\n");
                        return;
                    }
                    top = (uchar)stackGetTop(&_oprt);
                    flag = priority[mapped][top];
                }
                if (flag == 1){                     // 为1 说明当前运算符优先级高 可以直接入栈
                    if (stackPush(&_oprt, mapped) != 0x00){
                        printf("Stack Error.\n");
                        return;
                    }
                }
                else if (flag == 2){                // 当前与栈顶相等，直接删除
                    stackPop(&_oprt);
                    if (_oprt.top == 0){
                        printf("Final result: %f\n", stackGetTop(&_oprd));
                        return;
                    }
                }
                else{                               // 语法错误
                    /// Syntax Error;  
                    printf("Syntax Error.\n"); 
                    return;
                }
                flag = LAST_NOT_OPRD;
            }
            else {                                  // 小数点记号
                dot_counter ++;
                if (dot_counter > 1){
                    //Syntax Error
                    printf("Syntax Error.\n");
                    return;
                }
                flag = LAST_IS_OPRD;
            }
        }
        if (now == '='){
            printf("Syntax Error.\n");
            return;
        }
    }
}

uchar oprtMap(uchar ch){
    switch (ch)
    {
    case '+': return 0;
    case '-': return 1;
    case 'x': return 2;
    case '/': return 3;
    case '(': return 4;
    case ')': return 5;
    default: return 6;
    }
}

float calculate(uchar oprt, float a, float b){
    switch (oprt){
    case 0: return a + b;
    case 1: return a - b;
    case 2: return a * b;
    default: 
        if (b == 0.0){
            return MATH_ERROR;
        }
        return a / b;
    }
}

