#include"common.h"
#include"oledio.h"
#include"fivekeys.h"
#include"control.h"

un8 chooseLine = 0;
void initinial(void)
{
	//interrupt
	EA = 1;

	//IO
	P_SW2 |= 0x80;//���������չ RAM �����⹦�ܼĴ���
	P0M0 = P1M0 = P2M0 = P3M0 = P4M0 = 0xff;
	P0M1 = P1M1 = P2M1 = P3M1 = P4M1 = 0x00;
//	P0PU = P1PU = P2PU = P3PU = P4PU = 0xff;

	P_SW2 &= 0x7f;

	//ultra sound
	UlSoundInitinal();
}


//main
//1.��ʼ����ģ�飬����io����������������
//2.��ʼ����ʾ�������ſ�������
//3.��ʾ����ʾ
//4.������������˵�

void main()
{
	initinial();
	startCartoon();
	chooseLine = -1;
	while (key_down | key_up | key_mid | key_left | key_right)
	{
		OLED_print("press any key to continue");
		delay(800);
		screenClear();
		delay(500);
	}
	chooseLine = 0;
	while (1)
	{
		OLED_print("car state  <off>\n");
		OLED_print("model test\n");
		if ((!key_up) && chooseLine > 0)
			chooseLine--;
		if ((!key_down) && chooseLine < 1)
			chooseLine++;
	}
}

void delay(un16 time)
{
	//@12.000MHz
	unsigned char i, j;
	while (time--)
	{
		i = 16;
		j = 147;
		do
		{
			while (--j);
		} while (--i);
	}
}