#include "stdafx.h"
#include "playerManager.h"

HRESULT playerManager::init(void)
{
	_player = new player;
	_player->init();
	_bullet = new bullet;
	_bullet->init("bullet_blue", 3, 500);
	_triBullet = new triBullet;
	_triBullet->init("bullet_blue", 3, 500);
	_idleCount = 0;
	_idleMax = RND->getFromIntTo(100, 500);
	_isStayKey_up = false;
	return S_OK;
}

void playerManager::release(void)
{
	_player->release();
	SAFE_DELETE(_player);
	_bullet->release();
	SAFE_DELETE(_bullet);
	_triBullet->release();
	SAFE_DELETE(_triBullet);
}

void playerManager::update(void)
{
	_player->update();
	_bullet->update();
	_triBullet->update();

	this->keyInput();
	this->playerBackstep();
	this->playerJumpFall();
	this->playerFaceDown();
	this->collisionProcess();
	this->fromStateToIdle();
	this->fromIdleToState();

	if (_player->getState() != AIM_FIRE && 
		_player->getState() != AIM_IDLE && 
		_player->getState() != CHARGE && 
		_player->getState() != FULLCHARGE && 
		_player->getState() != FULLCHARGE_IDLE && 
		_player->getState() != JUMPFIRE_FALL && 
		_player->getState() != JUMPFIRE_RISE &&
		_player->getState() != AIM_DIAGONAL &&
		_player->getState() != AIM_DIAGONAL_FULLCHARGE &&
		_player->getState() != AIM_DIAGONAL_FULLCHARGE_IDLE &&
		_player->getState() != AIM_DIAGONALFIRE)
		_player->setIsFired(false);
}

void playerManager::render(void)
{
	_bullet->render();
	_triBullet->render();
	_player->render();
	char str[64];
	sprintf(str, "%d", _player->getIsLeft());
	TextOut(getMemDC(), 150, 100, str, strlen(str));
}

void playerManager::keyInput()
{
	if ((KEYMANAGER->isStayKeyDown(VK_LEFT) || 
		KEYMANAGER->isStayKeyDown('A')))// && _player->getPlayerRc().left > 0)
	{
		this->playerRun(LEFT);
	}
	if ((KEYMANAGER->isStayKeyDown(VK_RIGHT) || 
		KEYMANAGER->isStayKeyDown('D')))// && _player->getPlayerRc().right < TILESIZEX)
	{
		this->playerRun(RIGHT);
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP) 
		|| KEYMANAGER->isStayKeyDown('W'))
	{
		_isStayKey_up = true;

		if (_player->getOnLand())
		{
			if (_player->getState() == AIM_IDLE)
				_player->setState(AIM_DIAGONAL);
			else if (_player->getState() != RUN && _player->getState() != AIM_DIAGONALFIRE && _player->getState() != AIM_DIAGONAL)
				if (!_player->getIsFired())
					_player->setState(LOOKUP);
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) || 
		KEYMANAGER->isStayKeyDown('S'))
	{
		if (_player->getOnLand())
		{
			if (!_player->getIsFaceDown())
				EFFECTMANAGER->play("landDust", _player->getX() + _player->getPlayerImage(_player->getState())->getFrameWidth() / 2, _player->getY() + _player->getPlayerImage(_player->getState())->getFrameHeight() * 0.85);
			_player->setIsFaceDown(true);
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		if (!_player->getIsJump() && _player->getOnLand())
		{
			_player->setIsJump(true);
			EFFECTMANAGER->play("jumpDust" + to_string(RND->getFromIntTo(1, 3)), _player->getX() + _player->getPlayerImage(_player->getState())->getFrameWidth() / 2, _player->getY() + _player->getPlayerImage(_player->getState())->getFrameHeight() / 2);
			//EFFECTMANAGER->jumpDust(_player->getX() + _player->getPlayerImage(_player->getState())->getFrameWidth() / 2, _player->getY() + _player->getPlayerImage(_player->getState())->getFrameHeight() / 2);
		}
	}
	if (KEYMANAGER->isOnceKeyDown('L'))
	{
		if (_player->getOnLand())
		{
			_player->setIsBackstep(true);
			_player->setCount(0);
		}
	}
	if (KEYMANAGER->isStayKeyDown('J'))
	{
		this->playerFullCharge();
	}
	if (KEYMANAGER->isOnceKeyUp('J'))
	{
		this->bulletFire();
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT) || 
		KEYMANAGER->isOnceKeyUp(VK_RIGHT) ||
		KEYMANAGER->isOnceKeyUp('A') || 
		KEYMANAGER->isOnceKeyUp('D'))
	{
		_player->setState(IDLE);
	}
	if (KEYMANAGER->isOnceKeyUp(VK_UP) || 
		KEYMANAGER->isOnceKeyUp('W'))
	{
		_player->setState(IDLE);
		_isStayKey_up = false;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_DOWN) || 
		KEYMANAGER->isOnceKeyUp('S'))
	{
		_player->setIsFaceDown(false);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_TAB) || 
		KEYMANAGER->isOnceKeyDown(VK_SHIFT))
	{
		_player->setWeaponSwitch(!_player->getWeaponSwitch());
		_player->setWeaponIsActive(_player->getWeaponSwitch(), true);
	}
}

