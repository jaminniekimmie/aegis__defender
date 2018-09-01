#pragma once
#include "gameNode.h"
#include "tileNode.h"

class tileMap : public gameNode
{
private:
	tagTile _tiles[TILEX * TILEY];	//왼쪽화면 타일(총 400개)
	tagSampleTile _sampleTiles[SAMPLETILEX * SAMPLETILEY];	//오른쪽화면 타일(총 160개)
	tagCurrentTile _currentTile;	//현재타일

									//버튼 5개(세이브, 로드, 지형, 오브젝트, 지우개)
	CTRL _ctrlSelect;
	CTRL _oldCtrl;
	TERRAIN _terrain;
	OBJECT _object;
	RECT _rcSave, _rcLoad, _rcTerrain, _rcObject, _rcEraser;
	RECT _rcLetterBox[2];
	RECT _rcCamera;
	RECT _rcDrag;
	RECT _rcRange;
	LONG _dragX, _dragY;
	LONG _rangeEnd;
	POINT _globalPtMouse;
	tagImage _arrowButton[2];
	tagImage _characterMinor;
	tagImage _blackSolid;
	tagImage _buildAMapText;
	tagImage _textBubble_amber;
	tagImage _descBubble_terrain[2];
	tagImage _descBubble_object[1];
	tagImage _button[5];
	tagImage _cursorIcon[2];
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
	void render(void);

	//맵툴세팅
	void maptoolSetup(void); //초기화에 넣어두면 된다
							 //맵세팅
	void setMap(void);
	//세이브
	void save(void);
	//로드
	void load(void);

	void tileSelectPageSetup(void);
	void UIsetup(void);
	void descBubble(RECT *rcBackdrop);
	void cameraAdjustment(void);

	//지형, 오브젝트 셋터
	TERRAIN terrainSelect(int frameX, int frameY);
	OBJECT objectSelect(int frameX, int frameY);

	tileMap() {}
	~tileMap() {}
};