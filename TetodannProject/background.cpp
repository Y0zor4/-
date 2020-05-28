#include "Dxlib.h"	
#include "main.h"
#include "keycheck.h"
#include "background.h"


struct BGPOS
{
	float x[4];
	float y[4];
};

int wallImage;
int groundImage;
int shadowImage;
float bgPosY;
float bgPosX;
bool moveBgFlag;

BGPOS ConstBgLPos[7];
BGPOS ConstBgRPos[7];
BGPOS ConstBgDPos[7];
BGPOS ConstBgUPos[7];

BGPOS bgLPos[6];
BGPOS bgRPos[6];
BGPOS bgDPos[6];
BGPOS bgUPos[6];

int scrollCnt;

int bgImage;
bool bgImFlag;
int bgFadeCnt;

bool BackgroundSysInit(void)
{
	bool rtnFlag = true;
	wallImage = LoadGraph("image/wall.png");
	groundImage = LoadGraph("image/ground.png");
	shadowImage = LoadGraph("image/bg_shadow.png");
	bgImage = LoadGraph("image/bg_tmp3.png");

	ConstBgLPos[0].x[0] = (BG_POS_X - 1242);
	ConstBgLPos[0].y[0] = (BG_POS_Y - 782);
	ConstBgLPos[0].x[1] = (BG_POS_X - 1242);
	ConstBgLPos[0].y[1] = (BG_POS_Y + 1674);
	ConstBgLPos[0].x[2] = (BG_POS_X - 88);
	ConstBgLPos[0].y[2] = (BG_POS_Y);
	ConstBgLPos[0].x[3] = (BG_POS_X - 88);
	ConstBgLPos[0].y[3] = (BG_POS_Y + 760);

	ConstBgLPos[1].x[0] = (BG_POS_X - 88);
	ConstBgLPos[1].y[0] = (BG_POS_Y);
	ConstBgLPos[1].x[1] = (BG_POS_X - 88);
	ConstBgLPos[1].y[1] = (BG_POS_Y + 760);
	ConstBgLPos[1].x[2] = (BG_POS_X + 125);
	ConstBgLPos[1].y[2] = (BG_POS_Y + 144);
	ConstBgLPos[1].x[3] = (BG_POS_X + 125);
	ConstBgLPos[1].y[3] = (BG_POS_Y + 591);

	ConstBgLPos[2].x[0] = (BG_POS_X + 125);
	ConstBgLPos[2].y[0] = (BG_POS_Y + 144);
	ConstBgLPos[2].x[1] = (BG_POS_X + 125);
	ConstBgLPos[2].y[1] = (BG_POS_Y + 591);
	ConstBgLPos[2].x[2] = (BG_POS_X + 216);
	ConstBgLPos[2].y[2] = (BG_POS_Y + 204);
	ConstBgLPos[2].x[3] = (BG_POS_X + 216);
	ConstBgLPos[2].y[3] = (BG_POS_Y + 519);

	ConstBgLPos[3].x[0] = (BG_POS_X + 216);
	ConstBgLPos[3].y[0] = (BG_POS_Y + 204);
	ConstBgLPos[3].x[1] = (BG_POS_X + 216);
	ConstBgLPos[3].y[1] = (BG_POS_Y + 519);
	ConstBgLPos[3].x[2] = (BG_POS_X + 264);
	ConstBgLPos[3].y[2] = (BG_POS_Y + 237);
	ConstBgLPos[3].x[3] = (BG_POS_X + 264);
	ConstBgLPos[3].y[3] = (BG_POS_Y + 481);

	ConstBgLPos[4].x[0] = (BG_POS_X + 264);
	ConstBgLPos[4].y[0] = (BG_POS_Y + 237);
	ConstBgLPos[4].x[1] = (BG_POS_X + 264);
	ConstBgLPos[4].y[1] = (BG_POS_Y + 481);
	ConstBgLPos[4].x[2] = (BG_POS_X + 296);
	ConstBgLPos[4].y[2] = (BG_POS_Y + 260);
	ConstBgLPos[4].x[3] = (BG_POS_X + 296);
	ConstBgLPos[4].y[3] = (BG_POS_Y + 455);

	ConstBgLPos[5].x[0] = (BG_POS_X + 296);
	ConstBgLPos[5].y[0] = (BG_POS_Y + 260);
	ConstBgLPos[5].x[1] = (BG_POS_X + 296);
	ConstBgLPos[5].y[1] = (BG_POS_Y + 455);
	ConstBgLPos[5].x[2] = (BG_POS_X + 318);
	ConstBgLPos[5].y[2] = (BG_POS_Y + 274);
	ConstBgLPos[5].x[3] = (BG_POS_X + 318);
	ConstBgLPos[5].y[3] = (BG_POS_Y + 439);

	ConstBgLPos[6].x[0] = (BG_POS_X + 318);
	ConstBgLPos[6].y[0] = (BG_POS_Y + 274);
	ConstBgLPos[6].x[1] = (BG_POS_X + 318);
	ConstBgLPos[6].y[1] = (BG_POS_Y + 439);
	ConstBgLPos[6].x[2] = (BG_POS_X + 335);
	ConstBgLPos[6].y[2] = (BG_POS_Y + 285);
	ConstBgLPos[6].x[3] = (BG_POS_X + 335);
	ConstBgLPos[6].y[3] = (BG_POS_Y + 425);


	// ‰E•Ç
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			ConstBgRPos[i].y[j] = ConstBgLPos[i].y[j];
			ConstBgRPos[i].x[j] = (BG_POS_X + BG_CENTER_X) + ((BG_POS_X + BG_CENTER_X) - ConstBgLPos[i].x[j]);
		}
	}


	
	for (int i = 0; i < 7; i++)
	{
		// “Vˆä
		ConstBgUPos[i].x[0] = ConstBgLPos[i].x[0];
		ConstBgUPos[i].y[0] = ConstBgLPos[i].y[0];
		ConstBgUPos[i].x[1] = ConstBgLPos[i].x[2];
		ConstBgUPos[i].y[1] = ConstBgLPos[i].y[2];
		ConstBgUPos[i].x[2] = ConstBgRPos[i].x[0];
		ConstBgUPos[i].y[2] = ConstBgRPos[i].y[0];
		ConstBgUPos[i].x[3] = ConstBgRPos[i].x[2];
		ConstBgUPos[i].y[3] = ConstBgRPos[i].y[2];

		// °
		ConstBgDPos[i].x[0] = ConstBgLPos[i].x[3];
		ConstBgDPos[i].y[0] = ConstBgLPos[i].y[3];
		ConstBgDPos[i].x[1] = ConstBgLPos[i].x[1];
		ConstBgDPos[i].y[1] = ConstBgLPos[i].y[1];
		ConstBgDPos[i].x[2] = ConstBgRPos[i].x[3];
		ConstBgDPos[i].y[2] = ConstBgRPos[i].y[3];
		ConstBgDPos[i].x[3] = ConstBgRPos[i].x[1];
		ConstBgDPos[i].y[3] = ConstBgRPos[i].y[1];
	}

	bgImFlag = false;
	bgFadeCnt = 0;

	return rtnFlag;
}



