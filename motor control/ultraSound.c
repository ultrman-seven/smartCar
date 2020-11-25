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
	trig = echo = 0;
	Delay100ms();
}

un16 ULsound_diatance(void)
{
	un8 maxWait = 100;
	distance = 0;

	//ultra sound start
	//����������ģ��
	trig = 1;
	Delay20us();
	trig = 0;

	while (!echo);//waiting for echo//�ȴ�echo����
	//set timer0
	//���ö�ʱ��0
	TMOD = 0x01;
	TH0 = TL0 = 0;
	TR0 = 1;
	EX0 = 1;
	//�ȴ�echo���ͣ��ⲿ�жϽ�������ʱ
	while (echo&&--maxWait)
		delay(2);
	return distance * 0.017;//cm
}

//echo �õ͵�ƽʱ�����ⲿ�жϣ��ڴ�ֹͣ��ʱ������ȡ��ʱ��ʱ��
void countDistance(void) interrupt 0
{
	TR0 = 0;
	distance = TH0;
	distance <<= 8;
	distance |= TL0;
	EX0 = 0;
}