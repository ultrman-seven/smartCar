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
	//需先将P_SW2的BIT7设置为1
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
	
	//定时器3中断进行超声波
	//定时器4进行电感adc
	IE2 |= 0x60;//T3T4中断允许
	T4T3M = 0x20;//工作方式为定时，T3 12分频，T4 1分频

	//设置定时初值,超声波 60毫秒@12.000MHz
	T3L = 0xA0;
	T3H = 0x15;
		
	//设置定时初值,adc 1毫秒@12.000MHz
	T4L = 0x20;
	T4H = 0xD1;

	TR3 = TR4 = 1;//定时器3定时器4开始工作

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