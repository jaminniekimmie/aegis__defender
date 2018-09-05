//#pragma once
//#include "gameNode.h"
//
//class effect : public gameNode
//{
//private:
//	image * _image;
//	float _x;
//	float _y;
//	int _index;
//	int _count;
//	int _frameSpeed;
//	bool _isLeft;
//	bool _isFinish;
//public:
//	void setting(float x, float y)
//	{
//		_x = x - _image->getFrameWidth() / 2;
//		_y = y - _image->getFrameHeight() / 2;
//		_index = 0;
//		_count = 0;
//		_isLeft = false;
//		_isFinish = false;
//	}
//	int getIndex() { return _index; }
//	int getCount() { return _count; }
//	bool finish() { return _isFinish; }
//
//	void setX(float x) { _x = x; }
//	void setY(float y) { _y = y; }
//	void setIndex(int index) { _index = index; }
//	void setCount(int count) { _count = count; }
//	void setIsFinish(bool isFinish) { _isFinish = isFinish; }
//	HRESULT init(string str, int frameSpeed);
//	void release(void);
//	void update(void);
//	void render(void);
//
//	effect() {}
//	~effect() {}
//};

#pragma once
#include "gameNode.h"

class effect : public gameNode
{
private:
	image * _effectImg;		//����Ʈ �̹���(�ݵ�� �������̹��� �������)
	animation* _effectAni;	//����Ʈ �ִϸ��̼�

	int _x, _y;				//����Ʈ ��Ʈ�� ��ġ��ǥ
	float _effectFPS;		//����Ʈ �ӵ�
	bool _isRunning;		//����Ʈ ������̳�?

public:
	HRESULT init(image* effectImg, float effectFPS);
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

