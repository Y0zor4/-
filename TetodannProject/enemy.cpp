#include "Dxlib.h"	
#include "main.h"
#include "keycheck.h"
#include "enemy.h"


ENEMY enemy[ENEMY_MAX];
//int enemyImage[];


bool EnemySysInit(void)
{
	bool rtnFlag = true;

	return rtnFlag;
}

void EnemyInit(void)
{
	for (int e = 0; e < ENEMY_MAX; e++)
	{
		enemy[e].LifeMax = 200;
		enemy[e].Life = enemy[e].LifeMax;
		enemy[e].Attack = 1;
		enemy[e].cnt = 5;
	}
}

void EnemyCtl(int damage)
{
	for (int e = 0; e < ENEMY_MAX; e++)
	{
		if (enemy[0].Life > 0)enemy[0].Life = enemy[0].Life - damage;
	}
}

void EnemyDraw(void)
{
	
	// ìGÇÃëÃóÕÉQÅ[ÉW
	DrawBox(700, 90, 1300, 130, 0x000000, true);
	DrawBox(700, 90, 1300, 130, 0x00FF00, true);
	DrawBox(700, 90, 1300, 130, 0xFFFFFF, false);

	// ìGÇÃçUåÇÉQÅ[ÉW
	DrawBox(800, 820, 1400, 850, 0x000000, true);
	DrawBox(800, 820, 1400, 850, 0xFF0000, true);
	DrawBox(800, 820, 1400, 850, 0xFFFFFF, false);

	for (int e = 0; e < ENEMY_MAX; e++)
	{
		// ìGÇÃëÃóÕêîíl
		DrawFormatString(900, 30, 0xFFFFFF, "HP:%d/%d", enemy[e].Life, enemy[e].LifeMax);

		if (enemy[e].Life > 0)
		{
			// ìGÇÃë„ÇÌÇË
			DrawBox(1000, 500, 1200, 800, 0xFFFFFF, true);
		}
	}
}



