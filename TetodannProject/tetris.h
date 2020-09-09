//#pragma once

#define DATA_MAX_X 12
#define DATA_MAX_Y 31

#define MINO_MAX 8      // �Ɏ��
#define MINO_SIZE_X 40
#define MINO_SIZE_Y 40

#define DONT_CTL_TIME 20		// ����s�\����




// ��ۯ��̎��
enum BLOCK_TYPE
{
	BLOCK_TYPE_I,
	BLOCK_TYPE_O,
	BLOCK_TYPE_T,
	BLOCK_TYPE_J,
	BLOCK_TYPE_L,
	BLOCK_TYPE_S,
	BLOCK_TYPE_Z,
	BLOCK_TYPE_MAX
};


// ��ۯ��̌���
enum BLOCK_DIR
{
	DIR_0,
	DIR_1,
	DIR_2,
	DIR_3,
	DIR_MAX
};


// �ړ��̕���
enum MOVE_DIR
{
	MOVE_DIR_DOWN,
	MOVE_DIR_LEFT,
	MOVE_DIR_RIGHT,
	MOVE_DIR_MAX
};


// ���W
struct Pos
{
	int x;
	int y;
};


// �u���b�N
struct BLOCK
{
	int block[DIR_MAX][4][4];
	Pos pos;
	bool flag;
};






bool TetrisSysInit(void);		// ��ؽ�֘A���ьn������
void TetrisInit(void);			// ��ؽ�֘A������
void MinoInit(void);			// �ɏ�񏉊���
int TetrisCtl(int atk);			// ��ؽ�S�̏���
void CreateMino(void);			// �ɏo��
void MinoData(void);			// �ɏ���moveData��
void MoveMino(void);			// �ɂ̐���
void AutoMoveMino(void);		// �Ɏ�������
void KeyMoveMinoLR(void);		// �ɍ��E�ړ�����
void KeyMoveMinoDown(void);		// �ɉ��ړ�����
void KeyMoveMinoHardDown(void); // �ɍŉ��ړ�����
void KeyRotaMino(void);			// �ɉ�]����
void MapData(void);				// moveData��mapData��
bool HitCheckMove(void);		// �����蔻��
void DisMino(void);				// �ɏ��ŏ���
bool DisMino2(int y);			// �ɏ��ŏ���
void MinoSave(void);			// �ɏ����ޯ�����
void MinoSaveRev(void);			// �ɏ����ޯ����߂ŏ㏑��(�ړ�������)
void TetrisDraw(void);			// �`��
void EnemyAtkBlock(void);		// �G�̍U��
void MinoPreDown(void);			// �ɂ̗\�������n�_
bool HitCheckPreDown(void);		// �����蔻��ŉ������p
void ShakeBlock(void);			// ��ʗh�炵


bool CreateNext(int* nextBlock, int num); // next�p
void Hold(void);						  // hold�p

int TetrisLine(void);			// �������񐔂�Ԃ�l�Ƃ���֐�
int TetrisCombo(void);			// �R���{����Ԃ�l�Ƃ���֐�
bool Gameover(void);
