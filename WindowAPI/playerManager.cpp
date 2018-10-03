#include "stdafx.h"
#include "playerManager.h"

HRESULT playerManager::init(void)
{
	_character = CLU;

	_player[CLU] = new player;
	_player[CLU]->init(CLU);
	_player[BART] = new player;
	_player[BART]->init(BART);

	_player[_character]->setIsActive(true);
	_player[!_character]->setIsActive(false);

	_bullet = new bullet;
	_bullet->init("bullet_blue", 3, 500);
	
	_triBullet = new triBullet;
	_triBullet->init("bullet_blue", 3, 500);

	_arrow = new arrow;
	_arrow->init("bullet_arrow", 10, WINSIZEX);

	_triArrow = new triArrow;
	_triArrow->init("bullet_arrow", 30, WINSIZEX);

	_block[CLU] = new block;
	_block[CLU]->init("dynamiteTrap_idle", "dynamiteTrap_idle_shadow", 40, true);

	_block[BART] = new block;
	_block[BART]->init("defenseBlock", "defenseBlock_shadow", 40);
	
	this->setGUI();
	this->setFollow();

	_idleCount = _blackSolidAlpha = 0;
	_isStayKey_up = _isStayKey_down = _isBuild = false;
	_idleMax = RND->getFromIntTo(100, 500);

	return S_OK;
}

void playerManager::release(void)
{
	for (int i = 0; i < 2; i++)
	{
		_player[i]->release();
		SAFE_DELETE(_player[i]);
		_block[i]->release();
		SAFE_DELETE(_block[i]);
	}
	_bullet->release();
	SAFE_DELETE(_bullet);
	_triBullet->release();
	SAFE_DELETE(_triBullet);
	_arrow->release();
	SAFE_DELETE(_arrow);
	_triArrow->release();
	SAFE_DELETE(_triArrow);
}

void playerManager::update(void)
{
	_bullet->update();
	_triBullet->update();
	_arrow->update();
	_triArrow->update();

	_block[_character]->update();
	_block[!_character]->update();

	this->keyInput();
	this->playerBackstep();
	this->playerJumpFall();

	_player[_character]->update();
	_player[!_character]->update();
	
	this->collisionProcess();
	this->blockCollision();
	this->playerFaceDown();
	this->playerHit();
	this->playerLedgeGrab();
	this->playerFaint();
	this->fromStateToIdle();
	this->fromIdleToState();
	this->playerFollow();
	this->GUIupdate();
}

void playerManager::render(void)
{
	_bullet->render();
	_triBullet->render();
	_arrow->render();
	_triArrow->render();

	_block[CLU]->render();
	_block[BART]->render();

	_player[!_character]->render();
	_player[_character]->render();

	this->buildRender();

	//체력바 렌더
	_player[_character]->getHpBarRed()->render(getMemDC());
	_player[_character]->getHpBarYellow()->render(getMemDC());

	this->GUIrender();
}

void playerManager::setGUI()
{
	_blueFlower.img = IMAGEMANAGER->findImage("GUI_blueFlower");
	_blueFlower.rc = RectMake(1163, 25, _blueFlower.img->getWidth(), _blueFlower.img->getHeight());
	_blueFlower.isActive = true;
	_blueFlowerCount = 3;
	_blueFlowerMax = 3;
	_mineral.img = IMAGEMANAGER->findImage("GUI_mineral");
	_mineral.rc = RectMake(1163, 89, _mineral.img->getWidth(), _mineral.img->getHeight());
	_mineral.isActive = true;
	_mineralCount = 3;
	_mineralMax = 3;

	_icon[CLU].img = IMAGEMANAGER->findImage("GUI_icon_clu");
	_icon[CLU].shadow = IMAGEMANAGER->findImage("GUI_icon_clu_shadow");
	_icon[CLU].img->setFrameX(1);
	_icon[CLU].rc = RectMake(564, 13, _icon[CLU].img->getFrameWidth(), _icon[CLU].img->getFrameHeight());

	_icon[BART].img = IMAGEMANAGER->findImage("GUI_icon_bart");
	_icon[BART].img->setFrameX(0);
	_icon[BART].shadow = IMAGEMANAGER->findImage("GUI_icon_bart_shadow");
	_icon[BART].rc = RectMake(_icon[CLU].rc.right + 3, 13, _icon[BART].img->getFrameWidth(), _icon[BART].img->getFrameHeight());

	_button_bomb.img = IMAGEMANAGER->findImage("GUI_button_bomb");
	_button_bomb.x = 773, _button_bomb.y = WINSIZEY;
	_button_bomb.alpha = 0;
}

void playerManager::GUIupdate()
{
	_icon[_character].img->setFrameX(1);
	_icon[!_character].img->setFrameX(0);

	if (_isBuild)
	{
		if (_button_bomb.y > 663)
			_button_bomb.y -= 663 / 80;

		if (_button_bomb.alpha < 255)
			_button_bomb.alpha += 15;

		if (_blackSolidAlpha < 180)
			_blackSolidAlpha += 15;
	}
	else
	{
		if (_button_bomb.y < WINSIZEY)
			_button_bomb.y += 663 / 80;

		if (_button_bomb.alpha > 0)
			_button_bomb.alpha -= 15;

		if (_blackSolidAlpha > 0)
			_blackSolidAlpha -= 15;
	}
}

void playerManager::GUIrender()
{
	_button_bomb.img->alphaRender(getMemDC(), _button_bomb.x, _button_bomb.y, _button_bomb.alpha);

	if (_blueFlower.isActive)
		_blueFlower.img->render(getMemDC(), _blueFlower.rc.left, _blueFlower.rc.top);
	if (_mineral.isActive)
		_mineral.img->render(getMemDC(), _mineral.rc.left, _mineral.rc.top);

	for (int i = 0; i < 2; i++)
	{
		_icon[i].shadow->alphaFrameRender(getMemDC(), _icon[i].rc.left, _icon[i].rc.top, _icon[i].img->getFrameX(), _icon[i].img->getFrameY(), 200);
		_icon[i].img->frameRender(getMemDC(), _icon[i].rc.left, _icon[i].rc.top, _icon[i].img->getFrameX(), _icon[i].img->getFrameY());
	}

	char str[128];
	HFONT myFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "FirstFont-Bold");
	HFONT oldFont = (HFONT)SelectObject(getMemDC(), myFont);
	SetBkMode(getMemDC(), TRANSPARENT);

	SetTextColor(getMemDC(), RGB(50, 50, 50));
	sprintf_s(str, "%d/3", _blueFlowerCount);
	TextOut(getMemDC(), 1195, 53, str, strlen(str));
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	TextOut(getMemDC(), 1195, 51, str, strlen(str));

	SetTextColor(getMemDC(), RGB(50, 50, 50));
	sprintf_s(str, "%d/3", _mineralCount);
	TextOut(getMemDC(), 1195, 118, str, strlen(str));
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	TextOut(getMemDC(), 1195, 116, str, strlen(str));

	SelectObject(getMemDC(), oldFont);
	DeleteObject(myFont);
}

