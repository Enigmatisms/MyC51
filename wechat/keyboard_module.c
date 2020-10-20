#include "keyboard_module.h"

bit cap = 0;

uchar code charTable[40] = {
	'0', '1', '2', '3', '4', '5', '6', '7',
	'8', '9', 'a', 'b', 'c', 'd', 'e', 'f',
	'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
	'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
	'w', 'x', 'y', 'z',   0, ' ',   1,   2,
};

uchar code digit2Sign[6] = {
	',', '.', '?', '!', '&', '\''
};

uint sweepingScan(){
	uchar i, res, out = 0xfe;
	for (i = 0; i < 5; i++){
		P0 = out;					// 扫描
		out = _crol_(out, 1);		// 低电平左移一位
		res = P2;
		if (res != 0xfc){
			switch (res){
				case 0xfe: return 8 * i;
				case 0xfd: return 8 * i + 1;
				case 0xfb: return 8 * i + 2;
				case 0xf7: return 8 * i + 3;
				case 0xef: return 8 * i + 4;
				case 0xdf: return 8 * i + 5;
				case 0xbf: return 8 * i + 6;
				case 0x7f: return 8 * i + 7;
			}
		}
		delayMs(1);
	}
	P0 = 0x1f;
	return 40;			// 没有键盘事件
}

void keyboardEvent(uint pos){
	uchar ch;
	ch = charTable[pos];
	if (ch >= 32){
		if (cap == 1){
			if (ch < '6'){
				ch = digit2Sign[ch - '0'];
			}
			else if (ch >= 'a'){
				ch -= 32;				// 得到大写字母
			}
		}
		if (_mode == CHATTING){
			writeCursor(ch);
		}
		else if (_mode == LOCKED){
			printPassword(ch);
		}
	}
	else{
		if (_mode <= LOCKED){
			switch(ch){
				case 0: cap =~ cap; break;
				case 1: 
					doPop();
				break;
				case 2: 
					if (_mode == CHATTING){
						drawIncomingMessage(buffer, 1);		// 本机键盘响应输入绘制
					}
					else {
						isPasswordRight();
					}
				break;
			}
		}
	}
}