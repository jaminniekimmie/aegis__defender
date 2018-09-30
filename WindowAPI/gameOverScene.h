#pragma once
#include "gameNode.h"
class gameOverScene : public gameNode
{
	image * _gameOverImg;
	int _index;
	int _alpha;
	bool _sceneSwitch;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	gameOverScene() {}
	~gameOverScene() {}
};

