#include "stdafx.h"
#include "objectManager.h"
#include "playerManager.h"


HRESULT objectManager::init(int num)
{
	_factory = new objectFactory;

	if (num == 1)
	{
		OBJECTTYPE type;

		_chipGreenPos[0].x = 1478, _chipGreenPos[0].y = 920;
		_chipGreenPos[1].x = 2043, _chipGreenPos[1].y = 1104;
		_chipGreenPos[2].x = 2043, _chipGreenPos[2].y = 1144;
		_chipGreenPos[3].x = 2043, _chipGreenPos[3].y = 1184;
		_chipGreenPos[4].x = 3427, _chipGreenPos[4].y = 370;
		_chipGreenPos[5].x = 3427, _chipGreenPos[5].y = 450;
		_chipGreenPos[6].x = 3895, _chipGreenPos[6].y = 610;

		for (int i = 0; i < 7; i++)
		{
			type = CHIP_GREEN;

			objects* object = _factory->createObject(type);
			object->setPosition(_chipGreenPos[i].x, _chipGreenPos[i].y);

			_vObject.push_back(object);
		}

		_chipBluePos[0].x = 1965, _chipBluePos[0].y = 1360;
		_chipBluePos[1].x = 2280, _chipBluePos[1].y = 1360;
		_chipBluePos[2].x = 2890, _chipBluePos[2].y = 305;
		_chipBluePos[3].x = 2890 + 44, _chipBluePos[3].y = 305;
		_chipBluePos[4].x = 2890 + 44 * 2, _chipBluePos[4].y = 305;
		_chipBluePos[5].x = 3545, _chipBluePos[5].y = 1365;
		_chipBluePos[6].x = 3665, _chipBluePos[6].y = 1330;
		_chipBluePos[7].x = 5880, _chipBluePos[7].y = 1260;

		for (int i = 0; i < 8; i++)
		{
			type = CHIP_BLUE;

			objects* object = _factory->createObject(type);
			object->setPosition(_chipBluePos[i].x, _chipBluePos[i].y);

			_vObject.push_back(object);
		}

		_chipPurplePos[0].x = 5950, _chipPurplePos[0].y = 1400;

		for (int i = 0; i < 1; i++)
		{
			type = CHIP_PURPLE;

			objects* object = _factory->createObject(type);
			object->setPosition(_chipPurplePos[i].x, _chipPurplePos[i].y);

			_vObject.push_back(object);
		}

		_heartYellowPos[0].x = 3702, _heartYellowPos[0].y = 1024;

		for (int i = 0; i < 1; i++)
		{
			type = HEART_YELLOW;

			objects* object = _factory->createObject(type);
			object->setPosition(_heartYellowPos[i].x, _heartYellowPos[i].y);

			_vObject.push_back(object);
		}

		_bloomFlowerPos[0].x = 4355, _bloomFlowerPos[0].y = 1255;
		_bloomFlowerPos[1].x = 4500, _bloomFlowerPos[1].y = 1255;
		_bloomFlowerPos[2].x = 4830, _bloomFlowerPos[2].y = 1255;
		_bloomFlowerPos[3].x = 4920, _bloomFlowerPos[3].y = 1255;
		_bloomFlowerPos[4].x = 5300, _bloomFlowerPos[4].y = 775;
		_bloomFlowerPos[5].x = 5635, _bloomFlowerPos[5].y = 215;
		_bloomFlowerPos[6].x = 6105, _bloomFlowerPos[6].y = 550;

		for (int i = 0; i < 7; i++)
		{
			type = BLOOMFLOWER;

			objects* object = _factory->createObject(type);
			object->setPosition(_bloomFlowerPos[i].x, _bloomFlowerPos[i].y);

			_vObject.push_back(object);
		}

		_mineralPos[0].x = 5197, _mineralPos[0].y = 521;
		_mineralPos[1].x = 6240, _mineralPos[1].y = 518;

		for (int i = 0; i < 2; i++)
		{
			type = MINERAL;

			objects* object = _factory->createObject(type);
			object->setPosition(_mineralPos[i].x, _mineralPos[i].y);

			_vObject.push_back(object);
		}

		_blueFlowerPos[0].x = 6380, _blueFlowerPos[0].y = 155;

		for (int i = 0; i < 1; i++)
		{
			type = BLUEFLOWER;

			objects* object = _factory->createObject(type);
			object->setPosition(_blueFlowerPos[i].x, _blueFlowerPos[i].y);

			_vObject.push_back(object);
		}

		 _doorDNAyellowLeftPos[0].x = 5760, _doorDNAyellowLeftPos[0].y = 907;

		for (int i = 0; i < 1; i++)
		{
			type = DOOR_DNA_YELLOW_LEFT;

			objects* object = _factory->createObject(type);
			object->setPosition(_doorDNAyellowLeftPos[i].x, _doorDNAyellowLeftPos[i].y);

			_vObject.push_back(object);
		}

		_doorDNAyellowRightPos[0].x = 5476, _doorDNAyellowRightPos[0].y = 63;

		for (int i = 0; i < 1; i++)
		{
			type = DOOR_DNA_YELLOW_RIGHT;

			objects* object = _factory->createObject(type);
			object->setPosition(_doorDNAyellowRightPos[i].x, _doorDNAyellowRightPos[i].y);

			_vObject.push_back(object);
		}

		_doorDNAblueLeftPos[0].x = 5760, _doorDNAblueLeftPos[0].y = 429;

		for (int i = 0; i < 1; i++)
		{
			type = DOOR_DNA_BLUE_LEFT;

			objects* object = _factory->createObject(type);
			object->setPosition(_doorDNAblueLeftPos[i].x, _doorDNAblueLeftPos[i].y);

			_vObject.push_back(object);
		}

		_doorDNAblueRightPos[0].x = 5397, _doorDNAblueRightPos[0].y = 665;

		for (int i = 0; i < 1; i++)
		{
			type = DOOR_DNA_BLUE_RIGHT;

			objects* object = _factory->createObject(type);
			object->setPosition(_doorDNAblueRightPos[i].x, _doorDNAblueRightPos[i].y);

			_vObject.push_back(object);
		}

		_spawnerPos[0].x = 4167, _spawnerPos[0].y = 331;
		_spawnerPos[1].x = 5012, _spawnerPos[1].y = 331;

		for (int i = 0; i < 2; i++)
		{
			type = SPAWNER;

			objects* object = _factory->createObject(type);
			object->setPosition(_spawnerPos[i].x, _spawnerPos[i].y);

			_vObject.push_back(object);
		}

		_bushSpikesPos[0].x = 3630, _bushSpikesPos[0].y = 454;

		for (int i = 0; i < 1; i++)
		{
			type = BUSH_SPIKES;

			objects* object = _factory->createObject(type);
			object->setPosition(_bushSpikesPos[i].x, _bushSpikesPos[i].y);

			_vObject.push_back(object);
		}

		_switchHorPos[0].x = 3932, _switchHorPos[0].y = 817;
		_switchHorPos[1].x = 4588, _switchHorPos[1].y = 230;
		
		for (int i = 0; i < 2; i++)
		{
			type = SWITCH_HOR;

			objects* object = _factory->createObject(type);
			object->setPosition(_switchHorPos[i].x, _switchHorPos[i].y);
			object->init();

			_vObject.push_back(object);
		}

		_switchVertPos[0].x = 5137, _switchVertPos[0].y = 1061;
		_switchVertPos[1].x = 5975, _switchVertPos[1].y = 712;

		for (int i = 0; i < 2; i++)
		{
			type = SWITCH_VERT;

			objects* object = _factory->createObject(type);
			object->setPosition(_switchVertPos[i].x, _switchVertPos[i].y);
			object->init();

			_vObject.push_back(object);
		}

		_doorElevatorPos[0].x = 4505, _doorElevatorPos[0].y = 1093;

		for (int i = 0; i < 1; i++)
		{
			type = DOOR_ELEVATOR;

			objects* object = _factory->createObject(type);
			object->setPosition(_doorElevatorPos[i].x, _doorElevatorPos[i].y);

			_vObject.push_back(object);
		}

		_ventPos[0].x = 1245, _ventPos[0].y = 1422, _ventRange[0] = 350;
		_ventPos[1].x = 1985, _ventPos[1].y = 1420, _ventRange[1] = 350;
		_ventPos[2].x = 3120, _ventPos[2].y = 1250, _ventRange[2] = 295;
		_ventPos[3].x = 3048, _ventPos[3].y = 674, _ventRange[3] = 350;
		_ventPos[4].x = 3363, _ventPos[4].y = 547, _ventRange[4] = 95;
		_ventPos[5].x = 3626, _ventPos[5].y = 680, _ventRange[5] = 95;
		_ventPos[6].x = 3608, _ventPos[6].y = 1402, _ventRange[6] = 196;
		_ventPos[7].x = 4668, _ventPos[7].y = 1256, _ventRange[7] = 456;
		_ventPos[8].x = 5277, _ventPos[8].y = 520, _ventRange[8] = 350;
		_ventPos[9].x = 6227, _ventPos[9].y = 929, _ventRange[9] = 198;
		_ventPos[10].x = 5866, _ventPos[10].y = 308, _ventRange[10] = 204;
		_ventPos[11].x = 6588, _ventPos[11].y = 655, _ventRange[11] = 180;
		_ventPos[12].x = 6709, _ventPos[12].y = 664, _ventRange[12] = 180;
		_ventPos[13].x = 6831, _ventPos[13].y = 655, _ventRange[13] = 180;

		for (int i = 0; i < 14; i++)
		{
			type = VENT;

			objects* object = _factory->createObject(type);
			object->setPosition(_ventPos[i].x, _ventPos[i].y);
			//object->init();

			_vObject.push_back(object);
		}


		_isGameClear = false;
	}

	_alpha = 0;
	_isHit = false;

	return S_OK;
}

