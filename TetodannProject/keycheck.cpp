#include "Dxlib.h"
#include "keycheck.h"


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
	keyNew[KEY_ID_1] = CheckHitKey(KEY_INPUT_NUMPAD1);
	keyNew[KEY_ID_2] = CheckHitKey(KEY_INPUT_NUMPAD2);
	keyNew[KEY_ID_3] = CheckHitKey(KEY_INPUT_NUMPAD3);
	keyNew[KEY_ID_4] = CheckHitKey(KEY_INPUT_NUMPAD4);
	keyNew[KEY_ID_UP] = CheckHitKey(KEY_INPUT_UP);
	keyNew[KEY_ID_DOWN] = CheckHitKey(KEY_INPUT_DOWN);
	keyNew[KEY_ID_LEFT] = CheckHitKey(KEY_INPUT_LEFT);
	keyNew[KEY_ID_RIGHT] = CheckHitKey(KEY_INPUT_RIGHT);
	keyNew[KEY_ID_Z] = CheckHitKey(KEY_INPUT_Z);
	keyNew[KEY_ID_X] = CheckHitKey(KEY_INPUT_X);
	keyNew[KEY_ID_C] = CheckHitKey(KEY_INPUT_C);
	keyNew[KEY_ID_LSHIFT] = CheckHitKey(KEY_INPUT_LSHIFT);
	keyNew[KEY_ID_ENTER] = CheckHitKey(KEY_INPUT_RETURN);


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