#include"inadc.h"

un16 adcValue = 0;

un16 adcMeasure(un8 select)
{
	//时序
	P_SW2 |= 0x80;
	ADCTIM = 0x3f;
	P_SW2 &= 0x7f;

	//右对齐，系统时钟/2/16
	ADCCFG = 0xff; 
	//使能(同时ADC_FLAG=0)
	ADC_CONTR = select == LEFTindc ? 0x80 : 0x81;

	EADC = 1;//允许adc中断
	ADC_CONTR |= 0x40;//start
	_nop_();
	_nop_();
	while (ADC_CONTR & 0x40)
		;
	return adcValue;
}

void adc_interrupt(void) interrupt 5
{
	adcValue = 0;
	ADC_CONTR &= 0xdf;
	adcValue = ADC_RES;
	adcValue <<= 8;
	adcValue |= ADC_RESL;
}