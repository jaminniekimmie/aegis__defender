#include "stdafx.h"
#include "playerManager.h"

HRESULT playerManager::init(void)
{
	_player = new player;
	_player->init();
	_bullet = new bullet;
	_bullet->init("bullet_blue", 3, 250);
	_triBullet = new triBullet;
	_triBullet->init("bullet_blue", 3, 250);
	_idleCount = 0;
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

	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _player->getPlayerRc().left > 0)
	{
		this->playerRun(LEFT);
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _player->getPlayerRc().right < TILESIZEX)
	{
		this->playerRun(RIGHT);
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_isStayKey_up = true;
		if (_player->getOnLand())
		{
			if (_player->getState() == AIM_IDLE)
				_player->setState(AIM_DIAGONAL);
			else 
				if (!_player->getIsFired())
					_player->setState(LOOKUP);

		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		if (_player->getOnLand())
		{
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
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT) || KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		_player->setState(IDLE);
	}
	if (KEYMANAGER->isOnceKeyUp(VK_UP))
	{
		_player->setState(IDLE);
		_isStayKey_up = false;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{
		_player->setIsFaceDown(false);
	}

	this->playerBackstep();
	this->playerJumpFall();
	this->collisionProcess();
	this->fromStateToIdle();
	this->fromIdleToState();

	if (_player->getState() != AIM_FIRE && _player->getState() != AIM_IDLE && _player->getState() != CHARGE && _player->getState() != FULLCHARGE && _player->getState() != FULLCHARGE_IDLE && _player->getState() != JUMPFIRE_FALL && _player->getState() != JUMPFIRE_RISE)
		_player->setIsFired(false);
}

void playerManager::render(void)
{
	_bullet->render();
	_triBullet->render();
	_player->render();
	//char str[64];
	//sprintf(str, "%d", rnd);
	//TextOut(getMemDC(), 150, 100, str, strlen(str));
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
		if (_player->getCount() % 10 == 0)
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

void playerManager::playerBackstep()
{
	float speed = 18.0f;
	float pos = _player->getIsLeft() ? 0.8 : 0.2;

	if (_player->getIsBackstep())
	{
		if (_player->getCount() % 2 == 0)
		{
			EFFECTMANAGER->play("run" + to_string(RND->getFromIntTo(1, 4)), _player->getX() + _player->getPlayerImage(_player->getState())->getFrameWidth() * pos, _player->getY() + _player->getPlayerImage(_player->getState())->getFrameHeight() * 0.85);
		}
		if (_player->getState() == IDLE || _player->getState() == FULLCHARGE_IDLE)
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
					_player->setState(AIM_DIAGONAL_FULLCHARGE_IDLE);
			}
			else
			{
				if (_player->getIndex() >= _player->getPlayerImage(_player->getState())->getMaxFrameX())
					_player->setState(AIM_DIAGONAL_FULLCHARGE_IDLE);
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
					_player->setIndex(_player->getPlayerImage(_player->getState())->getMaxFrameX());
					_player->setState(FULLCHARGE_IDLE);
				}
			}
			else
			{
				if (_player->getIndex() >= _player->getPlayerImage(_player->getState())->getMaxFrameX())
				{
					_player->setIndex(0);
					_player->setState(FULLCHARGE_IDLE);
				}
			}
		}
	}
}

