#include "stdafx.h"
#include "tileMap.h"

HRESULT tileMap::init(void)
{
	string str;
	//타일맵 이미지 초기화
	for (int i = 0; i < 10; i++)
	{
		str = "tex/tiles/surfaceTile_93x2_" + to_string(i + 1) + ".bmp";
		IMAGEMANAGER->addFrameImage("tile_map" + to_string(i + 1), str.c_str(), 11160, 240, SAMPLETILEX, SAMPLETILEY, true, RGB(255, 0, 255));
	}

	IMAGEMANAGER->addFrameImage("pixel_map", "tex/tiles/pixelTile_93x2_01.bmp", 11160, 240, SAMPLETILEX, SAMPLETILEY, true, RGB(255, 0, 255));

	_pixelTiles = new image;
	_pixelTiles->init(TILESIZEX, TILESIZEY);

	//IMAGEMANAGER->addFrameImage("tile_map", "tex/tiles/surfaceTile_76x3_01.bmp", 9120, 360, SAMPLETILEX, SAMPLETILEY);

	_resource_yellowMineral.img = IMAGEMANAGER->findImage("resource_yellowMineral");
	_resource_blueFlowers.img = IMAGEMANAGER->findImage("resource_blueFlowers");
	_resource_redFlower.img = IMAGEMANAGER->findImage("resource_redFlower");

	for (int i = 0; i < 9; i++)
	{
		if (i < 5)
		{
			_object_grass[i].img = IMAGEMANAGER->findImage("object_grass" + to_string(i));
			_object_grass[i].rc = RectMake(0, 0, _object_grass[i].img->getWidth(), _object_grass[i].img->getHeight());
		}
		_object_bluePlant[i].img = IMAGEMANAGER->findImage("object_bluePlant" + to_string(i));
		//_object_bluePlant[i].rc = RectMake(0, 0, _object_bluePlant[i].img->getWidth(), _object_bluePlant[i].img->getHeight());
		_object_mushrooms[i].img = IMAGEMANAGER->findImage("object_mushrooms" + to_string(i));
		//_object_mushrooms[i].rc = RectMake(0, 0, _object_mushrooms[i].img->getWidth(), _object_mushrooms[i].img->getHeight());
		_object_whitePlant[i].img = IMAGEMANAGER->findImage("object_whitePlant" + to_string(i));
		//_object_whitePlant[i].rc = RectMake(0, 0, _object_whitePlant[i].img->getWidth(), _object_whitePlant[i].img->getHeight());
	}
	
	//맵툴셋팅
	this->maptoolSetup();

	//지형그리기 버튼으로 초기화
	_ctrlSelect = _oldCtrl = CTRL_TERRAINDRAW;

	_rcCamera = RectMake(0, TILESIZEY - WINSIZEY, WINSIZEX, WINSIZEY);
	CAMERAMANAGER->setCamera(_rcCamera);

	ShowCursor(false);
	_cursorIcon[0].img = IMAGEMANAGER->findImage("cursorIcon_idle");
	_cursorIcon[0].rc = RectMake(_ptMouse.x, _ptMouse.y, _cursorIcon[0].img->getWidth(), _cursorIcon[0].img->getHeight());
	_cursorIcon[1].img = IMAGEMANAGER->findImage("cursorIcon_erase");
	_cursorIcon[1].rc = RectMake(_ptMouse.x - 17, _ptMouse.y - 10, _cursorIcon[1].img->getFrameWidth(), _cursorIcon[1].img->getFrameHeight());
	_cursorIcon[1].img->setFrameX(0);
	
	_sampleTileType = 0;
	_count = 0;
	_saveDelta = 0;

	_dragStart = false;

	_globalPtMouse = { _ptMouse.x + CAMERAMANAGER->getCamera().left, _ptMouse.y + CAMERAMANAGER->getCamera().top };

	return S_OK;
}

void tileMap::release(void)
{
	SAFE_DELETE(_pixelTiles);
}

void tileMap::update(void)
{
	_globalPtMouse = { _ptMouse.x + CAMERAMANAGER->getCamera().left, _ptMouse.y + CAMERAMANAGER->getCamera().top };
	_cursorIcon[0].rc = RectMake(_ptMouse.x, _ptMouse.y, _cursorIcon[0].img->getWidth(), _cursorIcon[0].img->getHeight());
	_cursorIcon[1].rc = RectMake(_ptMouse.x - 17, _ptMouse.y - 10, _cursorIcon[1].img->getFrameWidth(), _cursorIcon[1].img->getFrameHeight());

	this->tileSelectPageSetup();
	this->UIsetup();
	this->keyInput();
	this->cameraAdjustment();
}

