/// ÏûÏ¢·¢ËÍ

#include "utils.h"

sbit FLAG = P3 ^ 2;

extern uchar sendBuffer[20];
extern uchar buf_ptr;
extern uchar code testString[4][20];
extern uchar test_ptr;

void send();
void publisherInit();