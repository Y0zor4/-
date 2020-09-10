#include "Dxlib.h"	
#include "main.h"
#include "keycheck.h"
#include "tetris.h"

int minoImage[MINO_MAX];					// ﾐﾉ画像

int mapData[DATA_MAX_Y][DATA_MAX_X];		// ﾏｯﾌﾟﾃﾞｰﾀ格納用

int moveData[DATA_MAX_Y][DATA_MAX_X];		// ﾏｯﾌﾟﾃﾞｰﾀに対するﾐﾉの情報格納用

int downData[DATA_MAX_Y][DATA_MAX_X];		// ﾏｯﾌﾟﾃﾞｰﾀに対する予測落下地点の情報格納用

int typeBlock;								// ﾌﾞﾛｯｸの種類格納用
BLOCK_DIR dir;								// ﾌﾞﾛｯｸの向き格納用
BLOCK_DIR dirTmp;							// ﾌﾞﾛｯｸの向き格納用ﾊﾞｯｸｱｯﾌﾟ

BLOCK blockType[BLOCK_TYPE_MAX];			// 移動中のﾐﾉ情報格納用
BLOCK blockTypeTmp[BLOCK_TYPE_MAX];			// 移動中のﾐﾉ情報格納用ﾊﾞｯｸｱｯﾌﾟ
BLOCK blockTypeDown[BLOCK_TYPE_MAX];		// 予測落下地点のﾐﾉ情報格納用

int next[BLOCK_TYPE_MAX];					// next保存用
int next2[BLOCK_TYPE_MAX];					// next保存用2

int hold;									// hold保存用


// そのﾌﾚｰﾑの消したﾗｲﾝ保存用
int line;

// 何行目を消したか保存用
int lines[4];

// 消したﾗｲﾝ数保存用
int lineCnt;

// ｺﾝﾎﾞ数保存用
int combo;

// 操作不能ｶｳﾝﾄ
int dontCtlTime;

// ﾐﾉを置いたかどうかの判定用
bool putFlag;

// holdを利用したかどうか
bool holdFlag;

// ﾐﾉ自動落下用
int minoCnt;

// 敵の攻撃
int atkMax;

// 画面揺らし用
int shakeCnt;
int shakePosX;
bool shakeFlag;
bool shakeLR;


// ﾁｬｰｼﾞ攻撃用
int charge;
int chargeBring;
bool chargeBringFlag;

// ｹﾞｰﾑｵｰﾊﾞｰ用
bool gameoverFlag;

// 効果音
int chargeSound;
int blockSound;
int deleteSound;
int chargeAtkSound;




// ﾃﾄﾘｽ関連ｼｽﾃﾑ系初期化
bool TetrisSysInit(void)
{
	bool rtnFlag = true;

	MinoInit();

	LoadDivGraph("Image/mino.png", MINO_MAX, MINO_MAX, 1, MINO_SIZE_X, MINO_SIZE_Y, &minoImage[0]);

	chargeSound = LoadSoundMem("sound/charge.mp3");

	blockSound = LoadSoundMem("sound/block.mp3");

	deleteSound = LoadSoundMem("sound/delete.mp3");

	chargeAtkSound = LoadSoundMem("sound/chargeatk.mp3");

	return rtnFlag;
}


// ﾃﾄﾘｽ関連初期化
void TetrisInit(void)
{
	// ﾑｰﾌﾞﾃﾞｰﾀ、予測落下地点の初期化
	for (int x = 0; x < DATA_MAX_X; x++)
	{
		for (int y = 0; y < DATA_MAX_Y; y++)
		{
			moveData[y][x] = -1;
			downData[y][x] = -1;
		}
	}


	// ﾏｯﾌﾟﾃﾞｰﾀの初期化
	for (int x = 0; x < DATA_MAX_X; x++)
	{
		for (int y = 0; y < DATA_MAX_Y; y++)
		{
			mapData[y][x] = -1;
			if (y == 0 || y == DATA_MAX_Y - 1)
			{
				mapData[y][x] = 7;
			}
			if (x == 0 || x == DATA_MAX_X - 1)
			{
				mapData[y][x] = 7;
			}
		}
	}


	// next初期化
	for (int i = 0; i < BLOCK_TYPE_MAX; i++)
	{
		next[i] = rand() % BLOCK_TYPE_MAX;
		next2[i] = rand() % BLOCK_TYPE_MAX;
		if (i > 0)
		{
			while (!CreateNext(next, i))
			{
				next[i] = rand() % BLOCK_TYPE_MAX;
			}

			while (!CreateNext(next2, i))
			{
				next2[i] = rand() % BLOCK_TYPE_MAX;
			}
		}
	}


	// hold初期化
	hold = -1;


	// ﾐﾉ初期化
	blockType[typeBlock].flag = false;	


	// その他変数
	line = 0;
	lineCnt = 0;
	combo = 0;
	dontCtlTime = 0;
	minoCnt = 0;
	atkMax = 0;
	shakeCnt = 0;
	shakePosX = 0;
	shakeFlag = false;
	shakeLR = true;
	charge = 0;
	chargeBring = 100;
	chargeBringFlag = false;
	putFlag = false; 
	holdFlag = false;
	gameoverFlag = false;
}