void objectManager::release()
{
	_vObject.clear();

	for (int i = 0; i < _vObject.size(); i++)
		_vObject[i]->release();
}

void objectManager::update()
{
	RECT rcTemp;
	RECT rcPlayer = _playerManager->getPlayer()->getRect();
	int activatorCount = 0;
	float angle, speed, smlRand, centerX, centerY, targetX, targetY;

	for (int i = 0; i < _vObject.size(); i++)
	{
		if (OBJECT_VANISH == _vObject[i]->getState()) continue;
		
		if (CHIP_GREEN <= _vObject[i]->getType() && _vObject[i]->getType() <= HEART_YELLOW)
		{
			if (IntersectRect(&rcTemp, &rcPlayer, &_vObject[i]->getRect()))
			{
				EFFECTMANAGER->play("ellipsePuff" + to_string(RND->getFromIntTo(1, 5)), _vObject[i]->getX(), _vObject[i]->getY());
				SOUNDMANAGER->play("UI_collect_common");
				_vObject[i]->setState(OBJECT_VANISH);

				if (HEART_RED == _vObject[i]->getType())
					_playerManager->getPlayer()->addHp();
				else if (HEART_YELLOW == _vObject[i]->getType())
					_playerManager->getPlayer()->addMp();

				break;
			}
		}
		else if (BLOOMFLOWER <= _vObject[i]->getType() && _vObject[i]->getType() <= BLUEFLOWER)
		{
			if (OBJECT_ITEM == _vObject[i]->getState())
			{
				if (IntersectRect(&rcTemp, &rcPlayer, &_vObject[i]->getRect()))
				{
					EFFECTMANAGER->play("ellipsePuff" + to_string(RND->getFromIntTo(1, 5)), _vObject[i]->getX(), _vObject[i]->getY());
					SOUNDMANAGER->play("UI_collect_bloomflower");
					_vObject[i]->setState(OBJECT_VANISH);

					if (BLOOMFLOWER == _vObject[i]->getType())
						_playerManager->getPlayer()->addHp();
					else if (MINERAL == _vObject[i]->getType())
						_playerManager->addMineral();
					else if (BLUEFLOWER == _vObject[i]->getType())
						_playerManager->addBlueFlower();

					break;
				}
			}
			else
			{
				this->collisionBullet(i, _playerManager->getBullet()->getVBullet(), OBJECT_MOVE);
				this->collisionBullet(i, _playerManager->getTriBullet()->getVBullet(), OBJECT_MOVE);
				this->collisionBullet(i, _playerManager->getArrow()->getVArrow(), OBJECT_MOVE);
				this->collisionBullet(i, _playerManager->getTriArrow()->getVArrow(), OBJECT_MOVE);
			}
		}
		else if (VENT == _vObject[i]->getType())
		{
			speed = 12;
			
			if (IntersectRect(&rcTemp, &rcPlayer, &_vObject[i]->getActionRect()))
			{
				if (rcPlayer.bottom - speed <= _vObject[i]->getActionRect().top)
					_playerManager->getPlayer()->setY(_vObject[i]->getActionRect().top - _playerManager->getPlayer()->getPlayerImage()->getFrameHeight() * 0.5f + 2);
				else
					_playerManager->getPlayer()->setY(_playerManager->getPlayer()->getY() - speed);

				_playerManager->getPlayer()->setGravity(0);
				_playerManager->getPlayer()->setIsJump(true);
				_playerManager->getPlayer()->setOnLand(false);

				//break;
			}
		}
		else if (BUSH_SPIKES == _vObject[i]->getType())
		{
			if (IntersectRect(&rcTemp, &rcPlayer, &_vObject[i]->getRect())
				&& _playerManager->getPlayer()->getIsActive() && HIT != _playerManager->getPlayer()->getState())
			{
				angle = !_playerManager->getPlayer()->getIsLeft() * PI;
				speed = 15.0f;
				smlRand = RND->getFromIntTo(1, 2);

				EFFECTMANAGER->play("number_red" + to_string(smlRand), _playerManager->getPlayer()->getX(), rcPlayer.top);
				_playerManager->getPlayer()->setX(_playerManager->getPlayer()->getX() + cosf(angle) * speed);
				_playerManager->getPlayer()->hitDamage(smlRand);
				_playerManager->getPlayer()->setState(HIT);
				_playerManager->getPlayer()->setIsActive(false);
				_isHit = true;

				break;
			}
		}
		else if (SWITCH_HOR == _vObject[i]->getType())
		{
			if (IntersectRect(&rcTemp, &_playerManager->getPlayer(CLU)->getRect(), &_vObject[i]->getActionRect()) ||
				IntersectRect(&rcTemp, &_playerManager->getPlayer(BART)->getRect(), &_vObject[i]->getActionRect()))
			{
				if (_vObject[i]->getIndex() == 0 && _vObject[i]->getCount() % _vObject[i]->getFrameSpeed() == 0)
					SOUNDMANAGER->play("Prop_Button_slam");
				_vObject[i]->setState(OBJECT_MOVE);
				
				//break;
			}
			else
			{
				_vObject[i]->setState(OBJECT_IDLE);
				_vObject[i]->setIndex(0);
			}
			if (_vObject[i]->getIndex() == _vObject[i]->getImage()->getMaxFrameX())
				activatorCount++;
		}
		else if (SWITCH_VERT == _vObject[i]->getType())
		{
			OBJECTSTATE state = _vObject[i]->getState();
			this->collisionBullet(i, _playerManager->getBullet()->getVBullet(), OBJECT_MOVE);
			this->collisionBullet(i, _playerManager->getTriBullet()->getVBullet(), OBJECT_MOVE);
			this->collisionBullet(i, _playerManager->getArrow()->getVArrow(), OBJECT_MOVE);
			this->collisionBullet(i, _playerManager->getTriArrow()->getVArrow(), OBJECT_MOVE);
			if (state != _vObject[i]->getState() && _vObject[i]->getState() == OBJECT_MOVE)
			{
				SOUNDMANAGER->play("Prop_Button_slam");
				CAMERAMANAGER->CameraBoomerang(_playerManager->getPlayer()->getX(), _playerManager->getPlayer()->getY(), _vObject[i]->getX(), _vObject[i]->getY());
			}

			if (_vObject[i]->getIndex() == _vObject[i]->getImage()->getMaxFrameX())
				activatorCount++;
		}
		else if (DOOR_DNA_YELLOW_LEFT == _vObject[i]->getType() || DOOR_DNA_YELLOW_RIGHT == _vObject[i]->getType())
		{
			this->collisionDoorDNA(i, CLU); 

			if (IntersectRect(&rcTemp, &_playerManager->getPlayer(BART)->getRect(), &_vObject[i]->getActionRect()))
			{
				SOUNDMANAGER->play("Prop_Door_DNA_enter");

				break;
			}
		}
		else if (DOOR_DNA_BLUE_LEFT == _vObject[i]->getType() || DOOR_DNA_BLUE_RIGHT == _vObject[i]->getType())
		{
			this->collisionDoorDNA(i, BART);

			if (IntersectRect(&rcTemp, &_playerManager->getPlayer(CLU)->getRect(), &_vObject[i]->getActionRect()))
			{
				SOUNDMANAGER->play("Prop_Door_DNA_enter");

				break;
			}
		}
		else if (DOOR_ELEVATOR == _vObject[i]->getType())
		{
			centerX = _vObject[i]->getX() + _vObject[i]->getImage()->getFrameWidth() * 0.5f;
			centerY = _vObject[i]->getY() + _vObject[i]->getImage()->getFrameHeight() * 0.5f;

			this->collisionDoorElevator(i, _playerManager->getCharacter());

			if (activatorCount >= 2 && _vObject[i]->getIndex() != _vObject[i]->getImage()->getMaxFrameX())
			{
				CAMERAMANAGER->CameraBoomerang(_playerManager->getPlayer()->getX(), _playerManager->getPlayer()->getY(), centerX, centerY);
				_vObject[i]->setState(OBJECT_MOVE);
			}
		}
		else if (SPAWNER == _vObject[i]->getType())
		{
			int index;
			centerX = _vObject[i]->getX() + _vObject[i]->getImage()->getWidth() * 0.5f;
			centerY = _vObject[i]->getY() + _vObject[i]->getImage()->getHeight() * 0.5f;

			if (IntersectRect(&rcTemp, &rcPlayer, &_vObject[i]->getActionRect()))
			{
				if (_vObject[i - 1]->getType() == SPAWNER) index = i - 1;
				else if (_vObject[i + 1]->getType() == SPAWNER) index = i + 1;
				else return;//break;

				targetX = _vObject[index]->getX() + _vObject[index]->getImage()->getWidth() * 0.5f;
				targetY = _vObject[index]->getY() + _vObject[index]->getImage()->getHeight() * 0.5f;

				CAMERAMANAGER->CameraSwitch(centerX, centerY, targetX, targetY);
				_playerManager->getPlayer()->setX(targetX);
				_playerManager->getPlayer()->setY(targetY);
			}
		}

		_vObject[i]->update();
	}
	this->collisionProcess();
}

