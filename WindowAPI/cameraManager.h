#pragma once
#include "singletonBase.h"
class cameraManager : public singletonBase<cameraManager>
{
	RECT _rcCamera;
	RECT _rcTemp;
	int _shakeCount;
	bool _shakeStart;
	int _maxWidth, _maxHeight;
public:
	RECT getCamera() { return _rcCamera; }
	int getMaxWidth() { return _maxWidth; }
	int getMaxHeight() { return _maxHeight; }

	void setCamera(RECT rc) { _rcCamera = rc; }
	void setRange(int width, int height) { _maxWidth = width; _maxHeight = height; }
	
	bool CameraIn(RECT rc);
	void CameraShakeOngoing();
	void CameraShake();

	//ī�޶�Ŵ��� �ʱ�ȭ
	HRESULT init();
	void update();
	//ī�޶�Ŵ��� ����
	void release();

	cameraManager() {}
	~cameraManager() {}
};