// ﾐﾉ情報初期化
void MinoInit(void)
{
	// ﾃﾞｰﾀ格納
	for (int a = 0; a < BLOCK_TYPE_MAX; a++)
	{
		for (int b = 0; b < DIR_MAX; b++)
		{
			for (int c = 0; c < 4; c++)
			{
				for (int d = 0; d < 4; d++)
				{
					blockType[a].block[b][c][d] = -1;
				}
			}
		}
	}

	// BROCK_TIPE_I
	blockType[BLOCK_TYPE_I].block[DIR_0][1][0] = 1;
	blockType[BLOCK_TYPE_I].block[DIR_0][1][1] = 1;
	blockType[BLOCK_TYPE_I].block[DIR_0][1][2] = 1;
	blockType[BLOCK_TYPE_I].block[DIR_0][1][3] = 1;

	blockType[BLOCK_TYPE_I].block[DIR_1][0][1] = 1;
	blockType[BLOCK_TYPE_I].block[DIR_1][1][1] = 1;
	blockType[BLOCK_TYPE_I].block[DIR_1][2][1] = 1;
	blockType[BLOCK_TYPE_I].block[DIR_1][3][1] = 1;

	blockType[BLOCK_TYPE_I].block[DIR_2][2][0] = 1;
	blockType[BLOCK_TYPE_I].block[DIR_2][2][1] = 1;
	blockType[BLOCK_TYPE_I].block[DIR_2][2][2] = 1;
	blockType[BLOCK_TYPE_I].block[DIR_2][2][3] = 1;

	blockType[BLOCK_TYPE_I].block[DIR_3][0][2] = 1;
	blockType[BLOCK_TYPE_I].block[DIR_3][1][2] = 1;
	blockType[BLOCK_TYPE_I].block[DIR_3][2][2] = 1;
	blockType[BLOCK_TYPE_I].block[DIR_3][3][2] = 1;



	// BLOCK_TYPE_J
	blockType[BLOCK_TYPE_J].block[DIR_0][0][0] = 1;
	blockType[BLOCK_TYPE_J].block[DIR_0][1][0] = 1;
	blockType[BLOCK_TYPE_J].block[DIR_0][1][1] = 1;
	blockType[BLOCK_TYPE_J].block[DIR_0][1][2] = 1;

	blockType[BLOCK_TYPE_J].block[DIR_1][0][1] = 1;
	blockType[BLOCK_TYPE_J].block[DIR_1][0][2] = 1;
	blockType[BLOCK_TYPE_J].block[DIR_1][1][1] = 1;
	blockType[BLOCK_TYPE_J].block[DIR_1][2][1] = 1;

	blockType[BLOCK_TYPE_J].block[DIR_2][1][0] = 1;
	blockType[BLOCK_TYPE_J].block[DIR_2][1][1] = 1;
	blockType[BLOCK_TYPE_J].block[DIR_2][1][2] = 1;
	blockType[BLOCK_TYPE_J].block[DIR_2][2][2] = 1;

	blockType[BLOCK_TYPE_J].block[DIR_3][0][1] = 1;
	blockType[BLOCK_TYPE_J].block[DIR_3][1][1] = 1;
	blockType[BLOCK_TYPE_J].block[DIR_3][2][0] = 1;
	blockType[BLOCK_TYPE_J].block[DIR_3][2][1] = 1;



	// BLOCK_TYPE_L
	blockType[BLOCK_TYPE_L].block[DIR_0][0][3] = 1;
	blockType[BLOCK_TYPE_L].block[DIR_0][1][1] = 1;
	blockType[BLOCK_TYPE_L].block[DIR_0][1][2] = 1;
	blockType[BLOCK_TYPE_L].block[DIR_0][1][3] = 1;

	blockType[BLOCK_TYPE_L].block[DIR_1][0][2] = 1;
	blockType[BLOCK_TYPE_L].block[DIR_1][1][2] = 1;
	blockType[BLOCK_TYPE_L].block[DIR_1][2][2] = 1;
	blockType[BLOCK_TYPE_L].block[DIR_1][2][3] = 1;

	blockType[BLOCK_TYPE_L].block[DIR_2][1][1] = 1;
	blockType[BLOCK_TYPE_L].block[DIR_2][1][2] = 1;
	blockType[BLOCK_TYPE_L].block[DIR_2][1][3] = 1;
	blockType[BLOCK_TYPE_L].block[DIR_2][2][1] = 1;

	blockType[BLOCK_TYPE_L].block[DIR_3][0][1] = 1;
	blockType[BLOCK_TYPE_L].block[DIR_3][0][2] = 1;
	blockType[BLOCK_TYPE_L].block[DIR_3][1][2] = 1;
	blockType[BLOCK_TYPE_L].block[DIR_3][2][2] = 1;



	// BLOCK_TYPE_S
	blockType[BLOCK_TYPE_S].block[DIR_0][1][2] = 1;
	blockType[BLOCK_TYPE_S].block[DIR_0][1][3] = 1;
	blockType[BLOCK_TYPE_S].block[DIR_0][2][1] = 1;
	blockType[BLOCK_TYPE_S].block[DIR_0][2][2] = 1;

	blockType[BLOCK_TYPE_S].block[DIR_1][0][1] = 1;
	blockType[BLOCK_TYPE_S].block[DIR_1][1][1] = 1;
	blockType[BLOCK_TYPE_S].block[DIR_1][1][2] = 1;
	blockType[BLOCK_TYPE_S].block[DIR_1][2][2] = 1;

	blockType[BLOCK_TYPE_S].block[DIR_2][0][2] = 1;
	blockType[BLOCK_TYPE_S].block[DIR_2][0][3] = 1;
	blockType[BLOCK_TYPE_S].block[DIR_2][1][1] = 1;
	blockType[BLOCK_TYPE_S].block[DIR_2][1][2] = 1;

	blockType[BLOCK_TYPE_S].block[DIR_3][0][2] = 1;
	blockType[BLOCK_TYPE_S].block[DIR_3][1][2] = 1;
	blockType[BLOCK_TYPE_S].block[DIR_3][1][3] = 1;
	blockType[BLOCK_TYPE_S].block[DIR_3][2][3] = 1;



	// BLOCK_TYPE_Z
	blockType[BLOCK_TYPE_Z].block[DIR_0][1][0] = 1;
	blockType[BLOCK_TYPE_Z].block[DIR_0][1][1] = 1;
	blockType[BLOCK_TYPE_Z].block[DIR_0][2][1] = 1;
	blockType[BLOCK_TYPE_Z].block[DIR_0][2][2] = 1;

	blockType[BLOCK_TYPE_Z].block[DIR_1][0][1] = 1;
	blockType[BLOCK_TYPE_Z].block[DIR_1][1][0] = 1;
	blockType[BLOCK_TYPE_Z].block[DIR_1][1][1] = 1;
	blockType[BLOCK_TYPE_Z].block[DIR_1][2][0] = 1;

	blockType[BLOCK_TYPE_Z].block[DIR_2][0][0] = 1;
	blockType[BLOCK_TYPE_Z].block[DIR_2][0][1] = 1;
	blockType[BLOCK_TYPE_Z].block[DIR_2][1][1] = 1;
	blockType[BLOCK_TYPE_Z].block[DIR_2][1][2] = 1;

	blockType[BLOCK_TYPE_Z].block[DIR_3][0][2] = 1;
	blockType[BLOCK_TYPE_Z].block[DIR_3][1][1] = 1;
	blockType[BLOCK_TYPE_Z].block[DIR_3][1][2] = 1;
	blockType[BLOCK_TYPE_Z].block[DIR_3][2][1] = 1;



	// BLOCK_TYPE_T
	blockType[BLOCK_TYPE_T].block[DIR_0][0][2] = 1;
	blockType[BLOCK_TYPE_T].block[DIR_0][1][1] = 1;
	blockType[BLOCK_TYPE_T].block[DIR_0][1][2] = 1;
	blockType[BLOCK_TYPE_T].block[DIR_0][1][3] = 1;

	blockType[BLOCK_TYPE_T].block[DIR_1][0][2] = 1;
	blockType[BLOCK_TYPE_T].block[DIR_1][1][2] = 1;
	blockType[BLOCK_TYPE_T].block[DIR_1][1][3] = 1;
	blockType[BLOCK_TYPE_T].block[DIR_1][2][2] = 1;

	blockType[BLOCK_TYPE_T].block[DIR_2][1][1] = 1;
	blockType[BLOCK_TYPE_T].block[DIR_2][1][2] = 1;
	blockType[BLOCK_TYPE_T].block[DIR_2][1][3] = 1;
	blockType[BLOCK_TYPE_T].block[DIR_2][2][2] = 1;

	blockType[BLOCK_TYPE_T].block[DIR_3][0][2] = 1;
	blockType[BLOCK_TYPE_T].block[DIR_3][1][1] = 1;
	blockType[BLOCK_TYPE_T].block[DIR_3][1][2] = 1;
	blockType[BLOCK_TYPE_T].block[DIR_3][2][2] = 1;



	// BLOCK_TYPE_O
	blockType[BLOCK_TYPE_O].block[DIR_0][1][1] = 1;
	blockType[BLOCK_TYPE_O].block[DIR_0][1][2] = 1;
	blockType[BLOCK_TYPE_O].block[DIR_0][2][1] = 1;
	blockType[BLOCK_TYPE_O].block[DIR_0][2][2] = 1;

	blockType[BLOCK_TYPE_O].block[DIR_1][1][1] = 1;
	blockType[BLOCK_TYPE_O].block[DIR_1][1][2] = 1;
	blockType[BLOCK_TYPE_O].block[DIR_1][2][1] = 1;
	blockType[BLOCK_TYPE_O].block[DIR_1][2][2] = 1;

	blockType[BLOCK_TYPE_O].block[DIR_2][1][1] = 1;
	blockType[BLOCK_TYPE_O].block[DIR_2][1][2] = 1;
	blockType[BLOCK_TYPE_O].block[DIR_2][2][1] = 1;
	blockType[BLOCK_TYPE_O].block[DIR_2][2][2] = 1;

	blockType[BLOCK_TYPE_O].block[DIR_3][1][1] = 1;
	blockType[BLOCK_TYPE_O].block[DIR_3][1][2] = 1;
	blockType[BLOCK_TYPE_O].block[DIR_3][2][1] = 1;
	blockType[BLOCK_TYPE_O].block[DIR_3][2][2] = 1;


	// ﾊﾞｯｸｱｯﾌﾟ用の変数にも格納
	for (int a = 0; a < BLOCK_TYPE_MAX; a++)
	{
		for (int b = 0; b < DIR_MAX; b++)
		{
			for (int c = 0; c < 4; c++)
			{
				for (int d = 0; d < 4; d++)
				{
					blockTypeTmp[a].block[b][c][d] = blockType[a].block[b][c][d];
					blockTypeDown[a].block[b][c][d] = blockType[a].block[b][c][d];
				}
			}
		}
	}
}



