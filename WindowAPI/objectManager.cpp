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

		_bloomFlowerPos[0].x = 4385, _bloomFlowerPos[0].y = 1245;
		_bloomFlowerPos[1].x = 4530, _bloomFlowerPos[1].y = 1245;
		_bloomFlowerPos[2].x = 4880, _bloomFlowerPos[2].y = 1245;
		_bloomFlowerPos[3].x = 4980, _bloomFlowerPos[3].y = 1245;
		_bloomFlowerPos[4].x = 5325, _bloomFlowerPos[4].y = 765;
		_bloomFlowerPos[5].x = 5664, _bloomFlowerPos[5].y = 205;
		_bloomFlowerPos[6].x = 6134, _bloomFlowerPos[6].y = 540;

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

		_doorElevatorPos[0].x = 4505, _doorElevatorPos[0].y = 1093;

		for (int i = 0; i < 1; i++)
		{
			type = DOOR_ELEVATOR;

			objects* object = _factory->createObject(type);
			object->setPosition(_doorElevatorPos[i].x, _doorElevatorPos[i].y);

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

		_ventPos[0].x = 1245, _ventPos[0].y = 1422;

		for (int i = 0; i < 1; i++)
		{
			type = VENT;

			objects* object = _factory->createObject(type);
			object->setPosition(_ventPos[i].x, _ventPos[i].y);
			object->init();

			_vObject.push_back(object);
		}

		_isGameClear = false;
	}

	return S_OK;
}

void objectManager::release()
{
	_vObject.clear();
}

void objectManager::update()
{
	RECT rcTemp;

	for (int i = 0; i < _vObject.size(); i++)
	{
		if (OBJECT_INACTIVE == _vObject[i]->getState()) continue;
		
		if (CHIP_GREEN <= _vObject[i]->getType() && _vObject[i]->getType() <= HEART_YELLOW)
		{
			if (IntersectRect(&rcTemp, &_playerManager->getClu()->getPlayerRc(), &_vObject[i]->getRect()))
			{
				EFFECTMANAGER->play("ellipsePuff" + to_string(RND->getFromIntTo(1, 5)), _vObject[i]->getX(), _vObject[i]->getY());
				_vObject[i]->setState(OBJECT_INACTIVE);
				break;
			}
		}
		else if (BLOOMFLOWER <= _vObject[i]->getType() && _vObject[i]->getType() <= BLUEFLOWER)
		{
			for (int j = 0; j < _playerManager->getBullet()->getVBullet().size(); j++)
			{
				if (IntersectRect(&rcTemp, &_playerManager->getBullet()->getVBullet()[j].rc, &_vObject[i]->getRect()))
				{
					EFFECTMANAGER->play("bulletPuff" + to_string(RND->getFromIntTo(1, 5)), _playerManager->getBullet()->getVBullet()[j].rc.left, _playerManager->getBullet()->getVBullet()[j].rc.top);
					_playerManager->getBullet()->getVBullet().erase(_playerManager->getBullet()->getVBullet().begin() + j);
					break;
				}
			}

			for (int j = 0; j < _playerManager->getTriBullet()->getVBullet().size(); j++)
			{
				if (!_playerManager->getTriBullet()->getVBullet()[j].fire) continue;

				if (IntersectRect(&rcTemp, &_playerManager->getTriBullet()->getVBullet()[j].rc, &_vObject[i]->getRect()))
				{
					EFFECTMANAGER->play("bulletPuff" + to_string(RND->getFromIntTo(1, 5)), _playerManager->getTriBullet()->getVBullet()[j].rc.left, _playerManager->getTriBullet()->getVBullet()[j].rc.top);
					_playerManager->getTriBullet()->getVBullet()[j].fire = false;
					break;
				}
			}
		}
		_vObject[i]->update();
	}
}

void objectManager::render(HDC hdc)
{
	//오브젝트 벡터 돌리면서 활성화된 오브젝트들만 그려주면 된다.
	//getMemDC() 를 못쓰니까 hdc 쓰면 된다.
	for (int i = 0; i < _vObject.size(); i++)
	{
		if (OBJECT_INACTIVE == _vObject[i]->getState()) continue;
		_vObject[i]->render(hdc);
	}
}

void objectManager::collisionProcess()
{
}