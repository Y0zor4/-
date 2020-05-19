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
		enemy[e].LifeMax = 100 * (e + 1);
		enemy[e].Life = enemy[e].LifeMax;
		enemy[e].Attack = 1;
		//enemy[e].CntMax = 300;
		enemy[e].CntMax = 10;
		enemy[e].Cnt = enemy[e].CntMax;
	}
}

// �G�̍s������
int EnemyCtl(int damage, int floor)
{
	
	// �G�̗͌�������
	if (enemy[floor - 1].Life > 0)enemy[floor - 1].Life = enemy[floor - 1].Life - damage;

	// �G�̍U���֘A
	if (enemy[floor - 1].Cnt > 0)enemy[floor - 1].Cnt--;

	return enemy[floor - 1].Life;
}

// �G�̕`��
void EnemyDraw(int floor)
{
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


	if (enemy[floor].Life > 0)
	{
		// �G�̑���(��ɉ摜�ƍ����ւ�)
		DrawBox(1000, 500, 1200, 800, 0xFFFFFF, true);
	}
	
}


int GetEnemyLife(void)
{
	return enemy[0].LifeMax;
}

int GetAttackLines(int floor)
{
	if (enemy[floor - 1].Cnt <= 0)
	{
 		enemy[floor - 1].Cnt = enemy[floor - 1].CntMax;
		return enemy[floor - 1].Attack;
	}
	return 0;
}



