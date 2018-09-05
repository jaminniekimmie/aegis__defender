#include "stdafx.h"
#include "playerManager.h"

HRESULT playerManager::init(void)
{
	_player = new player;
	_player->init();
	_bullet = new bullet;
	_bullet->init("bullet_blue", 3, 250);
	_count = 0;
	return S_OK;
}

void playerManager::release(void)
{
	_player->release();
	SAFE_DELETE(_player);
	_bullet->release();
	SAFE_DELETE(_bullet);
}

void playerManager::update(void)
{
	_player->update();
	_bullet->update();

	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _player->getPlayerRc().left > 0)
	{
		if (!_player->getIsLeft())
			EFFECTMANAGER->play("runDust" + to_string(!_player->getIsLeft()), _player->getX() + _player->getPlayerImage(_player->getState())->getFrameWidth() * 0.5, _player->getY() + _player->getPlayerImage(_player->getState())->getFrameHeight() * 0.85);
		_player->setIsLeft(LEFT);
		this->playerRun();
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _player->getPlayerRc().right < TILESIZEX)
	{
		if (_player->getIsLeft())
			EFFECTMANAGER->play("runDust" + to_string(!_player->getIsLeft()), _player->getX() + _player->getPlayerImage(_player->getState())->getFrameWidth() * 0.5, _player->getY() + _player->getPlayerImage(_player->getState())->getFrameHeight() * 0.85);
		_player->setIsLeft(RIGHT);
		this->playerRun();
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		if (_player->getState() == IDLE)
		{
			_player->setState(LOOKUP);
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		if (_player->getState() == IDLE)
		{
			_player->setIsFaceDown(true);
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		if (!_player->getIsJump() && _player->getOnLand())
		{
			_player->setIsJump(true);
			EFFECTMANAGER->play("jumpDust" + to_string(RND->getFromFloatTo(1, 3)), _player->getX() + _player->getPlayerImage(_player->getState())->getFrameWidth() / 2, _player->getY() + _player->getPlayerImage(_player->getState())->getFrameHeight() / 2);
			//EFFECTMANAGER->jumpDust(_player->getX() + _player->getPlayerImage(_player->getState())->getFrameWidth() / 2, _player->getY() + _player->getPlayerImage(_player->getState())->getFrameHeight() / 2);
		}
	}
	if (KEYMANAGER->isOnceKeyDown('L'))
	{
		if (_player->getState() == IDLE)
		{
			_player->setIsBackstep(true);
		}
	}
	if (KEYMANAGER->isOnceKeyDown('J'))
	{
		this->bulletFire();
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT) || KEYMANAGER->isOnceKeyUp(VK_RIGHT) || KEYMANAGER->isOnceKeyUp(VK_UP))
	{
		_player->setState(IDLE);
	}
	if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{
		_player->setIsFaceDown(false);
	}

	this->playerBackstep();
	this->playerJumpFall();
	this->collisionProcess();
	this->fromStateToIdle();
}

void playerManager::render(void)
{
	_bullet->render();
	_player->render();
	//char str[64];
	//sprintf(str, "%d", rnd);
	//TextOut(getMemDC(), 150, 100, str, strlen(str));
}

void playerManager::playerRun()
{
	float pos = _player->getIsLeft() ? 0.8 : 0.2;
	_player->setState(RUN);
	_player->setAngle(_player->getIsLeft() * PI);
	_player->setX(_player->getX() + cosf(_player->getAngle()) * 5.0f);
	if (_player->getCount() % 10 == 0)
	{
		EFFECTMANAGER->play("run" + to_string(RND->getFromIntTo(1, 4)), _player->getX() + _player->getPlayerImage(_player->getState())->getFrameWidth() * pos, _player->getY() + _player->getPlayerImage(_player->getState())->getFrameHeight() * 0.85);
	}
	//EFFECTMANAGER->runDust(_player->getX() + _player->getPlayerImage(_player->getState())->getFrameWidth() / 2, _player->getY() + _player->getPlayerImage(_player->getState())->getFrameHeight());
}

