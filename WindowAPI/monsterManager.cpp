#include "stdafx.h"
#include "monsterManager.h"
#include "playerManager.h"


HRESULT monsterManager::init(int scene)
{
	_factory = new monsterFactory;

	if (scene == 1)
	{
		MONSTERTYPE type;

		_sandwormPos[0].x = 2220, _sandwormPos[0].y = 1400, _sandwormRange[0] = 350;
		_sandwormPos[1].x = 3710, _sandwormPos[1].y = 1400, _sandwormRange[1] = 350;
		_sandwormPos[2].x = 5900, _sandwormPos[2].y = 1500, _sandwormRange[2] = 750;
		_sandwormPos[3].x = 5900, _sandwormPos[3].y = 1500, _sandwormRange[3] = 750;
		for (int i = 0; i < 4; i++)
		{
			type = SANDWORM;

			monster* monster = _factory->createMonster(type);
			monster->setPosition(_sandwormPos[i].x, _sandwormPos[i].y);
			monster->setOldPosition(_sandwormPos[i].x, _sandwormPos[i].y);
			monster->setRange(_sandwormRange[i]);

			_vMonster.push_back(monster);
		}

		_spiderBabyPos[0].x = 2990, _spiderBabyPos[0].y = 1170, _spiderBabyRange[0] = 80;
		_spiderBabyPos[1].x = 4110, _spiderBabyPos[1].y = 585, _spiderBabyRange[1] = 205;
		_spiderBabyPos[2].x = 6070, _spiderBabyPos[2].y = 100, _spiderBabyRange[2] = 80;
		_spiderBabyPos[3].x = 6730, _spiderBabyPos[3].y = 470, _spiderBabyRange[3] = 80;
		_spiderBabyPos[4].x = 4630, _spiderBabyPos[4].y = 940, _spiderBabyRange[4] = 80;
		_spiderBabyPos[5].x = 6080, _spiderBabyPos[5].y = 1185, _spiderBabyRange[5] = 80;
		_spiderBabyPos[6].x = 6080, _spiderBabyPos[6].y = 1185, _spiderBabyRange[6] = 80;
		for (int i = 0; i < 7; i++)
		{
			type = SPIDERBABY;

			monster* monster = _factory->createMonster(type);
			monster->setPosition(_spiderBabyPos[i].x, _spiderBabyPos[i].y);
			monster->setOldPosition(_spiderBabyPos[i].x, _spiderBabyPos[i].y);
			monster->setRange(_spiderBabyRange[i]);

			_vMonster.push_back(monster);
		}

		_firedrinkerFlyPos[0].x = 4540, _firedrinkerFlyPos[0].y = 445, _firedrinkerFlyRange[0] = 305;
		_firedrinkerFlyPos[1].x = 5240 + 100, _firedrinkerFlyPos[1].y = 400, _firedrinkerFlyRange[1] = 80;
		_firedrinkerFlyPos[2].x = 5220 + 100, _firedrinkerFlyPos[2].y = 1040, _firedrinkerFlyRange[2] = 80;
		for (int i = 0; i < 3; i++)
		{
			type = FIREDRINKERFLY;

			monster* monster = _factory->createMonster(type);
			monster->setPosition(_firedrinkerFlyPos[i].x, _firedrinkerFlyPos[i].y);
			monster->setOldPosition(_firedrinkerFlyPos[i].x, _firedrinkerFlyPos[i].y);
			monster->setRange(_firedrinkerFlyRange[i]);

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
		/*if (getDistance(_playerManager->getClu()->getX(), _playerManager->getClu()->getY(), _vMonster[i]->getX(), _vMonster[i]->getY()) < _vMonster[i]->getRange())
		{
			if (getAngle(_playerManager->getClu()->getX(), _playerManager->getClu()->getY(), _vMonster[i]->getX(), _vMonster[i]->getY()) > PI_4 * 3 && getAngle(_playerManager->getClu()->getX(), _playerManager->getClu()->getY(), _vMonster[i]->getX(), _vMonster[i]->getY()) < PI_4 * 5)
			{
				_vMonster[i]->setIsLeft(true);
			}
			else
			{
				_vMonster[i]->setIsLeft(false);
			}
		}
	*/
		if (IntersectRect(&rcTemp, &_playerManager->getPlayer(_playerManager->getCharacter())->getRect(), &_vMonster[i]->getRect()))
		{
			_playerManager->getPlayer(_playerManager->getCharacter())->setState(HIT);
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