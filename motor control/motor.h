#ifndef __MOTOR_H__
#define __MOTOR_H__
#include"common.h"

#define LEFTMOTOR 0
#define RIGHTMOTOR 1

#define MOTOR_FORWARD 2
#define MOTOR_OPPOSITE 1
#define MOTOR_BRAKING 3

sbit E_left = P2 ^ 0;
sbit E_right = P2 ^ 2;
sbit M1left = P3 ^ 5;
sbit M0left = P5 ^ 1;
sbit M0right = P5 ^ 0;
sbit M1right = P3 ^ 4;

void motorStateSet(un8 state, un8 motor);
void motorSpeedSet(un8 speed, un8 motor);
void motorInitial(void);
#endif // !__MOTOR_H__
