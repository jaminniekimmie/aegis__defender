#include "stdafx.h"
#include "backgroundElements.h"

void backgroundElements::render(int x, int y)
{
	_img->render(getMemDC(), x, y);
}

HRESULT cloud::init()
{
	_x = RND->getInt(CAMERAMANAGER->getMaxWidth() * 1.5) - CAMERAMANAGER->getMaxWidth() * 0.5;
	_y = RND->getInt(CAMERAMANAGER->getMaxHeight()) - CAMERAMANAGER->getMaxHeight();
	_z = RND->getFromFloatTo(0, 8) + 0;
	_speed = 0.5f;

	this->changeImage();

	return S_OK;
}

void cloud::release()
{
}

void cloud::update()
{
	_x += _speed;
	if (_x > CAMERAMANAGER->getMaxWidth())
	{
		this->changeImage();
		_x = - _img->getWidth() - RND->getInt(CAMERAMANAGER->getMaxWidth());
	}
}

void cloud::changeImage()
{
	int c = RND->getFromIntTo(0, 8);
	_img = IMAGEMANAGER->findImage("Cloud" + to_string(c + 1));
}

HRESULT sculptures_back::init()
{
	this->changeImage();

	_x = RND->getInt(CAMERAMANAGER->getMaxWidth());
	_y = CAMERAMANAGER->getMaxHeight() - _img->getHeight() * 2;
	_z = RND->getFromFloatTo(7.5, 7.9) + 1;

	return S_OK;
}

void sculptures_back::release()
{
}

void sculptures_back::update()
{
}

void sculptures_back::changeImage()
{
	int c = RND->getFromIntTo(0, 5);
	_img = IMAGEMANAGER->findImage("sculpture_back_0" + to_string(c + 1));
}

HRESULT autotile_lightorange::init()
{
	this->changeImage();

	_x = RND->getInt(CAMERAMANAGER->getMaxWidth() * 1.5) - CAMERAMANAGER->getMaxWidth();
	_y = CAMERAMANAGER->getMaxHeight() - _img->getHeight() * 1.75;
	_z = RND->getFromFloatTo(7, 7.4) + 1;
	_speed = 0.5f;

	return S_OK;
}

void autotile_lightorange::release()
{
}

void autotile_lightorange::update()
{
}

void autotile_lightorange::changeImage()
{
	int c = RND->getFromFloatTo(1, 8);
	_img = IMAGEMANAGER->findImage("autotile_lightorange" + to_string(c));
}

HRESULT autotile_back::init()
{
	_x = RND->getFromIntTo(CAMERAMANAGER->getMaxWidth() * 0.25, CAMERAMANAGER->getMaxWidth() * 1.5);
	_y = - RND->getInt(CAMERAMANAGER->getMaxHeight());
	_z = RND->getFromIntTo(7, 9);
	_speed = 0.5f;

	this->changeImage();

	return S_OK;
}

void autotile_back::release()
{
}

void autotile_back::update()
{
}

void autotile_back::changeImage()
{
	int c = RND->getFromIntTo(1, 6);
	_img = IMAGEMANAGER->findImage("autotile_back" + to_string(c));
}
