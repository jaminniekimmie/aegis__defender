#pragma once
#include "singletonBase.h"
#include "image.h"
//=============================================================
//	## imageManager ## (이미지 매니져)
//=============================================================

class imageManager : public singletonBase <imageManager>
{
private:
	//typedef int INT;
	//int a; //INT b; => 둘다 똑같은 정수형
	typedef map<string, image*> mapImageList;			//맵으로 만든 이미지목록
	typedef map<string, image*>::iterator mapImageIter;	//맵으로 만든 이미지목록의 반복자
	
private:
	mapImageList _mImageList;		//실제 이미지클래스를 담을 STL맵
	//map<string, image*> _mImageList; => 위의 코드와 100% 동일함

public:
	//이미지 매니져 초기화
	HRESULT init();
	//이미지 매니져 해제
	void release();

	//빈 비트맵으로 초기화
	image* addImage(string strKey, int width, int height);
	//이미지 파일로 초기화 (주사용)
	image* addImage(string strKey, const char* fileName, int width, int height, bool isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	image* addImage(string strKey, const char* fileName, float x, float y, int width, int height, bool isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	//프레임 이미지 파일로 초기화 (주사용)
	image* addFrameImage(string strKey, const char* fileName, int width, int height, int frameX, int frameY, bool isTrans = TRUE, COLORREF transColor = RGB(255, 0, 255));
	image* addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans = TRUE, COLORREF transColor = RGB(255, 0, 255));

	//이미지 키값으로 찾기
	image* findImage(string strKey);
	//이미지 키값으로 삭제
	BOOL deleteImage(string strKey);
	//이미지 전체 삭제
	BOOL deleteAll();

//=============================================================
//	## 일반렌더 ##
//=============================================================
	void render(string strKey, HDC hdc, int destX = 0, int destY = 0);
	void render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

//=============================================================
//	## 알파렌더 ##
//=============================================================
	void alphaRender(string strKey, HDC hdc, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);
	void alphaFrameRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha);
	void alphaFrameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);

//=============================================================
//	## 프레임렌더 ##
//=============================================================
	void frameRender(string strKey, HDC hdc, int destX, int destY);
	void frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

//=============================================================
//	## 로테이트렌더 ## (이미지 회전)
//=============================================================
	void rotateRender(HDC hdc, string strKey, float centerX, float centerY, float angle);
	void rotateFrameRender(HDC hdc, string strKey, float centerX, float centerY, float angle);
	void rotateAlphaRender(HDC hdc, string strKey, float centerX, float centerY, float angle, BYTE alpha);

//=============================================================
//	## 루프렌더 ##
//=============================================================
	void loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	void loopAlphaRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);

//=============================================================
//	## 스트레치렌더 ## (이미지 스케일링)
//=============================================================
	void stretchRender(string strKey, HDC hdc, int destX, int destY, float scale = 1.0f);
	void stretchFrameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, float scale = 1.0f);


	imageManager() {}
	~imageManager() {}
};

