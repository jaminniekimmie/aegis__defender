#pragma once
#include "gameNode.h"
/*앞으로는 씬 헤더파일만 추가해준다*/
#include "loadingBlackScene.h"
#include "loadingOpenScene.h"
#include "loadingCharScene.h"
#include "fakeLoadingScene.h"
#include "buildAMapScene.h"
#include "stageOneScene.h"
#include "titleScene.h"
#include "gameOverScene.h"
#include "tileTestScene.h"

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

