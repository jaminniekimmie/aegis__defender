#include "stdafx.h"
#include "titleScene.h"

HRESULT titleScene::init(void)
{
	_mainMenu.img = IMAGEMANAGER->findImage("menu_main");
	_mainMenu.x = 580, _mainMenu.y = 521;
	_mainMenu.alpha = 0;
	_mainMenu.isActive = false;
	_soundFrame.img = IMAGEMANAGER->findImage("menu_sound_frame");
	_soundFrame.x = 517, _soundFrame.y = 146;
	_soundFrame.alpha = 0;
	_pressAnyButton.img = IMAGEMANAGER->findImage("menu_pressAnyButton");
	_pressAnyButton.x = 509, _pressAnyButton.y = 584;
	_pressAnyButton.isActive = false;
	_pressAnyButton.alpha = 0;
	_soundMenu.img = IMAGEMANAGER->findImage("menu_sound");
	_soundMenu.alpha = 0;

	_alpha = 255;
	_titleIndex = 0;
	_index = 0;
	_count = 0;
	_frameSpeed = 3;
	_sceneSwitch = _soundMenuOn = false;
	_volume_sfx = _volume_BGM = 1.0f;

	SOUNDMANAGER->play("BGM_title", true);

	return S_OK;
}

void titleScene::release(void)
{
	SOUNDMANAGER->stop("BGM_title");
}

void titleScene::update(void)
{
	this->keyInput();
	this->pressAnyButton();
	this->sceneSwitch();
	this->soundMenu();
	this->frameChangeLoop();
}

void titleScene::render(void)
{
	IMAGEMANAGER->render("titleScene" + to_string(_titleIndex), getMemDC());
	_mainMenu.img->alphaFrameRender(getMemDC(), _mainMenu.x, _mainMenu.y, _index, 0, _mainMenu.alpha);
	_pressAnyButton.img->alphaRender(getMemDC(), _pressAnyButton.x, _pressAnyButton.y, _pressAnyButton.alpha);
	this->soundMenuRender();

	if (_alpha > 0) IMAGEMANAGER->alphaRender("solid_black", getMemDC(), _alpha);
}

void titleScene::pressAnyButton()
{
	if (_mainMenu.isActive)
	{
		if (_pressAnyButton.alpha > 0)
			_pressAnyButton.alpha -= 5;
		if (_mainMenu.alpha < 255)
			_mainMenu.alpha += 5;
	}
	else
	{
		if (_pressAnyButton.alpha < 50)
			_pressAnyButton.alpha += 5;
		else
		{
			if (_pressAnyButton.isActive)
			{
				if (_pressAnyButton.alpha > 50)
				{
					_pressAnyButton.alpha -= 5;
				}
				else
				{
					_pressAnyButton.isActive = false;
				}
			}
			else
			{
				if (_pressAnyButton.alpha < 255)
				{
					_pressAnyButton.alpha += 5;
				}
				else
				{
					_pressAnyButton.isActive = true;
				}
			}
		}
	}
}

void titleScene::frameChangeLoop()
{
	if (!_soundMenuOn)
	{
		_count++;
		if (_count % _frameSpeed == 0)
		{
			if (_titleIndex < 199)
				_titleIndex++;
			else
				_titleIndex = 0;
		}
	}
	else
	{
		_count = 0;
	}
}

void titleScene::soundMenu()
{
	if (_soundMenuOn)
	{
		if (_soundMenu.alpha < 255)
			_soundMenu.alpha += 15;
	}
	else
	{
		if (_soundMenu.alpha > 0)
			_soundMenu.alpha -= 15;
	}
}

