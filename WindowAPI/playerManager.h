#pragma once
#include "gameNode.h"
#include "player.h"

class playerManager : public gameNode
{
private:
	player * _player;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	player * getPlayer() { return _player; }
	
	void playerJumpFall();
	void playerBackstep();
	void fromStateToIdle();

	playerManager() {}
	~playerManager() {}
};

