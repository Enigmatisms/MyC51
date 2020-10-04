#include "display_module.h"

void Init(){
	write(INITIAL, 0);
	write(CLA, 0);
	write(NO_CURSOR, 0);
	write(CURSOR_FORWARD, 0);
}

uchar busyCheck()   //忙检查
{
  uchar	status;
  RS = 0;	 
  RW = 1;	 
  EN = 1;	 
  delayMs(DELAY);
  status = P0; 	//读出P0最高位状态值
  EN = 0;
  return status;
}

/// 写入数据或者指令
void write(uchar _data, bit data_flag){
	while((busyCheck()&0x80) == 0x80);
	RW = 0;
	RS = data_flag;		// data_flag为1时为写入数据
	EN = 0;
	delayMs(DELAY);
	EN = 1;
	P0 = _data;
	delayMs(DELAY);
	EN = 0;				// 约2 * DELAY ms的脉冲
}



void writeChar(uchar _dat, uint px, uint py){
	write(0x80 | (0x01 * px + line_offset[py]), 0);
	write(_dat, 1);
}

/// @todo 增加居中，左侧显示，右侧显示等模式
void writeLine(uchar ptr[20], uint line, bit clear, uchar align){
	uint index;
	uchar start_pos = 0;
	switch(align){
		case CENTRAL:
			start_pos = (uchar)((20 - strlen(ptr)) / 2); break;
		case LEFT:
			break;
		case RIGHT:
			start_pos = (uchar)(20 - strlen(ptr)); break;
		default:
			break;
	}
	if (clear == 0){
		write(DISPLAY_START | line_offset[line] | start_pos, 0);
		for (index = 0; index < 20 && ptr[index] >= 10; index++){
			write(ptr[index], 1);
		}
	}
	else{
		write(DISPLAY_START | line_offset[line], 0);
		for (index = 0; index < start_pos; index ++){
			write(0x20, 1);
		}
		for (index = 0; index < 20 && ptr[index] >= 0x0a; index ++){
			write(ptr[index], 1);
		}
		for (; index < 20 - start_pos; index ++){
			write(0x20, 1);
		}
	}
}