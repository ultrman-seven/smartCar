#include"control.h"

#define ADC_NUM 5
//障碍物距离
un8 obstacleDistance = 100;
//标准速度
un8 std_s_l = 100;
un8 std_d_r = 100;

un8 roundTime = 50;//转弯时间
un8 straightTime = 50;//直行时间
un8 roundSpeed = 50;//转弯幅度

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

	//定时器3中断进行超声波
	//定时器4进行电感adc
	IE2 |= 0x60;//T3T4中断允许
	T4T3M = 0x20;//工作方式为定时，T3 12分频，T4 1分频

	//设置定时初值,超声波 60毫秒@12.000MHz
	T3L = 0xA0;
	T3H = 0x15;

	//设置定时初值,adc 1毫秒@12.000MHz
	T4L = 0x20;
	T4H = 0xD1;

	//定时器3定时器4开始工作
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