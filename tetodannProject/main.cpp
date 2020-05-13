// ----- BaseProject ----- //
// ----- main.cpp ----- //
//�@2019.09.09
//�@Kuwata Masato

#include "Dxlib.h"	
#include "main.h"
#include "keycheck.h"
#include "effect.h"


/* ----- �ϐ� ----- */

// ���ъ֘A
SCENE_ID sceneID;					// ���݂̼�݊i�[�p
SCENE_ID preSceneID;				// ��O�̼��ID���i�[�p
int sceneCounter;					// ��ݗp

/* ----- ��߾ى� ----- */		// �� C++�A��޼ު�Ďw��

// �̪�Ă̏�����
void EffectInit(void)
{
	fadeIn = false;
	fadeOut = false;
	fadeCnt = 0;
	pauseFlag = false;
}

//�@WinMain()
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	//���т̏�����
	if (!SystemInit())
	{
		return -1;
	}


	// �ް�ٰ��
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClsDrawScreen();	//��ʏ���

		//��ݶ����𐧌�
		if (sceneID != preSceneID)
		{
			preSceneID = sceneID;
			sceneCounter = 0;
		}

		//���͏��̊m�F
		KeyCheck();

		switch (sceneID)
		{
			//���������
		case SCENE_ID_INIT:
			InitScene();
			break;

			//���ټ��
		case SCENE_ID_TITLE:
			//̪��޲�
			if (fadeIn)
			{
				if(!FadeInScreen(5)){}	// �̪�ďI����̏���
			}
			//̪��ޱ��
			else if (fadeOut)
			{
				if (!FadeOutScreen(5))
				{
					// �̪�ďI����̏���
					sceneID = SCENE_ID_GAME;		// ��������Ƽ�݂��ς���Ă���A̪��޲݂�true�ɂ���
					fadeIn = true;				
				}
			}

			TitleScene();
			break;

			//�ްѼ��
		case SCENE_ID_GAME:
			//̪��޲�
			if (fadeIn)
			{
				if (!FadeInScreen(5)) {}	// �̪�ďI����̏���

			}
			//̪��ޱ��
			else if (fadeOut)
			{
				if (!FadeOutScreen(5))
				{
					// �̪�ďI����̏���
					sceneID = SCENE_ID_GAMEOVER;	// ��������Ƽ�݂��ς���Ă���A̪��޲݂�true�ɂ���
					fadeIn = true;
				}
			}

			GameScene();
			break;

			//�ްѵ��ް���
		case SCENE_ID_GAMEOVER:
			//̪��޲�
			if (fadeIn)
			{
				if (!FadeInScreen(5)) {}	// �̪�ďI����̏���
			}
			//̪��ޱ��
			else if (fadeOut)
			{
				if (!FadeOutScreen(5))
				{
					// �̪�ďI����̏���
					sceneID = SCENE_ID_INIT;	// ��������Ƽ�݂��ς���Ă���A̪��޲݂�true�ɂ���
					fadeIn = true;
				}
			}
			GameoverScene();
			break;

		default:
			break;
		}

		sceneCounter++;

		ScreenFlip();
	}

	
	DxLib_End(); // DxLib�̏I��

	return true;
}

/* ----- ������ ----- */

//���ьn�̏�����
bool SystemInit(void)
{
	//���т̏�����
	SetWindowText("File_Kuwata");
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	ChangeWindowMode(true);

	//DXײ���؂̏�����
	if (DxLib_Init() == -1)
	{
		return  false;
	}
	SetDrawScreen(DX_SCREEN_BACK);

	KeyInit();		// ���͏��̏�����
	EffectInit();	// �̪�Ă̏�����

	//���̨���̓o�^

	//�ϐ��̏�����
	sceneCounter = 0;
	sceneID = SCENE_ID_INIT;
	preSceneID = SCENE_ID_MAX;
	fadeIn = true;

	return true;
}

/* ----- �ްѼ��� ----- */



/* ----- ��� ----- */

//���������
void InitScene(void)
{
	sceneID = SCENE_ID_TITLE;     // ���������I�������̂����ق�
}

//���ټ��
void TitleScene(void)
{
	
	if (keyDownTrigger[KEY_ID_SPACE])
	{
		fadeOut = true;
		//sceneID = SCENE_ID_GAME;
	}

	TitleDraw();
}

//�ްѼ��
void GameScene(void)
{	
	if (keyDownTrigger[KEY_ID_SPACE])
	{
		fadeOut = true;
		//sceneID = SCENE_ID_GAMEOVER;
	}

	// �ꎞ��~
	if (keyDownTrigger[KEY_ID_PAUSE])
	{
		pauseFlag = !pauseFlag;			// �悭�g���ے�
	}

	// Pause��
	if (pauseFlag)
	{
		SetDrawBright(120, 120, 120);
	}

	// �ʏ퓮�쎞
	else
	{

	}

	GameDraw();

	// Pauseү���ނ�`��
	if (pauseFlag)
	{
		SetDrawBright(255, 255, 255);
		DrawString(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2, "�o�`�t�r�d", 0xFFFFFF);
	}
}

//�ްѵ��ް���
void GameoverScene(void)
{
	
	if (keyDownTrigger[KEY_ID_SPACE])
	{
		fadeOut = true;
		//sceneID = SCENE_ID_TITLE;
	}

	GameoverDraw();
}

/* ----- �`�� ----- */

//���ټ��
void TitleDraw(void)
{
	DrawFormatString(0, 0, 0xFFFFFF, "TitleScene : %d", sceneCounter);
	DrawBox(100, 100, 700, 500, 0x00FF00, true);
}

//�ްѼ��
void GameDraw(void)
{
	DrawFormatString(0, 0, 0xFFFFFF, "GameScene : %d", sceneCounter);
	DrawBox(100, 100, 700, 500, 0xFF0000, true);
}

//�ްѵ��ް���
void GameoverDraw(void)
{
	DrawFormatString(0, 0, 0xFFFFFF, "GameoverScene : %d", sceneCounter);
	DrawBox(100, 100, 700, 500, 0x0000FF, true);
}