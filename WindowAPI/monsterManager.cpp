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
		_spiderBabyPos[1].x = 4110, _spiderBabyPos[1].y = 585, _spiderBabyRange[1] = 215;
		_spiderBabyPos[2].x = 6070, _spiderBabyPos[2].y = 100, _spiderBabyRange[2] = 80;
		_spiderBabyPos[3].x = 6730, _spiderBabyPos[3].y = 470, _spiderBabyRange[3] = 80;
		_spiderBabyPos[4].x = 4630, _spiderBabyPos[4].y = 940, _spiderBabyRange[4] = 130;
		_spiderBabyPos[5].x = 6080, _spiderBabyPos[5].y = 1185, _spiderBabyRange[5] = 320;
		_spiderBabyPos[6].x = 6080, _spiderBabyPos[6].y = 1185, _spiderBabyRange[6] = 320;
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
		_firedrinkerFlyPos[1].x = 5340, _firedrinkerFlyPos[1].y = 400, _firedrinkerFlyRange[1] = 150;
		_firedrinkerFlyPos[2].x = 5320, _firedrinkerFlyPos[2].y = 1040, _firedrinkerFlyRange[2] = 150;
		_firedrinkerFlyPos[3].x = 6150, _firedrinkerFlyPos[3].y = 800, _firedrinkerFlyRange[2] = 120;
		for (int i = 0; i < 4; i++)
		{
			type = FIREDRINKERFLY;

			monster* monster = _factory->createMonster(type);
			monster->setPosition(_firedrinkerFlyPos[i].x, _firedrinkerFlyPos[i].y);
			monster->setOldPosition(_firedrinkerFlyPos[i].x, _firedrinkerFlyPos[i].y);
			monster->setRange(_firedrinkerFlyRange[i]);

			_vMonster.push_back(monster);
		}
		
		_eaglePos[0].x = 1574, _eaglePos[0].y = 930, _eagleRange[0] = 300;
		_eaglePos[1].x = 2744, _eaglePos[1].y = 600, _eagleRange[1] = 400;
		for (int i = 0; i < 2; i++)
		{
			type = EAGLE;

			monster* monster = _factory->createMonster(type);
			monster->setPosition(_eaglePos[i].x, _eaglePos[i].y);
			monster->setOldPosition(_eaglePos[i].x, _eaglePos[i].y);
			monster->setRange(_eagleRange[i]);

			_vMonster.push_back(monster);
		}

		_thiefBoomerangPos[0].x = 3135, _thiefBoomerangPos[0].y = 935, _thiefBoomerangRange[0] = 200;
		_thiefBoomerangPos[1].x = 4822, _thiefBoomerangPos[1].y = 582, _thiefBoomerangRange[1] = 125;
		_thiefBoomerangPos[2].x = 6260, _thiefBoomerangPos[2].y = 575, _thiefBoomerangRange[2] = 1500;
		for (int i = 0; i < 3; i++)
		{
			type = THIEF_BOOMERANG;

			monster* monster = _factory->createMonster(type);
			monster->setPosition(_thiefBoomerangPos[i].x, _thiefBoomerangPos[i].y);
			monster->setOldPosition(_thiefBoomerangPos[i].x, _thiefBoomerangPos[i].y);
			monster->setRange(_thiefBoomerangRange[i]);

			_vMonster.push_back(monster);
		}

		_maskPos[0].x = 4297, _maskPos[0].y = 700, _maskRange[0] = 145;
		_maskPos[1].x = 6670, _maskPos[1].y = 88, _maskRange[1] = 120;
		for (int i = 0; i < 2; i++)
		{
			type = MASK;

			monster* monster = _factory->createMonster(type);
			monster->setPosition(_maskPos[i].x, _maskPos[i].y);
			monster->setOldPosition(_maskPos[i].x, _maskPos[i].y);
			monster->setRange(_maskRange[i]);

			_vMonster.push_back(monster);
		}

		_isGameClear = false;
	}

	_alpha = 0;
	_isHit = false;

	return S_OK;
}

void monsterManager::release()
{
	_vMonster.clear();

	for (int i = 0; i < _vMonster.size(); i++)
		_vMonster[i]->release();
}

