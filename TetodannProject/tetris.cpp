#include "Dxlib.h"	
#include "main.h"
#include "keycheck.h"
#include "tetris.h"

int minoImage[MINO_MAX];					// �ɉ摜

int mapData[DATA_MAX_Y][DATA_MAX_X];		// ϯ���ް��i�[�p

int moveData[DATA_MAX_Y][DATA_MAX_X];		// ϯ���ް��ɑ΂����ɂ̏��i�[�p

int downData[DATA_MAX_Y][DATA_MAX_X];		// ϯ���ް��ɑ΂���\�������n�_�̏��i�[�p

int typeBlock;								// ��ۯ��̎�ފi�[�p
BLOCK_DIR dir;								// ��ۯ��̌����i�[�p
BLOCK_DIR dirTmp;							// ��ۯ��̌����i�[�p�ޯ�����

BLOCK blockType[BLOCK_TYPE_MAX];			// �ړ������ɏ��i�[�p
BLOCK blockTypeTmp[BLOCK_TYPE_MAX];			// �ړ������ɏ��i�[�p�ޯ�����
BLOCK blockTypeDown[BLOCK_TYPE_MAX];		// �\�������n�_���ɏ��i�[�p

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

// �Ɏ��������p
int minoCnt;

// �G�̍U��
int atkMax;

// ��ʗh�炵�p
int shakeCnt;
int shakePosX;
bool shakeFlag;
bool shakeLR;


// ����ލU���p
int charge;
int chargeBring;
bool chargeBringFlag;

// �ްѵ��ް�p
bool gameoverFlag;

// ���ʉ�
int chargeSound;
int blockSound;
int deleteSound;
int chargeAtkSound;




// ��ؽ�֘A���ьn������
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


// ��ؽ�֘A������
void TetrisInit(void)
{
	// Ѱ���ް��A�\�������n�_�̏�����
	for (int x = 0; x < DATA_MAX_X; x++)
	{
		for (int y = 0; y < DATA_MAX_Y; y++)
		{
			moveData[y][x] = -1;
			downData[y][x] = -1;
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
					blockTypeDown[a].block[b][c][d] = blockType[a].block[b][c][d];
				}
			}
		}
	}
}



int TetrisCtl(int atk)
{
	// ����������
	int damage = 0;
	line = 0;			// ���ڰт�ײݐ��ۑ��p
	putFlag = false;    // �����ڰтł͂܂��u���Ă��Ȃ����ߏ�����

	atkMax += atk;

	if (dontCtlTime <= 0)
	{
		for (int j = 0; j < 4; j++)
		{
			lines[j] = -1;	// �������p
		}

		dontCtlTime = 0;	// �ړ��s���Զ���
		lineCnt = 0;		// ������ײݐ��̕ۑ��p

		// �ɂ��o�����Ă��邩�ǂ���������
		if (!blockType[typeBlock].flag && !gameoverFlag)
		{
			CreateMino();		// �Ȃ���Ώo������

			MinoData();			// �ް��ۑ�
			if (HitCheckMove())
			{
				gameoverFlag = true;
			}
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

	// �G�̍U��
	if (atkMax != 0 && putFlag)
	{
		EnemyAtkBlock();
		PlaySoundMem(blockSound, DX_PLAYTYPE_BACK, true);
		shakeFlag = true;
		shakeCnt = 0;
	}
	
	// �ɍ폜
	DisMino();

	// �����
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
			// ���Đ�
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


	// �ړ��s���Ԃ̌��Z
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
		PlaySoundFile("sound/hold.mp3", DX_PLAYTYPE_BACK);
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
		else
		{
			// ���Đ�
			if (keyDownTrigger[KEY_ID_Z] || keyDownTrigger[KEY_ID_X])
			{
				PlaySoundFile("sound/move.mp3", DX_PLAYTYPE_BACK);
			}
		}
		MinoData();		// �������Ă��Ȃ���΂��̂܂ܕۑ�
	}

	// �����̈ړ�����
	if (blockType[typeBlock].flag)
	{
		MinoSave();			// �ړ��O���ɏ��ۑ�
		AutoMoveMino();		// ��������
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
		else
		{
			// ���Đ�
			if (keyDownTrigger[KEY_ID_RIGHT] || keyDownTrigger[KEY_ID_LEFT])
			{
				PlaySoundFile("sound/move.mp3", DX_PLAYTYPE_BACK);
			}
		}
		MinoData();			// �������Ă��Ȃ���΂��̂܂ܕۑ�
	}

	// �\�������n�_����
	MinoPreDown();

	// �ŉ��ړ�����
	KeyMoveMinoHardDown();

	// ��ʗh�炵
	ShakeBlock();
}


// �Ɏ�������
void AutoMoveMino(void)
{
	minoCnt++;
	if (minoCnt % 70 == 0)
	{
		blockType[typeBlock].pos.y++;
	}
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
}


// �ɍŉ��ړ�����
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
		// ���Đ�
		PlaySoundFile("sound/down.mp3", DX_PLAYTYPE_BACK);
		
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
			PlaySoundMem(deleteSound, DX_PLAYTYPE_BACK, true);
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

	// ײ݂��グ��
	for (int j = 0; j < lineCnt; j++)
	{
		lines[j] -= atk;
	}

	// Ѱ���ް��␳(����X�s���n)
	//if (HitCheckMove())
	//{
	//	while (HitCheckMove())
	//	{
	//		blockType[typeBlock].pos.y--;
	//		MinoData();
	//	}
	//	MapData();
	//}
	// �l�ɂ͓������...by�Óc�B
}


// �ɂ̗\�������n�_
void MinoPreDown(void)
{
	if (blockType[typeBlock].flag)
	{
		// ���W���
		blockTypeDown[typeBlock].pos = blockType[typeBlock].pos;

		// ������܂�Y���W��+
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
		
		// ����������̍��W�␳
		blockTypeDown[typeBlock].pos.y--;


		// Down�ɕۑ�
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


// �����蔻��ŉ������p
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

// ��ʗh�炵
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


	// �\�������n�_�\��
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


	// ���ސ��\��
	if (combo > 0)
	{
		SetFontSize(70);
		DrawFormatString(405, 105, 0x000000, "%dRen", combo, true);
		DrawFormatString(400, 100, 0x00FFFF, "%dRen", combo, true);
	}

	// �U���񐔕\��
	if (atkMax > 0)
	{
		for (int i = 0; i < atkMax; i++)
		{
			DrawGraph(56, 776 - (i * MINO_SIZE_Y), minoImage[7], true);
		}
	}
	

	// ����ލU���\��
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
