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
	case MONSTER_ITEM:
		item();
		break;
	}

	if (_isFrameImg)
		_image[_state].rc = RectMakeCenter(_x, _y, _image[_state].img->getFrameWidth() * 0.75f, _image[_state].img->getFrameHeight() * 0.75f);
	else
		_image[_state].rc = RectMakeCenter(_x, _y, _image[_state].img->getWidth() * 0.75f, _image[_state].img->getHeight() * 0.75f);

	_hpBar->update();

	if (_state == MONSTER_DEAD || _state == MONSTER_ITEM)
		this->collisionProcess();
	else
		this->directionProcess();

	this->frameChange();
}

void monster::render(HDC hdc)
{
	if (CAMERAMANAGER->CameraIn(_image[_state].rc) && _isAlive)
	{
		if (_isFrameImg)
		{
			_image[_state].img->frameRender(hdc, _x - _image[_state].img->getFrameWidth() * 0.5f - CAMERAMANAGER->getCamera().left, _y - _image[_state].shadow->getFrameHeight() * 0.5f - CAMERAMANAGER->getCamera().top, _index, _isLeft);
			_image[_state].shadow->alphaFrameRender(hdc, _x - _image[_state].shadow->getFrameWidth() * 0.5f - CAMERAMANAGER->getCamera().left, _y - _image[_state].shadow->getFrameHeight() * 0.5f -CAMERAMANAGER->getCamera().top, _index, _isLeft, 100);
		}
		else
		{
			_image[_state].img->render(hdc, _x - _image[_state].img->getWidth() * 0.5f - CAMERAMANAGER->getCamera().left, _y - _image[_state].shadow->getHeight() * 0.5f - CAMERAMANAGER->getCamera().top);
			_image[_state].shadow->alphaRender(hdc, _x - _image[_state].shadow->getWidth() * 0.5f - CAMERAMANAGER->getCamera().left, _y - _image[_state].shadow->getHeight() * 0.5f - CAMERAMANAGER->getCamera().top, 100);
		}
		if (MONSTER_IDLE == _state || MONSTER_MOVE == _state || MONSTER_HIT == _state)
			_hpBar->render(hdc);
	}


	if (KEYMANAGER->isToggleKey('T'))
	{
		Rectangle(hdc, _image[_state].rc.left - CAMERAMANAGER->getCamera().left, _image[_state].rc.top - CAMERAMANAGER->getCamera().top, _image[_state].rc.right - CAMERAMANAGER->getCamera().left, _image[_state].rc.bottom - CAMERAMANAGER->getCamera().top);
	}
}

void monster::frameChange()
{
	if (_isFrameImg)
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
				{
					if (_state == MONSTER_DEAD)
					{
						_isAlive = false;
					}
					_index = _image[_state].img->getMaxFrameX();
				}

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
				{

					if (_state == MONSTER_DEAD)
						_isAlive = false;
					_index = 0;
				}

				_image[_state].img->setFrameX(_index);
				_image[_state].shadow->setFrameX(_index);
			}
		}
	}
}

void monster::directionProcess()
{
	if (getDistance(_oldX, _oldY, _x, _y) >= _range)
	{
		_isLeft = !_isLeft;
		_angle = PI - _angle;
	}
}