int TetrisCtl(int atk)
{
	// 初期化処理
	int damage = 0;
	line = 0;			// 毎ﾌﾚｰﾑのﾗｲﾝ数保存用
	putFlag = false;    // そのﾌﾚｰﾑではまだ置いていないため初期化

	atkMax += atk;

	if (dontCtlTime <= 0)
	{
		for (int j = 0; j < 4; j++)
		{
			lines[j] = -1;	// 初期化用
		}

		dontCtlTime = 0;	// 移動不可時間ｶｳﾝﾄ
		lineCnt = 0;		// 消したﾗｲﾝ数の保存用

		// ﾐﾉが出現しているかどうかのﾁｪｯｸ
		if (!blockType[typeBlock].flag && !gameoverFlag)
		{
			CreateMino();		// なければ出現処理

			MinoData();			// ﾃﾞｰﾀ保存
			if (HitCheckMove())
			{
				gameoverFlag = true;
			}
		}
	}


	// next2が空であれば、補充の処理
	if (next2[0] == -1)
	{
		for (int i = 0; i < BLOCK_TYPE_MAX; i++)
		{
			next2[i] = rand() % BLOCK_TYPE_MAX;
			if (i > 0)
			{
				while (!CreateNext(next2, i))
				{
					next2[i] = rand() % BLOCK_TYPE_MAX;
				}
			}
		}
	}


	// hold用
	Hold();

	// 移動、回転、当たり判定
	MoveMino();

	// 敵の攻撃
	if (atkMax != 0 && putFlag)
	{
		EnemyAtkBlock();
		PlaySoundMem(blockSound, DX_PLAYTYPE_BACK, true);
		shakeFlag = true;
		shakeCnt = 0;
	}
	
	// ﾐﾉ削除
	DisMino();

	// ﾁｬｰｼﾞ
	if (line > 0)
	{
		if (charge < 15)
		{
			charge += line;
			if (charge >= 15)
			{
				charge = 15;
			}
		}
		if (charge >= 10)
		{
			// 音再生
			PlaySoundMem(chargeSound, DX_PLAYTYPE_BACK, true);
		}
	}

	if (keyDownTrigger[KEY_ID_LSHIFT])
	{
		if (charge >= 10)
		{
			damage += charge * 200;
			charge = 0;
			PlaySoundMem(chargeAtkSound, DX_PLAYTYPE_BACK, true);
		}
	}


	// 移動不可時間の減算
	if (dontCtlTime >= 0)
	{
		dontCtlTime--;
	}

	for (int y = 0; y < 6 - 1; y++)
	{
		for (int x = 1; x < DATA_MAX_X - 1; x++)
		{
			mapData[y][x] = -1;
		}
	}

	return damage;
}


