#pragma once
//=============================================================
//	## hpBar ## (���α׷����� = ü�¹�)
//=============================================================

class pHpBar
{
private:
	RECT _rcHp;					//ü�¹� ��Ʈ
	int _x, _y;					//ü�¹� ��ġ��ǥ
	float _frontWidth;				//ü�¹� ���α���
	float _height;				//ü�¹� ���α���
	float _backWidth;
	float _maxWidth;

	image* _hpBarFront;	//ü�¹� �� �̹���
	image* _hpBarBack;	//ü�¹� �� �̹���

public:
	//ü�¹� �ʱ�ȭ(���̹���Ű, ���̹���Ű, x, y, ���α���, ���α���)
	HRESULT init(const char* frontImageKey, const char* backImageKey, int x, int y);
	void release(void);
	void update(void);
	void render(HDC hdc);

	//ü�¹� ������ �����ϱ�
	void setGauge(float currentHp, float maxHp);

	//ü�¹� ��ġ ��ǥ �����ϱ�
	void setX(int x) { _x = x; }
	void setY(int y) { _y = y; }
	void setPosition(int x, int y) { _x = x, _y = y; }
	//ü�¹� ��Ʈ ��������
	RECT getRect() { return _rcHp; }

	pHpBar() {}
	~pHpBar() {}
};

