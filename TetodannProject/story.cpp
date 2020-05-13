#include "Dxlib.h"	
#include "main.h"
#include "keycheck.h"
#include "story.h"

bool StorySysInit(void)
{
	bool rtnFlag = true;

	return rtnFlag;
}

void StoryInit(void)
{

}

int StoryScene(void)
{
	int rtn = 0;

	if (keyDownTrigger[KEY_ID_1])
	{
		rtn = 1;
	}

	StoryDraw();

	return rtn;
}

void StoryDraw(void)
{
	ClsDrawScreen();
	SetFontSize(50);
	DrawFormatString(0, 0, 0xFFFFFF, "StoryScene");
	DrawBox(100, 100, 700, 500, 0x00FF00, true);
	ScreenFlip();
}