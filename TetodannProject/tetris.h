//#pragma once

#define DATA_MAX_X 12
#define DATA_MAX_Y 31

#define MINO_MAX 8      // ﾐﾉ種類
#define MINO_SIZE_X 40
#define MINO_SIZE_Y 40



// ﾌﾞﾛｯｸの種類
enum BLOCK_TYPE
{
	BLOCK_TYPE_I,
	BLOCK_TYPE_O,
	BLOCK_TYPE_T,
	BLOCK_TYPE_J,
	BLOCK_TYPE_L,
	BLOCK_TYPE_S,
	BLOCK_TYPE_Z,
	BLOCK_TYPE_MAX
};


// ﾌﾞﾛｯｸの向き
enum BLOCK_DIR
{
	DIR_0,
	DIR_1,
	DIR_2,
	DIR_3,
	DIR_MAX
};


// 移動の方向
enum MOVE_DIR
{
	MOVE_DIR_DOWN,
	MOVE_DIR_LEFT,
	MOVE_DIR_RIGHT,
	MOVE_DIR_MAX
};


// 座標
struct Pos
{
	int x;
	int y;
};


// ブロック
struct BLOCK
{
	int block[DIR_MAX][4][4];
	Pos pos;
	bool flag;
};






bool TetrisSysInit(void);		// ﾃﾄﾘｽ関連ｼｽﾃﾑ系初期化
void TetrisInit(void);			// ﾃﾄﾘｽ関連初期化
void MinoInit(void);			// ﾐﾉ情報初期化
void TetrisCtl(int atk);
void CreateMino(void);			// ﾐﾉ出現
void MinoDataTmp(void);			// ﾐﾉ情報をmoveDataTmpへ
void MinoData(void);			// tmp情報をmoveDataへ
void MoveMino(void);			// ﾐﾉ自動落下
void KeyMoveMino(void);			// ﾐﾉ移動制御
void KeyRotaMino(void);			// ﾐﾉ回転制御
void TetrisDraw(void);


int TetrisLine(void);			// 消した列数を返り値とする関数
int TetrisCombo(void);			// コンボ数を返り値とする関数
