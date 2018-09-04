#include "stdafx.h"
#include "loadingScene.h"

HRESULT loadingScene::init(void)
{
	//로딩클래스 초기화
	_loading = new loading;
	_loading->init();

	//이미지 및 사운드 로딩
	this->loadingImage();
	this->loadingSound();

	return S_OK;
}

void loadingScene::release(void)
{
	//로딩클래스 해제
	_loading->release();
	SAFE_DELETE(_loading);
}

void loadingScene::update(void)
{
	//로딩클래스 업데이트
	_loading->update();

	//로딩완료후 씬변경
	if (_loading->loadingDone())
	{
		SCENEMANAGER->loadScene("맵툴");
	}

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

void loadingScene::render(void)
{
	//로딩클래스 렌더
	_loading->render();

	//if (_loading->getCurrentGauge() < _loading->getLoadItem().size())
	//{
	//	char str[128];
	//	sprintf_s(str, "%s.bmp", _loading->getLoadItem()[_loading->getCurrentGauge()]->getImageResource().keyName.c_str());
	//	TextOut(getMemDC(), 120, 430, str, strlen(str));
	//}

	float num = _loading->getLoadItem().size();
	float cur = _loading->getCurrentGauge();
	float per = cur / num * 100;
	char str[128];
	HFONT myFont = CreateFont(63, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Flood Std");
	HFONT oldFont = (HFONT)SelectObject(getMemDC(), myFont);
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	SetBkMode(getMemDC(), TRANSPARENT);
	
	sprintf_s(str, "LOADING %.f", per);
	TextOut(getMemDC(), 903, 635, str, strlen(str));
	
	SelectObject(getMemDC(), oldFont);
	DeleteObject(myFont);
}

//로딩이미지 함수(이곳에 이미지를 전부 넣어라)
void loadingScene::loadingImage()
{
	//_loading->loadImage();
	//_loading->loadFrameImage();
	//_loading->loadSound();
	//SetBkMode(getMemDC(), TRANSPARENT);
	//로딩이 너무 빠르게 진행되서 천천히 돌아가도록 테스트용으로 만들기
	//for (int i = 0; i < 500; i++)
	//{
	//	char str[128];
	//	sprintf_s(str, "%s_%d", "testImage", i + 1);
	//	_loading->loadImage(str, WINSIZEX, WINSIZEY);
	//}
	//IMAGEMANAGER->addImage("mountain", "mountain.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	//백그라운드 이미지
	//for (int i = 0; i < 500; i++)
	//{
	//	char str[128];
	//	sprintf_s(str, "%s_%d", "mountain", i + 1);
	//	_loading->loadImage(str, "mountain.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	//}
	string str;

	_loading->loadFrameImage("Clu_aim_diagonal", "tex/characters/Clu_aim_diagonal_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_aim_diagonal_fullCharge", "tex/characters/Clu_aim_diagonal_01.bmp", 116 * 8, 232, 8, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_aim_diagonalFire", "tex/characters/Clu_aim_diagonalFire_01.bmp", 116 * 3, 232, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_aim_fire", "tex/characters/Clu_aim_fire_01.bmp", 116 * 3, 232, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_aim_idle", "tex/characters/Clu_aim_idle_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_backStep", "tex/characters/Clu_backStep_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_bored", "tex/characters/Clu_bored_01.bmp", 116 * 5, 232, 5, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_charge", "tex/characters/Clu_charge_01.bmp", 116 * 6, 232, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_faint", "tex/characters/Clu_faint_01.bmp", 116 * 3, 232, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_faint_idle", "tex/characters/Clu_faint_idle_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_fullCharge", "tex/characters/Clu_fullCharge_01.bmp", 116 * 8, 232, 8, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_hit", "tex/characters/Clu_hit_01.bmp", 116 * 3, 232, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_idle", "tex/characters/Clu_idle_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_jump_fall", "tex/characters/Clu_jump_fall_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_jump_rise", "tex/characters/Clu_jump_rise_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_jumpFire_fall", "tex/characters/Clu_jumpFire_fall_01.bmp", 116 * 3, 232, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_jumpFire_rise", "tex/characters/Clu_jumpFire_rise_01.bmp", 116 * 2, 232, 2, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_jumpFireDiagonal_fall", "tex/characters/Clu_jumpFireDiagonal_fall_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_jumpFireDiagonal_rise", "tex/characters/Clu_jumpFireDiagonal_rise_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_land", "tex/characters/Clu_land_01.bmp", 116 * 3, 232, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_ledgeGrab", "tex/characters/Clu_ledgeGrab_01.bmp", 116 * 9, 232, 9, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_lookup", "tex/characters/Clu_lookup_01.bmp", 116 * 3, 232, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_push", "tex/characters/Clu_push_01.bmp", 116 * 6, 232, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_run", "tex/characters/Clu_run_01.bmp", 116 * 8, 232, 8, 2, true, RGB(255, 0, 255));

	_loading->loadFrameImage("Clu_aim_diagonal_shadow", "tex/characters/Clu_aim_diagonal_shadow_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_aim_diagonal_fullCharge_shadow", "tex/characters/Clu_aim_diagonal_shadow_01.bmp", 116 * 8, 232, 8, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_aim_diagonalFire_shadow", "tex/characters/Clu_aim_diagonalFire_shadow_01.bmp", 232 * 3, 232, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_aim_fire_shadow", "tex/characters/Clu_aim_fire_shadow_01.bmp", 116 * 3, 232, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_aim_idle_shadow", "tex/characters/Clu_aim_idle_shadow_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_backStep_shadow", "tex/characters/Clu_backStep_shadow_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_bored_shadow", "tex/characters/Clu_bored_shadow_01.bmp", 116 * 5, 232, 5, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_charge_shadow", "tex/characters/Clu_charge_shadow_01.bmp", 116 * 6, 232, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_faint_shadow", "tex/characters/Clu_faint_shadow_01.bmp", 116 * 3, 232, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_faint_idle_shadow", "tex/characters/Clu_faint_idle_shadow_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_fullCharge_shadow", "tex/characters/Clu_fullCharge_shadow_01.bmp", 116 * 8, 232, 8, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_hit_shadow", "tex/characters/Clu_hit_shadow_01.bmp", 16 * 3, 232, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_idle_shadow", "tex/characters/Clu_idle_shadow_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_jump_fall_shadow", "tex/characters/Clu_jump_fall_shadow_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_jump_rise_shadow", "tex/characters/Clu_jump_rise_shadow_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_jumpFire_fall_shadow", "tex/characters/Clu_jumpFire_fall_shadow_01.bmp", 116 * 3, 232, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_jumpFire_rise_shadow", "tex/characters/Clu_jumpFire_rise_shadow_01.bmp", 116 * 2, 232, 2, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_jumpFireDiagonal_fall_shadow", "tex/characters/Clu_jumpFireDiagonal_shadow_fall_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_jumpFireDiagonal_rise_shadow", "tex/characters/Clu_jumpFireDiagonal_shadow_rise_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_land_shadow", "tex/characters/Clu_land_shadow_01.bmp", 116 * 3, 232, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_ledgeGrab_shadow", "tex/characters/Clu_ledgeGrab_shadow_01.bmp", 116 * 9, 232, 9, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_lookup_shadow", "tex/characters/Clu_lookup_shadow_01.bmp", 116 * 3, 232, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_push_shadow", "tex/characters/Clu_push_shadow_01.bmp", 116 * 6, 232, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_run_shadow", "tex/characters/Clu_run_shadow_01.bmp", 116 * 8, 232, 8, 2, true, RGB(255, 0, 255));
	
	_loading->loadFrameImage("button_save", "tex/UI/button_save_01.bmp", 294, 45, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("button_load", "tex/UI/button_load_01.bmp", 288, 45, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("button_select", "tex/UI/button_select_01.bmp", 518, 45, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("button_erase", "tex/UI/button_erase_01.bmp", 408, 45, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("button_arrow1", "tex/UI/button_arrow_01.bmp", 78, 150, 2, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("button_arrow2", "tex/UI/button_arrow_01.bmp", 78, 150, 2, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_jumpDust", "tex/fx/JumpDust_01.bmp", 1080, 360, 9, 3, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_landDust", "tex/fx/Land_01.bmp", 928, 42, 8, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("cursorIcon_erase", "tex/icons/ATK_Hammer3_03_01.bmp", 108, 63, 2, 1, true, RGB(255, 0, 255));
	_loading->loadImage("cursorIcon_idle", "tex/icons/ATK_Hammer2_12_02.bmp", 34, 34, true, RGB(255, 0, 255));
	_loading->loadImage("button_tile", "tex/UI/button_tile_01.bmp", 104, 36, true, RGB(255, 0, 255));
	_loading->loadImage("character_minor", "tex/characters/character_minor_01.bmp", 443, 605, true, RGB(255, 0, 255));
	_loading->loadImage("text_buildAMap", "tex/UI/text_build_a_map_01.bmp", 514, 92, true, RGB(255, 0, 255));
	_loading->loadImage("solid_black", "tex/background/blackSolid_01.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("textBubble_amber", "tex/characters/amber_text_bubble_01.bmp", 680, 289, true, RGB(255, 0, 255));
	_loading->loadImage("temp", "tex/UI/build_a_map_page_01_temp.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("white_tile", "tex/tiles/plain_white_tile_01.bmp", 120, 120);
	_loading->loadImage("teal_tile", "tex/tiles/teal_tile_01.bmp", 120, 120);
	_loading->loadImage("resource_yellowMineral", "tex/objects/Resource_Multi1.bmp", 78, 88, true, RGB(255, 0, 255));
	_loading->loadImage("resource_blueFlowers", "tex/objects/Resource_Multi4.bmp", 80, 82, true, RGB(255, 0, 255));
	_loading->loadImage("resource_redFlower", "tex/objects/Resource_BloomFlower5.bmp", 60, 60, true, RGB(255, 0, 255));
	_loading->loadImage("object_grass0", "tex/objects/Debris3_0.bmp", 102, 76, true, RGB(255, 0, 255));
	_loading->loadImage("object_grass1", "tex/objects/Debris3_1.bmp", 114, 74, true, RGB(255, 0, 255));
	_loading->loadImage("object_grass2", "tex/objects/Debris3_2.bmp", 120, 74, true, RGB(255, 0, 255));
	_loading->loadImage("object_grass3", "tex/objects/Debris3_3.bmp", 114, 68, true, RGB(255, 0, 255));
	_loading->loadImage("object_grass4", "tex/objects/Debris3_4.bmp", 100, 72, true, RGB(255, 0, 255));
	_loading->loadImage("textBubble_desc_tile_ground", "tex/UI/description_ground_01.bmp", 802, 252, true, RGB(255, 0, 255)); 
	_loading->loadImage("textBubble_desc_tile_tree", "tex/UI/description_trees_01.bmp", 802, 252, true, RGB(255, 0, 255));
	_loading->loadImage("textBubble_desc_tile_rock", "tex/UI/description_rocks_01.bmp", 802, 252, true, RGB(255, 0, 255));

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
void loadingScene::loadingSound()
{
	_loading->loadSound("사운드1", "브금.mp3");
	_loading->loadSound("사운드2", "브금1.mp3");
}
