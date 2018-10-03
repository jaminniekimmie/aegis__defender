#include "stdafx.h"
#include "gameOverScene.h"

HRESULT gameOverScene::init(void)
{
	_gameOverImg = IMAGEMANAGER->findImage("scene_gameOver");
	_alpha = 255;
	_index = 0;
	_sceneSwitch = false;

	SOUNDMANAGER->play("BGM_gameOver", true);

	return S_OK;
}

void gameOverScene::release(void)
{
	SOUNDMANAGER->stop("BGM_gameOver");
}

void gameOverScene::update(void)
{
	if (!_sceneSwitch)
	{
		if (_alpha > 0)
			_alpha -= 5;
	}
	else
	{
		_alpha += 5;
		if (_alpha >= 255)
		{
			SCENEMANAGER->getCurrentScene()->release();
			if (_index == 0)
				SCENEMANAGER->loadScene("캐릭터로딩화면");
			else
				SCENEMANAGER->loadScene("타이틀화면");
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		if (_index == 0)
		{
			SOUNDMANAGER->play("UI_button_highlight1");
			_index = 1;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		if (_index == 1)
		{
			SOUNDMANAGER->play("UI_button_highlight2");
			_index = 0;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		SOUNDMANAGER->play("UI_button_main");
		_sceneSwitch = true;
	}
	
}

void gameOverScene::render(void)
{
	_gameOverImg->frameRender(getMemDC(), 0, 0, _index, 0);
	if (_alpha > 0)
		IMAGEMANAGER->alphaRender("solid_black", getMemDC(), _alpha);
}
