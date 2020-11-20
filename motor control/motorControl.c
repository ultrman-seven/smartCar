#include"control.h"
#include"oledio.h"
//adc采集样本数量
#define ADC_NUM 9
//速度控制系数，检测的电感电压值与标准检测值的差不能直接用来控制速度，
//因为大于100.要×这个比例系数，使其在区间（-std_s_l/r，100--std_s_l/r）内
#define speedControlCoefficient 40
#define obstacleDistance 100
#define std_adcValue 1900
//标准速度
#define std_s_l 20
#define std_s_r 20

un16 adcValueL, adcValueR;

int sleft, sright;
//标准adc检测值


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
	//T4ON
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

////返回中位数滤波后adc检测电感值
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

//在中断里对全局变量进行操作，
//如果全局变量被其他函数占用，对变量的操作会出错。草。

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