#include "Dxlib.h"	
#include "main.h"
#include "keycheck.h"
#include "game.h"
#include "tetris.h"
#include "enemy.h"

int backImage;   // ¹Ş°Ñ‚Ì”wŒi—p(“G‚ª‚¢‚È‚¢‚Æ‚±‚ë)

int line_game;
int combo_game;
int floor;

bool GameSysInit(void)
{
	bool rtnFlag = true;

	if (!TetrisSysInit()) rtnFlag = false;
	if (!EnemySysInit())  rtnFlag = false;

	backImage = LoadGraph("Image/back_tmp.png");

	return rtnFlag;
}

void GameInit(void)
{
	TetrisInit();
	EnemyInit();
	floor = 1;
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

	// ÃÄØ½Ctl‚É“n‚·ˆø”‚ÍA“G‚©‚çH‚ç‚¤‚»‚ÌÌÚ°Ñ‚ÌUŒ‚‚ÌÀŞÒ°¼Ş—ñ”
	TetrisCtl(0);

	line_game = TetrisLine();
	combo_game = TetrisCombo();

	// ƒ_ƒ[ƒW‚ÆŒ»İ‚ÌŠK‘w‚ğˆø‚«“n‚·
	EnemyCtl(DamageCalc());
	
	FloorMove();

	GameDraw();

	return rtn;
}

void GameDraw(void)
{
	ClsDrawScreen();
	SetFontSize(50);
	DrawFormatString(0, 0, 0xFFFFFF, "GameScene");
	DrawGraph(0, 0, backImage, true);
	TetrisDraw();
	EnemyDraw(floor);
	DrawFormatString(1000, 200, 0xFFFFFF, "Damage:%d", DamageCalc());
	DrawFormatString(1400, 90, 0xFFFFFF, "F%d", floor);

	ScreenFlip();
}

int DamageCalc(void)
{
	int damage = 0;
	
	damage = DAMAGE * line_game * combo_game;

	return damage;
}

// ŠK‘wˆÚ“®ˆ—
int FloorMove(void)
{
	int life = EnemyCtl(0);
	if (life <= 0)
	{
		floor += 1;
	}
	return floor;
}