#include "stdafx.h"
#include "monster.h"
#include "mHpBar.h"

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
	case MONSTER_HIT:
		hit();
		break;
	case MONSTER_DEAD:
		dead();
		break;
	}

	_image[_state].rc = RectMakeCenter(_x, _y, _image[_state].img->getFrameWidth() * 0.75f, _image[_state].img->getFrameHeight() * 0.75f);

	_hpBar->update();

	if (_state == MONSTER_DEAD) 
		this->collisionProcess();
	else
		this->directionProcess();

	this->frameChange();
}

void monster::render(HDC hdc)
{
	if (CAMERAMANAGER->CameraIn(_image[_state].rc) && _isAlive)
	{
		if (_type == FIREDRINKERFLY && _state == MONSTER_DEAD)
		{
			_image[_state].img->rotateFrameRender(hdc, _x - _image[_state].img->getFrameWidth() * 0.5f - CAMERAMANAGER->getCamera().left, _y - _image[_state].shadow->getFrameHeight() * 0.5f - CAMERAMANAGER->getCamera().top, _angle);
		}
		else
		{
			_image[_state].img->frameRender(hdc, _x - _image[_state].img->getFrameWidth() * 0.5f - CAMERAMANAGER->getCamera().left, _y - _image[_state].shadow->getFrameHeight() * 0.5f - CAMERAMANAGER->getCamera().top, _index, _isLeft);
			_image[_state].shadow->alphaFrameRender(hdc, _x - _image[_state].shadow->getFrameWidth() * 0.5f - CAMERAMANAGER->getCamera().left, _y - _image[_state].shadow->getFrameHeight() * 0.5f - CAMERAMANAGER->getCamera().top, _index, _isLeft, 100);
		}
		_hpBar->render(hdc);
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

void monster::directionProcess()
{
	if (getDistance(_oldX, _oldY, _x, _y) >= _range)
		_isLeft = !_isLeft;
}

void monster::collisionProcess()
{
	if (COLLISIONMANAGER->pixelCollision(_image[_state].rc, _x, _y, _speed, _gravity, BOTTOM) ||
		COLLISIONMANAGER->pixelCollision(_image[_state].rc, _x, _y, _speed, _gravity, BOTTOM) == BLUE)
	{
		_gravity = 0.0f;
		_y += (_image[_state].rc.bottom - _image[_state].rc.top) * 0.25f;
	}
	else
	{
		_gravity += 0.55f;
		_y += _gravity;
	}
}

void monster::playerAttack(int attack)
{
	_statusCount = 0;
	_hpCount -= attack;
	_hpBar->setGauge(_hpCount, _maxHp);

	if (_hpCount > 0)
		_state = MONSTER_HIT;
	else
	{
		EFFECTMANAGER->play("ellipseExplosion", _x, _y);
		_state = MONSTER_DEAD;
		_angle = 0;
	}

	_index = _isLeft * _image[_state].img->getMaxFrameX();
}

void sandworm::init()
{
	_hpBar = new mHpBar;
	_hpBar->init("GUI_hp_bar_yellow", "GUI_hp_bar_yellow_frame", _x, _y);
	_image[MONSTER_IDLE].img = IMAGEMANAGER->findImage("Sandworm_walk");
	_image[MONSTER_IDLE].shadow = IMAGEMANAGER->findImage("Sandworm_walk_shadow");
	_image[MONSTER_MOVE].img = IMAGEMANAGER->findImage("Sandworm_walk");
	_image[MONSTER_MOVE].shadow = IMAGEMANAGER->findImage("Sandworm_walk_shadow");
	_image[MONSTER_HIT].img = IMAGEMANAGER->findImage("Sandworm_walk");
	_image[MONSTER_HIT].shadow = IMAGEMANAGER->findImage("Sandworm_walk_shadow");
	_image[MONSTER_DEAD].img = IMAGEMANAGER->findImage("bloodBlob");
	_image[MONSTER_DEAD].shadow = IMAGEMANAGER->findImage("bloodBlob");
	_speed = 5.0f;
	_angle = 0.0f;
	_gravity = 0.0f;
	_count = 0, _index = 0;
	_oldX = _x;
	_oldY = _y;
	_frameSpeed = 5;
	_statusCount = 0;
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

void sandworm::hit()
{
}

void sandworm::dead()
{
}

void spiderBaby::init()
{
	_hpBar = new mHpBar;
	_hpBar->init("GUI_hp_bar_yellow", "GUI_hp_bar_yellow_frame", _x, _y);
	_image[MONSTER_IDLE].img = IMAGEMANAGER->findImage("SpiderBaby_walk");
	_image[MONSTER_IDLE].shadow = IMAGEMANAGER->findImage("SpiderBaby_walk_shadow");
	_image[MONSTER_MOVE].img = IMAGEMANAGER->findImage("SpiderBaby_walk");
	_image[MONSTER_MOVE].shadow = IMAGEMANAGER->findImage("SpiderBaby_walk_shadow");
	_image[MONSTER_HIT].img = IMAGEMANAGER->findImage("SpiderBaby_hit");
	_image[MONSTER_HIT].shadow = IMAGEMANAGER->findImage("SpiderBaby_hit_shadow");
	_image[MONSTER_DEAD].img = IMAGEMANAGER->findImage("bloodBlob");
	_image[MONSTER_DEAD].shadow = IMAGEMANAGER->findImage("bloodBlob");
	_speed = 5.0f;
	_angle = 0.0f;
	_gravity = 0.0f;
	_count = 0, _index = 0;
	_range = 150;
	_oldX = _x;
	_oldY = _y;
	_frameSpeed = 10;
	_hpCount = _maxHp = 10;
	_statusCount = 0;
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
	_angle = _isLeft * PI;
	_x += cosf(_angle) * _speed;

	_hpBar->setPosition(_x, _image[_state].rc.bottom + 15);
}

void spiderBaby::move()
{
	
}

void spiderBaby::hit()
{
	_hpBar->setPosition(_x, _image[_state].rc.bottom + 15);

	_angle = !_isLeft * PI;
	_x += cosf(_angle) * _speed * 1.5f;

	if (_statusCount < 20)
		_statusCount++;
	else
		_state = MONSTER_IDLE;
}

void spiderBaby::dead()
{
	if ((_isLeft && _index <= 0) || (!_isLeft && _index >= _image[_state].img->getMaxFrameX()))
	{
		_isAlive = false;
	}
}

void firedrinkerFly::init()
{
	_hpBar = new mHpBar;
	_hpBar->init("GUI_hp_bar_red", "GUI_hp_bar_red_frame", _x, _y);
	_image[MONSTER_IDLE].img = IMAGEMANAGER->findImage("firedrinkerFly_fly");
	_image[MONSTER_IDLE].shadow = IMAGEMANAGER->findImage("firedrinkerFly_fly_shadow");
	_image[MONSTER_MOVE].img = IMAGEMANAGER->findImage("firedrinkerFly_fly");
	_image[MONSTER_MOVE].shadow = IMAGEMANAGER->findImage("firedrinkerFly_fly_shadow");
	_image[MONSTER_HIT].img = IMAGEMANAGER->findImage("firedrinkerFly_hit");
	_image[MONSTER_HIT].shadow = IMAGEMANAGER->findImage("firedrinkerFly_hit_shadow");
	_image[MONSTER_DEAD].img = IMAGEMANAGER->findImage("FiredrinkerFly_dead");
	_image[MONSTER_DEAD].shadow = IMAGEMANAGER->addImage("blank", _image[MONSTER_DEAD].img->getWidth(), _image[MONSTER_DEAD].img->getHeight());
	_speed = 5.0f;
	_angle = 0.0f;
	_gravity = 0.0f;
	_count = 0, _index = 0;
	_range = 200;
	_oldX = _x;
	_oldY = _y;
	_frameSpeed = 10;
	_hpCount = _maxHp = 10;
	_statusCount = 0;
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
	_angle = _isLeft * PI;
	_x += cosf(_angle) * _speed;

	_hpBar->setPosition(_x, _image[_state].rc.bottom + 15);
}

void firedrinkerFly::move()
{
}

void firedrinkerFly::hit()
{
	_hpBar->setPosition(_x, _image[_state].rc.bottom + 15);

	_angle = !_isLeft * PI;
	_x += cosf(_angle) * _speed * 1.5f;

	if (_statusCount < 20)
		_statusCount++;
	else
		_state = MONSTER_IDLE;
}

void firedrinkerFly::dead()
{
	if (_statusCount < 50)
		_statusCount++;
	else
	{
		EFFECTMANAGER->play("aerialExplosion" + to_string(RND->getFromIntTo(1, 3)), _x, _y);
		SOUNDMANAGER->play("IMP_explo_medium" + to_string(RND->getFromIntTo(1, 4)));
		_isAlive = false;
	}

	if (_isLeft)
		_angle += 0.05f;
	else
		_angle -= 0.05f;
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

void eagle::hit()
{
	_hpBar->setPosition(_x, _image[_state].rc.bottom + 15);

	_angle = !_isLeft * PI;
	_x += cosf(_angle) * _speed * 1.5f;

	if (_statusCount < 20)
		_statusCount++;
	else
		_state = MONSTER_IDLE;
}

void eagle::dead()
{
	if ((_isLeft && _index <= 0) || (!_isLeft && _index >= _image[_state].img->getMaxFrameX()))
	{
		_isAlive = false;
	}
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