void playerManager::buildRender()
{
	if (_isBuild)
	{
		IMAGEMANAGER->alphaRender("solid_black", getMemDC(), _blackSolidAlpha);
		IMAGEMANAGER->alphaRender("bomb_selectDot", getMemDC(), _player[_character]->getX() - 44 * 0.5f - 2 - CAMERAMANAGER->getCamera().left, _player[_character]->getY() - 44 * 0.33f - 2 - CAMERAMANAGER->getCamera().top, _button_bomb.alpha);

		if (_character == CLU)
			IMAGEMANAGER->alphaRender("bomb_text", getMemDC(), _player[_character]->getX() - 153 * 0.5f - CAMERAMANAGER->getCamera().left, _player[_character]->getY() - 130 - CAMERAMANAGER->getCamera().top, _button_bomb.alpha);
		else
			IMAGEMANAGER->alphaRender("defenseBlock_text", getMemDC(), _player[_character]->getX() - 262 * 0.5f - CAMERAMANAGER->getCamera().left, _player[_character]->getY() - 130 - CAMERAMANAGER->getCamera().top, _button_bomb.alpha);

		_block[_character]->render();
	}
}

void playerManager::setFollow()
{
	_saveCount = _saveIndex = 0;
	_isFollowing = false;

	for (int i = 0; i < 30; i++)
	{
		_saveProperties[i].state = _player[!_character]->getState();
		_saveProperties[i].x = _player[!_character]->getX();
		_saveProperties[i].y = _player[!_character]->getY();
		_saveProperties[i].index = _player[!_character]->getIndex();
		_saveProperties[i].count = _player[!_character]->getCount();
		_saveProperties[i].isLeft = _player[!_character]->getIsLeft();
	}
}

void playerManager::keyInput()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))// || KEYMANAGER->isStayKeyDown('A'))
	{
		if (!_isBuild)
			this->playerRun(LEFT);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))// || KEYMANAGER->isStayKeyDown('A'))
	{
		if (_isBuild)
			_block[_character]->move(LEFT);
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))// || KEYMANAGER->isStayKeyDown('D'))
	{
		if (!_isBuild)
			this->playerRun(RIGHT);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))// || KEYMANAGER->isStayKeyDown('D'))
	{
		if (_isBuild)
			_block[_character]->move(RIGHT);
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))// || KEYMANAGER->isStayKeyDown('W'))
	{
		_isStayKey_up = true;
		if (!_isBuild && _player[_character]->getOnLand())
		{
			if (_player[_character]->getState() == AIM_IDLE)
				_player[_character]->setState(AIM_DIAGONAL);
			else if (_player[_character]->getState() != RUN && _player[_character]->getState() != AIM_DIAGONALFIRE && _player[_character]->getState() != AIM_DIAGONAL)
				if (!_player[_character]->getIsFired())
					_player[_character]->setState(LOOKUP);
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_UP))// || KEYMANAGER->isStayKeyDown('W'))
	{
		if (_isBuild)
			_block[_character]->move(TOP);
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))// || KEYMANAGER->isStayKeyDown('S'))
	{
		_isStayKey_down = true;

		if (!_isBuild && _player[_character]->getOnLand())
		{
			if (!_player[_character]->getIsFaceDown())
				EFFECTMANAGER->play("landDust", _player[_character]->getX(), _player[_character]->getY() + _player[_character]->getPlayerImage()->getFrameHeight() * 0.35);
			_player[_character]->setIsFaceDown(true);
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))// || KEYMANAGER->isStayKeyDown('S'))
	{
		_isStayKey_down = true;

		if (_isBuild)
			_block[_character]->move(BOTTOM);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		if (CAMERAMANAGER->getSwitchStart())
		{
			EFFECTMANAGER->play("ellipsePuff2", _player[_character]->getX(), _player[_character]->getY() + _player[_character]->getPlayerImage()->getFrameHeight() * 0.15f);
			EFFECTMANAGER->play("regen", _player[_character]->getX(), _player[_character]->getY() + _player[_character]->getPlayerImage()->getFrameHeight() * 0.45f);
			CAMERAMANAGER->setSwitchStart(false);
		}
		else
		{
			if (_isBuild)
			{
				if (_isBuild)
					_block[_character]->activate();
				_character ? _mineralCount-- : _blueFlowerCount--;
				_isBuild = false;
			}
			else
			{
				_player[_character]->setIsLedgeGrab(false);
				this->playerJumpRise();
			}
		}
	}
	if (KEYMANAGER->isOnceKeyDown('L'))
	{
		if (_player[_character]->getOnLand())
		{
			_player[_character]->setIsBackstep(true);
			_player[_character]->setCount(0);
		}
	}
	if (KEYMANAGER->isOnceKeyDown('K'))
	{
		this->playerBuild();
	}
	if (KEYMANAGER->isStayKeyDown('J'))
	{
		this->playerFullCharge();
	}
	if (KEYMANAGER->isOnceKeyUp('J'))
	{
		this->playerAttack();
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT) || KEYMANAGER->isOnceKeyUp(VK_RIGHT)) // || KEYMANAGER->isOnceKeyUp('A') || KEYMANAGER->isOnceKeyUp('D'))
	{
		_player[_character]->setState(IDLE);
	}
	if (KEYMANAGER->isOnceKeyUp(VK_UP)) // || KEYMANAGER->isOnceKeyUp('W'))
	{
		_player[_character]->setState(IDLE);
		_isStayKey_up = false;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_DOWN))// || KEYMANAGER->isOnceKeyUp('S'))
	{
		_isStayKey_down = false;
		_player[_character]->setIsFaceDown(false);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_TAB) || KEYMANAGER->isOnceKeyDown(VK_SHIFT))
	{
		_player[_character]->setCurrentWeapon(!_player[_character]->getCurrentWeapon());
		_player[_character]->setWeaponSwitch(true);
	}
	if (KEYMANAGER->isOnceKeyDown('I') || KEYMANAGER->isOnceKeyDown('O'))
	{
		_character = _character ? CLU : BART;
		
		_player[_character]->setIsActive(true);
		_player[!_character]->setIsActive(false);
	}
	if (KEYMANAGER->isToggleKey(VK_OEM_1))	//';'
	{
		this->playerFollow();
	}
	else
	{
		_saveCount = 0;
		_saveIndex = 0;
		_isFollowing = false;
		_player[!_character]->setState(IDLE);
	}
}

void playerManager::playerRun(bool isLeft)
{
	float pos = _player[_character]->getIsLeft() ? 0.3 : - 0.3;
	float angle = _player[_character]->getIsLeft() * PI;
	float speed = 6.0f;
	bool oldIsLeft = _player[_character]->getIsLeft();

	_player[_character]->setIsLeft(isLeft);
	_player[_character]->setX(_player[_character]->getX() + cosf(angle) * speed);
	
	if (_player[_character]->getOnLand())
	{
		if (_player[_character]->getState() != PUSH)
			_player[_character]->setState(RUN);

		if (oldIsLeft != _player[_character]->getIsLeft())
		{
			_player[_character]->setState(RUN);
			EFFECTMANAGER->play("runDust" + to_string(_player[_character]->getIsLeft()), _player[_character]->getX() + _player[_character]->getPlayerImage()->getFrameWidth() * pos, _player[_character]->getY() + _player[_character]->getPlayerImage()->getFrameHeight() * 0.35);
		}

		if (_player[_character]->getCount() % (_player[_character]->getFrameSpeed() * 2) == 3 && _player[_character]->getState() == RUN)
		{
			EFFECTMANAGER->play("run" + to_string(RND->getFromIntTo(1, 4)), _player[_character]->getX() + _player[_character]->getPlayerImage()->getFrameWidth() * pos, _player[_character]->getY() + _player[_character]->getPlayerImage()->getFrameHeight() * 0.35);
		}
	}
}

