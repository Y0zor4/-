// ----- keycheck.cpp ----- //
//　2019.09.20
//　Kuwata Masato


#include "Dxlib.h"
#include "keycheck.h"

/* ----- 変数 ----- */

bool keyOld[KEY_ID_MAX];				//1ﾌﾚｰﾑ前の入力状態
bool keyNew[KEY_ID_MAX];				//現在の入力状態
bool keyDownTrigger[KEY_ID_MAX];		//ﾀﾞｳﾝ時のﾄﾘｶﾞｰ
bool keyUpTrigger[KEY_ID_MAX];			//ｱｯﾌﾟ時のﾄﾘｶﾞｰ

//入力情報の初期化
void KeyInit(void)
{
	for (int keyID = 0; keyID < KEY_ID_MAX; keyID++)
	{
		keyOld[keyID] = false;
		keyNew[keyID] = false;
		keyDownTrigger[keyID] = false;
		keyUpTrigger[keyID] = false;
	}
}


//入力情報の確認
void KeyCheck(void)
{
	//Oldの準備
	for (int keyID = 0; keyID < KEY_ID_MAX; keyID++)
	{
		keyOld[keyID] = keyNew[keyID];
	}

	//現在の状態を取得する
	keyNew[KEY_ID_SPACE] = CheckHitKey(KEY_INPUT_SPACE);
	keyNew[KEY_ID_PAUSE] = CheckHitKey(KEY_INPUT_P);

	//ﾄﾘｶﾞｰの算出
	for (int keyID = 0; keyID < KEY_ID_MAX; keyID++)
	{
		keyDownTrigger[keyID] = false;
		keyUpTrigger[keyID] = false;

		//ﾀﾞｳﾝﾄﾘｶﾞｰ
		if (!keyOld[keyID] && keyNew[keyID])
		{
			keyDownTrigger[keyID] = true;
		}

		//ｱｯﾌﾟﾄﾘｶﾞｰ
		if (keyOld[keyID] && !keyNew[keyID])
		{
			keyUpTrigger[keyID] = true;
		}
	}
}