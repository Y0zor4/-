#include "Dxlib.h"	
#include "main.h"
#include "keycheck.h"
#include "story.h"


int bg_storyImage;

bool StorySysInit(void)
{
	bool rtnFlag = true;

	return rtnFlag;
}

void StoryInit(void)
{
	bg_storyImage = LoadGraph("image/bg_story.png");
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
	SetDrawBright(128, 128, 128);
	DrawGraph(0, 0, bg_storyImage, true);
	SetDrawBright(255, 255, 255);
	DrawFormatString(0, 0, 0xFFFFFF, "StoryScene");

	DrawFormatString(450, 100, 0xFFFFFF, "とある建造物が存在する。");
	DrawFormatString(300, 200, 0xFFFFFF, "ダンジョンと呼称されるこの建造物は");
	DrawFormatString(150, 250, 0xFFFFFF, "いつどのような目的で建造されたのか誰も知らない。");
	DrawFormatString(150, 300, 0xFFFFFF, "その秘密を知るべく、人々は果敢に挑戦を続けている。");
	DrawFormatString(150, 350, 0xFFFFFF, "ダンジョンは数十ものフロアで構成されているのだが");
	DrawFormatString(200, 400, 0xFFFFFF, "何故か至る所に強力なモンスターが存在しており");
	DrawFormatString(150, 450, 0xFFFFFF, "最終フロアまで到達できた者はいないと言われている。");
	DrawFormatString(250, 500, 0xFFFFFF, "主人公は、そんな未知を探求している者だ。");
	DrawFormatString(200, 550, 0xFFFFFF, "パズルをすることで何故か攻撃ができる主人公は");
	DrawFormatString(200, 600, 0xFFFFFF, "これを利用してダンジョンを進んでいくのだった…");


	ScreenFlip();
}