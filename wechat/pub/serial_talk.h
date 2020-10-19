/// 消息发送
#ifndef __SERIAL_TALK_H__
#define __SERIAL_TALK_H__
#include "utils.h"
#include <intrins.h>

sbit FLAG = P3 ^ 2;

extern uchar sendBuffer[20];
extern uchar buf_ptr;
extern uchar code testString[4][20];
extern uchar test_ptr;

void send();
void bufferInput(uchar dat);	// 缓冲输入
void bufferReset();				// 清空缓冲
void bufferPop();				// 删除一个值
void messageBuzz();				// 消息发送提示音
void publisherInit();

#endif 	//__SERIAL_TALK_H__