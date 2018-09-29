#include "stdafx.h"
#include "mHpBar.h"

HRESULT mHpBar::init(const char * frontImageKey, const char * backImageKey, int x, int y)
{
	//ü�¹� ��ġ �ʱ�ȭ
	_x = x;
	_y = y;
	//ü�¹� �̹��� �ʱ�ȭ
	_hpBarFront = IMAGEMANAGER->findImage(frontImageKey);
	_hpBarBack = IMAGEMANAGER->findImage(backImageKey);

	//ü�¹� ��Ʈ ��ġ �� ũ�� �ʱ�ȭ
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
		//������ �Ǵ� ������ ���ؼ� ������ �Ǵϱ� ������� ���� ��Ų��
		_hpBarBack->alphaRender(hdc, _rcHp.left - CAMERAMANAGER->getCamera().left, _rcHp.top - CAMERAMANAGER->getCamera().top, _alpha);
		//�տ� �������� ü�¹� �̹���
		_hpBarFront->alphaRender(hdc, _rcHp.left - CAMERAMANAGER->getCamera().left, _rcHp.top - CAMERAMANAGER->getCamera().top, 0, 0, _width, _hpBarFront->getHeight(), _alpha);
	}
}

void mHpBar::setGauge(float currentHp, float maxHp)
{
	_isActive = true;
	_width = (currentHp / maxHp) * _hpBarBack->getWidth();
}
