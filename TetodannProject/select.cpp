#include "Dxlib.h"	
#include "main.h"
#include "keycheck.h"
#include "select.h"

bool SelectSysInit(void)
{
	bool rtnFlag = true;

	return rtnFlag;
}

void SelectInit(void)
{

}

int SelectScene(void)
{
	int rtn = 0;

	if (keyDownTrigger[KEY_ID_1])
	{
		rtn = 1;
	}
	else if (keyDownTrigger[KEY_ID_2])
	{
		rtn = 2;
	}

	SelectDraw();

	return rtn;
}

void SelectDraw(void)
{
	ClsDrawScreen();
	SetFontSize(50);
	DrawFormatString(0, 0, 0xFFFFFF, "SelectScene");
	DrawBox(100, 100, 700, 500, 0x00FF00, true);
	ScreenFlip();
}