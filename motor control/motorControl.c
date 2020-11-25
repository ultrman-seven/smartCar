#include"control.h"
#include"oledio.h"
//adc采集样本数量
#define ADC_NUM 5
//#define stdADC 1220
//pid控制系数
#define Kp 60
#define Ki 0
#define Kd 10

//#define YinJie 290

//标准速度
#define stdSpeed 40

//开启定时器，t3 超声波，定时60ms；t4 adc检测，定时1毫秒；超声波及adc在定时器中断中进行
void carStart(void)
{
	//跑起来

	//正转
	motorStateSet(MOTOR_FORWARD, LEFTMOTOR);
	motorStateSet(MOTOR_FORWARD, RIGHTMOTOR);
	//全速
	motorSpeedSet(100, LEFTMOTOR);
	motorSpeedSet(100, RIGHTMOTOR);
	//无定时器（电感放在while，不用超声波）
}
void carOff(void)
{
	//减速
	//slow down
	motorSpeedSet(0, LEFTMOTOR);
	motorSpeedSet(0, RIGHTMOTOR);
	
	//制动
	//braking
	motorStateSet(MOTOR_BRAKING, LEFTMOTOR);
	motorStateSet(MOTOR_BRAKING, RIGHTMOTOR);
}

//返回平均值滤波后adc检测电感值
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
	static int proprotion = 0/*比例控制*/, integral = 0/*积分控制*/, differential = 0/*微分控制*/, temp;
	signed int controlSpeed, adcSum;
	un16 adcValueL, adcValueR, speedL, speedR;
	//采样
	adcValueL = findAverageAdcValue(LEFTindc);
	adcValueR = findAverageAdcValue(RIGHTindc);

	adcSum = (adcValueL + adcValueR) / 10;
	temp = proprotion;

	//比例误差
	proprotion = (adcValueL - adcValueR)/10;
	//积分误差
	integral += proprotion;
	//微分误差
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