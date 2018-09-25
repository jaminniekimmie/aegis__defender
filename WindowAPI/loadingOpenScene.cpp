#include "stdafx.h"
#include "loadingOpenScene.h"

HRESULT loadingOpenScene::init(void)
{
	//로딩클래스 초기화
	_loading = new loading;
	_loading->init();

	//이미지 및 사운드 로딩
	this->loadingImage();
	this->loadingSound();
	_background = IMAGEMANAGER->addImage("bgLoadingScene", "tex/background/Aegis_WP1.bmp", WINSIZEX, WINSIZEY);
	_alpha = 0;


	return S_OK;
}

void loadingOpenScene::release(void)
{
	//로딩클래스 해제
	_loading->release();
	SAFE_DELETE(_loading);
}

void loadingOpenScene::update(void)
{
	//로딩클래스 업데이트
	_loading->update();

	//로딩완료후 씬변경
	if (_loading->loadingDone())
		_alpha += 5;
	
	if (_alpha >= 255)
		SCENEMANAGER->loadScene("맵툴");

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		float num = _loading->getLoadItem().size();
		float cur = _loading->getCurrentGauge();
		float per = cur / num * 100;
		cout << "전체 파일갯수 : " << num << endl;
		cout << "현재 로딩갯수 : " << cur << endl;
		cout << per << " %" << endl;
	}
}

