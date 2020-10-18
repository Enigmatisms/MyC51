#include "serial_talk.h"

void main(){
	publisherInit();
	send();
	while(1);
}