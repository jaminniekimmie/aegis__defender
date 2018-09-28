#pragma once
#include "singletonBase.h"
#include "objects.h"

class playerManager;

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
	fPos _mineralPos[2];
	fPos _blueFlowerPos[1];
	fPos _spawnerPos[2];
	fPos _doorDNAyellowLeftPos[1];
	fPos _doorDNAyellowRightPos[1];
	fPos _doorDNAblueLeftPos[1];
	fPos _doorDNAblueRightPos[1];
	fPos _doorElevatorPos[1];
	fPos _bushSpikesPos[1];
	fPos _ventPos[14];
	fPos _switchHorPos[2];
	float _ventRange[14];
	int _bloomFlowerCount[7];
	int _mineralCount[1];
	int _blueFlowerCount[1];
	bool _isGameClear;
	bool _isHit;
	BYTE _alpha;

public:
	vector<objects*> getVObject() { return _vObject; }
	bool getGameClear() { return _isGameClear; }

	void setPlayerManager(playerManager* playerManager) { _playerManager = playerManager; }
	void collisionProcess();
	//오브젝트매니져 초기화
	HRESULT init(int num);
	//오브젝트매니져 해제
	void release();
	void update();
	void render(HDC hdc);
	objectManager() {}
	~objectManager() {}
};