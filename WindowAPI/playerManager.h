#pragma once
#include "gameNode.h"
#include "player.h"
#include "bullet.h"			//�̻��� Ŭ���� ����ϱ� ����

class playerManager : public gameNode
{
private:
	player * _player;
	bullet * _bullet;
	triBullet * _triBullet;
	int _idleCount;
	int _idleMax;
	bool _isStayKey_up;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	player * getPlayer() { return _player; }
	
	void keyInput();
	void playerRun(bool isLeft);
	void playerJumpFall();
	void playerFaceDown();
	void playerBackstep();
	void playerFullCharge();
	void playerLaugh();
	void playerThink();
	void playerBored();
	void collisionProcess();
	void fromStateToIdle();
	void fromIdleToState();
	void bulletFire();

	playerManager() {}
	~playerManager() {}
};

