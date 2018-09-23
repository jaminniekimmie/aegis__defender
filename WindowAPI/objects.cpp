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
	case OBJECT_INACTIVE:
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
			_image[_state].shadow->alphaFrameRender(hdc, _x - CAMERAMANAGER->getCamera().left, _y - CAMERAMANAGER->getCamera().top, 80);
			_image[_state].img->frameRender(hdc, _x - CAMERAMANAGER->getCamera().left, _y - CAMERAMANAGER->getCamera().top);

		}
		else
		{
			_image[_state].shadow->alphaRender(hdc, _x - CAMERAMANAGER->getCamera().left, _y - CAMERAMANAGER->getCamera().top, 80);
			_image[_state].img->render(hdc, _x - CAMERAMANAGER->getCamera().left, _y - CAMERAMANAGER->getCamera().top);
		}
	}
	if (KEYMANAGER->isToggleKey('Y'))
	{
		Rectangle(hdc, _image[_state].rc.left - CAMERAMANAGER->getCamera().left, _image[_state].rc.top - CAMERAMANAGER->getCamera().top, _image[_state].rc.right - CAMERAMANAGER->getCamera().left, _image[_state].rc.bottom - CAMERAMANAGER->getCamera().top);
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
}

void bloomFlower::move()
{
}

void mineral::init()
{
	_image[OBJECT_IDLE].img = IMAGEMANAGER->findImage("resource_yellowMineral");
	_image[OBJECT_IDLE].shadow = IMAGEMANAGER->findImage("resource_yellowMineral_shadow");
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
}

void mineral::move()
{
}

void blueFlower::init()
{
	_image[OBJECT_IDLE].img = IMAGEMANAGER->findImage("resource_blueFlowers");
	_image[OBJECT_IDLE].shadow = IMAGEMANAGER->findImage("resource_blueFlowers_shadow");
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
}

void blueFlower::move()
{
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
}

void door_DNA_yellow_left::move()
{
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
}

void door_DNA_yellow_right::move()
{
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
}

void door_DNA_blue_left::move()
{
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
}

void door_DNA_blue_right::move()
{
}

void door_elevator::init()
{
	_image[OBJECT_IDLE].img = IMAGEMANAGER->findImage("door_elevator");
	_image[OBJECT_IDLE].shadow = IMAGEMANAGER->findImage("door_elevator");
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
	_index = 0;
	_image[_state].img->setFrameX(_index);
}

void door_elevator::move()
{
	if (_index >= _image[_state].img->getMaxFrameX())
		_index = _image[_state].img->getMaxFrameX();
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
	_isFrameImg = true;
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
	_speed = 3.0f;
	_angle = PI_2;
	_gravity = 0.0f;
	_count = 0, _index = 0;
	_range = 100;
	_oldX = _x;
	_oldY = _y;
	_attackCount = 0;
	_isActive = false;
	_frameSpeed = 5;
	_isLeft = false;
	_isFrameImg = false;
	_state = OBJECT_IDLE;

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			tagElement element;
			element.elementImg = IMAGEMANAGER->findImage("fx_smoke" + to_string(j + 1));
			element.x = element.fireX = _x;
			element.y = element.fireY = _y;

			_vElement.push_back(element);
		}
	}
}

void vent::idle()
{
	if (_attackCount < 200)
		_attackCount++;
	else
		_state = OBJECT_MOVE;
}

void vent::move()
{
	for (int i = 0; i < _vElement.size(); i++)
	{
		_vElement[i].x += cosf(_angle + RND->getFloat(5)) * _speed;
		_vElement[i].y += -sinf(_angle) * _speed;

		if (getDistance(_vElement[i].fireX, _vElement[i].fireY, _vElement[i].x, _vElement[i].y) > _range)
		{
			_vElement[i].x = _vElement[i].fireX;
			_vElement[i].y = _vElement[i].fireY;
			_state = OBJECT_IDLE;
			_attackCount = 0;
		}
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
	default:
		//´©±¸³Ä ³Í??
		break;
	}
	_object->init();
	_object->setType(type);

	return _object;
}