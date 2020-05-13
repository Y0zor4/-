#include "Dxlib.h"	
#include "main.h"
#include "keycheck.h"
#include "name.h"

bool NameSysInit(void)
{
	bool rtnFlag = true;

	return rtnFlag;
}

void NameInit(void)
{

}

int NameScene(void)
{
	int rtn = 0;

	if (keyDownTrigger[KEY_ID_1])
	{
		rtn = 1;
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
	ScreenFlip();
}