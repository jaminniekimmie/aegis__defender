#include "stdafx.h"
#include "monsterManager.h"
#include "playerManager.h"


HRESULT monsterManager::init(int scene)
{
	//여기에서 오브젝트 객체들생성
	//팩토리 패턴에서 에너미 매니저 init 보고 하면 된다
	//그리고 bool* _targetIsActived 이거 다
	//자기 아래 렉트 isActived 연결 해줘야 한다
	//맵번호는 어케 찾냐면 받아놨으니까
	//_mapData->getmonster()[렉트번호].isActived 하면 된다
	_factory = new monsterFactory;

	if (scene == 1)
	{
		MONSTERTYPE type;

		_cricketPos[0].x = WINSIZEX / 2, _cricketPos[0].y = TILESIZEY - WINSIZEY;
		for (int i = 0; i < 14; i++)
		{
			type = CRICKET;

			monster* monster = _factory->createMonster(type);
			monster->setPosition(_cricketPos[i].x, _cricketPos[i].y);

			_vMonster.push_back(monster);
		}

		//_rolyPolyLargePos[0].x = 2873, _rolyPolyLargePos[0].y = 1220;
		//for (int i = 0; i < 14; i++)
		//{
		//	type = ROLYPOLY_LARGE;
		//
		//	monster* monster = _factory->createMonster(type);
		//	monster->setPosition(_rolyPolyLargePos[i].x, _rolyPolyLargePos[i].y);
		//
		//	_vMonster.push_back(monster);
		//}

		_isGameClear = false;
	}

	//스테이지에 오브젝트 몇개인지 찾아서 포문돌리자
	//오브젝트 수만큼 좌표 배열에 넣어두고 밑에 포문 돌려야함




	return S_OK;
}

void monsterManager::release()
{
	_vMonster.clear();
}

void monsterManager::update()
{

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
		_vMonster[i]->update();
	}
}

void monsterManager::render(HDC hdc)
{
	for (int i = 0; i < _vMonster.size(); i++)
	{
		if (_vMonster[i]->getState() == DEAD) continue;
		_vMonster[i]->render(hdc);
	}
}
void monsterManager::collisionProcess()
{
}