void tileMap::render(void)
{
	PatBlt(_pixelTiles->getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);

	SelectObject(getMemDC(), GetStockObject(NULL_BRUSH));
	SelectObject(getMemDC(), GetStockObject(DC_PEN));
	SetDCPenColor(getMemDC(), RGB(20, 20, 20));
	SelectObject(_pixelTiles->getMemDC(), GetStockObject(NULL_BRUSH));
	SelectObject(_pixelTiles->getMemDC(), GetStockObject(DC_PEN));
	SetDCPenColor(_pixelTiles->getMemDC(), RGB(20, 20, 20));
/*
	if (KEYMANAGER->isToggleKey('I'))
	{
		SelectObject(getMemDC(), GetStockObject(DC_BRUSH));
		SetDCBrushColor(getMemDC(), RGB(255, 255, 255));
		SelectObject(getMemDC(), GetStockObject(DC_PEN));
		SetDCPenColor(getMemDC(), RGB(235, 235, 235));
	}
*/
	//게임타일 렉트 렌더
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (CAMERAMANAGER->CameraIn(_tiles[i].rc))
		{
			Rectangle(getMemDC(), _tiles[i].rc.left - CAMERAMANAGER->getCamera().left, _tiles[i].rc.top - CAMERAMANAGER->getCamera().top, _tiles[i].rc.right - CAMERAMANAGER->getCamera().left, _tiles[i].rc.bottom - CAMERAMANAGER->getCamera().top);
			Rectangle(_pixelTiles->getMemDC(), _tiles[i].rc.left - CAMERAMANAGER->getCamera().left, _tiles[i].rc.top - CAMERAMANAGER->getCamera().top, _tiles[i].rc.right - CAMERAMANAGER->getCamera().left, _tiles[i].rc.bottom - CAMERAMANAGER->getCamera().top);

			IMAGEMANAGER->frameRender(_tiles[i].tileLabel, getMemDC(), _tiles[i].rc.left - CAMERAMANAGER->getCamera().left, _tiles[i].rc.top - CAMERAMANAGER->getCamera().top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
			IMAGEMANAGER->frameRender("pixel_map", _pixelTiles->getMemDC(), _tiles[i].rc.left - CAMERAMANAGER->getCamera().left, _tiles[i].rc.top - CAMERAMANAGER->getCamera().top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);

			if (_tiles[i].obj == OBJECT_NONE) continue;
			IMAGEMANAGER->frameRender(_tiles[i].tileLabel, getMemDC(), _tiles[i].rc.left - CAMERAMANAGER->getCamera().left, _tiles[i].rc.top - CAMERAMANAGER->getCamera().top, _tiles[i].objFrameX, _tiles[i].objFrameY);	
			IMAGEMANAGER->frameRender("pixel_map", _pixelTiles->getMemDC(), _tiles[i].rc.left - CAMERAMANAGER->getCamera().left, _tiles[i].rc.top - CAMERAMANAGER->getCamera().top, _tiles[i].objFrameX, _tiles[i].objFrameY);
		}
	}

	if (KEYMANAGER->isToggleKey('P'))
	{
		_pixelTiles->alphaRender(getMemDC(), 0, 0, 100);
	}

	this->cursorActionRender();
	
	_buildAMapText.img->alphaRender(getMemDC(), _buildAMapText.rc.left, _buildAMapText.rc.top, _buildAMapText.alpha);

	this->tileSelectPageRender();

	//IMAGEMANAGER->render("temp", getMemDC(), 0, 0);

	_button[CTRL_SAVE].img->alphaFrameRender(getMemDC(), _button[CTRL_SAVE].rc.left, _button[CTRL_SAVE].rc.top, _button[CTRL_SAVE].alpha);
	_button[CTRL_LOAD].img->alphaFrameRender(getMemDC(), _button[CTRL_LOAD].rc.left, _button[CTRL_LOAD].rc.top, _button[CTRL_LOAD].alpha);
	_button[CTRL_TERRAINDRAW].img->alphaFrameRender(getMemDC(), _button[CTRL_TERRAINDRAW].rc.left, _button[CTRL_TERRAINDRAW].rc.top, _button[CTRL_TERRAINDRAW].alpha);
	_button[CTRL_ERASER].img->alphaFrameRender(getMemDC(), _button[CTRL_ERASER].rc.left, _button[CTRL_ERASER].rc.top, _button[CTRL_ERASER].alpha);
	IMAGEMANAGER->alphaRender("button_tile", getMemDC(), 1128, _button[CTRL_ERASER].rc.top, _button[CTRL_ERASER].alpha);

	if (_ctrlSelect == CTRL_ERASER)
		_cursorIcon[1].img->frameRender(getMemDC(), _cursorIcon[1].rc.left, _cursorIcon[1].rc.top);
	else
		_cursorIcon[0].img->render(getMemDC(), _cursorIcon[0].rc.left, _cursorIcon[0].rc.top);

	char str[128];
	sprintf(str, "%d", _ctrlSelect);
	TextOut(getMemDC(), 100, 100, str, strlen(str));
}

