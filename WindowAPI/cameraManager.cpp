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

void cameraManager::CameraSwitch(float startX, float startY, float destX, float destY, bool effects)
{
	_startX = startX;
	_startY = startY;
	_destX = destX;
	_destY = destY;
	_effects = _effects;
	_switchStart = true;
	//_alpha = 0;
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
			if (_alpha < 180)
				_alpha += 15;
		}
		else
		{
			//_switchStart = false;
			//if (_effects)
			//{
			//	EFFECTMANAGER->play("ellipsePuff2", _destX, _destY + 58);
			//	EFFECTMANAGER->play("regen", _destX, _destY + 90);
			//}
		}

		RECT _rc = RectMakeCenter(_startX, _startY, WINSIZEX, WINSIZEY);
		this->setCamera(_rc);
	}
	else
	{
		if (_alpha > 0)
			_alpha -= 15;
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
	_shakeCount = 0;
	_alpha = 0;
	return S_OK;
}

void cameraManager::release(void)
{
}

void cameraManager::update(void)
{
	CameraShakeOngoing();
	CameraSwitchOngoing();
	CameraAdjustment();
}

void cameraManager::render(HDC hdc)
{
	IMAGEMANAGER->alphaRender("solid_black", hdc, _alpha);
}

