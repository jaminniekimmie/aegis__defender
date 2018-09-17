#include "stdafx.h"
#include "monster.h"

void monster::update()
{
	switch (_state)
	{
	case WALK:
		walk();
		break;
	case FLY:
		fly();
		break;
	case DEAD:
		break;
	}

	_image[_state].rc = RectMakeCenter(_x, _y, _image[_state].img->getFrameWidth(), _image[_state].img->getFrameHeight());

	_gravity += 0.55f;
	_y += _gravity;

	this->collisionProcess();
	this->frameChange();
}

void monster::render(HDC hdc)
{
	if (CAMERAMANAGER->CameraIn(_image[_state].rc))
	{
		_image[_state].shadow->alphaFrameRender(hdc, _x - _image[_state].shadow->getFrameWidth() * 0.5f - CAMERAMANAGER->getCamera().left, _y - _image[_state].shadow->getFrameHeight() * 0.5f - CAMERAMANAGER->getCamera().top, 80);
		_image[_state].img->frameRender(hdc, _x - _image[_state].img->getFrameWidth() * 0.5f - CAMERAMANAGER->getCamera().left, _y - _image[_state].shadow->getFrameHeight() * 0.5f - CAMERAMANAGER->getCamera().top);
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
	if (COLLISIONMANAGER->pixelCollision(_image[_state].rc, _x, _y, _speed, _gravity, BOTTOM))
	{
		_gravity = 0.0f;
	}
	if (COLLISIONMANAGER->pixelCollision(_image[_state].rc, _x, _y, _speed, _gravity, LEFT) ||
		COLLISIONMANAGER->pixelCollision(_image[_state].rc, _x, _y, _speed, _gravity, LEFT))
	{
		_isLeft = !_isLeft;
	}
}

void cricket::init()
{
	_image[WALK].img = IMAGEMANAGER->findImage("Cricket_walk");
	_image[WALK].shadow = IMAGEMANAGER->findImage("Cricket_walk_shadow");
	_image[FLY].img = IMAGEMANAGER->findImage("Cricket_fly");
	_image[FLY].shadow = IMAGEMANAGER->findImage("Cricket_fly_shadow");
	_speed = 3.0f;
	_angle = 0.0f;
	_gravity = 0.0f;
	_count = 0, _index = 0;
	_frameSpeed = 10;
	_isAlive = true;
	_isLeft = false;
	_state = WALK;
}

void cricket::walk()
{	
	_angle = _isLeft * PI;
	_x += cosf(_angle) * _speed;
}

void cricket::fly()
{
}

void rolyPoly_large::init()
{
	_image[WALK].img = IMAGEMANAGER->findImage("RolyPoly_Large_walk");
	_image[WALK].shadow = IMAGEMANAGER->findImage("RolyPoly_Large_walk_shadow");
	_image[FLY].img = IMAGEMANAGER->findImage("RolyPoly_Large_walk");
	_image[FLY].shadow = IMAGEMANAGER->findImage("RolyPoly_Large_walk_shadow");
	_speed = 3.0f;
	_angle = PI;
	_gravity = 0.0f;
	_count = 0, _index = 0;
	_frameSpeed = 10;
	_isAlive = true;
	_isLeft = true;
	_state = WALK;
}

void rolyPoly_large::walk()
{
	_angle = _isLeft * PI;
	_x += cosf(_angle) * _speed;
}

void rolyPoly_large::fly()
{
}

void rolyPoly_white::init()
{
	_image[WALK].img = IMAGEMANAGER->findImage("RolyPoly_White_walk");
	_image[WALK].shadow = IMAGEMANAGER->findImage("RolyPoly_White_walk_shadow");
	_image[FLY].img = IMAGEMANAGER->findImage("RolyPoly_White_walk");
	_image[FLY].shadow = IMAGEMANAGER->findImage("RolyPoly_White_walk_shadow");
	_speed = 3.0f;
	_angle = 0.0f;
	_gravity = 0.0f;
	_count = 0, _index = 0;
	_frameSpeed = 10;
	_isAlive = true;
	_isLeft = true;
	_state = WALK;
}

void rolyPoly_white::walk()
{
	_angle = _isLeft * PI;
	_x += cosf(_angle) * _speed;
}

void rolyPoly_white::fly()
{
}

monster * monsterFactory::createMonster(MONSTERTYPE type)
{
	monster* _monster;
	switch (type)
	{
	case CRICKET:
		_monster = new cricket;
		break;
	case ROLYPOLY_LARGE:
		_monster = new rolyPoly_large;
		break;
	case ROLYPOLY_WHITE:
		_monster = new rolyPoly_white;
		break;
	default:
		//´©±¸³Ä ³Í??
		break;
	}

	_monster->init();
	_monster->setType(type);

	return _monster;
}
