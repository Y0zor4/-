//#pragma once

#define ENEMY_MAX 50


struct ENEMY
{
	//int charType;			// �G�L�����̎��
	int Life;				// �G�̌��݂̗̑�
	int LifeMax;			// �G�̗͍̑ő�l
	int Attack;				// �G�̍U���́i�e�g���~�m�̏o�����j
	int cnt;				// �G���̍U�����x�p�J�E���g
};

bool EnemySysInit(void);
void EnemyInit(void);
void EnemyCtl(int damage);
void EnemyDraw(void);