void objectManager::render(HDC hdc)
{
	//오브젝트 벡터 돌리면서 활성화된 오브젝트들만 그려주면 된다.
	//getMemDC() 를 못쓰니까 hdc 쓰면 된다.
	for (int i = 0; i < _vObject.size(); i++)
	{
		if (OBJECT_VANISH == _vObject[i]->getState()) continue;
		_vObject[i]->render(hdc);
	}

	IMAGEMANAGER->alphaRender("solid_red", hdc, _alpha);

	//char str[32];
	//sprintf(str, "%d", count);
	//TextOut(hdc, 200, 200, str, strlen(str));
}

void objectManager::collisionProcess()
{
	if (_isHit)
	{
		if (_alpha < 90)
			_alpha += 15;
		else
			_isHit = false;
	}
	else
	{
		if (_alpha > 0)
			_alpha -= 15;
	}
}

void objectManager::collisionBullet(int index, vector<tagBullet> bullet, OBJECTSTATE setState)
{
	RECT rcTemp;

	for (int j = 0; j < bullet.size(); j++)
	{
		if (IntersectRect(&rcTemp, &bullet[j].rc, &_vObject[index]->getRect()))
		{
			EFFECTMANAGER->play("bulletPuff" + to_string(RND->getFromIntTo(1, 5)), bullet[j].rc.left, bullet[j].rc.top);
			bullet[j].fire = false;
			_vObject[index]->playerAttack();
			break;
		}
	}
}

