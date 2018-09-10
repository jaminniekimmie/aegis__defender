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

			if ((r == 244 && g == 180 && b == 23))
			{
				x = i + 1;
			
				return TRUE;
			}
		}
		break;
	case TOP: //top
		for (int i = rc.top + _speed; i >= rc.top; i--)
		{
			COLORREF color = GetPixel(_pixelTiles->getMemDC(), x, i);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if ((r == 244 && g == 180 && b == 23))
			{
		//		y = i + 1;

				return TRUE;
			}
		}
		break;
	case RIGHT: //right
		for (int i = rc.right - _speed; i <= rc.right; i++)
		{
			COLORREF color = GetPixel(_pixelTiles->getMemDC(), i, y);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if ((r == 244 && g == 180 && b == 23))
			{
				x = i - 1 - (rc.right - rc.left) / 2;

				return TRUE;
			}
		}
		break;
	case BOTTOM: //bottom
		for (int i = rc.bottom - (_speed + _gravity); i <= rc.bottom; i++)
		{
			COLORREF color = GetPixel(_pixelTiles->getMemDC(), x, i);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if ((r == 244 && g == 180 && b == 23))
			{
				y = i - 1 - (rc.bottom - rc.top) * 0.5;

				return TRUE;
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