void playerManager::playerRun(bool isLeft)
{
	float pos = _player->getIsLeft() ? 0.8 : 0.2;
	bool oldIsLeft = _player->getIsLeft();
	_player->setState(RUN);
	_player->setIsLeft(isLeft);
	_player->setAngle(_player->getIsLeft() * PI);
	_player->setX(_player->getX() + cosf(_player->getAngle()) * 5.0f);
	if (_player->getOnLand())
	{
		if (oldIsLeft != _player->getIsLeft())
			EFFECTMANAGER->play("runDust" + to_string(_player->getIsLeft()), _player->getX() + _player->getPlayerImage(_player->getState())->getFrameWidth() * 0.5, _player->getY() + _player->getPlayerImage(_player->getState())->getFrameHeight() * 0.85);
		if (_player->getCount() % (_player->getFrameSpeed() * 2) == 0)
		{
			EFFECTMANAGER->play("run" + to_string(RND->getFromIntTo(1, 4)), _player->getX() + _player->getPlayerImage(_player->getState())->getFrameWidth() * pos, _player->getY() + _player->getPlayerImage(_player->getState())->getFrameHeight() * 0.85);
		}
	}
}

void playerManager::playerJumpFall()
{
	_player->setGravity(_player->getGravity() + 0.85f);

	if (_player->getIsJump())
	{
		_player->setOnLand(false);
		_player->setSpeed(15.0f);
		_player->setAngle(PI_2);
		if (-sinf(_player->getAngle()) * _player->getSpeed() + _player->getGravity() <= 0)
		{
			if (_player->getIsFired())
				_player->setState(JUMPFIRE_RISE);
			else
				_player->setState(JUMP_RISE);
		}
		else
		{
			if (_player->getIsFired())
				_player->setState(JUMPFIRE_FALL);
			else
				_player->setState(JUMP_FALL);
		}
	}

	_player->setY(_player->getY() - sinf(_player->getAngle()) * _player->getSpeed() + _player->getGravity());
}

