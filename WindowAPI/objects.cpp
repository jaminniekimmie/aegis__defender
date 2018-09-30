#include "stdafx.h"
#include "objects.h"

void objects::update()
{
	switch (_state)
	{
	case OBJECT_IDLE:
		idle();
		break;
	case OBJECT_MOVE:
		move();
		break;
	case OBJECT_VANISH:
		break;
	}

	if (_isFrameImg)
		_image[_state].rc = RectMake(_x, _y, _image[_state].img->getFrameWidth(), _image[_state].img->getFrameHeight());
	else
		_image[_state].rc = RectMake(_x, _y, _image[_state].img->getWidth(), _image[_state].img->getHeight());

	this->collisionProcess();
	this->frameChange();
}

void objects::render(HDC hdc)
{
	if (CAMERAMANAGER->CameraIn(_image[_state].rc) && _isActive)
	{
		if (_isFrameImg)
		{
			_image[_state].shadow->alphaFrameRender(hdc, _x - CAMERAMANAGER->getCamera().left, _y - CAMERAMANAGER->getCamera().top, _index, _isLeft, 100);
			_image[_state].img->frameRender(hdc, _x - CAMERAMANAGER->getCamera().left, _y - CAMERAMANAGER->getCamera().top, _index, _isLeft);
		}
		else
		{
			_image[_state].shadow->alphaRender(hdc, _x - CAMERAMANAGER->getCamera().left, _y - CAMERAMANAGER->getCamera().top, 100);
			_image[_state].img->render(hdc, _x - CAMERAMANAGER->getCamera().left, _y - CAMERAMANAGER->getCamera().top);
		}
	}

	if (KEYMANAGER->isToggleKey('Y'))
	{
		Rectangle(hdc, _actionRc.left - CAMERAMANAGER->getCamera().left, _actionRc.top - CAMERAMANAGER->getCamera().top, _actionRc.right - CAMERAMANAGER->getCamera().left, _actionRc.bottom - CAMERAMANAGER->getCamera().top);
	}
	
	for (int i = 0; i < _vElement.size(); i++)
	{
		if (!CAMERAMANAGER->CameraIn(_vElement[i].rc)) continue;

		_vElement[i].elementImg->alphaRender(hdc, _vElement[i].rc.left - CAMERAMANAGER->getCamera().left, _vElement[i].rc.top - CAMERAMANAGER->getCamera().top, _vElement[i].alpha);

	}
}

void objects::frameChange()
{
	if (_isFrameImg && _state == OBJECT_MOVE)
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
}

void objects::collisionProcess()
{
}

void objects::playerAttack()
{
	_attackCount--;

	if (_attackCount > 0)
		_state = OBJECT_MOVE;
	else
	{
		_state = OBJECT_VANISH;
	}
}

void chip_green::init()
{
	_image[OBJECT_IDLE].img = IMAGEMANAGER->findImage("collectibleChip_green");
	_image[OBJECT_IDLE].shadow = IMAGEMANAGER->findImage("collectibleChip_green");
	_speed = 8.0f;
	_angle = 0.0f;
	_gravity = 0.0f;
	_count = 0, _index = 0;
	_range = 0;
	_oldX = _x;
	_oldY = _y;
	_isActive = true;
	_frameSpeed = 5;
	_isLeft = false;
	_isFrameImg = false;
	_state = OBJECT_IDLE;
}

void chip_green::idle()
{
}

void chip_green::move()
{
}

void chip_blue::init()
{
	_image[OBJECT_IDLE].img = IMAGEMANAGER->findImage("collectibleChip_blue");
	_image[OBJECT_IDLE].shadow = IMAGEMANAGER->findImage("collectibleChip_blue");
	_speed = 8.0f;
	_angle = 0.0f;
	_gravity = 0.0f;
	_count = 0, _index = 0;
	_range = 0;
	_oldX = _x;
	_oldY = _y;
	_isActive = true;
	_frameSpeed = 5;
	_isLeft = false;
	_isFrameImg = false;
	_state = OBJECT_IDLE;
}

