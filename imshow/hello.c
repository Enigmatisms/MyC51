#include<reg51.h>                   
#include<intrins.h>
#define uint unsigned int
#define uchar unsigned char
void Initiallize_LCD();//
void ShowString(uchar x,uchar y,uchar *str);
uchar code Display[35]="Hello world from 51 A panda picture";
 //�ַ�Ҫ��˫�������������ո�Ҳ��-һ���ַ�����32���ַ�(0~31)��
 void main()
{
 Initiallize_LCD();
 ShowString(0,0,Display); //�ӵ�һ������ʼʪʾ
 ShowString(0,1,Display+19);//�ڥ��дӵ�17���ַ�д��0�ǵ�һ���ַ�
 while(1);
}