// #pragma once


#define DAMAGE 100			// �_���[�W�v�Z�p�萔
#define FMCNT 200			// �K�w�ړ��J�E���g
#define FM_ST_CNT 80		// �K�w�ړ����n�܂�܂ł̕b��

bool GameSysInit(void);
void GameInit(void);
int GameScene(void);
void GameDraw(void);


int DamageCalc(void);		// �_���[�W�v�Z�p�֐�
int FloorMove(void);
