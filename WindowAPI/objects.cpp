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

	_image[_state].rc = RectMakeCenter(_x, _y, _image[_state].img->getWidth(), _image[_state].img->getHeight());

	this->collisionProcess();
	//this->frameChange();
}

void objects::render(HDC hdc)
{
	if (CAMERAMANAGER->CameraIn(_image[_state].rc))
	{
		_image[_state].shadow->alphaRender(hdc, _x - _image[_state].shadow->getWidth() * 0.5f - CAMERAMANAGER->getCamera().left, _y - _image[_state].shadow->getHeight() * 0.5f - CAMERAMANAGER->getCamera().top, 80);
		_image[_state].img->render(hdc, _x - _image[_state].img->getWidth() * 0.5f - CAMERAMANAGER->getCamera().left, _y - _image[_state].shadow->getHeight() * 0.5f - CAMERAMANAGER->getCamera().top);
	}
	if (KEYMANAGER->isToggleKey('Y'))
	{
		Rectangle(hdc, _image[_state].rc.left - CAMERAMANAGER->getCamera().left, _image[_state].rc.top - CAMERAMANAGER->getCamera().top, _image[_state].rc.right - CAMERAMANAGER->getCamera().left, _image[_state].rc.bottom - CAMERAMANAGER->getCamera().top);
	}
}

void objects::frameChange()
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
	_isActive = true;
	_frameSpeed = 5;
	_isLeft = false;
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
	_image[OBJECT_IDLE].shadow = IMAGEMANAGER->findImage("resource_yellowMineral");
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
	_image[OBJECT_IDLE].shadow = IMAGEMANAGER->findImage("resource_blueFlowers");
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
	_state = OBJECT_IDLE;
}

void blueFlower::idle()
{
}

void blueFlower::move()
{
}

void door_DNA::init()
{
}

void door_DNA::idle()
{
}

void door_DNA::move()
{
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
	case DOOR_DNA:
		_object = new door_DNA;
		break;
	default:
		//´©±¸³Ä ³Í??
		break;
	}
	_object->init();
	_object->setType(type);

	return _object;
}
