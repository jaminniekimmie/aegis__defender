#include "stdafx.h"
#include "mHpBar.h"

HRESULT mHpBar::init(const char * frontImageKey, const char * backImageKey, int x, int y)
{
	//체력바 위치 초기화
	_x = x;
	_y = y;
	//체력바 이미지 초기화
	_hpBarFront = IMAGEMANAGER->findImage(frontImageKey);
	_hpBarBack = IMAGEMANAGER->findImage(backImageKey);

	//체력바 렉트 위치 및 크기 초기화
	_rcHp = RectMakeCenter(x, y, _hpBarBack->getWidth(), _hpBarBack->getHeight());
	_width = _hpBarBack->getWidth();
	_isActive = false;
	_alpha = 0;
	_activeCount = 0;

	return S_OK;
}

void mHpBar::release(void)
{
}

void mHpBar::update(void)
{
	if (_isActive)
	{
		if (_alpha < 255)
			_alpha += 15;
		else
		{
			if (_activeCount < 100)
				_activeCount++;
			else
			{
				if (_alpha > 0)
					_alpha -= 15;
				else
				{
					_activeCount = 0;
					_isActive = false;
				}
			}
		}
	}

	_rcHp = RectMakeCenter(_x, _y, _hpBarBack->getWidth(), _hpBarBack->getHeight());
}

void mHpBar::render(HDC hdc)
{
	if (_isActive)
	{
		IMAGEMANAGER->alphaRender("GUI_hp_bar_shadow", hdc, _rcHp.left - CAMERAMANAGER->getCamera().left, _rcHp.top + 2 - CAMERAMANAGER->getCamera().top, _alpha * 0.33f);
		//렌더링 되는 순서에 의해서 렌더가 되니까 피통부터 렌더 시킨다
		_hpBarBack->alphaRender(hdc, _rcHp.left - CAMERAMANAGER->getCamera().left, _rcHp.top - CAMERAMANAGER->getCamera().top, _alpha);
		//앞에 보여지는 체력바 이미지
		_hpBarFront->alphaRender(hdc, _rcHp.left - CAMERAMANAGER->getCamera().left, _rcHp.top - CAMERAMANAGER->getCamera().top, 0, 0, _width, _hpBarFront->getHeight(), _alpha);
	}
}

void mHpBar::setGauge(float currentHp, float maxHp)
{
	_isActive = true;
	_width = (currentHp / maxHp) * _hpBarBack->getWidth();
}
