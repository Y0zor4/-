/* ===== keycheck.h ===== */
// 2019.09.20

//#pragma once


/* ----- �񋓌^ ----- */

//���͏��p
enum KEY_ID {
	  KEY_ID_SPACE				//��߰���
	, KEY_ID_PAUSE				//P����
	, KEY_ID_MOUSE_LEFT			//ϳ�������
	, KEY_ID_MOUSE_MIDDLE		//ϳ��^������
	, KEY_ID_MOUSE_RIGHT		//ϳ��E����
	, KEY_ID_MAX
};

/* ----- �������ߐ錾 ----- */

void KeyInit(void);				//���͏��̏�����
void KeyCheck(void);			//���͏��̊m�F

/* ----- ��۰��ى� ----- */

//���͏��Ǘ��p
extern bool keyOld[KEY_ID_MAX];				//1�ڰёO�̓��͏��
extern bool keyNew[KEY_ID_MAX];				//���݂̓��͏��
extern bool keyDownTrigger[KEY_ID_MAX];		//�޳ݎ����ضް
extern bool keyUpTrigger[KEY_ID_MAX];		//���ߎ����ضް