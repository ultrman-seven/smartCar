#ifndef __OLED_H__
#define __OLED_H__
#include"common.h"
#include"font.h"
#define HEIGHT 64
#define WIDE 69

#define REVERSE Ins_trans(0xA7);
sbit _CS = P1 ^ 6;
sbit RES = P1 ^ 5;
sbit RS = P3 ^ 0;
sbit SCL = P1 ^ 3;//serial clock input
sbit SI = P1 ^ 4;//serial data input

void Initial(void);
void Picture_display(un8* ptr_pic, un8 colStart, un8 pageStart, un8 line, un8 col);
void PictureContrastDisplay(un8* ptr_pic, un8 colStart, un8 pageStart, un8 line, un8 col);
void Screen_FillClear(unsigned char FC);
void Page_set(unsigned char page);
void Column_set(unsigned char column);
void Data_trans(unsigned char command);
void Ins_trans(unsigned char command);
#endif // !__OLED__H__
