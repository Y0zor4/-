//#pragma once


//���͏��p
enum KEY_ID 
{
	KEY_ID_SPACE,				//��߰���
	KEY_ID_1,
	KEY_ID_2,
	KEY_ID_3,
	KEY_ID_4,
	KEY_ID_UP,
	KEY_ID_DOWN,
	KEY_ID_LEFT,
	KEY_ID_RIGHT,
	KEY_ID_Z,
	KEY_ID_X,
	KEY_ID_C,
	KEY_ID_LSHIFT,
	KEY_ID_ENTER,
	KEY_ID_MAX
};


void KeyInit(void);				//���͏��̏�����
void KeyCheck(void);			//���͏��̊m�F


//���͏��Ǘ��p
extern bool keyOld[KEY_ID_MAX];				//1�ڰёO�̓��͏��
extern bool keyNew[KEY_ID_MAX];				//���݂̓��͏��
extern bool keyDownTrigger[KEY_ID_MAX];		//�޳ݎ����ضް
extern bool keyUpTrigger[KEY_ID_MAX];		//���ߎ����ضް