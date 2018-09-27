#pragma once
#include "gameNode.h"

class effect : public gameNode
{
private:
	image * _effectImg;		//����Ʈ �̹���(�ݵ�� �������̹��� �������)
	animation* _effectAni;	//����Ʈ �ִϸ��̼�
	BYTE _alpha;

	int _x, _y;				//����Ʈ ��Ʈ�� ��ġ��ǥ
	float _effectFPS;		//����Ʈ �ӵ�
	bool _isRunning;		//����Ʈ ������̳�?
	bool _isFadeOut;
	bool _isFloating;
	bool _isTransluscent;

public:
	HRESULT init(image* effectImg, float effectFPS, bool isFadeOut, bool isFloating);
	void release(void);
	void update(void);
	void render(void);

	//���� ���ϴ� ��ǥ�� ����Ʈ �����ϱ�
	void startEffect(int x, int y);
	//����Ʈ ���߱�
	void stopEffect();

	//����Ʈ�� ��������� ���°� ��������
	bool getIsRunning() { return _isRunning; }

	effect() : _effectImg(NULL), _effectAni(NULL), _isRunning(false), _x(0), _y(0) {}
	~effect() {}
};