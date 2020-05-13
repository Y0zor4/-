// ----- effect.cpp ----- //
//�@2019.09.26
//�@Kuwata Masato


#include"DxLib.h"
#include"effect.h"

/* ----- �ϐ� ----- */

// ��ʐִ̪ؑ��
bool fadeIn;					// ̪��޲ݗp
bool fadeOut;					// ̪��ޱ�ėp
int fadeCnt;					// ��ʐִ̪ؑ�ėp����

//�ꎞ��~�̪��
bool pauseFlag;					// �ꎞ��~�p(true:��~)

// ̪��޲�
bool FadeInScreen(int fadeStep)
{
	fadeCnt += fadeStep;
	if (fadeCnt <= 255)
	{
		SetDrawBright(fadeCnt, fadeCnt, fadeCnt);
		return true;
	}
	else
	{
		SetDrawBright(255, 255, 255);
		fadeCnt = 0;
		fadeIn = false;
		return false;
	}
}

// ̪��ޱ��
bool FadeOutScreen(int fadeStep)
{
	fadeCnt += fadeStep;
	if (fadeCnt <= 255)
	{
		SetDrawBright(255 - fadeCnt, 255 - fadeCnt, 255 - fadeCnt);
		return true;
	}
	else
	{
		SetDrawBright(0, 0, 0);
		fadeCnt = 0;
		fadeOut = false;
		return false;
	}
}