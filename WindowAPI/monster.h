#pragma once
#include "tileNode.h"

class monster
{
protected:
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
	bool _isAlive;
	bool _isLeft;
	int _count, _index;
	int _frameSpeed;
	int _attackCount;

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
	bool getIsAlive() { return _isAlive; }
	bool getIsLeft() { return _isLeft; }
	int getAttackCount() { return _attackCount; }
	MONSTERSTATE getState() { return _state; }
	MONSTERTYPE getType() { return _type; }
	image* getImage(MONSTERSTATE state) { return _image[state].img; }
	RECT getRect(MONSTERSTATE state) { return _image[state].rc; }

	void setX(float x) { _x = x; }
	void setY(float y) { _y = y; }
	void setOldX(float oldX) { _oldX = oldX; }
	void setOldY(float oldY) { _oldY = oldY; }
	void setPosition(float x, float y) { _x = x, _y = y; }
	void setDestPosition(float destX, float destY) { _destX = destX, _destY = destY; }
	void setAngle(float angle) { _angle = angle; }
	void setSpeed(float speed) { _speed = speed; }
	void setGravity(float gravity) { _gravity = gravity; }
	void setIndex(int index) { _index = index; }
	void setIsAlive(bool isAlive) { _isAlive = isAlive; }
	void setIsLeft(bool isLeft) { _isLeft = isLeft; }
	void setAttackCount(int attackCount) { _attackCount = attackCount; }
	void setState(MONSTERSTATE state) { _state = state; }
	void setType(MONSTERTYPE type) { _type = type; }

	void frameChange();
	void collisionProcess();

	virtual void init() = 0;
	virtual void update();
	virtual void render(HDC hdc);
	virtual void walk() = 0;
	virtual void fly() = 0;
};

class cricket : public monster
{
private:
	void init();
	void walk();
	void fly();

public:
};

class rolyPoly_large : public monster
{
private:
	void init();
	void walk();
	void fly();

public:
};

class rolyPoly_white : public monster
{
private:
	void init();
	void walk();
	void fly();

public:
};

class monsterFactory
{
public:
	monster * createMonster(MONSTERTYPE type);
};