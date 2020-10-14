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
				KEY2 = 1;
				KEY3 = 1; break;
			case 1:
				KEY0 = 1;
				KEY1 = 0;
				KEY2 = 1;
				KEY3 = 1; break;
			case 2:
				KEY0 = 1;
				KEY1 = 1;
				KEY2 = 0;
			    KEY3 = 1; break;
			default:
				KEY0 = 1;
				KEY1 = 1;
				KEY2 = 1;
			    KEY3 = 0;
		}
		res = P1 & 0xfc;				// 只取取高6位
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
		if (_mode == IN_ALARM){
			if (ch == '+'){
				alarmSet(1);
				drawAlarmUI(1);		// 更新一次LCD闹钟设置显示
			}
			else if (ch == '-'){
				alarmSet(0);
				drawAlarmUI(1);		// 更新一次LCD闹钟设置显示
			}
			return;
		}
		writeCursor(ch);
	}
	else{
		if (_mode == SUSPEND){
			if (ch == CLA)
				allClear();
			return;
		}
		switch(ch){
			case 0: doPop(); break;
			case 1: allClear(); break;
			case 2: settings(); break;
			case 3: mainMenu(); break;
			case 4: yieldResult(); break;
			case 5: moveLeft(); break;
			case 6: moveRight(); break;
		}
	}
}