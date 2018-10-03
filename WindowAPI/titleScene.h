#pragma once
#include "gameNode.h"
class titleScene : public gameNode
{
	tagImage _mainMenu;
	tagImage _soundFrame;
	tagImage _pressAnyButton;
	tagImage _soundMenu;
	int _index;
	int _titleIndex;
	int _alpha;
	int _count;
	int _frameSpeed;
	float _volume_BGM;
	float _volume_sfx;
	bool _sceneSwitch;
	bool _soundMenuOn;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void pressAnyButton();
	void frameChangeLoop();
	void soundMenu();
	void soundMenuRender();
	void keyInput();
	void sceneSwitch();

	titleScene() {}
	~titleScene() {}
};

