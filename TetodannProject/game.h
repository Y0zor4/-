// #pragma once


#define DAMAGE 100			// ダメージ計算用定数
#define FMCNT 200			// 階層移動カウント
#define FM_ST_CNT 80		// 階層移動が始まるまでの秒数

bool GameSysInit(void);
void GameInit(void);
int GameScene(void);
void GameDraw(void);


int DamageCalc(void);		// ダメージ計算用関数
int FloorMove(void);
