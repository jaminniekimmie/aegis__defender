#include "stdafx.h"
#include "monster.h"
#include "hpBar.h"

void monster::update()
{
	switch (_state)
	{
	case MONSTER_IDLE:
		idle();
		break;
	case MONSTER_MOVE:
		move();
		break;
	case MONSTER_DEAD:
		dead();
		break;
	}

	_image[_state].rc = RectMakeCenter(_x, _y, _image[_state].img->getFrameWidth(), _image[_state].img->getFrameHeight());

	_hpBar->update();

	this->directionProcess();
	this->collisionProcess();
	this->frameChange();
}

void monster::render(HDC hdc)
{
	if (CAMERAMANAGER->CameraIn(_image[_state].rc) && _isAlive)
	{
		_image[_state].img->frameRender(hdc, _x - _image[_state].img->getFrameWidth() * 0.5f - CAMERAMANAGER->getCamera().left, _y - _image[_state].shadow->getFrameHeight() * 0.5f - CAMERAMANAGER->getCamera().top, _index, _isLeft);
		_image[_state].shadow->alphaFrameRender(hdc, _x - _image[_state].shadow->getFrameWidth() * 0.5f - CAMERAMANAGER->getCamera().left, _y - _image[_state].shadow->getFrameHeight() * 0.5f - CAMERAMANAGER->getCamera().top, _index, _isLeft, 100);
		_hpBar->render(hdc);
	}
	if (KEYMANAGER->isToggleKey('T'))
	{
		Rectangle(hdc, _image[_state].rc.left - CAMERAMANAGER->getCamera().left, _image[_state].rc.top - CAMERAMANAGER->getCamera().top, _image[_state].rc.right - CAMERAMANAGER->getCamera().left, _image[_state].rc.bottom - CAMERAMANAGER->getCamera().top);
	}
}

void monster::idle()
{
}

