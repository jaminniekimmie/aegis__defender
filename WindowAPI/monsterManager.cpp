#include "stdafx.h"
#include "monsterManager.h"
#include "playerManager.h"


HRESULT monsterManager::init(int scene)
{
	//���⿡�� ������Ʈ ��ü�����
	//���丮 ���Ͽ��� ���ʹ� �Ŵ��� init ���� �ϸ� �ȴ�
	//�׸��� bool* _targetIsActived �̰� ��
	//�ڱ� �Ʒ� ��Ʈ isActived ���� ����� �Ѵ�
	//�ʹ�ȣ�� ���� ã�ĸ� �޾Ƴ����ϱ�
	//_mapData->getmonster()[��Ʈ��ȣ].isActived �ϸ� �ȴ�
	_factory = new monsterFactory;

	if (scene == 1)
	{
		MONSTERTYPE type;

		_sandwormPos[0].x = WINSIZEX / 2, _sandwormPos[0].y = TILESIZEY - WINSIZEY;
		for (int i = 0; i < 1; i++)
		{
			type = SANDWORM;

			monster* monster = _factory->createMonster(type);
			monster->setPosition(_sandwormPos[i].x, _sandwormPos[i].y);

			_vMonster.push_back(monster);
		}

		_isGameClear = false;
	}

	//���������� ������Ʈ ����� ã�Ƽ� ����������
	//������Ʈ ����ŭ ��ǥ �迭�� �־�ΰ� �ؿ� ���� ��������




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