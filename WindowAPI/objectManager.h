#pragma once
#include "singletonBase.h"
#include "objects.h"

class playerManager;

struct fPos
{
	float x;
	float y;
};
class objectManager : public singletonBase<objectManager>
{
	vector<objects*> _vObject;
	objectFactory* _factory;
	playerManager* _playerManager;
	fPos _chipGreenPos[7];
	fPos _chipBluePos[8];
	fPos _chipPurplePos[1];
	fPos _heartYellowPos[1];
	fPos _bloomFlowerPos[7];
	fPos _mineralPos[1];
	fPos _blueFlowerPos[1];
	int _bloomFlowerCount[7];
	int _mineralCount[1];
	int _blueFlowerCount[1];
	bool _isGameClear;

public:
	vector<objects*> getVObject() { return _vObject; }
	bool getGameClear() { return _isGameClear; }

	void setPlayerManager(playerManager* playerManager) { _playerManager = playerManager; }
	void collisionProcess();
	//������Ʈ�Ŵ��� �ʱ�ȭ
	HRESULT init(int num);
	//������Ʈ�Ŵ��� ����
	void release();
	void update();
	void render(HDC hdc);
	objectManager() {}
	~objectManager() {}
};