#include "stdafx.h"
#include "playerManager.h"

HRESULT playerManager::init(void)
{
	_playerCharacter = CLU;

	_clu = new player;
	_clu->init(CLU);

	_bart = new player;
	_bart->init(BART);
	
	_bullet = new bullet;
	_bullet->init("bullet_blue", 3, 500);
	
	_triBullet = new triBullet;
	_triBullet->init("bullet_blue", 3, 500);
	
	_idleCount = 0;
	_idleMax = RND->getFromIntTo(100, 500);
	_isStayKey_up = _isStayKey_down = false;

	//if (_playerCharacter)
	//	_clu->getPlayerImage(_clu->getState()).alpha = ;
	
	return S_OK;
}

void playerManager::release(void)
{
	_clu->release();
	SAFE_DELETE(_clu);
	_bart->release();
	SAFE_DELETE(_bart);
	_bullet->release();
	SAFE_DELETE(_bullet);
	_triBullet->release();
	SAFE_DELETE(_triBullet);
}

void playerManager::update(void)
{
	_bullet->update();
	_triBullet->update();

	this->keyInput();
	this->playerBackstep();
	this->playerJumpFall();

	_clu->update();
	_bart->update();
	
	this->collisionProcess();
	this->playerFaceDown();
	this->playerLedgeGrab();
	this->fromStateToIdle();
	this->fromIdleToState();
}

void playerManager::render(void)
{
	_bullet->render();
	_triBullet->render();
	_bart->render();
	_clu->render();
}

void playerManager::keyInput()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))// || KEYMANAGER->isStayKeyDown('A'))
	{
		this->playerRun(LEFT);
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))// || KEYMANAGER->isStayKeyDown('D'))
	{
		this->playerRun(RIGHT);
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))// || KEYMANAGER->isStayKeyDown('W'))
	{
		_isStayKey_up = true;

		if (_clu->getOnLand())
		{
			if (_clu->getState() == AIM_IDLE)
				_clu->setState(AIM_DIAGONAL);
			else if (_clu->getState() != RUN && _clu->getState() != AIM_DIAGONALFIRE && _clu->getState() != AIM_DIAGONAL)
				if (!_clu->getIsFired())
					_clu->setState(LOOKUP);
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))// || KEYMANAGER->isStayKeyDown('S'))
	{
		_isStayKey_down = true;

		if (_clu->getOnLand())
		{
			if (!_clu->getIsFaceDown())
				EFFECTMANAGER->play("landDust", _clu->getX(), _clu->getY() + _clu->getPlayerImage(_clu->getState())->getFrameHeight() * 0.35);
			_clu->setIsFaceDown(true);
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_SPACE))
	{
		_clu->setIsLedgeGrab(false);
		this->playerJumpRise();
	}
	if (KEYMANAGER->isOnceKeyDown('L'))
	{
		if (_clu->getOnLand())
		{
			_clu->setIsBackstep(true);
			_clu->setCount(0);
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
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT) || KEYMANAGER->isOnceKeyUp(VK_RIGHT)) // || KEYMANAGER->isOnceKeyUp('A') || KEYMANAGER->isOnceKeyUp('D'))
	{
		_clu->setState(IDLE);
	}
	if (KEYMANAGER->isOnceKeyUp(VK_UP)) // || KEYMANAGER->isOnceKeyUp('W'))
	{
		_clu->setState(IDLE);
		_isStayKey_up = false;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_DOWN))// || KEYMANAGER->isOnceKeyUp('S'))
	{
		_isStayKey_down = false;
		_clu->setIsFaceDown(false);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_TAB) || KEYMANAGER->isOnceKeyDown(VK_SHIFT))
	{
		_clu->setWeaponSwitch(!_clu->getWeaponSwitch());
		_clu->setWeaponIsActive(_clu->getWeaponSwitch(), true);
	}
}

void playerManager::playerRun(bool isLeft)
{
	float pos = _clu->getIsLeft() ? 0.3 : - 0.3;
	float angle = _clu->getIsLeft() * PI;
	bool oldIsLeft = _clu->getIsLeft();

	_clu->setIsLeft(isLeft);
	_clu->setX(_clu->getX() + cosf(angle) * 7.0f);
	
	if (_clu->getOnLand())
	{
		if (_clu->getState() != PUSH)
			_clu->setState(RUN);

		if (oldIsLeft != _clu->getIsLeft())
		{
			_clu->setState(RUN);
			EFFECTMANAGER->play("runDust" + to_string(_clu->getIsLeft()), _clu->getX() + _clu->getPlayerImage(_clu->getState())->getFrameWidth() * pos, _clu->getY() + _clu->getPlayerImage(_clu->getState())->getFrameHeight() * 0.35);
		}

		if (_clu->getCount() % (_clu->getFrameSpeed() * 2) == 3 && _clu->getState() == RUN)
		{
			EFFECTMANAGER->play("run" + to_string(RND->getFromIntTo(1, 4)), _clu->getX() + _clu->getPlayerImage(_clu->getState())->getFrameWidth() * pos, _clu->getY() + _clu->getPlayerImage(_clu->getState())->getFrameHeight() * 0.35);
		}
	}
}