void monster::collisionProcess()
{
	if (_state == MONSTER_DEAD)
	{
		_speed = 8;
		_gravity += 0.55f;
		_y += _gravity;
	}
	if (COLLISIONMANAGER->pixelCollision(_image[_state].rc, _x, _y, _speed, _gravity, BOTTOM) ||
		COLLISIONMANAGER->pixelCollision(_image[_state].rc, _x, _y, _speed, _gravity, BOTTOM) == BLUE)
	{
		_gravity = 0.0f;
		//_speed = 0;
		_y += (_image[_state].rc.bottom - _image[_state].rc.top) * 0.25f;
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
	//잘 하 자
	_index = _isLeft * _image[_state].img->getMaxFrameX();
}

void sandworm::init()
{
	_hpBar = new mHpBar;
	_hpBar->init("GUI_hp_bar_yellow", "GUI_hp_bar_yellow_frame", _x, _y);
	_image[MONSTER_IDLE].img = IMAGEMANAGER->findImage("Sandworm_walk");
	_image[MONSTER_IDLE].shadow = IMAGEMANAGER->findImage("Sandworm_walk");
	_image[MONSTER_MOVE].img = IMAGEMANAGER->findImage("Sandworm_attack");
	_image[MONSTER_MOVE].shadow = IMAGEMANAGER->findImage("Sandworm_attack");
	_image[MONSTER_HIT].img = IMAGEMANAGER->findImage("Sandworm_walk");
	_image[MONSTER_HIT].shadow = IMAGEMANAGER->findImage("Sandworm_walk");
	_image[MONSTER_DEAD].img = IMAGEMANAGER->findImage("bloodBlob");
	_image[MONSTER_DEAD].shadow = IMAGEMANAGER->findImage("bloodBlob");
	_image[MONSTER_ITEM].img = IMAGEMANAGER->findImage("g_bubble");
	_image[MONSTER_ITEM].shadow = IMAGEMANAGER->findImage("g_bubble");
	_speed = 4.0f;
	_angle = 0.0f;
	_gravity = 0.0f;
	_count = 0, _index = 0;
	_oldX = _x;
	_oldY = _y;
	_frameSpeed = 10;
	_statusCount = 0;
	_isAlive = true;
	_isLeft = RND->getFromIntTo(0, 1);
	_isFrameImg = true;
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
	_angle = _isLeft * PI;
	_x += cosf(_angle) * _speed;
}

void sandworm::hit()
{
}

void sandworm::dead()
{
}

void sandworm::item()
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
	_image[MONSTER_ITEM].img = IMAGEMANAGER->findImage("g_bubble");
	_image[MONSTER_ITEM].shadow = IMAGEMANAGER->findImage("g_bubble");
	_speed = 1.5f;
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
	_isFrameImg = true;
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
	_angle = _isLeft * PI;
	_hpBar->setPosition(_x, _image[_state].rc.bottom + 15);
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
		_state = MONSTER_ITEM;
	}
}

void spiderBaby::item()
{
	if (_isFrameImg)
	{
		_angle = RND->getFromFloatTo(PI_4, PI_4 * 3);
		_speed = RND->getFromFloatTo(6, 10);
		_gravity = 0.0f;
		_isFrameImg = false;
	}

	_x += cosf(_angle) * _speed;
	_y += -sinf(_angle) * _speed;
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
	_image[MONSTER_ITEM].img = IMAGEMANAGER->findImage("g_bubble");
	_image[MONSTER_ITEM].shadow = IMAGEMANAGER->findImage("g_bubble");
	_speed = 3.0f;
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
	_isFrameImg = true;
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
	_hpBar->setPosition(_x, _image[_state].rc.bottom + 15);
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
		_state = MONSTER_ITEM;
	}

	if (_isLeft)
		_angle += 0.05f;
	else
		_angle -= 0.05f;
}

void firedrinkerFly::item()
{
	if (_isFrameImg)
	{
		_angle = RND->getFromFloatTo(PI_4, PI_4 * 3);
		_speed = RND->getFromFloatTo(6, 10);
		_gravity = 0.0f;
		_isFrameImg = false;
	}

	_x += cosf(_angle) * _speed;
	_y += -sinf(_angle) * _speed;
}

void firedrinkerFly::render(HDC hdc)
{
	monster::render(hdc);

	if (CAMERAMANAGER->CameraIn(_image[_state].rc) && _state == MONSTER_DEAD)
	{
		_image[_state].img->rotateFrameRender(hdc, _x - _image[_state].img->getFrameWidth() * 0.5f - CAMERAMANAGER->getCamera().left, _y - _image[_state].shadow->getFrameHeight() * 0.5f - CAMERAMANAGER->getCamera().top, _angle);
	}
}

