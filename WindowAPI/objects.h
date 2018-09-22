#pragma once
#include "tileNode.h"

class objects
{
protected:
	OBJECTTYPE _type;
	OBJECTSTATE _state;
	RECT _rc;
	tagImage _image[MAXMONSTERSTATE];
	float _x, _y;
	float _destX, _destY;
	float _oldX, _oldY;
	float _speed;
	float _angle;
	float _gravity;
	float _range;
	bool _isActive;
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
	bool getIsActive() { return _isActive; }
	bool getIsLeft() { return _isLeft; }
	int getAttackCount() { return _attackCount; }
	OBJECTSTATE getState() { return _state; }
	OBJECTTYPE getType() { return _type; }
	image* getImage(OBJECTSTATE state) { return _image[state].img; }
	RECT getRect() { return _image[_state].rc; }

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
	void setIsAlive(bool isActive) { _isActive = isActive; }
	void setIsLeft(bool isLeft) { _isLeft = isLeft; }
	void setAttackCount(int attackCount) { _attackCount = attackCount; }
	void setState(OBJECTSTATE state) { _state = state; }
	void setType(OBJECTTYPE type) { _type = type; }

	void frameChange();
	void collisionProcess();

	virtual void init() = 0;
	virtual void update();
	virtual void render(HDC hdc);
	virtual void idle() = 0;
	virtual void move() = 0;
};

class chip_green : public objects
{
private:
	void init();
	void idle();
	void move();

public:
};

class chip_blue : public objects
{
private:
	void init();
	void idle();
	void move();

public:
};

class chip_purple : public objects
{
private:
	void init();
	void idle();
	void move();

public:
};

class chip_white : public objects
{
private:
	void init();
	void idle();
	void move();

public:
};

class heart_red : public objects
{
private:
	void init();
	void idle();
	void move();

public:
};

class heart_yellow : public objects
{
private:
	void init();
	void idle();
	void move();

public:
};

class bloomFlower : public objects
{
private:
	void init();
	void idle();
	void move();

public:
};

class mineral : public objects
{
private:
	void init();
	void idle();
	void move();

public:
};

class blueFlower : public objects
{
private:
	void init();
	void idle();
	void move();

public:
};

class door_DNA : public objects
{
private:
	void init();
	void idle();
	void move();

public:
};

class objectFactory
{
public:
	objects * createObject(OBJECTTYPE type);
};