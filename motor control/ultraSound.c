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
	//��t0: gate = 1��ֻ��INT0Ϊ�ߵ�ƽ��echo���ߣ�ʱ�ſ�ʼ������C/T = 0����ʱģʽ�� m1m0 = 01�� ������ʽ16λ����װ��
	TMOD = 0x09;
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
	TH0 = TL0 = 0;//��ʱ����ֵ0
	TR0 = 1;//��ʱ����ʼ��ʱ

	//echo���ͼ������ⲿ�ж�
	EX0 = 1;//�����ⲿ�ж�
	IE0 = 0;//����ⲿ�жϱ�־

	//�ȴ�echo���ͣ��ⲿ�жϽ�������ʱ
	while (echo&&--maxWait)
		delay(2);
	return distance * 0.017;//cm
}

//echo �õ͵�ƽʱ�����ⲿ�жϣ��ڴ�ֹͣ��ʱ������ȡ��ʱ��ʱ��
void countDistance(void) interrupt 0
{
	TR0 = 0;//�رռ�ʱ��
	//��ȡʱ��
	distance = TH0;
	distance <<= 8;
	distance |= TL0;

	EX0 = 0;//�ر��ⲿ�ж�
}