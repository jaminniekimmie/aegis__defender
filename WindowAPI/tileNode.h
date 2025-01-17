#pragma once

//게임화면타일 (화면 왼쪽) 
#define TILESIZE 120
#define TILEX 62
#define TILEY 15
#define TILESIZEX (TILEX * TILESIZE)
#define TILESIZEY (TILEY * TILESIZE)

//이미지타일
#define SAMPLETILEX 93
#define SAMPLETILEY 2

//맵툴에서 사용할 이넘문
enum CTRL
{
	CTRL_SAVE, CTRL_LOAD,
	CTRL_TERRAINDRAW, CTRL_OBJDRAW, CTRL_ERASER,
	CTRL_MAP1, CTRL_MAP2, CTRL_MAP3, CTRL_END
};

//지형
enum TERRAIN
{
	TR_GROUND, TR_NONE
};

//오브젝트
enum OBJECT
{
	OBJECT_ROCK, OBJECT_BGROCK, OBJECT_TREE, OBJECT_BRIDGE, OBJECT_NONE
};

//위치좌표
enum POS
{
	POS_TANK1, POS_TANK2, POS_FLAG1, POS_FLAG2
};

/*타일구조체*/
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

//이미지 타일구조체
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

//현재타일 구조체
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
	float x, y;
	float gravity;
	float speed;
	bool isActive;
	int count;
};


struct tagElement
{
	image* elementImg;
	RECT rc;
	float x, y;
	float fireX, fireY;
	float speed;
	float angle;
	float gravity;
	float radius;
	bool fire;
	bool isActive;
	bool isFrameImg;
	int alpha;
	int count;
	int index;
};

//총알 구조체
struct tagBullet
{
	image* bulletImage;
	image* shadowImage;
	RECT rc;
	BYTE alpha;
	float x, y;
	float fireX, fireY;
	float speed;
	float angle;
	float gravity;
	float radius;
	bool fire;
	int index;
	int count;
	int fadeCount;
};

//struct tagImage
//{
//	RECT rc;
//	image* img;
//	BYTE alpha;
//};