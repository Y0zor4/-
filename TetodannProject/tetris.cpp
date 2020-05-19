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

int next[BLOCK_TYPE_MAX];					// next�ۑ��p
int next2[BLOCK_TYPE_MAX];					// next�ۑ��p2

int hold;									// hold�ۑ��p


// �����ڰт̏�����ײݕۑ��p
int line;

// ���s�ڂ����������ۑ��p
int lines[4];

// ������ײݐ��ۑ��p
int lineCnt;

// ���ސ��ۑ��p
int combo;

// ����s�\����
int dontCtlTime;

// �ɂ�u�������ǂ����̔���p
bool putFlag;

// hold�𗘗p�������ǂ���
bool holdFlag;




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
	// Ѱ���ް��̏�����
	for (int x = 0; x < DATA_MAX_X; x++)
	{
		for (int y = 0; y < DATA_MAX_Y; y++)
		{
			moveData[y][x] = -1;
		}
	}


	// ϯ���ް��̏�����
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


	// next������
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


	// hold������
	hold = -1;


	// �ɏ�����
	blockType[typeBlock].flag = false;	


	// ���̑��ϐ�
	line = 0;
	lineCnt = 0;
	combo = 0;
	dontCtlTime = 0;
	putFlag = false; 
	holdFlag = false;
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
	// ����������
	line = 0;			// ���ڰт�ײݐ��ۑ��p
	putFlag = false;    // �����ڰтł͂܂��u���Ă��Ȃ����ߏ�����

	if (dontCtlTime <= 0)
	{
		for (int j = 0; j < 4; j++)
		{
			lines[j] = -1;	// �������p
		}

		dontCtlTime = 0;	// �ړ��s���Զ���
		lineCnt = 0;		// ������ײݐ��̕ۑ��p

		// �ɂ��o�����Ă��邩�ǂ���������
		if (!blockType[typeBlock].flag)
		{
			CreateMino();			// �Ȃ���Ώo������
		}
	}


	// next2����ł���΁A��[�̏���
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


	// hold�p
	Hold();

	// �ړ��A��]�A�����蔻��
	MoveMino();				
	
	// �ɍ폜
	DisMino();


	// �ɐ؂�ւ�
	if (CheckHitKey(KEY_INPUT_NUMPAD0))
	{
		blockType[typeBlock].flag = false;
	}


	// �ړ��s���Ԃ̌��Z
	if (dontCtlTime >= 0)
	{
		dontCtlTime--;
	}

	if (atk != 0)
	{
		EnemyAtkBlock(atk);
	}
}


// next�p
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


// hold�p
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
	}
}


// �ɏo��
void CreateMino(void)
{
	typeBlock = next[0];
	blockType[typeBlock].pos.x = 4;
	blockType[typeBlock].pos.y = 9;
	dir = DIR_0;
	blockType[typeBlock].flag = true;

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
		else
		{
			MinoData();			// �������Ă��Ȃ���΂��̂܂ܕۑ�
		}
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
		else
		{
			MinoData();			// �������Ă��Ȃ���΂��̂܂ܕۑ�
		}
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
	if (keyDownTrigger[KEY_ID_DOWN])
	{
		blockType[typeBlock].pos.y++;
	}
	else if (keyNew[KEY_ID_SPACE])
	{
		blockType[typeBlock].pos.y++;
	}
}


// �ɉ�]����
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
	putFlag = true;
	holdFlag = false;
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


// �ɏ��ŏ���
void DisMino(void)
{
	for (int y = 10; y < DATA_MAX_Y - 1; y++)
	{
		if (DisMino2(y))	// ��s�����ް������ׂĖ��܂��Ă����true��Ԃ��B
		{
			lines[lineCnt] = y;	// ���s�ڂ��̕ۑ�
			lineCnt++;			// ������ײݐ��̉��Z
			dontCtlTime = DONT_CTL_TIME;
		}
	}



	if (putFlag)
	{
		// ���ŏ���
		for (int j = 0; j < lineCnt; j++)
		{
			for (int x = 1; x < DATA_MAX_X - 1; x++)
			{
				mapData[lines[j]][x] = -1;
				line = lineCnt;
			}
		}
		// ���މ��Z
		if (line != 0)
		{
			combo++;
		}
		else
		{
			combo = 0;
		}
	}


	// ��i������
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


// �ɏ��ŏ���
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


// �G�̍U��
void EnemyAtkBlock(int atk)
{
	for (int y = 10; y < DATA_MAX_Y - 1; y++)
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
}


void TetrisDraw(void)
{
	// Ѱ���ް�
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


	// �Œ��ް�
	for (int y = 10; y < DATA_MAX_Y - 1; y++)
	{
		for (int x = 1; x < DATA_MAX_X - 1; x++)
		{
			if (mapData[y][x] != -1)
			{
				DrawGraph((x - 1) * MINO_SIZE_X + 152, (y - 10) * MINO_SIZE_Y + 16, minoImage[mapData[y][x]], true);
			}
		}
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
}



int TetrisLine(void)
{
	return line;
}

int TetrisCombo(void)
{
	return combo;
}

