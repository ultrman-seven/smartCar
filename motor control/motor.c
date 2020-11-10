#include"motor.h"

void motorStateSet(un8 state, un8 motor)
{
	un8 m0, m1;
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

	if (motor)
	{
		M0right = m0;
		M1right = m1;
	}
	else
	{
		M0left = m0;
		M1left = m1;
	}
}

void motorSpeedSet(un8 speed, un8 motor)
{
	if (motor == LEFTMOTOR)
		E_left = speed;
	else
		E_right = speed;
}
/*
void motorSpeedSet(un8 speed, un8 motor)
{
	un16 dutyCycle = 0xff * speed / 100;
	P_SW2 |= 0x80;
	PWM1_CCER1 = 0x00;
	PWM1_CCMR1 = 0x60;
	PWM1_CCER1 = 0x60;




	P_SW2 &= 0x7f;
}
*/