//#pragma once

#define ENEMY_MAX 50

//enum ENEMY_TYPE
//{
//	ENEMY_T_SLIME,
//	ENEMY_T_KNIGHT,
//	ENEMY_T_GIGANTES,
//	ENEMY_T_GOLEM,
//	ENEMY_T_KILLERDOLL,
//	ENEMY_T_DRAGON,
//	ENEMY_T_KINGDRAGON,
//	ENEMY_T_MAX
//};

struct ENEMY
{
	int charType;			// 敵キャラの種類
	int enemyLife;			// 敵の現在の体力
	int enemyLifeMax;		// 敵の体力最大値
	int enemyAttack;		// 敵の攻撃力（テトリミノの出現数）

};

bool EnemySysInit(void);
void EnemyInit(void);
void EnemyCtl(void);
void EnemyDraw(void);
