//#pragma once


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
	int Life;				// �G�̌��݂̗̑�
	int LifeMax;			// �G�̗͍̑ő�l
	int Attack;				// �G�̍U���́i�e�g���~�m�̏o�����j
	int cnt;				// �G���̍U�����x�p�J�E���g
};

bool EnemySysInit(void);
void EnemyInit(void);
void EnemyCtl(int damage);
void EnemyDraw(void);
