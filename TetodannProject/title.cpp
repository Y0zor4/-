#include "Dxlib.h"	
#include "main.h"
#include "keycheck.h"
#include "title.h"

int titleLogo;
int teamLogo;
int logoCnt;
int bringCnt;


bool TitleSysInit(void)
{
	bool rtnFlag = true;

	titleLogo = LoadGraph("image/title_logo.png");

	teamLogo = LoadGraph("image/team_logo.png");

	logoCnt = 0;
	bringCnt = 0;

	return rtnFlag;
}

void TitleInit(void)
{

}

int TitleScene(void)
{
	int rtn = 0;

	if (keyDownTrigger[KEY_ID_SPACE])
	{
		if (logoCnt < LOGO_CNT_MAX)
		{
			logoCnt = LOGO_CNT_MAX;
		}
		else
		{
			rtn = 1;
		}
	}

	if (logoCnt < LOGO_CNT_MAX)
	{
		logoCnt++;
	}
	else
	{
		bringCnt++;
	}

	TitleDraw();

	return rtn;
}

void TitleDraw(void)
{
	ClsDrawScreen();

	if (logoCnt < LOGO_CNT_MAX + 255)
	{
		DrawGraph(0, 0, teamLogo, true);
	}
	else
	{
		DrawGraph(0, 0, titleLogo, true);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, bringCnt);
		DrawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, 0x000000, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}


	ScreenFlip();
}