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
	DrawFormatString(100, 100, 0xFFFFFF, "�Ƃ��錚���������݂���B");
	DrawFormatString(100, 150, 0xFFFFFF, "�_���W�����ƌď̂���邱�̌�������");
	DrawFormatString(100, 200, 0xFFFFFF, "���ǂ̂悤�ȖړI�Ō������ꂽ�̂��N���m��Ȃ��B");
	DrawFormatString(100, 250, 0xFFFFFF, "���̔閧��m��ׂ��A�l�X�͉ʊ��ɒ���𑱂��Ă���B");
	DrawFormatString(100, 300, 0xFFFFFF, "�_���W�����͐��\���̃t���A�ō\������Ă���̂���");
	DrawFormatString(100, 350, 0xFFFFFF, "���̂����鏊�ɋ��͂ȃ����X�^�[�����݂��Ă���");
	DrawFormatString(100, 400, 0xFFFFFF, "�ŏI�t���A�܂œ��B�ł����҂͂��Ȃ��ƌ����Ă���B");
	DrawFormatString(100, 450, 0xFFFFFF, "��l���́A����Ȗ��m��T�����Ă���҂��B");





	ScreenFlip();
}