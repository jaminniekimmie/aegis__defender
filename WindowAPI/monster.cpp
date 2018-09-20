#include "stdafx.h"
#include "monster.h"

void monster::update()
{
	switch (_state)
	{
	case WALK:
		walk();
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

void sandworm::init()
{
	_image[WALK].img = IMAGEMANAGER->findImage("Sandworm");
	_image[WALK].shadow = IMAGEMANAGER->findImage("Sandworm");
	_speed = 3.0f;
	_angle = 0.0f;
	_gravity = 0.0f;
	_count = 0, _index = 0;
	_frameSpeed = 10;
	_isAlive = true;
	_isLeft = false;
	_state = WALK;
}

void sandworm::walk()
{
	_angle = _isLeft * PI;
	_x += cosf(_angle) * _speed;
}

monster * monsterFactory::createMonster(MONSTERTYPE type)
{
	monster* _monster;
	switch (type)
	{
	case SANDWORM:
		_monster = new sandworm;
		break;
	default:
		//´©±¸³Ä ³Í??
		break;
	}

	_monster->init();
	_monster->setType(type);

	return _monster;
}
