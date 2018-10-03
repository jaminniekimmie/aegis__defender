#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include "playerManager.h"

class tileTestScene : public gameNode
{
private:
	playerManager * _playerManager;
	tagTile _tiles[TILEX * TILEY];
	RECT _rcLetterBox[2];
	image * _pixelTiles;
	image * _pixelMap;
	RECT _rcCamera;
	BYTE _alpha;
	bool _camDebug;
	bool _sceneSwitch;
	int _switchCount;
	int _rand;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void cameraAdjustment();
	void mapLoad();

	tileTestScene() {}
	~tileTestScene() {}
};

