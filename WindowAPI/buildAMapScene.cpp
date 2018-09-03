#include "stdafx.h"
#include "buildAMapScene.h"

HRESULT buildAMapScene::init(void)
{
	_tileMap = new tileMap;
	_tileMap->init();

	return S_OK;
}

void buildAMapScene::release(void)
{
	_tileMap->release();
	SAFE_DELETE(_tileMap);
}

void buildAMapScene::update(void)
{
	_tileMap->update();
}

void buildAMapScene::render(void)
{
	_tileMap->render();
}