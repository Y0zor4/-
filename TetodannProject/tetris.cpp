#include "Dxlib.h"	
#include "main.h"
#include "keycheck.h"
#include "tetris.h"

int mapData[DATA_MAX_Y][DATA_MAX_X];		// �ް��i�[�p

// �m�F�p�R�����g

bool TetrisSysInit(void)
{
	bool rtnFlag = true;

	return rtnFlag;
}

void TetrisInit(void)
{
	for (int x = 0; x < DATA_MAX_X; x++)
	{
		for (int y = 0; y < DATA_MAX_Y; y++)
		{
			mapData[y][x] = -1;
			if (y == 0 || y == DATA_MAX_Y - 1)
			{
				mapData[y][x] = 1;
			}
			if (x == 0 || x == DATA_MAX_X - 1)
			{
				mapData[y][x] = 1;
			}
		}
	}
}

void TetrisCtl(void)
{

}

void TetrisDraw(void)
{

}

int TetrisLine(void)
{
	int line = 0;
	return line;
}

int TetrisCombo(void)
{
	int combo = 0;
	return combo;
}
