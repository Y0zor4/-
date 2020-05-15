#include "Dxlib.h"	
#include "main.h"
#include "keycheck.h"
#include "tetris.h"

int minoImage[MINO_MAX];					// ﾐﾉ画像

int mapData[DATA_MAX_Y][DATA_MAX_X];		// ﾃﾞｰﾀ格納用
int moveData[DATA_MAX_Y][DATA_MAX_X];
int moveDataTmp[DATA_MAX_Y][DATA_MAX_X];

int typeBlock;								// ﾌﾞﾛｯｸの種類格納用
BLOCK_DIR dir;								// ﾌﾞﾛｯｸの向き格納用


BLOCK_TYPE next[BLOCK_TYPE_MAX];
BLOCK_TYPE next2[BLOCK_TYPE_MAX];

BLOCK blockType[BLOCK_TYPE_MAX];



// ﾃﾄﾘｽ関連ｼｽﾃﾑ系初期化
bool TetrisSysInit(void)
{
	bool rtnFlag = true;

	MinoInit();

	LoadDivGraph("Image/mino.png", MINO_MAX, MINO_MAX, 1, MINO_SIZE_X, MINO_SIZE_Y, &minoImage[0]);

	return rtnFlag;
}


// ﾃﾄﾘｽ関連初期化
void TetrisInit(void)
{
	for (int x = 0; x < DATA_MAX_X; x++)
	{
		for (int y = 0; y < DATA_MAX_Y; y++)
		{
			moveData[y][x] = -1;
			moveDataTmp[y][x] = -1;
		}
	}


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


	// ﾐﾉ初期化
	blockType[typeBlock].flag = false;	
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
}



void TetrisCtl(int atk)
{
	// 動かすブロックがあるかどうかのチェック
	// なければ出現処理
	if (!blockType[typeBlock].flag)
	{
		CreateMino();
	}

	// next2が空であれば、補充の処理



	// 座標のバックアップ
	MinoDataTmp();
	MinoData();





	// キー情報の移動処理
	KeyMoveMino();
	// Tmpに保存
	MinoDataTmp();


	// 当たり判定

	// 当たり判定の後保存、反映
	MinoData();



	// キー情報の回転処理
	KeyRotaMino();
	// Tmpに保存
	MinoDataTmp();


	// 当たり判定

	// 当たり判定の後保存、反映
	MinoData();



	// 自動の移動処理

	// 当たり判定処理
	// 当たっていればフラグを切り替える

	// 座標の保存

	if (CheckHitKey(KEY_INPUT_NUMPAD0))
	{
		blockType[typeBlock].flag = false;
	}
}


// ﾐﾉ出現
void CreateMino(void)
{
	typeBlock = rand() % BLOCK_TYPE_MAX;
	blockType[typeBlock].pos.x = 4;
	blockType[typeBlock].pos.y = 9;
	dir = DIR_0;
	blockType[typeBlock].flag = true;
}


// ﾐﾉ情報をmoveDataTmpへ
void MinoDataTmp(void)
{
	// 一度初期化
	for (int x = 0; x < DATA_MAX_X; x++)
	{
		for (int y = 0; y < DATA_MAX_Y; y++)
		{
			moveDataTmp[y][x] = -1;
		}
	}

	// 反映
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (blockType[typeBlock].block[dir][y][x] != -1)
			{
				moveDataTmp[blockType[typeBlock].pos.y + y][blockType[typeBlock].pos.x + x] = typeBlock;
			}
		}
	}
}


// tmp情報をmoveDataへ
void MinoData(void)
{
	for (int x = 0; x < DATA_MAX_X; x++)
	{
		for (int y = 0; y < DATA_MAX_Y; y++)
		{
			moveData[y][x] = moveDataTmp[y][x];
		}
	}
}



// ﾐﾉ自動落下
void MoveMino(void)
{

}


// ﾐﾉ移動制御
void KeyMoveMino(void)
{
	if (keyDownTrigger[KEY_ID_DOWN])
	{
		blockType[typeBlock].pos.y++;
	}

	if (keyDownTrigger[KEY_ID_RIGHT])
	{
		blockType[typeBlock].pos.x++;
	}

	if (keyDownTrigger[KEY_ID_LEFT])
	{
		blockType[typeBlock].pos.x--;
	}
}


// ﾐﾉ回転制御
void KeyRotaMino(void)
{
	if (keyDownTrigger[KEY_ID_A])
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

	if (keyDownTrigger[KEY_ID_D])
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
}



// 当たり判定
void HitCheckMove(void)
{
	for (int x = 0; x < DATA_MAX_X; x++)
	{
		for (int y = 0; y < DATA_MAX_Y; y++)
		{
			if (moveDataTmp[y][x] != -1 && mapData[y][x] != -1)
			{

			}
		}
	}
}



void TetrisDraw(void)
{
	// ﾑｰﾌﾞﾃﾞｰﾀ
	for (int y = 10; y < DATA_MAX_Y - 1; y++)
	{
		for (int x = 1; x < DATA_MAX_X - 1; x++)
		{
			if (moveData[y][x] != -1)
			{
				DrawGraph((x - 1) * MINO_SIZE_X + 16, (y - 10) * MINO_SIZE_Y + 16, minoImage[moveData[y][x]], true);
			}
		}
	}


	// 固定ﾃﾞｰﾀ
	for (int y = 0; y < DATA_MAX_Y; y++)
	{
		for (int x = 0; x < DATA_MAX_X; x++)
		{
			if (mapData[y][x] != -1)
			{
				DrawGraph((x - 1) * MINO_SIZE_X + 16, (y - 10) * MINO_SIZE_Y + 16, minoImage[mapData[y][x]], true);
			}
		}
	}
}

int TetrisLine(void)
{
	int line = 0;
	return line;
}

int TetrisCombo(void)
{
	int combo = 0;
	return combo;
}