void playerManager::playerJumpFall()
{
	_player->setGravity(_player->getGravity() + 0.55f);

	if (_player->getIsJump())
	{
		_player->setOnLand(false);
		_player->setSpeed(12.0f);
		_player->setAngle(PI_2);
		if (-sinf(_player->getAngle()) * _player->getSpeed() + _player->getGravity() <= 0)
		{
			if (_player->getState() != JUMPFIRE_RISE)
				_player->setState(JUMP_RISE);
		}
		else
		{
			if (_player->getState() == JUMPFIRE_RISE)
				_player->setState(JUMPFIRE_FALL);
			else
				_player->setState(JUMP_FALL);
		}
	}

	_player->setY(_player->getY() - sinf(_player->getAngle()) * _player->getSpeed() + _player->getGravity());
}

void playerManager::playerBackstep()
{
	float speed = _player->getSpeed() * 1.5;

	if (_player->getIsBackstep())
	{
		if (_player->getState() == IDLE)
		{
			if (_player->getIsLeft())
				_player->setIndex(_player->getPlayerImage(_player->getState())->getMaxFrameX());
			else
				_player->setIndex(0);

			_player->setState(BACKSTEP);
		}
		else if (_player->getState() == BACKSTEP)
		{
			_player->setAngle(!_player->getIsLeft() * PI);
			_player->setX(_player->getX() + cosf(_player->getAngle()) * speed);
	
			if (_player->getIsLeft())
			{
				if (_player->getIndex() <= 0)
				{
					_player->setIndex(_player->getPlayerImage(_player->getState())->getMaxFrameX());
					_player->setState(IDLE);
					_player->setIsBackstep(false);
				}
			}
			else
			{
				if (_player->getIndex() >= _player->getPlayerImage(_player->getState())->getMaxFrameX())
				{
					_player->setIndex(0);
					_player->setState(IDLE);
					_player->setIsBackstep(false);
				}
			}
		}

		//if (_player->getIsLeft())
		//{
		//	if (_player->getPlayerImage(_player->getState())->getMaxFrameX())
		//	{
		//		_player->setState(IDLE);
		//		_player->setIsBackstep(false);
		//	}
		//}
		//else
		//{
		//	if (_player->getX() <= _player->getOldX() - speed * 3)
		//	{
		//		_player->setState(IDLE);
		//		_player->setIsBackstep(false);
		//	}
		//}
	}
	else
	{
		_player->setOldX(_player->getX());
		_player->setOldY(_player->getY());
	}
}

void playerManager::collisionProcess()
{
	if (_player->getY() >= TILESIZEY - WINSIZEY / 2)
	{
		_player->setSpeed(0.0f);
		_player->setGravity(0.0f);
		_player->setAngle(-PI_2);
		_player->setY(TILESIZEY - WINSIZEY / 2);
		if (_player->getIsJump())
		{
			EFFECTMANAGER->play("landDust", _player->getX() + _player->getPlayerImage(_player->getState())->getFrameWidth() / 2, _player->getY() + _player->getPlayerImage(_player->getState())->getFrameHeight() * 0.85);
			//EFFECTMANAGER->landDust(_player->getX() + _player->getPlayerImage(_player->getState())->getFrameWidth() / 2, _player->getY() + _player->getPlayerImage(_player->getState())->getFrameHeight());
		}
		_player->setIsJump(false);
		_player->setOnLand(true);
	}
}

