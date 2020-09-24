#include<reg51.h>
#include<intrins.h>
#define uint unsigned int
#define uchar unsigned char
sbit RS=P2^0;
sbit RW=P2^1;
sbit EN=P2^2;
void DelayMS(uint ms)//��ʱ
{
 uchar i;
 while(ms--)
 {
  for(i=0;i<120;i++); 
  }
}
 uchar Busy_Check()   //æ��飬������ÿ�ν��ж�д����֮ǰ����������ж�д��⣬
                      //ȷ��STA7Ϊ0
{
  uchar	LCD_Status;//����оƬ����ʱ�򣬶�����ʱRS=0��RW=1��EN�����壨150ns��
  RS=0;	 //RS=0 ѡ�����RS=1ѡ������
  RW=1;	 // RW=1ѡ����� RW=0ѡ��д
  EN=1;	 //��ʼ��
  DelayMS(1);
  LCD_Status=P0; //����STA7��״̬��Ҳ����P0�����λ
  EN=0;
  return LCD_Status;//�˻�״ֵ̬
}
void Write_LCD_Conmmand(uchar cmd)   //дLCD���RS=0��RW=0��EN������
{
 while((Busy_Check()&0x80)==0x80);//æ�ȴ������λΪ0ʱ��LCD���У�����
  RS=0;	 //����
  RW=0;	 //д
  EN=0;
  DelayMS(1);
  P0=cmd;
  EN=1;
  //DelayMS(1);
  EN=0;
}
void Write_LCD_Data(uchar dat)//��������
{
 while((Busy_Check()&0x80)==0x80);//æ�ȴ�
  RS=1;	 //����
  RW=0;	 //д
  EN=0;
   DelayMS(1);
  P0=dat;
  EN=1;
  //DelayMS(1);
  EN=0;
}
void Initiallize_LCD() //LCD��ʼ��
{
  Write_LCD_Conmmand(0x38);  //ָ��0x38��������16*2Һ����ʾ��5*7����8λ
  DelayMS(1);
  Write_LCD_Conmmand(0x01);  //����
  DelayMS(1);
  Write_LCD_Conmmand(0x06);
  DelayMS(1);
  Write_LCD_Conmmand(0x0C);
  DelayMS(1);
}
void ShowString(uchar x,uchar y,uchar *str) //��ʾ�ַ�����xȡֵ0~15��yȡֵ0~1��1602Һ��ÿ����ʾ16���ַ��������У�
{
  uchar i=0;  //������ʾ��ʼλ��
  if(y==0) //��һ��
  {
   Write_LCD_Conmmand(0x80|x);// 0x80��һ�е�����ָ��ָ����
   }
   if(y==1) //�ڶ���
   {
    Write_LCD_Conmmand(0xC0|x);
	}
   for(i=0;i<16;i++)  //ÿ��16���ַ�
   {
	 Write_LCD_Data(str[i]);
	}
}