void monsterManager::update()
{
	RECT rcTemp;
	RECT rcPlayer = _playerManager->getPlayer()->getRect();
	float angle, speed;
	int smlRand = RND->getFromIntTo(1, 2);
	int bigRand = RND->getFromIntTo(3, 6);

	for (int i = 0; i < _vMonster.size(); i++)
	{
		if (!_vMonster[i]->getIsAlive()) continue;
		if (_vMonster[i]->getState() == MONSTER_DEAD)
		{
			_vMonster[i]->frameChange();
			continue;
		}

		if (getDistance(_playerManager->getPlayer()->getX(), _playerManager->getPlayer()->getY(), _vMonster[i]->getX(), _vMonster[i]->getY()) < _vMonster[i]->getRange())
		{
			if (EAGLE == _vMonster[i]->getType() || THIEF_BOOMERANG == _vMonster[i]->getType())
			{
				if (getAngle(_playerManager->getPlayer()->getX(), _playerManager->getPlayer()->getY(), _vMonster[i]->getX(), _vMonster[i]->getY()) > PI_4 * 3 && 
					getAngle(_playerManager->getPlayer()->getX(), _playerManager->getPlayer()->getY(), _vMonster[i]->getX(), _vMonster[i]->getY()) < PI_4 * 5)
				{
					_vMonster[i]->setState(MONSTER_MOVE);
				}
				else if (getAngle(_playerManager->getPlayer()->getX(), _playerManager->getPlayer()->getY(), _vMonster[i]->getX(), _vMonster[i]->getY()) < PI_4 ||
					getAngle(_playerManager->getPlayer()->getX(), _playerManager->getPlayer()->getY(), _vMonster[i]->getX(), _vMonster[i]->getY()) > PI_4 * 7)
				{
					_vMonster[i]->setState(MONSTER_MOVE);
				}
			}
			//else
			//{
			//	if (getAngle(_playerManager->getPlayer()->getX(), _playerManager->getPlayer()->getY(), _vMonster[i]->getX(), _vMonster[i]->getY()) > PI_4 &&
			//		getAngle(_playerManager->getPlayer()->getX(), _playerManager->getPlayer()->getY(), _vMonster[i]->getX(), _vMonster[i]->getY()) < PI_4 * 3)
			//	{
			//		_vMonster[i]->setIsLeft(false);
			//		_vMonster[i]->setState(MONSTER_MOVE);
			//	}
			//	else if (getAngle(_playerManager->getPlayer()->getX(), _playerManager->getPlayer()->getY(), _vMonster[i]->getX(), _vMonster[i]->getY()) > PI_4 * 5 &&
			//		getAngle(_playerManager->getPlayer()->getX(), _playerManager->getPlayer()->getY(), _vMonster[i]->getX(), _vMonster[i]->getY()) < PI_4 * 7)
			//	{
			//		_vMonster[i]->setIsLeft(true);
			//		_vMonster[i]->setState(MONSTER_MOVE);
			//	}
			//}
		}
		else
		{
			if (EAGLE != _vMonster[i]->getType())
				_vMonster[i]->setState(MONSTER_IDLE);
		}

		if (IntersectRect(&rcTemp, &rcPlayer, &_vMonster[i]->getRect()) && _playerManager->getPlayer()->getIsActive() && 
			HIT != _playerManager->getPlayer()->getState() && FAINT != _playerManager->getPlayer()->getState() && FAINT_IDLE != _playerManager->getPlayer()->getState())
		{
			if (MONSTER_ITEM == _vMonster[i]->getState())
			{
				EFFECTMANAGER->play("ellipsePuff" + to_string(RND->getFromIntTo(1, 5)), _vMonster[i]->getX(), _vMonster[i]->getY());
				SOUNDMANAGER->play("UI_collect_common");
				_vMonster[i]->setIsAlive(false);
				//_vMonster.erase(_vMonster.begin() + i);

				break;
			}
			else
			{
				angle = !_playerManager->getPlayer()->getIsLeft() * PI;
				speed = 15.0f;

				_playerManager->getPlayer()->setX(_playerManager->getPlayer()->getX() + cosf(angle) * speed);
				_playerManager->getPlayer()->setState(HIT);
				_playerManager->getPlayer()->setIsActive(false);
				_isHit = true;
				EFFECTMANAGER->play("number_red" + to_string(smlRand), _playerManager->getPlayer()->getX(), rcPlayer.top);
				_playerManager->getPlayer()->hitDamage(smlRand);
				break;
			}
		}

		for (int j = 0; j < _playerManager->getBlock(CLU)->getVBlock().size(); j++)
		{
			if (IntersectRect(&rcTemp, &_playerManager->getBlock(CLU)->getVBlock()[j].rc, &_vMonster[i]->getRect()))
			{
				EFFECTMANAGER->play("aerialExplosion" + to_string(RND->getFromIntTo(1, 3)), _vMonster[i]->getX(), _vMonster[i]->getY());
				SOUNDMANAGER->play("IMP_explo_medium" + to_string(RND->getFromIntTo(1, 4)));
				_playerManager->getBlock(CLU)->removeBlock(j);

				if (SANDWORM == _vMonster[i]->getType())
					EFFECTMANAGER->play("blocked_white", _vMonster[i]->getX(), _vMonster[i]->getY());
				else
					_vMonster[i]->setState(MONSTER_DEAD);

				break;
			}
		}

		for (int j = 0; j < _playerManager->getBlock(BART)->getVBlock().size(); j++)
		{
			if (IntersectRect(&rcTemp, &_playerManager->getBlock(BART)->getVBlock()[j].rc, &_vMonster[i]->getRect()))
			{
				_vMonster[i]->setIsLeft(!_vMonster[i]->getIsLeft());
				break;
			}
		}

		if (IntersectRect(&rcTemp, &_playerManager->getPlayer(BART)->getHammerRc(), &_vMonster[i]->getRect()))
		{
			_vMonster[i]->setIsLeft(!_playerManager->getPlayer()->getIsLeft());
			this->monsterHurt(i);
			break;
		}

		for (int j = 0; j < _vMonster[i]->getVElement().size(); j++)
		{
			if (IntersectRect(&rcTemp, &rcPlayer, &_vMonster[i]->getVElement()[j].rc) && _playerManager->getPlayer()->getIsActive() &&
				HIT != _playerManager->getPlayer()->getState() && FAINT != _playerManager->getPlayer()->getState() && FAINT_IDLE != _playerManager->getPlayer()->getState())
			{
				angle = !_playerManager->getPlayer()->getIsLeft() * PI;
				speed = 15.0f;

				_playerManager->getPlayer()->setX(_playerManager->getPlayer()->getX() + cosf(angle) * speed);
				_playerManager->getPlayer()->setState(HIT);
				_playerManager->getPlayer()->setIsActive(false);
				_isHit = true;
				int rand = RND->getFromIntTo(0, 1);
				if (rand)
				{
					EFFECTMANAGER->play("number_red1", _playerManager->getPlayer()->getX(), rcPlayer.top);
					_playerManager->getPlayer()->hitDamage(1);
				}
				break;
			}
		}

		//this->collisionBullet(i, _playerManager->getBullet()->getVBullet());
		//this->collisionBullet(i, _playerManager->getTriBullet()->getVBullet());
		//this->collisionBullet(i, _playerManager->getArrow()->getVArrow());
		//this->collisionBullet(i, _playerManager->getTriArrow()->getVArrow());

		_vMonster[i]->update();
	}

	this->collisionProcess();
}

