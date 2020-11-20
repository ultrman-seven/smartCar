#include"control.h"
#include"oledio.h"
//adc�ɼ���������
#define ADC_NUM 9

//�ٶȿ���ϵ�������ĵ�е�ѹֵ���׼���ֵ�Ĳ��ֱ�����������ٶȣ�
//��Ϊ����100.Ҫ���������ϵ����ʹ�������䣨-std_s_l/r��100--std_s_l/r����
#define speedControlCoefficient 40

#define obstacleDistance 100

//��׼adc���ֵ
#define std_adcValue 1900

//��׼�ٶ�
#define std_s_l 20
#define std_s_r 20

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
un16 findMedianAdcValue(un8 adc)
{
	un16 sum = 0;
	un8 count;
	for (count = 0; count < ADC_NUM; count++)
		sum += adcMeasure(adc);
	return sum / ADC_NUM;
}
void carControl(void)
{
	int sleft, sright;
	un16 adcValueL, adcValueR;
	adcValueL = findMedianAdcValue(LEFTindc);
	adcValueR = findMedianAdcValue(RIGHTindc);
	sleft = std_s_l + (std_adcValue - adcValueL) / speedControlCoefficient;
	sright = std_s_r + (std_adcValue - adcValueR) / speedControlCoefficient;
	sleft = sleft > 100 ? 100 : sleft;
	sleft = sleft < 0 ? 0 : sleft;
	sright = sright > 100 ? 100 : sright;
	sright = sright < 0 ? 0 : sright;

	motorSpeedSet(sleft, LEFTMOTOR);
	motorSpeedSet(sright, RIGHTMOTOR);

	screenClear();
	OLED_print("left-->");
	OLED_putNumber(sleft);
	OLED_print("\nright-->");
	OLED_putNumber(sright);
	OLED_print("\nadc_l-->");
	OLED_putNumber(adcValueL);
	OLED_print("\nadc_r-->");
	OLED_putNumber(adcValueR);
}


//���ж����ȫ�ֱ������в�����
//���ȫ�ֱ�������������ռ�ã��Ա����Ĳ���������ݡ�

//MCU the shit

//void t4_InductanceAdc(void) interrupt 20
//{
//	T4OFF

//	T4ON
//}