void playerManager::playerJumpRise()
{
	if (!_clu->getIsJump() && _clu->getOnLand())
	{
		if (_clu->getIsFaceDown())
		{ 
			_clu->setOnLand(false);
			_clu->setY(_clu->getY() + (_clu->getPlayerRc().bottom - _clu->getPlayerRc().top) / 5);
		}
		else
		{
			_clu->setIsJump(true);
			_clu->setOnLand(false);
			_clu->setSpeed(15.0f);
			_clu->setAngle(PI_2);
			_clu->setGravity(0);
			
			SOUNDMANAGER->play("Clu_jump");
			EFFECTMANAGER->play("jumpDust" + to_string(RND->getFromIntTo(1, 3)), _clu->getX(), _clu->getY());
		}
	}
}
//역시 이미지는 사람들이 다 속는다 열심히 하는줄 안다~~
void playerManager::playerJumpFall()
{
	if (!_clu->getIsLedgeGrab())
		_clu->setGravity(_clu->getGravity() + 0.85f);

	if (_clu->getGravity() > 0.85f * 2)
		_clu->setOnLand(false);

	if (!_clu->getOnLand())
	{
		if (-sinf(_clu->getAngle()) * _clu->getSpeed() + _clu->getGravity() <= 0)
		{
			if (_clu->getIsFired())
				_clu->setState(JUMPFIRE_RISE);
			else
				_clu->setState(JUMP_RISE);
		}
		else
		{
			if (_clu->getIsFired())
				_clu->setState(JUMPFIRE_FALL);
			else
				_clu->setState(JUMP_FALL);
		}
	}
	
	_clu->setY(_clu->getY() - sinf(_clu->getAngle()) * _clu->getSpeed() + _clu->getGravity());
}

