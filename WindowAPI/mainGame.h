#pragma once
#include "gameNode.h"
/*앞으로는 씬 헤더파일만 추가해준다*/
#include "pixelCollision.h"
#include "sceneTest.h"
#include "iniTestScene.h"
#include "loadingBlackScene.h"
#include "loadingOpenScene.h"
#include "soundTestScene.h"
#include "aniTestScene.h"
#include "rotateTestScene.h"
#include "buildAMapScene.h"
#include "stageOneScene.h"
#include "stageTwoScene.h"

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

