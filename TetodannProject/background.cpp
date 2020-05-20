#include "Dxlib.h"	
#include "main.h"
#include "keycheck.h"
#include "background.h"

int bgImageTmp;
int bgPosY;
bool moveBgFlag;

bool BackgroundSysInit(void)
{
	bool rtnFlag = true;
	bgImageTmp = LoadGraph("image/bg_tmp.png");
	return rtnFlag;
}

void BackgroundInit(void)
{
	bgPosY = OFFSET_Y;
	moveBgFlag = true;
}

void BackgroundCtl(int floor)
{

}

void BackgroundDraw(int floor)
{
	// Žb’è“I‚ÉDraw‚Ì’†‚É‘‚­
	if (moveBgFlag)
	{
		if (bgPosY > OFFSET_Y - 15)
		{
			bgPosY -= 1;
		}
		else
		{
			moveBgFlag = false;
		}
	}
	else
	{
		if (bgPosY < OFFSET_Y + 15)
		{
			bgPosY += 1;
		}
		else
		{
			moveBgFlag = true;
		}
	}

	DrawBox(OFFSET_X, OFFSET_Y, BG_SIZE_X + OFFSET_X, BG_SIZE_Y + OFFSET_Y, 0x000000, true);
	DrawGraph(OFFSET_X, bgPosY, bgImageTmp, true);
}