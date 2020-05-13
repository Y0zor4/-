/* ===== effect.h ===== */
// 2019.09.26

//#pragma once

/* ----- ﾌﾟﾛﾄﾀｲﾌﾟ宣言 ----- */

void EffectInit(void);					//ｴﾌｪｸﾄの初期化
bool FadeInScreen(int fadeStep);		//ﾌｪｰﾄﾞｲﾝ用
bool FadeOutScreen(int fadeStep);		//ﾌｪｰﾄﾞｱｳﾄ用

/* ----- ｸﾞﾛｰﾊﾞﾙ化 ----- */

// 画面切替ｴﾌｪｸﾄ
extern bool fadeIn;						// ﾌｪｰﾄﾞｲﾝ用
extern bool fadeOut;					// ﾌｪｰﾄﾞｱｳﾄ用
extern int fadeCnt;						// 画面切替ｴﾌｪｸﾄ用ｶｳﾝﾀ

//一時停止ｴﾌｪｸﾄ
extern bool pauseFlag;					// 一時停止用(true:停止)