void chip_blue::idle()
{
}

void chip_blue::move()
{
}

void chip_purple::init()
{
	_image[OBJECT_IDLE].img = IMAGEMANAGER->findImage("collectibleChip_purple");
	_image[OBJECT_IDLE].shadow = IMAGEMANAGER->findImage("collectibleChip_purple");
	_speed = 8.0f;
	_angle = 0.0f;
	_gravity = 0.0f;
	_count = 0, _index = 0;
	_range = 0;
	_oldX = _x;
	_oldY = _y;
	_isActive = true;
	_frameSpeed = 5;
	_isLeft = false;
	_isFrameImg = false;
	_state = OBJECT_IDLE;
}

void chip_purple::idle()
{
}

void chip_purple::move()
{
}

void chip_white::init()
{
	_image[OBJECT_IDLE].img = IMAGEMANAGER->findImage("collectibleChip_white");
	_image[OBJECT_IDLE].shadow = IMAGEMANAGER->findImage("collectibleChip_white");
	_speed = 8.0f;
	_angle = 0.0f;
	_gravity = 0.0f;
	_count = 0, _index = 0;
	_range = 0;
	_oldX = _x;
	_oldY = _y;
	_isActive = true;
	_frameSpeed = 5;
	_isLeft = false;
	_isFrameImg = false;
	_state = OBJECT_IDLE;
}

void chip_white::idle()
{
}

void chip_white::move()
{
}

void heart_red::init()
{
	_image[OBJECT_IDLE].img = IMAGEMANAGER->findImage("heart_red");
	_image[OBJECT_IDLE].shadow = IMAGEMANAGER->findImage("heart_red");
	_speed = 8.0f;
	_angle = 0.0f;
	_gravity = 0.0f;
	_count = 0, _index = 0;
	_range = 0;
	_oldX = _x;
	_oldY = _y;
	_isActive = true;
	_frameSpeed = 5;
	_isLeft = false;
	_isFrameImg = false;
	_state = OBJECT_IDLE;
}

void heart_red::idle()
{
}

void heart_red::move()
{
}

void heart_yellow::init()
{
	_image[OBJECT_IDLE].img = IMAGEMANAGER->findImage("heart_yellow");
	_image[OBJECT_IDLE].shadow = IMAGEMANAGER->findImage("heart_yellow");
	_speed = 8.0f;
	_angle = 0.0f;
	_gravity = 0.0f;
	_count = 0, _index = 0;
	_range = 0;
	_oldX = _x;
	_oldY = _y;
	_isActive = true;
	_frameSpeed = 5;
	_isLeft = false;
	_isFrameImg = false;
	_state = OBJECT_IDLE;
}

void heart_yellow::idle()
{
}

void heart_yellow::move()
{
}

void bloomFlower::init()
{
	_image[OBJECT_IDLE].img = IMAGEMANAGER->findImage("resource_redFlower");
	_image[OBJECT_IDLE].shadow = IMAGEMANAGER->findImage("resource_redFlower");
	_image[OBJECT_MOVE].img = IMAGEMANAGER->findImage("resource_redFlower_hit");
	_image[OBJECT_MOVE].shadow = IMAGEMANAGER->findImage("resource_redFlower");
	_speed = 8.0f;
	_angle = 0.0f;
	_gravity = 0.0f;
	_count = 0, _index = 0;
	_range = 0;
	_oldX = _x;
	_oldY = _y;
	_attackCount = 3;
	_isActive = true;
	_frameSpeed = 5;
	_isLeft = false;
	_isFrameImg = false;
	_state = OBJECT_IDLE;
}

void bloomFlower::idle()
{
	_oldX = _x;
	_oldY = _y;
}

void bloomFlower::move()
{
	if (_oldY == _y)
		_y -= 10;
	else
	{
		_y = _oldY;
		_state = OBJECT_IDLE;
	}
}

