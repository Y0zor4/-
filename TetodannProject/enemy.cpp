#include "Dxlib.h"	
#include "main.h"
#include "keycheck.h"
#include "enemy.h"

ENEMY enemy;
//int enemyImage[];


bool EnemySysInit(void)
{
	bool rtnFlag = true;

	return rtnFlag;
}

void EnemyInit(void)
{
	enemy.LifeMax = 500;
	enemy.Life = enemy.LifeMax;
	enemy.Attack = 2;
	enemy.cnt = 4;
}

void EnemyCtl(int damage)
{
	if(enemy.Life > 0)enemy.Life = enemy.Life - damage;

}

void EnemyDraw(void)
{
	// “G‚Ì‘Ì—Í”’l
	DrawFormatString(900, 30, 0xFFFFFF, "HP:%d/%d", enemy.Life, enemy.LifeMax);
	
	// “G‚Ì‘Ì—ÍƒQ[ƒW
	DrawBox(700, 90, 1300, 130, 0x000000, true);
	DrawBox(700, 90, 1300, 130, 0x00FF00, true);
	DrawBox(700, 90, 1300, 130, 0xFFFFFF, false);

	// “G‚ÌUŒ‚ƒQ[ƒW
	DrawBox(800, 820, 1400, 850, 0x000000, true);
	DrawBox(800, 820, 1400, 850, 0xFF0000, true);
	DrawBox(800, 820, 1400, 850, 0xFFFFFF, false);

	if (enemy.Life > 0)
	{
		// “G‚Ì‘ã‚í‚è
		DrawBox(1000, 500, 1200, 800, 0xFFFFFF, true);
	}

}



