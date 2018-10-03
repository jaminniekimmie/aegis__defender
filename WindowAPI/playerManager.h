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
	arrow * _arrow;
	triArrow * _triArrow;
	block * _block[2];
	tagSave _saveProperties[30];
	tagImage _icon[2];
	tagImage _blueFlower;
	tagImage _mineral;
	tagImage _button_bomb;
	int _blueFlowerCount;
	int _blueFlowerMax;
	int _mineralCount;
	int _mineralMax;
	int _idleCount;
	int _idleMax;
	int _saveCount, _saveIndex;
	int _blackSolidAlpha;
	bool _isFollowing;
	bool _isStayKey_up;
	bool _isStayKey_down;
	bool _isBuild;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void setCharacter(PLAYERCHARACTER character) { _character = character; }

	player * getPlayer(PLAYERCHARACTER character) { return _player[character]; }
	player * getPlayer() { return _player[_character]; }
	PLAYERCHARACTER getCharacter() { return _character; }
	bullet * getBullet() { return _bullet; }
	triBullet * getTriBullet() { return _triBullet; }
	arrow * getArrow() { return _arrow; }
	triArrow * getTriArrow() { return _triArrow; }
	block * getBlock(PLAYERCHARACTER character) { return _block[character]; }

	void setFollow();
	void setGUI();
	void GUIupdate();
	void GUIrender();
	void buildRender();

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
	void playerBuild();
	void playerFollow();
	void playerFaint();

	void addBlueFlower();
	void addMineral();
	void blockCollision();

	playerManager() {}
	~playerManager() {}
};

