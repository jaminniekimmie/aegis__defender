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

void cameraManager::CameraSwitch(float startX, float startY, float destX, float destY)
{
	_startX = startX;
	_startY = startY;
	_destX = destX;
	_destY = destY;
	_switchStart = true;
}

void cameraManager::CameraSwitchOngoing()
{
	if (_switchStart)
	{
		float distance = getDistance(_startX, _startY, _destX, _destY);
		float angle = getAngle(_startX, _startY, _destX, _destY);
		float speed = 20.0f;

		if (distance > speed)
		{
			_startX += cosf(angle) * speed;
			_startY += -sinf(angle) * speed;
		}
		else
		{
			_switchStart = false;
			EFFECTMANAGER->play("ellipsePuff2", _destX, _destY + 58);
			EFFECTMANAGER->play("regen", _destX, _destY + 90);
		}

		RECT _rc = RectMakeCenter(_startX, _startY, WINSIZEX, WINSIZEY);
		this->setCamera(_rc);
	}
}

HRESULT cameraManager::init()
{
	_switchStart = false;
	_shakeStart = false;
	_shakeCount = 0;
	return S_OK;
}

void cameraManager::update()
{
	CameraShakeOngoing();
	CameraSwitchOngoing();
}

void cameraManager::release()
{
}
