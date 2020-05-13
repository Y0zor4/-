#include "Dxlib.h"	
#include "main.h"
#include "keycheck.h"
#include "gameclear.h"

bool GameclearSysInit(void)
{
	bool rtnFlag = true;

	return rtnFlag;
}

void GameclearInit(void)
{

}

int GameclearScene(void)
{
	int rtn = 0;

	if (keyDownTrigger[KEY_ID_1])
	{
		rtn = 1;
	}

	GameclearDraw();

	return rtn;
}

void GameclearDraw(void)
{
	ClsDrawScreen();
	SetFontSize(50);
	DrawFormatString(0, 0, 0xFFFFFF, "GameclearScene");
	DrawBox(100, 100, 700, 500, 0x00FF00, true);
	ScreenFlip();
}