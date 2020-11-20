#include"control.h"
#include"oledio.h"
//adc�ɼ���������
#define ADC_NUM 9
//�ٶȿ���ϵ�������ĵ�е�ѹֵ���׼���ֵ�Ĳ��ֱ�����������ٶȣ�
//��Ϊ����100.Ҫ���������ϵ����ʹ�������䣨-std_s_l/r��100--std_s_l/r����
#define speedControlCoefficient 40
#define obstacleDistance 100
#define std_adcValue 1900
//��׼�ٶ�
#define std_s_l 20
#define std_s_r 20

un16 adcValueL, adcValueR;

int sleft, sright;
//��׼adc���ֵ


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
	//T4ON
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

////������λ���˲���adc�����ֵ
//un16 findMedianAdcValue(un8 adc)
//{
//	//un16 value[ADC_NUM];
//	un16 sum = 0;
//	un8 count;
//	for (count = 0; count < ADC_NUM; count++)
//		sum += adcMeasure(adc);
//		//value[count] = adcMeasure(adc);
////ave
//	//for (count = 0; count > ADC_NUM; count--)
//	//	sum += value[count];
//	return sum / ADC_NUM;
//}

//���ж����ȫ�ֱ������в�����
//���ȫ�ֱ�������������ռ�ã��Ա����Ĳ���������ݡ�

//MCU the shit

void t4_InductanceAdc(void) interrupt 20
{

	T4OFF
		//adcValueL = findMedianAdcValue(LEFTindc);
		//adcValueR = findMedianAdcValue(RIGHTindc);

	adcValueL = adcMeasure(LEFTindc);
	delay(1);
	adcValueR = adcMeasure(RIGHTindc);
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
	delay(500);
	T4ON
}