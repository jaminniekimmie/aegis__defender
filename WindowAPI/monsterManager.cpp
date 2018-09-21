#include "stdafx.h"
#include "monsterManager.h"
#include "playerManager.h"


HRESULT monsterManager::init(int scene)
{
	_factory = new monsterFactory;

	if (scene == 1)
	{
		MONSTERTYPE type;

		_sandwormPos[0].x = 1790 + 200, _sandwormPos[0].y = 1350;
		_sandwormPos[1].x = 3890 + 200, _sandwormPos[1].y = 1350;
		_sandwormPos[2].x = 5260 + 200, _sandwormPos[2].y = 1350;
		_sandwormPos[3].x = 5260 + 200, _sandwormPos[3].y = 1350;
		for (int i = 0; i < 4; i++)
		{
			type = SANDWORM;

			monster* monster = _factory->createMonster(type);
			monster->setPosition(_sandwormPos[i].x, _sandwormPos[i].y);
			monster->init();

			_vMonster.push_back(monster);
		}

		_spiderBabyPos[0].x = 2890 + 100, _spiderBabyPos[0].y = 1150;
		_spiderBabyPos[1].x = 3290 + 100, _spiderBabyPos[1].y = 1350;
		_spiderBabyPos[2].x = 5890 + 100, _spiderBabyPos[2].y = 300;
		_spiderBabyPos[3].x = 5690 + 100, _spiderBabyPos[3].y = 1170;
		_spiderBabyPos[4].x = 6610 + 100, _spiderBabyPos[4].y = 650;
		for (int i = 0; i < 5; i++)
		{
			type = SPIDERBABY;

			monster* monster = _factory->createMonster(type);
			monster->setPosition(_spiderBabyPos[i].x, _spiderBabyPos[i].y);
			monster->init();

			_vMonster.push_back(monster);
		}

		_firedrinkerFlyPos[0].x = 4340 + 100, _firedrinkerFlyPos[0].y = 410;
		_firedrinkerFlyPos[1].x = 5240 + 100, _firedrinkerFlyPos[1].y = 400;
		_firedrinkerFlyPos[2].x = 5220 + 100, _firedrinkerFlyPos[2].y = 1040;
		for (int i = 0; i < 3; i++)
		{
			type = FIREDRINKERFLY;

			monster* monster = _factory->createMonster(type);
			monster->setPosition(_firedrinkerFlyPos[i].x, _firedrinkerFlyPos[i].y);
			monster->init();

			_vMonster.push_back(monster);
		}

		_isGameClear = false;
	}

	return S_OK;
}

void monsterManager::release()
{
	_vMonster.clear();
}

void monsterManager::update()
{
	RECT rcTemp;
	for (int i = 0; i < _vMonster.size(); i++)
	{
	//	if ((180 / 3.14f * getAngle(_vMonster[i]->getX(), _vMonster[i]->getY(), _playerManager->getClu()->getX(), _playerManager->getClu()-/>getY/())) >= 91.f && (180 / 3.14f * getAngle(_vMonster[i]->getX(), _vMonster[i]->getY(), _playerManager->getClu()->getX(), /_playerManager-/>getClu()->getY()) <= 270.f))
	//	{
	//		_vMonster[i]->setIsLeft(true);
	//	}
	//	else
	//	{
	//		_vMonster[i]->setIsLeft(false);
	//	}
	//
		if (IntersectRect(&rcTemp, &_playerManager->getClu()->getPlayerRc(), &_vMonster[i]->getRect(_vMonster[i]->getState())))
		{

		}

		_vMonster[i]->update();
	}
}

void monsterManager::render(HDC hdc)
{
	for (int i = 0; i < _vMonster.size(); i++)
	{
		if (_vMonster[i]->getState() == MONSTER_DEAD) continue;
		_vMonster[i]->render(hdc);
	}
}
void monsterManager::collisionProcess()
{

}