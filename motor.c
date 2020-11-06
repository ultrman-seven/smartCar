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

}