#include "Dxlib.h"	
#include "main.h"
#include "keycheck.h"
#include "background.h"


struct BGPOS
{
	float x[4];
	float y[4];
};

int bgImageTmp;
int wallImage;
int bgPosY;
int bgPosX;
bool moveBgFlag;

BGPOS ConstBgLPos[7];
BGPOS ConstBgRPos[7];

BGPOS bgLPos[6];
BGPOS bgRPos[6];

int scrollCnt;

bool BackgroundSysInit(void)
{
	bool rtnFlag = true;
	bgImageTmp = LoadGraph("image/bg_tmp.png");
	wallImage = LoadGraph("image/wall.png");

	ConstBgLPos[0].x[0] = (BG_POS_X - 496);
	ConstBgLPos[0].y[0] = (BG_POS_Y - 273);
	ConstBgLPos[0].x[1] = (BG_POS_X - 496);
	ConstBgLPos[0].y[1] = (BG_POS_Y + 1071);
	ConstBgLPos[0].x[2] = (BG_POS_X);
	ConstBgLPos[0].y[2] = (BG_POS_Y + 60);
	ConstBgLPos[0].x[3] = (BG_POS_X);
	ConstBgLPos[0].y[3] = (BG_POS_Y + 690);


	ConstBgLPos[1].x[0] = (BG_POS_X);
	ConstBgLPos[1].y[0] = (BG_POS_Y + 60);
	ConstBgLPos[1].x[1] = (BG_POS_X);
	ConstBgLPos[1].y[1] = (BG_POS_Y + 690);
	ConstBgLPos[1].x[2] = (BG_POS_X + 150);
	ConstBgLPos[1].y[2] = (BG_POS_Y + 161);
	ConstBgLPos[1].x[3] = (BG_POS_X + 150);
	ConstBgLPos[1].y[3] = (BG_POS_Y + 571);


	ConstBgLPos[2].x[0] = (BG_POS_X + 150);
	ConstBgLPos[2].y[0] = (BG_POS_Y + 161);
	ConstBgLPos[2].x[1] = (BG_POS_X + 150);
	ConstBgLPos[2].y[1] = (BG_POS_Y + 571);
	ConstBgLPos[2].x[2] = (BG_POS_X + 227);
	ConstBgLPos[2].y[2] = (BG_POS_Y + 212);
	ConstBgLPos[2].x[3] = (BG_POS_X + 227);
	ConstBgLPos[2].y[3] = (BG_POS_Y + 511);


	ConstBgLPos[3].x[0] = (BG_POS_X + 227);
	ConstBgLPos[3].y[0] = (BG_POS_Y + 212);
	ConstBgLPos[3].x[1] = (BG_POS_X + 227);
	ConstBgLPos[3].y[1] = (BG_POS_Y + 511);
	ConstBgLPos[3].x[2] = (BG_POS_X + 271);
	ConstBgLPos[3].y[2] = (BG_POS_Y + 242);
	ConstBgLPos[3].x[3] = (BG_POS_X + 271);
	ConstBgLPos[3].y[3] = (BG_POS_Y + 476);


	ConstBgLPos[4].x[0] = (BG_POS_X + 271);
	ConstBgLPos[4].y[0] = (BG_POS_Y + 242);
	ConstBgLPos[4].x[1] = (BG_POS_X + 271);
	ConstBgLPos[4].y[1] = (BG_POS_Y + 476);
	ConstBgLPos[4].x[2] = (BG_POS_X + 294);
	ConstBgLPos[4].y[2] = (BG_POS_Y + 257);
	ConstBgLPos[4].x[3] = (BG_POS_X + 294);
	ConstBgLPos[4].y[3] = (BG_POS_Y + 458);


	ConstBgLPos[5].x[0] = (BG_POS_X + 294);
	ConstBgLPos[5].y[0] = (BG_POS_Y + 257);
	ConstBgLPos[5].x[1] = (BG_POS_X + 294);
	ConstBgLPos[5].y[1] = (BG_POS_Y + 458);
	ConstBgLPos[5].x[2] = (BG_POS_X + 309);
	ConstBgLPos[5].y[2] = (BG_POS_Y + 267);
	ConstBgLPos[5].x[3] = (BG_POS_X + 309);
	ConstBgLPos[5].y[3] = (BG_POS_Y + 447);


	ConstBgLPos[6].x[0] = (BG_POS_X + 309);
	ConstBgLPos[6].y[0] = (BG_POS_Y + 267);
	ConstBgLPos[6].x[1] = (BG_POS_X + 309);
	ConstBgLPos[6].y[1] = (BG_POS_Y + 447);
	ConstBgLPos[6].x[2] = (BG_POS_X + 320);
	ConstBgLPos[6].y[2] = (BG_POS_Y + 275);
	ConstBgLPos[6].x[3] = (BG_POS_X + 320);
	ConstBgLPos[6].y[3] = (BG_POS_Y + 438);

	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			ConstBgRPos[i].y[j] = ConstBgLPos[i].y[j];
			ConstBgRPos[i].x[j] = (BG_POS_X + BG_CENTER_X) + ((BG_POS_X + BG_CENTER_X) - ConstBgLPos[i].x[j]);
		}
	}

	return rtnFlag;
}



void BackgroundInit(void)
{
	bgPosX = 0;
	bgPosY = 0;
	moveBgFlag = true;
	for (int i = 0; i < 6; i++)
	{
		bgLPos[i] = ConstBgLPos[i + 1];
		bgRPos[i] = ConstBgRPos[i + 1];
	}

	scrollCnt = 0;
}