void objectManager::collisionDoorDNA(int index, PLAYERCHARACTER character)
{
	RECT rcTemp;
	RECT rcPlayer = _playerManager->getPlayer(character)->getRect();
	if (IntersectRect(&rcTemp, &rcPlayer, &_vObject[index]->getActionRect()))
	{
		if (rcPlayer.left <= _vObject[index]->getActionRect().right &&
			rcPlayer.right > _vObject[index]->getActionRect().right &&
			rcPlayer.left > _vObject[index]->getActionRect().left &&
			rcPlayer.top <= _vObject[index]->getActionRect().bottom &&
			rcPlayer.bottom >= _vObject[index]->getActionRect().top &&
			_playerManager->getPlayer(character)->getIsLeft())
		{
			_playerManager->getPlayer(character)->setX(_playerManager->getPlayer(character)->getX() + (rcTemp.right - rcTemp.left));
			if (!_playerManager->getPlayer(character)->getIsJump())
				_playerManager->getPlayer(character)->setState(PUSH);
		}
		else if (rcPlayer.left < _vObject[index]->getActionRect().left &&
			rcPlayer.right >= _vObject[index]->getActionRect().left &&
			rcPlayer.top <= _vObject[index]->getActionRect().bottom &&
			rcPlayer.bottom >= _vObject[index]->getActionRect().top &&
			!_playerManager->getPlayer(character)->getIsLeft())
		{
			_playerManager->getPlayer(character)->setX(_playerManager->getPlayer(character)->getX() - (rcTemp.right - rcTemp.left));
			if (!_playerManager->getPlayer(character)->getIsJump())
				_playerManager->getPlayer(character)->setState(PUSH);
		}
	}
}

