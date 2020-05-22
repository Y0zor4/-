#include "Dxlib.h"	
#include "fade.h"

bool fadein;
bool fadeout;
int cnt;

bool FadeInit(void)
{
	bool rtnFlag = true;


	fadein = true;
	fadeout = false;

	return rtnFlag;
}

bool FadeIn(int fadestep)
{
	cnt += fadestep;
	if (cnt <= 255)
	{
		SetDrawBright(cnt, cnt, cnt);
		return true;
	}
	else
	{
		cnt = 0;
		fadein = false;
		return false;
	}
}

bool FadeOut(int fadestep)
{
	cnt += fadestep;
	if (cnt <= 255)
	{
		SetDrawBright(255 - cnt, 255 - cnt, 255 - cnt);
		return true;
	}
	else
	{
		cnt = 0;
		fadeout = false;
		return false;
	}
}