void playerManager::playerFaceDown()
{
	RECT rc = _player->getPlayerRc();

	if (_player->getOnLand())
	{
		if (_player->getIsFaceDown())
		{
			if (_player->getState() != LAND)
			{
				_player->setState(LAND);

				_player->setCount(0);

				if (_player->getIsLeft())
					_player->setIndex(_player->getPlayerImage(_player->getState())->getMaxFrameX());
				else
					_player->setIndex(0);
			}
			else if (_player->getState() == LAND)
			{
				if (rc.top < _player->getPlayerRc().bottom)// -_player->getPlayerImage(_player->getState())->getFrameHeight() / 3)
				{
					rc.top++;
					_player->setPlayerRc(rc);
				}

				if (_player->getIsLeft())
				{
					_player->setIndex(1);
				}
				else
				{
					_player->setIndex(_player->getPlayerImage(_player->getState())->getMaxFrameX() - 1);
				}
			}
		}
		else
		{
			if (_player->getState() == LAND)
			{
				if (rc.top > _player->getPlayerRc().bottom - _player->getPlayerImage(_player->getState())->getFrameHeight() / 3 * 2)
				{
					rc.top--;
					_player->setPlayerRc(rc);
				}

				if (_player->getIsLeft())
				{
					if (_player->getIndex() <= 0)
					{
						_player->setIndex(_player->getPlayerImage(_player->getState())->getMaxFrameX());
						_player->setState(IDLE);
						rc.top = _player->getPlayerRc().bottom - _player->getPlayerImage(_player->getState())->getFrameHeight() / 3 * 2;
						_player->setPlayerRc(rc);
					}
				}
				else
				{
					if (_player->getIndex() >= _player->getPlayerImage(_player->getState())->getMaxFrameX())
					{
						_player->setIndex(0);
						_player->setState(IDLE);
						rc.top = _player->getPlayerRc().bottom - _player->getPlayerImage(_player->getState())->getFrameHeight() / 3 * 2;
						_player->setPlayerRc(rc);
					}
				}
			}
		}
	}
}

void playerManager::playerBackstep()
{
	float speed = 18.0f;
	float pos = _player->getIsLeft() ? 0.2 : 0.8;

	if (_player->getIsBackstep())
	{
		if (_player->getState() != BACKSTEP)
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
	
			if (_player->getCount() % (_player->getFrameSpeed() / 3) == 0)
			{
				EFFECTMANAGER->play("run" + to_string(RND->getFromIntTo(1, 4)), _player->getX() + _player->getPlayerImage(_player->getState())->getFrameWidth() * pos, _player->getY() + _player->getPlayerImage(_player->getState())->getFrameHeight() * 0.85);
			}

			if (_player->getIsLeft())
			{
				if (_player->getIndex() <= 0)
				{
					_player->setIndex(_player->getPlayerImage(_player->getState())->getMaxFrameX());
					_player->setState(FULLCHARGE_IDLE);
					_player->setIsBackstep(false);
					EFFECTMANAGER->play("fullCharge_back", _player->getX() + _player->getPlayerImage(_player->getState())->getFrameWidth() / 2, _player->getY() + _player->getPlayerImage(_player->getState())->getFrameHeight() * 0.85);
					EFFECTMANAGER->play("fullCharge_front", _player->getX() + _player->getPlayerImage(_player->getState())->getFrameWidth() / 2, _player->getY() + _player->getPlayerImage(_player->getState())->getFrameHeight() * 0.85);
				}
			}
			else
			{
				if (_player->getIndex() >= _player->getPlayerImage(_player->getState())->getMaxFrameX())
				{
					_player->setIndex(0);
					_player->setState(FULLCHARGE_IDLE);
					_player->setIsBackstep(false);
					EFFECTMANAGER->play("fullCharge_back", _player->getX() + _player->getPlayerImage(_player->getState())->getFrameWidth() / 2, _player->getY() + _player->getPlayerImage(_player->getState())->getFrameHeight() * 0.85);
					EFFECTMANAGER->play("fullCharge_front", _player->getX() + _player->getPlayerImage(_player->getState())->getFrameWidth() / 2, _player->getY() + _player->getPlayerImage(_player->getState())->getFrameHeight() * 0.85);
				}
			}
		}
	}
}