void tileMap::maptoolSetup(void)
{
	//왼쪽 게임화면 렉트 초기화
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			_tiles[i * TILEX + j].rc = RectMake(j * TILESIZE, i * TILESIZE, TILESIZE, TILESIZE);
		}
	}

	//오른쪽 샘플타일 렉트 초기화
	for (int i = 0; i < SAMPLETILEY; i++)
	{
		for (int j = 0; j < SAMPLETILEX; j++)
		{
			_sampleTiles[i * SAMPLETILEX + j].rc = RectMake(500 + j * (TILESIZE + TILESIZE / 6), 307 + i * (TILESIZE + 50), TILESIZE, TILESIZE);
			_sampleTiles[i * SAMPLETILEX + j].backdrop = IMAGEMANAGER->addFrameImage("tile_backdrop" + to_string((i * SAMPLETILEX + j) + 1), "tex/tiles/Tile_Backdrop_02.bmp", 378, 157, 3, 1, true, RGB(255, 0, 255));
			_sampleTiles[i * SAMPLETILEX + j].backdrop->setFrameX(0);
			_sampleTiles[i * SAMPLETILEX + j].alpha = 0;
			_sampleTiles[i * SAMPLETILEX + j].terrain = terrainSelect(j, i);
			_sampleTiles[i * SAMPLETILEX + j].obj = objectSelect(j, i);
			//지형세팅
			_sampleTiles[i * SAMPLETILEX + j].terrainFrameX = j;
			_sampleTiles[i * SAMPLETILEX + j].terrainFrameY = i;
		}
	}

	_sampleTileStartX = _sampleTiles[0].rc.left;
	_sampleTileEndX = _sampleTiles[4].rc.right;

	//왼쪽화면을 모두 빈칸으로 기본타일 설정하기
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		_tiles[i].terrainFrameX = 23;
		_tiles[i].terrainFrameY = 1;
		_tiles[i].objFrameX = 0;
		_tiles[i].objFrameY = 0;
		_tiles[i].terrain = terrainSelect(_tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
		_tiles[i].obj = OBJECT_NONE;
	}

	_rangeEnd = _delta + 1;
	_rcRange = RectMakeCenter(_globalPtMouse.x, _globalPtMouse.y, _rangeEnd, _rangeEnd);

	_button[CTRL_SAVE].img = IMAGEMANAGER->findImage("button_save");
	_button[CTRL_SAVE].rc = RectMake(140, WINSIZEY * 1.1, _button[CTRL_SAVE].img->getFrameWidth(), _button[CTRL_SAVE].img->getFrameHeight());
	_button[CTRL_LOAD].img = IMAGEMANAGER->findImage("button_load");
	_button[CTRL_LOAD].rc = RectMake(347, WINSIZEY * 1.13, _button[CTRL_LOAD].img->getFrameWidth(), _button[CTRL_LOAD].img->getFrameHeight());
	_button[CTRL_TERRAINDRAW].img = IMAGEMANAGER->findImage("button_select");
	_button[CTRL_TERRAINDRAW].rc = RectMake(552, WINSIZEY * 1.16, _button[CTRL_TERRAINDRAW].img->getFrameWidth(), _button[CTRL_TERRAINDRAW].img->getFrameHeight());
	_button[CTRL_ERASER].img = IMAGEMANAGER->findImage("button_erase");
	_button[CTRL_ERASER].rc = RectMake(871, WINSIZEY * 1.19, _button[CTRL_ERASER].img->getFrameWidth(), _button[CTRL_ERASER].img->getFrameHeight());
	
	for (int i = 0; i < 5; i++)
		_button[i].alpha = 0;

	for (int i = 0; i < 2; i++)
	{
		_arrowButton[i].img = IMAGEMANAGER->findImage("button_arrow" + to_string(i + 1));
		_arrowButton[i].img->setFrameX(0);
		_arrowButton[i].img->setFrameY(i);
		_arrowButton[i].alpha = 0;
		_arrowButton[i].rc = RectMake(430 + (782 * i), 435, _arrowButton[i].img->getFrameWidth(), _arrowButton[i].img->getFrameHeight());
	}

	_characterMinor.img = IMAGEMANAGER->findImage("character_minor");
	_characterMinor.rc = RectMake(WINSIZEX, 118, _characterMinor.img->getWidth(), _characterMinor.img->getHeight());
	_characterMinor.alpha = 0;

	_textBubble_amber.img = IMAGEMANAGER->findImage("textBubble_amber");
	_textBubble_amber.rc = RectMake(WINSIZEX + 345, 15, _textBubble_amber.img->getWidth(), _textBubble_amber.img->getHeight());
	_textBubble_amber.alpha = 0;

	_terrain = TR_NONE;
	_descBubble_terrain[TR_GROUND].img = IMAGEMANAGER->findImage("textBubble_desc_tile_ground");
	for (int i = 0; i < 1; i++)
	{
		_descBubble_terrain[i].rc = RectMake(456, 27, _descBubble_terrain[i].img->getWidth(), _descBubble_terrain[i].img->getHeight());
		_descBubble_terrain[i].alpha = 0;
	}

	_object = OBJECT_NONE;
	_descBubble_object[OBJECT_TREE].img = IMAGEMANAGER->findImage("textBubble_desc_tile_tree");
	_descBubble_object[OBJECT_ROCK].img = IMAGEMANAGER->findImage("textBubble_desc_tile_rock");
	_descBubble_object[OBJECT_BGROCK].img = IMAGEMANAGER->findImage("textBubble_desc_tile_rock");
	for (int i = 0; i < 3; i++)
	{
		_descBubble_object[i].rc = RectMake(456, 27, _descBubble_object[i].img->getWidth(), _descBubble_object[i].img->getHeight());
		_descBubble_object[i].alpha = 0;
	}

	_buildAMapText.img = IMAGEMANAGER->findImage("text_buildAMap");
	_buildAMapText.rc = RectMakeCenter(WINSIZEX / 2, (0 - _buildAMapText.img->getHeight()), _buildAMapText.img->getWidth(), _buildAMapText.img->getHeight());
	_buildAMapText.alpha = 0;

	_blackSolid.img = IMAGEMANAGER->findImage("solid_black");
	_blackSolid.alpha = 0;

	_rcLetterBox[0] = RectMake(0, 0, WINSIZEX, 0);
	_rcLetterBox[1] = RectMake(0, WINSIZEY, WINSIZEX, 0);

	_descOn = false;
	_pageSwitch = false;
	_tileSelectPage = false;
	_moveSampleTiles = false;
}

