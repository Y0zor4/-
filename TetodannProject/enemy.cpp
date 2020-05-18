#include "Dxlib.h"	
#include "main.h"
#include "keycheck.h"
#include "enemy.h"

// •Ï”
ENEMY enemy[ENEMY_MAX];
//int enemyImage[];

// “G‚ÌƒVƒXƒeƒ€Œn‰Šú‰»
bool EnemySysInit(void)
{
	bool rtnFlag = true;

	return rtnFlag;
}

// “G‰Šú‰»
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

// “G‚Ìs“®§Œä
int EnemyCtl(int damage, int floor)
{
	for (int e = 0; e < ENEMY_MAX; e++)
	{
		// “G‘Ì—ÍŒ¸­ˆ—
		if (enemy[e].Life > 0)enemy[e].Life = enemy[e].Life - damage;

		// “G‚ÌUŒ‚ŠÖ˜A
		if (enemy[e].Cnt > 0)enemy[e].Cnt--;
		if (enemy[e].Cnt <= 0)
		{
			// “G‚ÌUŒ‚ˆ—iƒeƒgƒŠƒ~ƒm‚ğUŒ‚—Í•ª—N‚©‚¹‚éj
			// = enemy[e].Attack;

			enemy[e].Cnt = enemy[e].CntMax;
		}
	}
	return enemy->Life;
}

// “G‚Ì•`‰æ
void EnemyDraw(void)
{
	for (int e = 0; e < ENEMY_MAX; e++)
	{
		// “G‚Ì‘Ì—ÍƒQ[ƒW (Œã‚É•ÏX—L)
		DrawBox(700, 90, 1300, 130, 0x000000, true);
		DrawBox(700, 90, 1300, 130, 0x00FF00, true);
		DrawBox(700, 90, 1300, 130, 0xFFFFFF, false);

		// “G‚ÌUŒ‚ƒQ[ƒWiŒã‚É•ÏX—Lj
		DrawBox(800, 820, 1400, 850, 0x000000, true);
		DrawBox(800, 820, 1400 - (1400 / enemy[e].Cnt), 850, 0xFF0000, true);
		DrawBox(800, 820, 1400, 850, 0xFFFFFF, false);

	
		// “G‚Ì‘Ì—Í”’l
		DrawFormatString(900, 30, 0xFFFFFF, "HP:%d/%d", enemy[e].Life, enemy[e].LifeMax);


		if (enemy[e].Life > 0)
		{
			// “G‚Ì‘ã‚í‚è(Œã‚É‰æ‘œ‚Æ·‚µ‘Ö‚¦)
			DrawBox(1000, 500, 1200, 800, 0xFFFFFF, true);
		}
	}
}