void playerManager::fromStateToIdle()
{
	if (_player->getOnLand())
	{
		if (_player->getState() == JUMP_FALL || _player->getState() == JUMPFIRE_FALL || _player->getState() == JUMPFIREDIAGONAL_FALL)
		{
			_player->setState(LAND);
			if (_player->getIsLeft())
				_player->setIndex(_player->getPlayerImage(_player->getState())->getMaxFrameX());
			else
				_player->setIndex(0);
		}
		else if (_player->getState() == LAND)
		{
			if (_player->getIsLeft())
			{
				if (_player->getIndex() <= 0)
				{
					_player->setIndex(_player->getPlayerImage(_player->getState())->getMaxFrameX());
					_player->setState(IDLE);
				}
			}
			else
			{
				if (_player->getIndex() >= _player->getPlayerImage(_player->getState())->getMaxFrameX())
				{
					_player->setIndex(0);
					_player->setState(IDLE);
				}
			}
		}
	}

	if (_player->getIsFaceDown())
	{
		if (_player->getState() == IDLE)
		{
			_player->setState(LAND);
			if (_player->getIsLeft())
				_player->setIndex(_player->getPlayerImage(_player->getState())->getMaxFrameX());
			else
				_player->setIndex(0);
			EFFECTMANAGER->play("landDust", _player->getX() + _player->getPlayerImage(_player->getState())->getFrameWidth() / 2, _player->getY() + _player->getPlayerImage(_player->getState())->getFrameHeight() * 0.85);
		}
		else if (_player->getState() == LAND)
		{
			if (_player->getIsLeft())
			{
				_player->setIndex(2);
			}
			else
			{
				_player->setIndex(_player->getPlayerImage(_player->getState())->getMaxFrameX() - 2);
			}
		}
	}
	else
	{
		if (_player->getState() == LAND)
		{
			if (_player->getIsLeft())
			{
				if (_player->getIndex() <= 0)
				{
					_player->setIndex(_player->getPlayerImage(_player->getState())->getMaxFrameX());
					_player->setState(IDLE);
				}
			}
			else
			{
				if (_player->getIndex() >= _player->getPlayerImage(_player->getState())->getMaxFrameX())
				{
					_player->setIndex(0);
					_player->setState(IDLE);
				}
			}
		}
	}

	if (_player->getState() == AIM_FIRE)
	{
		if (_player->getIsLeft())
		{
			if (_player->getIndex() <= 0)
			{
				_player->setIndex(_player->getPlayerImage(_player->getState())->getMaxFrameX());
				_player->setState(AIM_IDLE);
			}
		}
		else
		{
			if (_player->getIndex() >= _player->getPlayerImage(_player->getState())->getMaxFrameX())
			{
				_player->setIndex(0);
				_player->setState(AIM_IDLE);
			}
		}
	}
}

void playerManager::bulletFire()
{
	float x = _player->getX() + _player->getPlayerImage(_player->getState())->getFrameWidth() * 0.5f;
	float y = _player->getY() + _player->getPlayerImage(_player->getState())->getFrameHeight() * 0.5f + 10;
	float angle = _player->getIsLeft() * PI;
	float speed = 10.5f;
	float pos = _player->getIsLeft() ? 0.7 : 0.3;

	if (_player->getIsJump())
	{
		if (_player->getState() == JUMP_RISE)
			_player->setState(JUMPFIRE_RISE);
		else if (_player->getState() == JUMP_FALL)
			_player->setState(JUMPFIRE_FALL);
	}
	else
	{
		if (_player->getState() != AIM_FIRE)
		{
			if (_player->getIsLeft())
				_player->setIndex(_player->getPlayerImage(_player->getState())->getMaxFrameX());
			else
				_player->setIndex(0);
			_player->setState(AIM_FIRE);
			EFFECTMANAGER->play("runDust" + to_string(_player->getIsLeft()), _player->getX() + _player->getPlayerImage(_player->getState())->getFrameWidth() * pos, _player->getY() + _player->getPlayerImage(_player->getState())->getFrameHeight() * 0.85);
		}
	}
	pos = _player->getIsLeft() ? -30 : _player->getPlayerImage(_player->getState())->getFrameWidth() + 30;
	_bullet->fire(x, y, angle, speed);
	EFFECTMANAGER->play("bulletFire" + to_string(_player->getIsLeft()), _player->getX() + pos, y);
}