void tileMap::setMap(void)
{
	RECT rcTemp;

	if (_tileSelectPage)
	{
		for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
		{
			if (_sampleTiles[i].rc.left < _sampleTileStartX || _sampleTiles[i].rc.right > _sampleTileEndX) continue;
			if (PtInRect(&_sampleTiles[i].rc, _ptMouse))
			{
				_currentTile.x = _sampleTiles[i].terrainFrameX;
				_currentTile.y = _sampleTiles[i].terrainFrameY;

				if (_sampleTiles[i].obj != OBJECT_NONE)
					_ctrlSelect = CTRL_OBJDRAW;
				else
					_ctrlSelect = CTRL_TERRAINDRAW;

				break;
			}
		}
	}
	else
	{
		for (int i = 0; i < TILEX * TILEY; i++)
		{
			if (PtInRect(&_tiles[i].rc, _globalPtMouse) || (_dragStart && IntersectRect(&rcTemp, &_tiles[i].rc, &_rcDrag)) || IntersectRect(&rcTemp, &_tiles[i].rc, &_rcRange))
			{
				//현재버튼이 지형이냐?
				if (_ctrlSelect == CTRL_TERRAINDRAW)
				{
					_tiles[i].terrainFrameX = _currentTile.x;
					_tiles[i].terrainFrameY = _currentTile.y;
					_tiles[i].terrain = terrainSelect(_currentTile.x, _currentTile.y);
					_tiles[i].tileLabel = "tile_map" + to_string(_sampleTileType + 1);
				}
				//현재버튼이 오브젝트냐?
				if (_ctrlSelect == CTRL_OBJDRAW)
				{
					_tiles[i].objFrameX = _currentTile.x;
					_tiles[i].objFrameY = _currentTile.y;
					_tiles[i].obj = objectSelect(_currentTile.x, _currentTile.y);
					_tiles[i].tileLabel = "tile_map" + to_string(_sampleTileType + 1);
				}
				//현재버튼이 지우개냐?
				if (_ctrlSelect == CTRL_ERASER)
				{
					_tiles[i].objFrameX = 0;
					_tiles[i].objFrameY = 0;
					_tiles[i].obj = OBJECT_NONE;
				}
			}
		}
	}
}

void tileMap::save(void)
{
	HANDLE file;
	DWORD write;
	
	file = CreateFile("save.map", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &write, NULL);

	CloseHandle(file);
}

void tileMap::load(void)
{
	HANDLE file;
	DWORD read;

	file = CreateFile("save.map", GENERIC_READ, 0, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);

	CloseHandle(file);
}

void tileMap::keyInput(void)
{
	if (KEYMANAGER->isOnceKeyDown('C'))
	{
		_button[CTRL_TERRAINDRAW].img->setFrameX(1);
		_pageSwitch = !_pageSwitch;
		_delta = _saveDelta;
		_count = 0;
		if (!_pageSwitch)
			_delta = 0;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (_ctrlSelect == CTRL_ERASER)
			_cursorIcon[1].img->setFrameX(1);

		if (_tileSelectPage)
		{
			_sampleTileType = _delta;

			if (!_moveSampleTiles)
			{
				for (int i = 0; i < 2; i++)
				{
					if (PtInRect(&_arrowButton[i].rc, _ptMouse))
					{
						_moveSampleTiles = true;
						_isLeft = i ? true : false;
						_count = 0;
					}
				}
			}
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		if (_ctrlSelect == CTRL_ERASER)
			_cursorIcon[1].img->setFrameX(1);

		if (!_tileSelectPage)
		{
			this->drawRcDrag();
		}

		this->setMap();
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		_dragStart = false;
		if (_ctrlSelect == CTRL_ERASER)
			_cursorIcon[1].img->setFrameX(0);
	}

	if (_tileSelectPage)
	{
		if (KEYMANAGER->isStayKeyDown('A'))
		{
			_moveSampleTiles = true;
			_isLeft = false;
			_count = 0;
		}

		if (KEYMANAGER->isStayKeyDown('D'))
		{
			_moveSampleTiles = true;
			_isLeft = true;
			_count = 0;
		}
	}
	else
	{
		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			if (!_tileSelectPage)
			{
				_button[CTRL_SAVE].img->setFrameX(1);
				_ctrlSelect = CTRL_SAVE;
				this->save();
			}
		}
		if (KEYMANAGER->isOnceKeyUp('Z'))
			_button[CTRL_SAVE].img->setFrameX(0);

		if (KEYMANAGER->isOnceKeyDown('X'))
		{
			if (!_tileSelectPage)
			{
				_button[CTRL_LOAD].img->setFrameX(1);
				_ctrlSelect = CTRL_LOAD;
				this->load();
			}
		}
		if (KEYMANAGER->isOnceKeyUp('X'))
			_button[CTRL_LOAD].img->setFrameX(0);

		if (KEYMANAGER->isOnceKeyDown('V'))
		{
			if (!_tileSelectPage)
			{
				if (_ctrlSelect != CTRL_ERASER)
				{
					_button[CTRL_ERASER].img->setFrameX(1);
					_delta = 0;
					_oldCtrl = _ctrlSelect;
					_ctrlSelect = CTRL_ERASER;
				}
				else
				{
					_delta = 0;
					_button[CTRL_ERASER].img->setFrameX(0);
					_ctrlSelect = _oldCtrl;
				}
			}
		}

		if (KEYMANAGER->isOnceKeyDown('Q'))
		{
			SCENEMANAGER->loadScene("흑로딩화면");
		}

		this->drawRcRange();
	}
}

