#include "Dxlib.h"	
#include "main.h"
#include "keycheck.h"
#include "tetris.h"

int minoImage[MINO_MAX];					// �ɉ摜

int mapData[DATA_MAX_Y][DATA_MAX_X];		// ϯ���ް��i�[�p

int moveData[DATA_MAX_Y][DATA_MAX_X];		// ϯ���ް��ɑ΂����ɂ̏��i�[�p

int typeBlock;								// ��ۯ��̎�ފi�[�p
BLOCK_DIR dir;								// ��ۯ��̌����i�[�p
BLOCK_DIR dirTmp;							// ��ۯ��̌����i�[�p�ޯ�����

BLOCK blockType[BLOCK_TYPE_MAX];			// �ړ������ɏ��i�[�p
BLOCK blockTypeTmp[BLOCK_TYPE_MAX];			// �ړ������ɏ��i�[�p�ޯ�����

BLOCK_TYPE next[BLOCK_TYPE_MAX];
BLOCK_TYPE next2[BLOCK_TYPE_MAX];





// ��ؽ�֘A���ьn������
bool TetrisSysInit(void)
{
	bool rtnFlag = true;

	MinoInit();

	LoadDivGraph("Image/mino.png", MINO_MAX, MINO_MAX, 1, MINO_SIZE_X, MINO_SIZE_Y, &minoImage[0]);

	return rtnFlag;
}


// ��ؽ�֘A������
void TetrisInit(void)
{
	for (int x = 0; x < DATA_MAX_X; x++)
	{
		for (int y = 0; y < DATA_MAX_Y; y++)
		{
			moveData[y][x] = -1;
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


	// �ɏ�����
	blockType[typeBlock].flag = false;	
}


// �ɏ�񏉊���
void MinoInit(void)
{
	// �ް��i�[
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


	// �ޯ����ߗp�̕ϐ��ɂ��i�[
	for (int a = 0; a < BLOCK_TYPE_MAX; a++)
	{
		for (int b = 0; b < DIR_MAX; b++)
		{
			for (int c = 0; c < 4; c++)
			{
				for (int d = 0; d < 4; d++)
				{
					blockTypeTmp[a].block[b][c][d] = blockType[a].block[b][c][d];
				}
			}
		}
	}
}



void TetrisCtl(int atk)
{
	// �������u���b�N�����邩�ǂ����̃`�F�b�N
	if (!blockType[typeBlock].flag)
	{
		CreateMino();			// �Ȃ���Ώo������
	}


	// next2����ł���΁A��[�̏���




	// �ړ��A��]�A�����蔻��
	MoveMino();				
	
	


	// �ɐ؂�ւ�
	if (CheckHitKey(KEY_INPUT_NUMPAD0))
	{
		blockType[typeBlock].flag = false;
	}
}


// �ɏo��
void CreateMino(void)
{
	typeBlock = rand() % BLOCK_TYPE_MAX;
	blockType[typeBlock].pos.x = 4;
	blockType[typeBlock].pos.y = 9;
	dir = DIR_0;
	blockType[typeBlock].flag = true;
}


// �ɏ���moveData��
void MinoData(void)
{
	// ��x������
	for (int x = 0; x < DATA_MAX_X; x++)
	{
		for (int y = 0; y < DATA_MAX_Y; y++)
		{
			moveData[y][x] = -1;
		}
	}

	// ���f
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


// �ɂ̐���
void MoveMino(void)
{
	// �����̈ړ�����
	if (blockType[typeBlock].flag)
	{
		MinoSave();			// �ړ��O���ɏ��ۑ�
		AutoMoveMino();			// ��������
		MinoData();			// �ް��ۑ�
		if (HitCheckMove())
		{
			MinoSaveRev();  // ���Ă��Ă�����ޯ����߂ŏ㏑��
			MinoData();		// �ް��ۑ�
			MapData();		// ϯ���ް��ւ̕ۑ�
		}
		MinoData();			// �������Ă��Ȃ���΂��̂܂ܕۑ�
	}

	// �L�[���̉��ړ�����
	if (blockType[typeBlock].flag)
	{
		MinoSave();			// �ړ��O���ɏ��ۑ�
		KeyMoveMinoDown();	// ������
		MinoData();			// �ް��ۑ�
		// �����蔻��
		if (HitCheckMove())	// �ۑ������ް��œ����蔻��
		{
			MinoSaveRev();  // ���Ă��Ă�����ޯ����߂ŏ㏑��
			MinoData();		// �ް��ۑ�
			MapData();		// ϯ���ް��ւ̕ۑ�
		}
		MinoData();			// �������Ă��Ȃ���΂��̂܂ܕۑ�
	}

	// �L�[���̍��E�ړ�����
	if (blockType[typeBlock].flag)
	{
		MinoSave();			// �ړ��O���ɏ��ۑ�
		KeyMoveMinoLR();	// ������
		MinoData();			// �ް��ۑ�
		// �����蔻��
		if (HitCheckMove())	// �ۑ������ް��œ����蔻��
		{
			MinoSaveRev();  // ���Ă��Ă�����ޯ����߂ŏ㏑��
		}
		MinoData();			// �������Ă��Ȃ���΂��̂܂ܕۑ�
	}

	// �L�[���̉�]����
	if (blockType[typeBlock].flag)
	{
		MinoSave();			// �ړ��O���ɏ��ۑ�
		KeyRotaMino();		// ������
		MinoData();			// �ް��ۑ�
		// �����蔻��
		if (HitCheckMove())	// �ۑ������ް��œ����蔻��
		{
			MinoSaveRev();  // ���Ă��Ă�����ޯ����߂ŏ㏑��
		}
		MinoData();		// �������Ă��Ȃ���΂��̂܂ܕۑ�
	}
}


// �Ɏ�������
void AutoMoveMino(void)
{

}


// �ɍ��E�ړ�����
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


// �ɉ��ړ�����
void KeyMoveMinoDown(void)
{
	if (keyDownTrigger[KEY_ID_S])
	{
		blockType[typeBlock].pos.y++;
	}
}


// �ɉ�]����
void KeyRotaMino(void)
{
	if (keyDownTrigger[KEY_ID_A])
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

	if (keyDownTrigger[KEY_ID_D])
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


// moveData��mapData��
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
}


// �����蔻��
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


// �ɏ����ޯ�����
void MinoSave(void)
{
	blockTypeTmp[typeBlock].pos = blockType[typeBlock].pos;
	dirTmp = dir;
}


// �ɏ����ޯ����߂ŏ㏑��(�ړ�������)
void MinoSaveRev(void)
{
	blockType[typeBlock].pos = blockTypeTmp[typeBlock].pos;
	dir = dirTmp;
}



void TetrisDraw(void)
{
	// Ѱ���ް�
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


	// �Œ��ް�
	for (int y = 10; y < DATA_MAX_Y - 1; y++)
	{
		for (int x = 1; x < DATA_MAX_X - 1; x++)
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

