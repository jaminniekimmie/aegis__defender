#include "stdafx.h"
#include "aniTestScene.h"


HRESULT aniTestScene::init(void)
{
	_camel = new camel;
	_camel->init();

	return S_OK;
}

void aniTestScene::release(void)
{
	_camel->release();
	SAFE_DELETE(_camel);
}

void aniTestScene::update(void)
{
	_camel->update();
}

void aniTestScene::render(void)
{
	_camel->render();
}
