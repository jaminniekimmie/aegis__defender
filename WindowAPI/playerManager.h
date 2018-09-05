#pragma once
#include "gameNode.h"
#include "player.h"
#include "bullet.h"			//미사일 클래스 사용하기 위해

class playerManager : public gameNode
{
private:
	player * _player;
	bullet * _bullet;
	int _count;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	player * getPlayer() { return _player; }
	
	void playerRun();
	void playerJumpFall();
	void playerBackstep();
	void collisionProcess();
	void fromStateToIdle();
	void bulletFire();

	playerManager() {}
	~playerManager() {}
};

