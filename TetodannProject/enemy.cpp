#include "Dxlib.h"	
#include "main.h"
#include "keycheck.h"
#include "enemy.h"

// 変数
ENEMY enemy[ENEMY_MAX];

int fmFlag_enemy;

SPARK Spark[MAX_SPARK];	// 火花データ

// 敵のシステム系初期化
bool EnemySysInit(void)
{
	bool rtnFlag = true;
	enemy[0].image = LoadGraph("image/slime1.png");
	enemy[1].image = LoadGraph("image/slime2.png");
	enemy[2].image = LoadGraph("image/slime3.png");
	enemy[3].image = LoadGraph("image/slime4.png");
	enemy[4].image = LoadGraph("image/slime5.png");

	// 仮処理
	for (int e = 5; e < ENEMY_MAX; e++)
	{
		int i = rand() % 5;
		enemy[e].image = enemy[i].image;
	}

	// 火花の存在を初期化する
	for (int i = 0; i < MAX_SPARK; i++)
		Spark[i].Valid = 0;

	return rtnFlag;
}

// 敵初期化
void EnemyInit(void)
{
	for (int e = 0; e < ENEMY_MAX; e++)
	{
		enemy[e].LifeMax = 100 * (e + 1);
		enemy[e].Life = enemy[e].LifeMax;
		enemy[e].Attack = 1;
		enemy[e].CntMax = 500;
		enemy[e].Cnt = enemy[e].CntMax;
		enemy[e].Appear = 0;
	}

	fmFlag_enemy = false;
}

// 敵の行動制御
int EnemyCtl(int damage, int floor, bool flag)
{
	fmFlag_enemy = flag;
	if (fmFlag_enemy)
	{
		return 0;
	}

	int i, j, R;
	// 敵体力減少処理
	if (enemy[floor - 1].Life > 0)
	{
		enemy[floor - 1].Life = enemy[floor - 1].Life - damage;
		// 火花を出す数をセット
		R = GetRand(60);
		for (j = 0; j < R; j++)
		{
			// 火花を生成
			CreateSpark(1000 + j, 500 + j);
		}
	}
	
	if (enemy[floor - 1].Life <= 0)
	{
		enemy[floor - 1].Life = 0;
		flag = false;
	}
	
	return enemy[floor - 1].Life;
}

// 敵の描画
void EnemyDraw(int floor)
{

	if (enemy[floor - 1].Life > 0)
	{
		enemy[floor - 1].Appear += 10;
		if (enemy[floor - 1].Appear >= 255)
		{
			enemy[floor - 1].Appear = 255;
		}
	}
	else
	{
		enemy[floor - 1].Appear -= 2;
		if (enemy[floor - 1].Appear <= 0)
		{
			enemy[floor - 1].Appear = 0;
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, enemy[floor - 1].Appear);
	DrawGraph(712, 176, enemy[floor - 1].image, true);
	//DrawBox(1000, 500, 1200, 800, 0xFFFFFF, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


	if (fmFlag_enemy)
	{
		return;
	}
	// 火花を描画する
	for (int j = 0; j < MAX_SPARK; j++)
	{
		// 火花データが有効な時のみ描画
		if (Spark[j].Valid == 1)
			DrawPixel(Spark[j].X / 100, Spark[j].Y / 100,
				GetColor(Spark[j].Bright, Spark[j].Bright, Spark[j].Bright));

	}

	// 敵の体力ゲージ (後に変更有)
	DrawBox(750, 90, 1350, 130, 0x000000, true);
	DrawBox(750, 90, 600 * enemy[floor - 1].Life / enemy[floor - 1].LifeMax + 750, 130, 0x00FF00, true);
	DrawBox(750, 90, 1350, 130, 0xFFFFFF, false);

	// 敵の攻撃ゲージ（後に変更有）
	DrawBox(800, 820, 1400, 850, 0x000000, true);
	DrawBox(800, 820, 600 * enemy[floor - 1].Cnt / enemy[floor - 1].CntMax + 800, 850, 0xFF0000, true);
	DrawBox(800, 820, 1400, 850, 0xFFFFFF, false);

	
	// 敵の体力数値
	DrawFormatString(900, 30, 0xFFFFFF, "HP:%d/%d", enemy[floor - 1].Life, enemy[floor - 1].LifeMax);




}


int GetEnemyLife(void)
{
	return enemy[0].LifeMax;
}

int GetAttackLines(int floor)
{
	if (fmFlag_enemy)
	{
		return 0;
	}

	
	if (enemy[floor - 1].Appear == 255)
	{
		// 敵の攻撃関連
		if (enemy[floor - 1].Cnt > 0)enemy[floor - 1].Cnt--;

		if (enemy[floor - 1].Cnt <= 0)
		{
			enemy[floor - 1].Cnt = enemy[floor - 1].CntMax;
			return enemy[floor - 1].Attack;
		}
	}
	return 0;
}



// 現在の敵の表示状態を返す。
bool GetEnemyBlend(int floor)
{
	if (enemy[floor - 1].Appear == 0)
	{
 		return false;
	}
	return true;
}


// 火花を出す処理
void CreateSpark(int x, int y)
{
	int i;

	// 使われていない火花データを探す
	for (i = 0; i < MAX_SPARK; i++)
	{
		if (Spark[i].Valid == 0) break;
	}

	// もし使われていない火花データがあったら火花を出す
	if (i != MAX_SPARK)
	{
		// 火花の位置を設定
		Spark[i].X = x * 100;
		Spark[i].Y = y * 100;

		// 移動力を設定
		Spark[i].Sx = GetRand(1000) - 500;
		Spark[i].Sy = -GetRand(500);

		// 火花の重さをセット
		Spark[i].G = GetRand(10);

		// 火花の明るさセット
		Spark[i].Bright = 255;

		// 火花データを使用中にセット
		Spark[i].Valid = 1;
	}
}