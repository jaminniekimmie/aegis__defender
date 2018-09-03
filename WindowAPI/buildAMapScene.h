#pragma once
#include "gameNode.h"
#include "tileMap.h"

class buildAMapScene : public gameNode
{
private:
	tileMap * _tileMap;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	buildAMapScene() {}
	~buildAMapScene() {}
};