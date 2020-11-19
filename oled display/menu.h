#ifndef __MEUN_H__
#define __MENU_H__
#include"oledio.h"
struct menuData
{
	char* str;
	un16 value;
};
typedef struct menuData menu;

void displayMenu(void);
void keyOperation(void);
void menuInitial(void);
#endif // !__MEUN_H__
