#include "Dxlib.h"	
#include "main.h"
#include "keycheck.h"
#include "enemy.h"


//int enemyImage;
int enemyLife;
int enemyAttack;


bool EnemySysInit(void)
{
	bool rtnFlag = true;

	return rtnFlag;
}

void EnemyInit(void)
{
	
	enemyLife = 500;
	enemyAttack = 600;
}

void EnemyCtl(void)
{
	//int damage = DamageCalc();
	//if(enemyLife > 0)	enemyLife = enemyLife - damage;

}

void EnemyDraw(void)
{
	// “G‚Ì‘Ì—ÍƒQ[ƒW
	DrawFormatString(900, 30, 0xFFFFFF, "100/100");
	/*DrawBox(900, 90, 1300, 120, 0x000000, true);
	DrawBox(900, 90, 1300, 120, 0x00FF00, true);
	DrawBox(900, 90, 1300, 120, 0xFFFFFF, false);*/

	// “G‚ÌUŒ‚ƒQ[ƒW
	/*DrawBox(800, 820, 1400, 850, 0x000000, true);
	DrawBox(800, 820, 1400, 850, 0xFF0000, true);
	DrawBox(800, 820, 1400, 850, 0xFFFFFF, false);*/

	if (enemyLife > 0)
	{
		// “G‚Ì‘ã‚í‚è
		DrawBox(1000, 500, 1200, 800, 0xFFFFFF, true);
	}

}



