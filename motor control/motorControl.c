#include"control.h"
#include"oledio.h"
#include"beep.h"
#include"fivekeys.h"

#define T4ON T4T3M|=0x80
#define T4OFF T4T3M&=0x7f
#define T3ON T4T3M|=0x08
#define T3OFF T4T3M&=0xf7

//adc采集样本数量
#define ADC_NUM 5
//pid控制系数
#define Kp 50
#define Ki 0
#define Kd 200
//标准速度
#define stdSpeed 90

bit testFlag = 0;

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
	
	//设置定时器3/4
	//定时器3用于检验直行转弯，定时10ms
	//定时器4用于检测障碍物距离，定时60ms
	T4T3M =0x00;	//定时器时钟12T模式

	T3L = 0xF0;		//设置定时初值
	T3H = 0xD8;		//设置定时初值
	T3ON;	//定时器3开始计时

	T4L = 0xA0;		//设置定时初值
	T4H = 0x15;		//设置定时初值
	T4ON;	//定时器4开始计时

	IE2 |= 0x60;//允许定时器3，4中断
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
	T3OFF;
	T4OFF;
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
	static un8 testTime = 0;
	static int runState = 0;
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

	//检测是直行还是转弯
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
	AUXINTIF &= 0xfd;//清除中断标志
	testFlag = 1;
}

void obstucleTest(void) interrupt 20
{
	AUXINTIF &= 0xfb;//清除中断标志
	if (ULsound_diatance() <= 40)
	{
		bepForSecs(1);
		key_mid = 0;
	}
}