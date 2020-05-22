#include "Dxlib.h"	
#include "main.h"
#include "keycheck.h"
#include "select.h"
#include "fade.h"

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

	// rtn = 1:ゲームシーンへ　rtn = 2:タイトルシーンへ
	if (keyDownTrigger[KEY_ID_SPACE])
	{
		fadeout = true;
		
		rtn = 1;
	}
	else if (keyDownTrigger[KEY_ID_ENTER])
	{
		rtn = 2;
	}
	

	SelectDraw();

	return rtn;
}

void SelectDraw(void)
{
	ClsDrawScreen();
	SetFontSize(25);
	DrawFormatString(1400, 850, 0xFFFFFF, "Back To Title");
	DrawFormatString(1400, 875, 0xFFFFFF, "Push to ENTER");
	SetFontSize(50);
	DrawFormatString(0, 0, 0xFFFFFF, "SelectScene");
	DrawFormatString(650, 450, 0xFFFFFF, "GameStart");
	DrawFormatString(600, 500, 0xFFFFFF, "Push to SPACE");
	ScreenFlip();
}