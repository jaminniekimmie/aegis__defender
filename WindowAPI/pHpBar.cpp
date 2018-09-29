#include "stdafx.h"
#include "pHpBar.h"

HRESULT pHpBar::init(const char * frontImageKey, const char * backImageKey, int x, int y)
{
	//체력바 위치 초기화
	_x = x;
	_y = y;
	//체력바 이미지 초기화
	_hpBarFront = IMAGEMANAGER->findImage(frontImageKey);
	_hpBarBack = IMAGEMANAGER->findImage(backImageKey);

	//체력바 렉트 위치 및 크기 초기화
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
	//렌더링 되는 순서에 의해서 렌더가 되니까 피통부터 렌더 시킨다
	_hpBarBack->alphaRender(hdc, _x, _y + 3, 0, 0, _backWidth, _hpBarBack->getHeight(), 200);
	//앞에 보여지는 체력바 이미지
	_hpBarFront->render(hdc, _x, _y, 0, 0, _frontWidth, _hpBarFront->getHeight());
}

void pHpBar::setGauge(float currentHp, float maxHp)
{
	_frontWidth = (currentHp / maxHp) * _maxWidth;

	if ((int)currentHp % 2 == 0)
		_backWidth = ((currentHp * 0.5f) / (maxHp * 0.5f)) * _maxWidth;
}