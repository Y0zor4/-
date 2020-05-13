/* ===== main.h ===== */
// 2019.09.09

//#pragma once

/* ----- 定数 ----- */

//ｼｽﾃﾑ関連
#define SCREEN_SIZE_X	800			//ｽｸﾘｰﾝのX座標
#define SCREEN_SIZE_Y	600			//ｽｸﾘｰﾝのY座標

#define COLOR_BRIGHT	255			//色の輝度

/* ----- 列挙型 ----- */

//ｼｰﾝ管理用
enum SCENE_ID {
	SCENE_ID_INIT				//ｹﾞｰﾑ初期化ｼｰﾝ
	, SCENE_ID_TITLE			//ﾀｲﾄﾙｼｰﾝ
	, SCENE_ID_GAME				//ｹﾞｰﾑｼｰﾝ
	, SCENE_ID_GAMEOVER			//ｹﾞｰﾑｵｰﾊﾞｰｼｰﾝ
	, SCENE_ID_MAX
};



/* ----- ﾌﾟﾛﾄﾀｲﾌﾟ宣言 ----- */

//ｼｽﾃﾑ関連
bool SystemInit(void);			//ｼｽﾃﾑの初期化

//ｼｰﾝ
void InitScene(void);			//初期化ｼｰﾝ
void TitleScene(void);			//ﾀｲﾄﾙｼｰﾝ
void GameScene(void);			//ｹﾞｰﾑｼｰﾝ
void GameoverScene(void);		//ｹﾞｰﾑｵｰﾊﾞｰｼｰﾝ

//描画
void TitleDraw(void);			//ﾀｲﾄﾙ用
void GameDraw(void);			//ｹﾞｰﾑ用
void GameoverDraw(void);		//ｹﾞｰﾑｵｰﾊﾞｰ用
