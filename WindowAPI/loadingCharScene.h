#pragma once
#include "gameNode.h"

class loadingCharScene : public gameNode
{
private:
	tagImage _player[2];
	image* _background;
	BYTE _alpha;
	int _rand;
	int _loadingCount;
	int _count;
	int _index;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void frameChange();

	loadingCharScene() {}
	~loadingCharScene() {}
};

