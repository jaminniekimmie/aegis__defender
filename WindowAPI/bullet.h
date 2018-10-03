#pragma once
#include "gameNode.h"

//=============================================================
//	## bullet ## (공용총알 - 너희들이 만들면 된다)
//=============================================================
class bullet : public gameNode
{
private:
	//총알 구조체를 담을 벡터, 반복자
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;
	vector<tagBullet> _vParticle;
	vector<tagBullet>::iterator _viParticle;
	vector<tagBullet> _vMagazine;
	vector<tagBullet>::iterator _viMagazine;

private:
	const char* _imageName;		//총알 이미지 이름(키값)
	float _range;			//총알 사거리
	int _bulletMax;			//총알 최대갯수
	bool _isFrameImg;		//이미지매니져에 들어 있는 이미지가 프레임이 있냐 없냐?

public:
	HRESULT init(const char* imageName, int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);

	//총알발사
	void fire(float x, float y, float angle, float speed);
	//총알무브
	void move();
	
	void collision();

	//총알삭제
	void removeBullet(int index);

	//총알벡터 가져오기
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
//	## triBullet ## (triBullet[0] -> 배열처럼 미리 장전해두고 총알발사)
//=============================================================
class triBullet : public gameNode
{
private:
	//총알 구조체를 담을 벡터, 반복자
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;
	vector<tagBullet> _vParticle;
	vector<tagBullet>::iterator _viParticle;
	vector<tagBullet> _vMagazine;
	vector<tagBullet>::iterator _viMagazine;

private:
	const char * _imageName;
	float _range;			//총알 사거리
	int _bulletMax;			//총알 최대갯수

public:
	HRESULT init(const char * imageName, int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);

	//총알발사
	void fire(float x, float y, float angle, float speed);
	//총알무브
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
//	## arrow ## (공용총알 - 너희들이 만들면 된다)
//=============================================================
class arrow : public gameNode
{
private:
	//총알 구조체를 담을 벡터, 반복자
	vector<tagBullet> _vArrow;
	vector<tagBullet>::iterator _viArrow;
	vector<tagBullet> _vParticle;
	vector<tagBullet>::iterator _viParticle;

private:
	const char* _imageName;		//총알 이미지 이름(키값)
	float _range;			//총알 사거리
	int _arrowMax;			//총알 최대갯수
	int _gravity;
	bool _isFrameImg;		//이미지매니져에 들어 있는 이미지가 프레임이 있냐 없냐?

public:
	HRESULT init(const char* imageName, int arrowMax, float range);
	void release(void);
	void update(void);
	void render(void);

	//총알발사
	void fire(float x, float y, float angle, float speed);
	//총알무브
	void move();

	void collision();

	//총알삭제
	void removeArrow(int index);

	//총알벡터 가져오기
	vector<tagBullet> getVArrow() { return _vArrow; }
	vector<tagBullet>::iterator getViArrow() { return _viArrow; }
	vector<tagBullet> getVParticle() { return _vParticle; }
	vector<tagBullet>::iterator getViParticle() { return _viParticle; }

	arrow() {}
	~arrow() {}
};

//=============================================================
//	## triBullet ## (triBullet[0] -> 배열처럼 미리 장전해두고 총알발사)
//=============================================================
class triArrow : public gameNode
{
private:
	//총알 구조체를 담을 벡터, 반복자
	vector<tagBullet> _vArrow;
	vector<tagBullet>::iterator _viArrow;
	vector<tagBullet> _vParticle;
	vector<tagBullet>::iterator _viParticle;

private:
	const char * _imageName;
	float _range;			//총알 사거리
	int _gravity;
	int _arrowMax;			//총알 최대갯수

public:
	HRESULT init(const char * imageName, int arrowMax, float range);
	void release(void);
	void update(void);
	void render(void);

	//총알발사
	void fire(float x, float y, float angle, float speed);
	//총알무브
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
	//총알 구조체를 담을 벡터, 반복자
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

	//총알발사
	void build(float x, float y);
	//총알무브
	void move(int dir);
	//총알삭제
	void removeBlock(int index);
	void activate();
	void collision();
	void frameChange();

	vector<tagBullet> getVBlock() { return _vBlock; }
	vector<tagBullet>::iterator getViblock() { return _viBlock; }

	block() {}
	~block() {}
};