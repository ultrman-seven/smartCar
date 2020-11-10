#include"menu.h"
#include"fivekeys.h"
#define MENU_NUM 3
#define TEST 3
#define MODIFY 4
un8 chooseLine = 0;
menu project[MENU_NUM] = { {"car state\n",0},{"model test\n",0},{"parameter modify\n",0} };
menu test[TEST] = { {"ultra sound\n",0},{"inductance adc\n",0},{"speed control\n",0} };
menu modify[MODIFY] = { {"",0},{"",0},{"",0} ,{"press 'mid'\nto return back\n",0} };
//��ʾֻ�п�/��״̬�Ĳ˵�
void displayStateMenu(un8 num, menu* men)
{
	un8 count;
	for (count = 0; count < num; count++)
		OLED_print(men[count].str);
}
//��ʾ����ֵ�Ĳ˵�
void displayValueMenu(un8 num, menu* men)
{
	un8 count;
	for (count = 0; count < num; count++)
	{
		OLED_print(men[count].str);
		OLED_print("----<");
		OLED_putNumber(men[count].value);
		OLED_print(">\n");
	}
}
//�Բ˵���Ŀ���п��ز���
void keyChooseState(un8 num,menu* pro)
{
	if ((!key_up) && chooseLine > 0)
		chooseLine--;
	if ((!key_down) && chooseLine < 1)
		chooseLine++;
	if (!(key_left && key_right))
		pro[chooseLine].value = !pro[chooseLine].value;
	screenClear();
	displayStateMenu(num, pro);
}
//�Բ˵���ֵ���е�������
void keyChangeValue(un8 num, menu* pro)
{
	if ((!key_up) && chooseLine > 0)
		chooseLine--;
	if ((!key_down) && chooseLine < 1)
		chooseLine++;
	if (!key_left)
		pro[chooseLine].value--;
	if (!key_right)
		pro[chooseLine].value++;
	screenClear();
	displayValueMenu(num, pro);
}
//��ʾһ���˵�
void displayMenu(void)
{
	displayStuctMenu(MENU_NUM, project);
}
//�ԡ����ܲ��ԡ��˵����а�������
void testMenu(void)
{
	un8 count;
	screenClear();
	displayStateMenu(TEST, testMenu);
	if (HAVE_KEY_BEEN_PRESSED)
	{
		keyChooseState(TEST, test);
	}
}
//�ԡ������������˵����а�������
void modifyMenu(void)
{
	screenClear();
	displayValueMenu(MODIFY, modify);
	if (HAVE_KEY_BEEN_PRESSED)
	{
		keyChangeValue(MODIFY, modify);
	}
}

//main������һ����������
void keyOperation(void)
{
	un8 count;
	if (HAVE_KEY_BEEN_PRESSED)
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
					OLED_print("smart car test\n\n\n(press 'mid' to\nreturn back)");
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