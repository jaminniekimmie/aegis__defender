#include "stdafx.h"
#include "mainGame.h"

//=============================================================
//	## 초기화 ## init(void)
//=============================================================
HRESULT mainGame::init(void)
{
	gameNode::init(TRUE);
	//이곳에서 초기화를 한다
	
	//앞으로 메인게임 클래스 안에서는 씬들만 관리한다
	//그리고 각각의 씬들이 메인게임 역할을 하면 된다

	/*씬추가*/
	SCENEMANAGER->addScene("흑로딩화면", new loadingBlackScene);
	SCENEMANAGER->addScene("훼이크로딩화면", new fakeLoadingScene);
	SCENEMANAGER->addScene("오픈로딩화면", new loadingOpenScene);
	SCENEMANAGER->addScene("캐릭터로딩화면", new loadingCharScene);
	SCENEMANAGER->addScene("게임오버화면", new gameOverScene);
	SCENEMANAGER->addScene("타이틀화면", new titleScene);
	SCENEMANAGER->addScene("맵툴", new buildAMapScene);
	SCENEMANAGER->addScene("타일테스트화면", new tileTestScene);
	SCENEMANAGER->addScene("스테이지원", new stageOneScene);

	/*현재씬 설정*/
	SCENEMANAGER->loadScene("오픈로딩화면");

	return S_OK;
}

//=============================================================
//	## 해제 ## release(void)
//=============================================================
void mainGame::release(void)
{
	gameNode::release();
}

//=============================================================
//	## 업데이트 ## update(void)
//=============================================================
void mainGame::update(void)
{
	//씬매니져 업데이트
	SCENEMANAGER->update();

	//사운드매니져 업데이트
	SOUNDMANAGER->update();

	//이펙트매니져 업데이트
	EFFECTMANAGER->update();

	//카메라매니져 업데이트
	CAMERAMANAGER->update();
}

//=============================================================
//	## 렌더 ## render(void)
//=============================================================
void mainGame::render(void)
{
	//흰색 빈 비트맵(이것도 렌더에 그냥 둘것!!)
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
//=============================================================

	//씬매니져 렌더
	SCENEMANAGER->render();

	//이펙트매니져 렌더
	EFFECTMANAGER->render();

	//타임매니져 렌더
	TIMEMANAGER->render(getMemDC());

	string test = to_string(_ptMouse.x) + "," + to_string(_ptMouse.y);
	OutputDebugString((test + "\n").c_str());

//=============================================================
	//백버퍼의 내용을 HDC에 그린다 (이것도 렌더에 그냥 둘것!!)
	this->getBackBuffer()->render(getHDC());
}
