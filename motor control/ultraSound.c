#include"ultraSound.h"

sbit trig = P0 ^ 5;
sbit echo = P3 ^ 2;

un16 distance = 0;
//8H
void Delay20us()		//@12.000MHz
{
	unsigned char i;

	i = 78;
	while (--i);
}
void Delay100ms()		//@12.000MHz
{
	unsigned char i, j, k;

	_nop_();
	i = 7;
	j = 23;
	k = 105;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void UlSoundInitinal(void)
{
	trig = 0;
	echo = 1;
	IT0 = 1;
	Delay100ms();
	//tmod:0000 1001
	//对t0: gate = 1，只有INT0为高电平（echo拉高）时才开始计数，C/T = 0，定时模式， m1m0 = 01， 工作方式16位不重装载
	TMOD = 0x09;
}

un16 ULsound_diatance(void)
{
	un8 maxWait = 100;
	distance = 0;

	//ultra sound start
	//启动超声波模块
	trig = 1;
	Delay20us();
	trig = 0;

	while (!echo);//waiting for echo//等待echo拉高

	//set timer0
	//设置定时器0
	TH0 = TL0 = 0;//定时器初值0
	TR0 = 1;//定时器开始计时

	//echo拉低即进入外部中断
	EX0 = 1;//允许外部中断
	IE0 = 0;//清除外部中断标志

	//等待echo拉低（外部中断结束）或超时
	while (echo&&--maxWait)
		delay(2);
	return distance * 0.017;//cm
}

//echo 置低电平时触发外部中断，在此停止定时器并读取定时的时间
void countDistance(void) interrupt 0
{
	TR0 = 0;//关闭计时器
	//读取时间
	distance = TH0;
	distance <<= 8;
	distance |= TL0;

	EX0 = 0;//关闭外部中断
}