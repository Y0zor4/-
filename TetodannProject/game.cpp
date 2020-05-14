#include "Dxlib.h"	
#include "main.h"
#include "keycheck.h"
#include "game.h"
#include "tetris.h"
#include "enemy.h"

bool GameSysInit(void)
{
	bool rtnFlag = true;

	TetrisSysInit();


	return rtnFlag;
}

void GameInit(void)
{

}

int GameScene(void)
{
	int rtn = 0;

	if (keyDownTrigger[KEY_ID_1])
	{
		rtn = 1;
	}
	else if (keyDownTrigger[KEY_ID_2])
	{
		rtn = 2;
	}
	else if (keyDownTrigger[KEY_ID_3])
	{
		rtn = 3;
	}
	else if (keyDownTrigger[KEY_ID_4])
	{
		rtn = 4;
	}
	TetrisCtl();
	EnemyCtl();
	GameDraw();

	return rtn;
}

void GameDraw(void)
{
	ClsDrawScreen();
	SetFontSize(50);
	DrawFormatString(0, 0, 0xFFFFFF, "GameScene");
	DrawBox(100, 100, 700, 500, 0x00FF00, true);
	DrawFormatString(300, 300, 0xFF0000, "Damage: %d", DamageCalc());
	TetrisDraw();
	EnemyDraw();
	ScreenFlip();
}

int DamageCalc(void)
{
	int line = TetrisLine();
	int combo = TetrisCombo();
	int damage = 0;
	
	damage = 100 * line * combo;

	return damage;
}