void eagle::init()
{
	_hpBar = new mHpBar;
	_hpBar->init("GUI_hp_bar_blue", "GUI_hp_bar_blue_frame", _x, _y);
	_image[MONSTER_IDLE].img = IMAGEMANAGER->findImage("Eagle_idle");
	_image[MONSTER_IDLE].shadow = IMAGEMANAGER->findImage("Eagle_idle");
	_image[MONSTER_MOVE].img = IMAGEMANAGER->findImage("Eagle_fly");
	_image[MONSTER_MOVE].shadow = IMAGEMANAGER->findImage("Eagle_fly");
	_image[MONSTER_HIT].img = IMAGEMANAGER->findImage("Eagle_hit");
	_image[MONSTER_HIT].shadow = IMAGEMANAGER->findImage("Eagle_hit");
	_image[MONSTER_DEAD].img = IMAGEMANAGER->findImage("bloodBlob");
	_image[MONSTER_DEAD].shadow = IMAGEMANAGER->addImage("blank", _image[MONSTER_DEAD].img->getWidth(), _image[MONSTER_DEAD].img->getHeight());
	_image[MONSTER_ITEM].img = IMAGEMANAGER->findImage("g_bubble");
	_image[MONSTER_ITEM].shadow = IMAGEMANAGER->findImage("g_bubble");
	_speed = 4.0f;
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
	_isFrameImg = true;
	_state = MONSTER_IDLE;
}

void eagle::release()
{
	_hpBar->release();
	SAFE_DELETE(_hpBar);
}

void eagle::idle()
{
	_hpBar->setPosition(_x, _image[_state].rc.bottom + 15);
	_statusCount = 0;
}

void eagle::move()
{
	if (_statusCount < 100)
		_statusCount++;
	else
	{
		_statusCount = 0;
		_isLeft = RND->getFromIntTo(0, 1);
		_angle = _isLeft ? RND->getFromFloatTo(PI_4 * 3, PI_4 * 5) : RND->getFromFloatTo(PI_4 * 7, PI_4 * 9);
	}

	_x += cosf(_angle) * _speed;
	_y += -sinf(_angle) * _speed;

	if (COLLISIONMANAGER->pixelCollision(_image[_state].rc, _x, _y, _speed, _gravity, BOTTOM) ||
		COLLISIONMANAGER->pixelCollision(_image[_state].rc, _x, _y, _speed, _gravity, BOTTOM))
	{
		_state = MONSTER_IDLE;
	}

	_hpBar->setPosition(_x, _image[_state].rc.bottom + 15);
}

void eagle::hit()
{
	_hpBar->setPosition(_x, _image[_state].rc.bottom + 15);

	_angle = !_isLeft * PI;
	_x += cosf(_angle) * _speed * 1.5f;

	if (_statusCount < 20)
		_statusCount++;
	else
		_state = MONSTER_MOVE;
}

void eagle::dead()
{
	if ((_isLeft && _index <= 0) || (!_isLeft && _index >= _image[_state].img->getMaxFrameX()))
	{
		//_state = MONSTER_ITEM;
		_isAlive = false;
	}
}

void eagle::item()
{
	if (_isFrameImg)
	{
		_angle = RND->getFromFloatTo(PI_4, PI_4 * 3);
		_speed = RND->getFromFloatTo(6, 10);
		_gravity = 0.0f;
		_isFrameImg = false;
	}

	_x += cosf(_angle) * _speed;
	_y += -sinf(_angle) * _speed;
}

