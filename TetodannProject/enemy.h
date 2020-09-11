//#pragma once

#define ENEMY_MAX 50
#define ENEMY_POSY_F 500

struct ENEMY
{
	int Life;				// 敵の現在の体力
	int LifeMax;			// 敵の体力最大値
	int Attack;				// 敵の攻撃力（テトリミノの出現列数）
	int Cnt;				// 敵毎の攻撃速度用カウント
	int CntMax;				// 敵毎の攻撃カウント最大数
	int Flag;
	int Appear;
	int image;
};


bool EnemySysInit(void);
void EnemyInit(void);
int EnemyCtl(int damage, int floor, bool flag);
void EnemyDraw(int floor);
int GetEnemyLife(void);
int GetAttackLines(int floor);

// 現在の敵の表示状態を返す
bool GetEnemyBlend(int floor);
