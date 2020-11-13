#include"control.h"

#define ADC_NUM 5
//�ϰ������
un8 obstacleDistance = 100;
//��׼�ٶ�
un8 std_s_l = 100;
un8 std_d_r = 100;

un8 roundTime = 50;//ת��ʱ��
un8 straightTime = 50;//ֱ��ʱ��
un8 roundSpeed = 50;//ת�����

//������ʱ����t3 ����������ʱ60ms��t4 adc��⣬��ʱ1���룻��������adc�ڶ�ʱ���ж��н���
void carStart(void)
{
	//������

	//��ת
	motorStateSet(MOTOR_FORWARD, LEFTMOTOR);
	motorStateSet(MOTOR_FORWARD, RIGHTMOTOR);
	//ȫ��
	motorSpeedSet(100, LEFTMOTOR);
	motorSpeedSet(100, RIGHTMOTOR);

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

	//��ʱ��3��ʱ��4��ʼ����
	T4ON
	T3ON
}
void carOff(void)
{
	T4OFF
	T3OFF
	motorSpeedSet(0, LEFTMOTOR);
	motorSpeedSet(0, RIGHTMOTOR);
}

void t3_UlSound(void) interrupt 19
{
	if (ULsound_diatance() <= obstacleDistance)
	{
		T3OFF
		motorSpeedSet(roundSpeed, LEFTMOTOR);
		delay(10 * roundTime);
		motorSpeedSet(100, LEFTMOTOR);
		motorSpeedSet(roundSpeed, RIGHTMOTOR);
		delay(10 * roundTime);
		motorSpeedSet(100, RIGHTMOTOR);
		delay(100 * straightTime);

		motorSpeedSet(roundSpeed, RIGHTMOTOR);
		delay(10 * roundTime);
		motorSpeedSet(100, RIGHTMOTOR);
		motorSpeedSet(roundSpeed, LEFTMOTOR);
		delay(10 * roundTime);
		motorSpeedSet(100, LEFTMOTOR);
		T3ON
	}
}

void t4_InductanceAdc(void) interrupt 20
{
	un8 aLeft[ADC_NUM];
	un8 aRight[ADC_NUM];
	un8 count;
	T4OFF
	for (count = 0; count < ADC_NUM; count++)
		aLeft[count] = adcMeasure(LEFTindc);
	for (count = 0; count < ADC_NUM; count++)
		aRight[count] = adcMeasure(RIGHTindc);

}