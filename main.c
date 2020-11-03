#include"common.h"
#include"OLED.h"
void IOinitinial(void)
{
	P0M0 = P1M0 = P2M0 = P3M0 = P4M0 = 0xff;
	P0M1 = P1M1 = P2M1 = P3M1 = P4M1 = 0x00;
	P0PU = P1PU = P2PU = P3PU = P4PU = 0xff;
}
void main()
{
	IOinitinial();
	startCartoon();
	OLED_print("kxjNB!!\nrmd nbDyp");
	while (1);
}