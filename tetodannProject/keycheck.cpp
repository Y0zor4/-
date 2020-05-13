// ----- keycheck.cpp ----- //
//�@2019.09.20
//�@Kuwata Masato


#include "Dxlib.h"
#include "keycheck.h"

/* ----- �ϐ� ----- */

bool keyOld[KEY_ID_MAX];				//1�ڰёO�̓��͏��
bool keyNew[KEY_ID_MAX];				//���݂̓��͏��
bool keyDownTrigger[KEY_ID_MAX];		//�޳ݎ����ضް
bool keyUpTrigger[KEY_ID_MAX];			//���ߎ����ضް

//���͏��̏�����
void KeyInit(void)
{
	for (int keyID = 0; keyID < KEY_ID_MAX; keyID++)
	{
		keyOld[keyID] = false;
		keyNew[keyID] = false;
		keyDownTrigger[keyID] = false;
		keyUpTrigger[keyID] = false;
	}
}


//���͏��̊m�F
void KeyCheck(void)
{
	//Old�̏���
	for (int keyID = 0; keyID < KEY_ID_MAX; keyID++)
	{
		keyOld[keyID] = keyNew[keyID];
	}

	//���݂̏�Ԃ��擾����
	keyNew[KEY_ID_SPACE] = CheckHitKey(KEY_INPUT_SPACE);
	keyNew[KEY_ID_PAUSE] = CheckHitKey(KEY_INPUT_P);

	//�ضް�̎Z�o
	for (int keyID = 0; keyID < KEY_ID_MAX; keyID++)
	{
		keyDownTrigger[keyID] = false;
		keyUpTrigger[keyID] = false;

		//�޳��ضް
		if (!keyOld[keyID] && keyNew[keyID])
		{
			keyDownTrigger[keyID] = true;
		}

		//�����ضް
		if (keyOld[keyID] && !keyNew[keyID])
		{
			keyUpTrigger[keyID] = true;
		}
	}
}