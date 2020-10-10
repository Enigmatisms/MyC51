#include "easy_stack.h"

uchar calculate(uchar* buffer, uchar* dst){
    uchar i;
    uchar now, next, temp = 0;
	*dst = 0;
    if (buffer[0] < '0' || buffer[0] > '9'){
		*dst = buffer[0];
        return SYNTAX_ERROR;
    }
    for (i = 0; i < 24; i++){
        now = buffer[i];
        if (now >= '0' && now <= '9'){
            temp *= 10;
            temp += (now - '0');
        }
        else if (now != '=' && now != 0){
            i++;
            next = buffer[i];
            if (next < '0' || next > '9'){
                return SYNTAX_ERROR;
            }
            *dst += temp;
            temp = 0;
            switch (now)
            {
            case '+':
                *dst += (next - '0');
                break;
            case '-':
                *dst -= (next - '0');
                break;
            case 'x':
                *dst *= (next - '0');
                break;
            case '/':
                if (next == '0'){
                    return MATH_ERROR;
                }
                *dst /= (next - '0');
                break;
            }
        }
        else{
            break;
        }
    }
    return 0x03;
}

