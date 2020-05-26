// #pragma once
#define BG_POS_X 712
#define BG_POS_Y 176

#define BG_SIZE_X 864
#define BG_SIZE_Y 700

#define BG_CENTER_X 432
#define BG_CENTER_Y 350

#define BG_CENTER_POS_X (BG_POS_X + BG_CENTER_X)
#define BG_CENTER_POS_Y (BG_POS_Y + BG_CENTER_Y)

#define SCROLL_MAX 80

bool BackgroundSysInit(void);
void BackgroundInit(void);
void BackgroundCtl(int floor, bool flag, int life);
void BackgroundDraw(int floor, bool eneFlag);
