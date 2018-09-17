#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include "progressBar.h"	//체력바 클래스 사용하기 위해

//#include "enemyManager.h"
//적매니져 상호참조하기 위해 클래스 전방선언

class player : public gameNode
{
private:
	PLAYERCHARACTER _playerCharacter;
	PLAYERSTATE _playerState;
	DIRECTION _direction;
	RECT _rc;
	RECT _rcLedge[2];
	tagImage _player[MAXPLAYERSTATE];
	tagImage _weapon[MAXPLAYERSTATE];
	tagImage _weaponIcon[2];
	float _x, _y;
	float _oldX, _oldY;
	float _gravity;
	float _speed;
	float _angle;
	float _speedBoost;
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
	bool _weaponSwitch;

	progressBar* _hpBar;		//체력바
	float _maxHp, _currentHp;	//최대체력, 현재체력

public:
	HRESULT init(PLAYERCHARACTER playerCharacter);
	void release(void);
	void update(void);
	void render(void);

	//체력바 피통깍기
	void hitDamage(float damage);

	PLAYERSTATE getState() { return _playerState; }
	RECT getPlayerRc() { return _rc; }
	RECT getLedgeRc(int num) { return _rcLedge[num]; }
	DIRECTION getDirection() { return _direction; }
	image* getPlayerImage(PLAYERSTATE playerState) { return _player[playerState].img; }
	BYTE getWeaponIsActive(bool weaponSwitch) { return _weaponIcon[weaponSwitch].isActive; }
	int getFrameSpeed() { return _frameSpeed; }
	int getIndex() { return _index; }
	int getCount() { return _count; }
	float getX() { return _x; }
	float getY() { return _y; }
	float getOldX() { return _oldX; }
	float getOldY() { return _oldY; }
	float getGravity() { return _gravity; }
	float getSpeed() { return _speed; }
	float getSpeedBoost() { return _speedBoost; }
	float getAngle() { return _angle; }
	bool getIsLeft() { return _isLeft; }
	bool getIsJump() { return _isJump; }
	bool getIsFall() { return _isFall; }
	bool getOnLand() { return _onLand; }
	bool getIsBackstep() { return _isBackstep; }
	bool getIsJumpDown() { return _isJumpDown; }
	bool getIsFaceDown() { return _isFaceDown; }
	bool getIsLedgeGrab() { return _isLedgeGrab; }
	bool getIsFired() { return _isFired; }
	bool getWeaponSwitch() { return _weaponSwitch; }

	void setState(PLAYERSTATE playerState) { _playerState = playerState; }
	void setPlayerRc(RECT rc) { _rc = rc; }
	void setDirection(DIRECTION direction) { _direction = direction; }
	void setWeaponIsActive(bool weaponSwitch, bool isActive) { _weaponIcon[weaponSwitch].isActive = isActive; }
	void setFrameSpeed(int animationSpeed) { _frameSpeed = animationSpeed; }
	void setIndex(int index) { _index = index; }
	void setCount(int count) { _count = count; }
	void setX(float x) { _x = x; }
	void setY(float y) { _y = y; }
	void setOldX(float oldX) { _x = oldX; }
	void setOldY(float oldY) { _y = oldY; }
	void setGravity(float gravity) { _gravity = gravity; }
	void setSpeed(float speed) { _speed = speed; }
	void setSpeedBoost(float speedBoost) { _speedBoost = speedBoost; }
	void setAngle(float angle) { _angle = angle; }
	void setIsLeft(bool isLeft) { _isLeft = isLeft; }
	void setIsJump(bool isJump) { _isJump = isJump; }
	void setIsFall(bool isFall) { _isFall = isFall; }
	void setOnLand(bool onLand) { _onLand = onLand; }
	void setIsBackstep(bool isBackstep) { _isBackstep = isBackstep; }
	void setIsJumpDown(bool isJumpDown) { _isJumpDown = isJumpDown; }
	void setIsFaceDown(bool isFaceDown) { _isFaceDown = isFaceDown; }
	void setIsLedgeGrab(bool isLedgeGrab) { _isLedgeGrab = isLedgeGrab; }
	void setIsFired(bool isFired) { _isFired = isFired; }
	void setWeaponSwitch(bool weaponSwitch) { _weaponSwitch = weaponSwitch; }

	void frameChangeLoop();
	void frameChangeOnce();
	void weaponSwitch(bool weaponSwitch);

	player() {}
	~player() {}
};

