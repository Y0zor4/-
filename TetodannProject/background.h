// #pragma once
#define BG_SIZE_X 864
#define BG_SIZE_Y 700
#define OFFSET_X 712
#define OFFSET_Y 176


bool BackgroundSysInit(void);
void BackgroundInit(void);
void BackgroundCtl(int floor);
void BackgroundDraw(int floor);