void mineral::init()
{
	_image[OBJECT_IDLE].img = IMAGEMANAGER->findImage("resource_yellowMineral");
	_image[OBJECT_IDLE].shadow = IMAGEMANAGER->findImage("resource_yellowMineral_shadow");
	_image[OBJECT_MOVE].img = IMAGEMANAGER->findImage("resource_yellowMineral_hit");
	_image[OBJECT_MOVE].shadow = IMAGEMANAGER->findImage("resource_yellowMineral_shadow");
	_speed = 8.0f;
	_angle = 0.0f;
	_gravity = 0.0f;
	_count = 0, _index = 0;
	_range = 0;
	_oldX = _x;
	_oldY = _y;
	_attackCount = 3;
	_isActive = true;
	_frameSpeed = 5;
	_isLeft = false;
	_isFrameImg = false;
	_state = OBJECT_IDLE;
}

void mineral ::idle()
{
	_oldX = _x;
	_oldY = _y;
}

void mineral::move()
{
	if (_oldY == _y)
		_y -= 10;
	else
	{
		_y = _oldY;
		_state = OBJECT_IDLE;
	}
}

void blueFlower::init()
{
	_image[OBJECT_IDLE].img = IMAGEMANAGER->findImage("resource_blueFlowers");
	_image[OBJECT_IDLE].shadow = IMAGEMANAGER->findImage("resource_blueFlowers_shadow");
	_image[OBJECT_MOVE].img = IMAGEMANAGER->findImage("resource_blueFlowers_hit");
	_image[OBJECT_MOVE].shadow = IMAGEMANAGER->findImage("resource_blueFlowers_shadow");
	_speed = 8.0f;
	_angle = 0.0f;
	_gravity = 0.0f;
	_count = 0, _index = 0;
	_range = 0;
	_oldX = _x;
	_oldY = _y;
	_attackCount = 3;
	_isActive = true;
	_frameSpeed = 5;
	_isLeft = false;
	_isFrameImg = false;
	_state = OBJECT_IDLE;
}

void blueFlower::idle()
{
	_oldX = _x;
	_oldY = _y;
}

void blueFlower::move()
{
	if (_oldY == _y)
		_y -= 10;
	else
	{
		_y = _oldY;
		_state = OBJECT_IDLE;
	}
}

void spawner::init()
{
	_image[OBJECT_IDLE].img = IMAGEMANAGER->findImage("spawner");
	_image[OBJECT_IDLE].shadow = IMAGEMANAGER->findImage("spawner");
	_speed = 8.0f;
	_angle = 0.0f;
	_gravity = 0.0f;
	_count = 0, _index = 0;
	_range = 0;
	_oldX = _x;
	_oldY = _y;
	_isActive = true;
	_frameSpeed = 5;
	_isLeft = false;
	_isFrameImg = false;
	_state = OBJECT_IDLE;
}

void spawner::idle()
{
}

void spawner::move()
{
}

void door_DNA_yellow_left::init()
{
	_image[OBJECT_IDLE].img = IMAGEMANAGER->findImage("door_DNA_yellow_left");
	_image[OBJECT_IDLE].shadow = IMAGEMANAGER->findImage("door_DNA_yellow_left");
	_speed = 8.0f;
	_angle = 0.0f;
	_gravity = 0.0f;
	_count = 0, _index = 0;
	_range = 0;
	_oldX = _x;
	_oldY = _y;
	_isActive = true;
	_frameSpeed = 5;
	_isLeft = false;
	_isFrameImg = false;
	_state = OBJECT_IDLE;
}

void door_DNA_yellow_left::idle()
{
	_actionRc = RectMake(_x + _image[_state].img->getWidth() * 0.5f, _y, _image[_state].img->getWidth() * 0.5f, _image[_state].img->getHeight());
}

void door_DNA_yellow_left::move()
{
	_actionRc = RectMake(_x, _y, 0, 0);
}

