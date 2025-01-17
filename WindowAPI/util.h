#pragma once
//=============================================================
//	## namespace MY_UTIL ##
//=============================================================

#define PI 3.141592654f		//180도
#define PI2 (PI * 2)			//360도

//나중에 이미지 회전시 사용할 값
#define PI_2 (PI / 2)		//90도
#define PI_4 (PI / 4)		//45도
#define PI_8 (PI / 8)		//22.5도

#define MAXPLAYERSTATE 34
#define MAXMONSTERSTATE 5
#define MAXOBJECTSTATE 4

#define YELLOW 1
#define BRIGHT_YELLOW 2
#define RED 3
#define BRIGHT_RED 4
#define BLUE 5
#define BRIGHT_BLUE 6

enum PLAYERCHARACTER
{
	CLU, BART
};

enum PLAYERSTATE
{
	AIM_DIAGONAL, AIM_DIAGONAL_FULLCHARGE, AIM_DIAGONAL_FULLCHARGE_IDLE, AIM_DIAGONALFIRE, AIM_FIRE, AIM_IDLE, BACKSTEP,
	BORED, BORED_IDLE, CHARGE, FAINT, FAINT_IDLE, FULLCHARGE, FULLCHARGE_IDLE, HIT, IDLE, JUMP_FALL, JUMP_RISE, JUMPFIRE_FALL, JUMPFIRE_RISE, 
	JUMPFIREDIAGONAL_FALL, JUMPFIREDIAGONAL_RISE, LAND, LAUGH, LAUGH_IDLE, LEDGEGRAB, LEDGEGRAB_IDLE, LEDGEGRAB_RISE, LOOKUP, PUSH, RUN, THINK, THINK_IDLE, UPSET
};

enum PLAYERWEAPON
{
	GUN, BOW
};

enum MONSTERTYPE
{
	SANDWORM, SPIDERBABY, FIREDRINKERFLY, EAGLE, THIEF_BOOMERANG, MASK
};

enum MONSTERSTATE
{
	MONSTER_IDLE, MONSTER_MOVE, MONSTER_HIT, MONSTER_DEAD, MONSTER_ITEM
};

enum OBJECTTYPE
{
	CHIP_GREEN, CHIP_BLUE, CHIP_PURPLE, CHIP_WHITE, HEART_RED, HEART_YELLOW, BLOOMFLOWER, MINERAL, BLUEFLOWER, SPAWNER, DOOR_DNA_YELLOW_LEFT, DOOR_DNA_YELLOW_RIGHT, DOOR_DNA_BLUE_LEFT, DOOR_DNA_BLUE_RIGHT, DOOR_ELEVATOR, SWITCH_HOR, SWITCH_VERT, BUSH_SPIKES, VENT, AEGIS
};

enum OBJECTSTATE
{
	OBJECT_IDLE, OBJECT_MOVE, OBJECT_ITEM, OBJECT_VANISH
};

enum DIRECTION
{
	RIGHT, LEFT, TOP, BOTTOM
};

namespace MY_UTIL //이름은 너희맘대로 변경해도 된다
{
	//두점 사이의 거리
	float getDistance(float startX, float startY, float endX, float endY);
	//두점 사이의 각도
	float getAngle(float startX, float startY, float endX, float endY);
	//씬의 제목보여주기
	void showTitle(HDC hdc, const char* title, int x = 0, int y = 70, COLORREF color = RGB(255, 255, 0));
};

struct fPos
{
	float x;
	float y;
};