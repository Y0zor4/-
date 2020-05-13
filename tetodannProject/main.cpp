// ----- BaseProject ----- //
// ----- main.cpp ----- //
//　2019.09.09
//　Kuwata Masato

#include "Dxlib.h"	
#include "main.h"
#include "keycheck.h"
#include "effect.h"


/* ----- 変数 ----- */

// ｼｽﾃﾑ関連
SCENE_ID sceneID;					// 現在のｼｰﾝ格納用
SCENE_ID preSceneID;				// 一つ前のｼｰﾝIDを格納用
int sceneCounter;					// ｼｰﾝ用

/* ----- ｶﾌﾟｾﾙ化 ----- */		// ← C++、ｵﾌﾞｼﾞｪｸﾄ指向

// ｴﾌｪｸﾄの初期化
void EffectInit(void)
{
	fadeIn = false;
	fadeOut = false;
	fadeCnt = 0;
	pauseFlag = false;
}

//　WinMain()
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	//ｼｽﾃﾑの初期化
	if (!SystemInit())
	{
		return -1;
	}


	// ｹﾞｰﾑﾙｰﾌﾟ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClsDrawScreen();	//画面消去

		//ｼｰﾝｶｳﾝﾀを制御
		if (sceneID != preSceneID)
		{
			preSceneID = sceneID;
			sceneCounter = 0;
		}

		//入力情報の確認
		KeyCheck();

		switch (sceneID)
		{
			//初期化ｼｰﾝ
		case SCENE_ID_INIT:
			InitScene();
			break;

			//ﾀｲﾄﾙｼｰﾝ
		case SCENE_ID_TITLE:
			//ﾌｪｰﾄﾞｲﾝ
			if (fadeIn)
			{
				if(!FadeInScreen(5)){}	// ｴﾌｪｸﾄ終了後の処理
			}
			//ﾌｪｰﾄﾞｱｳﾄ
			else if (fadeOut)
			{
				if (!FadeOutScreen(5))
				{
					// ｴﾌｪｸﾄ終了後の処理
					sceneID = SCENE_ID_GAME;		// しっかりとｼｰﾝが変わってから、ﾌｪｰﾄﾞｲﾝをtrueにする
					fadeIn = true;				
				}
			}

			TitleScene();
			break;

			//ｹﾞｰﾑｼｰﾝ
		case SCENE_ID_GAME:
			//ﾌｪｰﾄﾞｲﾝ
			if (fadeIn)
			{
				if (!FadeInScreen(5)) {}	// ｴﾌｪｸﾄ終了後の処理

			}
			//ﾌｪｰﾄﾞｱｳﾄ
			else if (fadeOut)
			{
				if (!FadeOutScreen(5))
				{
					// ｴﾌｪｸﾄ終了後の処理
					sceneID = SCENE_ID_GAMEOVER;	// しっかりとｼｰﾝが変わってから、ﾌｪｰﾄﾞｲﾝをtrueにする
					fadeIn = true;
				}
			}

			GameScene();
			break;

			//ｹﾞｰﾑｵｰﾊﾞｰｼｰﾝ
		case SCENE_ID_GAMEOVER:
			//ﾌｪｰﾄﾞｲﾝ
			if (fadeIn)
			{
				if (!FadeInScreen(5)) {}	// ｴﾌｪｸﾄ終了後の処理
			}
			//ﾌｪｰﾄﾞｱｳﾄ
			else if (fadeOut)
			{
				if (!FadeOutScreen(5))
				{
					// ｴﾌｪｸﾄ終了後の処理
					sceneID = SCENE_ID_INIT;	// しっかりとｼｰﾝが変わってから、ﾌｪｰﾄﾞｲﾝをtrueにする
					fadeIn = true;
				}
			}
			GameoverScene();
			break;

		default:
			break;
		}

		sceneCounter++;

		ScreenFlip();
	}

	
	DxLib_End(); // DxLibの終了

	return true;
}

/* ----- 初期化 ----- */

//ｼｽﾃﾑ系の初期化
bool SystemInit(void)
{
	//ｼｽﾃﾑの初期化
	SetWindowText("File_Kuwata");
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	ChangeWindowMode(true);

	//DXﾗｲﾌﾞﾗﾘの初期化
	if (DxLib_Init() == -1)
	{
		return  false;
	}
	SetDrawScreen(DX_SCREEN_BACK);

	KeyInit();		// 入力情報の初期化
	EffectInit();	// ｴﾌｪｸﾄの初期化

	//ｸﾞﾗﾌｨｯｸの登録

	//変数の初期化
	sceneCounter = 0;
	sceneID = SCENE_ID_INIT;
	preSceneID = SCENE_ID_MAX;
	fadeIn = true;

	return true;
}

/* ----- ｹﾞｰﾑｼｽﾃﾑ ----- */



/* ----- ｼｰﾝ ----- */

//初期化ｼｰﾝ
void InitScene(void)
{
	sceneID = SCENE_ID_TITLE;     // 初期化が終了したのでﾀｲﾄﾙへ
}

//ﾀｲﾄﾙｼｰﾝ
void TitleScene(void)
{
	
	if (keyDownTrigger[KEY_ID_SPACE])
	{
		fadeOut = true;
		//sceneID = SCENE_ID_GAME;
	}

	TitleDraw();
}

//ｹﾞｰﾑｼｰﾝ
void GameScene(void)
{	
	if (keyDownTrigger[KEY_ID_SPACE])
	{
		fadeOut = true;
		//sceneID = SCENE_ID_GAMEOVER;
	}

	// 一時停止
	if (keyDownTrigger[KEY_ID_PAUSE])
	{
		pauseFlag = !pauseFlag;			// よく使う否定
	}

	// Pause時
	if (pauseFlag)
	{
		SetDrawBright(120, 120, 120);
	}

	// 通常動作時
	else
	{

	}

	GameDraw();

	// Pauseﾒｯｾｰｼﾞを描画
	if (pauseFlag)
	{
		SetDrawBright(255, 255, 255);
		DrawString(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2, "ＰＡＵＳＥ", 0xFFFFFF);
	}
}

//ｹﾞｰﾑｵｰﾊﾞｰｼｰﾝ
void GameoverScene(void)
{
	
	if (keyDownTrigger[KEY_ID_SPACE])
	{
		fadeOut = true;
		//sceneID = SCENE_ID_TITLE;
	}

	GameoverDraw();
}

/* ----- 描画 ----- */

//ﾀｲﾄﾙｼｰﾝ
void TitleDraw(void)
{
	DrawFormatString(0, 0, 0xFFFFFF, "TitleScene : %d", sceneCounter);
	DrawBox(100, 100, 700, 500, 0x00FF00, true);
}

//ｹﾞｰﾑｼｰﾝ
void GameDraw(void)
{
	DrawFormatString(0, 0, 0xFFFFFF, "GameScene : %d", sceneCounter);
	DrawBox(100, 100, 700, 500, 0xFF0000, true);
}

//ｹﾞｰﾑｵｰﾊﾞｰｼｰﾝ
void GameoverDraw(void)
{
	DrawFormatString(0, 0, 0xFFFFFF, "GameoverScene : %d", sceneCounter);
	DrawBox(100, 100, 700, 500, 0x0000FF, true);
}