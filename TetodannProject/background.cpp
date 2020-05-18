#include "Dxlib.h"	
#include "main.h"
#include "keycheck.h"
#include "background.h"


bool BackgroundSysInit(void)
{
	bool rtnFlag = true;

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
	DrawBox(OFFSET_X, OFFSET_Y, BG_SIZE_X + OFFSET_X, BG_SIZE_Y + OFFSET_Y, 0x00FFFF, true);
}