// next用
bool CreateNext(int* nextBlock, int num)
{
	for (int i = 0; i < num; i++)
	{
		if (nextBlock[i] == nextBlock[num])
		{
			return false;
		}
	}
	return true;
}


// hold用
void Hold(void)
{
	if (keyDownTrigger[KEY_ID_C] && !holdFlag)
	{
		if (hold == -1)
		{
			hold = typeBlock;
			blockType[typeBlock].flag = false;
		}
		else
		{
			int tmp = typeBlock;
			typeBlock = hold;
			hold = tmp;
			blockType[typeBlock].pos.x = 4;
			blockType[typeBlock].pos.y = 9;
			dir = DIR_0;
			blockType[typeBlock].flag = true;
			holdFlag = true;
		}
		PlaySoundFile("sound/hold.mp3", DX_PLAYTYPE_BACK);
	}
}


// ﾐﾉ出現
void CreateMino(void)
{
	typeBlock = next[0];
	blockType[typeBlock].pos.x = 4;
	blockType[typeBlock].pos.y = 9;
	dir = DIR_0;
	blockType[typeBlock].flag = true;
	minoCnt = 0;

	for (int i = 0; i < BLOCK_TYPE_MAX - 1; i++)
	{
		next[i] = next[i + 1];
	}

	next[BLOCK_TYPE_MAX - 1] = next2[0];

	for (int i = 0; i < BLOCK_TYPE_MAX - 1; i++)
	{
		next2[i] = next2[i + 1];
	}

	next2[BLOCK_TYPE_MAX - 1] = -1;
}


