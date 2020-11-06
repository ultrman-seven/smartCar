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
sbit M0left = P0 ^ 2;
sbit M1left = P0 ^ 3;
sbit M0right = P0 ^ 4;
sbit M1right = P0 ^ 5;
#endif // !__MOTOR_H__
