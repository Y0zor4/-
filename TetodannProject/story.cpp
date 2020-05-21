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
	DrawFormatString(450, 900 + scrollPosY, 0xFFFFFF, "�Ƃ��錚���������݂���B");
	DrawFormatString(300, 1000 + scrollPosY, 0xFFFFFF, "�_���W�����ƌď̂���邱�̌�������");
	DrawFormatString(150, 1100 + scrollPosY, 0xFFFFFF, "���ǂ̂悤�ȖړI�Ō������ꂽ�̂��N���m��Ȃ��B");
	DrawFormatString(150, 1200 + scrollPosY, 0xFFFFFF, "���̔閧��m��ׂ��A�l�X�͉ʊ��ɒ���𑱂��Ă���B");
	DrawFormatString(150, 1300 + scrollPosY, 0xFFFFFF, "�_���W�����͐��\���̃t���A�ō\������Ă���̂���");
	DrawFormatString(200, 1400 + scrollPosY, 0xFFFFFF, "���̂����鏊�ɋ��͂ȃ����X�^�[�����݂��Ă���");
	DrawFormatString(150, 1500 + scrollPosY, 0xFFFFFF, "�ŏI�t���A�܂œ��B�ł����҂͂��Ȃ��ƌ����Ă���B");
	DrawFormatString(250, 1600 + scrollPosY, 0xFFFFFF, "��l���́A����Ȗ��m��T�����Ă���҂��B");
	DrawFormatString(200, 1700 + scrollPosY, 0xFFFFFF, "�p�Y�������邱�Ƃŉ��̂��U�����ł����l����");
	DrawFormatString(200, 1800 + scrollPosY, 0xFFFFFF, "����𗘗p���ă_���W������i��ł����̂������c");


	ScreenFlip();
}