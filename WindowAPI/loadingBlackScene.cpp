#include "stdafx.h"
#include "loadingBlackScene.h"

HRESULT loadingBlackScene::init(void)
{
	//로딩클래스 초기화
	_loading = new loading;
	_loading->init();

	_background = IMAGEMANAGER->addImage("bgLoadingScene", "tex/background/blackSolid_01.bmp", WINSIZEX, WINSIZEY);

	//이미지 및 사운드 로딩
	this->loadingImage();
	this->loadingSound();

	return S_OK;
}

void loadingBlackScene::release(void)
{
	//로딩클래스 해제
	_loading->release();
	SAFE_DELETE(_loading);
}

void loadingBlackScene::update(void)
{
	//로딩클래스 업데이트
	_loading->update();

	//로딩완료후 씬변경
	if (_loading->loadingDone())
	{
		SCENEMANAGER->loadScene("맵툴");
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		float num = _loading->getLoadItem().size();
		float cur = _loading->getCurrentGauge();
		float per = cur / num * 100;
		cout << "전체 파일갯수 : " << num << endl;
		cout << "현재 로딩갯수 : " << cur << endl;
		cout << per << " %" << endl;
	}
}

void loadingBlackScene::render(void)
{
	//로딩클래스 렌더
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

//로딩이미지 함수(이곳에 이미지를 전부 넣어라)
void loadingBlackScene::loadingImage()
{
	//_loading->loadImage();
	//_loading->loadFrameImage();
	//_loading->loadSound();
	SetBkMode(getMemDC(), TRANSPARENT);
	//로딩이 너무 빠르게 진행되서 천천히 돌아가도록 테스트용으로 만들기
	for (int i = 0; i < 500; i++)
	{
		char str[128];
		sprintf_s(str, "%s_%d", "testImage", i + 1);
		_loading->loadImage(str, WINSIZEX, WINSIZEY);
	}
	//IMAGEMANAGER->addImage("mountain", "mountain.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	//백그라운드 이미지
	for (int i = 0; i < 500; i++)
	{
		char str[128];
		sprintf_s(str, "%s_%d", "mountain", i + 1);
		_loading->loadImage(str, "mountain.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	}
}

//로딩사운드 함수(이곳에 사운드를 전부 넣어라)
void loadingBlackScene::loadingSound()
{
	_loading->loadSound("사운드1", "브금.mp3");
	_loading->loadSound("사운드2", "브금1.mp3");
}
