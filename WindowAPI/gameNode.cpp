#include "stdafx.h"
#include "gameNode.h"

//=============================================================
//	## 초기화 ## init(void)
//=============================================================
int _delta;
HRESULT gameNode::init(void)
{
	return S_OK;
}

HRESULT gameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	if (managerInit)
	{
		KEYMANAGER->init();					//키매니져 초기화
		RND->init();						//랜더펑션 초기화
		IMAGEMANAGER->init();				//이미지매니져 초기화
		SAVEDATA->init();					//세이브데이터 초기화
		TXTDATA->init();					//TXT데이터 초기화
		SCENEMANAGER->init();				//씬매니져 초기화
		INIDATA->init();					//INI데이터 초기화
		TIMEMANAGER->init();				//타임매니져 초기화
		SOUNDMANAGER->init();				//사운드매니져 초기화
		FRAMEMANAGER->init();
		EFFECTMANAGER->init();				//이펙트매니져 초기화
		CAMERAMANAGER->init();				//카메라매니져 초기화
		COLLISIONMANAGER->init();			//컬리젼매니져 초기화
		RENDERMANAGER->init();				//렌더매니져 초기화
	}

	return S_OK;
}

//=============================================================
//	## 해제 ## release(void)
//=============================================================
void gameNode::release(void)
{
	if (_managerInit)
	{
		//키매니져 싱글톤 해제
		KEYMANAGER->release();
		KEYMANAGER->releaseSingleton();
		//랜덤펑션 싱글톤 해제
		RND->release();
		RND->releaseSingleton();
		//이미지매니져 싱글톤 해제
		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();
		//세이브데이터 싱글톤 해제
		SAVEDATA->release();
		SAVEDATA->releaseSingleton();
		//TXT데이터 싱글톤 해제
		TXTDATA->release();
		TXTDATA->releaseSingleton();
		//씬매니져 싱글톤 해제
		SCENEMANAGER->release();
		SCENEMANAGER->releaseSingleton();
		//INI데이터 싱글톤 해제
		INIDATA->release();
		INIDATA->releaseSingleton();
		//타임매니져 싱글톤 해제
		TIMEMANAGER->release();
		TIMEMANAGER->releaseSingleton();
		//사운드매니져 싱글톤 해제
		SOUNDMANAGER->release();
		SOUNDMANAGER->releaseSingleton();
		//프레임매니져 싱글톤 해제
		FRAMEMANAGER->release();
		FRAMEMANAGER->releaseSingleton();
		//이펙트매니져 싱글톤 해제
		EFFECTMANAGER->release();
		EFFECTMANAGER->releaseSingleton();
		//카메라매니져 싱글톤 해제
		CAMERAMANAGER->release();
		CAMERAMANAGER->releaseSingleton();
		//컬리젼매니져 싱글톤 해제
		COLLISIONMANAGER->release();
		COLLISIONMANAGER->releaseSingleton();
		//몬스터매니져 싱글톤 해제
		MONSTERMANAGER->release();
		MONSTERMANAGER->releaseSingleton();
		//렌더매니져 싱글톤 해제
		RENDERMANAGER->release();
		RENDERMANAGER->releaseSingleton();
		//오브젝트매니져 싱글톤 해제
		OBJECTMANAGER->release();
		OBJECTMANAGER->releaseSingleton();
	}

	//DC 해제
	ReleaseDC(_hWnd, _hdc);
}

//=============================================================
//	## 업데이트 ## update(void)
//=============================================================
void gameNode::update(void)
{
}

//=============================================================
//	## 렌더 ## render(void)
//=============================================================
void gameNode::render(void)
{
}

//=============================================================
//	## 메인프로시져 ##
//=============================================================
LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_MOUSEMOVE:		
		_ptMouse.x = LOWORD(lParam);
		_ptMouse.y = HIWORD(lParam);
		break;
	case WM_KEYDOWN:		
		switch (wParam)
		{
		case VK_ESCAPE:		
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		}
		break;
	case WM_DESTROY:		
		PostQuitMessage(0);
		return 0;
	case WM_MOUSEWHEEL:
		int delta = GET_WHEEL_DELTA_WPARAM(wParam);
		switch (delta)
		{
		case 120:
			if (0 < _delta && _delta < 10)
				_delta -= cosf(0.0f);
			break;

		case -120:
			if ( 0 <= _delta && _delta < 9)
				_delta += cosf(0.0f);
			break;
		}
		_mouseWheel = (SHORT)HIWORD(wParam);
		break;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
