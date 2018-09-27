#include "stdafx.h"
#include "hpBar.h"

HRESULT hpBar::init(const char * frontImageKey, const char * backImageKey, int x, int y)
{
	//ü�¹� ��ġ �ʱ�ȭ
	_x = x;
	_y = y;
	//ü�¹� �̹��� �ʱ�ȭ
	_hpBarFront = IMAGEMANAGER->findImage(frontImageKey);
	_hpBarBack = IMAGEMANAGER->findImage(backImageKey);
	//_hpBarFront = IMAGEMANAGER->addImage(frontImageKey, frontImage, x, y, width, height, true, RGB(255, 0, 255));
	//_hpBarBack = IMAGEMANAGER->addImage(backImageKey, backImage, x, y, width, height, true, RGB(255, 0, 255));
	
	//ü�¹� ��Ʈ ��ġ �� ũ�� �ʱ�ȭ
	_rcHp = RectMakeCenter(x, y, _hpBarBack->getWidth(), _hpBarBack->getHeight());
	_width = _hpBarBack->getWidth();
	_isActive = false;
	_alpha = 0;
	_activeCount = 0;

	return S_OK;
}

void hpBar::release(void)
{
}

void hpBar::update(void)
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

void hpBar::render(HDC hdc)
{
	if (_isActive)
	{
		//������ �Ǵ� ������ ���ؼ� ������ �Ǵϱ� ������� ���� ��Ų��
		_hpBarBack->alphaRender(hdc, _rcHp.left - CAMERAMANAGER->getCamera().left, _rcHp.top - CAMERAMANAGER->getCamera().top, _alpha);
		//�տ� �������� ü�¹� �̹���
		_hpBarFront->alphaRender(hdc, _rcHp.left - CAMERAMANAGER->getCamera().left, _rcHp.top - CAMERAMANAGER->getCamera().top, 0, 0, _width, _hpBarFront->getHeight(), _alpha);
	}
}

void hpBar::setGauge(float currentHp, float maxHp)
{
	_isActive = true;
	_width = (currentHp / maxHp) * _hpBarBack->getWidth();
}
