#ifndef __ULTRASOUND_H__
#define __ULTRASOUND_H__
#include"common.h"

sbit trig = P0 ^ 5;
sbit echo = P3 ^ 2;

void UlSoundInitinal(void);
un16 ULsound_diatance(void);

#endif // !__ULTRASOUND_H__
