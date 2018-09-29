#include "stdafx.h"
#include "pHpBar.h"

HRESULT pHpBar::init(const char * frontImageKey, const char * backImageKey, int x, int y)
{
	//ü�¹� ��ġ �ʱ�ȭ
	_x = x;
	_y = y;
	//ü�¹� �̹��� �ʱ�ȭ
	_hpBarFront = IMAGEMANAGER->findImage(frontImageKey);
	_hpBarBack = IMAGEMANAGER->findImage(backImageKey);

	//ü�¹� ��Ʈ ��ġ �� ũ�� �ʱ�ȭ
	_frontWidth = _backWidth = _maxWidth = _hpBarBack->getWidth();
	_rcHp = RectMake(x, y, _maxWidth, _hpBarBack->getHeight());

	return S_OK;
}

void pHpBar::release(void)
{
}

void pHpBar::update(void)
{
}

void pHpBar::render(HDC hdc)
{
	//������ �Ǵ� ������ ���ؼ� ������ �Ǵϱ� ������� ���� ��Ų��
	_hpBarBack->alphaRender(hdc, _x, _y + 3, 0, 0, _backWidth, _hpBarBack->getHeight(), 200);
	//�տ� �������� ü�¹� �̹���
	_hpBarFront->render(hdc, _x, _y, 0, 0, _frontWidth, _hpBarFront->getHeight());
}

void pHpBar::setGauge(float currentHp, float maxHp)
{
	_frontWidth = (currentHp / maxHp) * _maxWidth;

	if ((int)currentHp % 2 == 0)
		_backWidth = ((currentHp * 0.5f) / (maxHp * 0.5f)) * _maxWidth;
}