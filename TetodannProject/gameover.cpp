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

	if (keyDownTrigger[KEY_ID_SPACE])
	{
		rtn = 1;
	}

	GameoverDraw();

	return rtn;
}

void GameoverDraw(void)
{
	ClsDrawScreen();
	SetFontSize(150);
	DrawFormatString(450, 300, 0x00FF00, "(TÉ T)");
	DrawFormatString(450, 450, 0xFF0000, "GameOver");
	SetFontSize(50);
	DrawFormatString(0, 0, 0xFFFFFF, "GameoverScene");
	ScreenFlip();
}