// ﾐﾉ情報をmoveDataへ
void MinoData(void)
{
	// 一度初期化
	for (int x = 0; x < DATA_MAX_X; x++)
	{
		for (int y = 0; y < DATA_MAX_Y; y++)
		{
			moveData[y][x] = -1;
		}
	}

	// 反映
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (blockType[typeBlock].block[dir][y][x] != -1)
			{
				moveData[blockType[typeBlock].pos.y + y][blockType[typeBlock].pos.x + x] = typeBlock;
			}
		}
	}
}


// ﾐﾉの制御
void MoveMino(void)
{
	// キー情報の回転処理
	if (blockType[typeBlock].flag)
	{
		MinoSave();			// 移動前のﾐﾉ情報保存
		KeyRotaMino();		// ｷｰ操作
		MinoData();			// ﾃﾞｰﾀ保存
		// 当たり判定
		if (HitCheckMove())	// 保存したﾃﾞｰﾀで当たり判定
		{
			MinoSaveRev();  // 当てっていればﾊﾞｯｸｱｯﾌﾟで上書き
		}
		else
		{
			// 音再生
			if (keyDownTrigger[KEY_ID_Z] || keyDownTrigger[KEY_ID_X])
			{
				PlaySoundFile("sound/move.mp3", DX_PLAYTYPE_BACK);
			}
		}
		MinoData();		// 当たっていなければそのまま保存
	}

	// 自動の移動処理
	if (blockType[typeBlock].flag)
	{
		MinoSave();			// 移動前のﾐﾉ情報保存
		AutoMoveMino();		// 自動落下
		MinoData();			// ﾃﾞｰﾀ保存
		if (HitCheckMove())
		{
			MinoSaveRev();  // 当てっていればﾊﾞｯｸｱｯﾌﾟで上書き
			MinoData();		// ﾃﾞｰﾀ保存
			MapData();		// ﾏｯﾌﾟﾃﾞｰﾀへの保存
		}
		else
		{
			MinoData();			// 当たっていなければそのまま保存
		}
	}

	// キー情報の下移動処理
	if (blockType[typeBlock].flag)
	{
		MinoSave();			// 移動前のﾐﾉ情報保存
		KeyMoveMinoDown();	// ｷｰ操作
		MinoData();			// ﾃﾞｰﾀ保存
		// 当たり判定
		if (HitCheckMove())	// 保存したﾃﾞｰﾀで当たり判定
		{
			MinoSaveRev();  // 当てっていればﾊﾞｯｸｱｯﾌﾟで上書き
			MinoData();		// ﾃﾞｰﾀ保存
			MapData();		// ﾏｯﾌﾟﾃﾞｰﾀへの保存
		}
		else
		{
			MinoData();			// 当たっていなければそのまま保存
		}
	}

	// キー情報の左右移動処理
	if (blockType[typeBlock].flag)
	{
		MinoSave();			// 移動前のﾐﾉ情報保存
		KeyMoveMinoLR();	// ｷｰ操作
		MinoData();			// ﾃﾞｰﾀ保存
		// 当たり判定
		if (HitCheckMove())	// 保存したﾃﾞｰﾀで当たり判定
		{
			MinoSaveRev();  // 当てっていればﾊﾞｯｸｱｯﾌﾟで上書き
		}
		else
		{
			// 音再生
			if (keyDownTrigger[KEY_ID_RIGHT] || keyDownTrigger[KEY_ID_LEFT])
			{
				PlaySoundFile("sound/move.mp3", DX_PLAYTYPE_BACK);
			}
		}
		MinoData();			// 当たっていなければそのまま保存
	}

	// 予測落下地点決定
	MinoPreDown();

	// 最下移動処理
	KeyMoveMinoHardDown();

	// 画面揺らし
	ShakeBlock();
}


