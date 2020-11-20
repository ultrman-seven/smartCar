#include"control.h"
#include"oledio.h"
//adc采集样本数量
#define ADC_NUM 9

//速度控制系数，检测的电感电压值与标准检测值的差不能直接用来控制速度，
//因为大于100.要×这个比例系数，使其在区间（-std_s_l/r，100--std_s_l/r）内
#define speedControlCoefficient 40

#define obstacleDistance 100

//标准adc检测值
#define std_adcValue 1900

//标准速度
#define std_s_l 20
#define std_s_r 20

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


//在中断里对全局变量进行操作，
//如果全局变量被其他函数占用，对变量的操作会出错。草。

//MCU the shit

//void t4_InductanceAdc(void) interrupt 20
//{
//	T4OFF

//	T4ON
//}