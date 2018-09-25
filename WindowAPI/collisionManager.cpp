#include "stdafx.h"
#include "collisionManager.h"

int collisionManager::pixelCollision(RECT rc, float& x, float& y, float speed, float gravity, int dir)
{
	int _speed = (int)speed; //명시적
	int _gravity = (int)gravity; //명시적
	switch (dir)
	{
	case LEFT: //left
		for (int i = rc.left + _speed; i >= rc.left; i--)
		{
			COLORREF color = GetPixel(_pixelTiles->getMemDC(), i, y);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (r == 244 && g == 180 && b == 23)
			{
				x = i + 7 + (rc.right - rc.left) * 0.5f;
			
				return YELLOW;
			}
		}
		break;
	case TOP:
		for (int i = rc.top + _speed; i >= rc.top; i--)
		{
			COLORREF color = GetPixel(_pixelTiles->getMemDC(), x, i);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (r == 244 && g == 180 && b == 23)
			{
				y = i + 1 + (rc.bottom - rc.top) * 0.5f;

				return YELLOW;
			}
		}
		break;
	case RIGHT:
		for (int i = rc.right - _speed; i <= rc.right; i++)
		{
			COLORREF color = GetPixel(_pixelTiles->getMemDC(), i, y + 20);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (r == 244 && g == 180 && b == 23)
			{
				x = i - 7 - (rc.right - rc.left) * 0.5f;

				return YELLOW;
			}
		}
		break;
	case BOTTOM:
		for (int i = rc.bottom - (_speed + _gravity) - 10; i <= rc.bottom + 5; i++)
		{
			COLORREF color = GetPixel(_pixelTiles->getMemDC(), x, i);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if ((r == 244 && g == 180 && b == 23))
			{
				y = i - 1 - (rc.bottom - rc.top) * 0.5f;

				return YELLOW;
			}

			if ((r == 58 && g == 213 && b == 255))
			{
				y = i - 1 - (rc.bottom - rc.top) * 0.5f;

				return BLUE;
			}
		}
		break;
	}

	return FALSE;
}

HRESULT collisionManager::init()
{
	return S_OK;
}

void collisionManager::release()
{
}
