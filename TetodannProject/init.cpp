#include "Dxlib.h"	
#include "main.h"
#include "keycheck.h"
#include "title.h"
#include "story.h"
#include "name.h"
#include "select.h"
#include "game.h"
#include "gameover.h"
#include "gameclear.h"
#include "ranking.h"


bool SysInit(void)
{
	SetWindowText("tetorisudanzyonn");
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	ChangeWindowMode(false);

	//DX×²ÌŞ×Ø‚Ì‰Šú‰»
	if (DxLib_Init() == -1)
	{
		return  false;
	}
	SetDrawScreen(DX_SCREEN_BACK);

	KeyInit();		// “ü—Íî•ñ‚Ì‰Šú‰»

	if (!TitleSysInit())	 return false;
	if (!StorySysInit())	 return false;
	if (!NameSysInit())		 return false;
	if (!SelectSysInit())	 return false;
	if (!GameSysInit())		 return false;
	if (!GameoverSysInit())  return false;
	if (!GameclearSysInit()) return false;
	if (!RankingSysInit())   return false;

	return true;
}