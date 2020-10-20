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
		if (ready == 1){			// ���մ�����Ϣʱ����Ӧ����
			receive();
		}
		else{						// ���ӳ�10ms�ļ���
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
		if (draw_allow == 1){		// �����������
			drawIncomingMessage(receiveBuffer, 0);	// ���ԶԷ�������
			playSound(message_tone);
		}
	}
}