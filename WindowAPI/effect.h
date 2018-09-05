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
	image * _effectImg;		//이펙트 이미지(반드시 프레임이미지 사용하자)
	animation* _effectAni;	//이펙트 애니메이션

	int _x, _y;				//이펙트 터트릴 위치좌표
	float _effectFPS;		//이펙트 속도
	bool _isRunning;		//이펙트 재생중이냐?

public:
	HRESULT init(image* effectImg, float effectFPS);
	void release(void);
	void update(void);
	void render(void);

	//내가 원하는 좌표에 이펙트 시작하기
	void startEffect(int x, int y);
	//이펙트 멈추기
	void stopEffect();

	//이펙트가 재생중인지 상태값 가져오기
	bool getIsRunning() { return _isRunning; }

	effect() : _effectImg(NULL), _effectAni(NULL), _isRunning(false), _x(0), _y(0) {}
	~effect() {}
};

