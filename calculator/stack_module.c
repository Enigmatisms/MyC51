#include "stack_module.h"

stack _oprt;
stack _oprd;

//  +  -  x  /  (  )  =
uchar code  priority[7][7] = {
    1, 0, 0, 0, 1, 0, 1,    // +
    1, 0, 0, 0, 1, 0, 1,    // -
    1, 1, 1, 0, 1, 0, 1,    // x
    1, 1, 1, 0, 1, 0, 1,    // /
    1, 1, 1, 1, 1, 3, 1,    // (
    0, 0, 0, 0, 2, 3, 3,    // )
    0, 0, 0, 0, 3, 0, 2     // =
};

uchar stackPush(stack* st, uchar _dat){
    if (st->top < 12){
        st->static_mem[st->top] = _dat;
        st->top++;
        return 0x00;
    }
    return 0xff;
}

uchar stackPop(stack* st){
    uchar temp;
    if (st->top > 0){
        temp = st->static_mem[st->top - 1];
        st->static_mem[st->top - 1] = -1;
        st->top --;
        return temp;
    }
	return 0xff;
}

uchar stackGetTop(stack* st){
    return st->static_mem[st->top - 1];
}

uchar stackInput(uchar* buffer, uchar* res){
    uchar oprd1, oprd2, temp = 0;                 // 临时结果与乘数
    uchar i;
    uchar now, top, flag;
	_oprd.top = 0;
    _oprt.top = 0;
    stackPush(&_oprt, 6);
    for (i = 0; i < 40; i++){
        now = buffer[i];
        if (now >= '0' && now <= '9'){      
            temp *= 10;
            temp += (uchar)(now - 48);
            flag = LAST_IS_OPRD;                    // flag进行了复用，上一个输入是数字
        }
        else{
            if (flag == LAST_IS_OPRD){          // 上次输入为数字，本次为操作数，则上次数字入栈
                if (stackPush(&_oprd, temp) != 0x00){
                    return STACK_ERROR;
                }
                temp = 0;
            }
            switch (now){
                case '+': now = 0; break;
                case '-': now = 1; break;
                case 'x': now = 2; break;
                case '/': now = 3; break;
                case '(': now = 4; break;
                case ')': now = 5; break;
                default: now = 6;
            }
            top = (uchar)stackGetTop(&_oprt);
            flag = priority[now][top];       // 优先级判定
            while (flag == 0){                  // 出栈顶
                top = (uchar)stackPop(&_oprt);
                if (_oprd.top < 2){
                    return SYNTAX_ERROR;
                }
                oprd2 = stackPop(&_oprd);
                oprd1 = stackPop(&_oprd);
                oprd2 = calculate(top, oprd1, oprd2);
                if (oprd2 != MATH_ERROR){
                    if (stackPush(&_oprd, oprd2) != 0x00){
                        return STACK_ERROR;
                    }
                }
                else{
                    return MATH_ERROR;
                }
                top = (uchar)stackGetTop(&_oprt);
                flag = priority[now][top];
            }
            if (flag == 1){                     // 为1 说明当前运算符优先级高 可以直接入栈
                if (stackPush(&_oprt, now) != 0x00){
                    return STACK_ERROR;
                }
            }
            else if (flag == 2){                // 当前与栈顶相等，直接删除
                stackPop(&_oprt);
                if (_oprt.top == 0){
                    *res = stackGetTop(&_oprd);
                    return NO_ERROR;
                }
            }
            else{                               // 语法错误
                break;
            }
            flag = LAST_NOT_OPRD;
        }
    }
    return SYNTAX_ERROR;
}

uchar calculate(uchar oprt, uchar a, uchar b){
    switch (oprt){
    case 0: return a + b;
    case 1: return a - b;
    case 2: return a * b;
    default: 
        if (b == 0){
            return MATH_ERROR;
        }
        return a / b;
    }
}

