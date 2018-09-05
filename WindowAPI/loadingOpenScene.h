#pragma once
#include "gameNode.h"
#include "loading.h"

class loadingOpenScene : public gameNode
{
private:
	loading * _loading;
	image * _background;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//�ε��̹��� �Լ�(�̰��� �̹����� ���� �־��)
	void loadingImage();
	//�ε����� �Լ�(�̰��� ���带 ���� �־��)
	void loadingSound();

	loadingOpenScene() {}
	~loadingOpenScene() {}
};

