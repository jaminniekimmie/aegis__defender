#pragma once
#include "gameNode.h"
#include "tileNode.h"

class tileMap : public gameNode
{
private:
	tagTile _tiles[TILEX * TILEY];	//����ȭ�� Ÿ��(�� 400��)
	tagSampleTile _sampleTiles[SAMPLETILEX * SAMPLETILEY];	//������ȭ�� Ÿ��(�� 160��)
	tagCurrentTile _currentTile;	//����Ÿ��

									//��ư 5��(���̺�, �ε�, ����, ������Ʈ, ���찳)
	CTRL _ctrlSelect;
	CTRL _oldCtrl;
	TERRAIN _terrain;
	OBJECT _object;
	RECT _rcSave, _rcLoad, _rcTerrain, _rcObject, _rcEraser;
	RECT _rcLetterBox[2];
	RECT _rcCamera;
	RECT _rcDrag;
	RECT _rcRange;
	LONG _dragStartX, _dragStartY;
	LONG _rangeEnd;
	POINT _globalPtMouse;
	tagImage _arrowButton[2];
	tagImage _characterMinor;
	tagImage _blackSolid;
	tagImage _buildAMapText;
	tagImage _textBubble_amber;
	tagImage _descBubble_terrain[1];
	tagImage _descBubble_object[3];
	tagImage _button[5];
	tagImage _cursorIcon[2];
	tagImage _resource_yellowMineral;
	tagImage _resource_blueFlowers;
	tagImage _resource_redFlower;
	tagImage _object_grass[5];
	tagImage _object_bluePlant[9];
	tagImage _object_mushrooms[9];
	tagImage _object_whitePlant[9];
	image* _pixelTiles;
	float _sampleTileStartX, _sampleTileEndX;
	bool _tileSelectPage;
	bool _pageSwitch;
	bool _dragStart;
	bool _moveSampleTiles;
	bool _isLeft;
	bool _descOn;
	int _sampleTileType;
	int _count;
	int _saveDelta;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render();

	//��������
	void maptoolSetup(void); //�ʱ�ȭ�� �־�θ� �ȴ�
							 //�ʼ���
	void setMap(void);
	//���̺�
	void save(void);
	//�ε�
	void load(void);

	void keyInput(void);
	void tileSelectPageSetup(void);
	void tileSelectPageRender(void);
	void UIsetup(void);
	void descBubble(RECT* rcBackdrop);
	void drawRcRange(void);
	void drawRcDrag(void);
	void cursorActionRender(void);
	void cameraAdjustment(void);

	//����, ������Ʈ ����
	TERRAIN terrainSelect(int frameX, int frameY);
	OBJECT objectSelect(int frameX, int frameY);

	tagTile getTiles(int tileNum) { return _tiles[tileNum]; }
	image* getPixelTiles() { return _pixelTiles; }


	tileMap() {}
	~tileMap() {}
};