void objectManager::collisionDoorElevator (int index, PLAYERCHARACTER character)
{
	RECT rcTemp;
	RECT rcPlayer = _playerManager->getPlayer(character)->getRect();
	if (IntersectRect(&rcTemp, &rcPlayer, &_vObject[index]->getActionRect()))
	{
		if (rcPlayer.left <= _vObject[index]->getActionRect().right &&
			rcPlayer.right >= _vObject[index]->getActionRect().left &&
			rcPlayer.bottom >= _vObject[index]->getActionRect().top &&
			rcPlayer.top < _vObject[index]->getActionRect().top)
		{
			_playerManager->getPlayer(character)->setY(_vObject[index]->getActionRect().top - (rcPlayer.bottom - rcPlayer.top) * 0.75 + 1);
			_playerManager->getPlayer(character)->setOnLand(true);
			_playerManager->getPlayer(character)->setGravity(0);
			_playerManager->getPlayer(character)->setSpeed(0);
		}
		else if (rcPlayer.left <= _vObject[index]->getActionRect().right &&
			rcPlayer.right >= _vObject[index]->getActionRect().left &&
			rcPlayer.top <= _vObject[index]->getActionRect().bottom &&
			rcPlayer.bottom > _vObject[index]->getActionRect().bottom)
		{
			_playerManager->getPlayer(character)->setY(_playerManager->getPlayer(character)->getY() + (rcTemp.bottom - rcTemp.top));
		}
	}
}
