#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include "playerManager.h"

class stageOneScene : public gameNode
{
private:
	playerManager* _playerManager;
	tagTile _mapTiles[TILEX * TILEY];
	image * _pixelTiles;
	RECT _rcCamera;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void mapLoad(void);

	stageOneScene() {}
	~stageOneScene() {}
};