void BackgroundCtl(int floor, bool flag)
{
	if (!flag)
	{
		bgPosY = 0;
		return;
	}

	// ‰æ–Ê—h‚ç‚µ
	if (moveBgFlag)
	{
		if (bgPosY > -20)
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
		if (bgPosY < 20)
		{
			bgPosY += 1;
		}
		else
		{
			moveBgFlag = true;
		}
	}


	// ½¸Û°Ù
	scrollCnt++;
	if (scrollCnt < SCROLL_MAX - 1)
	{
		for (int i = 0; i < 6; i++)
		{
			bgLPos[i].y[0] -= (ConstBgLPos[i + 1].y[0] - ConstBgLPos[i].y[0]) / SCROLL_MAX;
			bgLPos[i].y[1] += (ConstBgLPos[i].y[1] - ConstBgLPos[i + 1].y[1]) / SCROLL_MAX;
			bgLPos[i].y[2] -= (ConstBgLPos[i + 1].y[2] - ConstBgLPos[i].y[2]) / SCROLL_MAX;
			bgLPos[i].y[3] += (ConstBgLPos[i].y[3] - ConstBgLPos[i + 1].y[3]) / SCROLL_MAX;

			for (int j = 0; j < 4; j++)
			{
				bgRPos[i].y[j] = bgLPos[i].y[j];

				bgLPos[i].x[j] -= (ConstBgLPos[i + 1].x[j] - ConstBgLPos[i].x[j]) / SCROLL_MAX;
				bgRPos[i].x[j] -= (ConstBgRPos[i + 1].x[j] - ConstBgRPos[i].x[j]) / SCROLL_MAX;
			}		
		}
	}
	else
	{
		for (int i = 0; i < 6; i++)
		{
			bgLPos[i] = ConstBgLPos[i + 1];
			bgRPos[i] = ConstBgRPos[i + 1];
			scrollCnt = 0;
		}
	}
}



void BackgroundDraw(int floor)
{

	DrawBox(0, 0, 1600, 900, 0x512700, true);



	for (int i = 0; i < 7; i++)
	{
		DrawModiGraph(bgLPos[i].x[0] + bgPosX,
			bgLPos[i].y[0] + bgPosY,
			bgLPos[i].x[2] + bgPosX,
			bgLPos[i].y[2] + bgPosY,
			bgLPos[i].x[3] + bgPosX,
			bgLPos[i].y[3] + bgPosY,
			bgLPos[i].x[1] + bgPosX,
			bgLPos[i].y[1] + bgPosY,
			wallImage, true);

		DrawModiGraph(bgRPos[i].x[0] + bgPosX,
			bgRPos[i].y[0] + bgPosY,
			bgRPos[i].x[2] + bgPosX,
			bgRPos[i].y[2] + bgPosY,
			bgRPos[i].x[3] + bgPosX,
			bgRPos[i].y[3] + bgPosY,
			bgRPos[i].x[1] + bgPosX,
			bgRPos[i].y[1] + bgPosY,
			wallImage, true);
	}

	DrawBox(BG_CENTER_POS_X + bgPosX - 130, BG_CENTER_POS_Y + bgPosY - 87, BG_CENTER_POS_X + bgPosX + 130, BG_CENTER_POS_Y + bgPosY + 102, 0x000000, true);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 70);
	// ŽlŠp
	DrawBox(BG_CENTER_POS_X + bgPosX - 150, BG_CENTER_POS_Y + bgPosY - 102, BG_CENTER_POS_X + bgPosX + 150, BG_CENTER_POS_Y + bgPosY + 117, 0x000000, true);
	DrawBox(BG_CENTER_POS_X + bgPosX - 170, BG_CENTER_POS_Y + bgPosY - 117, BG_CENTER_POS_X + bgPosX + 170, BG_CENTER_POS_Y + bgPosY + 132, 0x000000, true);
	DrawBox(BG_CENTER_POS_X + bgPosX - 190, BG_CENTER_POS_Y + bgPosY - 132, BG_CENTER_POS_X + bgPosX + 190, BG_CENTER_POS_Y + bgPosY + 147, 0x000000, true);
	DrawBox(BG_CENTER_POS_X + bgPosX - 210, BG_CENTER_POS_Y + bgPosY - 147, BG_CENTER_POS_X + bgPosX + 210, BG_CENTER_POS_Y + bgPosY + 162, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawLine(BG_CENTER_POS_X + bgPosX - 432, BG_CENTER_POS_Y + bgPosY - 290, BG_CENTER_POS_X + bgPosX, BG_CENTER_POS_Y + bgPosY, 0x000000);
	DrawLine(BG_CENTER_POS_X + bgPosX - 432, BG_CENTER_POS_Y + bgPosY + 340, BG_CENTER_POS_X + bgPosX, BG_CENTER_POS_Y + bgPosY, 0x000000);
	DrawLine(BG_CENTER_POS_X + bgPosX + 432, BG_CENTER_POS_Y + bgPosY - 290, BG_CENTER_POS_X + bgPosX, BG_CENTER_POS_Y + bgPosY, 0x000000);
	DrawLine(BG_CENTER_POS_X + bgPosX + 432, BG_CENTER_POS_Y + bgPosY + 340, BG_CENTER_POS_X + bgPosX, BG_CENTER_POS_Y + bgPosY, 0x000000);


	DrawGraph(bgPosX - 432, bgPosY - 350, bgImageTmp, true);
}