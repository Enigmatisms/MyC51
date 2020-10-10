#include "include/easy_stack.h"

int main(){
    uchar buffers[5][40] = {
        "1+1=",                     // 2.0
        "3x4+2=",                // -2.0
        "1+2+3+4+5+6=",            // 4.6667
        "3x4x2-3-4-1=",  // 21
        "1+3+5-3=",  // 1.5
    };
    uchar faults[4][40] = {
        "4/0=",
        "2xx2=",
        "2x=",
        "1+2+3+=",
    };
    printf("These are good expressions:\n");
    for (int i = 0; i < 5; i++){
        calculate(buffers[i]);
    }
    printf("\nThese are bad expressions:\n");
    for (int i = 0; i < 4; i++){
        calculate(faults[i]);
    }
    printf("\nOutput completed.\n");
    return 0;
}