#ifndef __OLEDIO_H__
#define __OLEDIO_H__
#include"OLED.h"

extern un8 chooseLine;

void startCartoon(void);
void OLED_print(char* str);
void OLED_putchar(char ch);
void OLED_putNumber(un16 num);
void screenClear(void);
#endif // !__OLEDIO_H__
