/**
 * ================= ���ú����Լ����� ====================
 * @date 2020.10.4
 * @author ��ǧԽ
*/
#ifndef __UTILS_H__
#define __UTILS_H__

#include <reg52.h>
#define uint unsigned int
#define uchar unsigned char
	

// =============== ������ ================== //
#define CENTRAL 0
#define LEFT	1
#define RIGHT	2
#define CALC	0			// ϵͳģʽ
#define SETS	1			// 1Ϊ ָʾ�� 2Ϊ������ 3Ϊ��ѧ��������ʾ
#define MENU	4			// 4Ϊ����ģʽ	5Ϊ�¶���ʾ  6Ϊ��������
#define TEMP_SENSOR	5		// �¶ȴ�������ѡ
#define ALARM_SET	6		// ���Ӵ�ѡ
#define IN_SENSOR	7		// �¶ȴ����������ڲ�
#define IN_ALARM	8		// �������ý����ڲ�
#define ALARMING	9		// ����������
#define SUSPEND		0xff	// ����ģʽ

#define ALARM_MAX 3599		// ����������59��59��

extern uchar _mode;			// ��ǰģʽ @todo ��ͨ����ģʽ���¶�/������ʾģʽ���������ã���ʱ���жϴ�/�رգ���
extern bit suspend_lock;
extern uchar sets[3];		// ����
	
// ��ƫ��
extern uchar code line_offset[4];

extern uchar code menuItems[3][20];

extern uchar code settingItems[3][20];

extern uchar code errors[3][20];

extern uchar code temp_info[4][20];

extern uchar code describe[4][12];

extern uchar code alarm_info[6][20];

extern uchar code alarm_ui[4][20];

extern uchar code suspend_ui[3][20];

extern uchar code FREQH[28];

extern uchar code FREQL[28];

extern uchar code song[84];

int strlen(uchar* ptr);

void delayMs(uint ms);

void tempDisplay(uint temp, bit celc, uchar* str);

#endif 	//__UTILS_H__