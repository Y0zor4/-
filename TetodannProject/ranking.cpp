#include "Dxlib.h"	
#include "main.h"
#include "keycheck.h"
#include "ranking.h"

RANKING ranking[20];
int rankingPosY;
int keyCnt;
int scrollSpeed;

bool RankingSysInit(void)
{
	bool rtnFlag = true;

	// É¿î≈âºèàóù
	for (int i = 0; i < 20; i++)
	{
		strcpy_s(ranking[i].name_r, 256, "");
		ranking[i].floor_r = 0;
		ranking[i].posY = 300 + i * 100;
	}

	return rtnFlag;
}

void RankingInit(void)
{
	// ñºëOÇ∆Ã€±Ç≈◊›∑›∏ﬁçÏê¨
	int tmp = -1;
	for (int i = 0; i < 20; i++)
	{
		if (ranking[i].floor_r < floor_main)
		{
			tmp = i;
			break;
		}
	}

	if (tmp != -1)
	{
		for (int i = 20 - 1; i > tmp - 1; i--)
		{
			ranking[i].floor_r = ranking[i - 1].floor_r;
			strcpy_s(ranking[i].name_r, 256, ranking[i - 1].name_r);
		}
		ranking[tmp].floor_r = floor_main;
		strcpy_s(ranking[tmp].name_r, 256, name);
	}

	rankingPosY = 0;
	keyCnt = 0;
	scrollSpeed = 7;
}

int RankingScene(void)
{
	int rtn = 0;

	if (keyDownTrigger[KEY_ID_SPACE])
	{
		rtn = 1;
	}
	else if (keyDownTrigger[KEY_ID_ENTER])
	{
		rtn = 2;
	}

	// Ω∏€∞Ÿ
	if (keyNew[KEY_ID_UP] && rankingPosY < 0)
	{
		rankingPosY += scrollSpeed;
		keyCnt++;
		if (rankingPosY > 0) rankingPosY = 0;
	}
	else if (keyNew[KEY_ID_DOWN] && rankingPosY > -20 * 100)
	{
		rankingPosY -= scrollSpeed;
		keyCnt++;
		if (rankingPosY < -20 * 100) rankingPosY = -20 * 100;
	}

	if (!keyNew[KEY_ID_UP] && !keyNew[KEY_ID_DOWN])
	{
		scrollSpeed = 7;
		keyCnt = 0;
	}
	if (keyCnt > 120)
	{
		scrollSpeed = 20;
	}


	RankingDraw();

	return rtn;
}

void RankingDraw(void)
{
	ClsDrawScreen();
	
	SetFontSize(50);
	for (int i = 0; i < 20; i++)
	{
		DrawFormatString(200, ranking[i].posY + rankingPosY, 0xFFFFFF, "%d.", i + 1);
		DrawFormatString(300, ranking[i].posY + rankingPosY, 0xFFFFFF, "%s", ranking[i].name_r);
		DrawFormatString(700, ranking[i].posY + rankingPosY, 0xFFFFFF, "%d", ranking[i].floor_r);
	}


	SetFontSize(150);
	DrawBox(0, 0, SCREEN_SIZE_X, 200, 0x000000, true);
	DrawFormatString(100, 20, 0xFFFFFF, "RANKING");


	ScreenFlip();
}