void playerManager::playerJumpRise()
{
	if (!_player[_character]->getIsJump() && _player[_character]->getOnLand())
	{
		if (_player[_character]->getIsFaceDown())
		{ 
			_player[_character]->setOnLand(false);
			_player[_character]->setY(_player[_character]->getY() + (_player[_character]->getRect().bottom - _player[_character]->getRect().top) / 5);
		}
		else
		{
			_player[_character]->setIsJump(true);
			_player[_character]->setOnLand(false);
			_player[_character]->setSpeed(16.0f);
			_player[_character]->setAngle(PI_2);
			_player[_character]->setGravity(0);
			
			_character ? SOUNDMANAGER->play("Clu_jump") : SOUNDMANAGER->play("Bart_jump");
			EFFECTMANAGER->play("jumpDust" + to_string(RND->getFromIntTo(1, 3)), _player[_character]->getX(), _player[_character]->getY());
		}
	}
}
//역시 이미지는 사람들이 다 속는다 열심히 하는줄 안다~~
void playerManager::playerJumpFall()
{
	if (!_player[_character]->getIsLedgeGrab())
		_player[_character]->setGravity(_player[_character]->getGravity() + 0.85f);

	if (_player[_character]->getGravity() > 0.85f * 2)
		_player[_character]->setOnLand(false);

	if (!_player[_character]->getOnLand())
	{
		if (-sinf(_player[_character]->getAngle()) * _player[_character]->getSpeed() + _player[_character]->getGravity() <= 0)
		{
			if (_player[_character]->getIsFired())
				_player[_character]->setState(JUMPFIRE_RISE);
			else
				_player[_character]->setState(JUMP_RISE);
		}
		else
		{
			if (_player[_character]->getIsFired())
				_player[_character]->setState(JUMPFIRE_FALL);
			else
				_player[_character]->setState(JUMP_FALL);
		}
	}
	
	_player[_character]->setY(_player[_character]->getY() - sinf(_player[_character]->getAngle()) * _player[_character]->getSpeed() + _player[_character]->getGravity());
}

void playerManager::collisionProcess()
{
	//float x = _player[_character]->getX();
	//float y = _player[_character]->getY();

	//if (COLLISIONMANAGER->pixelCollision(_player[_character]->getRect(), x, y, _player[_character]->getSpeed(), _player[_character]->getGravity(), BOTTOM))
	//{
	//	if (-sinf(_player[_character]->getAngle()) * _player[_character]->getSpeed() + _player[_character]->getGravity() >= 0)
	//	{
	//		_player[_character]->setSpeed(0.0f);
	//		_player[_character]->setGravity(0.0f);
	//		_player[_character]->setAngle(-PI_2);
	//		_player[_character]->setY(y);
	//		_player[_character]->setIsJump(false);
	//		if (!_player[_character]->getOnLand())
	//		{
	//			EFFECTMANAGER->play("landDust", _player[_character]->getX(), _player[_character]->getY() + _player[_character]->getPlayerImage()->getFrameHeight() * 0.35);
	//			SOUNDMANAGER->play("Clu_land" + to_string(RND->getFromIntTo(1, 3)));
	//		}
	//		_player[_character]->setOnLand(true);
	//	}
	//}
	//else if (COLLISIONMANAGER->pixelCollision(_player[_character]->getRect(), x, y, _player[_character]->getSpeed(), _player[_character]->getGravity(), TOP))// == RED)
	//{
	//	_player[_character]->setY(y);
	//	_player[_character]->setAngle(-PI_2);
	//	_player[_character]->setGravity(0.0f);
	//}
	////if (_clu->getOnLand())
	//{
	//	if (COLLISIONMANAGER->pixelCollision(_player[_character]->getRect(), x, y, _player[_character]->getSpeed(), _player[_character]->getGravity(), LEFT) ||
	//		COLLISIONMANAGER->pixelCollision(_player[_character]->getRect(), x, y, _player[_character]->getSpeed(), _player[_character]->getGravity(), RIGHT))
	//	{
	//		_player[_character]->setX(x);
	//		if (!_player[_character]->getIsJump())
	//			_player[_character]->setState(PUSH);
	//	}
	//}

	//if (COLLISIONMANAGER->pixelCollision(_player[_character]->getRect(), x, y, _player[_character]->getSpeed(), _player[_character]->getGravity(), BOTTOM) == BLUE)
	//{
	//	if (-sinf(_player[_character]->getAngle()) * _player[_character]->getSpeed() + _player[_character]->getGravity() >= 0)
	//	{
	//		_player[_character]->setSpeed(0.0f);
	//		_player[_character]->setGravity(0.0f);
	//		_player[_character]->setAngle(-PI_2);
	//		_player[_character]->setY(y);
	//		_player[_character]->setIsJump(false);
	//		if (!_player[_character]->getOnLand())
	//			EFFECTMANAGER->play("landDust", _player[_character]->getX(), _player[_character]->getY() + _player[_character]->getPlayerImage()->getFrameHeight() * 0.35);
	//		_player[_character]->setOnLand(true);
	//	}
	//}

	////여기서 채팅 마아아아아악 치면 시영이가 피식하고 무한반복
	////후우.........

	////else
	//{
	//	//if (COLLISIONMANAGER->pixelCollision(_clu->getRect(), x, y, _clu->getSpeed(), _clu->getGravity(), LEFT) == ORANGE ||
	//	//	COLLISIONMANAGER->pixelCollision(_clu->getRect(), x, y, _clu->getSpeed(), _clu->getGravity(), RIGHT) == ORANGE)
	//	//{
	//	//	if (-sinf(_clu->getAngle()) * _clu->getSpeed() + _clu->getGravity() >= 0)
	//	//	{
	//	//		_clu->setSpeed(0.0f);
	//	//		_clu->setGravity(0.0f);
	//	//		_clu->setAngle(-PI_2);
	//	//		_clu->setX(x);
	//	//		_clu->setOnLand(false);
	//	//		_clu->setIsJump(false);
	//	//		_clu->setIsLedgeGrab(true);
	//	//		_clu->setState(LEDGEGRAB);
	//	//	}
	//	//}
	//	//if (COLLISIONMANAGER->pixelCollision(_clu->getLedgeRc(0), x, y, _clu->getSpeed() / 2, _clu->getGravity(), BOTTOM) == ORANGE ||
	//	//	COLLISIONMANAGER->pixelCollision(_clu->getLedgeRc(1), x, y, _clu->getSpeed() / 2, _clu->getGravity(), BOTTOM) == ORANGE)
	//	//{
	//	//	//if (!_clu->getOnLand())
	//	//	{
	//	//		_clu->setSpeed(0.0f);
	//	//		_clu->setGravity(0.0f);
	//	//		_clu->setAngle(-PI_2);
	//	//		_clu->setOnLand(false);
	//	//		_clu->setIsJump(false);
	//	//		_clu->setIsLedgeGrab(true);
	//	//		//_clu->setState(LEDGEGRAB);
	//	//	}
	//	//}
	//}

}

