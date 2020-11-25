#include"control.h"
#include"oledio.h"
//adc�ɼ���������
#define ADC_NUM 5
//#define stdADC 1220
//pid����ϵ��
#define Kp 60
#define Ki 0
#define Kd 10

//#define YinJie 290

//��׼�ٶ�
#define stdSpeed 40

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
	//�޶�ʱ������з���while�����ó�������
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

	delay(1);
}