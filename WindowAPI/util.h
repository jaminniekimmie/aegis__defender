#pragma once
//=============================================================
//	## namespace MY_UTIL ##
//=============================================================

#define PI 3.141592654f		//180��
#define PI2 (PI * 2)			//360��

//���߿� �̹��� ȸ���� ����� ��
#define PI_2 (PI / 2)		//90��
#define PI_4 (PI / 4)		//45��
#define PI_8 (PI / 8)		//22.5��

#define MAXPLAYERSTATE 24

enum PLAYERSTATE
{
	AIM_DIAGONAL, AIM_DIAGONAL_FULLCHARGE, AIM_DIAGONALFIRE, AIM_FIRE, AIM_IDLE, BACKSTEP,
	BORED, CHARGE, FAINT, FAINT_IDLE, FULLCHARGE, HIT, IDLE, JUMP_FALL, JUMP_RISE, JUMPFIRE_FALL,
	JUMPFIRE_RISE, JUMPFIREDIAGONAL_FALL, JUMPFIREDIAGONAL_RISE, LAND, LEDGEGRAB, LOOKUP, PUSH, RUN
};

enum DIRECTION
{
	RIGHT, LEFT
};

namespace MY_UTIL //�̸��� ���񸾴�� �����ص� �ȴ�
{
	//���� ������ �Ÿ�
	float getDistance(float startX, float startY, float endX, float endY);
	//���� ������ ����
	float getAngle(float startX, float startY, float endX, float endY);
	//���� ���񺸿��ֱ�
	void showTitle(HDC hdc, const char* title, int x = 0, int y = 70, COLORREF color = RGB(255, 255, 0));
};

