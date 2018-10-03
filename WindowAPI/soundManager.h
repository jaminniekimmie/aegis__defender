#pragma once
#include "singletonBase.h"
/*FMOD ����ϱ� ����*/
#include "SOUND/inc/fmod.hpp"
#pragma comment (lib, "SOUND/lib/fmodex_vc.lib")
using namespace FMOD;
//=============================================================
//	## soundManager ## (���� �Ŵ���)
//=============================================================

//����� ������� (���尹���� 30���� �Ѿ�� ũ�⸦ �� �÷���� �Ѵ�)
#define SOUNDBUFFER 100

class soundManager : public singletonBase <soundManager>
{
private:
	typedef map<string, Sound**> arrSound;
	typedef map<string, Sound**>::iterator arrSoundIter;

private:
	System* _system;		//�ý��� Ŭ����
	Sound** _sound;			//���� Ŭ����
	Channel** _channel;		//ä�� Ŭ����
	string _currentBGM;

	arrSound _mTotalSound;	//�ʿ� ��Ƶ� �����

public:
	HRESULT init(void);
	void release(void);
	void update(void);

	//���� �߰�(Ű��, �����̸�, BGM?, ������ų����?)
	void addSound(string keyName, string soundName, bool bgm = false, bool loop = false);

	//���� ���
	void play(string keyName, bool bgm = false, float volume = 1.0f);//������ 0.0f ~ 1.0f
	//���� ����
	void stop(string keyName);
	//���� �Ͻ�����
	void pause(string keyName);
	//���� �ٽ����
	void resume(string keyName);

	void setVolume(float volume);

	//�÷��� ���̳�?
	bool isPlaySound(string keyName);
	//�Ͻ����� ���̳�?
	bool isPauseSound(string keyName);

	soundManager() : _system(NULL), _sound(NULL), _channel(NULL) {}
	~soundManager() {}
};

