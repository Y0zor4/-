//#pragma once

#define DATA_MAX_X 12
#define DATA_MAX_Y 25

bool TetrisSysInit(void);
void TetrisInit(void);
void TetrisCtl(void);
void TetrisDraw(void);

int TetrisLine(void);			// �������񐔂�Ԃ�l�Ƃ���֐�
int TetrisCombo(void);			// �R���{����Ԃ�l�Ƃ���֐�
