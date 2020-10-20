#include "serial_listen.h"
#include "display_module.h"
#include "keyboard_module.h"

void main(){
	uint pos, old_pos = 40;
	Init();
	subscriberInit();
	_mode = LOCKED;
	drawSuspend();
	setCursor(2, 5);
	while (1){
		if (ready == 1){			// 接收串口消息时不响应键盘
			receive();
		}
		else{						// 带延迟10ms的键盘
			if (T0 == 0){
				pos = sweepingScan();
				if (pos != 40 && pos == old_pos){
					continue;
				}
				if (pos < 40){
					keyboardEvent(pos);
				}
				delayMs(10);
				old_pos = pos;
			}
		}
		if (draw_allow == 1){		// 输出则进行输出
			drawIncomingMessage(receiveBuffer, 0);	// 来自对方的输入
			playSound(message_tone);
		}
	}
}