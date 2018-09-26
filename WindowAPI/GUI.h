#pragma once
#include "gameNode.h"

class playerManager;

class GUI : public gameNode
{
private:
	playerManager * _playerManager;
	vector<tagImage> _vHeartRed;
	vector<tagImage> _vHeartYellow;
	tagImage _button_switch;
	tagImage _icon[2];
	tagImage _blueFlower;
	int _blueFlowerCount;
	tagImage _mineral;
	int _mineralCount;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	vector<tagImage> getHeartRed() { return _vHeartRed; }
	vector<tagImage> getHeartYellow() { return _vHeartYellow; }

	void setPlayerManager(playerManager* playerManager) { _playerManager = playerManager; }

	GUI() {}
	~GUI() {}
};

