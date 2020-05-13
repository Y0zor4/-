/* ===== keycheck.h ===== */
// 2019.09.20

//#pragma once


/* ----- 列挙型 ----- */

//入力情報用
enum KEY_ID {
	  KEY_ID_SPACE				//ｽﾍﾟｰｽｷｰ
	, KEY_ID_PAUSE				//Pﾎﾞﾀﾝ
	, KEY_ID_MOUSE_LEFT			//ﾏｳｽ左ﾎﾞﾀﾝ
	, KEY_ID_MOUSE_MIDDLE		//ﾏｳｽ真ん中ﾎﾞﾀﾝ
	, KEY_ID_MOUSE_RIGHT		//ﾏｳｽ右ﾎﾞﾀﾝ
	, KEY_ID_MAX
};

/* ----- ﾌﾟﾛﾄﾀｲﾌﾟ宣言 ----- */

void KeyInit(void);				//入力情報の初期化
void KeyCheck(void);			//入力情報の確認

/* ----- ｸﾞﾛｰﾊﾞﾙ化 ----- */

//入力情報管理用
extern bool keyOld[KEY_ID_MAX];				//1ﾌﾚｰﾑ前の入力状態
extern bool keyNew[KEY_ID_MAX];				//現在の入力状態
extern bool keyDownTrigger[KEY_ID_MAX];		//ﾀﾞｳﾝ時のﾄﾘｶﾞｰ
extern bool keyUpTrigger[KEY_ID_MAX];		//ｱｯﾌﾟ時のﾄﾘｶﾞｰ