void playerManager::collisionProcess()
{
	float x = _clu->getX();
	float y = _clu->getY();

	if (COLLISIONMANAGER->pixelCollision(_clu->getPlayerRc(), x, y, _clu->getSpeed(), _clu->getGravity(), BOTTOM))
	{
		if (-sinf(_clu->getAngle()) * _clu->getSpeed() + _clu->getGravity() >= 0)
		{
			_clu->setSpeed(0.0f);
			_clu->setGravity(0.0f);
			_clu->setAngle(-PI_2);
			_clu->setY(y);
			_clu->setIsJump(false);
			if (!_clu->getOnLand())
			{
				EFFECTMANAGER->play("landDust", _clu->getX(), _clu->getY() + _clu->getPlayerImage(_clu->getState())->getFrameHeight() * 0.35);
				SOUNDMANAGER->play("Clu_land" + to_string(RND->getFromIntTo(1, 3)));
			}
			_clu->setOnLand(true);
		}
	}
	else if (COLLISIONMANAGER->pixelCollision(_clu->getPlayerRc(), x, y, _clu->getSpeed(), _clu->getGravity(), TOP))// == RED)
	{
		_clu->setY(y);
		_clu->setAngle(-PI_2);
		_clu->setGravity(0.0f);
	}
	//if (_clu->getOnLand())
	{
		if (COLLISIONMANAGER->pixelCollision(_clu->getPlayerRc(), x, y, _clu->getSpeed(), _clu->getGravity(), LEFT) ||
			COLLISIONMANAGER->pixelCollision(_clu->getPlayerRc(), x, y, _clu->getSpeed(), _clu->getGravity(), RIGHT))
		{
			_clu->setX(x);
			if (!_clu->getIsJump())
				_clu->setState(PUSH);
		}
	}

	if (COLLISIONMANAGER->pixelCollision(_clu->getPlayerRc(), x, y, _clu->getSpeed(), _clu->getGravity(), BOTTOM) == BLUE)
	{
		if (-sinf(_clu->getAngle()) * _clu->getSpeed() + _clu->getGravity() >= 0)
		{
			_clu->setSpeed(0.0f);
			_clu->setGravity(0.0f);
			_clu->setAngle(-PI_2);
			_clu->setY(y);
			_clu->setIsJump(false);
			if (!_clu->getOnLand())
				EFFECTMANAGER->play("landDust", _clu->getX(), _clu->getY() + _clu->getPlayerImage(_clu->getState())->getFrameHeight() * 0.35);
			_clu->setOnLand(true);
		}
	}

	//여기서 채팅 마아아아아악 치면 시영이가 피식하고 무한반복
	//후우.........

	//else
	{
		//if (COLLISIONMANAGER->pixelCollision(_clu->getPlayerRc(), x, y, _clu->getSpeed(), _clu->getGravity(), LEFT) == ORANGE ||
		//	COLLISIONMANAGER->pixelCollision(_clu->getPlayerRc(), x, y, _clu->getSpeed(), _clu->getGravity(), RIGHT) == ORANGE)
		//{
		//	if (-sinf(_clu->getAngle()) * _clu->getSpeed() + _clu->getGravity() >= 0)
		//	{
		//		_clu->setSpeed(0.0f);
		//		_clu->setGravity(0.0f);
		//		_clu->setAngle(-PI_2);
		//		_clu->setX(x);
		//		_clu->setOnLand(false);
		//		_clu->setIsJump(false);
		//		_clu->setIsLedgeGrab(true);
		//		_clu->setState(LEDGEGRAB);
		//	}
		//}
		//if (COLLISIONMANAGER->pixelCollision(_clu->getLedgeRc(0), x, y, _clu->getSpeed() / 2, _clu->getGravity(), BOTTOM) == ORANGE ||
		//	COLLISIONMANAGER->pixelCollision(_clu->getLedgeRc(1), x, y, _clu->getSpeed() / 2, _clu->getGravity(), BOTTOM) == ORANGE)
		//{
		//	//if (!_clu->getOnLand())
		//	{
		//		_clu->setSpeed(0.0f);
		//		_clu->setGravity(0.0f);
		//		_clu->setAngle(-PI_2);
		//		_clu->setOnLand(false);
		//		_clu->setIsJump(false);
		//		_clu->setIsLedgeGrab(true);
		//		//_clu->setState(LEDGEGRAB);
		//	}
		//}
	}

}

void playerManager::playerLand()
{
	if (_clu->getState() == JUMP_FALL || _clu->getState() == JUMPFIRE_FALL)
	{
		if (_clu->getIsFired())
			_clu->setState(FULLCHARGE);
		else
			_clu->setState(LAND);
		if (_clu->getIsLeft())
			_clu->setIndex(_clu->getPlayerImage(_clu->getState())->getMaxFrameX());
		else
			_clu->setIndex(0);
	}
	else if (_clu->getState() == LAND || _clu->getState() == FULLCHARGE)
	{
		if (_clu->getIsLeft())
		{
			if (_clu->getIndex() <= 0)
			{
				_clu->setIndex(_clu->getPlayerImage(_clu->getState())->getMaxFrameX());
				_clu->setCount(0);

				if (_clu->getIsFired())
					_clu->setState(AIM_IDLE);
				else
					_clu->setState(IDLE);
			}
		}
		else
		{
			if (_clu->getIndex() >= _clu->getPlayerImage(_clu->getState())->getMaxFrameX())
			{
				_clu->setIndex(0);
				_clu->setCount(0);

				if (_clu->getIsFired())
					_clu->setState(AIM_IDLE);
				else
					_clu->setState(IDLE);
			}
		}
	}
}

