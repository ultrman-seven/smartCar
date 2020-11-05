#ifndef __FIVEKEYS_H__
#define __FIVEKEYS_H__
#include"common.h"

sbit key_up = P0 ^ 0;
sbit key_down = P0 ^ 1;
sbit key_left = P0 ^ 2;
sbit key_right = P0 ^ 3;
sbit key_mid = P0 ^ 4;
#endif // !__FIVEKEYS_H__