void playerManager::playerFullCharge()
{
	if (_isStayKey_up)
	{
		_player->setIsFired(true);

		if (_player->getState() == LOOKUP || _player->getState() == AIM_DIAGONAL)
		{
			if (_idleCount < 40)
				_idleCount++;
			else
			{
				_idleCount = 0;
				_player->setState(AIM_DIAGONAL_FULLCHARGE);

				if (_player->getIsLeft())
					_player->setIndex(_player->getPlayerImage(_player->getState())->getMaxFrameX());
				else
					_player->setIndex(0);
				EFFECTMANAGER->play("fullCharge_back", _player->getX() + _player->getPlayerImage(_player->getState())->getFrameWidth() / 2, _player->getY() + _player->getPlayerImage(_player->getState())->getFrameHeight() * 0.85);
				EFFECTMANAGER->play("fullCharge_front", _player->getX() + _player->getPlayerImage(_player->getState())->getFrameWidth() / 2, _player->getY() + _player->getPlayerImage(_player->getState())->getFrameHeight() * 0.85);
			}
		}
		else if (_player->getState() == AIM_DIAGONAL_FULLCHARGE);
		{
			if (_player->getIsLeft())
			{
				if (_player->getIndex() <= 0)
				{
					_player->setState(AIM_DIAGONAL_FULLCHARGE_IDLE);
					_player->setCount(0);
				}
			}
			else
			{
				if (_player->getIndex() >= _player->getPlayerImage(_player->getState())->getMaxFrameX())
				{
					_player->setState(AIM_DIAGONAL_FULLCHARGE_IDLE);
					_player->setCount(0);
				}
			}
		}
	}
	else
	{
		if (_player->getState() == IDLE || _player->getState() == AIM_IDLE)
		{
			_player->setState(CHARGE);

			if (_player->getIsLeft())
				_player->setIndex(_player->getPlayerImage(_player->getState())->getMaxFrameX());
			else
				_player->setIndex(0);
		}
		else if (_player->getState() == CHARGE)
		{
			_idleCount++;

			if (_player->getIsLeft())
			{
				if (_idleCount < 40)
					_player->setIndex(_player->getPlayerImage(_player->getState())->getMaxFrameX());
				else
				{
					if (_player->getIndex() <= 0)
					{
						_idleCount = 0;
						_player->setIndex(_player->getPlayerImage(_player->getState())->getMaxFrameX());
						_player->setState(FULLCHARGE);
						EFFECTMANAGER->play("fullCharge_back", _player->getX() + _player->getPlayerImage(_player->getState())->getFrameWidth() / 2, _player->getY() + _player->getPlayerImage(_player->getState())->getFrameHeight() * 0.85);
						EFFECTMANAGER->play("fullCharge_front", _player->getX() + _player->getPlayerImage(_player->getState())->getFrameWidth() / 2, _player->getY() + _player->getPlayerImage(_player->getState())->getFrameHeight() * 0.85);
					}
				}
			}
			else
			{
				if (_idleCount < 40)
					_player->setIndex(0);
				else
				{
					if (_player->getIndex() >= _player->getPlayerImage(_player->getState())->getMaxFrameX())
					{
						_idleCount = 0;
						_player->setIndex(0);
						_player->setState(FULLCHARGE);
						EFFECTMANAGER->play("fullCharge_back", _player->getX() + _player->getPlayerImage(_player->getState())->getFrameWidth() / 2, _player->getY() + _player->getPlayerImage(_player->getState())->getFrameHeight() * 0.85);
						EFFECTMANAGER->play("fullCharge_front", _player->getX() + _player->getPlayerImage(_player->getState())->getFrameWidth() / 2, _player->getY() + _player->getPlayerImage(_player->getState())->getFrameHeight() * 0.85);
					}
				}
			}
		}
		else if (_player->getState() == FULLCHARGE)
		{
			if (_player->getIsLeft())
			{
				if (_player->getIndex() <= 0)
				{
					_player->setState(FULLCHARGE_IDLE);
					_player->setIndex(_player->getPlayerImage(_player->getState())->getMaxFrameX());
					_player->setCount(0);
				}
			}
			else
			{
				if (_player->getIndex() >= _player->getPlayerImage(_player->getState())->getMaxFrameX())
				{
					_player->setState(FULLCHARGE_IDLE);
					_player->setIndex(0);
					_player->setCount(0);
				}
			}
		}
	}
}