void door_DNA_yellow_right::init()
{
	_image[OBJECT_IDLE].img = IMAGEMANAGER->findImage("door_DNA_yellow_right");
	_image[OBJECT_IDLE].shadow = IMAGEMANAGER->findImage("door_DNA_yellow_right");
	_speed = 8.0f;
	_angle = 0.0f;
	_gravity = 0.0f;
	_count = 0, _index = 0;
	_range = 0;
	_oldX = _x;
	_oldY = _y;
	_isActive = true;
	_frameSpeed = 5;
	_isLeft = false;
	_isFrameImg = false;
	_state = OBJECT_IDLE;
}

void door_DNA_yellow_right::idle()
{
	_actionRc = RectMake(_x, _y, _image[_state].img->getWidth() * 0.5f, _image[_state].img->getHeight());
}

void door_DNA_yellow_right::move()
{
	_actionRc = RectMake(_x, _y, 0, 0);
}

void door_DNA_blue_left::init()
{
	_image[OBJECT_IDLE].img = IMAGEMANAGER->findImage("door_DNA_blue_left");
	_image[OBJECT_IDLE].shadow = IMAGEMANAGER->findImage("door_DNA_blue_left");
	_speed = 8.0f;
	_angle = 0.0f;
	_gravity = 0.0f;
	_count = 0, _index = 0;
	_range = 0;
	_oldX = _x;
	_oldY = _y;
	_isActive = true;
	_frameSpeed = 5;
	_isLeft = false;
	_isFrameImg = false;
	_state = OBJECT_IDLE;
}

void door_DNA_blue_left::idle()
{
	_actionRc = RectMake(_x + _image[_state].img->getWidth() * 0.5f, _y, _image[_state].img->getWidth() * 0.5f, _image[_state].img->getHeight());
}

void door_DNA_blue_left::move()
{
	_actionRc = RectMake(_x, _y, 0, 0);
}

void door_DNA_blue_right::init()
{
	_image[OBJECT_IDLE].img = IMAGEMANAGER->findImage("door_DNA_blue_right");
	_image[OBJECT_IDLE].shadow = IMAGEMANAGER->findImage("door_DNA_blue_right");
	_speed = 8.0f;
	_angle = 0.0f;
	_gravity = 0.0f;
	_count = 0, _index = 0;
	_range = 0;
	_oldX = _x;
	_oldY = _y;
	_isActive = true;
	_frameSpeed = 5;
	_isLeft = false;
	_isFrameImg = false;
	_state = OBJECT_IDLE;
}

void door_DNA_blue_right::idle()
{
	_actionRc = RectMake(_x, _y, _image[_state].img->getWidth() * 0.5f, _image[_state].img->getHeight());
}

void door_DNA_blue_right::move()
{
	_actionRc = RectMake(_x, _y, 0, 0);
}

void door_elevator::init()
{
	_image[OBJECT_IDLE].img = IMAGEMANAGER->findImage("door_elevator");
	_image[OBJECT_IDLE].shadow = IMAGEMANAGER->findImage("door_elevator");
	_image[OBJECT_MOVE].img = IMAGEMANAGER->findImage("door_elevator");
	_image[OBJECT_MOVE].shadow = IMAGEMANAGER->findImage("door_elevator");
	_speed = 8.0f;
	_angle = 0.0f;
	_gravity = 0.0f;
	_count = 0, _index = 0;
	_range = 0;
	_oldX = _x;
	_oldY = _y;
	_isActive = true;
	_frameSpeed = 5;
	_isLeft = false;
	_isFrameImg = true;
	_state = OBJECT_IDLE;
}

void door_elevator::idle()
{
	_actionRc = RectMake(_x, _y + _image[_state].img->getFrameHeight() * 0.17f, _image[_state].img->getFrameWidth(), _image[_state].img->getFrameHeight() * 0.66f);
	_image[_state].img->setFrameX(_index);
}

void door_elevator::move()
{
	_actionRc = RectMake(_x, _y, 0, 0);

	if (_index >= _image[_state].img->getMaxFrameX())
	{
		_index = _image[_state].img->getMaxFrameX();
		_image[_state].img->setFrameX(_index);
		_state = OBJECT_IDLE;
	}
}

