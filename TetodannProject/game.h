// #pragma once


#define DAMAGE 100			// �_���[�W�v�Z�p�萔
#define FMCNT 200			// �K�w�ړ��J�E���g

bool GameSysInit(void);
void GameInit(void);
int GameScene(void);
void GameDraw(void);


int DamageCalc(void);		// �_���[�W�v�Z�p�֐�
void FloorMove(void);
