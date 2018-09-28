#pragma once
#include "tileNode.h"

struct tagElement
{
	image* elementImg;
	RECT rc;
	float x, y;
	float fireX, fireY;
	float speed;
	float angle;
	float gravity;
	float radius;
	bool fire;
	bool isActive;
	bool isFrameImg;
	int alpha;
	int count;
	int index;
};

class objects
{
protected:
	OBJECTTYPE _type;
	OBJECTSTATE _state;
	RECT _rc;
	RECT _actionRc;
	tagImage _image[MAXOBJECTSTATE];
	vector<tagElement> _vElement;
	float _x, _y;
	float _destX, _destY;
	float _oldX, _oldY;
	float _speed;
	float _angle;
	float _gravity;
	float _range;
	bool _isActive;
	bool _isLeft;
	bool _isFrameImg;
	int _count, _index;
	int _frameSpeed;
	int _attackCount;
	int _randNo;

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
	int getIndex() { return _index; }
	int getAttackCount() { return _attackCount; }
	OBJECTSTATE getState() { return _state; }
	OBJECTTYPE getType() { return _type; }
	image* getImage() { return _image[_state].img; }
	vector<tagElement> getVElement() { return _vElement; }
	RECT getRect() { return _image[_state].rc; }
	RECT getActionRect() { return _actionRc; }

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

class spawner : public objects
{
private:
	void init();
	void idle();
	void move();

public:
};

class door_DNA_yellow_left : public objects
{
private:
	void init();
	void idle();
	void move();

public:
};

class door_DNA_yellow_right : public objects
{
private:
	void init();
	void idle();
	void move();

public:
};

class door_DNA_blue_left : public objects
{
private:
	void init();
	void idle();
	void move();

public:
};

class door_DNA_blue_right : public objects
{
private:
	void init();
	void idle();
	void move();

public:
};

class door_elevator : public objects
{
private:
	void init();
	void idle();
	void move();

public:
};

class bush_spikes : public objects
{
private:
	void init();
	void idle();
	void move();

public:
};

class vent : public objects
{
private:
	void init();
	void idle();
	void move();

public:
};

class switch_hor : public objects
{
private:
	void init();
	void idle();
	void move();

public:
};

class switch_vert : public objects
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