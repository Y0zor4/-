//#pragma once

#define ENEMY_MAX 50


struct ENEMY
{
	//int charType;			// �G�L�����̎��
	int Life;				// �G�̌��݂̗̑�
	int LifeMax;			// �G�̗͍̑ő�l
	int Attack;				// �G�̍U���́i�e�g���~�m�̏o�����j
	int Cnt;				// �G���̍U�����x�p�J�E���g
	int CntMax;				// �G���̍U���J�E���g�ő吔
};

bool EnemySysInit(void);
void EnemyInit(void);
int EnemyCtl(int damage, int floor);
void EnemyDraw(void);
