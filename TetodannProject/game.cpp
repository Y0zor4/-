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
bool fmFlag;		// �K�w�ړ������̔��f�p

int gameoverCnt;		// �Q�[���I�[�o�[���̃J�E���g

// ��Ұ�ޕ\���p
int damageTmp;
int damageCnt;
int damageFade;
bool damageFlag;

// ����ފ֌W
int bgm;


bool GameSysInit(void)
{
	bool rtnFlag = true;

	if (!TetrisSysInit()) rtnFlag = false;
	if (!EnemySysInit())  rtnFlag = false;
	if (!BackgroundSysInit())  rtnFlag = false;

	backImage = LoadGraph("Image/back_tmp.png");

	bgm = LoadSoundMem("sound/bgm.mp3");

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

	damageTmp = 0;
	damageCnt = 0;
	damageFlag = false;
}

int GameScene(void)
{
	int rtn = 0;

	if (gameover_game)
	{
		gameoverCnt++;
		if (gameoverCnt == 60)
		{
			rtn = 1;
			gameoverCnt = 0;
		}
	}
	if (keyDownTrigger[KEY_ID_2])
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
	if (!fmFlag)
	{
		damage += DamageCalc();
	}

	// �_���[�W�ƌ��݂̊K�w�������n��
	life = EnemyCtl(damage, floor, fmFlag);
	attack = GetAttackLines(floor);

	// ��Ұ�ޕ\���p
	if (damage != 0)
	{
		damageTmp = damage;
		damageFlag = true;
		damageCnt = 0;
	}

	// �K�w�֘A����
	if (life <= 0 && !fmFlag)
	{
		if (!GetEnemyBlend(floor) && !GetBgBlend(floor))
		{
			fmFlag = true;
		}
	}

	BackgroundCtl(floor, fmFlag, GetEnemyBlend(floor));
	
	FloorMove();
	floor_main = floor;

	GameDraw();

	// ���Đ�
	PlaySoundMem(bgm, DX_PLAYTYPE_LOOP, false);
	
	if (rtn != 0)
	{
		StopSoundMem(bgm);
	}
	return rtn;
}

void GameDraw(void)
{
	ClsDrawScreen();
	SetFontSize(50);
	DrawFormatString(0, 0, 0xFFFFFF, "GameScene");
	BackgroundDraw(floor, GetEnemyBlend(floor));
	DrawGraph(0, 0, backImage, true);

	EnemyDraw(floor);
	TetrisDraw();
	
	DrawFormatString(1400, 90, 0xFFFFFF, "F%d", floor);

	// ��Ұ�ޕ\��
	if (damageFlag)
	{
		damageCnt++;
		if (damageCnt < 150)
		{
			SetFontSize(55);
			DrawFormatString(1103, 503, 0x000000, "%d", damageTmp, true);
			DrawFormatString(1100, 500, 0xFFFFFF, "%d", damageTmp, true);
		}
		else
		{
			damageFlag = false;
		}
	}
	
	ScreenFlip();
}

int DamageCalc(void)
{
	int damage = 0;
	
	damage = DAMAGE * line_game * combo_game;

	return damage;
}

// �K�w�ړ�����
int FloorMove(void)
{
	if (fmFlag)
	{
		if (fmCnt < FMCNT)
		{
			fmCnt++;
		}
		if (fmCnt >= FMCNT)
		{
			fmFlag = false;
			if (life <= 0)floor += 1;
			fmCnt = 0;
		}
	}
	return floor;
}