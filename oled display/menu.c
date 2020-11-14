#include"menu.h"
#include"fivekeys.h"
#include"control.h"
#define MENU_NUM 3
#define TEST 3
#define MODIFY 6
un8 chooseLine = 0;
menu project[MENU_NUM] = { {"car start\n",0},{"model test\n",0},{"parameter modify\n",0} };
menu test[TEST] = { {"ultra sound\n",0},{"inductance adc\n",0},{"speed control\n",0} };
menu modify[MODIFY] = { {"obstacle distance",0},{"std_s_l",0},{"std_s_r",0} ,{"round speed",0},{"round time",0}, {"stright time",0} };
//显示只有开/关状态的菜单
void displayStateMenu(un8 num, menu* men)
{
	un8 count;
	for (count = 0; count < num; count++)
		OLED_print(men[count].str);
}
//显示有数值的菜单
void displayValueMenu(un8 num, menu* men)
{
	un8 count;
	for (count = 0; count < num; count++)
	{
		OLED_print(men[count].str);
		OLED_print("\n----<");
		OLED_putNumber(men[count].value);
		OLED_print(">\n");
	}
	OLED_print("press mid to return back");
}
//对菜单项目进行开关操作
void keyChooseState(un8 num,menu* pro)
{
	un8 maxWait = 20;
	if ((!key_up) && chooseLine > 0)
		chooseLine -= 2;
	if (!key_down)
		chooseLine += 2;
	if (!(key_left && key_right))
		pro[chooseLine].value = !pro[chooseLine].value;
	screenClear();
	displayStateMenu(num, pro);
	while (maxWait-- && !NO_HaveKeyBeenPressed)
		delay(100);
}
//对菜单数值进行调整操作
void keyChangeValue(un8 num, menu* pro)
{
	un8 maxWait = 20;
	if ((!key_up) && chooseLine > 0)
		chooseLine -= 2;
	if ((!key_down) && chooseLine < 1)
		chooseLine += 2;
	if (!key_left)
		pro[chooseLine].value--;
	if (!key_right)
		pro[chooseLine].value++;
	screenClear();
	displayValueMenu(num, pro);
	while (maxWait-- && !NO_HaveKeyBeenPressed)
		delay(100);
}
//显示一级菜单
void displayMenu(void)
{
	displayStateMenu(MENU_NUM, project);
}
//对“功能测试”菜单进行按键操作
void testMenu(void)
{
	un8 count;
	screenClear();
	displayStateMenu(TEST, test);
	while(key_mid)
		if (!NO_HaveKeyBeenPressed)
		{
			while (NO_HaveKeyBeenPressed);
			keyChooseState(TEST, test);
			for (count = 0; count < TEST; count++)
			{
				if (test[count].value)
					switch (count)
					{
					case 0:
						screenClear();
						OLED_print("obstacle distance\nis <");
						OLED_putNumber(ULsound_diatance());
						OLED_print(">\npress 'mid' to\nreturn back");
						while (key_mid)
							;
						screenClear();
						displayStateMenu(TEST, test);
						break;
					case 1:
						screenClear();
						OLED_print("press 'left' to show left induced voltage value, so the left\npress 'mid' to back");
						while (key_mid)
							if (!key_left)
							{
								screenClear();
								OLED_print("left induced voltage value is <");
								OLED_putNumber(adcMeasure(LEFTindc));
								OLED_putchar('>');
							}
							else
								if (!key_right)
								{
									screenClear();
									OLED_print("right induced voltage value is <");
									OLED_putNumber(adcMeasure(RIGHTindc));
									OLED_putchar('>');
								}
						screenClear();
						displayStateMenu(TEST, test);
						break;
					case 2:
						break;
					default:
						break;
					}
				test[count].value = 0;
			}
		}
}
//对“参数调整”菜单进行按键操作
void modifyMenu(void)
{
	screenClear();
	displayValueMenu(MODIFY, modify);
	while(key_mid)
		if (!NO_HaveKeyBeenPressed)
		{
			keyChangeValue(MODIFY, modify);
			displayValueMenu(MODIFY - chooseLine, modify + chooseLine);
		}
}

//main函数里 一级按键操作
void keyOperation(void)
{
	un8 count;
	if (!NO_HaveKeyBeenPressed)
	{
		keyChooseState(MENU_NUM,project);
		for (count = 0; count < MENU_NUM; count++)
			if (project[count].value)
			{
				chooseLine = 0;
				switch (count)
				{

				case 0:
					screenClear();
					OLED_print("smart car test\n(press 'mid' to\nreturn back)");
					carStart();
					while (key_mid)
						;
					carOff();
					break;
				case 1:
					testMenu();
					break;
				case 2:
					while (key_mid)
						modifyMenu();
					break;
				default:
					break;
				}
			}
			project[count].value = 0;
		}
}

void menuInitial(void)
{
	modify[0].value = obstacleDistance;
	modify[1].value = std_s_l;
	modify[2].value = std_s_r;
	modify[3].value = roundSpeed;
	modify[4].value = roundSpeed;
	modify[5].value = straightTime;
}