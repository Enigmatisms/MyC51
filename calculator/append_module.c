#include "append_module.h"

/// ds18b20 10*t延时函数
void delay10us(uint t)
{
    uint i;
    for(i = t; i > 0; i --)		// 一个_nop_空指令函数延时 1us，加上for循环有10us
    {
        _nop_();
		_nop_();
        _nop_();
    }
}

/// ds18b20初始化
bit sensorInit()
{
	bit ack;
	Bus = 0;
	delay10us(60);	//最小480，最大960
	Bus = 1;
	delay10us(6);	//15-60us
	while(Bus == 0);
	Bus = 1;		//让传感器释放总线，避免影响下一步
	return ack;		//ack为0则响应成功
}

/// ds18b20写时序
void writeInSensor(uchar dat)		//一个写周期为60-120us，主机在15--45us内对信号采样
{
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
		delay10us(6);//15-60us采样
		Bus = 1;
		_nop_();
		_nop_();
	}
}


/*ds18b20读时序*/
uchar readFromSensor(){
	uchar dat = 0;
	uchar mask, fmask;
	for(mask = 0x01; mask != 0; mask <<= 1)//一个周期需要至少60us，但采样要在15us内完成
	{
		Bus = 0;
		_nop_();
		Bus = 1;
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		if(Bus == 0){		//读0
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


/// 转换温度子函数
void tempConvert(){
	sensorInit();
	delayMs(1);
	writeInSensor(0xCC);		//跳过ROM寻址
	writeInSensor(0x44);		//启动一次温度转换
}


/// ds18b20获取温度
uint getTemp(){
	uint temp = 0;
	uchar LSB, MSB;				//用来储存数据的第八位与高八位
	sensorInit();
	delayMs(1);
	writeInSensor(0xCC);		//跳过寻址
	writeInSensor(0xBE);		//发送读值命令·
	LSB = readFromSensor();
	MSB = readFromSensor();
	temp = MSB;
	temp <<= 8;
	temp |= LSB;
	return temp;
}


/*ds18b20  返回最终结果子函数*/
uint getTempResult(){
	float tp;
	uint temp;
	delayMs(10);		//10ms度过不稳定期
	tempConvert();		//转换温度
    delayMs(1000);		//延时1s等待转化
    temp = getTemp();
    tp = temp;
    temp = tp * 0.0625;
    return temp;		//最终结果为temp
}