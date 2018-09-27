#pragma once
#include "tileNode.h"
#include "hpBar.h"

class monster
{
protected:
	hpBar * _hpBar;
	MONSTERTYPE _type;
	MONSTERSTATE _state;
	RECT _rc;
	tagImage _image[MAXMONSTERSTATE];
	float _x, _y;
	float _destX, _destY;
	float _oldX, _oldY;
	float _speed;
	float _angle;
	float _gravity;
	float _range;
	bool _isAlive;
	bool _isLeft;
	bool _isHit;
	int _count, _index;
	int _frameSpeed;
	int _hpCount;
	int _maxHp;

public:
	float getX() { return _x; }
	float getY() { return _y; }
	float getOldX() { return _oldX; }
	float getOldY() { return _oldY; }
	float getDestX() { return _destX; }
	float getDestY() { return _destY; }
	float getGravity() { return _gravity; }
	float getSpeed() { return _speed; }
	float getAngle() { return _angle; }
	float getRange() { return _range; }
	bool getIsAlive() { return _isAlive; }
	bool getIsLeft() { return _isLeft; }
	bool getIsHit() { return _isHit; }
	MONSTERSTATE getState() { return _state; }
	MONSTERTYPE getType() { return _type; }
	hpBar* getHpBar() { return _hpBar; }
	image* getImage(MONSTERSTATE state) { return _image[state].img; }
	RECT getRect() { return _image[_state].rc; }

	void setX(float x) { _x = x; }
	void setY(float y) { _y = y; }
	void setOldX(float oldX) { _oldX = oldX; }
	void setOldY(float oldY) { _oldY = oldY; }
	void setPosition(float x, float y) { _x = x, _y = y; }
	void setOldPosition(float oldX, float oldY) { _oldX = oldX, _oldY = oldY; }
	void setAngle(float angle) { _angle = angle; }
	void setRange(float range) { _range = range; }
	void setSpeed(float speed) { _speed = speed; }
	void setGravity(float gravity) { _gravity = gravity; }
	void setIndex(int index) { _index = index; }
	void setIsAlive(bool isAlive) { _isAlive = isAlive; }
	void setIsLeft(bool isLeft) { _isLeft = isLeft; }
	void setIsHit(bool isHit) { _isHit = isHit; }
	void setState(MONSTERSTATE state) { _state = state; }
	void setType(MONSTERTYPE type) { _type = type; }

	void frameChange();
	void directionProcess();
	void collisionProcess();

	virtual void init() = 0;
	virtual void release() = 0;
	virtual void update();
	virtual void render(HDC hdc);
	virtual void idle() = 0;
	virtual void move() = 0;
	virtual void dead() = 0;
};

class sandworm : public monster
{
private:
	void init();
	void release();
	void idle();
	void move();
	void dead();

public:
};

class spiderBaby : public monster
{
private:
	void init();
	void release();
	void idle();
	void move();
	void dead();

public:
};

class firedrinkerFly : public monster
{
private:
	void init();
	void release();
	void idle();
	void move();
	void dead();

public:
};

class eagle : public monster
{
private:
	void init();
	void release();
	void idle();
	void move();
	void dead();

public:
};

class monsterFactory
{
public:
	monster * createMonster(MONSTERTYPE type);
};