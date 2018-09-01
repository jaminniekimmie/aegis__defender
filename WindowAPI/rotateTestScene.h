#pragma once
#include "gameNode.h"

class rotateTestScene : public gameNode
{
private:
	image* _missile;
	image* _frameMissle;
	float _angle;
	int _count;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	rotateTestScene() {}
	~rotateTestScene() {}
};

