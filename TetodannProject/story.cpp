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

	DrawFormatString(450, 100, 0xFFFFFF, "�Ƃ��錚���������݂���B");
	DrawFormatString(300, 200, 0xFFFFFF, "�_���W�����ƌď̂���邱�̌�������");
	DrawFormatString(150, 250, 0xFFFFFF, "���ǂ̂悤�ȖړI�Ō������ꂽ�̂��N���m��Ȃ��B");
	DrawFormatString(150, 300, 0xFFFFFF, "���̔閧��m��ׂ��A�l�X�͉ʊ��ɒ���𑱂��Ă���B");
	DrawFormatString(150, 350, 0xFFFFFF, "�_���W�����͐��\���̃t���A�ō\������Ă���̂���");
	DrawFormatString(200, 400, 0xFFFFFF, "���̂����鏊�ɋ��͂ȃ����X�^�[�����݂��Ă���");
	DrawFormatString(150, 450, 0xFFFFFF, "�ŏI�t���A�܂œ��B�ł����҂͂��Ȃ��ƌ����Ă���B");
	DrawFormatString(250, 500, 0xFFFFFF, "��l���́A����Ȗ��m��T�����Ă���҂��B");
	DrawFormatString(200, 550, 0xFFFFFF, "�p�Y�������邱�Ƃŉ��̂��U�����ł����l����");
	DrawFormatString(200, 600, 0xFFFFFF, "����𗘗p���ă_���W������i��ł����̂������c");


	ScreenFlip();
}