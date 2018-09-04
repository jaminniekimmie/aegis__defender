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
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _player->getPlayerRc().right < TILESIZEX)
	{
		_player->setIsLeft(RIGHT);
		_player->setState(RUN);
		_player->setX(_player->getX() + cosf(0.0f) * 5.0f);
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT) || KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		_player->setState(IDLE);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		if (!_player->getIsJump() && _player->getOnLand())
			_player->setIsJump(true);
	}

	this->playerJump();

	if (_player->getY() >= TILESIZEY - WINSIZEY / 2)
	{
		_player->setSpeed(0.0f);
		_player->setGravity(0.0f);
		_player->setAngle(-PI_2);
		_player->setY(TILESIZEY - WINSIZEY / 2);
		_player->setIsJump(false);
		_player->setState(LAND);
	}
}

void playerManager::render(void)
{
	_player->render();
}

void playerManager::playerJump()
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
