#include "stdafx.h"
#include "GUI.h"
#include "playerManager.h"

HRESULT GUI::init(void)
{
	for (int i = 0; i < 3; i++)
	{
		tagImage heartRed;
		ZeroMemory(&heartRed, sizeof(tagImage));
		heartRed.img = IMAGEMANAGER->findImage("GUI_heart_red");
		heartRed.shadow = IMAGEMANAGER->findImage("GUI_heart_red_shadow");
		heartRed.rc = RectMake(25 + (i * (heartRed.img->getWidth() + 6)), 25, heartRed.img->getWidth(), heartRed.img->getHeight());
		_vHeartRed.push_back(heartRed);

		tagImage heartYellow;
		ZeroMemory(&heartYellow, sizeof(tagImage));
		heartYellow.img = IMAGEMANAGER->findImage("GUI_heart_yellow");
		heartYellow.shadow = IMAGEMANAGER->findImage("GUI_heart_yellow_shadow");
		heartYellow.rc = RectMake(25 + (i * (heartYellow.img->getWidth() + 6)), 64, heartYellow.img->getWidth(), heartYellow.img->getHeight());
		_vHeartYellow.push_back(heartYellow);
	}

	_blueFlower.img = IMAGEMANAGER->findImage("GUI_blueFlower");
	_blueFlower.rc = RectMake(1163, 25, _blueFlower.img->getWidth(), _blueFlower.img->getHeight());
	_blueFlower.isActive = true;
	_blueFlowerCount = 0;
	_mineral.img = IMAGEMANAGER->findImage("GUI_mineral");
	_mineral.rc = RectMake(1163, 89, _mineral.img->getWidth(), _mineral.img->getHeight());
	_mineral.isActive = true;
	_mineralCount = 0;
	
	_icon[CLU].img = IMAGEMANAGER->findImage("GUI_icon_clu");
	_icon[CLU].shadow = IMAGEMANAGER->findImage("GUI_icon_clu_shadow");
	_icon[CLU].img->setFrameX(1);
	_icon[CLU].rc = RectMake(564, 13, _icon[CLU].img->getFrameWidth(), _icon[CLU].img->getFrameHeight());
	
	_icon[BART].img = IMAGEMANAGER->findImage("GUI_icon_bart");
	_icon[BART].img->setFrameX(0);
	_icon[BART].shadow = IMAGEMANAGER->findImage("GUI_icon_bart_shadow");
	_icon[BART].rc = RectMake(_icon[CLU].rc.right + 3, 13, _icon[BART].img->getFrameWidth(), _icon[BART].img->getFrameHeight());

	_button_switch.img = IMAGEMANAGER->findImage("GUI_button_switch");
	_button_switch.rc = RectMake(671, WINSIZEY, _button_switch.img->getWidth(), _button_switch.img->getHeight());
	_button_switch.alpha = 0;

	return S_OK;
}

void GUI::release(void)
{
}

void GUI::update(void)
{
	_icon[_playerManager->getCharacter()].img->setFrameX(1);
	_icon[!_playerManager->getCharacter()].img->setFrameX(0);

	if (CAMERAMANAGER->getSwitchStart() && CAMERAMANAGER->getIsFade())
	{
		if (_button_switch.rc.top > 663)
			_button_switch.rc.top -= 663 / 80;
		if (_button_switch.alpha < 255)
			_button_switch.alpha += 15;
	}
	else
	{
		if (_button_switch.rc.top < WINSIZEY)
			_button_switch.rc.top += 663 / 80;
		if (_button_switch.alpha > 0)
			_button_switch.alpha -= 15;
	}

	_button_switch.rc = RectMake(_button_switch.rc.left, _button_switch.rc.top, _button_switch.img->getWidth(), _button_switch.img->getHeight());
}

void GUI::render(void)
{
	for (int i = 0; i < _vHeartRed.size(); i++)
	{
		_vHeartRed[i].shadow->alphaRender(getMemDC(), _vHeartRed[i].rc.left, _vHeartRed[i].rc.top, 150);
		_vHeartRed[i].img->render(getMemDC(), _vHeartRed[i].rc.left, _vHeartRed[i].rc.top);
	}
	for (int i = 0; i < _vHeartYellow.size(); i++)
	{
		_vHeartYellow[i].shadow->alphaRender(getMemDC(), _vHeartYellow[i].rc.left, _vHeartYellow[i].rc.top, 150);
		_vHeartYellow[i].img->render(getMemDC(), _vHeartYellow[i].rc.left, _vHeartYellow[i].rc.top);
	}
	if (_blueFlower.isActive)
		_blueFlower.img->render(getMemDC(), _blueFlower.rc.left, _blueFlower.rc.top);
	if (_mineral.isActive)
		_mineral.img->render(getMemDC(), _mineral.rc.left, _mineral.rc.top);

	for (int i = 0; i < 2; i++)
	{
		_icon[i].shadow->alphaFrameRender(getMemDC(), _icon[i].rc.left, _icon[i].rc.top, _icon[i].img->getFrameX(), _icon[i].img->getFrameY(), 150);
		_icon[i].img->frameRender(getMemDC(), _icon[i].rc.left, _icon[i].rc.top, _icon[i].img->getFrameX(), _icon[i].img->getFrameY());
	}

	_button_switch.img->alphaRender(getMemDC(), _button_switch.rc.left, _button_switch.rc.top, _button_switch.alpha);

	char str[128];
	HFONT myFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "FirstFont-Bold");
	HFONT oldFont = (HFONT)SelectObject(getMemDC(), myFont);
	SetBkMode(getMemDC(), TRANSPARENT);

	SetTextColor(getMemDC(), RGB(50, 50, 50));
	sprintf_s(str, "%d/3", _blueFlowerCount);
	TextOut(getMemDC(), 1195, 53, str, strlen(str));
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	TextOut(getMemDC(), 1195, 51, str, strlen(str));

	SetTextColor(getMemDC(), RGB(50, 50, 50));
	sprintf_s(str, "%d/3", _mineralCount);
	TextOut(getMemDC(), 1195, 118, str, strlen(str));
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	TextOut(getMemDC(), 1195, 116, str, strlen(str));

	SelectObject(getMemDC(), oldFont);
	DeleteObject(myFont);
}
