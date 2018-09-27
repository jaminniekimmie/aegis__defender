#include "stdafx.h"
#include "effect.h"

HRESULT effect::init(image * effectImg, float effectFPS, bool isFadeOut, bool isFloating)
{
	//���� �ʱ�ȭ
	_effectImg = effectImg;
	_effectFPS = effectFPS;
	_isFadeOut = isFadeOut;
	_isFloating = isFloating;
	_alpha = 255;
	_isRunning = false;

	//����Ʈ �ִϸ��̼� ���� �� �ʱ�ȭ
	_effectAni = new animation;
	_effectAni->init(_effectImg->getWidth(), _effectImg->getHeight(), _effectImg->getMaxFrameX() + 1, _effectImg->getMaxFrameY() + 1);
	_effectAni->setPlayFrame();
	_effectAni->setFPS(1);

	return S_OK;
}

void effect::release(void)
{
	//����Ʈ�ִ� ����
	_effectAni->release();
	SAFE_DELETE(_effectAni);
}

void effect::update(void)
{
	if (_isRunning)
	{
		if (_isFadeOut)
			_alpha -= 5;
		if (_isFloating)
			_y--;

		_effectAni->frameUpdate(_effectFPS);
	}
	//����Ʈ �ִϸ��̼� ���ᰡ �Ǹ� ���߱�(_isRunning = false;)
	if (!_effectAni->isPlay()) this->stopEffect();
}

void effect::render(void)
{
	if (_isRunning)
	{
		if (_isFadeOut)
			_effectImg->aniAlphaRender(getMemDC(), _x - CAMERAMANAGER->getCamera().left, _y - CAMERAMANAGER->getCamera().top, _effectAni, _alpha);
		else
			_effectImg->aniRender(getMemDC(), _x - CAMERAMANAGER->getCamera().left, _y - CAMERAMANAGER->getCamera().top, _effectAni);
	}
}

void effect::startEffect(int x, int y)
{
	//��ġ�� ������ǥ�� �����
	_x = x - (_effectAni->getFrameWidth() / 2);
	_y = y - (_effectAni->getFrameHeight() / 2);

	_isRunning = true;
	_alpha = 255;
	_effectAni->start();
}

void effect::stopEffect()
{
	_isRunning = false;
}