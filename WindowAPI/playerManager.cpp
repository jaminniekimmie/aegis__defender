#include "stdafx.h"
#include "playerManager.h"

HRESULT playerManager::init(void)
{
	_character = CLU;

	_player[CLU] = new player;
	_player[CLU]->init(CLU);
	_player[BART] = new player;
	_player[BART]->init(BART);

	_bullet = new bullet;
	_bullet->init("bullet_blue", 3, 500);
	
	_triBullet = new triBullet;
	_triBullet->init("bullet_blue", 3, 500);
	
	_idleCount = 0;
	_idleMax = RND->getFromIntTo(100, 500);
	_isStayKey_up = _isStayKey_down = false;

	_player[_character]->setIsActive(true);
	_player[!_character]->setIsActive(false);

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

	return S_OK;
}

void playerManager::release(void)
{
	for (int i = 0; i < 2; i++)
	{
		_player[i]->release();
		SAFE_DELETE(_player[i]);
	}
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
	this->playerBackstep();
	this->playerJumpFall();

	for (int i = 0; i < 2; i++)
	{
		_player[i]->update();
	}
	
	//this->collisionProcess();
	this->playerFaceDown();
	this->playerHit();
	this->playerLedgeGrab();
	this->fromStateToIdle();
	this->fromIdleToState();
	this->playerFollow();
}

