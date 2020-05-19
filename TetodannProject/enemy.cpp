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
		enemy[e].LifeMax = 100 * (e + 1);
		enemy[e].Life = enemy[e].LifeMax;
		enemy[e].Attack = 1;
		//enemy[e].CntMax = 300;
		enemy[e].CntMax = 10;
		enemy[e].Cnt = enemy[e].CntMax;
	}
}

// “G‚Ìs“®§Œä
int EnemyCtl(int damage, int floor)
{
	
	// “G‘Ì—ÍŒ¸­ˆ—
	if (enemy[floor - 1].Life > 0)enemy[floor - 1].Life = enemy[floor - 1].Life - damage;

	// “G‚ÌUŒ‚ŠÖ˜A
	if (enemy[floor - 1].Cnt > 0)enemy[floor - 1].Cnt--;

	return enemy[floor - 1].Life;
}

// “G‚Ì•`‰æ
void EnemyDraw(int floor)
{
	// “G‚Ì‘Ì—ÍƒQ[ƒW (Œã‚É•ÏX—L)
	DrawBox(750, 90, 1350, 130, 0x000000, true);
	DrawBox(750, 90, 600 * enemy[floor - 1].Life / enemy[floor - 1].LifeMax + 750, 130, 0x00FF00, true);
	DrawBox(750, 90, 1350, 130, 0xFFFFFF, false);

	// “G‚ÌUŒ‚ƒQ[ƒWiŒã‚É•ÏX—Lj
	DrawBox(800, 820, 1400, 850, 0x000000, true);
	DrawBox(800, 820, 600 * enemy[floor - 1].Cnt / enemy[floor - 1].CntMax + 800, 850, 0xFF0000, true);
	DrawBox(800, 820, 1400, 850, 0xFFFFFF, false);

	
	// “G‚Ì‘Ì—Í”’l
	DrawFormatString(900, 30, 0xFFFFFF, "HP:%d/%d", enemy[floor - 1].Life, enemy[floor - 1].LifeMax);


	if (enemy[floor].Life > 0)
	{
		// “G‚Ì‘ã‚í‚è(Œã‚É‰æ‘œ‚Æ·‚µ‘Ö‚¦)
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



