#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include "pHpBar.h"

//#include "enemyManager.h"
//적매니져 상호참조하기 위해 클래스 전방선언

class player : public gameNode
{
private:
	PLAYERCHARACTER _character;
	PLAYERSTATE _state;
	DIRECTION _direction;
	RECT _rc;
	RECT _rcLedge[2];
	RECT _rcHammer;
	tagImage _player[MAXPLAYERSTATE];
	tagImage _weapon[2][MAXPLAYERSTATE];
	tagImage _weaponIcon[2];
	float _x, _y;
	float _oldX, _oldY;
	float _gravity;
	float _speed;
	float _angle;
	int _frameSpeed;
	int _index;
	int _count;
	int _weaponCount;
	bool _isLeft;
	bool _isJump;
	bool _isFall;
	bool _isBackstep;
	bool _isJumpDown;
	bool _isFaceDown;
	bool _onLand;
	bool _isLedgeGrab;
	bool _isFired;
	bool _isActive;
	bool _currentWeapon;
	bool _weaponSwitch;

	pHpBar * _hpBar_red;		//체력바
	pHpBar * _hpBar_yellow;		//체력바
	float _maxHp, _currentHp, _currentMp;	//최대체력, 현재체력

public:
	HRESULT init(PLAYERCHARACTER character);
	void release(void);
	void update(void);
	void render(void);

	//체력바 피통깍기
	void hitDamage(float damage);
	void addHp();
	void addMp();
	void frameChangeLoop();
	void setCharacter(PLAYERCHARACTER character);
	void setHpBar();
	void weaponSwitch();
	void rectUpdate();
	void collisionProcess();

	pHpBar * getHpBarRed() { return _hpBar_red; }
	pHpBar * getHpBarYellow() { return _hpBar_yellow; }
	PLAYERSTATE getState() { return _state; }
	RECT getRect() { return _rc; }
	RECT getLedgeRc(int num) { return _rcLedge[num]; }
	RECT getHammerRc() { return _rcHammer; }
	DIRECTION getDirection() { return _direction; }
	image* getPlayerImage(PLAYERSTATE state) { return _player[state].img; }
	image* getPlayerImage() { return _player[_state].img; }
	int getFrameSpeed() { return _frameSpeed; }
	int getIndex() { return _index; }
	int getCount() { return _count; }
	float getX() { return _x; }
	float getY() { return _y; }
	float getOldX() { return _oldX; }
	float getOldY() { return _oldY; }
	float getGravity() { return _gravity; }
	float getSpeed() { return _speed; }
	float getAngle() { return _angle; }
	float getAlpha() { return _player[_state].alpha; }
	float getCurrentHp() { return _currentHp; }
	bool getIsLeft() { return _isLeft; }
	bool getIsJump() { return _isJump; }
	bool getIsFall() { return _isFall; }
	bool getOnLand() { return _onLand; }
	bool getIsBackstep() { return _isBackstep; }
	bool getIsJumpDown() { return _isJumpDown; }
	bool getIsFaceDown() { return _isFaceDown; }
	bool getIsLedgeGrab() { return _isLedgeGrab; }
	bool getIsFired() { return _isFired; }
	bool getIsActive() { return _isActive; }
	bool getCurrentWeapon() { return _currentWeapon; }

	void setState(PLAYERSTATE playerState) { _state = playerState; }
	void setRect(RECT rc) { _rc = rc; }
	void setDirection(DIRECTION direction) { _direction = direction; }
	void setFrameSpeed(int animationSpeed) { _frameSpeed = animationSpeed; }
	void setIndex(int index) { _index = index; }
	void setCount(int count) { _count = count; }
	void setX(float x) { _x = x; }
	void setY(float y) { _y = y; }
	void setOldX(float oldX) { _x = oldX; }
	void setOldY(float oldY) { _y = oldY; }
	void setGravity(float gravity) { _gravity = gravity; }
	void setSpeed(float speed) { _speed = speed; }
	void setAngle(float angle) { _angle = angle; }
	void setAlpha(BYTE alpha) { _player[_state].alpha = alpha; }
	void setIsLeft(bool isLeft) { _isLeft = isLeft; }
	void setIsJump(bool isJump) { _isJump = isJump; }
	void setIsFall(bool isFall) { _isFall = isFall; }
	void setOnLand(bool onLand) { _onLand = onLand; }
	void setIsBackstep(bool isBackstep) { _isBackstep = isBackstep; }
	void setIsJumpDown(bool isJumpDown) { _isJumpDown = isJumpDown; }
	void setIsFaceDown(bool isFaceDown) { _isFaceDown = isFaceDown; }
	void setIsLedgeGrab(bool isLedgeGrab) { _isLedgeGrab = isLedgeGrab; }
	void setIsFired(bool isFired) { _isFired = isFired; }
	void setIsActive(bool isActive) { _isActive = isActive; }
	void setCurrentWeapon(bool currentWeapon) { _currentWeapon = currentWeapon; }
	void setWeaponSwitch(bool weaponSwitch) { _weaponSwitch = weaponSwitch; }

	player() {}
	~player() {}
};

