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

	this->frameChange();
}

void monster::render(HDC hdc)
{
	if (CAMERAMANAGER->CameraIn(_image[_state].rc))
	{
		_image[_state].shadow->alphaFrameRender(hdc, _x - _image[_state].shadow->getFrameWidth() / 2 - CAMERAMANAGER->getCamera().left, _y - _image[_state].shadow->getFrameHeight() / 2 - CAMERAMANAGER->getCamera().top, 80);
		_image[_state].img->frameRender(hdc, _x - _image[_state].img->getFrameWidth() / 2 - CAMERAMANAGER->getCamera().left, _y - _image[_state].shadow->getFrameHeight() / 2 - CAMERAMANAGER->getCamera().top);
	}
}

void monster::frameChange()
{
	_count++;
	_image[_state].img->setFrameY(_isLeft);
	_image[_state].shadow->setFrameY(_isLeft);
	if (_isLeft)
	{
		_index--;
		if (_count % _frameSpeed == 0)
		{
			if (_index < 0)
				_index = _image[_state].img->getMaxFrameX();

			_image[_state].img->setFrameX(_index);
			_image[_state].shadow->setFrameX(_index);
		}
	}
	else
	{
		_index++;
		if (_count % _frameSpeed == 0)
		{
			if (_index > _image[_state].img->getMaxFrameX())
				_index = 0;

			_image[_state].img->setFrameX(_index);
			_image[_state].shadow->setFrameX(_index);
		}
	}
}

void cricket::init()
{
	_image[WALK].img = IMAGEMANAGER->findImage("Cricket_walk");
	_image[WALK].shadow = IMAGEMANAGER->findImage("Cricket_walk_shadow");
	_image[FLY].img = IMAGEMANAGER->findImage("Cricket_fly");
	_image[FLY].shadow = IMAGEMANAGER->findImage("Cricket_fly_shadow");
}

void cricket::walk()
{
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
}

void rolyPoly_large::walk()
{
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
}

void rolyPoly_white::walk()
{
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
