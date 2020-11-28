#include"beep.h"

sbit bep = P0 ^ 4;

un8 t2time = 0;

// ��/�ط�����
void beepOnOff(bit state)
{
	bep = state;
}

//��ʱ����time��
void bepForSecs(un8 time)
{
	bep = 0;

	//ʹ�ö�ʱ��2��ʱ50ms
	//���ж��У��ﵽtime����رշ�����
	AUXR &= 0xF3;		//��ʱ��ʱ��12Tģʽ
	T2L = 0xB0;		//���ö�ʱ��ֵ
	T2H = 0x3C;		//���ö�ʱ��ֵ
	AUXR |= 0x10;		//��ʱ��2��ʼ��ʱ

	IE2 |= 0x04;//����ʱ��2�ж�
	AUXINTIF &= 0xfe;//����жϱ�־

	t2time = time * 20;
}

void t2Interrupt(void) interrupt 12
{
	AUXINTIF &= 0xfe;//����жϱ�־
	if (t2time--)
	{
		T2L = 0xB0;		//���ö�ʱ��ֵ
		T2H = 0x3C;		//���ö�ʱ��ֵ
		AUXR |= 0x10;		//��ʱ��2��ʼ��ʱ
	}
	else
	{
		AUXR &= 0xef;//��ʱ��ֹͣ��ʱ
		bep = 1;//�ط�����
	}
}