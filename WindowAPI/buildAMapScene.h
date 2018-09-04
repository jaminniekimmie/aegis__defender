#pragma once
#include "gameNode.h"
#include "tileMap.h"
#include "playerManager.h"

class buildAMapScene : public gameNode
{
private:
	tileMap* _tileMap;
	playerManager* _playerManager;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	buildAMapScene() {}
	~buildAMapScene() {}
};