// ﾐﾉ自動落下
void AutoMoveMino(void)
{
	minoCnt++;
	if (minoCnt % 70 == 0)
	{
		blockType[typeBlock].pos.y++;
	}
}


// ﾐﾉ左右移動制御
void KeyMoveMinoLR(void)
{
	if (keyDownTrigger[KEY_ID_RIGHT])
	{
		blockType[typeBlock].pos.x++;
	}

	if (keyDownTrigger[KEY_ID_LEFT])
	{
		blockType[typeBlock].pos.x--;
	}
}


// ﾐﾉ下移動制御
void KeyMoveMinoDown(void)
{
	if (keyDownTrigger[KEY_ID_DOWN])
	{
		blockType[typeBlock].pos.y++;
	}
}


// ﾐﾉ最下移動制御
void KeyMoveMinoHardDown(void)
{
	if (keyDownTrigger[KEY_ID_SPACE])
	{
		for (int x = 0; x < DATA_MAX_X; x++)
		{
			for (int y = 0; y < DATA_MAX_Y; y++)
			{
				if (downData[y][x] != -1)
				{
					mapData[y][x] = downData[y][x];
				}
			}
		}
		blockType[typeBlock].flag = false;
		putFlag = true;
		holdFlag = false;
		// 音再生
		PlaySoundFile("sound/down.mp3", DX_PLAYTYPE_BACK);
		
	}
}

// ﾐﾉ回転制御
void KeyRotaMino(void)
{
	if (keyDownTrigger[KEY_ID_Z])
	{
		if (dir > 0)
		{
			dir = (BLOCK_DIR)(dir - 1);
		}
		else
		{
			dir = DIR_3;
		}
	}

	if (keyDownTrigger[KEY_ID_X])
	{
		if (dir < DIR_3)
		{
			dir = (BLOCK_DIR)(dir + 1);
		}
		else
		{
			dir = DIR_0;
		}
	}
}


// moveDataをmapDataへ
void MapData(void)
{
	for (int x = 0; x < DATA_MAX_X; x++)
	{
		for (int y = 0; y < DATA_MAX_Y; y++)
		{
			if (moveData[y][x] != -1)
			{
				mapData[y][x] = moveData[y][x];
			}
		}
	}
	blockType[typeBlock].flag = false;
	putFlag = true;
	holdFlag = false;
}


// 当たり判定
bool HitCheckMove(void)
{
	for (int x = 0; x < DATA_MAX_X; x++)
	{
		for (int y = 0; y < DATA_MAX_Y; y++)
		{
			if (moveData[y][x] != -1 && mapData[y][x] != -1)
			{
				return true;
			}
		}
	}
	return false;
}


// ﾐﾉ消滅処理
void DisMino(void)
{
	for (int y = 10; y < DATA_MAX_Y - 1; y++)
	{
		if (DisMino2(y))	// 一行分のﾃﾞｰﾀがすべて埋まっていればtrueを返す。
		{
			lines[lineCnt] = y;	// 何行目かの保存
			lineCnt++;			// 消したﾗｲﾝ数の加算
			dontCtlTime = DONT_CTL_TIME;
			PlaySoundMem(deleteSound, DX_PLAYTYPE_BACK, true);
		}
	}



	if (putFlag)
	{
		// 消滅処理
		for (int j = 0; j < lineCnt; j++)
		{
			for (int x = 1; x < DATA_MAX_X - 1; x++)
			{
				mapData[lines[j]][x] = -1;
				line = lineCnt;
			}
		}
		// ｺﾝﾎﾞ加算
		if (line != 0)
		{
			combo++;
		}
		else
		{
			combo = 0;
		}
	}


	// 一段下げる
	if (dontCtlTime <= 1)
	{
		for (int j = 0; j < lineCnt; j++)
		{
			for (int x = 1; x < DATA_MAX_X - 1; x++)
			{
				for (int y = lines[j]; y > 8; y--)
				{
					mapData[y][x] = mapData[y - 1][x];
				}
			}
		}
	}
}


// ﾐﾉ消滅処理
bool DisMino2(int y)
{
	for (int x = 1; x < DATA_MAX_X - 1; x++)
	{
		if (mapData[y][x] == -1)
		{
			return false;
		}
	}
	return true;
}


// ﾐﾉ情報のﾊﾞｯｸｱｯﾌﾟ
void MinoSave(void)
{
	blockTypeTmp[typeBlock].pos = blockType[typeBlock].pos;
	dirTmp = dir;
}


