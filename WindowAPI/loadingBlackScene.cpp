#include "stdafx.h"
#include "loadingBlackScene.h"

HRESULT loadingBlackScene::init(void)
{
	//�ε�Ŭ���� �ʱ�ȭ
	_loading = new loading;
	_loading->init();

	_background = IMAGEMANAGER->addImage("bgLoadingScene", "tex/background/blackSolid_01.bmp", WINSIZEX, WINSIZEY);

	//�̹��� �� ���� �ε�
	this->loadingImage();
	this->loadingSound();

	return S_OK;
}

void loadingBlackScene::release(void)
{
	//�ε�Ŭ���� ����
	_loading->release();
	SAFE_DELETE(_loading);
}

void loadingBlackScene::update(void)
{
	//�ε�Ŭ���� ������Ʈ
	_loading->update();

	//�ε��Ϸ��� ������
	if (_loading->loadingDone())
	{
		SCENEMANAGER->loadScene("����");
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		float num = _loading->getLoadItem().size();
		float cur = _loading->getCurrentGauge();
		float per = cur / num * 100;
		cout << "��ü ���ϰ��� : " << num << endl;
		cout << "���� �ε����� : " << cur << endl;
		cout << per << " %" << endl;
	}
}

void loadingBlackScene::render(void)
{
	//�ε�Ŭ���� ����
	_loading->render();

	_background->render(getMemDC());

	//if (_loading->getCurrentGauge() < _loading->getLoadItem().size())
	//{
	//	char str[128];
	//	sprintf_s(str, "%s.bmp", _loading->getLoadItem()[_loading->getCurrentGauge()]->getImageResource().keyName.c_str());
	//	TextOut(getMemDC(), 120, 430, str, strlen(str));
	//}

	float num = _loading->getLoadItem().size();
	float cur = _loading->getCurrentGauge();
	float per = cur / num * 100;
	char str[128];
	HFONT myFont = CreateFont(63, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Flood Std");
	HFONT oldFont = (HFONT)SelectObject(getMemDC(), myFont);
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	SetBkMode(getMemDC(), TRANSPARENT);
	
	sprintf_s(str, "LOADING %.f", per);
	TextOut(getMemDC(), 903, 635, str, strlen(str));
	
	SelectObject(getMemDC(), oldFont);
	DeleteObject(myFont);
}

//�ε��̹��� �Լ�(�̰��� �̹����� ���� �־��)
void loadingBlackScene::loadingImage()
{
	//_loading->loadImage();
	//_loading->loadFrameImage();
	//_loading->loadSound();
	SetBkMode(getMemDC(), TRANSPARENT);
	//�ε��� �ʹ� ������ ����Ǽ� õõ�� ���ư����� �׽�Ʈ������ �����
	for (int i = 0; i < 500; i++)
	{
		char str[128];
		sprintf_s(str, "%s_%d", "testImage", i + 1);
		_loading->loadImage(str, WINSIZEX, WINSIZEY);
	}
	//IMAGEMANAGER->addImage("mountain", "mountain.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	//��׶��� �̹���
	for (int i = 0; i < 500; i++)
	{
		char str[128];
		sprintf_s(str, "%s_%d", "mountain", i + 1);
		_loading->loadImage(str, "mountain.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	}
}

//�ε����� �Լ�(�̰��� ���带 ���� �־��)
void loadingBlackScene::loadingSound()
{
	_loading->loadSound("����1", "���.mp3");
	_loading->loadSound("����2", "���1.mp3");
}
