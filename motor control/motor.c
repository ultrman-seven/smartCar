#include"motor.h"

void motorSpeedSet(un8 speed, un8 motor)
{
	un16 dutyCycle = 0xff * speed / 100;
	P_SW2 |= 0x80;
	if (motor == LEFTMOTOR)
	{
		PWM2_CCR1H = (dutyCycle >> 8) & 0x00ff;
		PWM2_CCR1L = dutyCycle & 0x00ff;

	}
	else
	{
		PWM2_CCR3H = (dutyCycle >> 8) & 0x00ff;
		PWM2_CCR3L = dutyCycle & 0x00ff;
	}
	P_SW2 &= 0x7f;
}
void motorStateSet(un8 state, un8 motor)
{
	bit m0, m1;
	switch (state)
	{
	case MOTOR_FORWARD:
		m0 = 0;
		m1 = 1;
		break;
	case MOTOR_OPPOSITE:
		m0 = 1;
		m1 = 0;
		break;
	case MOTOR_BRAKING:
		m0 = m1 = 0;
		break;
	default:
		break;
	}
	if (motor == LEFTMOTOR)
	{
		M0left = m0;
		M1left = m1;
	}
	else
	{
		M0right = m0;
		M1right = m1;
	}
}
void motorInitial(void)
{
	P_SW2 |= 0x80;
	//设置pwm输出模式，使能通道
	PWM2_CCER1 = 0x00;
	PWM2_CCER2 = 0x00;
	PWM2_CCMR1 = 0x60;
	PWM2_CCMR3 = 0x60;
	PWM2_CCER1 = 0x01;
	PWM2_CCER2 = 0x01;
	//周期
	PWM2_ARRH = 0x00;
	PWM2_ARRL = 0x00;

	//初始占空比100%
	PWM2_CCR1H = 0xff;
	PWM2_CCR1L = 0xff;
	PWM2_CCR3H = 0xff;
	PWM2_CCR3L = 0xff;

	PWM2_ENO = 0x11;//使能pwm2_P1/P2输出
	PWM2_BKR = 0x80;//使能总输出
	PWM2_CR1 = 0x01;//开始计时
	P_SW2 &= 0x7f;
}