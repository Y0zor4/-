#include "Dxlib.h"	
#include "main.h"
#include "keycheck.h"
#include "background.h"

int bgImageTmp;
int wallImageTmp;;
int bgPosY;
int bgPosX;
bool moveBgFlag;



bool BackgroundSysInit(void)
{
	bool rtnFlag = true;
	bgImageTmp = LoadGraph("image/bg_tmp.png");
	wallImageTmp = LoadGraph("image/wall_tmp.png");
	return rtnFlag;
}



void BackgroundInit(void)
{
	bgPosX = 712 + BG_CENTER_X;
	bgPosY = 176 + BG_CENTER_Y;
	moveBgFlag = true;
}



void BackgroundCtl(int floor, bool flag)
{
	if (!flag) return;
	if (moveBgFlag)
	{
		if (bgPosY > BG_CENTER_Y + 161)
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
		if (bgPosY < BG_CENTER_Y + 191)
		{
			bgPosY += 1;
		}
		else
		{
			moveBgFlag = true;
		}
	}

}



void BackgroundDraw(int floor)
{

	DrawBox(0, 0, 1600, 900, 0x512700, true);

	// L1
	DrawModiGraph(bgPosX - 432,
		bgPosY - 290,
		bgPosX - 282,
		bgPosY - 189,
		bgPosX - 282,
		bgPosY + 189,
		bgPosX - 432,
		bgPosY + 290,
		wallImageTmp, true);

	// L2
	DrawModiGraph(bgPosX - 282,
		bgPosY - 189,
		bgPosX - 205,
		bgPosY - 137,
		bgPosX - 205,
		bgPosY + 137,
		bgPosX - 282,
		bgPosY + 189,
		wallImageTmp, true);

	// L3
	DrawModiGraph(bgPosX - 205,
		bgPosY - 137,
		bgPosX - 161,
		bgPosY - 108,
		bgPosX - 161,
		bgPosY + 108,
		bgPosX - 205,
		bgPosY + 137,
		wallImageTmp, true);


	DrawBox(bgPosX - 130, bgPosY - 87, bgPosX + 130, bgPosY + 87, 0x000000, true);


	// R1
	//DrawModiGraph(bgPosX,
	//	bgPosY,
	//	bgPosX + 432,
	//	bgPosY - 290,
	//	bgPosX + 432,
	//	bgPosY + 290,
	//	bgPosX,
	//	bgPosY,
	//	wallImageTmp, true);

	DrawLine(bgPosX - 432, bgPosY - 290, bgPosX, bgPosY, 0x000000);
	DrawLine(bgPosX - 432, bgPosY + 290, bgPosX, bgPosY, 0x000000);
	DrawLine(bgPosX + 432, bgPosY - 290, bgPosX, bgPosY, 0x000000);
	DrawLine(bgPosX + 432, bgPosY + 290, bgPosX, bgPosY, 0x000000);


	 DrawGraph(bgPosX - 432, bgPosY - 350, bgImageTmp, true);
}