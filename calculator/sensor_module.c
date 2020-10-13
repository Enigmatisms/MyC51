#include "sensor_module.h"

/// ds18b20 10*t��ʱ����
void delay10us(uint t){
    uint i;
    for(i = t; i > 0; i --){		// һ��_nop_��ָ�����ʱ 1us������forѭ����10us
        _nop_();
		_nop_();
        _nop_();
    }
}

void sensorInit(){
	sensorReset();
	delayMs(1);
	writeInSensor(0xcc);		// ����ROM	
	writeInSensor(0x4e);		// дEEPROM�Ĵ���
	writeInSensor(0x5f);		// ����¶�95��
	writeInSensor(0x00);		// ����¶�����Ϊ0
	writeInSensor(0x1f);		// ��;�������0.5����λ��������100ms�����ת����
}

/// ds18b20��ʼ��
bit sensorReset(){
	bit ack;
	Bus = 0;
	delay10us(60);	// ��С480�����960
	Bus = 1;
	delay10us(6);	// 15-60us
	while(Bus == 0);
	Bus = 1;		// �ô������ͷ����ߣ�����Ӱ����һ��
	return ack;		// ackΪ0����Ӧ�ɹ� ʵ�ʲ����ж�
}

/// ds18b20дʱ��
void writeInSensor(uchar dat){		// һ��д����Ϊ60-120us��������15--45us�ڶ��źŲ���
	uchar mask;
	for(mask = 0x01; mask != 0; mask <<= 1){
		Bus = 0;
		_nop_();
		if((mask & dat) == 0){
			Bus = 0;
		}
		else{
			Bus = 1;
		}
		delay10us(6);//15-60us����
		Bus = 1;
		_nop_();
		_nop_();
	}
}


/*ds18b20��ʱ��*/
uchar readFromSensor(){
	uchar dat = 0;
	uchar mask, fmask;
	for(mask = 0x01; mask != 0; mask <<= 1){	// һ��������Ҫ����60us��������Ҫ��15us�����
		Bus = 0;
		_nop_();
		Bus = 1;
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		if(Bus == 0){		// ��0
			fmask = ~mask;
			dat = dat & fmask;
		}
		else{
			dat |= mask;
		}
		delay10us(5);
		Bus = 1;
	}
 return dat;
}


/// ת���¶��Ӻ���
void tempConvert(){
	sensorReset();
	delayMs(1);
	writeInSensor(0xcc);		// ����ROMѰַ
	writeInSensor(0x44);		// ����һ���¶�ת��
}


/// ds18b20��ȡ�¶�
uint getTemp(){
	uint temp = 0;
	uchar LSB, MSB;				// �����������ݵĵڰ�λ��߰�λ
	sensorReset();
	delayMs(1);
	writeInSensor(0xcc);		// ����Ѱַ
	writeInSensor(0xbe);		// ���Ͷ�ֵ����
	LSB = readFromSensor();
	MSB = readFromSensor();
	temp = MSB;
	temp <<= 8;
	temp |= LSB;
	return temp;
}


/*ds18b20  �������ս���Ӻ���*/
uint getTempResult(){
	float tp;
	uint temp;
	delayMs(10);		// 10ms�ȹ����ȶ���
	tempConvert();		// ת���¶�
    delayMs(120);		// 120ms ת����
    temp = getTemp();
    tp = temp;
    temp = tp * 0.0625;
    return temp;		// ���ս��Ϊtemp
}