void playerManager::playerLand()
{
	if (_player[_character]->getState() == JUMP_FALL || _player[_character]->getState() == JUMPFIRE_FALL)
	{
		if (_player[_character]->getIsFired())
			_player[_character]->setState(FULLCHARGE);
		else
			_player[_character]->setState(LAND);
		if (_player[_character]->getIsLeft())
			_player[_character]->setIndex(_player[_character]->getPlayerImage()->getMaxFrameX());
		else
			_player[_character]->setIndex(0);
	}
	else if (_player[_character]->getState() == LAND || _player[_character]->getState() == FULLCHARGE)
	{
		if (_player[_character]->getIsLeft())
		{
			if (_player[_character]->getIndex() <= 0)
			{
				_player[_character]->setIndex(_player[_character]->getPlayerImage()->getMaxFrameX());
				_player[_character]->setCount(0);

				if (_player[_character]->getIsFired())
					_player[_character]->setState(AIM_IDLE);
				else
					_player[_character]->setState(IDLE);
			}
		}
		else
		{
			if (_player[_character]->getIndex() >= _player[_character]->getPlayerImage()->getMaxFrameX())
			{
				_player[_character]->setIndex(0);
				_player[_character]->setCount(0);

				if (_player[_character]->getIsFired())
					_player[_character]->setState(AIM_IDLE);
				else
					_player[_character]->setState(IDLE);
			}
		}
	}
}

void playerManager::playerFaceDown()
{
	RECT rc = _player[_character]->getRect();

	if (_player[_character]->getOnLand())
	{
		if (_player[_character]->getIsFaceDown())
		{
			if (_player[_character]->getState() != LAND)
			{
				_player[_character]->setState(LAND);

				_player[_character]->setCount(0);

				if (_player[_character]->getIsLeft())
					_player[_character]->setIndex(_player[_character]->getPlayerImage()->getMaxFrameX());
				else
					_player[_character]->setIndex(0);
			}
			else if (_player[_character]->getState() == LAND)
			{
				if (rc.top < _player[_character]->getRect().bottom)// -_player[_character]->getPlayerImage()->getFrameHeight() / 3)
				{
					rc.top++;
					_player[_character]->setRect(rc);
				}

				if (_player[_character]->getIsLeft())
				{
					_player[_character]->setIndex(1);
				}
				else
				{
					_player[_character]->setIndex(_player[_character]->getPlayerImage()->getMaxFrameX() - 1);
				}
			}
		}
		else
		{
			if (_player[_character]->getState() == LAND)
			{
				if (rc.top > _player[_character]->getRect().bottom - _player[_character]->getPlayerImage()->getFrameHeight() / 3 * 2)
				{
					rc.top--;
					_player[_character]->setRect(rc);
				}

				if (_player[_character]->getIsLeft())
				{
					if (_player[_character]->getIndex() <= 0)
					{
						_player[_character]->setIndex(_player[_character]->getPlayerImage()->getMaxFrameX());
						_player[_character]->setState(IDLE);
						rc.top = _player[_character]->getRect().bottom - _player[_character]->getPlayerImage()->getFrameHeight() / 3 * 2;
						_player[_character]->setRect(rc);
					}
				}
				else
				{
					if (_player[_character]->getIndex() >= _player[_character]->getPlayerImage()->getMaxFrameX())
					{
						_player[_character]->setIndex(0);
						_player[_character]->setState(IDLE);
						rc.top = _player[_character]->getRect().bottom - _player[_character]->getPlayerImage()->getFrameHeight() / 3 * 2;
						_player[_character]->setRect(rc);
					}
				}
			}
		}
	}
}

void playerManager::playerBackstep()
{
	float speed = 18.0f;
	float pos = _player[_character]->getIsLeft() ? - 0.2 :  0.2;

	if (_player[_character]->getIsBackstep())
	{

		if (_player[_character]->getState() != BACKSTEP)
		{
			_player[_character]->setState(BACKSTEP);
			
			if (_player[_character]->getIsLeft())
				_player[_character]->setIndex(_player[_character]->getPlayerImage()->getMaxFrameX());
			else
				_player[_character]->setIndex(0);

			_character ? SOUNDMANAGER->play("Clu_dashback") : SOUNDMANAGER->play("Bart_block");
		}
		else if (_player[_character]->getState() == BACKSTEP)
		{
			_player[_character]->setAngle(!_player[_character]->getIsLeft() * PI);
			_player[_character]->setX(_player[_character]->getX() + cosf(_player[_character]->getAngle()) * speed);
	
			if (_player[_character]->getCount() % (_player[_character]->getFrameSpeed() / 3) == 0)
			{
				EFFECTMANAGER->play("run" + to_string(RND->getFromIntTo(1, 4)), _player[_character]->getX() + _player[_character]->getPlayerImage()->getFrameWidth() * pos, _player[_character]->getY() + _player[_character]->getPlayerImage()->getFrameHeight() * 0.35);
			}

			if (_player[_character]->getIsLeft())
			{
				if (_player[_character]->getIndex() <= 0)
				{
					_player[_character]->setIndex(_player[_character]->getPlayerImage()->getMaxFrameX());
					_player[_character]->setState(FULLCHARGE_IDLE);
					_player[_character]->setIsBackstep(false);
					_player[_character]->setIsFired(true);
					EFFECTMANAGER->play("fullCharge_back", _player[_character]->getX(), _player[_character]->getY() + _player[_character]->getPlayerImage()->getFrameHeight() * 0.35);
					EFFECTMANAGER->play("fullCharge_front", _player[_character]->getX(), _player[_character]->getY() + _player[_character]->getPlayerImage()->getFrameHeight() * 0.35);
				}
			}
			else
			{
				if (_player[_character]->getIndex() >= _player[_character]->getPlayerImage()->getMaxFrameX())
				{
					_player[_character]->setIndex(0);
					_player[_character]->setState(FULLCHARGE_IDLE);
					_player[_character]->setIsBackstep(false);
					_player[_character]->setIsFired(true);
					EFFECTMANAGER->play("fullCharge_back", _player[_character]->getX(), _player[_character]->getY() + _player[_character]->getPlayerImage()->getFrameHeight() * 0.35);
					EFFECTMANAGER->play("fullCharge_front", _player[_character]->getX(), _player[_character]->getY() + _player[_character]->getPlayerImage()->getFrameHeight() * 0.35);
				}
			}
		}
	}
}