void playerManager::playerLaugh()
{
	if (_player->getState() == LAUGH)
	{
		_idleCount = 0;
		_idleMax = RND->getFromIntTo(100, 500);

		if (_player->getIsLeft())
		{
			if (_player->getIndex() <= 0)
			{
				_player->setState(LAUGH_IDLE);
				_player->setCount(0);
				_player->setIndex(_player->getPlayerImage(_player->getState())->getMaxFrameX());
			}
		}
		else
		{
			if (_player->getIndex() >= _player->getPlayerImage(_player->getState())->getMaxFrameX())
			{
				_player->setState(LAUGH_IDLE);
				_player->setCount(0);
				_player->setIndex(0);
			}
		}
	}
	else if (_player->getState() == LAUGH_IDLE)
	{
		if (_idleCount < _idleMax)
			_idleCount++;
		else
		{
			int randNo = RND->getInt(MAXPLAYERSTATE - 1);

			if (randNo == IDLE)
				_player->setState(IDLE);
			else if (randNo == THINK)
				_player->setState(THINK);
			else if (randNo == BORED)
				_player->setState(BORED);
		}
	}
}

void playerManager::playerThink()
{
	if (_player->getState() == THINK)
	{
		_idleCount = 0;
		_idleMax = RND->getFromIntTo(100, 500);

		if (_player->getIsLeft())
		{
			if (_player->getIndex() <= 0)
			{
				_player->setState(THINK_IDLE);
				_player->setCount(0);
				_player->setIndex(_player->getPlayerImage(_player->getState())->getMaxFrameX());
			}
		}
		else
		{
			if (_player->getIndex() >= _player->getPlayerImage(_player->getState())->getMaxFrameX())
			{
				_player->setState(THINK_IDLE);
				_player->setCount(0);
				_player->setIndex(0);
			}
		}
	}
	else if (_player->getState() == THINK_IDLE)
	{
		if (_idleCount < _idleMax)
			_idleCount++;
		else
		{
			int randNo = RND->getInt(MAXPLAYERSTATE - 1);

			if (randNo == IDLE)
				_player->setState(IDLE);
			else if (randNo == THINK)
				_player->setState(LAUGH);
			else if (randNo == BORED)
				_player->setState(BORED);
		}
	}
}

