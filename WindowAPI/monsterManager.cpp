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

		_cricketPos[0].x = 2873, _cricketPos[0].y = 1220;
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
}

void monsterManager::render(HDC hdc)
{
	//������Ʈ ���� �����鼭 Ȱ��ȭ�� ������Ʈ�鸸 �׷��ָ� �ȴ�.
	//getMemDC() �� �����ϱ� hdc ���� �ȴ�.

}
void monsterManager::collisionProcess()
{
}