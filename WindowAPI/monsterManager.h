#pragma once
#include "singletonBase.h"
#include "monster.h"

class playerManager;

struct fPos
{
	float x;
	float y;
};

class monsterManager : public singletonBase<monsterManager>
{
	vector<monster*> _vMonster;
	monsterFactory* _factory;
	playerManager* _playerManager;
	fPos _cricketPos[2];
	fPos _rolyPolyLargePos[1];
	fPos _rolyPolyWhitePos[3];
	bool _isGameClear;
	bool _isDead;
public:
	vector<monster*> getVMonster() { return _vMonster; }
	bool getGameClear() { return _isGameClear; }

	void setIsDead(bool isDead) { _isDead = isDead; }
	void setPlayerManager(playerManager* playerManager) { _playerManager = playerManager; }
	void collisionProcess();
	//������Ʈ�Ŵ��� �ʱ�ȭ
	HRESULT init(int scene);
	//������Ʈ�Ŵ��� ����
	void release();
	void update();
	void render(HDC hdc);

	monsterManager() {}
	~monsterManager() {}
};