#include"control.h"
#include"stdlib.h"
#define ADC_NUM 5
//障碍物最小距离
un8 obstacleDistance = 100;
//标准速度
un8 std_s_l = 90;
un8 std_s_r = 90;

//标准adc检测值
un16 std_adcValue = 0xf0f0;

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
	//T3ON//不使用超声波
}
void carOff(void)
{
	//关定时器（关超声波和电感）
	T4OFF
	T3OFF
	//减速
	//slow down
	motorSpeedSet(0, LEFTMOTOR);
	motorSpeedSet(0, RIGHTMOTOR);
	
	//制动
	//braking
	motorStateSet(MOTOR_BRAKING, LEFTMOTOR);
	motorStateSet(MOTOR_BRAKING, RIGHTMOTOR);
}

void t3_UlSound(void) interrupt 19
{
	if (ULsound_diatance() <= obstacleDistance)
	{
		T3OFF
		//反正没用，写着玩。。。。
		//just for fun
		//龙卷风摧毁停车场
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

//返回中位数滤波后adc检测电感值
un16 findMedianAdcValue(un16 adc)
{
	un16 value[ADC_NUM];
	un8 count, i, temp;
	for (count = 0; count < ADC_NUM; count++)
		value[count] = adcMeasure(adc);
//排个序，因为数值比较少，所以不用shell算法，简单排序就行
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