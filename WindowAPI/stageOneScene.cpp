#include "stdafx.h"
#include "stageOneScene.h"

HRESULT stageOneScene::init(void)
{
	_playerManager = new playerManager;
	_playerManager->init();

	_GUI = new GUI;
	_GUI->init();

	_pixelTiles = new image;
	_pixelTiles->init(TILESIZEX, TILESIZEY);

	_pixelMap = new image;
	_pixelMap->init("tex/map/map_pixel_01.bmp", 7409, 1760, true, RGB(255, 0, 255));

	_playerManager->getPlayer(CLU)->setX(755);
	_playerManager->getPlayer(CLU)->setY(1300);
	_playerManager->getPlayer(BART)->setX(_playerManager->getPlayer(CLU)->getX() - _playerManager->getPlayer(CLU)->getPlayerImage()->getFrameWidth() * 0.5f);
	_playerManager->getPlayer(BART)->setY(1300);

	_rcCamera = RectMakeCenter(_playerManager->getPlayer()->getX(), _playerManager->getPlayer()->getY() - _playerManager->getPlayer()->getPlayerImage()->getFrameHeight() / 3, WINSIZEX, WINSIZEY);

	CAMERAMANAGER->setCamera(_rcCamera);
	CAMERAMANAGER->setRange(7409, 1760);
	COLLISIONMANAGER->setPixelMap(_pixelMap);
	MONSTERMANAGER->init(1);
	MONSTERMANAGER->setPlayerManager(_playerManager);
	OBJECTMANAGER->init(1);
	OBJECTMANAGER->setPlayerManager(_playerManager);
	_GUI->setPlayerManager(_playerManager);
	
	cloud* _cloud;
	for (int i = 0; i < 40; ++i)
	{
		_cloud = new cloud;
		_cloud->init();
		RENDERMANAGER->addBackground(_cloud->getZ(), _cloud);
	}

	sculptures_back* _sculptures_back;
	for (int i = 0; i < 6; ++i)
	{
		_sculptures_back = new sculptures_back;
		_sculptures_back->init();
		RENDERMANAGER->addBackground(_sculptures_back->getZ(), _sculptures_back);
	}

	sculptures_front* _sculptures_front;
	for (int i = 0; i < 5; ++i)
	{
		_sculptures_front = new sculptures_front;
		_sculptures_front->init();
		RENDERMANAGER->addForeground(_sculptures_front->getZ(), _sculptures_front);
	}

	//this->mapLoad();

	_camDebug = _sceneSwitch = false;
	_alpha = 255;

	ShowCursor(true);

	SOUNDMANAGER->play("BGM_nereisdesert");

	return S_OK;
}

void stageOneScene::release(void)
{
	_playerManager->release();
	SAFE_DELETE(_playerManager);
	_GUI->release();
	SAFE_DELETE(_GUI);
	_pixelTiles->release();
	SAFE_DELETE(_pixelTiles);
	_pixelMap->release();
	SAFE_DELETE(_pixelMap);
	RENDERMANAGER->clearBackground();
	RENDERMANAGER->clearForeground();
}

void stageOneScene::update(void)
{
	PLAYERCHARACTER character = _playerManager->getCharacter();

	_playerManager->update();

	if (character != _playerManager->getCharacter())
	{
		float startX = _playerManager->getPlayer(character)->getX();
		float startY = _playerManager->getPlayer(character)->getY() - _playerManager->getPlayer(character)->getPlayerImage()->getFrameHeight() * 0.33f;
		float destX = _playerManager->getPlayer(_playerManager->getCharacter())->getX();
		float destY = _playerManager->getPlayer(_playerManager->getCharacter())->getY() - _playerManager->getPlayer(_playerManager->getCharacter())->getPlayerImage()->getFrameHeight() * 0.33f;
		CAMERAMANAGER->CameraSwitch(startX, startY, destX, destY, true);
	}
	else
	{
		if (!_camDebug)
		{
			if (_playerManager->getPlayer()->getState() == LAND)
			{
				_rcCamera.top++;
			}
			else
			{
				_rcCamera = RectMakeCenter(_playerManager->getPlayer()->getX(), _playerManager->getPlayer()->getY() - _playerManager->getPlayer()->getPlayerImage()->getFrameHeight() / 3, WINSIZEX, WINSIZEY);
			}
		}
	}


	MONSTERMANAGER->update();
	OBJECTMANAGER->update();
	_GUI->update();


	//temporary
	if (KEYMANAGER->isOnceKeyDown('Q'))
		_sceneSwitch = true;

	this->cameraAdjustment();
	
	if (!_sceneSwitch)
	{
		if (_alpha > 0)
			_alpha -= 5;
	}
	else
	{
		_alpha += 5;
		if (_alpha >= 255)
			SCENEMANAGER->loadScene("∏ ≈¯");
	}
}

