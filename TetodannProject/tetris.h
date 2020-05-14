//#pragma once

#define DATA_MAX_X 12
#define DATA_MAX_Y 25

bool TetrisSysInit(void);
void TetrisInit(void);
void TetrisCtl(void);
void TetrisDraw(void);

int TetrisLine(void);			// 消した列数を返り値とする関数
int TetrisCombo(void);			// コンボ数を返り値とする関数
