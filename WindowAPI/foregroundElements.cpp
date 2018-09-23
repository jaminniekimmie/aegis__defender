#include "stdafx.h"
#include "foregroundElements.h"

void foregroundElements::render(int x, int y)
{
	_img->render(getMemDC(), x, y);
}

HRESULT sculptures_front::init()
{
	this->changeImage();

	_x = RND->getInt(CAMERAMANAGER->getMaxWidth());
	_y = CAMERAMANAGER->getMaxHeight() - _img->getHeight() * 1.5;
	_z = RND->getInt(4) + 1;

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