void stageOneScene::render(void)
{
	//PatBlt(_pixelTiles->getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);

	//∞‘¿”≈∏¿œ ∑∫∆Æ ∑ª¥ı
	//for (int i = 0; i < TILEX * TILEY; i++)
	//{
	//	if (!CAMERAMANAGER->CameraIn(_tiles[i].rc)) continue;
	//	
	//	IMAGEMANAGER->frameRender(_tiles[i].tileLabel, getMemDC(), _tiles[i].rc.left - CAMERAMANAGER->getCamera().left, _tiles[i].rc.top - CAMERAMANAGER->getCamera().top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
	//	IMAGEMANAGER->frameRender("pixel_map", _pixelTiles->getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
	//
	//	if (_tiles[i].obj == OBJECT_NONE) continue;
	//	IMAGEMANAGER->frameRender(_tiles[i].tileLabel, getMemDC(), _tiles[i].rc.left - CAMERAMANAGER->getCamera().left, _tiles[i].rc.top - CAMERAMANAGER->getCamera().top, _tiles[i].objFrameX, _tiles[i].objFrameY);
	//	//IMAGEMANAGER->frameRender(_tiles[0].tileLabel, getMemDC(), 100, 100, _tiles[0].objFrameX, _tiles[0].objFrameY);
	//	IMAGEMANAGER->frameRender("pixel_map", _pixelTiles->getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].objFrameX, _tiles[i].objFrameY);
	//	
	//}
	//if (KEYMANAGER->isToggleKey('P'))
	//{
	//	_pixelTiles->render(getMemDC(), -CAMERAMANAGER->getCamera().left, -CAMERAMANAGER->getCamera().top);
	//}

	IMAGEMANAGER->render("stage1_sky", getMemDC(), 0, 0, CAMERAMANAGER->getCamera().left, CAMERAMANAGER->getCamera().top, WINSIZEX, WINSIZEY);

	RENDERMANAGER->backgroundRender(getMemDC());

	IMAGEMANAGER->render("stage1_topology", getMemDC(), 0, 0, CAMERAMANAGER->getCamera().left, CAMERAMANAGER->getCamera().top, WINSIZEX, WINSIZEY);
	
	if (KEYMANAGER->isToggleKey('P'))
		_pixelMap->render(getMemDC(), 0, 0, CAMERAMANAGER->getCamera().left, CAMERAMANAGER->getCamera().top, WINSIZEX, WINSIZEY);

	MONSTERMANAGER->render(getMemDC());
	OBJECTMANAGER->render(getMemDC());
	_playerManager->render();

	RENDERMANAGER->foregroundRender(getMemDC());

	CAMERAMANAGER->render(getMemDC());
	if (CAMERAMANAGER->getSwitchStart())
		_playerManager->getPlayer()->render();
	
	_GUI->render();

	if (_alpha > 0)
		IMAGEMANAGER->alphaRender("solid_black", getMemDC(), _alpha);
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

	if (_playerManager->getPlayer()->getRect().left <= 0)
	{
		_playerManager->getPlayer()->setX(_playerManager->getPlayer()->getPlayerImage()->getFrameWidth() / 6);
	}
	else if (_playerManager->getPlayer()->getRect().right >= CAMERAMANAGER->getMaxWidth())
	{
		_playerManager->getPlayer()->setX(CAMERAMANAGER->getMaxWidth() - _playerManager->getPlayer()->getPlayerImage()->getFrameWidth() / 6);
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