void playerManager::playerFullCharge()
{
	if (_isStayKey_up)
	{
		_player[_character]->setIsFired(true);

		if (_player[_character]->getState() == LOOKUP || _player[_character]->getState() == AIM_DIAGONAL)
		{
			if (_idleCount < 40)
				_idleCount++;
			else
			{
				_idleCount = 0;
				_player[_character]->setState(AIM_DIAGONAL_FULLCHARGE);

				if (_player[_character]->getIsLeft())
					_player[_character]->setIndex(_player[_character]->getPlayerImage()->getMaxFrameX());
				else
					_player[_character]->setIndex(0);
				EFFECTMANAGER->play("fullCharge_back", _player[_character]->getX(), _player[_character]->getY() + _player[_character]->getPlayerImage()->getFrameHeight() * 0.35);
				EFFECTMANAGER->play("fullCharge_front", _player[_character]->getX(), _player[_character]->getY() + _player[_character]->getPlayerImage()->getFrameHeight() * 0.35);
			}
		}
		else if (_player[_character]->getState() == AIM_DIAGONAL_FULLCHARGE);
		{
			if (_player[_character]->getIsLeft())
			{
				if (_player[_character]->getIndex() <= 0)
				{
					_player[_character]->setState(AIM_DIAGONAL_FULLCHARGE_IDLE);
					_idleCount = 0;
					_player[_character]->setCount(0);
				}
			}
			else
			{
				if (_player[_character]->getIndex() >= _player[_character]->getPlayerImage()->getMaxFrameX())
				{
					_player[_character]->setState(AIM_DIAGONAL_FULLCHARGE_IDLE);
					_idleCount = 0;
					_player[_character]->setCount(0);
				}
			}
		}
	}
	else
	{
		if (_player[_character]->getState() == IDLE || _player[_character]->getState() == AIM_IDLE)
		{
			_player[_character]->setState(CHARGE);

			if (_player[_character]->getIsLeft())
				_player[_character]->setIndex(_player[_character]->getPlayerImage()->getMaxFrameX());
			else
				_player[_character]->setIndex(0);
		}
		else if (_player[_character]->getState() == CHARGE)
		{
			_idleCount++;

			if (_player[_character]->getIsLeft())
			{
				if (_idleCount < 40)
					_player[_character]->setIndex(_player[_character]->getPlayerImage()->getMaxFrameX());
				else
				{
					if (_player[_character]->getIndex() <= 0)
					{
						_idleCount = 0;
						_player[_character]->setIndex(_player[_character]->getPlayerImage()->getMaxFrameX());
						_player[_character]->setState(FULLCHARGE);
						EFFECTMANAGER->play("fullCharge_back", _player[_character]->getX(), _player[_character]->getY() + _player[_character]->getPlayerImage()->getFrameHeight() * 0.35);
						EFFECTMANAGER->play("fullCharge_front", _player[_character]->getX(), _player[_character]->getY() + _player[_character]->getPlayerImage()->getFrameHeight() * 0.35);
					}
				}
			}
			else
			{
				if (_idleCount < 40)
					_player[_character]->setIndex(0);
				else
				{
					if (_player[_character]->getIndex() >= _player[_character]->getPlayerImage()->getMaxFrameX())
					{
						_idleCount = 0;
						_player[_character]->setIndex(0);
						_player[_character]->setState(FULLCHARGE);
						EFFECTMANAGER->play("fullCharge_back", _player[_character]->getX(), _player[_character]->getY() + _player[_character]->getPlayerImage()->getFrameHeight() * 0.35);
						EFFECTMANAGER->play("fullCharge_front", _player[_character]->getX(), _player[_character]->getY() + _player[_character]->getPlayerImage()->getFrameHeight() * 0.35);
					}
				}
			}
		}
		else if (_player[_character]->getState() == FULLCHARGE)
		{
			if (_player[_character]->getIsLeft())
			{
				if (_player[_character]->getIndex() <= 0)
				{
					_player[_character]->setState(FULLCHARGE_IDLE);
					_player[_character]->setIndex(_player[_character]->getPlayerImage()->getMaxFrameX());
					_idleCount = 0;
					_player[_character]->setCount(0);
				}
			}
			else
			{
				if (_player[_character]->getIndex() >= _player[_character]->getPlayerImage()->getMaxFrameX())
				{
					_player[_character]->setState(FULLCHARGE_IDLE);
					_player[_character]->setIndex(0);
					_idleCount = 0;
					_player[_character]->setCount(0);
				}
			}
		}
	}
}

void playerManager::playerLedgeGrab()
{
	if (_player[_character]->getIsLedgeGrab())
	{
		if (_player[_character]->getState() == JUMP_FALL)
		{
			_player[_character]->setState(LEDGEGRAB);
			_player[_character]->setCount(0);
			if (_player[_character]->getIsLeft())
				_player[_character]->setIndex(_player[_character]->getPlayerImage()->getMaxFrameX());
			else
				_player[_character]->setIndex(0);
		}
		else if (_player[_character]->getState() == LEDGEGRAB)
		{
			if (_player[_character]->getIsLeft())
			{
				if (_player[_character]->getIndex() <= 0)
				{
					_player[_character]->setState(LEDGEGRAB_IDLE);
					_player[_character]->setIndex(_player[_character]->getPlayerImage()->getMaxFrameX());
					_player[_character]->setCount(0);
				}
			}
			else
			{
				if (_player[_character]->getIndex() >= _player[_character]->getPlayerImage()->getMaxFrameX())
				{
					_player[_character]->setState(LEDGEGRAB_IDLE);
					_player[_character]->setIndex(0);
					_player[_character]->setCount(0);
				}
			}
		}
	}
	else
	{
		if (_player[_character]->getState() == LEDGEGRAB_IDLE)
		{
			if (_player[_character]->getIsLeft())
			{
				if (_player[_character]->getIndex() <= 0)
				{
					_player[_character]->setState(LEDGEGRAB_RISE);
					_player[_character]->setIndex(_player[_character]->getPlayerImage()->getMaxFrameX());
					_player[_character]->setCount(0);
				}
			}
			else
			{
				if (_player[_character]->getIndex() >= _player[_character]->getPlayerImage()->getMaxFrameX())
				{
					_player[_character]->setState(LEDGEGRAB_RISE);
					_player[_character]->setIndex(0);
					_player[_character]->setCount(0);
				}
			}
		}
		else if (_player[_character]->getState() == LEDGEGRAB_RISE)
		{
			if (_player[_character]->getIsLeft())
			{
				if (_player[_character]->getIndex() <= 0)
				{
					_player[_character]->setState(IDLE);
					_player[_character]->setIndex(_player[_character]->getPlayerImage()->getMaxFrameX());
					_player[_character]->setCount(0);
				}
			}
			else
			{
				if (_player[_character]->getIndex() >= _player[_character]->getPlayerImage()->getMaxFrameX())
				{
					_player[_character]->setState(IDLE);
					_player[_character]->setIndex(0);
					_player[_character]->setCount(0);
				}
			}
		}
	}
}

/*
													이응주
													2 = 0
													3 = 1
													4 = 4
													5 = 6
													6 = 2
													7 = 4
													8 = 0
													9 = 3
													10 = 5
													11 = 1
													12 = 3

*/