void monster::move()
{
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

void monster::directionProcess()
{
	if (getDistance(_oldX, _oldY, _x, _y) >= _range)
	{
		_isLeft = !_isLeft;
	}
}

void monster::collisionProcess()
{
	if (_state == MONSTER_DEAD)
	{
		if (COLLISIONMANAGER->pixelCollision(_image[_state].rc, _x, _y, _speed, _gravity, BOTTOM))
		{
			_gravity = 0.0f;
		}
		else
		{
			_gravity += 0.55f;
			_y += _gravity;
		}

	}
}

void sandworm::init()
{
	_hpBar = new hpBar;
	_hpBar->init("GUI_hp_bar_yellow", "GUI_hp_bar_yellow_frame", _x, _y);
	_image[MONSTER_IDLE].img = IMAGEMANAGER->findImage("Sandworm_walk");
	_image[MONSTER_IDLE].shadow = IMAGEMANAGER->findImage("Sandworm_walk_shadow");
	_image[MONSTER_MOVE].img = IMAGEMANAGER->findImage("Sandworm_walk");
	_image[MONSTER_MOVE].shadow = IMAGEMANAGER->findImage("Sandworm_walk_shadow");
	_image[MONSTER_DEAD].img = IMAGEMANAGER->findImage("fx_bloodBlob");
	_image[MONSTER_DEAD].shadow = IMAGEMANAGER->findImage("fx_bloodBlob");
	_speed = 5.0f;
	_angle = 0.0f;
	_gravity = 0.0f;
	_count = 0, _index = 0;
	_oldX = _x;
	_oldY = _y;
	_frameSpeed = 5;
	_isHit = false;
	_isAlive = true;
	_isLeft = RND->getFromIntTo(0, 1);
	_state = MONSTER_IDLE;
}

void sandworm::release()
{
	_hpBar->release();
	SAFE_DELETE(_hpBar);
}

void sandworm::idle()
{
	_angle = _isLeft * PI;
	_x += cosf(_angle) * _speed;
}

void sandworm::move()
{
}

void sandworm::dead()
{
}

void spiderBaby::init()
{
	_hpBar = new hpBar;
	_hpBar->init("GUI_hp_bar_yellow", "GUI_hp_bar_yellow_frame", _x, _y);
	_image[MONSTER_IDLE].img = IMAGEMANAGER->findImage("SpiderBaby_walk");
	_image[MONSTER_IDLE].shadow = IMAGEMANAGER->findImage("SpiderBaby_walk_shadow");
	_image[MONSTER_MOVE].img = IMAGEMANAGER->findImage("SpiderBaby_walk");
	_image[MONSTER_MOVE].shadow = IMAGEMANAGER->findImage("SpiderBaby_walk_shadow");
	_image[MONSTER_DEAD].img = IMAGEMANAGER->findImage("fx_bloodBlob");
	_image[MONSTER_DEAD].shadow = IMAGEMANAGER->findImage("fx_bloodBlob");
	_speed = 5.0f;
	_angle = 0.0f;
	_gravity = 0.0f;
	_count = 0, _index = 0;
	_range = 150;
	_oldX = _x;
	_oldY = _y;
	_frameSpeed = 10;
	_hpCount = _maxHp = 5;
	_isHit = false;
	_isAlive = true;
	_isLeft = RND->getFromIntTo(0, 1);
	_state = MONSTER_IDLE;
}

void spiderBaby::release()
{
	_hpBar->release();
	SAFE_DELETE(_hpBar);
}

void spiderBaby::idle()
{
	_state = MONSTER_MOVE;
}

void spiderBaby::move()
{
	if (_isHit)
	{
		if (_hpCount > 0)
			_hpCount--;
		else
			_state = MONSTER_DEAD;

		_hpBar->setGauge(_hpCount, _maxHp);
		_isHit = false;
	}

	_hpBar->setPosition(_x, _y);

	_angle = _isLeft * PI;
	_x += cosf(_angle) * _speed;
}

void spiderBaby::dead()
{

}

void firedrinkerFly::init()
{
	_hpBar = new hpBar;
	_hpBar->init("GUI_hp_bar_red", "GUI_hp_bar_red_frame", _x, _y);
	_image[MONSTER_IDLE].img = IMAGEMANAGER->findImage("firedrinkerFly_fly");
	_image[MONSTER_IDLE].shadow = IMAGEMANAGER->findImage("firedrinkerFly_fly_shadow");
	_image[MONSTER_MOVE].img = IMAGEMANAGER->findImage("firedrinkerFly_fly");
	_image[MONSTER_MOVE].shadow = IMAGEMANAGER->findImage("firedrinkerFly_fly_shadow");
	_image[MONSTER_DEAD].img = IMAGEMANAGER->findImage("fx_bloodBlob");
	_image[MONSTER_DEAD].shadow = IMAGEMANAGER->findImage("fx_bloodBlob");
	_speed = 5.0f;
	_angle = 0.0f;
	_gravity = 0.0f;
	_count = 0, _index = 0;
	_range = 200;
	_oldX = _x;
	_oldY = _y;
	_frameSpeed = 10;
	_hpCount = _maxHp = 5;
	_isHit = false;
	_isAlive = true;
	_isLeft = RND->getFromIntTo(0, 1);
	_state = MONSTER_IDLE;
}

void firedrinkerFly::release()
{
	_hpBar->release();
	SAFE_DELETE(_hpBar);
}

void firedrinkerFly::idle()
{
	_state = MONSTER_MOVE;
}

void firedrinkerFly::move()
{
	if (_isHit)
	{
		if (_hpCount > 0)
			_hpCount--;
		else
			_state = MONSTER_DEAD;

		_hpBar->setGauge(_hpCount, _maxHp);
		_isHit = false;
	}

	_hpBar->setPosition(_x, _y);

	_angle = _isLeft * PI;
	_x += cosf(_angle) * _speed;
}

void firedrinkerFly::dead()
{
}

void eagle::init()
{
}

void eagle::release()
{
}

void eagle::idle()
{
}

void eagle::move()
{
}

void eagle::dead()
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
		//´©±¸³Ä ³Í??
		break;
	}

	_monster->init();
	_monster->setType(type);

	return _monster;
}
