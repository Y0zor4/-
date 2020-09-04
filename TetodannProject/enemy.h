//#pragma once

#define ENEMY_MAX 50
#define ENEMY_POSY_F 500
#define MAX_SPARK	800

struct ENEMY
{
	int Life;				// 敵の現在の体力
	int LifeMax;			// 敵の体力最大値
	int Attack;				// 敵の攻撃力（テトリミノの出現列数）
	int Cnt;				// 敵毎の攻撃速度用カウント
	int CntMax;				// 敵毎の攻撃カウント最大数
	int Flag;
	int Appear;
	int image;
};

// 火花データ型
typedef struct tagSPARK
{
	int Valid;	// このデータが使用中か、フラグ
	int X, Y;	// 火花の位置
	int Sx, Sy;	// 火花の移動力
	int G;		// 火花の重さ
	int Bright;	// 火花の明るさ
} SPARK;

bool EnemySysInit(void);
void EnemyInit(void);
int EnemyCtl(int damage, int floor, bool flag);
void EnemyDraw(int floor);
int GetEnemyLife(void);
int GetAttackLines(int floor);

// 現在の敵の表示状態を返す(津田が勝手に作りました)。
bool GetEnemyBlend(int floor);

void CreateSpark(int x, int y);	// 火花を出す処理