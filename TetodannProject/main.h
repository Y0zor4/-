//#pragma once

#define SCREEN_SIZE_X	1600		// ｽｸﾘｰﾝのX座標
#define SCREEN_SIZE_Y	900			// ｽｸﾘｰﾝのY座標

#define COLOR_BRIGHT	255			// 色の輝度


//ｼｰﾝ管理用
enum SCENE_ID {
	SCENE_ID_TITLE,				// ﾀｲﾄﾙｼｰﾝ
	SCENE_ID_STORY,				// ｽﾄｰﾘｰ
	SCENE_ID_NAME,				// ﾌﾟﾚｲﾔｰ名入力
	SCENE_ID_SELECT,            // ｾﾚｸﾄ
	SCENE_ID_GAME,				// ｹﾞｰﾑｼｰﾝ
	SCENE_ID_GAMEOVER,			// ｹﾞｰﾑｵｰﾊﾞｰｼｰﾝ
	SCENE_ID_GAMECLEAR,			// ｹﾞｰﾑｸﾘｱ
	SCENE_ID_RANKING,			// ﾗﾝｷﾝｸﾞ
	SCENE_ID_MAX,
};




