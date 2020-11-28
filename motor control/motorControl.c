#include"control.h"
#include"oledio.h"
#include"beep.h"
#include"fivekeys.h"

#define T4ON T4T3M|=0x80
#define T4OFF T4T3M&=0x7f
#define T3ON T4T3M|=0x08
#define T3OFF T4T3M&=0xf7

//adc�ɼ���������
#define ADC_NUM 5
//pid����ϵ��
#define Kp 50
#define Ki 0
#define Kd 200
//��׼�ٶ�
#define stdSpeed 90

bit testFlag = 0;

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
	
	//���ö�ʱ��3/4
	//��ʱ��3���ڼ���ֱ��ת�䣬��ʱ10ms
	//��ʱ��4���ڼ���ϰ�����룬��ʱ60ms
	T4T3M =0x00;	//��ʱ��ʱ��12Tģʽ

	T3L = 0xF0;		//���ö�ʱ��ֵ
	T3H = 0xD8;		//���ö�ʱ��ֵ
	T3ON;	//��ʱ��3��ʼ��ʱ

	T4L = 0xA0;		//���ö�ʱ��ֵ
	T4H = 0x15;		//���ö�ʱ��ֵ
	T4ON;	//��ʱ��4��ʼ��ʱ

	IE2 |= 0x60;//����ʱ��3��4�ж�
}
void carOff(void)
{
	//����
	//slow down
	motorSpeedSet(0, LEFTMOTOR);
	motorSpeedSet(0, RIGHTMOTOR);
	
	//�ƶ�
	//braking
	motorStateSet(MOTOR_BRAKING, LEFTMOTOR);
	motorStateSet(MOTOR_BRAKING, RIGHTMOTOR);
	T3OFF;
	T4OFF;
}

//����ƽ��ֵ�˲���adc�����ֵ
un16 findAverageAdcValue(un8 adc)
{
	un16 sum = 0;
	un8 count;
	for (count = 0; count < ADC_NUM; count++)
		sum += adcMeasure(adc);
	return sum / ADC_NUM;
}

void carControl(void)
{
	static int proprotion = 0/*��������*/, integral = 0/*���ֿ���*/, differential = 0/*΢�ֿ���*/, temp;
	signed int controlSpeed, adcSum;
	un16 adcValueL, adcValueR, speedL, speedR;
	static un8 testTime = 0;
	static int runState = 0;
	//����
	adcValueL = findAverageAdcValue(LEFTindc);
	adcValueR = findAverageAdcValue(RIGHTindc);

	adcSum = (adcValueL + adcValueR) / 10;
	temp = proprotion;

	//�������
	proprotion = (adcValueL - adcValueR)/10;
	//�������
	integral += proprotion;
	//΢�����
	differential = proprotion - temp;

	controlSpeed = (Kp * proprotion + Ki * integral + Kd * differential) / adcSum;

	speedL = (stdSpeed - controlSpeed) > 0 ? stdSpeed - controlSpeed : 0;
	speedR = (stdSpeed + controlSpeed) > 0 ? stdSpeed + controlSpeed : 0;
	
	speedL = (speedL > 100) ? 100 : speedL;
	speedR = (speedR > 100) ? 100 : speedR;
	motorSpeedSet(speedL, LEFTMOTOR);
	motorSpeedSet(speedR, RIGHTMOTOR);

	screenClear();
	OLED_print("left-->");
	OLED_putNumber(speedL);
	OLED_print("\nright-->");
	OLED_putNumber(speedR);
	OLED_print("\nadc_l-->");
	OLED_putNumber(adcValueL);
	OLED_print("\nadc_r-->");
	OLED_putNumber(adcValueR);

	//�����ֱ�л���ת��
	if (testFlag)
		if (testTime++ < 10)
		{
			runState += (controlSpeed / 10);
		}
		else
		{
			testTime = testFlag = runState = 0;
			if (runState >= 10 || runState <= -10)
				beepOnOff(BEEP_ON);
			else
				beepOnOff(BEEP_OFF);
		}
}

void runStateTest(void) interrupt 19
{
	AUXINTIF &= 0xfd;//����жϱ�־
	testFlag = 1;
}

void obstucleTest(void) interrupt 20
{
	AUXINTIF &= 0xfb;//����жϱ�־
	if (ULsound_diatance() <= 40)
	{
		bepForSecs(1);
		key_mid = 0;
	}
}