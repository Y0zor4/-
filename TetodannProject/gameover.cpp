#include "Dxlib.h"	
#include "main.h"
#include "keycheck.h"
#include "gameover.h"

bool GameoverSysInit(void)
{
	bool rtnFlag = true;

	return rtnFlag;
}

void GameoverInit(void)
{

}

int GameoverScene(void)
{
	int rtn = 0;

	if (keyDownTrigger[KEY_ID_1])
	{
		rtn = 1;
	}

	GameoverDraw();

	return rtn;
}

void GameoverDraw(void)
{
	ClsDrawScreen();
	SetFontSize(50);
	DrawFormatString(0, 0, 0xFFFFFF, "GameoverScene");
	DrawBox(100, 100, 700, 500, 0x00FF00, true);
	ScreenFlip();
}