void tileMap::tileSelectPageSetup(void)
{
	RECT _rcBackdrop[SAMPLETILEX * SAMPLETILEY];
	float speed, angle;
	if (_pageSwitch)
	{
		_tileSelectPage = true;
		
		if (_ctrlSelect == CTRL_ERASER)
		{
			_button[CTRL_ERASER].img->setFrameX(0);
			_ctrlSelect = _oldCtrl;
		}

		if (_tileSelectPage)
		{
			_saveDelta = _delta;
			//_ctrlSelect = CTRL_TERRAINDRAW;

			if (_rcLetterBox[0].bottom < 80 && _rcLetterBox[1].top > WINSIZEY - 80)
			{
				_rcLetterBox[0].bottom += -sinf(-PI_2) * 5.0f;
				_rcLetterBox[1].top += -sinf(PI_2) * 5.0f;
			}
			
			if (_blackSolid.alpha < 150)
				_blackSolid.alpha += 5;
			
			if (_characterMinor.alpha < 255)
				_characterMinor.alpha += 15;
				
			if (_textBubble_amber.alpha > 100)
			{
				for (int i = 0; i < 2; i++)
				{
					if (_arrowButton[i].alpha < 255)
						_arrowButton[i].alpha += 15;
					else
					{
						if (PtInRect(&_arrowButton[i].rc, _ptMouse))
							_arrowButton[i].img->setFrameX(1);
						else
							_arrowButton[i].img->setFrameX(0);
					}
				}
			}
			
			if (_characterMinor.rc.left > -47)
			{
				speed = 95.0f;
				_characterMinor.rc.left += cosf(PI) * speed;
				_characterMinor.rc.right += cosf(PI) * speed;
				_textBubble_amber.rc.left += cosf(PI) * speed;
				_textBubble_amber.rc.right += cosf(PI) * speed;
			}

			for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
			{
				_rcBackdrop[i] = RectMake(_sampleTiles[i].rc.left - 3, _sampleTiles[i].rc.top - 3, _sampleTiles[i].backdrop->getFrameWidth(), _sampleTiles[i].backdrop->getFrameHeight());
			
				if (PtInRect(&_rcBackdrop[i], _ptMouse))
					_sampleTiles[i].backdrop->setFrameX(1);
				
				else
					_sampleTiles[i].backdrop->setFrameX(0);

				if (_sampleTiles[i].rc.left >= _sampleTileStartX && _sampleTiles[i].rc.right <= _sampleTileEndX)
				{
					if (_sampleTiles[i].alpha < 255)
						_sampleTiles[i].alpha += 5;
				}
				else
					_sampleTiles[i].alpha = 0;
				
				if (_sampleTiles[i].terrainFrameX == _currentTile.x && _sampleTiles[i].terrainFrameY == _currentTile.y)
					_sampleTiles[i].backdrop->setFrameX(2);

				if (_moveSampleTiles)
				{
					_arrowButton[_isLeft].img->setFrameX(1);

					speed = TILESIZE + TILESIZE / 6;
					angle = _isLeft ? PI : 0.0f;
					
					_sampleTiles[i].rc.left += cosf(angle) * speed;
					_sampleTiles[i].rc.right += cosf(angle) * speed;
				}
			}
			
			_moveSampleTiles = false;

			this->descBubble(_rcBackdrop);
		}
	}
	else
	{
		if (_tileSelectPage)
		{
			if (_rcLetterBox[0].bottom > 0 && _rcLetterBox[1].top < WINSIZEY)
			{
				_rcLetterBox[0].bottom -= -sinf(-PI_2) * 5.0f;
				_rcLetterBox[1].top -= -sinf(PI_2) * 5.0f;
			}
			
			for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
			{
				if (_sampleTiles[i].alpha > 0)
					_sampleTiles[i].alpha -= 15;
			}
			
			for (int i = 0; i < 2; i++)
			{
				if (_arrowButton[i].alpha > 0)
					_arrowButton[i].alpha -= 15;
			}
			
			if (_blackSolid.alpha > 0)
				_blackSolid.alpha -= 10;
			
			if (_characterMinor.alpha > 0)
				_characterMinor.alpha -= 15;
			
			if (_textBubble_amber.alpha > 0)
				_textBubble_amber.alpha -= 15;
			else
			{
				_characterMinor.rc = RectMake(WINSIZEX, _characterMinor.rc.top, _characterMinor.img->getWidth(), _characterMinor.img->getHeight());
				_textBubble_amber.rc = RectMake(WINSIZEX + 345, _textBubble_amber.rc.top, _textBubble_amber.img->getWidth(), _textBubble_amber.img->getHeight());
				_tileSelectPage = false;
			}
		}
		else
		{
			//_delta = 0;
			_button[CTRL_TERRAINDRAW].img->setFrameX(0);
		}
	}
}

