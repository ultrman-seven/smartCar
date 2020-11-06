#ifndef __OLED_H__
#define __OLED_H__
#include"common.h"
#include"font.h"
#define HEIGHT 64
#define WIDE 69

#define REVERSE Ins_trans(0xA7);
sbit _CS = P5 ^ 0;
sbit RES = P3 ^ 2;
sbit RS = P3 ^ 0;
sbit SCL = P1 ^ 3;//serial clock input
sbit SI = P1 ^ 4;//serial data input

void Ins_trans(unsigned char command);
void Initial(void);
void startCartoon(void);
void OLED_print(char* str);
#endif // !__OLED__H__
