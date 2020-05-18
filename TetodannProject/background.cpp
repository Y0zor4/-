#include "Dxlib.h"	
#include "main.h"
#include "keycheck.h"
#include "background.h"

int bgImageTmp;

bool BackgroundSysInit(void)
{
	bool rtnFlag = true;
	bgImageTmp = LoadGraph("image/bg_tmp.png");
	return rtnFlag;
}

void BackgroundInit(void)
{

}

void BackgroundCtl(int floor)
{

}

void BackgroundDraw(int floor)
{
	DrawBox(OFFSET_X, OFFSET_Y, BG_SIZE_X + OFFSET_X, BG_SIZE_Y + OFFSET_Y, 0x000000, true);
	DrawGraph(OFFSET_X, OFFSET_Y, bgImageTmp, true);
}