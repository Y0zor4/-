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
	int charType;			// �G�L�����̎��
	int enemyLife;			// �G�̌��݂̗̑�
	int enemyLifeMax;		// �G�̗͍̑ő�l
	int enemyAttack;		// �G�̍U���́i�e�g���~�m�̏o�����j

};

bool EnemySysInit(void);
void EnemyInit(void);
void EnemyCtl(void);
void EnemyDraw(void);