void bush_spikes::init()
{
	_image[OBJECT_IDLE].img = IMAGEMANAGER->findImage("bush_spikes_upsideDown");
	_image[OBJECT_IDLE].shadow = IMAGEMANAGER->findImage("bush_spikes_upsideDown");
	_speed = 8.0f;
	_angle = 0.0f;
	_gravity = 0.0f;
	_count = 0, _index = 0;
	_range = 0;
	_oldX = _x;
	_oldY = _y;
	_isActive = true;
	_frameSpeed = 5;
	_isLeft = false;
	_isFrameImg = false;
	_state = OBJECT_IDLE;
}

void bush_spikes::idle()
{
}

void bush_spikes::move()
{
}

void vent::init()
{
	_image[OBJECT_IDLE].img = IMAGEMANAGER->findImage("vent");
	_image[OBJECT_IDLE].shadow = IMAGEMANAGER->findImage("vent");
	_image[OBJECT_MOVE].img = IMAGEMANAGER->findImage("vent");
	_image[OBJECT_MOVE].shadow = IMAGEMANAGER->findImage("vent");
	_speed = 3.0f;
	_angle = PI_2;
	_gravity = 0.0f;
	_count = 0, _index = 0;
	_range = 300;
	_oldX = _x;
	_oldY = _y;
	_attackCount = 0;
	_isActive = false;
	_frameSpeed = 5;
	_randNo = RND->getFromIntTo(100, 200);
	_isLeft = false;
	_isFrameImg = false;
	_state = OBJECT_IDLE;
}

void vent::idle()
{
	_actionRc = RectMake(_x, _y, _image[_state].img->getWidth(), 0);

	if (_attackCount < _randNo)
		_attackCount++;
	else
	{
		_state = OBJECT_MOVE;
		_randNo = RND->getFromIntTo(100, 200);
		_attackCount = 0;

		for (int i = 0; i < 20; i++)
		{
			int rand = RND->getFloat(_image[_state].img->getWidth());
			float speed = RND->getFromFloatTo(1, 4.5);
			for (int j = 0; j < 5; j++)
			{
				tagElement element;
				ZeroMemory(&element, sizeof(tagElement));
				element.elementImg = IMAGEMANAGER->findImage("fx_smoke" + to_string(j + 1));
				element.x = element.fireX = _x + rand;
				element.y = element.fireY = _y;
				element.speed = speed;
				element.alpha = (j + 1) * 20;
				element.fire = false;
				element.rc = RectMakeCenter(element.x, element.y, element.elementImg->getWidth(), element.elementImg->getHeight());

				_vElement.push_back(element);
			}
		}
	}
}

void vent::move()
{
	if (_range > (_y - _actionRc.top))
		_actionRc.top -= 4;
	else
		_actionRc.bottom -= 1.5f;

	//_actionRc = RectMake(_x, _y - _range, _image[_state].img->getWidth(), _range);

	for (int i = 0; i < _vElement.size(); i++)
	{
		_vElement[i].x += cosf(_angle) * _vElement[i].speed;
		_vElement[i].y += -sinf(_angle) * _vElement[i].speed;
		_vElement[i].rc = RectMakeCenter(_vElement[i].x, _vElement[i].y, _vElement[i].elementImg->getWidth(), _vElement[i].elementImg->getHeight());
	
		if (getDistance(_vElement[i].fireX, _vElement[i].fireY, _vElement[i].x, _vElement[i].y) > _range)
		{
			_vElement[i].alpha -= 5;

			if (_vElement[i].alpha <= 5)
			{
				_vElement.erase(_vElement.begin() + i);

				if (_vElement.empty())
				{
					_state = OBJECT_IDLE;
				}
			}
		}
	}
}