void playerManager::playerFaceDown()
{
	RECT rc = _clu->getPlayerRc();

	if (_clu->getOnLand())
	{
		if (_clu->getIsFaceDown())
		{
			if (_clu->getState() != LAND)
			{
				_clu->setState(LAND);

				_clu->setCount(0);

				if (_clu->getIsLeft())
					_clu->setIndex(_clu->getPlayerImage(_clu->getState())->getMaxFrameX());
				else
					_clu->setIndex(0);
			}
			else if (_clu->getState() == LAND)
			{
				if (rc.top < _clu->getPlayerRc().bottom)// -_player->getPlayerImage(_player->getState())->getFrameHeight() / 3)
				{
					rc.top++;
					_clu->setPlayerRc(rc);
				}

				if (_clu->getIsLeft())
				{
					_clu->setIndex(1);
				}
				else
				{
					_clu->setIndex(_clu->getPlayerImage(_clu->getState())->getMaxFrameX() - 1);
				}
			}
		}
		else
		{
			if (_clu->getState() == LAND)
			{
				if (rc.top > _clu->getPlayerRc().bottom - _clu->getPlayerImage(_clu->getState())->getFrameHeight() / 3 * 2)
				{
					rc.top--;
					_clu->setPlayerRc(rc);
				}

				if (_clu->getIsLeft())
				{
					if (_clu->getIndex() <= 0)
					{
						_clu->setIndex(_clu->getPlayerImage(_clu->getState())->getMaxFrameX());
						_clu->setState(IDLE);
						rc.top = _clu->getPlayerRc().bottom - _clu->getPlayerImage(_clu->getState())->getFrameHeight() / 3 * 2;
						_clu->setPlayerRc(rc);
					}
				}
				else
				{
					if (_clu->getIndex() >= _clu->getPlayerImage(_clu->getState())->getMaxFrameX())
					{
						_clu->setIndex(0);
						_clu->setState(IDLE);
						rc.top = _clu->getPlayerRc().bottom - _clu->getPlayerImage(_clu->getState())->getFrameHeight() / 3 * 2;
						_clu->setPlayerRc(rc);
					}
				}
			}
		}
	}
}

void playerManager::playerBackstep()
{
	float speed = 18.0f;
	float pos = _clu->getIsLeft() ? - 0.2 :  0.2;


	if (_clu->getIsBackstep())
	{

		if (_clu->getState() != BACKSTEP)
		{
			if (_clu->getIsLeft())
				_clu->setIndex(_clu->getPlayerImage(_clu->getState())->getMaxFrameX());
			else
				_clu->setIndex(0);

			_clu->setState(BACKSTEP);

			SOUNDMANAGER->play("Clu_dashback");
		}
		else if (_clu->getState() == BACKSTEP)
		{
			_clu->setAngle(!_clu->getIsLeft() * PI);
			_clu->setX(_clu->getX() + cosf(_clu->getAngle()) * speed);
	
			if (_clu->getCount() % (_clu->getFrameSpeed() / 3) == 0)
			{
				EFFECTMANAGER->play("run" + to_string(RND->getFromIntTo(1, 4)), _clu->getX() + _clu->getPlayerImage(_clu->getState())->getFrameWidth() * pos, _clu->getY() + _clu->getPlayerImage(_clu->getState())->getFrameHeight() * 0.35);
			}

			if (_clu->getIsLeft())
			{
				if (_clu->getIndex() <= 0)
				{
					_clu->setIndex(_clu->getPlayerImage(_clu->getState())->getMaxFrameX());
					_clu->setState(FULLCHARGE_IDLE);
					_clu->setIsBackstep(false);
					_clu->setIsFired(true);
					EFFECTMANAGER->play("fullCharge_back", _clu->getX(), _clu->getY() + _clu->getPlayerImage(_clu->getState())->getFrameHeight() * 0.35);
					EFFECTMANAGER->play("fullCharge_front", _clu->getX(), _clu->getY() + _clu->getPlayerImage(_clu->getState())->getFrameHeight() * 0.35);
				}
			}
			else
			{
				if (_clu->getIndex() >= _clu->getPlayerImage(_clu->getState())->getMaxFrameX())
				{
					_clu->setIndex(0);
					_clu->setState(FULLCHARGE_IDLE);
					_clu->setIsBackstep(false);
					_clu->setIsFired(true);
					EFFECTMANAGER->play("fullCharge_back", _clu->getX(), _clu->getY() + _clu->getPlayerImage(_clu->getState())->getFrameHeight() * 0.35);
					EFFECTMANAGER->play("fullCharge_front", _clu->getX(), _clu->getY() + _clu->getPlayerImage(_clu->getState())->getFrameHeight() * 0.35);
				}
			}
		}
	}
}

