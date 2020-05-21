#include "Dxlib.h"	
#include "main.h"
#include "keycheck.h"
#include "story.h"


int bg_storyImage;

int scrollPosY;

bool StorySysInit(void)
{
	bool rtnFlag = true;

	return rtnFlag;
}

void StoryInit(void)
{
	bg_storyImage = LoadGraph("image/bg_story.png");
	scrollPosY = 0;
}

int StoryScene(void)
{
	int rtn = 0;

	if (keyDownTrigger[KEY_ID_SPACE] || scrollPosY <= -SCROLLPOSY_MAX)
	{
		scrollPosY = 0;

		rtn = 1;
	}

	StoryDraw();

	scrollPosY--;

	return rtn;
}

void StoryDraw(void)
{
	ClsDrawScreen();
	
	SetDrawBright(128, 128, 128);
	DrawGraph(0, 0, bg_storyImage, true);
	SetFontSize(25);
	DrawFormatString(1425, 825, 0xFFFFFF, "Read without");
	DrawFormatString(1450, 850, 0xFFFFFF, "skipping");
	DrawFormatString(1415, 875, 0xFFFFFF, "Push To SPACE");
	SetDrawBright(255, 255, 255);

	SetFontSize(50);
	DrawFormatString(0, 0, 0xFFFFFF, "StoryScene");
	DrawFormatString(450, 900 + scrollPosY, 0xFFFFFF, "とある建造物が存在する。");
	DrawFormatString(300, 1000 + scrollPosY, 0xFFFFFF, "ダンジョンと呼称されるこの建造物は");
	DrawFormatString(150, 1100 + scrollPosY, 0xFFFFFF, "いつどのような目的で建造されたのか誰も知らない。");
	DrawFormatString(150, 1200 + scrollPosY, 0xFFFFFF, "その秘密を知るべく、人々は果敢に挑戦を続けている。");
	DrawFormatString(150, 1300 + scrollPosY, 0xFFFFFF, "ダンジョンは数十ものフロアで構成されているのだが");
	DrawFormatString(200, 1400 + scrollPosY, 0xFFFFFF, "何故か至る所に強力なモンスターが存在しており");
	DrawFormatString(150, 1500 + scrollPosY, 0xFFFFFF, "最終フロアまで到達できた者はいないと言われている。");
	DrawFormatString(250, 1600 + scrollPosY, 0xFFFFFF, "主人公は、そんな未知を探求している者だ。");
	DrawFormatString(200, 1700 + scrollPosY, 0xFFFFFF, "パズルをすることで何故か攻撃ができる主人公は");
	DrawFormatString(200, 1800 + scrollPosY, 0xFFFFFF, "これを利用してダンジョンを進んでいくのだった…");


	ScreenFlip();
}