#pragma once
#include "gameNode.h"
#include "player.h"
#include "bullet.h"			//미사일 클래스 사용하기 위해

class playerManager : public gameNode
{
private:
	player * _player;
	bullet * _bullet;
	triBullet * _triBullet;
	int _idleCount;
	bool _isStayKey_up;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	player * getPlayer() { return _player; }
	
	void playerRun(bool isLeft);
	void playerJumpFall();
	void playerBackstep();
	void playerFullCharge();
	void playerLaugh();
	void collisionProcess();
	void fromStateToIdle();
	void fromIdleToState();
	void bulletFire();

	playerManager() {}
	~playerManager() {}
};

