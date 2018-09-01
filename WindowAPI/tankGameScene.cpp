#include "stdafx.h"
#include "tankGameScene.h"

HRESULT tankGameScene::init(void)
{
	_tileMap = new tileMap;
	_tileMap->init();

	return S_OK;
}

void tankGameScene::release(void)
{
	_tileMap->release();
	SAFE_DELETE(_tileMap);
}

void tankGameScene::update(void)
{
	_tileMap->update();
}

void tankGameScene::render(void)
{
	_tileMap->render();
}