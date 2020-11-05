#include"common.h"
#include"OLED.h"
#include"fivekeys.h"
#include"ultraSound.h"
#define OBSTACLE_DISTANCE 100
sbit TR4 = T4T3M ^ 7;
sbit TR3 = T4T3M ^ 3;
void initinial(void)
{
	//interrupt
	EA = 1;

	//IO
	//���Ƚ�P_SW2��BIT7����Ϊ1
	P_SW2 |= 0x80;
	P0M0 = P1M0 = P2M0 = P3M0 = P4M0 = 0xff;
	P0M1 = P1M1 = P2M1 = P3M1 = P4M1 = 0x00;
//	P0PU = P1PU = P2PU = P3PU = P4PU = 0xff;

	//ultra sound
	UlSoundInitinal();
}
void main()
{
	initinial();
	startCartoon();
	
	//��ʱ��3�жϽ��г�����
	//��ʱ��4���е��adc
	IE2 |= 0x60;//T3T4�ж�����
	T4T3M = 0x20;//������ʽΪ��ʱ��T3 12��Ƶ��T4 1��Ƶ

	//���ö�ʱ��ֵ,������ 60����@12.000MHz
	T3L = 0xA0;
	T3H = 0x15;
		
	//���ö�ʱ��ֵ,adc 1����@12.000MHz
	T4L = 0x20;
	T4H = 0xD1;

	TR3 = TR4 = 1;//��ʱ��3��ʱ��4��ʼ����

	while (1);
}

void t3_UlSound(void) interrupt 19
{
	if (ULsound_diatance() <= OBSTACLE_DISTANCE)
	{
		TR3 = 0;

		TR3 = 1;
	}
}

void t4_InductanceAdc(void) interrupt 20
{


}