void monsterManager::render(HDC hdc)
{
	for (int i = 0; i < _vMonster.size(); i++)
	{
		if (!_vMonster[i]->getIsAlive()) continue;
		_vMonster[i]->render(hdc);
	}

	IMAGEMANAGER->alphaRender("solid_red", hdc, _alpha);
}
void monsterManager::collisionProcess()
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

void monsterManager::collisionBullet(int index, vector<tagBullet> bullet)
{
	RECT rcTemp;

	for (int j = 0; j < bullet.size(); j++)
	{
		if (!bullet[j].fire) continue;
		if (_vMonster[index]->getState() == MONSTER_DEAD) continue;

		if (IntersectRect(&rcTemp, &bullet[j].rc, &_vMonster[index]->getRect()))
		{
			EFFECTMANAGER->play("bulletPuff" + to_string(RND->getFromIntTo(1, 5)),bullet[j].rc.left, bullet[j].rc.top);
			bullet[j].fire = false;
			_vMonster[index]->setIsLeft(!_playerManager->getPlayer()->getIsLeft());

			this->monsterHurt(index);

			break;
		}
	}
}

void monsterManager::monsterHurt(int index)
{
	int smlRand = RND->getFromIntTo(1, 2);
	int bigRand = RND->getFromIntTo(3, 6);

	switch (_vMonster[index]->getType())
	{
	case SANDWORM:
		EFFECTMANAGER->play("blocked_white", _vMonster[index]->getX(), _vMonster[index]->getY());
		SOUNDMANAGER->play("Mon_Sandworm_hurt" + to_string(RND->getFromIntTo(1, 3)));
		break;
	case SPIDERBABY:
		if (CLU == _playerManager->getCharacter())
		{
			EFFECTMANAGER->play("blocked_yellow", _vMonster[index]->getX(), _vMonster[index]->getY());
			EFFECTMANAGER->play("number_yellow" + to_string(smlRand), _vMonster[index]->getX(), _vMonster[index]->getRect().top);
			_vMonster[index]->playerAttack(smlRand);
		}
		else
		{
			EFFECTMANAGER->play("number_yellow" + to_string(bigRand), _vMonster[index]->getX(), _vMonster[index]->getRect().top);
			_vMonster[index]->playerAttack(bigRand);
		}
		break;
	case FIREDRINKERFLY:
		EFFECTMANAGER->play("blocked_red", _vMonster[index]->getX(), _vMonster[index]->getY());
		EFFECTMANAGER->play("number_red" + to_string(smlRand), _vMonster[index]->getX(), _vMonster[index]->getRect().top);
		_vMonster[index]->playerAttack(smlRand);
		break;
	case EAGLE:
		if (CLU == _playerManager->getCharacter())
		{
			EFFECTMANAGER->play("number_blue" + to_string(bigRand), _vMonster[index]->getX(), _vMonster[index]->getRect().top);
			_vMonster[index]->playerAttack(bigRand);
		}
		else
		{
			EFFECTMANAGER->play("blocked_blue", _vMonster[index]->getX(), _vMonster[index]->getY());
			EFFECTMANAGER->play("number_blue" + to_string(smlRand), _vMonster[index]->getX(), _vMonster[index]->getRect().top);
			_vMonster[index]->playerAttack(smlRand);
		}
		break;
	case THIEF_BOOMERANG:
		if (CLU == _playerManager->getCharacter())
		{
			EFFECTMANAGER->play("blocked_yellow", _vMonster[index]->getX(), _vMonster[index]->getY());
			EFFECTMANAGER->play("number_yellow" + to_string(bigRand), _vMonster[index]->getX(), _vMonster[index]->getRect().top);
			_vMonster[index]->playerAttack(smlRand);
		}
		else
		{
			EFFECTMANAGER->play("number_yellow" + to_string(smlRand), _vMonster[index]->getX(), _vMonster[index]->getRect().top);
			_vMonster[index]->playerAttack(bigRand);
		}
		break;
	case MASK:
		if (CLU == _playerManager->getCharacter())
		{
			EFFECTMANAGER->play("number_blue" + to_string(bigRand), _vMonster[index]->getX(), _vMonster[index]->getRect().top);
			_vMonster[index]->playerAttack(bigRand);
		}
		else
		{
			EFFECTMANAGER->play("blocked_blue", _vMonster[index]->getX(), _vMonster[index]->getY());
			EFFECTMANAGER->play("number_blue" + to_string(smlRand), _vMonster[index]->getX(), _vMonster[index]->getRect().top);
			_vMonster[index]->playerAttack(smlRand);
		}
		break;
	default:
		//´©±¸³Ä ³Í??
		break;
	}
}
