#include "stdafx.h"
#include "tileTestScene.h"

HRESULT tileTestScene::init(void)
{
	_playerManager = new playerManager;
	_playerManager->init();

	_pixelTiles = new image;
	_pixelTiles->init(TILESIZEX, TILESIZEY);

	_playerManager->getPlayer(CLU)->setX(WINSIZEX / 2);
	_playerManager->getPlayer(CLU)->setY(WINSIZEY / 2);
	_playerManager->getPlayer(BART)->setX(WINSIZEX / 2);
	_playerManager->getPlayer(BART)->setY(WINSIZEY / 2);

	_rcCamera = RectMakeCenter(_playerManager->getPlayer()->getX(), _playerManager->getPlayer()->getY() - _playerManager->getPlayer()->getPlayerImage()->getFrameHeight() / 3, WINSIZEX, WINSIZEY);

	CAMERAMANAGER->setCamera(_rcCamera);
	CAMERAMANAGER->setRange(TILESIZEX, TILESIZEY);
	COLLISIONMANAGER->setPixelMap(_pixelTiles);
	
	this->mapLoad();

	_camDebug = _sceneSwitch = false;
	_alpha = 255;
	_switchCount = 0;
	_rand = RND->getFromIntTo(0, 1);
	_playerManager->setCharacter(_rand ? CLU : BART);

	_rcLetterBox[0] = RectMake(0, 0, WINSIZEX, 0);
	_rcLetterBox[1] = RectMake(0, WINSIZEY, WINSIZEX, 0);

	ShowCursor(true);

	_rand ? SOUNDMANAGER->play("BGM_ClusTheme", true) : SOUNDMANAGER->play("BGM_BartsTheme", true);

	return S_OK;
}

void tileTestScene::release(void)
{
	_playerManager->release();
	SAFE_DELETE(_playerManager);
	_pixelTiles->release();
	SAFE_DELETE(_pixelTiles);
	SOUNDMANAGER->stop("BGM_ClusTheme");
	SOUNDMANAGER->stop("BGM_BartsTheme");
}

void tileTestScene::update(void)
{
	_playerManager->update();

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
		{
			SCENEMANAGER->getCurrentScene()->release();
			SCENEMANAGER->loadScene("타이틀화면");
		}
	}

	if (KEYMANAGER->isOnceKeyDown('Q'))
		_sceneSwitch = true;
}


void tileTestScene::render(void)
{
	PatBlt(_pixelTiles->getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);

	IMAGEMANAGER->render("stage1_sky", getMemDC(), 0, 0, CAMERAMANAGER->getCamera().left, CAMERAMANAGER->getCamera().top, WINSIZEX, WINSIZEY);

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

	if (_alpha > 0)
		IMAGEMANAGER->alphaRender("solid_black", getMemDC(), _alpha);
}

void tileTestScene::cameraAdjustment()
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

void tileTestScene::mapLoad(void)
{
	HANDLE file;
	DWORD read;

	file = CreateFile("save.map", GENERIC_READ, 0, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);


	CloseHandle(file);
}