void tileMap::tileSelectPageRender(void)
{
	if (_tileSelectPage)	//타일 선택 페이지 렌더
	{
		SelectObject(getMemDC(), GetStockObject(DC_BRUSH));
		SetDCBrushColor(getMemDC(), RGB(0, 0, 0));
		SelectObject(getMemDC(), GetStockObject(DC_PEN));
		SetDCPenColor(getMemDC(), RGB(0, 0, 0));
		Rectangle(getMemDC(), _rcLetterBox[0]);
		Rectangle(getMemDC(), _rcLetterBox[1]);
		_blackSolid.img->alphaRender(getMemDC(), _blackSolid.alpha);

		for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
		{
			if (_sampleTiles[i].rc.left < _sampleTileStartX || _sampleTiles[i].rc.right > _sampleTileEndX) continue;
			IMAGEMANAGER->alphaFrameRender("tile_map" + to_string(_saveDelta + 1), getMemDC(), _sampleTiles[i].rc.left, _sampleTiles[i].rc.top, _sampleTiles[i].terrainFrameX, _sampleTiles[i].terrainFrameY, _sampleTiles[i].alpha);
			_sampleTiles[i].backdrop->alphaFrameRender(getMemDC(), _sampleTiles[i].rc.left - 3, _sampleTiles[i].rc.top - 3, _sampleTiles[i].alpha);
			if (KEYMANAGER->isToggleKey(VK_F2))
			{
				char str[128];
				sprintf(str, "%d", i);
				TextOut(getMemDC(), _sampleTiles[i].rc.left, _sampleTiles[i].rc.top, str, strlen(str));
			}
		}

		if (_terrain != TR_NONE)
			_descBubble_terrain[_terrain].img->render(getMemDC(), _descBubble_terrain[_terrain].rc.left, _descBubble_terrain[_terrain].rc.top);
		else if (_object != OBJECT_NONE)
			_descBubble_object[_object].img->render(getMemDC(), _descBubble_object[_object].rc.left, _descBubble_object[_object].rc.top);
		else
			_textBubble_amber.img->alphaRender(getMemDC(), _textBubble_amber.rc.left, _textBubble_amber.rc.top, _textBubble_amber.alpha);

		if (_sampleTiles[0].rc.left < _sampleTileStartX)
			_arrowButton[0].img->alphaFrameRender(getMemDC(), _arrowButton[0].rc.left, _arrowButton[0].rc.top, _arrowButton[0].alpha);
		if (_sampleTiles[SAMPLETILEX - 1].rc.right > _sampleTileEndX)
			_arrowButton[1].img->alphaFrameRender(getMemDC(), _arrowButton[1].rc.left, _arrowButton[1].rc.top, _arrowButton[1].alpha);

		_characterMinor.img->alphaRender(getMemDC(), _characterMinor.rc.left, _characterMinor.rc.top, _characterMinor.alpha);
	}
}

void tileMap::UIsetup(void)
{
	RECT rcTemp;

	if (_count <= 50)
		_count++;

	if (_tileSelectPage)
	{
		for (int i = 0; i < 5; i++)
		{
			if (i == CTRL_OBJDRAW || i == CTRL_TERRAINDRAW) continue;
			if (_button[i].alpha > 75)
				_button[i].alpha -= 15;
		}
		
		if (_buildAMapText.alpha > 0)
			_buildAMapText.alpha -= 15;
		else
			_buildAMapText.rc = RectMakeCenter(WINSIZEX / 2, 0 - _buildAMapText.img->getHeight(), _buildAMapText.img->getWidth(), _buildAMapText.img->getHeight());
	}
	else
	{
		if (_count <= 51)
		{
			if (_buildAMapText.alpha < 255)
				_buildAMapText.alpha += 5;
			
			if (_buildAMapText.rc.top < 55)
			{
				_buildAMapText.rc.top += sinf(PI_2) * 8.0f;
				_buildAMapText.rc.bottom += sinf(PI_2) * 8.0f;
			}
		}
		else
		{
			if (IntersectRect(&rcTemp, &_buildAMapText.rc, &_cursorIcon[0].rc))
				_buildAMapText.alpha = 70;
			else
				_buildAMapText.alpha = 255;
		}

		for (int i = 0; i < 5; i++)
		{
			if (i == CTRL_OBJDRAW) continue;
			if (_count <= 51)
			{
				if (_button[i].alpha < 255 && _button[i].rc.top <= WINSIZEY)
					_button[i].alpha += 15;
				if (_button[i].rc.top > 661)
				{
					_button[i].rc.top -= sinf(PI_2) * (661 / 102);
					_button[i].rc.bottom -= sinf(PI_2) * (661 / 102);
				}
			}
			else
			{
				if (IntersectRect(&rcTemp, &_button[i].rc, &_cursorIcon[0].rc))
					_button[i].alpha = 70;
				else
					_button[i].alpha = 255;
			}
		}
	}
}

