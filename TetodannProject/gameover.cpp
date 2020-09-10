#include "Dxlib.h"	
#include "main.h"
#include "keycheck.h"
#include "gameover.h"


int gameoverImage;

bool GameoverSysInit(void)
{
	bool rtnFlag = true;

	return rtnFlag;
}

void GameoverInit(void)
{
	gameoverImage = LoadGraph("Image/gameover.jpeg");
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
	//SetFontSize(150);
	//DrawFormatString(450, 300, 0x00FF00, "(TÉ T)");
	//DrawFormatString(450, 450, 0xFF0000, "GameOver");
	SetFontSize(50);
	DrawFormatString(600, 750, 0xFFFFFF, "Push To SPACE");
	DrawGraph(520, 250, gameoverImage, true);
	ScreenFlip();
}