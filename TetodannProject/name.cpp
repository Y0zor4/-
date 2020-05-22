#include "Dxlib.h"	
#include <string.h>
#include "main.h"
#include "keycheck.h"
#include "name.h"

char name[256];
char letter[8][26];

bool nameFlag;


bool NameSysInit(void)
{
	bool rtnFlag = true;

	strcpy_s(letter[0], 8, "A");
	strcpy_s(letter[1], 8, "B");
	strcpy_s(letter[2], 8, "C");
	strcpy_s(letter[3], 8, "D");

	return rtnFlag;
}


void NameInit(void)
{
	strcpy_s(name, 256, "");

	nameFlag = false;
}

int NameScene(void)
{
	int rtn = 0;

	if (keyDownTrigger[KEY_ID_1])
	{
		rtn = 1;
	}

	if (keyDownTrigger[KEY_ID_ENTER])
	{
		nameFlag = true;
	}

	if (nameFlag)
	{
		strcpy_s(name, 256, "");
		strcat_s(name, 256, letter[0]);
		strcat_s(name, 256, letter[1]);
		strcat_s(name, 256, letter[2]);
		strcat_s(name, 256, letter[3]);
		nameFlag = false;
	}
	

	NameDraw();

	return rtn;
}

void NameDraw(void)
{
	ClsDrawScreen();
	SetFontSize(50);
	DrawFormatString(0, 0, 0xFFFFFF, "NameScene");
	DrawBox(100, 100, 700, 500, 0x00FF00, true);
	DrawFormatString(500, 500, 0xFFFFFF, "%s", name);
	ScreenFlip();
}


char GetName(void)
{
	return name[0];
}