#ifndef __FIVEKEYS_H__
#define __FIVEKEYS_H__
#include"common.h"

sbit key_up = P2 ^ 4;
sbit key_down = P2 ^ 3;
sbit key_left = P2 ^ 1;
sbit key_right = P3 ^ 6;
sbit key_mid = P3 ^ 7;
#define NO_HaveKeyBeenPressed (key_down && key_up && key_mid && key_left && key_right)
#endif // !__FIVEKEYS_H__
