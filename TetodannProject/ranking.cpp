#include "Dxlib.h"	
#include "main.h"
#include "keycheck.h"
#include "ranking.h"

bool RankingSysInit(void)
{
	bool rtnFlag = true;

	return rtnFlag;
}

void RankingInit(void)
{

}

int RankingScene(void)
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

	RankingDraw();

	return rtn;
}

void RankingDraw(void)
{
	ClsDrawScreen();
	SetFontSize(50);
	DrawFormatString(0, 0, 0xFFFFFF, "RankingScene");
	DrawBox(100, 100, 700, 500, 0x00FF00, true);
	ScreenFlip();
}