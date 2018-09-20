#pragma once
#include "singletonBase.h"

class backgroundElements;
class foregroundElements;

class renderManager : public singletonBase<renderManager>
{
private:
	multimap<float, backgroundElements *> backgroundList;
	multimap<float, foregroundElements *> foregroundList;

public:
	HRESULT init();
	void release();
	void render(HDC hdc);
	void backgroundRender(HDC hdc);
	void foregroundRender(HDC hdc);

	void addBackground(float z, backgroundElements *backElements);
	void addForeground(float z, foregroundElements *foreElements);
	void clearBackground();
	void clearForeground();


	renderManager() {}
	~renderManager() {}
};

