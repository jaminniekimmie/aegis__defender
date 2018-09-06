#include "stdafx.h"
#include "stageOneScene.h"

HRESULT stageOneScene::init(void)
{
	_playerManager = new playerManager;
	_playerManager->init();
	EFFECTMANAGER->init();
	return S_OK;
}

void stageOneScene::release(void)
{
	_playerManager->release();
	SAFE_DELETE(_playerManager);
}

void stageOneScene::update(void)
{
	_playerManager->update();
	//EFFECTMANAGER->update();
}

void stageOneScene::render(void)
{
	_playerManager->render();
	//EFFECTMANAGER->render();
}