void playerManager::playerFullCharge()
{
	if (_isStayKey_up)
	{
		_clu->setIsFired(true);

		if (_clu->getState() == LOOKUP || _clu->getState() == AIM_DIAGONAL)
		{
			if (_idleCount < 40)
				_idleCount++;
			else
			{
				_idleCount = 0;
				_clu->setState(AIM_DIAGONAL_FULLCHARGE);

				if (_clu->getIsLeft())
					_clu->setIndex(_clu->getPlayerImage(_clu->getState())->getMaxFrameX());
				else
					_clu->setIndex(0);
				EFFECTMANAGER->play("fullCharge_back", _clu->getX(), _clu->getY() + _clu->getPlayerImage(_clu->getState())->getFrameHeight() * 0.35);
				EFFECTMANAGER->play("fullCharge_front", _clu->getX(), _clu->getY() + _clu->getPlayerImage(_clu->getState())->getFrameHeight() * 0.35);
			}
		}
		else if (_clu->getState() == AIM_DIAGONAL_FULLCHARGE);
		{
			if (_clu->getIsLeft())
			{
				if (_clu->getIndex() <= 0)
				{
					_clu->setState(AIM_DIAGONAL_FULLCHARGE_IDLE);
					_idleCount = 0;
					_clu->setCount(0);
				}
			}
			else
			{
				if (_clu->getIndex() >= _clu->getPlayerImage(_clu->getState())->getMaxFrameX())
				{
					_clu->setState(AIM_DIAGONAL_FULLCHARGE_IDLE);
					_idleCount = 0;
					_clu->setCount(0);
				}
			}
		}
	}
	else
	{
		if (_clu->getState() == IDLE || _clu->getState() == AIM_IDLE)
		{
			_clu->setState(CHARGE);

			if (_clu->getIsLeft())
				_clu->setIndex(_clu->getPlayerImage(_clu->getState())->getMaxFrameX());
			else
				_clu->setIndex(0);
		}
		else if (_clu->getState() == CHARGE)
		{
			_idleCount++;

			if (_clu->getIsLeft())
			{
				if (_idleCount < 40)
					_clu->setIndex(_clu->getPlayerImage(_clu->getState())->getMaxFrameX());
				else
				{
					if (_clu->getIndex() <= 0)
					{
						_idleCount = 0;
						_clu->setIndex(_clu->getPlayerImage(_clu->getState())->getMaxFrameX());
						_clu->setState(FULLCHARGE);
						EFFECTMANAGER->play("fullCharge_back", _clu->getX(), _clu->getY() + _clu->getPlayerImage(_clu->getState())->getFrameHeight() * 0.35);
						EFFECTMANAGER->play("fullCharge_front", _clu->getX(), _clu->getY() + _clu->getPlayerImage(_clu->getState())->getFrameHeight() * 0.35);
					}
				}
			}
			else
			{
				if (_idleCount < 40)
					_clu->setIndex(0);
				else
				{
					if (_clu->getIndex() >= _clu->getPlayerImage(_clu->getState())->getMaxFrameX())
					{
						_idleCount = 0;
						_clu->setIndex(0);
						_clu->setState(FULLCHARGE);
						EFFECTMANAGER->play("fullCharge_back", _clu->getX(), _clu->getY() + _clu->getPlayerImage(_clu->getState())->getFrameHeight() * 0.35);
						EFFECTMANAGER->play("fullCharge_front", _clu->getX(), _clu->getY() + _clu->getPlayerImage(_clu->getState())->getFrameHeight() * 0.35);
					}
				}
			}
		}
		else if (_clu->getState() == FULLCHARGE)
		{
			if (_clu->getIsLeft())
			{
				if (_clu->getIndex() <= 0)
				{
					_clu->setState(FULLCHARGE_IDLE);
					_clu->setIndex(_clu->getPlayerImage(_clu->getState())->getMaxFrameX());
					_idleCount = 0;
					_clu->setCount(0);
				}
			}
			else
			{
				if (_clu->getIndex() >= _clu->getPlayerImage(_clu->getState())->getMaxFrameX())
				{
					_clu->setState(FULLCHARGE_IDLE);
					_clu->setIndex(0);
					_idleCount = 0;
					_clu->setCount(0);
				}
			}
		}
	}
}

