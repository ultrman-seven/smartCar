#include"OLED.h"
un8 line = 0;
void Delay(unsigned int time)
{
	unsigned int i, j;
	for (i = 0; i < time; i++)
		for (j = 0; j < 20000; j++)
			;
}
void Ins_trans(unsigned char command)
  {
    unsigned char counter;
	  _CS=0;
	  RS=0;
    for(counter=0;counter<8;counter++)
       {
	     SCL=0;
         SI=(command&0x80)>>7;
         command=command<<1;
	       _nop_();
		     SCL=1;
	     //  _nop_();
		     _nop_();
		     SCL=0;
        }
	RS=1;
   _CS=1;
  }
void Data_trans(unsigned char command)
  {
    unsigned char counter;
	  _CS=0;
	  RS=1;
    for(counter=0;counter<8;counter++)
       {
         SCL=0;
	     SI=(command&0x80)>>7;
		 command=command<<1;
	       _nop_();
		     SCL=1;
	      // _nop_();
		     _nop_();
		     SCL=0;
       }
	RS=1;
   _CS=1;
   }
void Column_set(unsigned char column)
          {
		     Ins_trans(0x10|(column>>4));
		     Ins_trans(0x00|(column&0x0f));
		  }
void Page_set(unsigned char page)
          {
		    Ins_trans(0xb0+page);
		  }
void Screen_FillClear(unsigned char FC)
{
	unsigned char page, column;
	for (page = 0; page < 8; page++)             //page loop
	{
		Page_set(page);
		Column_set(2);
		for (column = 0; column < 128; column++)	//column loop
			Data_trans(FC);
	}
}

void Picture_display(un8* ptr_pic, un8 colStart, un8 pageStart, un8 line, un8 col)
{
	un8 page, column;

	for (page = pageStart; page < pageStart + (line / 8); page++)        //page loop
	{
		Column_set(colStart);
		Page_set(page);

		for (column = 0; column < col; column++)	//column loop
			Data_trans(*ptr_pic++);
	}
}

void Initial()
{
//11
Ins_trans(0xAE);//--turn off oled panel

//1,2
Ins_trans(0x02);//--set low column address
Ins_trans(0x10);//--set high column address

//4
Ins_trans(0x40);//--set start line address

//12
Ins_trans(0xB0);//--set page address

//5
Ins_trans(0x81);//--set contrast control register
Ins_trans(0xFF);

//6
Ins_trans(0xA1);//--set segment re-map 127 to 0   a0:0 to seg127
//8
Ins_trans(0xA4);//--set normal display
//7
Ins_trans(0xA6);//--set indication display
//13
Ins_trans(0xC8);//--set com(N-1)to com0  c0:com0 to com(N-1)

//9
Ins_trans(0xA8);//--set multiples ratio(1to64)
Ins_trans(0x3F);//--1/64 duty

//15
Ins_trans(0xD5);//--set display clock divide ratio/oscillator frequency
Ins_trans(0x80);//--set divide ratio

//14
Ins_trans(0xD3);//--set display offset
Ins_trans(0x00);//--not offset

//10
Ins_trans(0xAD);//--DC-DC ON/OFF Mode Set
Ins_trans(0x8B);//--8A:DC-DC is disable,8B:DC-DC will be turned on when display on.(POR)

//17
Ins_trans(0xDA);//--set com pins hardware configuration
Ins_trans(0x12);

//18
Ins_trans(0xDB);//--set vcomh
Ins_trans(0x40);

//16
Ins_trans(0xD9);//--set charge period
Ins_trans(0xF1);

//11
Ins_trans(0xAF);//--turn on oled panel
}

void startCartoon(void)
{
	RES = 0;
	Delay(10);
	RES = 1;
	Initial();
	Screen_FillClear(0x00);
	Picture_display(xing, 0, 0, 64, 49);
	Delay(5);
	Screen_FillClear(0x00);
	Picture_display(bei, 49, 0, 64, 49);
	Delay(5);
	Screen_FillClear(0x00);
	Picture_display(dfd_a, 0, 1, 40, 30);
	Picture_display(dfd_b, 30, 1, 40, 30);
	Picture_display(dfd_c, 60, 1, 40, 30);
	Picture_display(dfd_d, 90, 1, 40, 30);
	Delay(10);
	Screen_FillClear(0xff);
	Screen_FillClear(0x00);
	Picture_display(zjy_a, 0, 1, 40, 10);
	Picture_display(zjy_b, 10, 1, 40, 24);
	Picture_display(zjy_c, 34, 1, 40, 24);
	Picture_display(zjy_d, 58, 1, 40, 24);
	Picture_display(zjy_e, 82, 1, 40, 10);
	Delay(10);
	Screen_FillClear(0xff);
	Screen_FillClear(0x00);
}

void OLED_print(char* str)
{
	un8 count = 0;
	while (*str)
	{
		switch (*str)
		{
		case '\n':
			line += asciiHigh / 8;
			count = -1;
			break;
		case '\b':
			count--;
			break;
		case 127:
			break;
		default:
			if (*str >= 32)
				Picture_display(ASCII[*str - 32], 1 + count * asciiWide + count, line, asciiHigh, asciiWide);
			break;
		}
		count++;
		str++;
	}
}