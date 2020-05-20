// #pragma once
#define BG_SIZE_X 864
#define BG_SIZE_Y 700
#define BG_CENTER_X 432
#define BG_CENTER_Y 350


bool BackgroundSysInit(void);
void BackgroundInit(void);
void BackgroundCtl(int floor, bool flag);
void BackgroundDraw(int floor);
