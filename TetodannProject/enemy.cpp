#include "Dxlib.h"	
#include "main.h"
#include "keycheck.h"
#include "enemy.h"

// �ϐ�
ENEMY enemy[ENEMY_MAX];
//int enemyImage[];

// �G�̃V�X�e���n������
bool EnemySysInit(void)
{
	bool rtnFlag = true;

	return rtnFlag;
}

// �G������
void EnemyInit(void)
{
	for (int e = 0; e < ENEMY_MAX; e++)
	{
		enemy[e].LifeMax = 200;
		enemy[e].Life = enemy[e].LifeMax;
		enemy[e].Attack = 1;
		enemy[e].CntMax = 300;
		enemy[e].Cnt = enemy[e].CntMax;
	}
}

// �G�̍s������
int EnemyCtl(int damage, int floor)
{
	for (int e = 0; e < ENEMY_MAX; e++)
	{
		// �G�̗͌�������
		if (enemy[e].Life > 0)enemy[e].Life = enemy[e].Life - damage;

		// �G�̍U���֘A
		if (enemy[e].Cnt > 0)enemy[e].Cnt--;
		if (enemy[e].Cnt <= 0)
		{
			// �G�̍U�������i�e�g���~�m���U���͕��N������j
			// = enemy[e].Attack;

			enemy[e].Cnt = enemy[e].CntMax;
		}
	}
	return enemy->Life;
}

// �G�̕`��
void EnemyDraw(void)
{
	for (int e = 0; e < ENEMY_MAX; e++)
	{
		// �G�̗̑̓Q�[�W (��ɕύX�L)
		DrawBox(700, 90, 1300, 130, 0x000000, true);
		DrawBox(700, 90, 1300, 130, 0x00FF00, true);
		DrawBox(700, 90, 1300, 130, 0xFFFFFF, false);

		// �G�̍U���Q�[�W�i��ɕύX�L�j
		DrawBox(800, 820, 1400, 850, 0x000000, true);
		DrawBox(800, 820, 1400 - (1400 / enemy[e].Cnt), 850, 0xFF0000, true);
		DrawBox(800, 820, 1400, 850, 0xFFFFFF, false);

	
		// �G�̗̑͐��l
		DrawFormatString(900, 30, 0xFFFFFF, "HP:%d/%d", enemy[e].Life, enemy[e].LifeMax);


		if (enemy[e].Life > 0)
		{
			// �G�̑���(��ɉ摜�ƍ����ւ�)
			DrawBox(1000, 500, 1200, 800, 0xFFFFFF, true);
		}
	}
}



