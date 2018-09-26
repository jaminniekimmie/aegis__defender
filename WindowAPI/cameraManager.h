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
	bool _effects;
	float _startX, _startY;
	float _destX, _destY;
	BYTE _alpha;

public:
	RECT getCamera() { return _rcCamera; }
	int getMaxWidth() { return _maxWidth; }
	int getMaxHeight() { return _maxHeight; }
	bool getSwitchStart() { return _switchStart; }

	void setCamera(RECT rc) { _rcCamera = rc; }
	void setRange(int width, int height) { _maxWidth = width; _maxHeight = height; }
	void setSwitchStart(bool switchStart) { _switchStart = switchStart; }
	
	bool CameraIn(RECT rc);
	void CameraShakeOngoing();
	void CameraShake();
	void CameraSwitch(float startX, float startY, float destX, float destY, bool effects = false);
	void CameraSwitchOngoing();
	void CameraAdjustment();

	//카메라매니져 초기화
	HRESULT init(void);
	//카메라매니져 해제
	void release(void);
	void update(void);
	void render(HDC hdc);

	cameraManager() {}
	~cameraManager() {}
};