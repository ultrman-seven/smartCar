#ifndef __CONTROL_H__
#define __CONTOL_H__
#include"common.h"
#include"motor.h"
#include"inadc.h"
#include"ultraSound.h"

#define T4ON T4T3M|=0x80;
#define T4OFF T4T3M&=0x7f;
#define T3ON T4T3M|=0x08;
#define T3OFF T4T3M&=0xf7;

extern un8 obstacleDistance;
extern un8 std_s_l;
extern un8 std_s_r;

void carStart(void);
void carOff(void);
#endif // !__CONTROL_H__