void BackgroundInit(void)
{
	bgPosX = 5;
	bgPosY = 5;
	moveBgFlag = true;
	for (int i = 0; i < 6; i++)
	{
		bgLPos[i] = ConstBgLPos[i + 1];
		bgRPos[i] = ConstBgRPos[i + 1];
		bgDPos[i] = ConstBgDPos[i + 1];
		bgUPos[i] = ConstBgUPos[i + 1];
	}

	scrollCnt = 0;
}



void BackgroundCtl(int floor, bool flag, bool eneFlag)
{

	if (floor % 5 == 0 && !flag && eneFlag)
	{
		if (!bgImFlag)
		{
			bgImFlag = true;
			bgFadeCnt = 0;
		}
	}
	else
	{
		bgImFlag = false;
	}

	if (!flag)
	{
		bgPosY = 0;
		return;
	}

	// ‰æ–Ê—h‚ç‚µ
	if (moveBgFlag)
	{
		if (bgPosY > -5)
		{
			bgPosY -= 0.3;
		}
		else
		{
			moveBgFlag = false;
		}
	}
	else
	{
		if (bgPosY < 5)
		{
			bgPosY += 0.3;
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
			// ¶‰E
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


			// ã‰º
			bgDPos[i].x[0] -= (ConstBgDPos[i + 1].x[0] - ConstBgDPos[i].x[0]) / SCROLL_MAX;
			bgDPos[i].x[1] += (ConstBgDPos[i].x[1] - ConstBgDPos[i + 1].x[1]) / SCROLL_MAX;
			bgDPos[i].x[2] -= (ConstBgDPos[i + 1].x[2] - ConstBgDPos[i].x[2]) / SCROLL_MAX;
			bgDPos[i].x[3] += (ConstBgDPos[i].x[3] - ConstBgDPos[i + 1].x[3]) / SCROLL_MAX;

			bgUPos[i].x[0] -= (ConstBgUPos[i + 1].x[0] - ConstBgUPos[i].x[0]) / SCROLL_MAX;
			bgUPos[i].x[1] += (ConstBgUPos[i].x[1] - ConstBgUPos[i + 1].x[1]) / SCROLL_MAX;
			bgUPos[i].x[2] -= (ConstBgUPos[i + 1].x[2] - ConstBgUPos[i].x[2]) / SCROLL_MAX;
			bgUPos[i].x[3] += (ConstBgUPos[i].x[3] - ConstBgUPos[i + 1].x[3]) / SCROLL_MAX;

			for (int j = 0; j < 4; j++)
			{
				bgDPos[i].y[j] -= (ConstBgDPos[i + 1].y[j] - ConstBgDPos[i].y[j]) / SCROLL_MAX;
				bgUPos[i].y[j] -= (ConstBgUPos[i + 1].y[j] - ConstBgUPos[i].y[j]) / SCROLL_MAX;
			}
		}
	}
	else
	{
		for (int i = 0; i < 6; i++)
		{
			bgLPos[i] = ConstBgLPos[i + 1];
			bgRPos[i] = ConstBgRPos[i + 1];
			bgDPos[i] = ConstBgDPos[i + 1];
			bgUPos[i] = ConstBgUPos[i + 1];
			scrollCnt = 0;
		}
	}
}



