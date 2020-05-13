#include "Dxlib.h"	
#include "main.h"
#include "keycheck.h"
#include "game.h"

bool GameSysInit(void)
{
	bool rtnFlag = true;

	return rtnFlag;
}

void GameInit(void)
{

}

int GameScene(void)
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
	else if (keyDownTrigger[KEY_ID_3])
	{
		rtn = 3;
	}
	else if (keyDownTrigger[KEY_ID_4])
	{
		rtn = 4;
	}

	GameDraw();

	return rtn;
}

void GameDraw(void)
{
	ClsDrawScreen();
	SetFontSize(50);
	DrawFormatString(0, 0, 0xFFFFFF, "GameScene");
	DrawBox(100, 100, 700, 500, 0x00FF00, true);
	ScreenFlip();
}