void loadingOpenScene::render(void)
{
	//로딩클래스 렌더
	_loading->render();

	_background->render(getMemDC());

	float num = _loading->getLoadItem().size();
	float cur = _loading->getCurrentGauge();
	float per = cur / num * 100;
	char str[128];
	HFONT myFont = CreateFont(63, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Flood Std");
	HFONT oldFont = (HFONT)SelectObject(getMemDC(), myFont);
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	SetBkMode(getMemDC(), TRANSPARENT);

	sprintf_s(str, "LOADING %.f", per);
	TextOut(getMemDC(), WINSIZEX / 2 - 195, WINSIZEY / 2 - 40, str, strlen(str));

	SelectObject(getMemDC(), oldFont);
	DeleteObject(myFont);
	
	if (_loading->loadingDone())
		IMAGEMANAGER->alphaRender("solid_black", getMemDC(), _alpha);

}

//로딩이미지 함수(이곳에 이미지를 전부 넣어라)
void loadingOpenScene::loadingImage()
{
	string str;

	//타일맵
	_loading->loadFrameImage("button_save", "tex/UI/button_save_01.bmp", 294, 45, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("button_load", "tex/UI/button_load_01.bmp", 288, 45, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("button_select", "tex/UI/button_select_01.bmp", 518, 45, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("button_erase", "tex/UI/button_erase_01.bmp", 408, 45, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("button_arrow1", "tex/UI/button_arrow_01.bmp", 78, 150, 2, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("button_arrow2", "tex/UI/button_arrow_01.bmp", 78, 150, 2, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("cursorIcon_erase", "tex/icons/ATK_Hammer3_03_01.bmp", 108, 63, 2, 1, true, RGB(255, 0, 255));
	_loading->loadImage("cursorIcon_idle", "tex/icons/ATK_Hammer2_12_02.bmp", 34, 34, true, RGB(255, 0, 255));
	_loading->loadImage("button_tile", "tex/UI/button_tile_01.bmp", 104, 36, true, RGB(255, 0, 255));
	_loading->loadImage("character_minor", "tex/characters/character_minor_01.bmp", 443, 605, true, RGB(255, 0, 255));
	_loading->loadImage("text_buildAMap", "tex/UI/text_build_a_map_01.bmp", 514, 92, true, RGB(255, 0, 255));
	_loading->loadImage("solid_red", "tex/background/redSolid_01.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("solid_black", "tex/background/blackSolid_01.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("textBubble_amber", "tex/characters/amber_text_bubble_01.bmp", 680, 289, true, RGB(255, 0, 255));
	_loading->loadImage("temp", "tex/UI/build_a_map_page_01_temp.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("white_tile", "tex/tiles/plain_white_tile_01.bmp", 120, 120);
	_loading->loadImage("teal_tile", "tex/tiles/teal_tile_01.bmp", 120, 120);
	_loading->loadImage("object_grass0", "tex/objects/Debris3_0.bmp", 102, 76, true, RGB(255, 0, 255));
	_loading->loadImage("object_grass1", "tex/objects/Debris3_1.bmp", 114, 74, true, RGB(255, 0, 255));
	_loading->loadImage("object_grass2", "tex/objects/Debris3_2.bmp", 120, 74, true, RGB(255, 0, 255));
	_loading->loadImage("object_grass3", "tex/objects/Debris3_3.bmp", 114, 68, true, RGB(255, 0, 255));
	_loading->loadImage("object_grass4", "tex/objects/Debris3_4.bmp", 100, 72, true, RGB(255, 0, 255));
	_loading->loadImage("textBubble_desc_tile_ground", "tex/UI/description_ground_01.bmp", 802, 252, true, RGB(255, 0, 255));
	_loading->loadImage("textBubble_desc_tile_tree", "tex/UI/description_trees_01.bmp", 802, 252, true, RGB(255, 0, 255));
	_loading->loadImage("textBubble_desc_tile_rock", "tex/UI/description_rocks_01.bmp", 802, 252, true, RGB(255, 0, 255));

	//GUI
	_loading->loadImage("GUI_temp", "tex/UI/GUI_01_temp.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("GUI_heart_red", "tex/UI/heart_red_UI_01.bmp", 27, 27, true, RGB(255, 0, 255));
	_loading->loadImage("GUI_heart_red_shadow", "tex/UI/heart_red_UI_shadow_01.bmp", 27, 27, true, RGB(255, 0, 255));
	_loading->loadImage("GUI_heart_yellow", "tex/UI/heart_yellow_UI_01.bmp", 27, 27, true, RGB(255, 0, 255));
	_loading->loadImage("GUI_heart_yellow_shadow", "tex/UI/heart_yellow_UI_shadow_01.bmp", 27, 27, true, RGB(255, 0, 255));
	_loading->loadImage("GUI_blueFlower", "tex/UI/blueFlower_UI_01.bmp", 54, 48, true, RGB(255, 0, 255));
	_loading->loadImage("GUI_mineral", "tex/UI/mineral_UI_01.bmp", 54, 51, true, RGB(255, 0, 255));

	//items
	_loading->loadImage("collectibleChip_green", "tex/resource/Collectible_Chip1.bmp", 40, 36, true, RGB(255, 0, 255));
	_loading->loadImage("collectibleChip_blue", "tex/resource/Collectible_Chip2.bmp", 40, 36, true, RGB(255, 0, 255));
	_loading->loadImage("collectibleChip_purple", "tex/resource/Collectible_Chip3.bmp", 40, 36, true, RGB(255, 0, 255));
	_loading->loadImage("collectibleChip_white", "tex/resource/Collectible_Chip4.bmp", 40, 36, true, RGB(255, 0, 255));
	_loading->loadImage("heart_red", "tex/resource/Heart_red_01.bmp", 18, 16, true, RGB(255, 0, 255));
	_loading->loadImage("heart_yellow", "tex/resource/Heart_yellow_01.bmp", 18, 16, true, RGB(255, 0, 255));
	_loading->loadImage("resource_yellowMineral", "tex/resource/Resource_Multi1.bmp", 78, 88, true, RGB(255, 0, 255));
	_loading->loadImage("resource_yellowMineral_shadow", "tex/resource/Resource_Multi1_shadow.bmp", 78, 88, true, RGB(255, 0, 255));
	_loading->loadImage("resource_blueFlowers", "tex/resource/Resource_Multi4.bmp", 80, 82, true, RGB(255, 0, 255));
	_loading->loadImage("resource_blueFlowers_shadow", "tex/resource/Resource_Multi4_shadow.bmp", 80, 82, true, RGB(255, 0, 255));
	_loading->loadImage("resource_redFlower", "tex/resource/Resource_BloomFlower5.bmp", 60, 60, true, RGB(255, 0, 255));

	for (int i = 0; i < 9; i++)
	{
		str = "tex/objects/Debris_Single4_" + to_string(i) + ".bmp";
		_loading->loadImage("object_bluePlant" + to_string(i), str.c_str(), 40, 60, true, RGB(255, 0, 255));
		str = "tex/objects/Debris_Single5_" + to_string(i) + ".bmp";
		_loading->loadImage("object_mushrooms" + to_string(i), str.c_str(), 40, 60, true, RGB(255, 0, 255));
		str = "tex/objects/Debris_Single6_" + to_string(i) + ".bmp";
		_loading->loadImage("object_whitePlant" + to_string(i), str.c_str(), 40, 60, true, RGB(255, 0, 255));
	}
}

//로딩사운드 함수(이곳에 사운드를 전부 넣어라)
void loadingOpenScene::loadingSound()
{
	//_loading->loadSound("사운드1", "브금.mp3");
}