void switch_hor::init()
{
	_image[OBJECT_IDLE].img = IMAGEMANAGER->findImage("switch_hor");
	_image[OBJECT_IDLE].shadow = IMAGEMANAGER->findImage("switch_hor");
	_image[OBJECT_MOVE].img = IMAGEMANAGER->findImage("switch_hor");
	_image[OBJECT_MOVE].shadow = IMAGEMANAGER->findImage("switch_hor");
	_speed = 3.0f;
	_angle = PI_2;
	_gravity = 0.0f;
	_count = 0, _index = 0;
	_range = 300;
	_oldX = _x;
	_oldY = _y;
	_attackCount = 0;
	_isActive = true;
	_frameSpeed = 5;
	_isLeft = false;
	_isFrameImg = true;
	_state = OBJECT_IDLE;
}

void switch_hor::idle()
{
	_actionRc = RectMake(_x + 10, _y, 45, 37);
	_image[_state].img->setFrameX(_index);
}

void switch_hor::move()
{
	if (_index >= _image[_state].img->getMaxFrameX())
	{
		_index = _image[_state].img->getMaxFrameX();
		_image[_state].img->setFrameX(_index);
		_state = OBJECT_IDLE;
	}
}

void switch_vert::init()
{
	_image[OBJECT_IDLE].img = IMAGEMANAGER->findImage("switch_vert");
	_image[OBJECT_IDLE].shadow = IMAGEMANAGER->findImage("switch_vert");
	_image[OBJECT_MOVE].img = IMAGEMANAGER->findImage("switch_vert");
	_image[OBJECT_MOVE].shadow = IMAGEMANAGER->findImage("switch_vert");
	_speed = 3.0f;
	_angle = PI_2;
	_gravity = 0.0f;
	_count = 0, _index = 0;
	_range = 300;
	_oldX = _x;
	_oldY = _y;
	_attackCount = 10;
	_isActive = true;
	_frameSpeed = 5;
	_isLeft = false;
	_isFrameImg = true;
	_state = OBJECT_IDLE;
}

void switch_vert::idle()
{
	_actionRc = RectMake(_x + 17, _y + 10, 38, 46);
	_image[_state].img->setFrameX(_index);
}

void switch_vert::move()
{
	if (_index >= _image[_state].img->getMaxFrameX())
	{
		_index = _image[_state].img->getMaxFrameX();
		_state = OBJECT_IDLE;
	}
}

objects * objectFactory::createObject(OBJECTTYPE type)
{
	objects* _object;
	switch (type)
	{
	case CHIP_GREEN:
		_object = new chip_green;
		break;
	case CHIP_BLUE:
		_object = new chip_blue;
		break;
	case CHIP_PURPLE:
		_object = new chip_purple;
		break;
	case CHIP_WHITE:
		_object = new chip_white;
		break;
	case HEART_RED:
		_object = new heart_red;
		break;
	case HEART_YELLOW:
		_object = new heart_yellow;
		break;
	case BLOOMFLOWER:
		_object = new bloomFlower;
		break;
	case MINERAL:
		_object = new mineral;
		break;
	case BLUEFLOWER:
		_object = new blueFlower;
		break;
	case SPAWNER:
		_object = new spawner;
		break;
	case DOOR_DNA_YELLOW_LEFT:
		_object = new door_DNA_yellow_left;
		break;
	case DOOR_DNA_YELLOW_RIGHT:
		_object = new door_DNA_yellow_right;
		break;
	case DOOR_DNA_BLUE_LEFT:
		_object = new door_DNA_blue_left;
		break;
	case DOOR_DNA_BLUE_RIGHT:
		_object = new door_DNA_blue_right;
		break;
	case DOOR_ELEVATOR:
		_object = new door_elevator;
		break;
	case BUSH_SPIKES:
		_object = new bush_spikes;
		break;
	case VENT:
		_object = new vent;
		break;
	case SWITCH_HOR:
		_object = new switch_hor;
		break;
	case SWITCH_VERT:
		_object = new switch_vert;
		break;
	default:
		//´©±¸³Ä ³Í??
		break;
	}
	_object->init();
	_object->setType(type);

	return _object;
}
