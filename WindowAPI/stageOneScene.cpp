#include "stdafx.h"
#include "stageOneScene.h"

HRESULT stageOneScene::init(void)
{
	_playerManager = new playerManager;
	_playerManager->init();

	EFFECTMANAGER->init();

	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			_mapTiles[i * TILEX + j].rc = RectMake(j * TILESIZE, i * TILESIZE, TILESIZE, TILESIZE);
		}
	}
	
	//this->mapLoad();

	_rcCamera = RectMakeCenter(_playerManager->getPlayer()->getPlayerRc().left + (_playerManager->getPlayer()->getPlayerRc().right - _playerManager->getPlayer()->getPlayerRc().left) * 0.5,
		_playerManager->getPlayer()->getPlayerRc().top, WINSIZEX, WINSIZEY);

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

	this->cameraAdjustment();
}

void stageOneScene::render(void)
{
	//PatBlt(_pixelTiles->getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);

	////게임타일 렉트 렌더
	//for (int i = 0; i < TILEX * TILEY; i++)
	//{
	//	//if (CAMERAMANAGER->CameraIn(_mapTiles[i].rc))
	//	{
	//		IMAGEMANAGER->frameRender(_mapTiles[i].tileLabel, getMemDC(), _mapTiles[i].rc.left - CAMERAMANAGER->getCamera().left, _mapTiles//[i].rc.top - CAMERAMANAGER->getCamera().top, _mapTiles[i].terrainFrameX, _mapTiles[i].terrainFrameY);
	//		//IMAGEMANAGER->frameRender("pixel_map", _pixelTiles->getMemDC(), _mapTiles[i].rc.left - CAMERAMANAGER->getCamera().left, /_mapTiles/[i].rc.top - CAMERAMANAGER->getCamera().top, _mapTiles[i].terrainFrameX, _mapTiles[i].terrainFrameY);
	//
	//		if (_mapTiles[i].obj == OBJECT_NONE) continue;
	//		IMAGEMANAGER->frameRender(_mapTiles[i].tileLabel, getMemDC(), _mapTiles[i].rc.left - CAMERAMANAGER->getCamera().left, _mapTiles//[i].rc.top - CAMERAMANAGER->getCamera().top, _mapTiles[i].objFrameX, _mapTiles[i].objFrameY);
	//		IMAGEMANAGER->frameRender("pixel_map", _pixelTiles->getMemDC(), _mapTiles[i].rc.left - CAMERAMANAGER->getCamera().left, _mapTiles//[i].rc.top - CAMERAMANAGER->getCamera().top, _mapTiles[i].objFrameX, _mapTiles[i].objFrameY);
	//	}
	//}
	//
	//if (KEYMANAGER->isToggleKey('P'))
	//{
	//	_pixelTiles->alphaRender(getMemDC(), 0, 0, 100);
	//}

	_playerManager->render();

	//IMAGEMANAGER->render("cursonIcon_idle", getMemDC(), _ptMouse.x, _ptMouse.y);
}

void stageOneScene::cameraAdjustment()
{
	_rcCamera = RectMakeCenter(_playerManager->getPlayer()->getPlayerRc().left + (_playerManager->getPlayer()->getPlayerRc().right - _playerManager->getPlayer()->getPlayerRc().left) * 0.5,
		_playerManager->getPlayer()->getPlayerRc().top, WINSIZEX, WINSIZEY);

	if (_rcCamera.left <= 0)
	{
		_rcCamera.left = 0;
		_rcCamera.right = _rcCamera.left + WINSIZEX;
	}
	else if (_rcCamera.right >= TILESIZEX)
	{
		_rcCamera.left = TILESIZEX - WINSIZEX;
		_rcCamera.right = _rcCamera.left + WINSIZEX;
	}
	if (_rcCamera.top <= 0)
	{
		_rcCamera.top = 0;
		_rcCamera.bottom = _rcCamera.top + WINSIZEY;
	}
	else if (_rcCamera.bottom >= TILESIZEY)
	{
		_rcCamera.top = TILESIZEY - WINSIZEY;
		_rcCamera.bottom = _rcCamera.top + WINSIZEY;
	}

	_rcCamera = RectMake(_rcCamera.left, _rcCamera.top, WINSIZEX, WINSIZEY);
	CAMERAMANAGER->setCamera(_rcCamera);
}

void stageOneScene::mapLoad(void)
{
	HANDLE file;
	DWORD read;

	file = CreateFile("save.map", GENERIC_READ, 0, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, _mapTiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);

	CloseHandle(file);
}
