#pragma once
#include "singletonBase.h"
class cameraManager : public singletonBase<cameraManager>
{
	RECT _rcCamera;
	RECT _rcTemp;
	RECT _rcLetterBox[2];
	float _button_switch_x, _button_switch_y;
	int _maxWidth, _maxHeight;
	int _shakeCount;
	int _pauseCount;
	bool _shakeStart;
	bool _switchStart;
	bool _boomerangStart;
	bool _isFade;
	float _originX, _originY;
	float _startX, _startY;
	float _destX, _destY;
	BYTE _button_switch_alpha;
	BYTE _alpha;

public:
	RECT getCamera() { return _rcCamera; }
	int getMaxWidth() { return _maxWidth; }
	int getMaxHeight() { return _maxHeight; }
	bool getSwitchStart() { return _switchStart; }
	bool getIsFade() { return _isFade; }

	void setCamera(RECT rc) { _rcCamera = rc; }
	void setRange(int width, int height) { _maxWidth = width; _maxHeight = height; }
	void setSwitchStart(bool switchStart) { _switchStart = switchStart; }
	
	bool CameraIn(RECT rc);
	void CameraShakeOngoing();
	void CameraShake();
	void CameraSwitch(float startX, float startY, float destX, float destY, bool isFade = false);
	void CameraBoomerang(float startX, float startY, float destX, float destY);
	void CameraBoomerangOngoing();
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