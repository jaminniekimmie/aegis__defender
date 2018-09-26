#pragma once
#include "singletonBase.h"
class cameraManager : public singletonBase<cameraManager>
{
	RECT _rcCamera;
	RECT _rcTemp;
	int _maxWidth, _maxHeight;
	int _shakeCount;
	bool _shakeStart;
	bool _switchStart;
	float _startX, _startY;
	float _destX, _destY;
public:
	RECT getCamera() { return _rcCamera; }
	int getMaxWidth() { return _maxWidth; }
	int getMaxHeight() { return _maxHeight; }

	void setCamera(RECT rc) { _rcCamera = rc; }
	void setRange(int width, int height) { _maxWidth = width; _maxHeight = height; }
	
	bool CameraIn(RECT rc);
	void CameraShakeOngoing();
	void CameraShake();
	void CameraSwitch(float startX, float startY, float destX, float destY);
	void CameraSwitchOngoing();

	//카메라매니져 초기화
	HRESULT init();
	void update();
	//카메라매니져 해제
	void release();

	cameraManager() {}
	~cameraManager() {}
};