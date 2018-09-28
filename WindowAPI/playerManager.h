#pragma once
#include "gameNode.h"
#include "player.h"
#include "bullet.h"			//미사일 클래스 사용하기 위해

struct tagSave
{
	PLAYERSTATE state;
	float x, y;
	float angle;
	float gravity;
	float speed;
	float count;
	float index;
	float frameSpeed;
	bool isLeft;
};

class playerManager : public gameNode
{
private:
	PLAYERCHARACTER _character;
	player * _player[2];
	bullet * _bullet;
	triBullet * _triBullet;
	tagSave _saveProperties[30];
	int _idleCount;
	int _idleMax;
	int _saveCount, _saveIndex;
	bool _isFollowing;
	bool _isStayKey_up;
	bool _isStayKey_down;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	player * getPlayer(PLAYERCHARACTER character) { return _player[character]; }
	//player * getClu() { return _player[CLU]; }
	//player * getBart() { return _player[BART]; }
	PLAYERCHARACTER getCharacter() { return _character; }
	bullet * getBullet() { return _bullet; }
	triBullet * getTriBullet() { return _triBullet; }

	void keyInput();
	void playerRun(bool isLeft);
	void playerJumpRise();
	void playerJumpFall();
	void collisionProcess();
	void playerLand();
	void playerFaceDown();
	void playerBackstep();
	void playerFullCharge();
	void playerLedgeGrab();
	void fromStateToIdle();
	void fromIdleToState();
	void playerLaugh();
	void playerThink();
	void playerBored();
	void playerHit();
	void playerUpset();
	void bulletFire();
	void hammer();
	void playerAttack();
	void playerFollow();

	playerManager() {}
	~playerManager() {}
};

