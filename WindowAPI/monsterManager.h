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
	float _sandwormRange[4];
	float _spiderBabyRange[7];
	float _firedrinkerFlyRange[3];
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
	void monsterHurt();
	//������Ʈ�Ŵ��� �ʱ�ȭ
	HRESULT init(int scene);
	//������Ʈ�Ŵ��� ����
	void release();
	void update();
	void render(HDC hdc);

	monsterManager() {}
	~monsterManager() {}
};