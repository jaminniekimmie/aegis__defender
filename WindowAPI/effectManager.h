#pragma once
#include "singletonBase.h"
//����Ʈ Ŭ���� ���漱��(���� ������)
class effect;

class effectManager : public singletonBase <effectManager>
{
private:
	//����Ʈ Ŭ������ ���� ���� �� �ݺ���
	typedef vector<effect*> vEffect;
	typedef vector<effect*>::iterator viEffect;
	//����Ʈ�� ��Ƴ��� ���͸� ���� ��
	typedef map<string, vEffect> mEffect;
	typedef map<string, vEffect>::iterator miEffect;

private:
	mEffect _mEffect;		//����Ʈ���Ͱ� ����ִ� ��

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//����Ʈ �߰�(����ƮŰ��, �̹���Ű��, ����Ʈ�ӵ�, ���۰���)
	void addEffect(string effectName, const char* imageName, float effectFPS, int buffer, bool isFadeOut = false);
	//����Ʈ �÷���
	void play(string effectName, int x, int y);

	effectManager() {}
	~effectManager() {}
};

//#pragma once
//#include "singletonBase.h"
////����Ʈ Ŭ���� ���漱��(���� ������)
//class effect;
//
//class effectManager : public singletonBase <effectManager>
//{
//	effect* _jumpDust;
//	effect* _landDust;
//	effect* _runDust;
//
//	bool _isJumpStart;
//	bool _isLandStart;
//	bool _isRunStart;
//public:
//	void jumpDust(float x, float y);
//	void landDust(float x, float y);
//	void runDust(float x, float y);
//
//	HRESULT init(void);
//	void release(void);
//	void update(void);
//	void render();
//
//	effectManager() {}
//	~effectManager() {}
//};
//


