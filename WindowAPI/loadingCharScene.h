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

	//�ε��̹��� �Լ�(�̰��� �̹����� ���� �־��)
	void loadingImage();
	//�ε����� �Լ�(�̰��� ���带 ���� �־��)
	void loadingSound();
	void loadingEffect();
	void frameChange();

	loadingCharScene() {}
	~loadingCharScene() {}
};

