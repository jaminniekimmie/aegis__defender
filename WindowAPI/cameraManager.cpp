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

HRESULT cameraManager::init()
{
	_shakeStart = false;
	_shakeCount = 0;
	return S_OK;
}

void cameraManager::update()
{
	CameraShakeOngoing();
}

void cameraManager::release()
{
}
