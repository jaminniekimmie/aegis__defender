#include "stdafx.h"
#include "rotateTestScene.h"

HRESULT rotateTestScene::init(void)
{
	_missile = IMAGEMANAGER->addImage("미사일1", "missile1.bmp", 26, 124, true, RGB(255, 0, 255));
	_frameMissle = IMAGEMANAGER->addFrameImage("미사일2", "missile.bmp", 416, 64, 13, 1, true, RGB(255, 0, 255));
	
	_count = 0;

	return S_OK;
}

void rotateTestScene::release(void)
{
}

void rotateTestScene::update(void)
{
	//미사일 애니메이션
	_count++;
	if (_count % 5 == 0)
	{
		_frameMissle->setFrameX(_frameMissle->getFrameX() + 1);
		if (_frameMissle->getFrameX() >= _frameMissle->getMaxFrameX())
		{
			_frameMissle->setFrameX(0);
			_count = 0;
		}
	}

	//각도를 화면 중점과 마우스 좌표로 구하기
	_angle = getAngle(WINSIZEX / 2, WINSIZEY / 2, _ptMouse.x, _ptMouse.y);
}

void rotateTestScene::render(void)
{
	showTitle(getMemDC(), "로테이트 테스트");

	//미사일 로테이트렌더
	_missile->rotateRender(getMemDC(), WINSIZEX / 2 - 200, WINSIZEY / 2, _angle);
	//미사일 로테이트프레임렌더
	_frameMissle->rotateFrameRender(getMemDC(), WINSIZEX / 2 + 200, WINSIZEY / 2, _angle);
}