void titleScene::soundMenuRender()
{
	IMAGEMANAGER->alphaRender("solid_black", getMemDC(), _soundMenu.alpha * 0.9f);
	_soundMenu.img->alphaRender(getMemDC(), _soundMenu.alpha);
	_soundFrame.img->alphaRender(getMemDC(), _soundFrame.x, _soundFrame.y, _soundMenu.alpha);

	if (_soundMenuOn)
	{
		float BGM = _volume_BGM / 1.0f * 100;
		if (BGM <= 0) BGM = 0;
		float SFX = _volume_sfx / 1.0f * 100;
		if (SFX <= 0) SFX = 0;
		char str[128];
		HFONT myFont = CreateFont(31, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "PF Ronda Seven");
		HFONT oldFont = (HFONT)SelectObject(getMemDC(), myFont);
		SetTextColor(getMemDC(), RGB(229, 205, 145));
		SetBkMode(getMemDC(), TRANSPARENT);

		sprintf_s(str, "MUSIC         %.f/100", BGM);
		TextOut(getMemDC(), 541, 114, str, strlen(str));

		sprintf_s(str, "SFX           %.f/100", SFX);
		TextOut(getMemDC(), 551, 264, str, strlen(str));

		SelectObject(getMemDC(), oldFont);
		DeleteObject(myFont);
	}
}

void titleScene::keyInput()
{
	if (!_mainMenu.isActive)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN) || KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			SOUNDMANAGER->play("UI_button_main");
			_mainMenu.isActive = true;
		}
	}
	else
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			if (_soundMenuOn)
			{
				if (_soundFrame.x == 517 + 136)
				{
					SOUNDMANAGER->play("UI_button_sub");
					_soundFrame.x -= 136;
				}
			}
		}

		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			if (_soundMenuOn)
			{
				if (_soundFrame.x == 517)
				{
					SOUNDMANAGER->play("UI_button_sub");
					_soundFrame.x += 136;
				}
			}
		}

		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			if (_soundMenuOn)
			{
				if (_soundFrame.y == 146 + 151)
				{
					SOUNDMANAGER->play("UI_button_sub");
					_soundFrame.y -= 151;
				}
			}
			else
			{
				if (0 < _index && _index <= 3)
				{
					SOUNDMANAGER->play("UI_button_highlight2");
					_index--;
				}
			}
		}

		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			if (_soundMenuOn)
			{
				if (_soundFrame.y == 146)
				{
					SOUNDMANAGER->play("UI_button_sub");
					_soundFrame.y += 151;
				}
			}
			else
			{
				if (0 <= _index && _index < 3)
				{
					SOUNDMANAGER->play("UI_button_highlight1");
					_index++;
				}
			}
		}

		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			if (_soundMenuOn)
			{
				if (_soundFrame.x == 517 && _soundFrame.y == 146 && _volume_BGM > 0)
				{
					SOUNDMANAGER->play("UI_button_sub");
					_volume_BGM -= 0.1f;
					SOUNDMANAGER->setVolume(_volume_BGM);
				}
				else if (_soundFrame.x == 517 + 136 && _soundFrame.y == 146 && _volume_BGM < 1.0f)
				{
					SOUNDMANAGER->play("UI_button_sub");
					_volume_BGM += 0.1f;
					SOUNDMANAGER->setVolume(_volume_BGM);
				}
				else if (_soundFrame.x == 517 && _soundFrame.y == 146 + 151 && _volume_sfx > 0)
				{
					_volume_sfx -= 0.1f;
					SOUNDMANAGER->play("UI_button_sub", false, _volume_sfx);
				}
				else if (_soundFrame.x == 517 + 136 && _soundFrame.y == 146 + 151 && _volume_sfx < 1.0f)
				{
					_volume_sfx += 0.1f;
					SOUNDMANAGER->play("UI_button_sub", false, _volume_sfx);
				}
			}
			else
			{
				SOUNDMANAGER->play("UI_button_main");
				if (_index == 2)
				{
					SOUNDMANAGER->play("UI_menu_open");
					_soundMenuOn = true;
				}
				else
					_sceneSwitch = true;
			}
		}

		if (KEYMANAGER->isOnceKeyDown('L'))
		{
			SOUNDMANAGER->play("UI_menu_close");
			_soundMenuOn = false;
		}
	}
}

void titleScene::sceneSwitch()
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
			else if (_index == 1)
				SCENEMANAGER->loadScene("흑로딩화면");
			else if (_index == 3)
				PostQuitMessage(0);
		}
	}
}
