#include "stdafx.h"
#include "foregroundElements.h"

void foregroundElements::render(int x, int y)
{
	_img->render(getMemDC(), x, y);
}

HRESULT sculptures_front::init()
{
	this->changeImage();

	_x = RND->getInt(CAMERAMANAGER->getMaxWidth()) - CAMERAMANAGER->getMaxWidth() * 0.33f;
	_y = CAMERAMANAGER->getMaxHeight() - _img->getHeight() * 1.25;
	_z = RND->getFromFloatTo(6.5, 6.9) + 1;

	return S_OK;
}

void sculptures_front::release()
{
}

void sculptures_front::update()
{
}

void sculptures_front::changeImage()
{
	int c = RND->getFromIntTo(0, 6);
	_img = IMAGEMANAGER->findImage("sculpture_front_0" + to_string(c + 1));
}

HRESULT autotile_darkbrown::init()
{
	this->changeImage();

	_x = RND->getInt(CAMERAMANAGER->getMaxWidth()) - CAMERAMANAGER->getMaxWidth() * 0.33f;
	_y = CAMERAMANAGER->getMaxHeight() - _img->getHeight() * 0.6;
	_z = RND->getFromFloatTo(7, 7.4) + 1; 


	return S_OK;
}

void autotile_darkbrown::release()
{
}

void autotile_darkbrown::update()
{
}

void autotile_darkbrown::changeImage()
{
	int c = RND->getFromIntTo(1, 5);
	_img = IMAGEMANAGER->findImage("autotile_darkbrown" + to_string(c));
}

HRESULT autotile_orange::init()
{
	this->changeImage();

	_x = RND->getInt(CAMERAMANAGER->getMaxWidth()) - CAMERAMANAGER->getMaxWidth() * 0.33f;
	_y = CAMERAMANAGER->getMaxHeight() - _img->getHeight() * 0.85;
	_z = RND->getFromFloatTo(7.5, 7.9) + 1;
	//ÇÃ·¹ÀÌ¾î°¡ 10ÂëÀÎ°¡?
	//¸ÊÀÌ 9

	return S_OK;
}

void autotile_orange::release()
{
}

void autotile_orange::update()
{
}

void autotile_orange::changeImage()
{
	int c = RND->getFromIntTo(1, 8);
	_img = IMAGEMANAGER->findImage("autotile_orange" + to_string(c));
}