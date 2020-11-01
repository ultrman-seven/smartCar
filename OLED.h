#ifndef __OLED_H__
#define __OLED_H__
#include"common.h"
#include"font.h"
#define HEIGHT 64
#define WIDE 69

#define REVERSE Ins_trans(0xA7);
sbit _CS = P0 ^ 4;
sbit RES = P0 ^ 2;
sbit RS = P0 ^ 3;
sbit SCL = P0 ^ 0;//serial clock input
sbit SI = P0 ^ 1;//serial data input

void Ins_trans(unsigned char command);
void Initial(void);
void startCartoon(void);
void OLED_print(char* str);
#endif // !__OLED__H__
