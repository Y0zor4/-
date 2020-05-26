// #pragma once

struct RANKING
{
	char name_r[256];
	int floor_r;
	int posY;
};


bool RankingSysInit(void);
void RankingInit(void);
int RankingScene(void);
void RankingDraw(void);