void BackgroundDraw(int floor, bool eneFlag)
{

	DrawBox(0, 0, 1600, 900, 0x512700, true);



	for (int i = 0; i < 6; i++)
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

		DrawModiGraph(bgDPos[i].x[0] + bgPosX,
			bgDPos[i].y[0] + bgPosY,
			bgDPos[i].x[2] + bgPosX,
			bgDPos[i].y[2] + bgPosY,
			bgDPos[i].x[3] + bgPosX,
			bgDPos[i].y[3] + bgPosY,
			bgDPos[i].x[1] + bgPosX,
			bgDPos[i].y[1] + bgPosY,
			groundImage, true);

		DrawModiGraph(bgUPos[i].x[0] + bgPosX,
			bgUPos[i].y[0] + bgPosY,
			bgUPos[i].x[2] + bgPosX,
			bgUPos[i].y[2] + bgPosY,
			bgUPos[i].x[3] + bgPosX,
			bgUPos[i].y[3] + bgPosY,
			bgUPos[i].x[1] + bgPosX,
			bgUPos[i].y[1] + bgPosY,
			wallImage, true);
	}


	// ‰e
	DrawGraph(BG_POS_X, BG_POS_Y, shadowImage, true);


	
	//DrawBox(BG_CENTER_POS_X + bgPosX - 130, BG_CENTER_POS_Y + bgPosY - 87, BG_CENTER_POS_X + bgPosX + 130, BG_CENTER_POS_Y + bgPosY + 102, 0x000000, true);

	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, 70);
	
	//DrawBox(BG_CENTER_POS_X + bgPosX - 150, BG_CENTER_POS_Y + bgPosY - 102, BG_CENTER_POS_X + bgPosX + 150, BG_CENTER_POS_Y + bgPosY + 117, 0x000000, true);
	//DrawBox(BG_CENTER_POS_X + bgPosX - 170, BG_CENTER_POS_Y + bgPosY - 117, BG_CENTER_POS_X + bgPosX + 170, BG_CENTER_POS_Y + bgPosY + 132, 0x000000, true);
	//DrawBox(BG_CENTER_POS_X + bgPosX - 190, BG_CENTER_POS_Y + bgPosY - 132, BG_CENTER_POS_X + bgPosX + 190, BG_CENTER_POS_Y + bgPosY + 147, 0x000000, true);
	//DrawBox(BG_CENTER_POS_X + bgPosX - 210, BG_CENTER_POS_Y + bgPosY - 147, BG_CENTER_POS_X + bgPosX + 210, BG_CENTER_POS_Y + bgPosY + 162, 0x000000, true);
	//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawLine(BG_CENTER_POS_X + bgPosX - 432, BG_CENTER_POS_Y + bgPosY - 290, BG_CENTER_POS_X + bgPosX, BG_CENTER_POS_Y + bgPosY, 0x000000);
	DrawLine(BG_CENTER_POS_X + bgPosX - 432, BG_CENTER_POS_Y + bgPosY + 340, BG_CENTER_POS_X + bgPosX, BG_CENTER_POS_Y + bgPosY, 0x000000);
	DrawLine(BG_CENTER_POS_X + bgPosX + 432, BG_CENTER_POS_Y + bgPosY - 290, BG_CENTER_POS_X + bgPosX, BG_CENTER_POS_Y + bgPosY, 0x000000);
	DrawLine(BG_CENTER_POS_X + bgPosX + 432, BG_CENTER_POS_Y + bgPosY + 340, BG_CENTER_POS_X + bgPosX, BG_CENTER_POS_Y + bgPosY, 0x000000);


	// “Á•ÊŠK‘w
	if (bgImFlag)
	{
		bgFadeCnt += 2;
		if (bgFadeCnt > 255)
		{
			bgFadeCnt = 255;
		}
	}
	else if(bgFadeCnt != 0 && !eneFlag)
	{
		bgFadeCnt -= 5;
		if (bgFadeCnt < 0)
		{
			bgFadeCnt = 0;
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, bgFadeCnt);
	DrawGraph(BG_POS_X, BG_POS_Y, bgImage, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}



bool GetBgBlend(int floor)
{
	if (bgFadeCnt == 0)
	{
		return false;
	}
	return true;
}