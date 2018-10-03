#pragma once
#include "gameNode.h"

//=============================================================
//	## bullet ## (�����Ѿ� - ������� ����� �ȴ�)
//=============================================================
class bullet : public gameNode
{
private:
	//�Ѿ� ����ü�� ���� ����, �ݺ���
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;
	vector<tagBullet> _vParticle;
	vector<tagBullet>::iterator _viParticle;
	vector<tagBullet> _vMagazine;
	vector<tagBullet>::iterator _viMagazine;

private:
	const char* _imageName;		//�Ѿ� �̹��� �̸�(Ű��)
	float _range;			//�Ѿ� ��Ÿ�
	int _bulletMax;			//�Ѿ� �ִ밹��
	bool _isFrameImg;		//�̹����Ŵ����� ��� �ִ� �̹����� �������� �ֳ� ����?

public:
	HRESULT init(const char* imageName, int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);

	//�Ѿ˹߻�
	void fire(float x, float y, float angle, float speed);
	//�Ѿ˹���
	void move();
	
	void collision();

	//�Ѿ˻���
	void removeBullet(int index);

	//�Ѿ˺��� ��������
	vector<tagBullet> getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator getViBullet() { return _viBullet; }
	vector<tagBullet> getVParticle() { return _vParticle; }
	vector<tagBullet>::iterator getViParticle() { return _viParticle; }
	vector<tagBullet> getVMagazine() { return _vMagazine; }
	vector<tagBullet>::iterator getViMagazine() { return _viMagazine; }

	bullet() {}
	~bullet() {}
};

//=============================================================
//	## triBullet ## (triBullet[0] -> �迭ó�� �̸� �����صΰ� �Ѿ˹߻�)
//=============================================================
class triBullet : public gameNode
{
private:
	//�Ѿ� ����ü�� ���� ����, �ݺ���
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;
	vector<tagBullet> _vParticle;
	vector<tagBullet>::iterator _viParticle;
	vector<tagBullet> _vMagazine;
	vector<tagBullet>::iterator _viMagazine;

private:
	const char * _imageName;
	float _range;			//�Ѿ� ��Ÿ�
	int _bulletMax;			//�Ѿ� �ִ밹��

public:
	HRESULT init(const char * imageName, int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);

	//�Ѿ˹߻�
	void fire(float x, float y, float angle, float speed);
	//�Ѿ˹���
	void move();

	void collision();

	vector<tagBullet> getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator getViBullet() { return _viBullet; }
	vector<tagBullet> getVParticle() { return _vParticle; }
	vector<tagBullet>::iterator getViParticle() { return _viParticle; }
	vector<tagBullet> getVMagazine() { return _vMagazine; }
	vector<tagBullet>::iterator getViMagazine() { return _viMagazine; }

	triBullet() {}
	~triBullet() {}
};

//=============================================================
//	## arrow ## (�����Ѿ� - ������� ����� �ȴ�)
//=============================================================
class arrow : public gameNode
{
private:
	//�Ѿ� ����ü�� ���� ����, �ݺ���
	vector<tagBullet> _vArrow;
	vector<tagBullet>::iterator _viArrow;
	vector<tagBullet> _vParticle;
	vector<tagBullet>::iterator _viParticle;

private:
	const char* _imageName;		//�Ѿ� �̹��� �̸�(Ű��)
	float _range;			//�Ѿ� ��Ÿ�
	int _arrowMax;			//�Ѿ� �ִ밹��
	int _gravity;
	bool _isFrameImg;		//�̹����Ŵ����� ��� �ִ� �̹����� �������� �ֳ� ����?

public:
	HRESULT init(const char* imageName, int arrowMax, float range);
	void release(void);
	void update(void);
	void render(void);

	//�Ѿ˹߻�
	void fire(float x, float y, float angle, float speed);
	//�Ѿ˹���
	void move();

	void collision();

	//�Ѿ˻���
	void removeArrow(int index);

	//�Ѿ˺��� ��������
	vector<tagBullet> getVArrow() { return _vArrow; }
	vector<tagBullet>::iterator getViArrow() { return _viArrow; }
	vector<tagBullet> getVParticle() { return _vParticle; }
	vector<tagBullet>::iterator getViParticle() { return _viParticle; }

	arrow() {}
	~arrow() {}
};

//=============================================================
//	## triBullet ## (triBullet[0] -> �迭ó�� �̸� �����صΰ� �Ѿ˹߻�)
//=============================================================
class triArrow : public gameNode
{
private:
	//�Ѿ� ����ü�� ���� ����, �ݺ���
	vector<tagBullet> _vArrow;
	vector<tagBullet>::iterator _viArrow;
	vector<tagBullet> _vParticle;
	vector<tagBullet>::iterator _viParticle;

private:
	const char * _imageName;
	float _range;			//�Ѿ� ��Ÿ�
	int _gravity;
	int _arrowMax;			//�Ѿ� �ִ밹��

public:
	HRESULT init(const char * imageName, int arrowMax, float range);
	void release(void);
	void update(void);
	void render(void);

	//�Ѿ˹߻�
	void fire(float x, float y, float angle, float speed);
	//�Ѿ˹���
	void move();

	void collision();

	vector<tagBullet> getVArrow() { return _vArrow; }
	vector<tagBullet>::iterator getViArrow() { return _viArrow; }
	vector<tagBullet> getVParticle() { return _vParticle; }
	vector<tagBullet>::iterator getViParticle() { return _viParticle; }

	triArrow() {}
	~triArrow() {}
};

//=============================================================
//	## block ##
//=============================================================
class block : public gameNode
{
private:
	//�Ѿ� ����ü�� ���� ����, �ݺ���
	vector<tagBullet> _vBlock;
	vector<tagBullet>::iterator _viBlock;

private:
	const char * _imageName;
	const char * _shadowName;
	int _frameSpeed;
	float _speed;
	bool _isFrameImg;

public:
	HRESULT init(const char * imageName, const char * shadowName, float speed, bool isFrameImg = false);
	void release(void);
	void update(void);
	void render(void);

	//�Ѿ˹߻�
	void build(float x, float y);
	//�Ѿ˹���
	void move(int dir);
	//�Ѿ˻���
	void removeBlock(int index);
	void activate();
	void collision();
	void frameChange();

	vector<tagBullet> getVBlock() { return _vBlock; }
	vector<tagBullet>::iterator getViblock() { return _viBlock; }

	block() {}
	~block() {}
};