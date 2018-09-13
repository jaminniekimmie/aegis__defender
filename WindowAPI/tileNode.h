#pragma once

//����ȭ��Ÿ�� (ȭ�� ����) 
#define TILESIZE 120
#define TILEX 50
#define TILEY 50
#define TILESIZEX (TILEX * TILESIZE)
#define TILESIZEY (TILEY * TILESIZE)

//�̹���Ÿ��
#define SAMPLETILEX 93
#define SAMPLETILEY 2

//�������� ����� �̳ѹ�
enum CTRL
{
	CTRL_SAVE, CTRL_LOAD,
	CTRL_TERRAINDRAW, CTRL_OBJDRAW, CTRL_ERASER,
	CTRL_MAP1, CTRL_MAP2, CTRL_MAP3, CTRL_END
};

//����
enum TERRAIN
{
	TR_GROUND, TR_NONE
};

//������Ʈ
enum OBJECT
{
	OBJECT_ROCK, OBJECT_BGROCK, OBJECT_TREE, OBJECT_BRIDGE, OBJECT_NONE
};

//��ġ��ǥ
enum POS
{
	POS_TANK1, POS_TANK2, POS_FLAG1, POS_FLAG2
};

/*Ÿ�ϱ���ü*/
struct tagTile
{
	TERRAIN terrain;
	OBJECT obj;
	RECT rc;
	BYTE alpha;

	//string tileLabel;
	char tileLabel[256];
	image* img;
	int terrainFrameX;
	int terrainFrameY;
	int objFrameX;
	int objFrameY;
};

//�̹��� Ÿ�ϱ���ü
struct tagSampleTile
{
	TERRAIN terrain;
	OBJECT obj;
	RECT rc;
	BYTE alpha;
	
	image* backdrop;
	int terrainFrameX;
	int terrainFrameY;
	int objFrameX;
	int objFrameY;
};

//����Ÿ�� ����ü
struct tagCurrentTile
{
	int x, y;
};


struct tagImage
{
	RECT rc;
	image* img;
	image* shadow;
	BYTE alpha;
	bool isActive;
};


//struct tagImage
//{
//	RECT rc;
//	image* img;
//	BYTE alpha;
//};