void tileMap::descBubble(RECT *rcBackdrop)
{
	for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
	{
		if (_sampleTiles[i].rc.left < _sampleTileStartX || _sampleTiles[i].rc.right > _sampleTileEndX) continue;
		if (PtInRect(&rcBackdrop[i], _ptMouse))
		{
			_terrain = _sampleTiles[i].terrain;
			_object = _sampleTiles[i].obj;
			_descOn = true;
			break;
		}
		else
		{
			_terrain = TR_NONE;
			_object = OBJECT_NONE;
			_descOn = false;
		}
	}

	if (_descOn)
	{
		if (_textBubble_amber.alpha > 0)
			_textBubble_amber.alpha -= 15;

		if (_descBubble_terrain[_terrain].alpha < 240 && _terrain != TR_NONE)
			_descBubble_terrain[_terrain].alpha += 15;

		if (_descBubble_object[_object].alpha < 240 && _object != OBJECT_NONE)
			_descBubble_object[_object].alpha += 15;
	}
	else
	{
		if (_textBubble_amber.alpha < 240)
			_textBubble_amber.alpha += 15;

		if (_descBubble_terrain[_terrain].alpha > 0)
			_descBubble_terrain[_terrain].alpha -= 15;

		if (_descBubble_object[_object].alpha > 0)
			_descBubble_object[_object].alpha -= 15;
	}
}

void tileMap::drawRcRange(void)
{
	_rangeEnd = (_delta + 1) * 1.5;
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (PtInRect(&_tiles[i].rc, _globalPtMouse))
		{
			_rcRange = RectMakeCenter(_tiles[i].rc.left + (_tiles[i].rc.right - _tiles[i].rc.left) / 2, _tiles[i].rc.top + (_tiles[i].rc.bottom - _tiles[i].rc.top) / 2, TILESIZE * _rangeEnd, TILESIZE * _rangeEnd);
		}
	}
}

void tileMap::drawRcDrag(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_SHIFT))
	{
		if (!_dragStart)
		{
			_dragStartX = _globalPtMouse.x;
			_dragStartY = _globalPtMouse.y;
			_rcDrag = { _dragStartX, _dragStartY, (LONG)_globalPtMouse.x, (LONG)_globalPtMouse.y };
			_dragStart = true;
		}
		else
		{
			_rcDrag = { _dragStartX, _dragStartY, (LONG)_globalPtMouse.x, (LONG)_globalPtMouse.y };
		}
	}
	else
	{
		_dragStart = false;
	}
}

void tileMap::cursorActionRender(void)
{
	if (!_tileSelectPage)
	{
		SelectObject(getMemDC(), GetStockObject(DC_PEN));
		SetDCPenColor(getMemDC(), RGB(58, 213, 255));
		RECT ptRect = RectMakeCenter((LONG)_ptMouse.x + CAMERAMANAGER->getCamera().left, (LONG)_ptMouse.y + CAMERAMANAGER->getCamera().top, TILESIZE * 2, TILESIZE * 2);
		RECT rcTemp;
		for (int i = 0; i < TILEX * TILEY; i++)
		{
			if (CAMERAMANAGER->CameraIn(_tiles[i].rc))
			{
				if (_dragStart)
				{
					if (_ctrlSelect == CTRL_ERASER)
					{
						SelectObject(getMemDC(), GetStockObject(DC_PEN));
						SetDCPenColor(getMemDC(), RGB(255, 255, 255));
					}
					//Rectangle(getMemDC(), _rcDrag.left - CAMERAMANAGER->getCamera().left, _rcDrag.top - CAMERAMANAGER->getCamera().top, 
					//	_rcDrag.right - CAMERAMANAGER->getCamera().left, _rcDrag.bottom - CAMERAMANAGER->getCamera().top);
					if (IntersectRect(&rcTemp, &_rcDrag, &_tiles[i].rc))
					{
						Rectangle(getMemDC(), _tiles[i].rc.left - CAMERAMANAGER->getCamera().left, _tiles[i].rc.top - CAMERAMANAGER->getCamera().top,
							_tiles[i].rc.right - CAMERAMANAGER->getCamera().left, _tiles[i].rc.bottom - CAMERAMANAGER->getCamera().top);
					}
				}
				else
				{
					if (IntersectRect(&rcTemp, &_rcRange, &_tiles[i].rc))
					{
						if (_ctrlSelect == CTRL_ERASER)
						{
							//SelectObject(getMemDC(), GetStockObject(DC_PEN));
							SetDCPenColor(getMemDC(), RGB(255, 255, 255));
						}
						Rectangle(getMemDC(), _tiles[i].rc.left - CAMERAMANAGER->getCamera().left, _tiles[i].rc.top - CAMERAMANAGER->getCamera().top,
							_tiles[i].rc.right - CAMERAMANAGER->getCamera().left, _tiles[i].rc.bottom - CAMERAMANAGER->getCamera().top);
					}
				}
				if (PtInRect(&_tiles[i].rc, _globalPtMouse))
				{
					if (_ctrlSelect == CTRL_ERASER)
					{
						//SelectObject(getMemDC(), GetStockObject(DC_PEN));
						SetDCPenColor(getMemDC(), RGB(255, 255, 255));
					}
					Rectangle(getMemDC(), _tiles[i].rc.left - CAMERAMANAGER->getCamera().left, _tiles[i].rc.top - CAMERAMANAGER->getCamera().top,
						_tiles[i].rc.right - CAMERAMANAGER->getCamera().left, _tiles[i].rc.bottom - CAMERAMANAGER->getCamera().top);
				}

				if (PtInRect(&_tiles[i].rc, _globalPtMouse) || IntersectRect(&rcTemp, &_rcRange, &_tiles[i].rc) || (_dragStart && IntersectRect(&rcTemp, &_rcDrag, &_tiles[i].rc)))
				{
					if (_ctrlSelect == CTRL_ERASER)
						IMAGEMANAGER->alphaRender("white_tile", getMemDC(), _tiles[i].rc.left - CAMERAMANAGER->getCamera().left, _tiles[i].rc.top - CAMERAMANAGER->getCamera().top, 30);
					else
					{
						IMAGEMANAGER->alphaRender("teal_tile", getMemDC(), _tiles[i].rc.left - CAMERAMANAGER->getCamera().left, _tiles[i].rc.top - CAMERAMANAGER->getCamera().top, 30);
						IMAGEMANAGER->alphaFrameRender("tile_map" + to_string(_sampleTileType + 1), getMemDC(), _tiles[i].rc.left - CAMERAMANAGER->getCamera().left, _tiles[i].rc.top - CAMERAMANAGER->getCamera().top, _currentTile.x, _currentTile.y, 100);
					}
				}
			}
		}
	}
}

