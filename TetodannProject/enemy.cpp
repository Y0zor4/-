#include "Dxlib.h"	
#include "main.h"
#include "keycheck.h"
#include "enemy.h"

// 変数
ENEMY enemy[ENEMY_MAX];
//int enemyImage[];

// 敵のシステム系初期化
bool EnemySysInit(void)
{
	bool rtnFlag = true;

	return rtnFlag;
}

// 敵初期化
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

// 敵の行動制御
int EnemyCtl(int damage, int floor)
{
	
	// 敵体力減少処理
	if (enemy[floor - 1].Life > 0)enemy[floor - 1].Life = enemy[floor - 1].Life - damage;

	// 敵の攻撃関連
	if (enemy[floor - 1].Cnt > 0)enemy[floor - 1].Cnt--;

	return enemy[floor - 1].Life;
}

// 敵の描画
void EnemyDraw(int floor)
{
	// 敵の体力ゲージ (後に変更有)
	DrawBox(750, 90, 1350, 130, 0x000000, true);
	DrawBox(750, 90, 600 * enemy[floor - 1].Life / enemy[floor - 1].LifeMax + 750, 130, 0x00FF00, true);
	DrawBox(750, 90, 1350, 130, 0xFFFFFF, false);

	// 敵の攻撃ゲージ（後に変更有）
	DrawBox(800, 820, 1400, 850, 0x000000, true);
	DrawBox(800, 820, 600 * enemy[floor - 1].Cnt / enemy[floor - 1].CntMax + 800, 850, 0xFF0000, true);
	DrawBox(800, 820, 1400, 850, 0xFFFFFF, false);

	
	// 敵の体力数値
	DrawFormatString(900, 30, 0xFFFFFF, "HP:%d/%d", enemy[floor - 1].Life, enemy[floor - 1].LifeMax);


	if (enemy[floor].Life > 0)
	{
		// 敵の代わり(後に画像と差し替え)
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



