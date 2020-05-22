#include "Dxlib.h"	
#include <string.h>
#include "main.h"
#include "keycheck.h"
#include "name.h"

char letter[26][8];
int nameNum[8];
int nameCnt;

bool nameFlag;


bool NameSysInit(void)
{
	bool rtnFlag = true;

	strcpy_s(letter[0], 8, "A");
	strcpy_s(letter[1], 8, "B");
	strcpy_s(letter[2], 8, "C");
	strcpy_s(letter[3], 8, "D");
	strcpy_s(letter[4], 8, "E");
	strcpy_s(letter[5], 8, "F");
	strcpy_s(letter[6], 8, "G");
	strcpy_s(letter[7], 8, "H");
	strcpy_s(letter[8], 8, "I");
	strcpy_s(letter[9], 8, "J");
	strcpy_s(letter[10], 8, "K");
	strcpy_s(letter[11], 8, "L");
	strcpy_s(letter[12], 8, "N");
	strcpy_s(letter[13], 8, "M");
	strcpy_s(letter[14], 8, "O");
	strcpy_s(letter[15], 8, "P");
	strcpy_s(letter[16], 8, "Q");
	strcpy_s(letter[17], 8, "R");
	strcpy_s(letter[18], 8, "S");
	strcpy_s(letter[19], 8, "T");
	strcpy_s(letter[20], 8, "U");
	strcpy_s(letter[21], 8, "V");
	strcpy_s(letter[22], 8, "W");
	strcpy_s(letter[23], 8, "X");
	strcpy_s(letter[24], 8, "Y");
	strcpy_s(letter[25], 8, "Z");
	


	return rtnFlag;
}


void NameInit(void)
{
	strcpy_s(name, 256, "");

	for (int i = 0; i < 8; i++)
	{
		nameNum[i] = -1;
	}

	nameCnt = 0;

	nameFlag = false;
}



int NameScene(void)
{
	int rtn = 0;

	if (keyDownTrigger[KEY_ID_SPACE])
	{
		//if (nameFlag)
		{
			rtn = 1;
		}
	}



	if (!nameFlag)
	{
		if (keyDownTrigger[KEY_ID_UP])
		{
			if (nameNum[nameCnt] > -1)
			{
				nameNum[nameCnt]--;
			}
		}
		if (keyDownTrigger[KEY_ID_DOWN])
		{
			if (nameNum[nameCnt] < 25)
			{
				nameNum[nameCnt]++;
			}
		}
		if (keyDownTrigger[KEY_ID_RIGHT])
		{
			if (nameCnt < 7)
			{
				nameCnt++;
			}
		}
		if (keyDownTrigger[KEY_ID_LEFT])
		{
			if (nameCnt > 0)
			{
				nameCnt--;
			}
		}
	}




	if (keyDownTrigger[KEY_ID_SPACE] && nameCnt > 1)
	{
		if(nameCnt == 7 || nameNum[nameCnt] == -1)
		strcpy_s(name, 256, "");
		for (int i = 0; i < 8; i++)
		{
			if (nameNum[i] != -1)
			{
				strcat_s(name, 256, letter[nameNum[i]]);
			}
		}
		nameFlag = true;
	}
	

	NameDraw();

	return rtn;
}

void NameDraw(void)
{
	ClsDrawScreen();
	SetFontSize(50);


	for (int i = 0; i < 8; i++)
	{
		if (nameNum[i] != -1)
		{
			SetFontSize(100);
			DrawFormatString(400 + i * 100, 100, 0xFFFFFF, "%s", letter[nameNum[i]]);
		}
		if (i == nameCnt && !nameFlag)
		{
			SetFontSize(100);
			if (nameNum[i] != -1)
			{
				DrawFormatString(400 + i * 100, 500, 0xFFFFFF, "%s", letter[nameNum[i]]);
			}
			SetFontSize(80);
			if (nameNum[i] > -1)
			{
				DrawFormatString(405 + i * 100, 420, 0xFFFFFF, "%s", letter[nameNum[i] - 1]);
			}
			if (nameNum[i] < 25)
			{
				DrawFormatString(405 + i * 100, 590, 0xFFFFFF, "%s", letter[nameNum[i] + 1]);
			}

			DrawBox(370 + nameCnt * 100, 485, 485 + nameCnt * 100, 600, 0xFFFFFF, false);
		}

		SetFontSize(160);
		DrawFormatString(385 + i * 100, 70, 0xFFFFFF, "_");
		
	}

	SetFontSize(50);
	ScreenFlip();
}


char GetName(void)
{
	return *name;
}