void playerManager::fromStateToIdle()
{
	if (_player[_character]->getOnLand())
	{
		if (_isStayKey_up)
		{
			if (_player[_character]->getState() == AIM_DIAGONALFIRE)
			{
				if (_player[_character]->getIsLeft())
				{
					if (_player[_character]->getIndex() <= 0)
					{
						_player[_character]->setState(AIM_DIAGONAL);
						_player[_character]->setCount(0);
						_player[_character]->setIndex(_player[_character]->getPlayerImage()->getMaxFrameX());
					}
				}
				else
				{
					if (_player[_character]->getIndex() >= _player[_character]->getPlayerImage()->getMaxFrameX())
					{
						_player[_character]->setState(AIM_DIAGONAL);
						_player[_character]->setCount(0);
						_player[_character]->setIndex(0);
					}
				}
			}
			else if (_player[_character]->getState() == AIM_DIAGONAL || _player[_character]->getState() == AIM_DIAGONAL_FULLCHARGE_IDLE)
			{
				if (_idleCount < 200)
					_idleCount++;
				else
				{
					_player[_character]->setState(IDLE);
					_player[_character]->setCount(0);
					_player[_character]->setIsFired(false);
					_idleCount = 0;
				}
			}
		}
		else
		{
			this->playerLand();

			if (_player[_character]->getState() == AIM_FIRE)
			{
				if (_player[_character]->getIsLeft())
				{
					if (_player[_character]->getIndex() <= 0)
					{
						_player[_character]->setState(AIM_IDLE);
						_player[_character]->setCount(0);
						_player[_character]->setIndex(_player[_character]->getPlayerImage()->getMaxFrameX());
					}
				}
				else
				{
					if (_player[_character]->getIndex() >= _player[_character]->getPlayerImage()->getMaxFrameX())
					{
						_player[_character]->setState(AIM_IDLE);
						_player[_character]->setCount(0);
						_player[_character]->setIndex(0);
					}
				}
			}
			else if (_player[_character]->getState() == AIM_IDLE || _player[_character]->getState() == FULLCHARGE_IDLE)
			{
				if (_idleCount < 200)
					_idleCount++;
				else
				{
					_player[_character]->setState(IDLE);
					_player[_character]->setCount(0);
					_player[_character]->setIsFired(false);
					_idleCount = 0;
				}
			}
			else if (_player[_character]->getState() == LAUGH)
			{

			}
		}
	}
}

void playerManager::fromIdleToState()
{
	int randNo;

	if (_player[_character]->getState() == IDLE)
	{
		if (_idleCount < _idleMax)
			_idleCount++;
		else
		{
			randNo = RND->getFromIntTo(0, MAXPLAYERSTATE - 1);

			if (randNo == LAUGH)
				_player[_character]->setState(LAUGH);
			else if (randNo == THINK)
				_player[_character]->setState(THINK);
			else if (randNo == BORED)
				_player[_character]->setState(BORED);
			else if (randNo == UPSET)
				_player[_character]->setState(UPSET);
		}
	}
	else
	{
		this->playerLaugh();
		this->playerThink();
		this->playerBored();
		this->playerUpset();
	}
}

void playerManager::playerLaugh()
{
	if (_player[_character]->getState() == LAUGH)
	{
		_idleCount = 0;
		_idleMax = RND->getFromIntTo(100, 500);

		if (_player[_character]->getIsLeft())
		{
			if (_player[_character]->getIndex() <= 0)
			{
				_player[_character]->setState(LAUGH_IDLE);
				_player[_character]->setCount(0);
				_player[_character]->setIndex(_player[_character]->getPlayerImage()->getMaxFrameX());
			}
		}
		else
		{
			if (_player[_character]->getIndex() >= _player[_character]->getPlayerImage()->getMaxFrameX())
			{
				_player[_character]->setState(LAUGH_IDLE);
				_player[_character]->setCount(0);
				_player[_character]->setIndex(0);
			}
		}
	}
	else if (_player[_character]->getState() == LAUGH_IDLE)
	{
		if (_idleCount < _idleMax)
			_idleCount++;
		else
		{
			int randNo = RND->getFromIntTo(0, MAXPLAYERSTATE - 1);

			if (randNo == IDLE)
			{
				_player[_character]->setState(IDLE);
				_idleCount = 0;
			}
			else if (randNo == THINK)
				_player[_character]->setState(THINK);
			else if (randNo == BORED)
				_player[_character]->setState(BORED);
			else if (randNo == UPSET)
				_player[_character]->setState(UPSET);
		}
	}
}

void playerManager::playerThink()
{
	if (_player[_character]->getState() == THINK)
	{
		_idleCount = 0;
		_idleMax = RND->getFromIntTo(100, 500);

		if (_player[_character]->getIsLeft())
		{
			if (_player[_character]->getIndex() <= 0)
			{
				_player[_character]->setState(THINK_IDLE);
				_player[_character]->setCount(0);
				_player[_character]->setIndex(_player[_character]->getPlayerImage()->getMaxFrameX());
			}
		}
		else
		{
			if (_player[_character]->getIndex() >= _player[_character]->getPlayerImage()->getMaxFrameX())
			{
				_player[_character]->setState(THINK_IDLE);
				_player[_character]->setCount(0);
				_player[_character]->setIndex(0);
			}
		}
	}
	else if (_player[_character]->getState() == THINK_IDLE)
	{
		if (_idleCount < _idleMax)
			_idleCount++;
		else
		{
			int randNo = RND->getFromIntTo(0, MAXPLAYERSTATE - 1);

			if (randNo == IDLE)
			{
				_player[_character]->setState(IDLE);
				_idleCount = 0;
			}
			else if (randNo == LAUGH)
				_player[_character]->setState(LAUGH);
			else if (randNo == BORED)
				_player[_character]->setState(BORED);
			else if (randNo == UPSET)
				_player[_character]->setState(UPSET);
		}
	}
}

void playerManager::playerBored()
{
	if (_player[_character]->getState() == BORED)
	{
		_idleCount = 0;
		_idleMax = RND->getFromIntTo(100, 500);

		if (_player[_character]->getIsLeft())
		{
			if (_player[_character]->getIndex() <= 0)
			{
				_player[_character]->setState(BORED_IDLE);
				_player[_character]->setCount(0);
				_player[_character]->setIndex(_player[_character]->getPlayerImage()->getMaxFrameX());
			}
		}
		else
		{
			if (_player[_character]->getIndex() >= _player[_character]->getPlayerImage()->getMaxFrameX())
			{
				_player[_character]->setState(BORED_IDLE);
				_player[_character]->setCount(0);
				_player[_character]->setIndex(0);
			}
		}
	}
	else if (_player[_character]->getState() == BORED_IDLE)
	{
		if (_idleCount < _idleMax)
			_idleCount++;
		else
		{
			int randNo = RND->getFromIntTo(0, MAXPLAYERSTATE - 1);

			if (randNo == IDLE)
			{
				_player[_character]->setState(IDLE);
				_idleCount = 0;
			}
			else if (randNo == LAUGH)
				_player[_character]->setState(LAUGH);
			else if (randNo == THINK)
				_player[_character]->setState(THINK);
			else if (randNo == UPSET)
				_player[_character]->setState(UPSET);
		}
	}
}

void playerManager::playerHit()
{
	if (_player[_character]->getState() == HIT)
	{
		if (_player[_character]->getIsLeft())
		{
			if (_player[_character]->getIndex() <= 0)
			{
				_idleCount = 0;
				_player[_character]->setCount(0);
				_player[_character]->setIndex(_player[_character]->getPlayerImage()->getMaxFrameX());
			}
		}
		else
		{
			if (_player[_character]->getIndex() >= _player[_character]->getPlayerImage()->getMaxFrameX())
			{
				_idleCount = 0;
				_player[_character]->setCount(0);
				_player[_character]->setIndex(0);
			}
		}
	}

	if (!_player[_character]->getIsActive())
	{
		if (_idleCount < 100)
			_idleCount++;
		else
		{
			_player[_character]->setIsActive(true);
			_idleCount = 0;
		}
	}
}

