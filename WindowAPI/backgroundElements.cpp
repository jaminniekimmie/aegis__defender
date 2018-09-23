#include "stdafx.h"
#include "backgroundElements.h"

void backgroundElements::render(int x, int y)
{
	_img->render(getMemDC(), x, y);
}

HRESULT cloud::init()
{
	_x = RND->getInt(CAMERAMANAGER->getMaxWidth() * 2) - CAMERAMANAGER->getMaxWidth();
	_y = RND->getInt(CAMERAMANAGER->getMaxHeight()) - CAMERAMANAGER->getMaxHeight();
	_z = RND->getFromIntTo(0, 10) + 0;
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
	_z = RND->getInt(10) + 0;

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