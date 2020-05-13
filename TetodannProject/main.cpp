#include "Dxlib.h"	
#include "main.h"
#include "init.h"
#include "keycheck.h"
#include "title.h"
#include "story.h"
#include "name.h"
#include "select.h"
#include "game.h"
#include "gameover.h"
#include "gameclear.h"
#include "ranking.h"


// ���ъ֘A
SCENE_ID scnID;					// ���݂̼�݊i�[�p
int nextscn;					// ���̼�݈ړ��挈��p


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	//���т̏�����
	if (!SysInit())
	{
		return -1;
	}
	//�ϐ��̏�����
	scnID = SCENE_ID_TITLE;


	// �ް�ٰ��
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClsDrawScreen();	//��ʏ���

		//���͏��̊m�F
		KeyCheck();

		switch (scnID)
		{
		case SCENE_ID_TITLE:
			nextscn = TitleScene();
			if (nextscn == 1)
			{
				StoryInit();
				scnID = SCENE_ID_STORY;
			}
			break;

		case SCENE_ID_STORY:
			nextscn = StoryScene();
			if (nextscn == 1)
			{
				NameInit();
				scnID = SCENE_ID_NAME;
			}
			break;

		case SCENE_ID_NAME:
			nextscn = NameScene();
			if (nextscn == 1)
			{
				SelectInit();
				scnID = SCENE_ID_SELECT;
			}
			break;

		case SCENE_ID_SELECT:
			nextscn = SelectScene();
			if (nextscn == 1)
			{
				GameInit();
				scnID = SCENE_ID_GAME;
			}
			else if (nextscn == 2)
			{
				TitleInit();
				scnID = SCENE_ID_TITLE;
			}
			break;

		case SCENE_ID_GAME:
			nextscn = GameScene();
			if (nextscn == 1)
			{
				GameoverInit();
				scnID = SCENE_ID_GAMEOVER;
			}
			else if (nextscn == 2)
			{
				GameclearInit();
				scnID = SCENE_ID_GAMECLEAR;
			}
			else if (nextscn == 3)
			{
				SelectInit();
				scnID = SCENE_ID_SELECT;
			}
			else if (nextscn == 4)
			{
				TitleInit();
				scnID = SCENE_ID_TITLE;
			}
			break;

		case SCENE_ID_GAMEOVER:
			nextscn = GameoverScene();
			if (nextscn == 1)
			{
				RankingInit();
				scnID = SCENE_ID_RANKING;
			}
			break;

		case SCENE_ID_GAMECLEAR:
			nextscn = GameclearScene();
			if (nextscn == 1)
			{
				RankingInit();
				scnID = SCENE_ID_RANKING;
			}
			break;

		case SCENE_ID_RANKING:
			nextscn = RankingScene();
			if (nextscn == 1)
			{
				SelectInit();
				scnID = SCENE_ID_SELECT;
			}
			else if (nextscn == 2)
			{
				TitleInit();
				scnID = SCENE_ID_TITLE;
			}

			break;

		default:
			break;
		}
	}
	DxLib_End(); // DxLib�̏I��

	return true;
}