void playerManager::playerLedgeGrab()
{
	if (_clu->getIsLedgeGrab())
	{
		if (_clu->getState() == JUMP_FALL)
		{
			_clu->setState(LEDGEGRAB);
			_clu->setCount(0);
			if (_clu->getIsLeft())
				_clu->setIndex(_clu->getPlayerImage(_clu->getState())->getMaxFrameX());
			else
				_clu->setIndex(0);
		}
		else if (_clu->getState() == LEDGEGRAB)
		{
			if (_clu->getIsLeft())
			{
				if (_clu->getIndex() <= 0)
				{
					_clu->setState(LEDGEGRAB_IDLE);
					_clu->setIndex(_clu->getPlayerImage(_clu->getState())->getMaxFrameX());
					_clu->setCount(0);
				}
			}
			else
			{
				if (_clu->getIndex() >= _clu->getPlayerImage(_clu->getState())->getMaxFrameX())
				{
					_clu->setState(LEDGEGRAB_IDLE);
					_clu->setIndex(0);
					_clu->setCount(0);
				}
			}
		}
	}
	else
	{
		if (_clu->getState() == LEDGEGRAB_IDLE)
		{
			if (_clu->getIsLeft())
			{
				if (_clu->getIndex() <= 0)
				{
					_clu->setState(LEDGEGRAB_RISE);
					_clu->setIndex(_clu->getPlayerImage(_clu->getState())->getMaxFrameX());
					_clu->setCount(0);
				}
			}
			else
			{
				if (_clu->getIndex() >= _clu->getPlayerImage(_clu->getState())->getMaxFrameX())
				{
					_clu->setState(LEDGEGRAB_RISE);
					_clu->setIndex(0);
					_clu->setCount(0);
				}
			}
		}
		else if (_clu->getState() == LEDGEGRAB_RISE)
		{
			if (_clu->getIsLeft())
			{
				if (_clu->getIndex() <= 0)
				{
					_clu->setState(IDLE);
					_clu->setIndex(_clu->getPlayerImage(_clu->getState())->getMaxFrameX());
					_clu->setCount(0);
				}
			}
			else
			{
				if (_clu->getIndex() >= _clu->getPlayerImage(_clu->getState())->getMaxFrameX())
				{
					_clu->setState(IDLE);
					_clu->setIndex(0);
					_clu->setCount(0);
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
	if (_clu->getOnLand())
	{
		if (_isStayKey_up)
		{
			if (_clu->getState() == AIM_DIAGONALFIRE)
			{
				if (_clu->getIsLeft())
				{
					if (_clu->getIndex() <= 0)
					{
						_clu->setState(AIM_DIAGONAL);
						_clu->setCount(0);
						_clu->setIndex(_clu->getPlayerImage(_clu->getState())->getMaxFrameX());
					}
				}
				else
				{
					if (_clu->getIndex() >= _clu->getPlayerImage(_clu->getState())->getMaxFrameX())
					{
						_clu->setState(AIM_DIAGONAL);
						_clu->setCount(0);
						_clu->setIndex(0);
					}
				}
			}
			else if (_clu->getState() == AIM_DIAGONAL || _clu->getState() == AIM_DIAGONAL_FULLCHARGE_IDLE)
			{
				if (_idleCount < 200)
					_idleCount++;
				else
				{
					_clu->setState(IDLE);
					_clu->setCount(0);
					_clu->setIsFired(false);
					_idleCount = 0;
				}
			}
		}
		else
		{
			this->playerLand();

			if (_clu->getState() == AIM_FIRE)
			{
				if (_clu->getIsLeft())
				{
					if (_clu->getIndex() <= 0)
					{
						_clu->setState(AIM_IDLE);
						_clu->setCount(0);
						_clu->setIndex(_clu->getPlayerImage(_clu->getState())->getMaxFrameX());
					}
				}
				else
				{
					if (_clu->getIndex() >= _clu->getPlayerImage(_clu->getState())->getMaxFrameX())
					{
						_clu->setState(AIM_IDLE);
						_clu->setCount(0);
						_clu->setIndex(0);
					}
				}
			}
			else if (_clu->getState() == AIM_IDLE || _clu->getState() == FULLCHARGE_IDLE)
			{
				if (_idleCount < 200)
					_idleCount++;
				else
				{
					_clu->setState(IDLE);
					_clu->setCount(0);
					_clu->setIsFired(false);
					_idleCount = 0;
				}
			}
			else if (_clu->getState() == LAUGH)
			{

			}
		}
	}
}

void playerManager::fromIdleToState()
{
	int randNo;

	if (_clu->getState() == IDLE)
	{
		if (_idleCount < _idleMax)
			_idleCount++;
		else
		{
			randNo = RND->getFromIntTo(0, MAXPLAYERSTATE - 1);

			if (randNo == LAUGH)
				_clu->setState(LAUGH);
			else if (randNo == THINK)
				_clu->setState(THINK);
			else if (randNo == BORED)
				_clu->setState(BORED);
			else if (randNo == UPSET)
				_clu->setState(UPSET);
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
	if (_clu->getState() == LAUGH)
	{
		_idleCount = 0;
		_idleMax = RND->getFromIntTo(100, 500);

		if (_clu->getIsLeft())
		{
			if (_clu->getIndex() <= 0)
			{
				_clu->setState(LAUGH_IDLE);
				_clu->setCount(0);
				_clu->setIndex(_clu->getPlayerImage(_clu->getState())->getMaxFrameX());
			}
		}
		else
		{
			if (_clu->getIndex() >= _clu->getPlayerImage(_clu->getState())->getMaxFrameX())
			{
				_clu->setState(LAUGH_IDLE);
				_clu->setCount(0);
				_clu->setIndex(0);
			}
		}
	}
	else if (_clu->getState() == LAUGH_IDLE)
	{
		if (_idleCount < _idleMax)
			_idleCount++;
		else
		{
			int randNo = RND->getFromIntTo(0, MAXPLAYERSTATE - 1);

			if (randNo == IDLE)
			{
				_clu->setState(IDLE);
				_idleCount = 0;
			}
			else if (randNo == THINK)
				_clu->setState(THINK);
			else if (randNo == BORED)
				_clu->setState(BORED);
			else if (randNo == UPSET)
				_clu->setState(UPSET);
		}
	}
}

void playerManager::playerThink()
{
	if (_clu->getState() == THINK)
	{
		_idleCount = 0;
		_idleMax = RND->getFromIntTo(100, 500);

		if (_clu->getIsLeft())
		{
			if (_clu->getIndex() <= 0)
			{
				_clu->setState(THINK_IDLE);
				_clu->setCount(0);
				_clu->setIndex(_clu->getPlayerImage(_clu->getState())->getMaxFrameX());
			}
		}
		else
		{
			if (_clu->getIndex() >= _clu->getPlayerImage(_clu->getState())->getMaxFrameX())
			{
				_clu->setState(THINK_IDLE);
				_clu->setCount(0);
				_clu->setIndex(0);
			}
		}
	}
	else if (_clu->getState() == THINK_IDLE)
	{
		if (_idleCount < _idleMax)
			_idleCount++;
		else
		{
			int randNo = RND->getFromIntTo(0, MAXPLAYERSTATE - 1);

			if (randNo == IDLE)
			{
				_clu->setState(IDLE);
				_idleCount = 0;
			}
			else if (randNo == LAUGH)
				_clu->setState(LAUGH);
			else if (randNo == BORED)
				_clu->setState(BORED);
			else if (randNo == UPSET)
				_clu->setState(UPSET);
		}
	}
}

void playerManager::playerBored()
{
	if (_clu->getState() == BORED)
	{
		_idleCount = 0;
		_idleMax = RND->getFromIntTo(100, 500);

		if (_clu->getIsLeft())
		{
			if (_clu->getIndex() <= 0)
			{
				_clu->setState(BORED_IDLE);
				_clu->setCount(0);
				_clu->setIndex(_clu->getPlayerImage(_clu->getState())->getMaxFrameX());
			}
		}
		else
		{
			if (_clu->getIndex() >= _clu->getPlayerImage(_clu->getState())->getMaxFrameX())
			{
				_clu->setState(BORED_IDLE);
				_clu->setCount(0);
				_clu->setIndex(0);
			}
		}
	}
	else if (_clu->getState() == BORED_IDLE)
	{
		if (_idleCount < _idleMax)
			_idleCount++;
		else
		{
			int randNo = RND->getFromIntTo(0, MAXPLAYERSTATE - 1);

			if (randNo == IDLE)
			{
				_clu->setState(IDLE);
				_idleCount = 0;
			}
			else if (randNo == LAUGH)
				_clu->setState(LAUGH);
			else if (randNo == THINK)
				_clu->setState(THINK);
			else if (randNo == UPSET)
				_clu->setState(UPSET);
		}
	}
}

void playerManager::playerUpset()
{
	if (_clu->getState() == UPSET)
	{
		_idleCount = 0;
		_idleMax = RND->getFromIntTo(100, 500);

		if (_clu->getIsLeft())
		{
			if (_clu->getIndex() <= 0)
			{
				_clu->setState(IDLE);
				_clu->setCount(0);
				_clu->setIndex(_clu->getPlayerImage(_clu->getState())->getMaxFrameX());
			}
		}
		else
		{
			if (_clu->getIndex() >= _clu->getPlayerImage(_clu->getState())->getMaxFrameX())
			{
				_clu->setState(IDLE);
				_clu->setCount(0);
				_clu->setIndex(0);
			}
		}
	}
}

void playerManager::bulletFire()
{
	float x, y, angle, speed, pos;
	x = _clu->getX();
	y = _clu->getY() + 7;
	speed = 20.0f;

	_clu->setIsFired(true);
	SOUNDMANAGER->play("Wep_Clu_rifle" + to_string(RND->getFromIntTo(1, 4)));
	if (_isStayKey_up && _clu->getState() != RUN)	//대각선
	{
		angle = _clu->getIsLeft() ? PI_4 * 3 : PI_4;
		pos = _clu->getIsLeft() ? 0.3f : - 0.3f;

		if (_clu->getState() == AIM_DIAGONAL_FULLCHARGE || _clu->getState() == AIM_DIAGONAL_FULLCHARGE_IDLE)
		{
			_clu->setState(AIM_DIAGONALFIRE);
		
			_clu->setCount(0);

			if (_clu->getIsLeft())
				_clu->setIndex(_clu->getPlayerImage(_clu->getState())->getMaxFrameX());
			else
				_clu->setIndex(0);

			if (!_clu->getIsJump())
				EFFECTMANAGER->play("runDust" + to_string(_clu->getIsLeft()), _clu->getX() + _clu->getPlayerImage(_clu->getState())->getFrameWidth() * pos, _clu->getY() + _clu->getPlayerImage(_clu->getState())->getFrameHeight() * 0.35);

			pos = _clu->getIsLeft() ? - 0.7 : 0.7;
			_triBullet->fire(x, y, angle, speed);
			EFFECTMANAGER->play("triBulletFire" + to_string(_clu->getIsLeft() + 2), _clu->getX() + _clu->getPlayerImage(_clu->getState())->getFrameWidth() * pos, _clu->getY() - 70);
			CAMERAMANAGER->CameraShake();
		}
		else if (_clu->getState() != AIM_DIAGONALFIRE)
		{
			_clu->setState(AIM_DIAGONALFIRE);

			_clu->setCount(0);

			if (_clu->getIsLeft())
				_clu->setIndex(_clu->getPlayerImage(_clu->getState())->getMaxFrameX());
			else
				_clu->setIndex(0);

			if (!_clu->getIsJump())
				EFFECTMANAGER->play("runDust" + to_string(_clu->getIsLeft()), _clu->getX() + _clu->getPlayerImage(_clu->getState())->getFrameWidth() * pos, _clu->getY() + _clu->getPlayerImage(_clu->getState())->getFrameHeight() * 0.35);

			pos = _clu->getIsLeft() ? - 0.5f : 0.5f;
			_bullet->fire(x, y, angle, speed);
			EFFECTMANAGER->play("bulletFire" + to_string(_clu->getIsLeft() + 2), _clu->getX() + _clu->getPlayerImage(_clu->getState())->getFrameWidth() * pos, _clu->getY() - 50);
		}
	}
	else	//노대각선
	{
		angle = _clu->getIsLeft() * PI;
		pos = _clu->getIsLeft() ? 0.3f : - 0.3f;

		if (_clu->getState() == FULLCHARGE || _clu->getState() == FULLCHARGE_IDLE)
		{
			_clu->setState(AIM_FIRE);

			_clu->setCount(0);

			if (_clu->getIsLeft())
				_clu->setIndex(_clu->getPlayerImage(_clu->getState())->getMaxFrameX());
			else
				_clu->setIndex(0);
			
			if (!_clu->getIsJump())
				EFFECTMANAGER->play("runDust" + to_string(_clu->getIsLeft()), _clu->getX() + _clu->getPlayerImage(_clu->getState())->getFrameWidth() * pos, _clu->getY() + _clu->getPlayerImage(_clu->getState())->getFrameHeight() * 0.35);

			pos = _clu->getIsLeft() ? - 0.7f : 0.7f;
			_triBullet->fire(x, y, angle, speed);
			EFFECTMANAGER->play("triBulletFire" + to_string(_clu->getIsLeft()), _clu->getX() + _clu->getPlayerImage(_clu->getState())->getFrameWidth() * pos, y);
			CAMERAMANAGER->CameraShake();
		}
		else if (_clu->getState() != AIM_FIRE)
		{
			_clu->setState(AIM_FIRE);
			_clu->setCount(0);
			
			if (_clu->getIsLeft())
				_clu->setIndex(_clu->getPlayerImage(_clu->getState())->getMaxFrameX());
			else
				_clu->setIndex(0);
				

			if (!_clu->getIsJump())
				EFFECTMANAGER->play("runDust" + to_string(_clu->getIsLeft()), _clu->getX() + _clu->getPlayerImage(_clu->getState())->getFrameWidth() * pos, _clu->getY() + _clu->getPlayerImage(_clu->getState())->getFrameHeight() * 0.35);

			pos = _clu->getIsLeft() ? - 0.7f : 0.7f;
			_bullet->fire(x, y, angle, speed);
			EFFECTMANAGER->play("bulletFire" + to_string(_clu->getIsLeft()), _clu->getX() + _clu->getPlayerImage(_clu->getState())->getFrameWidth() * pos, y);
		}
	}
}

void playerManager::objectCollision()
{
}