void playerManager::playerLaugh()
{
	if (_player->getState() == IDLE)
	{
		if (_idleCount < 500)
			_idleCount++;
		else
		{
			_player->setState(LAUGH);

			if (_player->getIsLeft())
				_player->setIndex(_player->getPlayerImage(_player->getState())->getMaxFrameX());
			else
				_player->setIndex(0);

			_idleCount = 0;
		}
	}
	else if (_player->getState() == LAUGH)
	{
		if (_player->getIsLeft())
		{
			if (_player->getIndex() <= 0)
				_player->setState(LAUGH_IDLE);
		}
		else
		{
			if (_player->getIndex() >= _player->getPlayerImage(_player->getState())->getMaxFrameX())
				_player->setState(LAUGH_IDLE);
		}
	}
	else if (_player->getState() == LAUGH_IDLE)
	{
		if (_idleCount < 300)
			_idleCount++;
		else
		{
			_player->setState(IDLE);
			//_player->setState(THINK);
			_idleCount = 0;
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
	else if (_player->getState() == AIM_IDLE || _player->getState() == FULLCHARGE_IDLE || _player->getState() == AIM_DIAGONAL || _player->getState() == AIM_DIAGONAL_FULLCHARGE_IDLE)
	{
		if (_idleCount < 200)
			_idleCount++;
		else
		{
			_player->setState(IDLE);
			_player->setIsFired(false);
			_idleCount = 0;
		}
	}
	else if (_player->getState() == LAUGH)
	{

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
}

void playerManager::fromIdleToState()
{
	this->playerLaugh();
}

void playerManager::bulletFire()
{
	float x, y, angle, speed, pos;
	x = _player->getX() + _player->getPlayerImage(_player->getState())->getFrameWidth() * 0.5f;
	y = _player->getY() + _player->getPlayerImage(_player->getState())->getFrameHeight() * 0.5f + 10;
	speed = 10.5f;
	_player->setIsFired(true);

	if (_isStayKey_up)	//대각선
	{
		angle = _player->getIsLeft() ? PI_4 * 3 : PI_4;
		pos = _player->getIsLeft() ? 0.7f : 0.3f;

		if (_player->getState() == AIM_DIAGONAL_FULLCHARGE || _player->getState() == AIM_DIAGONAL_FULLCHARGE_IDLE)
		{
			if (_player->getIsLeft())
				_player->setIndex(_player->getPlayerImage(_player->getState())->getMaxFrameX());
			else
				_player->setIndex(0);

			_player->setState(AIM_DIAGONALFIRE);

			if (!_player->getIsJump())
				EFFECTMANAGER->play("runDust" + to_string(_player->getIsLeft()), _player->getX() + _player->getPlayerImage(_player->getState())->getFrameWidth() * pos, _player->getY() + _player->getPlayerImage(_player->getState())->getFrameHeight() * 0.85);

			pos = _player->getIsLeft() ? -30 : _player->getPlayerImage(_player->getState())->getFrameWidth() + 30;
			_triBullet->fire(x, y, angle, speed);
			EFFECTMANAGER->play("triBulletFire" + to_string(_player->getIsLeft() + 2), _player->getX() + pos, _player->getY());
		}
		else
		{

			if (_player->getIsLeft())
				_player->setIndex(_player->getPlayerImage(_player->getState())->getMaxFrameX());
			else
				_player->setIndex(0);

			_player->setState(AIM_DIAGONALFIRE);

			if (!_player->getIsJump())
				EFFECTMANAGER->play("runDust" + to_string(_player->getIsLeft()), _player->getX() + _player->getPlayerImage(_player->getState())->getFrameWidth() * pos, _player->getY() + _player->getPlayerImage(_player->getState())->getFrameHeight() * 0.85);

			pos = _player->getIsLeft() ? -30 : _player->getPlayerImage(_player->getState())->getFrameWidth() + 30;
			_bullet->fire(x, y, angle, speed);
			EFFECTMANAGER->play("bulletFire" + to_string(_player->getIsLeft() + 2), _player->getX() + pos, _player->getY());
		}
	}
	else	//노대각선
	{
		angle = _player->getIsLeft() * PI;
		pos = _player->getIsLeft() ? 0.7f : 0.3f;

		if (_player->getState() == FULLCHARGE || _player->getState() == FULLCHARGE_IDLE)
		{
			if (_player->getIsLeft())
				_player->setIndex(_player->getPlayerImage(_player->getState())->getMaxFrameX());
			else
				_player->setIndex(0);
			
			_player->setState(AIM_FIRE);
			
			if (!_player->getIsJump())
				EFFECTMANAGER->play("runDust" + to_string(_player->getIsLeft()), _player->getX() + _player->getPlayerImage(_player->getState())->getFrameWidth() * pos, _player->getY() + _player->getPlayerImage(_player->getState())->getFrameHeight() * 0.85);

			pos = _player->getIsLeft() ? -30 : _player->getPlayerImage(_player->getState())->getFrameWidth() + 30;
			_triBullet->fire(x, y, angle, speed);
			EFFECTMANAGER->play("triBulletFire" + to_string(_player->getIsLeft()), _player->getX() + pos, y);
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

				if (!_player->getIsJump())
					EFFECTMANAGER->play("runDust" + to_string(_player->getIsLeft()), _player->getX() + _player->getPlayerImage(_player->getState())->getFrameWidth() * pos, _player->getY() + _player->getPlayerImage(_player->getState())->getFrameHeight() * 0.85);
			}

			pos = _player->getIsLeft() ? -30 : _player->getPlayerImage(_player->getState())->getFrameWidth() + 30;
			_bullet->fire(x, y, angle, speed);
			EFFECTMANAGER->play("bulletFire" + to_string(_player->getIsLeft()), _player->getX() + pos, y);
		}
	}
}
