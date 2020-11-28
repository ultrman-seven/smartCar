#include"beep.h"

sbit bep = P0 ^ 4;

un8 t2time = 0;

// 开/关蜂鸣器
void beepOnOff(bit state)
{
	bep = state;
}

//定时器响time秒
void bepForSecs(un8 time)
{
	bep = 0;

	//使用定时器2定时50ms
	//在中断中，达到time秒则关闭蜂鸣器
	AUXR &= 0xF3;		//定时器时钟12T模式
	T2L = 0xB0;		//设置定时初值
	T2H = 0x3C;		//设置定时初值
	AUXR |= 0x10;		//定时器2开始计时

	IE2 |= 0x04;//允许定时器2中断
	AUXINTIF &= 0xfe;//清除中断标志

	t2time = time * 20;
}

void t2Interrupt(void) interrupt 12
{
	AUXINTIF &= 0xfe;//清除中断标志
	if (t2time--)
	{
		T2L = 0xB0;		//设置定时初值
		T2H = 0x3C;		//设置定时初值
		AUXR |= 0x10;		//定时器2开始计时
	}
	else
	{
		AUXR &= 0xef;//定时器停止计时
		bep = 1;//关蜂鸣器
	}
}