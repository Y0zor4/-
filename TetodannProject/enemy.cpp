#include "Dxlib.h"	
#include "main.h"
#include "keycheck.h"
#include "enemy.h"

// �ϐ�
ENEMY enemy[ENEMY_MAX];

int fmFlag_enemy;

SPARK Spark[MAX_SPARK];	// �Ήԃf�[�^

// �G�̃V�X�e���n������
bool EnemySysInit(void)
{
	bool rtnFlag = true;
	enemy[0].image = LoadGraph("image/slime1.png");
	enemy[1].image = LoadGraph("image/slime2.png");
	enemy[2].image = LoadGraph("image/slime3.png");
	enemy[3].image = LoadGraph("image/slime4.png");
	enemy[4].image = LoadGraph("image/slime5.png");

	// ������
	for (int e = 5; e < ENEMY_MAX; e++)
	{
		int i = rand() % 5;
		enemy[e].image = enemy[i].image;
	}

	// �ΉԂ̑��݂�����������
	for (int i = 0; i < MAX_SPARK; i++)
		Spark[i].Valid = 0;

	return rtnFlag;
}

// �G������
void EnemyInit(void)
{
	for (int e = 0; e < ENEMY_MAX; e++)
	{
		enemy[e].LifeMax = 100 * (e + 1);
		enemy[e].Life = enemy[e].LifeMax;
		enemy[e].Attack = 1;
		enemy[e].CntMax = 500;
		enemy[e].Cnt = enemy[e].CntMax;
		enemy[e].Appear = 0;
	}

	fmFlag_enemy = false;
}

// �G�̍s������
int EnemyCtl(int damage, int floor, bool flag)
{
	fmFlag_enemy = flag;
	if (fmFlag_enemy)
	{
		return 0;
	}

	int i, j, R;
	// �G�̗͌�������
	if (enemy[floor - 1].Life > 0)
	{
		enemy[floor - 1].Life = enemy[floor - 1].Life - damage;
		// �ΉԂ��o�������Z�b�g
		R = GetRand(60);
		for (j = 0; j < R; j++)
		{
			// �ΉԂ𐶐�
			CreateSpark(1000 + j, 500 + j);
		}
	}
	
	if (enemy[floor - 1].Life <= 0)
	{
		enemy[floor - 1].Life = 0;
		flag = false;
	}
	
	return enemy[floor - 1].Life;
}

// �G�̕`��
void EnemyDraw(int floor)
{

	if (enemy[floor - 1].Life > 0)
	{
		enemy[floor - 1].Appear += 10;
		if (enemy[floor - 1].Appear >= 255)
		{
			enemy[floor - 1].Appear = 255;
		}
	}
	else
	{
		enemy[floor - 1].Appear -= 2;
		if (enemy[floor - 1].Appear <= 0)
		{
			enemy[floor - 1].Appear = 0;
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, enemy[floor - 1].Appear);
	DrawGraph(712, 176, enemy[floor - 1].image, true);
	//DrawBox(1000, 500, 1200, 800, 0xFFFFFF, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


	if (fmFlag_enemy)
	{
		return;
	}
	// �ΉԂ�`�悷��
	for (int j = 0; j < MAX_SPARK; j++)
	{
		// �Ήԃf�[�^���L���Ȏ��̂ݕ`��
		if (Spark[j].Valid == 1)
			DrawPixel(Spark[j].X / 100, Spark[j].Y / 100,
				GetColor(Spark[j].Bright, Spark[j].Bright, Spark[j].Bright));

	}

	// �G�̗̑̓Q�[�W (��ɕύX�L)
	DrawBox(750, 90, 1350, 130, 0x000000, true);
	DrawBox(750, 90, 600 * enemy[floor - 1].Life / enemy[floor - 1].LifeMax + 750, 130, 0x00FF00, true);
	DrawBox(750, 90, 1350, 130, 0xFFFFFF, false);

	// �G�̍U���Q�[�W�i��ɕύX�L�j
	DrawBox(800, 820, 1400, 850, 0x000000, true);
	DrawBox(800, 820, 600 * enemy[floor - 1].Cnt / enemy[floor - 1].CntMax + 800, 850, 0xFF0000, true);
	DrawBox(800, 820, 1400, 850, 0xFFFFFF, false);

	
	// �G�̗̑͐��l
	DrawFormatString(900, 30, 0xFFFFFF, "HP:%d/%d", enemy[floor - 1].Life, enemy[floor - 1].LifeMax);




}


int GetEnemyLife(void)
{
	return enemy[0].LifeMax;
}

int GetAttackLines(int floor)
{
	if (fmFlag_enemy)
	{
		return 0;
	}

	
	if (enemy[floor - 1].Appear == 255)
	{
		// �G�̍U���֘A
		if (enemy[floor - 1].Cnt > 0)enemy[floor - 1].Cnt--;

		if (enemy[floor - 1].Cnt <= 0)
		{
			enemy[floor - 1].Cnt = enemy[floor - 1].CntMax;
			return enemy[floor - 1].Attack;
		}
	}
	return 0;
}



// ���݂̓G�̕\����Ԃ�Ԃ��B
bool GetEnemyBlend(int floor)
{
	if (enemy[floor - 1].Appear == 0)
	{
 		return false;
	}
	return true;
}


// �ΉԂ��o������
void CreateSpark(int x, int y)
{
	int i;

	// �g���Ă��Ȃ��Ήԃf�[�^��T��
	for (i = 0; i < MAX_SPARK; i++)
	{
		if (Spark[i].Valid == 0) break;
	}

	// �����g���Ă��Ȃ��Ήԃf�[�^����������ΉԂ��o��
	if (i != MAX_SPARK)
	{
		// �ΉԂ̈ʒu��ݒ�
		Spark[i].X = x * 100;
		Spark[i].Y = y * 100;

		// �ړ��͂�ݒ�
		Spark[i].Sx = GetRand(1000) - 500;
		Spark[i].Sy = -GetRand(500);

		// �ΉԂ̏d�����Z�b�g
		Spark[i].G = GetRand(10);

		// �ΉԂ̖��邳�Z�b�g
		Spark[i].Bright = 255;

		// �Ήԃf�[�^���g�p���ɃZ�b�g
		Spark[i].Valid = 1;
	}
}