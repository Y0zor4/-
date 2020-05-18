// #pragma once


#define DAMAGE 100			// ダメージ計算用定数

bool GameSysInit(void);
void GameInit(void);
int GameScene(void);
void GameDraw(void);


int DamageCalc(void);		// ダメージ計算用関数
void FloorMove(void);
