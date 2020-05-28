#include "Dxlib.h"	
#include "main.h"
#include "keycheck.h"
#include "title.h"

int titleLogo;


bool TitleSysInit(void)
{
	bool rtnFlag = true;

	titleLogo = LoadGraph("image/title_logo.png");

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
		rtn = 1;
	}

	TitleDraw();

	return rtn;
}

void TitleDraw(void)
{
	ClsDrawScreen();
	DrawGraph(0, 0, titleLogo, true);
	ScreenFlip();
}