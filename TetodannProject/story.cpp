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
	//DrawBox(100, 100, 700, 500, 0x00FF00, true);
	DrawFormatString(100, 100, 0xFFFFFF, "とある建造物が存在する。");
	DrawFormatString(100, 150, 0xFFFFFF, "ダンジョンと呼称されるこの建造物は");
	DrawFormatString(100, 200, 0xFFFFFF, "いつどのような目的で建造されたのか誰も知らない。");
	DrawFormatString(100, 250, 0xFFFFFF, "その秘密を知るべく、人々は果敢に挑戦を続けている。");
	DrawFormatString(100, 300, 0xFFFFFF, "ダンジョンは数十ものフロアで構成されているのだが");
	DrawFormatString(100, 350, 0xFFFFFF, "何故か至る所に強力なモンスターが存在しており");
	DrawFormatString(100, 400, 0xFFFFFF, "最終フロアまで到達できた者はいないと言われている。");
	DrawFormatString(100, 450, 0xFFFFFF, "主人公は、そんな未知を探求している者だ。");





	ScreenFlip();
}