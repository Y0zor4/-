#include "Dxlib.h"	
#include "main.h"
#include "keycheck.h"
#include "game.h"
#include "tetris.h"
#include "enemy.h"

int backImage;   // �ްт̔w�i�p(�G�����Ȃ��Ƃ���)

int line_game;
int combo_game;


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

	// ��ؽCtl�ɓn�������́A�G����H�炤�����ڰю��̍U������Ұ�ޗ�
	TetrisCtl(0);

	line_game = TetrisLine();
	combo_game = TetrisCombo();

	if (!FloorMove)
	{
		// �_���[�W�ƌ��݂̊K�w�������n��
		EnemyCtl(DamageCalc(), 0);
	}
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
	EnemyDraw();
	DrawFormatString(1000, 200, 0xFFFFFF, "Damage:%d", DamageCalc());
	ScreenFlip();
}

int DamageCalc(void)
{
	int damage = 0;
	
	damage = DAMAGE * line_game * combo_game;

	return damage;
}

// �K�w�ړ�����
void FloorMove(int floor)
{
	int life = EnemyCtl(0, floor);
	if (life <= 0)
	{
		floor = floor + 1;
	}	
}