void playerManager::playerUpset()
{
	if (_player[_character]->getState() == UPSET)
	{
		_idleCount = 0;
		_idleMax = RND->getFromIntTo(100, 500);

		if (_player[_character]->getIsLeft())
		{
			if (_player[_character]->getIndex() <= 0)
			{
				_player[_character]->setState(IDLE);
				_player[_character]->setCount(0);
				_player[_character]->setIndex(_player[_character]->getPlayerImage()->getMaxFrameX());
			}
		}
		else
		{
			if (_player[_character]->getIndex() >= _player[_character]->getPlayerImage()->getMaxFrameX())
			{
				_player[_character]->setState(IDLE);
				_player[_character]->setCount(0);
				_player[_character]->setIndex(0);
			}
		}
	}
}

void playerManager::bulletFire()
{
	float x, y, angle, speed, pos;
	x = _player[_character]->getX();
	y = _player[_character]->getY() + 7;
	speed = 20.0f;

	_player[_character]->setIsFired(true);

	if (_player[_character]->getCurrentWeapon())
		SOUNDMANAGER->play("Wep_Clu_rifle" + to_string(RND->getFromIntTo(1, 4)));
	else
		SOUNDMANAGER->play("Wep_Clu_bow_fire" + to_string(RND->getFromIntTo(1, 4)));

	if (_isStayKey_up && _player[_character]->getState() != RUN)	//대각선
	{
		angle = _player[_character]->getIsLeft() ? PI_4 * 3 : PI_4;
		pos = _player[_character]->getIsLeft() ? 0.3f : - 0.3f;

		if (_player[_character]->getState() == AIM_DIAGONAL_FULLCHARGE || _player[_character]->getState() == AIM_DIAGONAL_FULLCHARGE_IDLE)
		{
			_player[_character]->setState(AIM_DIAGONALFIRE);
		
			_player[_character]->setCount(0);

			if (_player[_character]->getIsLeft())
				_player[_character]->setIndex(_player[_character]->getPlayerImage()->getMaxFrameX());
			else
				_player[_character]->setIndex(0);

			if (!_player[_character]->getIsJump())
				EFFECTMANAGER->play("runDust" + to_string(_player[_character]->getIsLeft()), _player[_character]->getX() + _player[_character]->getPlayerImage()->getFrameWidth() * pos, _player[_character]->getY() + _player[_character]->getPlayerImage()->getFrameHeight() * 0.35);

			pos = _player[_character]->getIsLeft() ? -0.7 : 0.7;

			if (_player[_character]->getCurrentWeapon())
			{
				_triArrow->fire(x, y, angle, speed);
				EFFECTMANAGER->play("triArrowFire" + to_string(_player[_character]->getIsLeft() + 2), _player[_character]->getX() + _player[_character]->getPlayerImage()->getFrameWidth() * pos, _player[_character]->getY() - 65);
			}
			else
			{
				_triBullet->fire(x, y, angle, speed);
				EFFECTMANAGER->play("triBulletFire" + to_string(_player[_character]->getIsLeft() + 2), _player[_character]->getX() + _player[_character]->getPlayerImage()->getFrameWidth() * pos, _player[_character]->getY() - 70);
			}

			CAMERAMANAGER->CameraShake();
		}
		else if (_player[_character]->getState() != AIM_DIAGONALFIRE)
		{
			_player[_character]->setState(AIM_DIAGONALFIRE);

			_player[_character]->setCount(0);

			if (_player[_character]->getIsLeft())
				_player[_character]->setIndex(_player[_character]->getPlayerImage()->getMaxFrameX());
			else
				_player[_character]->setIndex(0);

			if (!_player[_character]->getIsJump())
				EFFECTMANAGER->play("runDust" + to_string(_player[_character]->getIsLeft()), _player[_character]->getX() + _player[_character]->getPlayerImage()->getFrameWidth() * pos, _player[_character]->getY() + _player[_character]->getPlayerImage()->getFrameHeight() * 0.35);

			pos = _player[_character]->getIsLeft() ? -0.5f : 0.5f;

			if (_player[_character]->getCurrentWeapon())
			{
				_arrow->fire(x, y, angle, speed);
				EFFECTMANAGER->play("arrowFire" + to_string(_player[_character]->getIsLeft() + 2), _player[_character]->getX() + _player[_character]->getPlayerImage()->getFrameWidth() * pos, _player[_character]->getY() - 45);
			}
			else
			{
				_bullet->fire(x, y, angle, speed);
				EFFECTMANAGER->play("bulletFire" + to_string(_player[_character]->getIsLeft() + 2), _player[_character]->getX() + _player[_character]->getPlayerImage()->getFrameWidth() * pos, _player[_character]->getY() - 50);
			}
		}
	}
	else	//노대각선
	{
		angle = _player[_character]->getIsLeft() * PI;
		pos = _player[_character]->getIsLeft() ? 0.3f : - 0.3f;

		if (_player[_character]->getState() == FULLCHARGE || _player[_character]->getState() == FULLCHARGE_IDLE)
		{
			_player[_character]->setState(AIM_FIRE);

			_player[_character]->setCount(0);

			if (_player[_character]->getIsLeft())
				_player[_character]->setIndex(_player[_character]->getPlayerImage()->getMaxFrameX());
			else
				_player[_character]->setIndex(0);
			
			if (!_player[_character]->getIsJump())
				EFFECTMANAGER->play("runDust" + to_string(_player[_character]->getIsLeft()), _player[_character]->getX() + _player[_character]->getPlayerImage()->getFrameWidth() * pos, _player[_character]->getY() + _player[_character]->getPlayerImage()->getFrameHeight() * 0.35);

			pos = _player[_character]->getIsLeft() ? -0.7f : 0.7f;

			if (_player[_character]->getCurrentWeapon())
			{
				_triArrow->fire(x, y + 5, angle, speed);
				EFFECTMANAGER->play("triArrowFire" + to_string(_player[_character]->getIsLeft()), _player[_character]->getX() + _player[_character]->getPlayerImage()->getFrameWidth() * pos, y + 5);
			}
			else
			{
				_triBullet->fire(x, y, angle, speed);
				EFFECTMANAGER->play("triBulletFire" + to_string(_player[_character]->getIsLeft()), _player[_character]->getX() + _player[_character]->getPlayerImage()->getFrameWidth() * pos, y);
			}
			CAMERAMANAGER->CameraShake();
		}
		else if (_player[_character]->getState() != AIM_FIRE)
		{
			_player[_character]->setState(AIM_FIRE);
			_player[_character]->setCount(0);
			
			if (_player[_character]->getIsLeft())
				_player[_character]->setIndex(_player[_character]->getPlayerImage()->getMaxFrameX());
			else
				_player[_character]->setIndex(0);
				
			if (!_player[_character]->getIsJump())
				EFFECTMANAGER->play("runDust" + to_string(_player[_character]->getIsLeft()), _player[_character]->getX() + _player[_character]->getPlayerImage()->getFrameWidth() * pos, _player[_character]->getY() + _player[_character]->getPlayerImage()->getFrameHeight() * 0.35);

			pos = _player[_character]->getIsLeft() ? -0.7f : 0.7f;

			if (_player[_character]->getCurrentWeapon())
			{
				_arrow->fire(x, y + 5, angle, speed);
				EFFECTMANAGER->play("arrowFire" + to_string(_player[_character]->getIsLeft()), _player[_character]->getX() + _player[_character]->getPlayerImage()->getFrameWidth() * pos, y + 5);
			}
			else
			{
				_bullet->fire(x, y, angle, speed);
				EFFECTMANAGER->play("bulletFire" + to_string(_player[_character]->getIsLeft()), _player[_character]->getX() + _player[_character]->getPlayerImage()->getFrameWidth() * pos, y);
			}
		}
	}
}

