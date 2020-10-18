/**
 *	========== 串口通信，只管接收数据的模块 ============
 *
 * 
*/
#ifndef __SERIAL_LISTEN_H__
#define __SERIAL_LISTEN_H__
#include "utils.h"

sbit ALE = P3 ^ 4;
extern uchar receiveBuffer[20];
extern uchar buffer_ptr;
extern bit ready;
extern bit draw_allow;

void subscriberInit();
void receive();
void bufferReset();

#endif 	//__SERIAL_LISTEN_H__