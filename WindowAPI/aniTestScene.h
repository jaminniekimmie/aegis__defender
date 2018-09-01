#pragma once
#include "gameNode.h"
#include "camel.h"

class aniTestScene : public gameNode
{
private:
	camel * _camel;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	aniTestScene() {}
	~aniTestScene() {}
};