void thief_boomerang::init()
{
	_hpBar = new mHpBar;
	_hpBar->init("GUI_hp_bar_yellow", "GUI_hp_bar_yellow_frame", _x, _y);
	_image[MONSTER_IDLE].img = IMAGEMANAGER->findImage("Thief_Boomerang_walk");
	_image[MONSTER_IDLE].shadow = IMAGEMANAGER->findImage("Thief_Boomerang_walk_shadow");
	_image[MONSTER_MOVE].img = IMAGEMANAGER->findImage("Thief_Boomerang_attack");
	_image[MONSTER_MOVE].shadow = IMAGEMANAGER->findImage("Thief_Boomerang_attack_shadow");
	_image[MONSTER_HIT].img = IMAGEMANAGER->findImage("Thief_Boomerang_hit");
	_image[MONSTER_HIT].shadow = IMAGEMANAGER->findImage("Thief_Boomerang_hit");
	_image[MONSTER_DEAD].img = IMAGEMANAGER->findImage("bloodBlob");
	_image[MONSTER_DEAD].shadow = IMAGEMANAGER->addImage("blank", _image[MONSTER_DEAD].img->getWidth(), _image[MONSTER_DEAD].img->getHeight());
	_image[MONSTER_ITEM].img = IMAGEMANAGER->findImage("g_bubble");
	_image[MONSTER_ITEM].shadow = IMAGEMANAGER->findImage("g_bubble");
	_speed = 3.0f;
	_angle = 0.0f;
	_gravity = 0.0f;
	_count = 0, _index = 0;
	_range = 200;
	_oldX = _x;
	_oldY = _y;
	_frameSpeed = 10;
	_hpCount = _maxHp = 10;
	_statusCount = 0;
	_rotateAngle = 0;
	_isAlive = true;
	_isLeft = RND->getFromIntTo(0, 1);
	_isFrameImg = true;
	_state = MONSTER_IDLE;
}

void thief_boomerang::release()
{
	_hpBar->release();
	SAFE_DELETE(_hpBar);
}

void thief_boomerang::idle()
{
	_angle = _isLeft * PI;
	_x += cosf(_angle) * _speed;
	
	if (!_vElement.empty()) _vElement.clear();
}

void thief_boomerang::move()
{
	RECT rcTemp;

	_angle = _isLeft * PI;
	_statusCount++;

	if (_statusCount > 10 && _vElement.empty())
	{
		tagElement element;
		ZeroMemory(&element, sizeof(tagElement));
		element.elementImg = IMAGEMANAGER->findImage("boomerang");
		element.x = element.fireX = _x;
		element.y = element.fireY = _y;
		element.speed = 10.0f;
		element.count = 0;
		element.alpha = 255;
		element.gravity = 0.0f;
		element.angle = !_isLeft * PI;
		element.fire = false;
		element.rc = RectMakeCenter(element.x, element.y, element.elementImg->getWidth(), element.elementImg->getHeight());

		_vElement.push_back(element);
	}
	else
	{
		for (int i = 0; i < _vElement.size(); i++)
		{
			//if (_vElement[i].fire)
			{
				_vElement[i].speed -= 0.2f;
				_vElement[i].x += cosf(_angle) * _vElement[i].speed;
				_vElement[i].y += -sinf(_angle) * _vElement[i].speed;
				_vElement[i].rc = RectMakeCenter(_vElement[i].x, _vElement[i].y, _vElement[i].elementImg->getWidth(), _vElement[i].elementImg->getHeight());
			}

			_isLeft ? _rotateAngle -= 1.f : _rotateAngle += 1.f;

			if (_vElement[i].speed < 0)
			{
				//if (getDistance(_vElement[i].fireX, _vElement[i].fireY, _vElement[i].x, _vElement[i].y) < 1)
				if (IntersectRect(&rcTemp, &_vElement[i].rc, &_image[_state].rc))
				{
					_vElement.erase(_vElement.begin() + i);
					_statusCount = 0;
					_rotateAngle = 0;
				}
			}
		}

		//if (_index >= _image[_state].img->getMaxFrameX() - 1)
		//{
		//	_index = _image[_state].img->getMaxFrameX();
		//	_image[_state].img->setFrameX(_index);
		//}
	}
	_hpBar->setPosition(_x, _image[_state].rc.bottom + 15);
}

void thief_boomerang::hit()
{
	_hpBar->setPosition(_x, _image[_state].rc.bottom + 15);

	_angle = !_isLeft * PI;
	_x += cosf(_angle) * _speed * 1.5f;

	if (_statusCount < 20)
		_statusCount++;
	else
		_state = MONSTER_IDLE;
}

