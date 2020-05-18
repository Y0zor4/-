//#pragma once

#define ENEMY_MAX 50


struct ENEMY
{
	//int charType;			// 敵キャラの種類
	int Life;				// 敵の現在の体力
	int LifeMax;			// 敵の体力最大値
	int Attack;				// 敵の攻撃力（テトリミノの出現数）
	int Cnt;				// 敵毎の攻撃速度用カウント
	int CntMax;				// 敵毎の攻撃カウント最大数
};

bool EnemySysInit(void);
void EnemyInit(void);
int EnemyCtl(int damage, int floor);
void EnemyDraw(void);