// ﾐﾉ情報をﾊﾞｯｸｱｯﾌﾟで上書き(移動取り消し)
void MinoSaveRev(void)
{
	blockType[typeBlock].pos = blockTypeTmp[typeBlock].pos;
	dir = dirTmp;
}


// 敵の攻撃
void EnemyAtkBlock(void)
{
	int atk = 0;
	if (atkMax < 4)
	{
		atk = atkMax;
		atkMax = 0;
	}
	else
	{
		atk = 4;
		atkMax -= 4;
	}

	for (int y = 9; y < DATA_MAX_Y - 1; y++)
	{
		for (int x = 1; x < DATA_MAX_X - 1; x++)
		{
			mapData[y - atk][x] = mapData[y][x];
		}
	}

	for (int y = DATA_MAX_Y - atk - 1; y < DATA_MAX_Y - 1; y++)
	{
		for (int x = 1; x < DATA_MAX_X - 1; x++)
		{
			mapData[y][x] = -1;
		}
	}

	int randLine = (rand() % 10) + 1;
	for (int y = DATA_MAX_Y - atk - 1; y < DATA_MAX_Y - 1; y++)
	{
		for (int x = 1; x < DATA_MAX_X - 1; x++)
		{
			if (x != randLine)
			{
				mapData[y][x] = 7;
			}
		}
	}

	// ﾗｲﾝを上げる
	for (int j = 0; j < lineCnt; j++)
	{
		lines[j] -= atk;
	}

	// ﾑｰﾌﾞﾃﾞｰﾀ補正(特殊スピン系)
	//if (HitCheckMove())
	//{
	//	while (HitCheckMove())
	//	{
	//		blockType[typeBlock].pos.y--;
	//		MinoData();
	//	}
	//	MapData();
	//}
	// 僕には難しかった...by津田。
}


// ﾐﾉの予測落下地点
void MinoPreDown(void)
{
	if (blockType[typeBlock].flag)
	{
		// 座標代入
		blockTypeDown[typeBlock].pos = blockType[typeBlock].pos;

		// 当たるまでY座標を+
		while (!HitCheckPreDown())
		{
			blockTypeDown[typeBlock].pos.y++;

			for (int x = 0; x < DATA_MAX_X; x++)
			{
				for (int y = 0; y < DATA_MAX_Y; y++)
				{
					downData[y][x] = -1;
				}
			}

			for (int y = 0; y < 4; y++)
			{
				for (int x = 0; x < 4; x++)
				{
					if (blockTypeDown[typeBlock].block[dir][y][x] != -1)
					{
						downData[blockTypeDown[typeBlock].pos.y + y][blockTypeDown[typeBlock].pos.x + x] = typeBlock;
					}
				}
			}
		}
		
		// 当たった後の座標補正
		blockTypeDown[typeBlock].pos.y--;


		// Downに保存
		for (int x = 0; x < DATA_MAX_X; x++)
		{
			for (int y = 0; y < DATA_MAX_Y; y++)
			{
				downData[y][x] = -1;
			}
		}

		for (int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				if (blockTypeDown[typeBlock].block[dir][y][x] != -1)
				{
					downData[blockTypeDown[typeBlock].pos.y + y][blockTypeDown[typeBlock].pos.x + x] = typeBlock;
				}
			}
		}
	}
}


// 当たり判定最下落下用
bool HitCheckPreDown(void)
{
	for (int x = 0; x < DATA_MAX_X; x++)
	{
		for (int y = 0; y < DATA_MAX_Y; y++)
		{
			if (downData[y][x] != -1 && mapData[y][x] != -1)
			{
				return true;
			}
		}
	}
	return false;
}

// 画面揺らし
void ShakeBlock(void)
{
	if (shakeFlag)
	{
		shakeCnt++;
		if (shakeCnt < 60)
		{
			if (shakeLR)
			{
				if (shakePosX > -6)
				{
					shakePosX -= 2;
				}
				else
				{
					shakeLR = !shakeLR;
				}
			}
			else
			{
				if (shakePosX < 6)
				{
					shakePosX += 2;
				}
				else
				{
					shakeLR = !shakeLR;
				}
			}
		}
		else
		{
			shakeFlag = false;
			shakePosX = 0;
		}
	}
}