void playerManager::playerBored()
{
	if (_player->getState() == BORED)
	{
		_idleCount = 0;
		_idleMax = RND->getFromIntTo(100, 500);

		if (_player->getIsLeft())
		{
			if (_player->getIndex() <= 0)
			{
				_player->setState(BORED_IDLE);
				_player->setCount(0);
				_player->setIndex(_player->getPlayerImage(_player->getState())->getMaxFrameX());
			}
		}
		else
		{
			if (_player->getIndex() >= _player->getPlayerImage(_player->getState())->getMaxFrameX())
			{
				_player->setState(BORED_IDLE);
				_player->setCount(0);
				_player->setIndex(0);
			}
		}
	}
	else if (_player->getState() == BORED_IDLE)
	{
		if (_idleCount < _idleMax)
			_idleCount++;
		else
		{
			int randNo = RND->getInt(MAXPLAYERSTATE - 1);

			if (randNo == IDLE)
				_player->setState(IDLE);
			else if (randNo == LAUGH)
				_player->setState(LAUGH);
			else if (randNo == THINK)
				_player->setState(THINK);
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

void playerManager::collisionProcess()
{
	if (_player->getY() >= TILESIZEY - WINSIZEY)
	{
		_player->setSpeed(0.0f);
		_player->setGravity(0.0f);
		_player->setAngle(-PI_2);
		_player->setY(TILESIZEY - WINSIZEY);
		if (_player->getIsJump())
		{
			EFFECTMANAGER->play("landDust", _player->getX() + _player->getPlayerImage(_player->getState())->getFrameWidth() / 2, _player->getY() + _player->getPlayerImage(_player->getState())->getFrameHeight() * 0.85);
		}
		_player->setIsJump(false);
		_player->setOnLand(true);
	}
}

void playerManager::fromStateToIdle()
{
	if (_player->getOnLand())
	{
		if (_isStayKey_up)
		{
			if (_player->getState() == AIM_DIAGONALFIRE)
			{
				if (_player->getIsLeft())
				{
					if (_player->getIndex() <= 0)
					{
						_player->setState(AIM_DIAGONAL);
						_player->setCount(0);
						_player->setIndex(_player->getPlayerImage(_player->getState())->getMaxFrameX());
					}
				}
				else
				{
					if (_player->getIndex() >= _player->getPlayerImage(_player->getState())->getMaxFrameX())
					{
						_player->setState(AIM_DIAGONAL);
						_player->setCount(0);
						_player->setIndex(0);
					}
				}
			}
			else if (_player->getState() == AIM_DIAGONAL || _player->getState() == AIM_DIAGONAL_FULLCHARGE_IDLE)
			{
				if (_idleCount < 200)
					_idleCount++;
				else
				{
					_player->setState(IDLE);
					_player->setCount(0);
					_player->setIsFired(false);
					_idleCount = 0;
				}
			}
		}
		else
		{
			if (_player->getState() == JUMP_FALL || _player->getState() == JUMPFIRE_FALL)
			{
				if (_player->getIsFired())
					_player->setState(FULLCHARGE);
				else
					_player->setState(LAND);
				if (_player->getIsLeft())
					_player->setIndex(_player->getPlayerImage(_player->getState())->getMaxFrameX());
				else
					_player->setIndex(0);
			}
			else if (_player->getState() == LAND || _player->getState() == FULLCHARGE)
			{
				if (_player->getIsLeft())
				{
					if (_player->getIndex() <= 0)
					{
						_player->setIndex(_player->getPlayerImage(_player->getState())->getMaxFrameX());
						_player->setCount(0);

						if (_player->getIsFired())
							_player->setState(AIM_IDLE);
						else
							_player->setState(IDLE);
					}
				}
				else
				{
					if (_player->getIndex() >= _player->getPlayerImage(_player->getState())->getMaxFrameX())
					{
						_player->setIndex(0);
						_player->setCount(0);

						if (_player->getIsFired())
							_player->setState(AIM_IDLE);
						else
							_player->setState(IDLE);
					}
				}
			}
			else if (_player->getState() == AIM_FIRE)
			{
				if (_player->getIsLeft())
				{
					if (_player->getIndex() <= 0)
					{
						_player->setState(AIM_IDLE);
						_player->setCount(0);
						_player->setIndex(_player->getPlayerImage(_player->getState())->getMaxFrameX());
					}
				}
				else
				{
					if (_player->getIndex() >= _player->getPlayerImage(_player->getState())->getMaxFrameX())
					{
						_player->setState(AIM_IDLE);
						_player->setCount(0);
						_player->setIndex(0);
					}
				}
			}
			else if (_player->getState() == AIM_IDLE || _player->getState() == FULLCHARGE_IDLE)
			{
				if (_idleCount < 200)
					_idleCount++;
				else
				{
					_player->setState(IDLE);
					_player->setCount(0);
					_player->setIsFired(false);
					_idleCount = 0;
				}
			}
			else if (_player->getState() == LAUGH)
			{

			}
		}
	}
}

void playerManager::fromIdleToState()
{
	int randNo;

	if (_player->getState() == IDLE)
	{
		if (_idleCount < _idleMax)
			_idleCount++;
		else
		{
			randNo = RND->getInt(MAXPLAYERSTATE - 1);

			if (randNo == LAUGH)
				_player->setState(LAUGH);
			else if (randNo == THINK)
				_player->setState(THINK);
			else if (randNo == BORED)
				_player->setState(BORED);
		}
	}
	else
	{
		this->playerLaugh();
		this->playerThink();
		this->playerBored();
	}
}

void playerManager::bulletFire()
{
	float x, y, angle, speed, pos;
	x = _player->getX() + _player->getPlayerImage(_player->getState())->getFrameWidth() * 0.5f;
	y = _player->getY() + _player->getPlayerImage(_player->getState())->getFrameHeight() * 0.5f + 7;
	speed = 20.0f;
	_player->setIsFired(true);

	if (_isStayKey_up && _player->getState() != RUN)	//대각선
	{
		angle = _player->getIsLeft() ? PI_4 * 3 : PI_4;
		pos = _player->getIsLeft() ? 0.7f : 0.3f;

		if (_player->getState() == AIM_DIAGONAL_FULLCHARGE || _player->getState() == AIM_DIAGONAL_FULLCHARGE_IDLE)
		{
			_player->setState(AIM_DIAGONALFIRE);
		
			_player->setCount(0);

			if (_player->getIsLeft())
				_player->setIndex(_player->getPlayerImage(_player->getState())->getMaxFrameX());
			else
				_player->setIndex(0);

			if (!_player->getIsJump())
				EFFECTMANAGER->play("runDust" + to_string(_player->getIsLeft()), _player->getX() + _player->getPlayerImage(_player->getState())->getFrameWidth() * pos, _player->getY() + _player->getPlayerImage(_player->getState())->getFrameHeight() * 0.85);

			pos = _player->getIsLeft() ? -5 : _player->getPlayerImage(_player->getState())->getFrameWidth() + 5;
			_triBullet->fire(x, y, angle, speed);
			EFFECTMANAGER->play("triBulletFire" + to_string(_player->getIsLeft() + 2), _player->getX() + pos, _player->getY() + 8);
			CAMERAMANAGER->CameraShake();
		}
		else if (_player->getState() != AIM_DIAGONALFIRE)
		{
			_player->setState(AIM_DIAGONALFIRE);

			_player->setCount(0);

			if (_player->getIsLeft())
				_player->setIndex(_player->getPlayerImage(_player->getState())->getMaxFrameX());
			else
				_player->setIndex(0);

			if (!_player->getIsJump())
				EFFECTMANAGER->play("runDust" + to_string(_player->getIsLeft()), _player->getX() + _player->getPlayerImage(_player->getState())->getFrameWidth() * pos, _player->getY() + _player->getPlayerImage(_player->getState())->getFrameHeight() * 0.85);

			pos = _player->getIsLeft() ? -5 : _player->getPlayerImage(_player->getState())->getFrameWidth() + 5;
			_bullet->fire(x, y, angle, speed);
			EFFECTMANAGER->play("bulletFire" + to_string(_player->getIsLeft() + 2), _player->getX() + pos, _player->getY() + 8);
		}
	}
	else	//노대각선
	{
		angle = _player->getIsLeft() * PI;
		pos = _player->getIsLeft() ? 0.7f : 0.3f;

		if (_player->getState() == FULLCHARGE || _player->getState() == FULLCHARGE_IDLE)
		{
			_player->setState(AIM_FIRE);

			_player->setCount(0);

			if (_player->getIsLeft())
				_player->setIndex(_player->getPlayerImage(_player->getState())->getMaxFrameX());
			else
				_player->setIndex(0);
			
			if (!_player->getIsJump())
				EFFECTMANAGER->play("runDust" + to_string(_player->getIsLeft()), _player->getX() + _player->getPlayerImage(_player->getState())->getFrameWidth() * pos, _player->getY() + _player->getPlayerImage(_player->getState())->getFrameHeight() * 0.85);

			pos = _player->getIsLeft() ? -25 : _player->getPlayerImage(_player->getState())->getFrameWidth() + 25;
			_triBullet->fire(x, y, angle, speed);
			EFFECTMANAGER->play("triBulletFire" + to_string(_player->getIsLeft()), _player->getX() + pos, y);
			CAMERAMANAGER->CameraShake();
		}
		else if (_player->getState() != AIM_FIRE)
		{
			_player->setState(AIM_FIRE);
			_player->setCount(0);
			
			if (_player->getIsLeft())
				_player->setIndex(_player->getPlayerImage(_player->getState())->getMaxFrameX());
			else
				_player->setIndex(0);
				

			if (!_player->getIsJump())
				EFFECTMANAGER->play("runDust" + to_string(_player->getIsLeft()), _player->getX() + _player->getPlayerImage(_player->getState())->getFrameWidth() * pos, _player->getY() + _player->getPlayerImage(_player->getState())->getFrameHeight() * 0.85);

			pos = _player->getIsLeft() ? -25 : _player->getPlayerImage(_player->getState())->getFrameWidth() + 25;
			_bullet->fire(x, y, angle, speed);
			EFFECTMANAGER->play("bulletFire" + to_string(_player->getIsLeft()), _player->getX() + pos, y);
		}
	}
}
