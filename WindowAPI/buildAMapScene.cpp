#include "stdafx.h"
#include "buildAMapScene.h"

HRESULT buildAMapScene::init(void)
{
	_tileMap = new tileMap;
	_tileMap->init();

	EFFECTMANAGER->init();

	_playerManager = new playerManager;
	_playerManager->init();

	return S_OK;
}

void buildAMapScene::release(void)
{
	_tileMap->release();
	_playerManager->release();
	SAFE_DELETE(_tileMap);
	SAFE_DELETE(_playerManager);
}

void buildAMapScene::update(void)
{
	_tileMap->update();
	_playerManager->update();

	//EFFECTMANAGER->update();
}

void buildAMapScene::render(void)
{
	_tileMap->render();
	_playerManager->render();

	//EFFECTMANAGER->render();
}