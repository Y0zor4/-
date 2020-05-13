/* ===== main.h ===== */
// 2019.09.09

//#pragma once

/* ----- �萔 ----- */

//���ъ֘A
#define SCREEN_SIZE_X	800			//��ذ݂�X���W
#define SCREEN_SIZE_Y	600			//��ذ݂�Y���W

#define COLOR_BRIGHT	255			//�F�̋P�x

/* ----- �񋓌^ ----- */

//��݊Ǘ��p
enum SCENE_ID {
	SCENE_ID_INIT				//�ްя��������
	, SCENE_ID_TITLE			//���ټ��
	, SCENE_ID_GAME				//�ްѼ��
	, SCENE_ID_GAMEOVER			//�ްѵ��ް���
	, SCENE_ID_MAX
};



/* ----- �������ߐ錾 ----- */

//���ъ֘A
bool SystemInit(void);			//���т̏�����

//���
void InitScene(void);			//���������
void TitleScene(void);			//���ټ��
void GameScene(void);			//�ްѼ��
void GameoverScene(void);		//�ްѵ��ް���

//�`��
void TitleDraw(void);			//���ٗp
void GameDraw(void);			//�ްїp
void GameoverDraw(void);		//�ްѵ��ް�p
