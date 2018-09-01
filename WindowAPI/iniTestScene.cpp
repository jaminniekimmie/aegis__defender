#include "stdafx.h"
#include "iniTestScene.h"

HRESULT iniTestScene::init(void)
{
	return S_OK;
}

void iniTestScene::release(void)
{
}

void iniTestScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//섹션, 키, 밸류
		//[세원]
		//노력=99
		//집중=70
		//[기훈]
		//롤실력=20
		//코딩력=80
		INIDATA->addData("세원", "노력", "99");
		INIDATA->addData("세원", "집중", "70");
		INIDATA->addData("기훈", "롤실력", "20");
		INIDATA->addData("기훈", "코딩력", "80");
		INIDATA->addData("기훈", "실수", "15.8f");
		//파일이름으로 세이브
		INIDATA->saveINI("ARVR");
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		//int num = INIDATA->loadDataInteger("ARVR", "기훈", "롤실력");
		float num = INIDATA->loadDataFloat("ARVR", "기훈", "실수");
		cout << "기훈이 실수값: " << num << endl;
	}
}

void iniTestScene::render(void)
{
}
