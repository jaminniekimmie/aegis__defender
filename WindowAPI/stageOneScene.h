#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include "playerManager.h"

class stageOneScene : public gameNode
{
private:
	playerManager* _playerManager;
	tagTile _tiles[TILEX * TILEY];
	image * _pixelTiles;
	RECT _rcCamera;
	BYTE _alpha;
	bool _camDebug;
	bool _sceneSwitch;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void cameraAdjustment();
	void playerSwitch();
	void mapLoad();

	stageOneScene() {}
	~stageOneScene() {}
};