void TetrisDraw(void)
{
	// ﾑｰﾌﾞﾃﾞｰﾀ
	if (blockType[typeBlock].flag)
	{
		for (int y = 10; y < DATA_MAX_Y - 1; y++)
		{
			for (int x = 1; x < DATA_MAX_X - 1; x++)
			{
				if (moveData[y][x] != -1)
				{
					DrawGraph((x - 1) * MINO_SIZE_X + 152, (y - 10) * MINO_SIZE_Y + 16, minoImage[moveData[y][x]], true);
				}
			}
		}
	}


	// 固定ﾃﾞｰﾀ
	for (int y = 10; y < DATA_MAX_Y - 1; y++)
	{
		for (int x = 1; x < DATA_MAX_X - 1; x++)
		{
			if (mapData[y][x] != -1)
			{
				DrawGraph((x - 1) * MINO_SIZE_X + 152 + shakePosX, (y - 10) * MINO_SIZE_Y + 16, minoImage[mapData[y][x]], true);
			}
		}
	}

	if (gameoverFlag)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);

		for (int y = 10; y < DATA_MAX_Y - 1; y++)
		{
			for (int x = 1; x < DATA_MAX_X - 1; x++)
			{
				if (mapData[y][x] != -1)
				{
					DrawBox((x - 1) * MINO_SIZE_X + 152, (y - 10) * MINO_SIZE_Y + 16, 
						(x - 1) * MINO_SIZE_X + 152 + MINO_SIZE_X, (y - 10) * MINO_SIZE_Y + 16 + MINO_SIZE_Y,
						0x000000, true);
				}
			}
		}

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}


	// next
	for (int i = 0; i < BLOCK_TYPE_MAX; i++)
	{
		for (int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				if (blockType[next[i]].block[DIR_0][y][x] != -1)
				{
					DrawExtendGraph(x * (MINO_SIZE_X / 2) + 628 - MINO_SIZE_X,
						y * (MINO_SIZE_Y / 2) + 120 - (MINO_SIZE_Y / 2) + (MINO_SIZE_Y * 5 / 2) * i,
						x * (MINO_SIZE_X / 2) + 628 + (MINO_SIZE_X / 2) - MINO_SIZE_X,
						y * (MINO_SIZE_Y / 2) + 120 + (MINO_SIZE_Y / 2) - (MINO_SIZE_Y / 2) + (MINO_SIZE_Y * 5 / 2) * i,
						minoImage[next[i]], true);
				}
			}
		}	
	}



	// hold
	if (hold != -1)
	{
		for (int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				if (blockType[hold].block[DIR_0][y][x] != -1)
				{
					DrawExtendGraph(x * (MINO_SIZE_X / 2) + 76 - MINO_SIZE_X,
						y * (MINO_SIZE_Y / 2) + 135 - (MINO_SIZE_Y / 2),
						x * (MINO_SIZE_X / 2) + 76 + (MINO_SIZE_X / 2) - MINO_SIZE_X,
						y * (MINO_SIZE_Y / 2) + 135 + (MINO_SIZE_Y / 2) - (MINO_SIZE_Y / 2),
						minoImage[hold], true);
				}
			}
		}
	}


	// 予測落下地点表示
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);

	if (blockType[typeBlock].flag)
	{
		for (int y = 10; y < DATA_MAX_Y - 1; y++)
		{
			for (int x = 1; x < DATA_MAX_X - 1; x++)
			{
				if (downData[y][x] != -1)
				{
					DrawGraph((x - 1) * MINO_SIZE_X + 152, (y - 10) * MINO_SIZE_Y + 16, minoImage[downData[y][x]], true);
				}
			}
		}
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


	// ｺﾝﾎﾞ数表示
	if (combo > 0)
	{
		SetFontSize(70);
		DrawFormatString(405, 105, 0x000000, "%dRen", combo, true);
		DrawFormatString(400, 100, 0x00FFFF, "%dRen", combo, true);
	}

	// 攻撃列数表示
	if (atkMax > 0)
	{
		for (int i = 0; i < atkMax; i++)
		{
			DrawGraph(56, 776 - (i * MINO_SIZE_Y), minoImage[7], true);
		}
	}
	

	// ﾁｬｰｼﾞ攻撃表示
	for (int i = 0; i < charge; i++)
	{
		DrawGraph(16 + (i * MINO_SIZE_X), 838, minoImage[0], true);
	}
	if (charge < 10)	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	if (charge >= 10)	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);
	for (int i = 0; i < charge; i++)
	{
		DrawBox(16 + (i * MINO_SIZE_X), 838,
			16 + (i * MINO_SIZE_X) + MINO_SIZE_X, 838 + MINO_SIZE_Y, 0x000000, true);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	if (charge >= 10)
	{
		if (chargeBringFlag)
		{
			chargeBring += 2;
			if (chargeBring > 200)
			{
				chargeBringFlag = false;
			}
		}
		else
		{
			chargeBring -= 2;
			if (chargeBring < 100)
			{
				chargeBringFlag = true;
			}
		}
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, chargeBring);
		for (int i = 0; i < charge; i++)
		{
			DrawBox(16 + (i * MINO_SIZE_X), 838, 
				16 + (i * MINO_SIZE_X) + MINO_SIZE_X, 838 + MINO_SIZE_Y, 0xFFFFFF, true);
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}



int TetrisLine(void)
{
	return line;
}

int TetrisCombo(void)
{
	return combo;
}

bool Gameover(void)
{
	return gameoverFlag;
}
