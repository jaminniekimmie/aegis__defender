#include "stdafx.h"
#include "stageOneScene.h"

HRESULT stageOneScene::init(void)
{
	_playerManager = new playerManager;
	_playerManager->init();
	EFFECTMANAGER->init();

	_rcCamera = RectMakeCenter(_playerManager->getPlayer()->getX() + _playerManager->getPlayer()->getPlayerImage(_playerManager->getPlayer()->getState())->getFrameWidth() * 0.5,
		_playerManager->getPlayer()->getY() + _playerManager->getPlayer()->getPlayerImage(_playerManager->getPlayer()->getState())->getFrameHeight() * 0.5, WINSIZEX, WINSIZEY);
	CAMERAMANAGER->setCamera(_rcCamera);
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

	//_rcCamera = RectMake(_rcCamera.left, _rcCamera.top, WINSIZEX, WINSIZEY);
	CAMERAMANAGER->setCamera(_rcCamera);
}

void stageOneScene::render(void)
{
	_playerManager->render();
	//EFFECTMANAGER->render();
}
