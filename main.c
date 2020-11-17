#include"common.h"
#include"oledio.h"
#include"fivekeys.h"
#include"control.h"
#include"menu.h"

sbit bep = P0 ^ 4;

void initinial(void)
{
	//interrupt
	EA = 1;//总中断

	P_SW2 |= 0x80;//允许访问扩展 RAM 区特殊功能寄存器

	//IO全设置成推挽输出，带劲！
	P0M0 = P1M0 = P2M0 = P3M0 = P4M0 = P5M0 = 0xff;
	P0M1 = P1M1 = P2M1 = P3M1 = P4M1 = P5M1 = 0x00;
	//上拉电阻
	P0PU = P1PU = P2PU = P3PU = P4PU = 0xff;

	P_SW2 &= 0x7f;

	bep = 1;
	//ultra sound
	UlSoundInitinal();

	//car
	motorInitial();
	carOff();

	//key
	key_up = key_down = key_left = key_right = key_mid = 1;
	
	//menu
	menuInitial();
}

//main
//1.初始化各模块，包括io，超声波，蜂鸣器
//2.初始化显示屏，播放开机动画
//3.显示屏显示
//4.触发按键进入菜单

void main()
{
	initinial();
	startCartoon();
	chooseLine = -1;
	while (NO_HaveKeyBeenPressed)
	{
		OLED_print("press any key\nto continue");
		delay(800);
		screenClear();
		delay(500);
	}
	chooseLine = 0;
	displayMenu();
	while (!NO_HaveKeyBeenPressed)
		;
	while (1)
		keyOperation();
}

void delay(un16 time)//大约延时为time毫秒
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