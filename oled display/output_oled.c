#include"oledio.h"
un8 line = 0;
char wordCount = 0;

void startCartoon(void)
{
	RES = 0;
	delay(2);
	RES = 1;
	_nop_();
	_nop_();
	Initial();
	Screen_FillClear(0x00);
	Picture_display(xin, 0, 0, 64, 49);
	delay(500);
	Screen_FillClear(0x00);
	Picture_display(bei, 49, 0, 64, 49);
	delay(500);
	Screen_FillClear(0x00);
	Picture_display(dfd1, 0, 1, 40, 30);
	Picture_display(dfd2, 30, 1, 40, 30);
	Picture_display(dfd3, 60, 1, 40, 30);
	Picture_display(dfd4, 90, 1, 40, 30);
	delay(700);
	Screen_FillClear(0xff);
	Screen_FillClear(0x00);
	Picture_display(zjy1, 0, 1, 40, 10);
	Picture_display(zjy2, 10, 1, 40, 24);
	Picture_display(zjy3, 34, 1, 40, 24);
	Picture_display(zjy4, 58, 1, 40, 24);
	Picture_display(zjy5, 82, 1, 40, 10);
	delay(800);
	Screen_FillClear(0xff);
	Screen_FillClear(0x00);
}

void screenClear(void)
{
	Screen_FillClear(0x00);
	line = wordCount = 0;
}

void OLED_putchar(char ch)
{
	if (wordCount >= 16)
	{
		wordCount = 0;
		line += asciiHigh / 8;
	}

	switch (ch)
	{
	case '\n':
		line += asciiHigh / 8;
		wordCount = -1;
		break;
	case '\b':
		wordCount--;
		break;
	case 127:
		break;
	default:
		if (ch >= 32)
			Picture_display(ASCII[ch - 32], 1 + wordCount * asciiWide, line, asciiHigh, asciiWide);
		break;
	}
	wordCount++;
}

void OLED_putContrastChar(char ch)
{
	if (wordCount >= 16)
	{
		wordCount = 0;
		line += asciiHigh / 8;
	}

	switch (ch)
	{
	case '\n':
		line += asciiHigh / 8;
		wordCount = -1;
		break;
	case '\b':
		wordCount--;
		break;
	case 127:
		break;
	default:
		if (ch >= 32)
			PictureContrastDisplay(ASCII[ch - 32], 1 + wordCount * asciiWide, line, asciiHigh, asciiWide);
		break;
	}
	wordCount++;
}

void OLED_putNumber(un16 num)
{
	un16 count;
	for (count = 10000; num / count == 0; num %= count, count /= 10)
		;
	while (count>=1)
	{
		OLED_putchar(num / count + '0');
		num %= count;
		count /= 10;
	}
}

void OLED_print(char* str)
{
	if (chooseLine == line)
		while (*str)
			OLED_putContrastChar(*str++);
	else
		while (*str)
			OLED_putchar(*str++);
}