void tileMap::cameraAdjustment(void)
{
	/*for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (PtInRect(&_tiles[i].rc, _globalPtMouse))
		{
			if (_tiles[i].rc.left <= _rcCamera.left && _tiles[i].rc.right > _rcCamera.left)
			{
				_rcCamera.left = _tiles[i].rc.left - TILESIZE / 2;
				_rcCamera.right = _rcCamera.left + WINSIZEX;
			}
			else if (_tiles[i].rc.left < _rcCamera.right && _tiles[i].rc.right >= _rcCamera.right)
			{
				_rcCamera.right = _tiles[i].rc.right + TILESIZE / 2;
				_rcCamera.left = _rcCamera.right - WINSIZEX;
			}
			if (_tiles[i].rc.top <= _rcCamera.top && _tiles[i].rc.bottom > _rcCamera.top)
			{
				_rcCamera.top = _tiles[i].rc.top - TILESIZE / 2;
				_rcCamera.bottom = _rcCamera.top + WINSIZEY;
			}
			else if (_tiles[i].rc.top < _rcCamera.bottom && _tiles[i].rc.bottom >= _rcCamera.bottom)
			{
				_rcCamera.bottom = _tiles[i].rc.bottom + TILESIZE / 2;
				_rcCamera.top = _rcCamera.bottom - WINSIZEY;
			}
		}
	}*/

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

	if (!_tileSelectPage)
	{
		if (_cursorIcon[1].rc.left <= _rcCamera.left)
		{
			_rcCamera.left = _cursorIcon[1].rc.left - TILESIZE / 2;
			_rcCamera.right = _rcCamera.left + WINSIZEX;
		}
		else if (_cursorIcon[1].rc.right >= _rcCamera.right)
		{
			_rcCamera.right = _cursorIcon[1].rc.right + TILESIZE / 2;
			_rcCamera.left = _rcCamera.right - WINSIZEX;
		}
		if (_cursorIcon[1].rc.top <= _rcCamera.top)
		{
			_rcCamera.top = _cursorIcon[1].rc.top - TILESIZE / 2;
			_rcCamera.bottom = _rcCamera.top + WINSIZEY;
		}
		else if (_cursorIcon[1].rc.bottom >= _rcCamera.bottom)
		{
			_rcCamera.bottom = _cursorIcon[1].rc.bottom + TILESIZE / 2;
			_rcCamera.top = _rcCamera.bottom - WINSIZEY;
		}
	}

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

TERRAIN tileMap::terrainSelect(int frameX, int frameY)
{
	if (frameX <= 23 && frameY <= 1)
	{
		return TR_GROUND;
	}
	return TR_NONE;
}

OBJECT tileMap::objectSelect(int frameX, int frameY)
{
	if (24 <= frameX && frameX <= 41 && frameY <= 1)
	{
		return OBJECT_ROCK;
	}
	else if (42 <= frameX && frameX <= 59 && frameY <= 1)
	{
		return OBJECT_BGROCK;
	}
	else if (60 <= frameX && frameX < SAMPLETILEX && frameY <= 1)
	{
		return OBJECT_TREE;
	}
	return OBJECT_NONE;
}