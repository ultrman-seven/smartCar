#include"control.h"
#include"stdlib.h"
#define ADC_NUM 5
//�ϰ�����С����
un8 obstacleDistance = 100;
//��׼�ٶ�
un8 std_s_l = 90;
un8 std_s_r = 90;

//��׼adc���ֵ
un16 std_adcValue = 0xf0f0;

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
	//T3ON//��ʹ�ó�����
}
void carOff(void)
{
	//�ض�ʱ�����س������͵�У�
	T4OFF
	T3OFF
	//����
	//slow down
	motorSpeedSet(0, LEFTMOTOR);
	motorSpeedSet(0, RIGHTMOTOR);
	
	//�ƶ�
	//braking
	motorStateSet(MOTOR_BRAKING, LEFTMOTOR);
	motorStateSet(MOTOR_BRAKING, RIGHTMOTOR);
}

void t3_UlSound(void) interrupt 19
{
	if (ULsound_diatance() <= obstacleDistance)
	{
		T3OFF
		//����û�ã�д���档������
		//just for fun
		//�����ݻ�ͣ����
		motorStateSet(MOTOR_OPPOSITE, LEFTMOTOR);
		delay(0xffff);
		motorStateSet(MOTOR_FORWARD, RIGHTMOTOR);
		//motorSpeedSet(roundSpeed, LEFTMOTOR);
		//delay(10 * roundTime);
		//motorSpeedSet(100, LEFTMOTOR);
		//motorSpeedSet(roundSpeed, RIGHTMOTOR);
		//delay(10 * roundTime);
		//motorSpeedSet(100, RIGHTMOTOR);
		//delay(100 * straightTime);

		//motorSpeedSet(roundSpeed, RIGHTMOTOR);
		//delay(10 * roundTime);
		//motorSpeedSet(100, RIGHTMOTOR);
		//motorSpeedSet(roundSpeed, LEFTMOTOR);
		//delay(10 * roundTime);
		//motorSpeedSet(100, LEFTMOTOR);
		T3ON
	}
}

//������λ���˲���adc�����ֵ
un16 findMedianAdcValue(un16 adc)
{
	un16 value[ADC_NUM];
	un8 count, i, temp;
	for (count = 0; count < ADC_NUM; count++)
		value[count] = adcMeasure(adc);
//�Ÿ�����Ϊ��ֵ�Ƚ��٣����Բ���shell�㷨�����������
	for (count = ADC_NUM - 1; count > 0; count--)
		for (i = 0; i < count; i++)
			if (value[i] < value[i + 1])
			{
				temp = value[i];
				value[i] = value[i + 1];
				value[i + 1] = temp;
			}
	return value[1 + ADC_NUM / 2];
}

void t4_InductanceAdc(void) interrupt 20
{
	un16 adcValueL, adcValueR;
	T4OFF
	adcValueL = findMedianAdcValue(LEFTindc);
	adcValueR = findMedianAdcValue(RIGHTindc);
	motorSpeedSet(std_s_l + std_adcValue - adcValueL, LEFTMOTOR);
	motorSpeedSet(std_s_r + std_adcValue - adcValueR, RIGHTMOTOR);
	T4ON
}