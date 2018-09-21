#pragma once
#include "gameNode.h"

class backgroundElements : public gameNode
{
protected:
	image * _img;
	RECT _rc;
	float _x, _y, _z;
	float _speed;

public:
	virtual HRESULT init(void) { return S_OK; }
	virtual void release(void) {}
	virtual void update(void) {}
	virtual void render(void) {}
	virtual void render(int x, int y);

	void setImage(image *img) { _img = img; }
	void setX(float x) { _x = x; }
	void setY(float y) { _y = y; }
	void setZ(float z) { _z = z; }
	void setSpeed(float speed) { _speed = speed; }

	image* getImage() { return _img; }
	RECT getRect() { return RectMake(_x, _y, _img->getWidth(), _img->getWidth()); }
	float getX() { return _x; }
	float getY() { return _y; }
	float getZ() { return _z; }
	float getSpeed() { return _speed; }

	backgroundElements() {}
	~backgroundElements() {}
};

class cloud : public backgroundElements
{
public:
	HRESULT init();
	void release();
	void update();

	void changeImage();

	cloud() {}
	~cloud() {}
};

class sculptures_back : public backgroundElements
{
public:
	HRESULT init();
	void release();
	void update();

	void changeImage();

	sculptures_back() {}
	~sculptures_back() {}
};