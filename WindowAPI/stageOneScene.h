#pragma once
#include "gameNode.h"
#include "playerManager.h"

class stageOneScene : public gameNode
{
private:
	playerManager* _playerManager;
	RECT _rcCamera;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	stageOneScene() {}
	~stageOneScene() {}
};

