#include "display_module.h"
#include "keyboard_module.h"

uchar code charTable[24] = {
	'7', '8', '9', '+', 0, 1,
	'4', '5', '6', '-', '(', ')',
	'1', '2', '3', 'x', 2, 3,
	'.', '0', 4, '/', 5, 6, 
};

uint sweepingScan(){
	int i;
	uchar res = 0x00;
	for (i = 0; i < 4; i++){
		switch(i){
			case 0:
				KEY0 = 0;
				KEY1 = 1;
				P3 = 0xff; break;
			case 1:
				KEY0 = 1;
				KEY1 = 0;
				P3 = 0xff; break;
			case 2:
				KEY0 = 1;
				KEY1 = 1;
				P3 = 0xfe;	break;
			default:
				KEY0 = 1;
				KEY1 = 1;
				P3 = 0xfd;
		}
		res = P3 & 0xfc;				// 只取取高6位
		if (res != 0xfc){				// P3 第四位变0后的结果如果为0b1111 0000 说明没有对应键盘响应
			switch (res){
				case 0xf8: return 6 * i;
				case 0xf4: return 6 * i + 1;
				case 0xec: return 6 * i + 2;
				case 0xdc: return 6 * i + 3;
				case 0xbc: return 6 * i + 4;
				case 0x7c: return 6 * i + 5;
			}
		}
	}
	return 24;			// 没有键盘事件
}

void keyboardEvent(uint pos){
	uchar ch;
	ch = charTable[pos];
	if (ch > 10){
		writeCursor(ch);
	}
	else{
		functions[ch]();
	}
}