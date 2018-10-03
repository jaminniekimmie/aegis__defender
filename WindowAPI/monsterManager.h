#pragma once
#include "singletonBase.h"
#include "monster.h"

class playerManager;

class monsterManager : public singletonBase<monsterManager>
{
	vector<monster*> _vMonster;
	monsterFactory* _factory;
	playerManager* _playerManager;
	fPos _sandwormPos[4];
	fPos _spiderBabyPos[7];
	fPos _firedrinkerFlyPos[3];
	fPos _eaglePos[2];
	fPos _thiefBoomerangPos[3];
	fPos _maskPos[2];
	float _sandwormRange[4];
	float _spiderBabyRange[7];
	float _firedrinkerFlyRange[3];
	float _eagleRange[2];
	float _thiefBoomerangRange[3];
	float _maskRange[2];
	bool _isGameClear;
	bool _isDead;
	bool _isHit;
	BYTE _alpha;

public:
	vector<monster*> getVMonster() { return _vMonster; }
	bool getGameClear() { return _isGameClear; }

	void setIsDead(bool isDead) { _isDead = isDead; }
	void setPlayerManager(playerManager* playerManager) { _playerManager = playerManager; }
	void collisionProcess();
	void collisionBullet(int index, vector<tagBullet> bullet);
	void monsterHurt(int index);
	//오브젝트매니져 초기화
	HRESULT init(int scene);
	//오브젝트매니져 해제
	void release();
	void update();
	void render(HDC hdc);

	monsterManager() {}
	~monsterManager() {}
};