void thief_boomerang::dead()
{
	if ((_isLeft && _index <= 0) || (!_isLeft && _index >= _image[_state].img->getMaxFrameX()))
	{
		_state = MONSTER_ITEM;
	}
}

void thief_boomerang::item()
{
	if (_isFrameImg)
	{
		_angle = RND->getFromFloatTo(PI_4, PI_4 * 3);
		_speed = RND->getFromFloatTo(6, 10);
		_gravity = 0.0f;
		_isFrameImg = false;
	}

	_x += cosf(_angle) * _speed;
	_y += -sinf(_angle) * _speed;
}

void thief_boomerang::render(HDC hdc)
{
	monster::render(hdc);

	for (int i = 0; i < _vElement.size(); i++)
	{
		if (!CAMERAMANAGER->CameraIn(_vElement[i].rc)) continue;

		_vElement[i].elementImg->rotateRender(hdc, _vElement[i].rc.left - CAMERAMANAGER->getCamera().left, _vElement[i].rc.top - CAMERAMANAGER->getCamera().top, _rotateAngle);

	}

}

void mask::init()
{
	_hpBar = new mHpBar;
	_hpBar->init("GUI_hp_bar_blue", "GUI_hp_bar_blue_frame", _x, _y);
	_image[MONSTER_IDLE].img = IMAGEMANAGER->findImage("Mask_walk");
	_image[MONSTER_IDLE].shadow = IMAGEMANAGER->findImage("Mask_walk");
	_image[MONSTER_MOVE].img = IMAGEMANAGER->findImage("Mask_walk");
	_image[MONSTER_MOVE].shadow = IMAGEMANAGER->findImage("Mask_walk");
	_image[MONSTER_HIT].img = IMAGEMANAGER->findImage("Mask_hit");
	_image[MONSTER_HIT].shadow = IMAGEMANAGER->findImage("Mask_hit");
	_image[MONSTER_DEAD].img = IMAGEMANAGER->findImage("bloodBlob");
	_image[MONSTER_DEAD].shadow = IMAGEMANAGER->addImage("blank", _image[MONSTER_DEAD].img->getWidth(), _image[MONSTER_DEAD].img->getHeight());
	_image[MONSTER_ITEM].img = IMAGEMANAGER->findImage("g_bubble");
	_image[MONSTER_ITEM].shadow = IMAGEMANAGER->findImage("g_bubble");
	_speed = 2.0f;
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
	_isFrameImg = true;
	_state = MONSTER_IDLE;
}

void mask::release()
{
	_hpBar->release();
	SAFE_DELETE(_hpBar);
}

void mask::idle()
{
	_angle = _isLeft * PI;
	_x += cosf(_angle) * _speed;

	_hpBar->setPosition(_x, _image[_state].rc.bottom + 15);
}

void mask::move()
{
	_angle = _isLeft * PI;

	_hpBar->setPosition(_x, _image[_state].rc.bottom + 15);
}

void mask::hit()
{
	_hpBar->setPosition(_x, _image[_state].rc.bottom + 15);

	_angle = !_isLeft * PI;
	_x += cosf(_angle) * _speed * 1.5f;

	if (_statusCount < 20)
		_statusCount++;
	else
		_state = MONSTER_IDLE;
}

void mask::dead()
{
	if ((_isLeft && _index <= 0) || (!_isLeft && _index >= _image[_state].img->getMaxFrameX()))
	{
		_state = MONSTER_ITEM;
	}
}

void mask::item()
{
	if (_isFrameImg)
	{
		_angle = RND->getFromFloatTo(PI_4, PI_4 * 3);
		_speed = RND->getFromFloatTo(6, 10);
		_gravity = 0.0f;
		_isFrameImg = false;
	}

	_x += cosf(_angle) * _speed;
	_y += -sinf(_angle) * _speed;
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
	case THIEF_BOOMERANG:
		_monster = new thief_boomerang;
		break;
	case MASK:
		_monster = new mask;
		break;
	default:
		//누구냐 넌??
		break;
	}

	_monster->init();
	_monster->setType(type);

	return _monster;
}
