#include "stdafx.h"
#include "cameraManager.h"

bool cameraManager::CameraIn(RECT rc)
{
	if (IntersectRect(&_rcTemp, &RectMake(_rcCamera.left, _rcCamera.top, WINSIZEX, WINSIZEY), &rc))
		return true;
	else
		return false;
}

void cameraManager::CameraShakeOngoing()
{
	if (_shakeStart)
	{
		_shakeCount++;
		_rcCamera = RectMake(_rcCamera.left + RND->getInt(10) - 10, _rcCamera.top + RND->getInt(10) - 10, WINSIZEX, WINSIZEY);
	}

	if (_shakeCount > 5)
	{
		_shakeStart = false;
		_shakeCount = 0;
	}
}

void cameraManager::CameraShake()
{
	_shakeStart = true;
}

void cameraManager::CameraSwitch(float startX, float startY, float destX, float destY, bool isFade)
{
	_startX = startX;
	_startY = startY;
	_destX = destX;
	_destY = destY;
	_isFade = isFade;
	_switchStart = true;
}

void cameraManager::CameraBoomerang(float startX, float startY, float destX, float destY)
{
	_startX = _originX = startX;
	_startY = _originY = startY;
	_destX = destX;
	_destY = destY;
	_pauseCount = 0;
	_boomerangStart = true;
	_boomerangEnd = false;
}

void cameraManager::CameraBoomerangOngoing()
{
	if (_boomerangStart)
	{
		float distance = getDistance(_startX, _startY, _destX, _destY);
		float angle = getAngle(_startX, _startY, _destX, _destY);
		float speed = distance / 5;
		
		if (speed > 1)
		{
			_startX += cosf(angle) * speed;
			_startY += -sinf(angle) * speed;
		}
		else
		{
			if (!_boomerangEnd && (_startX - _originX < 10 || _originX - _startX < 10))
				_boomerangStart = false;

			if (_pauseCount < 40)
				_pauseCount++;
			else
			{
				_destX = _originX;
				_destY = _originY;
				_boomerangEnd = false;
			}	
		}

		RECT _rc = RectMakeCenter(_startX, _startY, WINSIZEX, WINSIZEY);
		this->setCamera(_rc);

		if (_rcLetterBox[0].bottom < 80 && _rcLetterBox[1].top > WINSIZEY - 80)
		{
			_rcLetterBox[0].bottom += -sinf(-PI_2) * 5.0f;
			_rcLetterBox[1].top += -sinf(PI_2) * 5.0f;
		}
	}
	else
	{
		if (_rcLetterBox[0].bottom > 0 && _rcLetterBox[1].top < WINSIZEY)
		{
			_rcLetterBox[0].bottom += sinf(-PI_2) * 5.0f;
			_rcLetterBox[1].top += sinf(PI_2) * 5.0f;
		}
	}
}

void cameraManager::CameraSwitchOngoing()
{
	if (_switchStart)
	{
		float distance = getDistance(_startX, _startY, _destX, _destY);
		float angle = getAngle(_startX, _startY, _destX, _destY);
		float speed = distance / 5;

		if (distance > 0)
		{
			_startX += cosf(angle) * speed;
			_startY += -sinf(angle) * speed;
			if (_isFade && _alpha < 180)
				_alpha += 15;
		}

		if (_isFade)
		{
			if (_button_switch_y > 663)
				_button_switch_y -= 663 / 80;
			if (_button_switch_alpha < 255)
				_button_switch_alpha += 15;
		}

		RECT _rc = RectMakeCenter(_startX, _startY, WINSIZEX, WINSIZEY);
		this->setCamera(_rc);
	}
	else
	{
		if (_isFade && _alpha > 0)
			_alpha -= 15;

		if (_button_switch_y < WINSIZEY)
			_button_switch_y += 663 / 80;
		if (_button_switch_alpha > 0)
			_button_switch_alpha -= 15;
	}
}

void cameraManager::CameraAdjustment()
{
	if (_rcCamera.left <= 0)
	{
		_rcCamera.left = 0;
		_rcCamera.right = _rcCamera.left + WINSIZEX;
	}
	else if (_rcCamera.right >= _maxWidth)
	{
		_rcCamera.left = _maxWidth - WINSIZEX;
		_rcCamera.right = _rcCamera.left + WINSIZEX;
	}
	if (_rcCamera.top <= 0)
	{
		_rcCamera.top = 0;
		_rcCamera.bottom = _rcCamera.top + WINSIZEY;
	}
	else if (_rcCamera.bottom >= _maxHeight)
	{
		_rcCamera.top = _maxHeight - WINSIZEY;
		_rcCamera.bottom = _rcCamera.top + WINSIZEY;
	}
}

HRESULT cameraManager::init(void)
{
	_switchStart = false;
	_shakeStart = false;
	_boomerangStart = false;
	_boomerangEnd = false;
	_isFade = false;
	_pauseCount = 0;
	_shakeCount = 0;
	_alpha = 0;

	_button_switch_x = 671, _button_switch_y = WINSIZEY;
	_button_switch_alpha = 0;

	_rcLetterBox[0] = RectMake(0, 0, WINSIZEX, 0);
	_rcLetterBox[1] = RectMake(0, WINSIZEY, WINSIZEX, 0);

	return S_OK;
}

void cameraManager::release(void)
{
}

void cameraManager::update(void)
{
	this->CameraShakeOngoing();
	this->CameraSwitchOngoing();
	this->CameraBoomerangOngoing();
	this->CameraAdjustment();
}

void cameraManager::render(HDC hdc)
{
	SelectObject(hdc, GetStockObject(DC_BRUSH));
	SetDCBrushColor(hdc, RGB(0, 0, 0));
	SelectObject(hdc, GetStockObject(DC_PEN));
	SetDCPenColor(hdc, RGB(0, 0, 0));
	
	Rectangle(hdc, _rcLetterBox[0]);
	Rectangle(hdc, _rcLetterBox[1]);

	if (_isFade)
		IMAGEMANAGER->alphaRender("solid_black", hdc, _alpha);

	IMAGEMANAGER->alphaRender("GUI_button_switch", hdc, _button_switch_x, _button_switch_y, _button_switch_alpha);
}

