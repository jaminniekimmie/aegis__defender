#include "stdafx.h"
#include "effect.h"

HRESULT effect::init(image * effectImg, float effectFPS, bool isFadeOut)
{
	//변수 초기화
	_effectImg = effectImg;
	_effectFPS = effectFPS;
	_isFadeOut = isFadeOut;
	_alpha = 255;
	_isRunning = false;

	//이펙트 애니메이션 생성 및 초기화
	_effectAni = new animation;
	_effectAni->init(_effectImg->getWidth(), _effectImg->getHeight(), _effectImg->getMaxFrameX() + 1, _effectImg->getMaxFrameY() + 1);
	_effectAni->setPlayFrame();
	_effectAni->setFPS(1);

	return S_OK;
}

void effect::release(void)
{
	//이펙트애니 해제
	_effectAni->release();
	SAFE_DELETE(_effectAni);
}

void effect::update(void)
{
	if (_isRunning)
	{
		//if (_isFadeOut)
		//	_alpha -= 255 / (_effectImg->getMaxFrameX() + 1);
		_effectAni->frameUpdate(_effectFPS);
	}
	//이펙트 애니메이션 종료가 되면 멈추기(_isRunning = false;)
	if (!_effectAni->isPlay()) this->stopEffect();
}

void effect::render(void)
{
	if (_isRunning)
	{
		if (_isFadeOut)
			_effectImg->aniAlphaRender(getMemDC(), _x - CAMERAMANAGER->getCamera().left, _y - CAMERAMANAGER->getCamera().top, 255);
			//_effectImg->aniAlphaRender(getMemDC(), _x - CAMERAMANAGER->getCamera().left, _y - CAMERAMANAGER->getCamera().top, _effectAni, _alpha);
		else
			_effectImg->aniRender(getMemDC(), _x - CAMERAMANAGER->getCamera().left, _y - CAMERAMANAGER->getCamera().top, _effectAni);
	}
}

void effect::startEffect(int x, int y)
{
	//위치를 센터좌표로 만들기
	_x = x - (_effectAni->getFrameWidth() / 2);
	_y = y - (_effectAni->getFrameHeight() / 2);

	_isRunning = true;
	_effectAni->start();
}

void effect::stopEffect()
{
	_isRunning = false;
}

//#include "stdafx.h"
//#include "effect.h"
//
//HRESULT effect::init(string str, int frameSpeed)
//{
//	_image = IMAGEMANAGER->findImage(str);
//	_x = 0.f;
//	_y = 0.f;
//	_index = 0;
//	_count = 0;
//	_frameSpeed = frameSpeed;
//	_isLeft = false;
//	_isFinish = false;
//
//	return S_OK;
//}
//
//void effect::release(void)
//{
//}
//
//void effect::update(void)
//{
//	_count++;
//	if (_count % _frameSpeed == 0)
//	{
//		_index++;
//		if (_index == _image->getMaxFrameX())
//		{
//			_image->setFrameY(RND->getInt(_image->getMaxFrameY() + 1));
//			_isFinish = true;
//		}
//		_image->setFrameX(_index);
//	}
//}
//
//void effect::render(void)
//{
//	_image->frameRender(getMemDC(), (int)_x - CAMERAMANAGER->getCamera().left, (int)_y - CAMERAMANAGER->getCamera().top);
//	/*char str[64];
//	sprintf(str, "%d", _image->getMaxFrameX());
//	TextOut(getMemDC(), 700, 500, str, strlen(str));
//
//	sprintf(str, "%d", _index);
//	TextOut(getMemDC(), 700, 550, str, strlen(str));*/
//}
