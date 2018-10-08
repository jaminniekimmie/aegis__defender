#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include "playerManager.h"
#include "backgroundElements.h"
#include "foregroundElements.h"

class stageOneScene : public gameNode
{
private:
	playerManager* _playerManager;
	tagTile _tiles[TILEX * TILEY];
	RECT _rcLetterBox[2];
	image * _pixelTiles;
	image * _pixelMap;
	RECT _rcCamera;
	BYTE _alpha;
	BYTE _victoryAlpha;
	bool _camDebug;
	bool _sceneSwitch;
	int _switchCount;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void backgroundElementsInit();
	void cameraAdjustment(PLAYERCHARACTER character);
	void sceneSwitch();
	void tileMapLoad();
	void tileMapRender();
	void mapRender();

	stageOneScene() {}
	~stageOneScene() {}
};

