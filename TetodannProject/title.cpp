#include "Dxlib.h"	
#include "main.h"
#include "keycheck.h"
#include "title.h"

bool TitleSysInit(void)
{
	bool rtnFlag = true;

	return rtnFlag;
}

void TitleInit(void)
{

}

int TitleScene(void)
{
	int rtn = 0;

	if (keyDownTrigger[KEY_ID_1])
	{
		rtn = 1;
	}

	TitleDraw();

	return rtn;
}

void TitleDraw(void)
{
	ClsDrawScreen();
	SetFontSize(50);
	DrawFormatString(0, 0, 0xFFFFFF, "TitleScene");
	DrawBox(100, 100, 700, 500, 0x00FF00, true);
	ScreenFlip();
}