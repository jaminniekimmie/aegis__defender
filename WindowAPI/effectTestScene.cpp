#include "stdafx.h"
#include "effectTestScene.h"

HRESULT effectTestScene::init(void)
{
	//폭발이미지
	IMAGEMANAGER->addFrameImage("폭발이펙트", "explosion.bmp", 832, 62, 26, 1);

	//이펙트 클래스 초기화
	_effect = new effect;
	_effect->init(IMAGEMANAGER->findImage("폭발이펙트"), 0.3f);

	/*이펙트 매니져 사용시*/
	EFFECTMANAGER->addEffect("폭발", "폭발이펙트", 0.2f, 100);

	return S_OK;
}

void effectTestScene::release(void)
{
	//이펙트 클래스 해제
	_effect->release();
	SAFE_DELETE(_effect);

	/*이펙트 매니져 사용시*/
	//이미지매니져 처럼 위에 클래스 해제해줄 필요 없음
}

void effectTestScene::update(void)
{
	//이펙트 클래스 업데이트
	_effect->update();

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//이펙트 터트릴 좌표
		_effect->startEffect(_ptMouse.x, _ptMouse.y);
	}

	/*이펙트 매니져 사용시*/
	if (KEYMANAGER->isStayKeyDown(VK_RBUTTON))
	{
		EFFECTMANAGER->play("폭발", _ptMouse.x, _ptMouse.y);
	}

}

void effectTestScene::render(void)
{
	//MY_UTIL 안에 그냥 간단하게 만들어 두었음
	//너희들은 사용할 일 거의 없음
	showTitle(getMemDC(), "이펙트 테스트");

	//이펙트 클래스 렌더
	_effect->render();
}