void playerManager::hammer()
{
	_player[_character]->setState(AIM_FIRE);
}

void playerManager::playerAttack()
{
	_character ? this->hammer() : this->bulletFire();
}

void playerManager::playerBuild()
{
	if (!_isBuild)
	{
		if (_character == CLU)
		{
			if (_blueFlowerCount > 0)
			{
				_block[CLU]->build(_player[CLU]->getX() - 44 * 0.5f, _player[CLU]->getY() - 44 * 0.33f);
				_isBuild = true;
			}
		}
		else
		{
			if (_mineralCount > 0)
			{
				_block[BART]->build(_player[BART]->getX() - 44 * 0.5f, _player[BART]->getY() - 44 * 0.33f);
				_isBuild = true;
			}
		}
	}
}

void playerManager::playerFollow()
{
	_saveProperties[_saveIndex].state = _player[_character]->getState();
	_saveProperties[_saveIndex].x = _player[_character]->getX();
	_saveProperties[_saveIndex].y = _player[_character]->getY();
	_saveProperties[_saveIndex].index = _player[_character]->getIndex();
	_saveProperties[_saveIndex].count = _player[_character]->getCount();
	_saveProperties[_saveIndex].isLeft = _player[_character]->getIsLeft();

	_saveIndex++;
	if (_saveIndex >= 30)
	{
		_saveIndex = 0;
		_isFollowing = true;
	}
	
	if (_isFollowing)
	{
		if (_saveProperties[_saveCount].state == FAINT || _saveProperties[_saveCount].state == FAINT_IDLE)
			_player[!_character]->setState(IDLE);
		else
			_player[!_character]->setState(_saveProperties[_saveCount].state);

		_player[!_character]->setX(_saveProperties[_saveCount].x);
		_player[!_character]->setY(_saveProperties[_saveCount].y);
		_player[!_character]->setIndex(_saveProperties[_saveCount].index);
		_player[!_character]->setCount(_saveProperties[_saveCount].count);
		_player[!_character]->setIsLeft(_saveProperties[_saveCount].isLeft);

		_saveCount++;
		if (_saveCount >= 30)
			_saveCount = 0;
	}
}

void playerManager::playerFaint()
{
	if (_player[_character]->getCurrentHp() <= 0)
	{
		if (_player[_character]->getState() != FAINT && _player[_character]->getState() != FAINT_IDLE)
		{
			_player[_character]->setIsActive(true);
			_player[_character]->setState(FAINT);
			_player[_character]->setCount(0);

			if (_player[_character]->getIsLeft())
				_player[_character]->setIndex(_player[_character]->getPlayerImage()->getMaxFrameX());
			else
				_player[_character]->setIndex(0);
		}
		else if (_player[_character]->getState() == FAINT)
		{
			if (_player[_character]->getIsLeft())
			{
				if (_player[_character]->getIndex() <= 0)
				{
					_player[_character]->setState(FAINT_IDLE);
					_player[_character]->setCount(0);
					_player[_character]->setIndex(_player[_character]->getPlayerImage()->getMaxFrameX());
				}
			}
			else
			{
				if (_player[_character]->getIndex() >= _player[_character]->getPlayerImage()->getMaxFrameX())
				{
					_player[_character]->setState(FAINT_IDLE);
					_player[_character]->setCount(0);
					_player[_character]->setIndex(0);
				}
			}
		}
	}
}

void playerManager::addBlueFlower()
{
	_blueFlowerCount++;
	if (_blueFlowerCount > _blueFlowerMax)
		_blueFlowerCount = _blueFlowerMax;
}

void playerManager::addMineral()
{
	_mineralCount++;
	if (_mineralCount > _mineralMax)
		_mineralCount = _mineralMax;
}

void playerManager::blockCollision()
{
	RECT rcTemp;
	float playerWidth = _player[_character]->getRect().right - _player[_character]->getRect().left;

	for (int i = 0; i < _block[BART]->getVBlock().size(); i++)
	{
		if (!_block[BART]->getVBlock()[i].fire) continue;

		if (IntersectRect(&rcTemp, &_player[_character]->getRect(), &_block[BART]->getVBlock()[i].rc))
		{
			//if (-sinf(_player[_character]->getAngle()) * _player[_character]->getSpeed() + _player[_character]->getGravity() <= 0 &&
			if (_player[_character]->getRect().bottom >= _block[BART]->getVBlock()[i].rc.top &&
				_player[_character]->getRect().top < _block[BART]->getVBlock()[i].rc.top &&
				_player[_character]->getRect().bottom < _block[BART]->getVBlock()[i].rc.bottom)
			{
				_player[_character]->setY(_block[BART]->getVBlock()[i].rc.top - _player[_character]->getPlayerImage()->getFrameHeight() * 0.5 + 1);
				_player[_character]->setIsJump(false);
				if (!_player[_character]->getOnLand())
				{
					EFFECTMANAGER->play("landDust", _player[_character]->getX(), _player[_character]->getY() + _player[_character]->getPlayerImage()->getFrameHeight() * 0.35);
					_character ? SOUNDMANAGER->play("Clu_land" + to_string(RND->getFromIntTo(1, 3))) : SOUNDMANAGER->play("Bart_land" + to_string(RND->getFromIntTo(1, 3)));
				}
				_player[_character]->setOnLand(true);
				_player[_character]->setGravity(0);
				_player[_character]->setSpeed(0);

				break;
			}

			//if (_player[_character]->getRect().left <= _block[BART]->getVBlock()[i].rc.right &&
			//	_player[_character]->getRect().right >_block[BART]->getVBlock()[i].rc.right &&
			//	_player[_character]->getRect().left > _block[BART]->getVBlock()[i].rc.left &&
			//	_player[_character]->getRect().right < _block[BART]->getVBlock()[i].rc.right &&
			//	_player[_character]->getRect().top <= _block[BART]->getVBlock()[i].rc.bottom &&
			//	_player[_character]->getRect().bottom >= _block[BART]->getVBlock()[i].rc.top &&
			//	_player[_character]->getIsLeft())
			//{
			//	_player[_character]->setX(_block[BART]->getVBlock()[i].rc.right + playerWidth * 0.5f - 1);
			//	if (!_player[_character]->getIsJump())
			//		_player[_character]->setState(PUSH);
			//
			//	break;
			//}
		}
	}
}