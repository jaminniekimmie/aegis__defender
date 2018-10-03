#pragma once
#include "gameNode.h"
#include "loading.h"

class loadingCharScene : public gameNode
{
private:
	loading * _loading;
	tagImage _player[2];
	image* _background;
	BYTE _alpha;
	int _rand;
	int _count;
	int _index;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//로딩이미지 함수(이곳에 이미지를 전부 넣어라)
	void loadingImage();
	//로딩사운드 함수(이곳에 사운드를 전부 넣어라)
	void loadingSound();
	void loadingEffect();
	void frameChange();

	loadingCharScene() {}
	~loadingCharScene() {}
};

