#ifndef __MOTOR_H__
#define __MOTOR_H__
#include"common.h"

#define LEFTMOTOR 0
#define RIGHTMOTOR 1

#define MOTOR_FORWARD 1
#define MOTOR_OPPOSITE 2
#define MOTOR_BRAKING 3

sbit E_left = P0 ^ 0;
sbit E_right = P0 ^ 1;
sbit M0left = P3 ^ 5;
sbit M1left = P5 ^ 1;
sbit M0right = P5 ^ 0;
sbit M1right = P3 ^ 4;

void motorStateSet(un8 state, un8 motor);
void motorSpeedSet(un8 speed, un8 motor);
#endif // !__MOTOR_H__
