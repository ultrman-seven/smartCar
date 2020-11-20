#include"inadc.h"

un16 adcValue = 0;

un16 adcMeasure(un8 select)
{
	//ʱ��
	P_SW2 |= 0x80;
	ADCTIM = 0x3f;
	P_SW2 &= 0x7f;

	//�Ҷ��룬ϵͳʱ��/2/16
	ADCCFG = 0xff; 
	//ʹ��(ͬʱADC_FLAG=0)
	ADC_CONTR = select == LEFTindc ? 0x80 : 0x81;

	EADC = 1;//����adc�ж�
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