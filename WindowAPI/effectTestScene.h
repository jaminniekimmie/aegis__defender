#pragma once
#include "gameNode.h"
#include "effect.h"		//이펙트 클래스 추가

class effectTestScene : public gameNode
{
private:
	effect * _effect;	//이펙트 클래스 선언

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	effectTestScene() {}
	~effectTestScene() {}
};

