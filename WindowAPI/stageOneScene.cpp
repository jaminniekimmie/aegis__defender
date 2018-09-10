#include "stdafx.h"
#include "stageOneScene.h"

HRESULT stageOneScene::init(void)
{
	_playerManager = new playerManager;
	_playerManager->init();

	EFFECTMANAGER->init();

	_pixelTiles = new image;
	_pixelTiles->init(TILESIZEX, TILESIZEY);

	this->mapLoad();

	_rcCamera = RectMakeCenter(_playerManager->getPlayer()->getX(),	_playerManager->getPlayer()->getY() - _playerManager->getPlayer()->getPlayerImage(_playerManager->getPlayer()->getState())->getFrameHeight() / 3, WINSIZEX, WINSIZEY);
	
	_camDebug = false;

	COLLISIONMANAGER->setPixelMap(_pixelTiles);

	CAMERAMANAGER->setCamera(_rcCamera);

	return S_OK;
}

void stageOneScene::release(void)
{
	_playerManager->release();
	SAFE_DELETE(_playerManager);
	_pixelTiles->release();
	SAFE_DELETE(_pixelTiles);
}

void stageOneScene::update(void)
{
	_playerManager->update();

	this->cameraAdjustment();
}

void stageOneScene::render(void)
{
	PatBlt(_pixelTiles->getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);

	//게임타일 렉트 렌더
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (!CAMERAMANAGER->CameraIn(_tiles[i].rc)) continue;
		
		IMAGEMANAGER->frameRender(_tiles[i].tileLabel, getMemDC(), _tiles[i].rc.left - CAMERAMANAGER->getCamera().left, _tiles[i].rc.top - CAMERAMANAGER->getCamera().top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
		IMAGEMANAGER->frameRender("pixel_map", _pixelTiles->getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
	
		if (_tiles[i].obj == OBJECT_NONE) continue;
		IMAGEMANAGER->frameRender(_tiles[i].tileLabel, getMemDC(), _tiles[i].rc.left - CAMERAMANAGER->getCamera().left, _tiles[i].rc.top - CAMERAMANAGER->getCamera().top, _tiles[i].objFrameX, _tiles[i].objFrameY);
		//IMAGEMANAGER->frameRender(_tiles[0].tileLabel, getMemDC(), 100, 100, _tiles[0].objFrameX, _tiles[0].objFrameY);
		IMAGEMANAGER->frameRender("pixel_map", _pixelTiles->getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].objFrameX, _tiles[i].objFrameY);
		
	}
	if (KEYMANAGER->isToggleKey('P'))
	{
		_pixelTiles->render(getMemDC(), -CAMERAMANAGER->getCamera().left, -CAMERAMANAGER->getCamera().top);
	}

	_playerManager->render();

	//IMAGEMANAGER->render("cursonIcon_idle", getMemDC(), _ptMouse.x, _ptMouse.y);
}

void stageOneScene::cameraAdjustment()
{
	if (KEYMANAGER->isOnceKeyDown('C'))
		_camDebug = !_camDebug;

	if (_camDebug)
	{
		if (KEYMANAGER->isStayKeyDown('A'))
		{
			_rcCamera.left -= 30;
			_rcCamera.right -= 30;
		}

		if (KEYMANAGER->isStayKeyDown('D'))
		{
			_rcCamera.left += 30;
			_rcCamera.right += 30;
		}
		if (KEYMANAGER->isStayKeyDown('W'))
		{
			_rcCamera.top -= 30;
			_rcCamera.bottom -= 30;
		}
		if (KEYMANAGER->isStayKeyDown('S'))
		{
			_rcCamera.top += 30;
			_rcCamera.bottom += 30;
		}
	}
	else
		_rcCamera = RectMakeCenter(_playerManager->getPlayer()->getX(), _playerManager->getPlayer()->getY() - _playerManager->getPlayer()->getPlayerImage(_playerManager->getPlayer()->getState())->getFrameHeight() / 3, WINSIZEX, WINSIZEY);


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
	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);


	CloseHandle(file);
}
