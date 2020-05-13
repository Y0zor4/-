// ----- effect.cpp ----- //
//　2019.09.26
//　Kuwata Masato


#include"DxLib.h"
#include"effect.h"

/* ----- 変数 ----- */

// 画面切替ｴﾌｪｸﾄ
bool fadeIn;					// ﾌｪｰﾄﾞｲﾝ用
bool fadeOut;					// ﾌｪｰﾄﾞｱｳﾄ用
int fadeCnt;					// 画面切替ｴﾌｪｸﾄ用ｶｳﾝﾀ

//一時停止ｴﾌｪｸﾄ
bool pauseFlag;					// 一時停止用(true:停止)

// ﾌｪｰﾄﾞｲﾝ
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

// ﾌｪｰﾄﾞｱｳﾄ
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