#include "Dxlib.h"	
#include "main.h"
#include "keycheck.h"
#include "enemy.h"


int enemyImage;
int enemyLife;
int enemyAttack;


bool EnemySysInit(void)
{
	bool rtnFlag = true;

	return rtnFlag;
}

void EnemyInit(void)
{

}

void EnemyCtl(void)
{
	//int damage = DamageCalc();
}

void EnemyDraw(void)
{
	// �G�̗̑̓Q�[�W
	DrawBox(900, 90, 1300, 120, 0x000000, true);
	DrawBox(900, 90, 1300, 120, 0x00FF00, true);
	DrawBox(900, 90, 1300, 120, 0xFFFFFF, false);

	// �G�̍U���Q�[�W
	DrawBox(900, 820, 1300, 850, 0x000000, true);
	DrawBox(900, 820, 1300, 850, 0xFF0000, true);
	DrawBox(900, 820, 1300, 850, 0xFFFFFF, false);


	DrawFormatString(900, 30, 0xFFFFFF, "100/100");


}



