#include "include/stack_module.h"

int main(){
    uchar buffers[9][40] = {
        "1+1=",                     // 2.0
        "3+4/5-6+0.2=",                // -2.0
        "1x2/3+4x4/4=",            // 4.6667
        "(1+3-4)/2+(1+2)x(3+4)=",  // 21
        "(12/4)/(12/3)x(3-9/9)=",  // 1.5
        "6.622+8.12230+123.333/12.22=",
        "(1/2+4/(1+3)x(1+2))/2+(2)=",
        "(((1+3/2)/2)x2)/2x2+(((2))x((2)))=",
        "1.21325+1.6+1.7/2.0"
    };
    float answers[9] = {2, -2.0, 4.6667, 21.0, 1.5, 0, 0, 0, 0};
    uchar faults[8][40] = {
        "4.0/0.0=",
        "((2+3/5)=",
        "3x5+2x4+x5=",
        "1xx2=",
        "1.3+1.3.4=",
        "(9+2)(9-8)=",
        ")3+4=",
        "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1="
    };
    printf("These are good expressions:\n");
    for (int i = 0; i < 9; i++){
        stackInput(buffers[i]);
        printf("While the true answer for question %d is %f\n\n", i + 1, answers[i]);
    }
    printf("\nThese are bad expressions:\n");
    for (int i = 0; i < 8; i++){
        stackInput(faults[i]);
    }
    printf("\nOutput completed.\n");
    return 0;
}