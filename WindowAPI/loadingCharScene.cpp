#include "stdafx.h"
#include "loadingCharScene.h"

HRESULT loadingCharScene::init(void)
{
	_player[CLU].img = IMAGEMANAGER->findImage("Clu_run");
	_player[BART].img = IMAGEMANAGER->findImage("Bart_run");
	
	_rand = RND->getFromIntTo(0, 1);
	
	_player[_rand].x = - _player[_rand].img->getFrameWidth() * 0.5f;
	_player[!_rand].x = _player[_rand].x - _player[_rand].img->getFrameWidth() * 0.75;
	_player[_rand].y = 400;
	_player[!_rand].y = 400;

	_background = IMAGEMANAGER->findImage("solid_black");

	_loadingCount = _index = _count = _alpha = 0;

	return S_OK;
}

void loadingCharScene::release(void)
{
}

void loadingCharScene::update(void)
{
	int rand = RND->getInt(20);
	
	if (rand)
	{
		_loadingCount++;
		if (_loadingCount > 100)
			_loadingCount = 100;
	}

	_player[CLU].x += 5.0f;
	_player[BART].x += 5.0f;

	if (_player[!_rand].x >= WINSIZEX && _loadingCount == 100)
		_alpha += 5;

	if (_alpha >= 255)
		SCENEMANAGER->loadScene("스테이지원");

	this->frameChange();
}

void loadingCharScene::render(void)
{
	_background->render(getMemDC());

	for (int i = 0; i < 2; i++)
	{
		_player[i].img->frameRender(getMemDC(), _player[i].x, _player[i].y, _index, 0);
	}
	
	char str[128];
	HFONT myFont = CreateFont(63, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Flood Std");
	HFONT oldFont = (HFONT)SelectObject(getMemDC(), myFont);
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	SetBkMode(getMemDC(), TRANSPARENT);

	sprintf_s(str, "LOADING %d", _loadingCount);
	TextOut(getMemDC(), 903, 635, str, strlen(str));

	SelectObject(getMemDC(), oldFont);
	DeleteObject(myFont);

	if (_alpha > 0)
		IMAGEMANAGER->alphaRender("solid_black", getMemDC(), _alpha);
}

void loadingCharScene::frameChange()
{
	_count++;
	if (_count % 10 == 0)
	{
		_index++;
		if (_index > _player[0].img->getMaxFrameX())
			_index = 0;
	}
}
