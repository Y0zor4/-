//#pragma once

#define ENEMY_MAX 50
#define ENEMY_POSY_F 500
#define MAX_SPARK	800

struct ENEMY
{
	int Life;				// �G�̌��݂̗̑�
	int LifeMax;			// �G�̗͍̑ő�l
	int Attack;				// �G�̍U���́i�e�g���~�m�̏o���񐔁j
	int Cnt;				// �G���̍U�����x�p�J�E���g
	int CntMax;				// �G���̍U���J�E���g�ő吔
	int Flag;
	int Appear;
	int image;
};

// �Ήԃf�[�^�^
typedef struct tagSPARK
{
	int Valid;	// ���̃f�[�^���g�p�����A�t���O
	int X, Y;	// �ΉԂ̈ʒu
	int Sx, Sy;	// �ΉԂ̈ړ���
	int G;		// �ΉԂ̏d��
	int Bright;	// �ΉԂ̖��邳
} SPARK;

bool EnemySysInit(void);
void EnemyInit(void);
int EnemyCtl(int damage, int floor, bool flag);
void EnemyDraw(int floor);
int GetEnemyLife(void);
int GetAttackLines(int floor);

// ���݂̓G�̕\����Ԃ�Ԃ�(�Óc������ɍ��܂���)�B
bool GetEnemyBlend(int floor);

void CreateSpark(int x, int y);	// �ΉԂ��o������