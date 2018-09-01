#include "stdafx.h"
#include "camel.h"


HRESULT camel::init(void)
{
	//낙타 이미지
	_camel = IMAGEMANAGER->addImage("camel", "camel.bmp", 300, 267, true, RGB(255, 0, 255));

	//애니메이션1 (처음부터 끝까지)
	_ani1 = new animation;
	_ani1->init(_camel->getWidth(), _camel->getHeight(), 4, 3);
	_ani1->setPlayFrame(false, true);
	_ani1->setFPS(1);

	//애니메이션2 (배열에 담아서)
	int arrAni[] = {0, 3, 6, 9};
	_ani2 = new animation;
	_ani2->init(_camel->getWidth(), _camel->getHeight(), 4, 3);
	_ani2->setPlayFrame(arrAni, 4, true);
	_ani2->setFPS(1);

	//애니메이션3 (구간 정해서)
	_ani3 = new animation;
	_ani3->init(_camel->getWidth(), _camel->getHeight(), 4, 3);
	_ani3->setPlayFrame(3, 10, false);
	_ani3->setFPS(1);

	return S_OK;
}

void camel::release(void)
{
	SAFE_DELETE(_ani1);
	SAFE_DELETE(_ani2);
	SAFE_DELETE(_ani3);
}

void camel::update(void)
{
	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		_ani1->start();
	}
	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		_ani2->start();
	}
	if (KEYMANAGER->isOnceKeyDown('3'))
	{
		_ani3->start();
	}

	_ani1->frameUpdate(0.1f);
	_ani2->frameUpdate(0.5f);
	_ani3->frameUpdate(1.0f);
}

void camel::render(void)
{
	_camel->aniRender(getMemDC(), WINSIZEX / 2 - 200, WINSIZEY / 2, _ani1);
	_camel->aniRender(getMemDC(), WINSIZEX / 2 , WINSIZEY / 2, _ani2);
	_camel->aniRender(getMemDC(), WINSIZEX / 2 + 200, WINSIZEY / 2, _ani3);
}
