#pragma once
#include "gameNode.h"
/*�����δ� �� ������ϸ� �߰����ش�*/
#include "loadingBlackScene.h"
#include "loadingOpenScene.h"
#include "loadingCharScene.h"
#include "buildAMapScene.h"
#include "stageOneScene.h"
#include "stageTwoScene.h"
#include "gameOverScene.h"

class mainGame : public gameNode
{
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	mainGame() {}
	~mainGame() {}
};

