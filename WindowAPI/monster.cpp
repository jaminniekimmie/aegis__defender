#include "stdafx.h"
#include "monster.h"

void monster::update()
{
	switch (_state)
	{
	case MONSTER_IDLE:
		idle();
	case MONSTER_MOVE:
		move();
		break;
	case MONSTER_DEAD:
		break;
	}

	_image[_state].rc = RectMakeCenter(_x, _y, _image[_state].img->getFrameWidth(), _image[_state].img->getFrameHeight());

	this->collisionProcess();
	this->frameChange();
}

void monster::render(HDC hdc)
{
	if (CAMERAMANAGER->CameraIn(_image[_state].rc))
	{
		_image[_state].img->frameRender(hdc, _x - _image[_state].img->getFrameWidth() * 0.5f - CAMERAMANAGER->getCamera().left, _y - _image[_state].shadow->getFrameHeight() * 0.5f - CAMERAMANAGER->getCamera().top);
		_image[_state].shadow->alphaFrameRender(hdc, _x - _image[_state].shadow->getFrameWidth() * 0.5f - CAMERAMANAGER->getCamera().left, _y - _image[_state].shadow->getFrameHeight() * 0.5f - CAMERAMANAGER->getCamera().top, 80);
	}
	if (KEYMANAGER->isToggleKey('T'))
	{
		Rectangle(hdc, _image[_state].rc.left - CAMERAMANAGER->getCamera().left, _image[_state].rc.top - CAMERAMANAGER->getCamera().top, _image[_state].rc.right - CAMERAMANAGER->getCamera().left, _image[_state].rc.bottom - CAMERAMANAGER->getCamera().top);
	}
}

void monster::frameChange()
{
	_count++;
	_image[_state].img->setFrameY(_isLeft);
	_image[_state].shadow->setFrameY(_isLeft);
	if (_isLeft)
	{
		if (_count % _frameSpeed == 0)
		{
			_index--;
			if (_index < 0)
				_index = _image[_state].img->getMaxFrameX();

			_image[_state].img->setFrameX(_index);
			_image[_state].shadow->setFrameX(_index);
		}
	}
	else
	{
		if (_count % _frameSpeed == 0)
		{
			_index++;
			if (_index > _image[_state].img->getMaxFrameX())
				_index = 0;

			_image[_state].img->setFrameX(_index);
			_image[_state].shadow->setFrameX(_index);
		}
	}
}

void monster::collisionProcess()
{
	if (getDistance(_oldX, _oldY, _x, _y) > _range)
	{
		_isLeft = !_isLeft;
	}
}

void sandworm::init()
{
	_image[MONSTER_MOVE].img = IMAGEMANAGER->findImage("Sandworm_walk");
	_image[MONSTER_MOVE].shadow = IMAGEMANAGER->findImage("Sandworm_walk_shadow");
	_speed = 8.0f;
	_angle = 0.0f;
	_gravity = 0.0f;
	_count = 0, _index = 0;
	_range = 500;
	_oldX = _x;
	_oldY = _y;
	_frameSpeed = 5;
	_isAlive = true;
	_isLeft = false;
	_state = MONSTER_MOVE;
}

void sandworm::idle()
{
	_state = MONSTER_MOVE;
}

void sandworm::move()
{
	_angle = _isLeft * PI;
	_x += cosf(_angle) * _speed;
}

void spiderBaby::init()
{
	_image[MONSTER_MOVE].img = IMAGEMANAGER->findImage("SpiderBaby_walk");
	_image[MONSTER_MOVE].shadow = IMAGEMANAGER->findImage("SpiderBaby_walk_shadow");
	_speed = 3.0f;
	_angle = 0.0f;
	_gravity = 0.0f;
	_count = 0, _index = 0;
	_range = 200;
	_oldX = _x;
	_oldY = _y;
	_frameSpeed = 10;
	_isAlive = true;
	_isLeft = false;
	_state = MONSTER_MOVE;
}

void spiderBaby::idle()
{
	_state = MONSTER_MOVE;
}

void spiderBaby::move()
{
	_angle = _isLeft * PI;
	_x += cosf(_angle) * _speed;
}

void firedrinkerFly::init()
{
	_image[MONSTER_MOVE].img = IMAGEMANAGER->findImage("firedrinkerFly_fly");
	_image[MONSTER_MOVE].shadow = IMAGEMANAGER->findImage("firedrinkerFly_fly_shadow");
	_speed = 3.0f;
	_angle = 0.0f;
	_gravity = 0.0f;
	_count = 0, _index = 0;
	_range = 200;
	_oldX = _x;
	_oldY = _y;
	_frameSpeed = 10;
	_isAlive = true;
	_isLeft = false;
	_state = MONSTER_MOVE;
}

void firedrinkerFly::idle()
{
	_state = MONSTER_MOVE;
}

void firedrinkerFly::move()
{
}

void eagle::init()
{
}

void eagle::idle()
{
}

void eagle::move()
{
}

monster * monsterFactory::createMonster(MONSTERTYPE type)
{
	monster* _monster;
	switch (type)
	{
	case SANDWORM:
		_monster = new sandworm;
		break;
	case SPIDERBABY:
		_monster = new spiderBaby;
		break;
	case FIREDRINKERFLY:
		_monster = new firedrinkerFly;
		break;
	case EAGLE:
		_monster = new eagle;
		break;
	default:
		//������ ��??
		break;
	}

	_monster->init();
	_monster->setType(type);

	return _monster;
}