void playerManager::render(void)
{
	_bullet->render();
	_triBullet->render(); 

	_player[!_character]->render();
	_player[_character]->render();
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

		if (_player[_character]->getOnLand())
		{
			if (_player[_character]->getState() == AIM_IDLE)
				_player[_character]->setState(AIM_DIAGONAL);
			else if (_player[_character]->getState() != RUN && _player[_character]->getState() != AIM_DIAGONALFIRE && _player[_character]->getState() != AIM_DIAGONAL)
				if (!_player[_character]->getIsFired())
					_player[_character]->setState(LOOKUP);
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))// || KEYMANAGER->isStayKeyDown('S'))
	{
		_isStayKey_down = true;

		if (_player[_character]->getOnLand())
		{
			if (!_player[_character]->getIsFaceDown())
				EFFECTMANAGER->play("landDust", _player[_character]->getX(), _player[_character]->getY() + _player[_character]->getPlayerImage(_player[_character]->getState())->getFrameHeight() * 0.35);
			_player[_character]->setIsFaceDown(true);
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		if (CAMERAMANAGER->getSwitchStart())
		{
			EFFECTMANAGER->play("ellipsePuff2", _player[_character]->getX(), _player[_character]->getY() + _player[_character]->getPlayerImage(_player[_character]->getState())->getFrameHeight() * 0.15f);
			EFFECTMANAGER->play("regen", _player[_character]->getX(), _player[_character]->getY() + _player[_character]->getPlayerImage(_player[_character]->getState())->getFrameHeight() * 0.45f);
			CAMERAMANAGER->setSwitchStart(false);
		}
		else
		{
			_player[_character]->setIsLedgeGrab(false);
			this->playerJumpRise();
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
		_player[_character]->setWeaponSwitch(!_player[_character]->getWeaponSwitch());
		_player[_character]->setWeaponIsActive(_player[_character]->getWeaponSwitch(), true);
	}
	if (KEYMANAGER->isOnceKeyDown('I') || KEYMANAGER->isOnceKeyDown('O'))
	{
		_character = _character ? CLU : BART;
		
		_player[_character]->setIsActive(true);
		_player[!_character]->setIsActive(false);
	}
}

void playerManager::playerRun(bool isLeft)
{
	float pos = _player[_character]->getIsLeft() ? 0.3 : - 0.3;
	float angle = _player[_character]->getIsLeft() * PI;
	bool oldIsLeft = _player[_character]->getIsLeft();

	_player[_character]->setIsLeft(isLeft);
	_player[_character]->setX(_player[_character]->getX() + cosf(angle) * 7.0f);
	
	if (_player[_character]->getOnLand())
	{
		if (_player[_character]->getState() != PUSH)
			_player[_character]->setState(RUN);

		if (oldIsLeft != _player[_character]->getIsLeft())
		{
			_player[_character]->setState(RUN);
			EFFECTMANAGER->play("runDust" + to_string(_player[_character]->getIsLeft()), _player[_character]->getX() + _player[_character]->getPlayerImage(_player[_character]->getState())->getFrameWidth() * pos, _player[_character]->getY() + _player[_character]->getPlayerImage(_player[_character]->getState())->getFrameHeight() * 0.35);
		}

		if (_player[_character]->getCount() % (_player[_character]->getFrameSpeed() * 2) == 3 && _player[_character]->getState() == RUN)
		{
			EFFECTMANAGER->play("run" + to_string(RND->getFromIntTo(1, 4)), _player[_character]->getX() + _player[_character]->getPlayerImage(_player[_character]->getState())->getFrameWidth() * pos, _player[_character]->getY() + _player[_character]->getPlayerImage(_player[_character]->getState())->getFrameHeight() * 0.35);
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
			_player[_character]->setSpeed(15.0f);
			_player[_character]->setAngle(PI_2);
			_player[_character]->setGravity(0);
			
			SOUNDMANAGER->play("Clu_jump");
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
	//			EFFECTMANAGER->play("landDust", _player[_character]->getX(), _player[_character]->getY() + _player[_character]->getPlayerImage(_player[_character]->getState())->getFrameHeight() * 0.35);
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
	//			EFFECTMANAGER->play("landDust", _player[_character]->getX(), _player[_character]->getY() + _player[_character]->getPlayerImage(_player[_character]->getState())->getFrameHeight() * 0.35);
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
			_player[_character]->setIndex(_player[_character]->getPlayerImage(_player[_character]->getState())->getMaxFrameX());
		else
			_player[_character]->setIndex(0);
	}
	else if (_player[_character]->getState() == LAND || _player[_character]->getState() == FULLCHARGE)
	{
		if (_player[_character]->getIsLeft())
		{
			if (_player[_character]->getIndex() <= 0)
			{
				_player[_character]->setIndex(_player[_character]->getPlayerImage(_player[_character]->getState())->getMaxFrameX());
				_player[_character]->setCount(0);

				if (_player[_character]->getIsFired())
					_player[_character]->setState(AIM_IDLE);
				else
					_player[_character]->setState(IDLE);
			}
		}
		else
		{
			if (_player[_character]->getIndex() >= _player[_character]->getPlayerImage(_player[_character]->getState())->getMaxFrameX())
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
					_player[_character]->setIndex(_player[_character]->getPlayerImage(_player[_character]->getState())->getMaxFrameX());
				else
					_player[_character]->setIndex(0);
			}
			else if (_player[_character]->getState() == LAND)
			{
				if (rc.top < _player[_character]->getRect().bottom)// -_player[_character]->getPlayerImage(_player[_character]->getState())->getFrameHeight() / 3)
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
					_player[_character]->setIndex(_player[_character]->getPlayerImage(_player[_character]->getState())->getMaxFrameX() - 1);
				}
			}
		}
		else
		{
			if (_player[_character]->getState() == LAND)
			{
				if (rc.top > _player[_character]->getRect().bottom - _player[_character]->getPlayerImage(_player[_character]->getState())->getFrameHeight() / 3 * 2)
				{
					rc.top--;
					_player[_character]->setRect(rc);
				}

				if (_player[_character]->getIsLeft())
				{
					if (_player[_character]->getIndex() <= 0)
					{
						_player[_character]->setIndex(_player[_character]->getPlayerImage(_player[_character]->getState())->getMaxFrameX());
						_player[_character]->setState(IDLE);
						rc.top = _player[_character]->getRect().bottom - _player[_character]->getPlayerImage(_player[_character]->getState())->getFrameHeight() / 3 * 2;
						_player[_character]->setRect(rc);
					}
				}
				else
				{
					if (_player[_character]->getIndex() >= _player[_character]->getPlayerImage(_player[_character]->getState())->getMaxFrameX())
					{
						_player[_character]->setIndex(0);
						_player[_character]->setState(IDLE);
						rc.top = _player[_character]->getRect().bottom - _player[_character]->getPlayerImage(_player[_character]->getState())->getFrameHeight() / 3 * 2;
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
				_player[_character]->setIndex(_player[_character]->getPlayerImage(_player[_character]->getState())->getMaxFrameX());
			else
				_player[_character]->setIndex(0);

			SOUNDMANAGER->play("Clu_dashback");
		}
		else if (_player[_character]->getState() == BACKSTEP)
		{
			_player[_character]->setAngle(!_player[_character]->getIsLeft() * PI);
			_player[_character]->setX(_player[_character]->getX() + cosf(_player[_character]->getAngle()) * speed);
	
			if (_player[_character]->getCount() % (_player[_character]->getFrameSpeed() / 3) == 0)
			{
				EFFECTMANAGER->play("run" + to_string(RND->getFromIntTo(1, 4)), _player[_character]->getX() + _player[_character]->getPlayerImage(_player[_character]->getState())->getFrameWidth() * pos, _player[_character]->getY() + _player[_character]->getPlayerImage(_player[_character]->getState())->getFrameHeight() * 0.35);
			}

			if (_player[_character]->getIsLeft())
			{
				if (_player[_character]->getIndex() <= 0)
				{
					_player[_character]->setIndex(_player[_character]->getPlayerImage(_player[_character]->getState())->getMaxFrameX());
					_player[_character]->setState(FULLCHARGE_IDLE);
					_player[_character]->setIsBackstep(false);
					_player[_character]->setIsFired(true);
					EFFECTMANAGER->play("fullCharge_back", _player[_character]->getX(), _player[_character]->getY() + _player[_character]->getPlayerImage(_player[_character]->getState())->getFrameHeight() * 0.35);
					EFFECTMANAGER->play("fullCharge_front", _player[_character]->getX(), _player[_character]->getY() + _player[_character]->getPlayerImage(_player[_character]->getState())->getFrameHeight() * 0.35);
				}
			}
			else
			{
				if (_player[_character]->getIndex() >= _player[_character]->getPlayerImage(_player[_character]->getState())->getMaxFrameX())
				{
					_player[_character]->setIndex(0);
					_player[_character]->setState(FULLCHARGE_IDLE);
					_player[_character]->setIsBackstep(false);
					_player[_character]->setIsFired(true);
					EFFECTMANAGER->play("fullCharge_back", _player[_character]->getX(), _player[_character]->getY() + _player[_character]->getPlayerImage(_player[_character]->getState())->getFrameHeight() * 0.35);
					EFFECTMANAGER->play("fullCharge_front", _player[_character]->getX(), _player[_character]->getY() + _player[_character]->getPlayerImage(_player[_character]->getState())->getFrameHeight() * 0.35);
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
					_player[_character]->setIndex(_player[_character]->getPlayerImage(_player[_character]->getState())->getMaxFrameX());
				else
					_player[_character]->setIndex(0);
				EFFECTMANAGER->play("fullCharge_back", _player[_character]->getX(), _player[_character]->getY() + _player[_character]->getPlayerImage(_player[_character]->getState())->getFrameHeight() * 0.35);
				EFFECTMANAGER->play("fullCharge_front", _player[_character]->getX(), _player[_character]->getY() + _player[_character]->getPlayerImage(_player[_character]->getState())->getFrameHeight() * 0.35);
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
				if (_player[_character]->getIndex() >= _player[_character]->getPlayerImage(_player[_character]->getState())->getMaxFrameX())
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
				_player[_character]->setIndex(_player[_character]->getPlayerImage(_player[_character]->getState())->getMaxFrameX());
			else
				_player[_character]->setIndex(0);
		}
		else if (_player[_character]->getState() == CHARGE)
		{
			_idleCount++;

			if (_player[_character]->getIsLeft())
			{
				if (_idleCount < 40)
					_player[_character]->setIndex(_player[_character]->getPlayerImage(_player[_character]->getState())->getMaxFrameX());
				else
				{
					if (_player[_character]->getIndex() <= 0)
					{
						_idleCount = 0;
						_player[_character]->setIndex(_player[_character]->getPlayerImage(_player[_character]->getState())->getMaxFrameX());
						_player[_character]->setState(FULLCHARGE);
						EFFECTMANAGER->play("fullCharge_back", _player[_character]->getX(), _player[_character]->getY() + _player[_character]->getPlayerImage(_player[_character]->getState())->getFrameHeight() * 0.35);
						EFFECTMANAGER->play("fullCharge_front", _player[_character]->getX(), _player[_character]->getY() + _player[_character]->getPlayerImage(_player[_character]->getState())->getFrameHeight() * 0.35);
					}
				}
			}
			else
			{
				if (_idleCount < 40)
					_player[_character]->setIndex(0);
				else
				{
					if (_player[_character]->getIndex() >= _player[_character]->getPlayerImage(_player[_character]->getState())->getMaxFrameX())
					{
						_idleCount = 0;
						_player[_character]->setIndex(0);
						_player[_character]->setState(FULLCHARGE);
						EFFECTMANAGER->play("fullCharge_back", _player[_character]->getX(), _player[_character]->getY() + _player[_character]->getPlayerImage(_player[_character]->getState())->getFrameHeight() * 0.35);
						EFFECTMANAGER->play("fullCharge_front", _player[_character]->getX(), _player[_character]->getY() + _player[_character]->getPlayerImage(_player[_character]->getState())->getFrameHeight() * 0.35);
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
					_player[_character]->setIndex(_player[_character]->getPlayerImage(_player[_character]->getState())->getMaxFrameX());
					_idleCount = 0;
					_player[_character]->setCount(0);
				}
			}
			else
			{
				if (_player[_character]->getIndex() >= _player[_character]->getPlayerImage(_player[_character]->getState())->getMaxFrameX())
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
				_player[_character]->setIndex(_player[_character]->getPlayerImage(_player[_character]->getState())->getMaxFrameX());
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
					_player[_character]->setIndex(_player[_character]->getPlayerImage(_player[_character]->getState())->getMaxFrameX());
					_player[_character]->setCount(0);
				}
			}
			else
			{
				if (_player[_character]->getIndex() >= _player[_character]->getPlayerImage(_player[_character]->getState())->getMaxFrameX())
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
					_player[_character]->setIndex(_player[_character]->getPlayerImage(_player[_character]->getState())->getMaxFrameX());
					_player[_character]->setCount(0);
				}
			}
			else
			{
				if (_player[_character]->getIndex() >= _player[_character]->getPlayerImage(_player[_character]->getState())->getMaxFrameX())
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
					_player[_character]->setIndex(_player[_character]->getPlayerImage(_player[_character]->getState())->getMaxFrameX());
					_player[_character]->setCount(0);
				}
			}
			else
			{
				if (_player[_character]->getIndex() >= _player[_character]->getPlayerImage(_player[_character]->getState())->getMaxFrameX())
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
						_player[_character]->setIndex(_player[_character]->getPlayerImage(_player[_character]->getState())->getMaxFrameX());
					}
				}
				else
				{
					if (_player[_character]->getIndex() >= _player[_character]->getPlayerImage(_player[_character]->getState())->getMaxFrameX())
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
						_player[_character]->setIndex(_player[_character]->getPlayerImage(_player[_character]->getState())->getMaxFrameX());
					}
				}
				else
				{
					if (_player[_character]->getIndex() >= _player[_character]->getPlayerImage(_player[_character]->getState())->getMaxFrameX())
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
				_player[_character]->setIndex(_player[_character]->getPlayerImage(_player[_character]->getState())->getMaxFrameX());
			}
		}
		else
		{
			if (_player[_character]->getIndex() >= _player[_character]->getPlayerImage(_player[_character]->getState())->getMaxFrameX())
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
				_player[_character]->setIndex(_player[_character]->getPlayerImage(_player[_character]->getState())->getMaxFrameX());
			}
		}
		else
		{
			if (_player[_character]->getIndex() >= _player[_character]->getPlayerImage(_player[_character]->getState())->getMaxFrameX())
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
				_player[_character]->setIndex(_player[_character]->getPlayerImage(_player[_character]->getState())->getMaxFrameX());
			}
		}
		else
		{
			if (_player[_character]->getIndex() >= _player[_character]->getPlayerImage(_player[_character]->getState())->getMaxFrameX())
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
				_player[_character]->setIndex(_player[_character]->getPlayerImage(_player[_character]->getState())->getMaxFrameX());
			}
		}
		else
		{
			if (_player[_character]->getIndex() >= _player[_character]->getPlayerImage(_player[_character]->getState())->getMaxFrameX())
			{
				_idleCount = 0;
				_player[_character]->setCount(0);
				_player[_character]->setIndex(0);
			}
		}
	}

	if (!_player[_character]->getIsActive())
	{
		if (_idleCount < 200)
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
				_player[_character]->setIndex(_player[_character]->getPlayerImage(_player[_character]->getState())->getMaxFrameX());
			}
		}
		else
		{
			if (_player[_character]->getIndex() >= _player[_character]->getPlayerImage(_player[_character]->getState())->getMaxFrameX())
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
	SOUNDMANAGER->play("Wep_Clu_rifle" + to_string(RND->getFromIntTo(1, 4)));
	if (_isStayKey_up && _player[_character]->getState() != RUN)	//대각선
	{
		angle = _player[_character]->getIsLeft() ? PI_4 * 3 : PI_4;
		pos = _player[_character]->getIsLeft() ? 0.3f : - 0.3f;

		if (_player[_character]->getState() == AIM_DIAGONAL_FULLCHARGE || _player[_character]->getState() == AIM_DIAGONAL_FULLCHARGE_IDLE)
		{
			_player[_character]->setState(AIM_DIAGONALFIRE);
		
			_player[_character]->setCount(0);

			if (_player[_character]->getIsLeft())
				_player[_character]->setIndex(_player[_character]->getPlayerImage(_player[_character]->getState())->getMaxFrameX());
			else
				_player[_character]->setIndex(0);

			if (!_player[_character]->getIsJump())
				EFFECTMANAGER->play("runDust" + to_string(_player[_character]->getIsLeft()), _player[_character]->getX() + _player[_character]->getPlayerImage(_player[_character]->getState())->getFrameWidth() * pos, _player[_character]->getY() + _player[_character]->getPlayerImage(_player[_character]->getState())->getFrameHeight() * 0.35);

			pos = _player[_character]->getIsLeft() ? - 0.7 : 0.7;
			_triBullet->fire(x, y, angle, speed);
			EFFECTMANAGER->play("triBulletFire" + to_string(_player[_character]->getIsLeft() + 2), _player[_character]->getX() + _player[_character]->getPlayerImage(_player[_character]->getState())->getFrameWidth() * pos, _player[_character]->getY() - 70);
			CAMERAMANAGER->CameraShake();
		}
		else if (_player[_character]->getState() != AIM_DIAGONALFIRE)
		{
			_player[_character]->setState(AIM_DIAGONALFIRE);

			_player[_character]->setCount(0);

			if (_player[_character]->getIsLeft())
				_player[_character]->setIndex(_player[_character]->getPlayerImage(_player[_character]->getState())->getMaxFrameX());
			else
				_player[_character]->setIndex(0);

			if (!_player[_character]->getIsJump())
				EFFECTMANAGER->play("runDust" + to_string(_player[_character]->getIsLeft()), _player[_character]->getX() + _player[_character]->getPlayerImage(_player[_character]->getState())->getFrameWidth() * pos, _player[_character]->getY() + _player[_character]->getPlayerImage(_player[_character]->getState())->getFrameHeight() * 0.35);

			pos = _player[_character]->getIsLeft() ? - 0.5f : 0.5f;
			_bullet->fire(x, y, angle, speed);
			EFFECTMANAGER->play("bulletFire" + to_string(_player[_character]->getIsLeft() + 2), _player[_character]->getX() + _player[_character]->getPlayerImage(_player[_character]->getState())->getFrameWidth() * pos, _player[_character]->getY() - 50);
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
				_player[_character]->setIndex(_player[_character]->getPlayerImage(_player[_character]->getState())->getMaxFrameX());
			else
				_player[_character]->setIndex(0);
			
			if (!_player[_character]->getIsJump())
				EFFECTMANAGER->play("runDust" + to_string(_player[_character]->getIsLeft()), _player[_character]->getX() + _player[_character]->getPlayerImage(_player[_character]->getState())->getFrameWidth() * pos, _player[_character]->getY() + _player[_character]->getPlayerImage(_player[_character]->getState())->getFrameHeight() * 0.35);

			pos = _player[_character]->getIsLeft() ? - 0.7f : 0.7f;
			_triBullet->fire(x, y, angle, speed);
			EFFECTMANAGER->play("triBulletFire" + to_string(_player[_character]->getIsLeft()), _player[_character]->getX() + _player[_character]->getPlayerImage(_player[_character]->getState())->getFrameWidth() * pos, y);
			CAMERAMANAGER->CameraShake();
		}
		else if (_player[_character]->getState() != AIM_FIRE)
		{
			_player[_character]->setState(AIM_FIRE);
			_player[_character]->setCount(0);
			
			if (_player[_character]->getIsLeft())
				_player[_character]->setIndex(_player[_character]->getPlayerImage(_player[_character]->getState())->getMaxFrameX());
			else
				_player[_character]->setIndex(0);
				

			if (!_player[_character]->getIsJump())
				EFFECTMANAGER->play("runDust" + to_string(_player[_character]->getIsLeft()), _player[_character]->getX() + _player[_character]->getPlayerImage(_player[_character]->getState())->getFrameWidth() * pos, _player[_character]->getY() + _player[_character]->getPlayerImage(_player[_character]->getState())->getFrameHeight() * 0.35);

			pos = _player[_character]->getIsLeft() ? - 0.7f : 0.7f;
			_bullet->fire(x, y, angle, speed);
			EFFECTMANAGER->play("bulletFire" + to_string(_player[_character]->getIsLeft()), _player[_character]->getX() + _player[_character]->getPlayerImage(_player[_character]->getState())->getFrameWidth() * pos, y);
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
