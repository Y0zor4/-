#include "Dxlib.h"	
#include "main.h"
#include "keycheck.h"
#include "game.h"
#include "tetris.h"
#include "enemy.h"
#include "background.h"


int backImage;		// �ްт̔w�i�p(�G�����Ȃ��Ƃ���)

int line_game;		// ��v�Z�p�ϐ�
int combo_game;		// �R���{�v�Z�p�ϐ�
bool gameover_game;


int floor;			// �K�w�ړ��p�ϐ�
int life;			// �G�̗͊i�[�p�ϐ�
int damage;			// �G���󂯂�_���[�W�i�[�p�ϐ�
int attack;			// �G�̍U����

int fmCnt;			// �K�w�ړ����̃J�E���g
int fmFlag;

bool GameSysInit(void)
{
	bool rtnFlag = true;

	if (!TetrisSysInit()) rtnFlag = false;
	if (!EnemySysInit())  rtnFlag = false;
	if (!BackgroundSysInit())  rtnFlag = false;

	backImage = LoadGraph("Image/back_tmp.png");

	return rtnFlag;
}

void GameInit(void)
{
	// �e����̏�����
	TetrisInit();
	EnemyInit();
	BackgroundInit();


	floor = 1;
	damage = 0;
	life = GetEnemyLife();
	attack = 0;

	fmCnt = 0;
	fmFlag = false;
	gameover_game = false;

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
	damage = TetrisCtl(attack);
	gameover_game = Gameover();


	line_game = TetrisLine();
	combo_game = TetrisCombo();
	damage += DamageCalc();
	
	// �_���[�W�ƌ��݂̊K�w�������n��
	life = EnemyCtl(damage, floor);

	if (life <= 0)fmFlag = true;
	
	if (!fmFlag)
	{
		attack = GetAttackLines(floor);
	}
	else if(fmFlag)
	{
		
		if (fmCnt < FMCNT)
		{
			fmCnt++;
			
		}
		if (fmCnt >= FMCNT)
		{
			fmFlag = false;
			FloorMove();
 			fmCnt = 0;
		}
	}

	GameDraw();
	
	return rtn;
}

void GameDraw(void)
{
	ClsDrawScreen();
	SetFontSize(50);
	DrawFormatString(0, 0, 0xFFFFFF, "GameScene");
	BackgroundDraw(floor);
	DrawGraph(0, 0, backImage, true);

	EnemyDraw(floor);
	TetrisDraw();
	DrawFormatString(1000, 200, 0xFFFFFF, "Damage:%d", DamageCalc());
	DrawFormatString(1400, 90, 0xFFFFFF, "F%d", floor);
	// ��������ƃR���{�m�F�p
	DrawFormatString(900, 300, 0xFFFFFF, "line combo : %d, %d", line_game, combo_game);
	// �G����TetrisCtl�ɓn�����񐔊m�F�p
	DrawFormatString(900, 350, 0xFFFFFF, "atk : %d", attack);

	ScreenFlip();
}

int DamageCalc(void)
{
	int damage = 0;
	
	damage = DAMAGE * line_game * combo_game;

	return damage;
}

// �K�w�ړ�����
void FloorMove(void)
{
	if (life <= 0)floor += 1;	
}