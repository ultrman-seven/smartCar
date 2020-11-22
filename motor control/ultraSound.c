#include"ultraSound.h"

sbit trig = P0 ^ 5;
sbit echo = P3 ^ 2;

un16 distance = 0;
un8 t0Time = 1;
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
	Delay100ms();
}

un16 ULsound_diatance(void)
{
	un8 maxWait = 30;
	distance = 0;
	t0Time = 0;

	//ultra sound start
	//启动超声波模块
	trig = 1;
	Delay20us();
	trig = 0;

	while (!echo);//waiting for echo//等待echo拉高
	//set timer0
	//设置定时器0
	TMOD = 0x01;
	TH0 = TL0 = 0;
	TR0 = 1;
	EX0 = ET0 = 1;
	//等待echo拉低（外部中断结束）或超时
	while (echo&&--maxWait)
		delay(2);
	return t0Time * 1114 + distance * 0.017;//cm
}

//echo 置低电平时触发外部中断，在此停止定时器并读取定时的时间
void countDistance(void) interrupt 0
{
	TR0 = ET0 = 0;
	distance = TH0;
	distance <<= 8;
	distance |= TL0;
	EX0 = 0;
}

//定时器0计数满后，t0time（定时器0满的次数）+1，重置定时器初值
void t0interrupt(void) interrupt 1
{
	t0Time++;
	TH0 = TL0 = 0;
}