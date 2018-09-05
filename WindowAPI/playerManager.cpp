#include "stdafx.h"
#include "playerManager.h"

HRESULT playerManager::init(void)
{
	_player = new player;
	_player->init();

	return S_OK;
}

void playerManager::release(void)
{
	_player->release();
	SAFE_DELETE(_player);
}

void playerManager::update(void)
{
	_player->update();

	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _player->getPlayerRc().left > 0)
	{
		_player->setIsLeft(LEFT);
		_player->setState(RUN);
		_player->setX(_player->getX() + cosf(PI) * 5.0f);
		EFFECTMANAGER->play("runDust", _player->getX() + _player->getPlayerImage(_player->getState())->getFrameWidth() / 2, _player->getY() + _player->getPlayerImage(_player->getState())->getFrameHeight());
		//EFFECTMANAGER->runDust(_player->getX() + _player->getPlayerImage(_player->getState())->getFrameWidth() / 2, _player->getY() + _player->getPlayerImage(_player->getState())->getFrameHeight());
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _player->getPlayerRc().right < TILESIZEX)
	{
		_player->setIsLeft(RIGHT);
		_player->setState(RUN);
		_player->setX(_player->getX() + cosf(0.0f) * 5.0f);
		EFFECTMANAGER->play("runDust", _player->getX() + _player->getPlayerImage(_player->getState())->getFrameWidth() / 2, _player->getY() + _player->getPlayerImage(_player->getState())->getFrameHeight());
		//EFFECTMANAGER->runDust(_player->getX() + _player->getPlayerImage(_player->getState())->getFrameWidth() / 2, _player->getY() + _player->getPlayerImage(_player->getState())->getFrameHeight());
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		if (!_player->getIsJump() && _player->getOnLand())
		{
			_player->setIsJump(true);
			EFFECTMANAGER->play("jumpDust1", _player->getX() + _player->getPlayerImage(_player->getState())->getFrameWidth() / 2, _player->getY() + _player->getPlayerImage(_player->getState())->getFrameHeight() / 2);
			//EFFECTMANAGER->jumpDust(_player->getX() + _player->getPlayerImage(_player->getState())->getFrameWidth() / 2, _player->getY() + _player->getPlayerImage(_player->getState())->getFrameHeight() / 2);
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		if (_player->getState() == IDLE)
		{
			_player->setState(LOOKUP);
		}
	}
	if (KEYMANAGER->isOnceKeyDown('L'))
	{
		if (_player->getState() == IDLE)
		{
			_player->setIsBackstep(true);
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT) || KEYMANAGER->isOnceKeyUp(VK_RIGHT) || KEYMANAGER->isOnceKeyUp(VK_UP))
	{
		_player->setState(IDLE);
	}

	this->playerBackstep();
	this->playerJumpFall();

	if (_player->getY() >= TILESIZEY - WINSIZEY / 2)
	{
		_player->setSpeed(0.0f);
		_player->setGravity(0.0f);
		_player->setAngle(-PI_2);
		_player->setY(TILESIZEY - WINSIZEY / 2);
		if (_player->getIsJump())
		{
			EFFECTMANAGER->play("landDust", _player->getX() + _player->getPlayerImage(_player->getState())->getFrameWidth() / 2, _player->getY() + _player->getPlayerImage(_player->getState())->getFrameHeight());
			//EFFECTMANAGER->landDust(_player->getX() + _player->getPlayerImage(_player->getState())->getFrameWidth() / 2, _player->getY() + _player->getPlayerImage(_player->getState())->getFrameHeight());
		}
		_player->setIsJump(false);
		_player->setOnLand(true);
	}
	this->fromStateToIdle();
}

void playerManager::render(void)
{
	_player->render();

	char str[64];
	sprintf(str, "%f", _player->getX());
	TextOut(getMemDC(), 100, 100, str, strlen(str));
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
			_player->setState(JUMP_RISE);
		else
			_player->setState(JUMP_FALL);
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
			_player->setAngle(_player->getIsLeft() ? 0.0f : PI);
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
}
