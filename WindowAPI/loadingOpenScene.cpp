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
	{
		this->loadingEffect();
		_alpha += 5;
		if (_alpha >= 255)
			SCENEMANAGER->loadScene("흑로딩화면");
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

	//게임오버씬
	_loading->loadFrameImage("scene_gameOver", "tex/background/gameOver_01.bmp", WINSIZEX * 2, WINSIZEY, 2, 1, true, RGB(255, 0, 255));

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
	_loading->loadImage("GUI_heart_red", "tex/UI/heart_red_UI_01.bmp", 99, 24, true, RGB(255, 0, 255));
	_loading->loadImage("GUI_heart_yellow", "tex/UI/heart_yellow_UI_01.bmp", 99, 24, true, RGB(255, 0, 255));
	_loading->loadImage("GUI_heart_shadow", "tex/UI/heart_shadow_UI_01.bmp", 99, 24, true, RGB(255, 0, 255));
	_loading->loadImage("GUI_blueFlower", "tex/UI/blueFlower_UI_01.bmp", 54, 48, true, RGB(255, 0, 255));
	_loading->loadImage("GUI_mineral", "tex/UI/mineral_UI_01.bmp", 54, 51, true, RGB(255, 0, 255));
	_loading->loadImage("GUI_button_switch", "tex/UI/button_switch_01.bmp", 566, 45, true, RGB(255, 0, 255));
	_loading->loadImage("GUI_button_bomb", "tex/UI/button_bomb_01.bmp", 464, 45, true, RGB(255, 0, 255));
	_loading->loadImage("GUI_hp_bar_blue", "tex/UI/hpBar_blue_01.bmp", 57, 12);
	_loading->loadImage("GUI_hp_bar_blue_frame", "tex/UI/hpBar_blue_frame_01.bmp", 57, 12, true, RGB(255, 0, 255));
	_loading->loadImage("GUI_hp_bar_yellow", "tex/UI/hpBar_yellow_01.bmp", 57, 12);
	_loading->loadImage("GUI_hp_bar_yellow_frame", "tex/UI/hpBar_yellow_frame_01.bmp", 57, 12, true, RGB(255, 0, 255));
	_loading->loadImage("GUI_hp_bar_red", "tex/UI/hpBar_red_01.bmp", 57, 12);
	_loading->loadImage("GUI_hp_bar_red_frame", "tex/UI/hpBar_red_frame_01.bmp", 57, 12, true, RGB(255, 0, 255));
	_loading->loadImage("GUI_hp_bar_shadow", "tex/UI/hpBar_shadow_01.bmp", 57, 12);
	_loading->loadImage("GUI_control_attack", "tex/UI/control_attack_01.bmp", 205, 45, true, RGB(255, 0, 255));
	_loading->loadImage("GUI_control_backstep", "tex/UI/control_backstep_01.bmp", 255, 46, true, RGB(255, 0, 255));
	_loading->loadImage("GUI_control_bomb", "tex/UI/control_bomb_01.bmp", 170, 45, true, RGB(255, 0, 255));
	_loading->loadImage("GUI_control_move", "tex/UI/control_move_01.bmp", 226, 48, true, RGB(255, 0, 255));
	_loading->loadFrameImage("GUI_icon_clu", "tex/UI/clu_UI_icon_01.bmp", 148, 77, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("GUI_icon_clu_shadow", "tex/UI/clu_UI_icon_shadow_01.bmp", 148, 77, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("GUI_icon_bart", "tex/UI/bart_UI_icon_01.bmp", 148, 77, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("GUI_icon_bart_shadow", "tex/UI/bart_UI_icon_shadow_01.bmp", 148, 77, 2, 1, true, RGB(255, 0, 255));

	//items
	_loading->loadImage("collectibleChip_green", "tex/resource/Collectible_Chip1.bmp", 40, 36, true, RGB(255, 0, 255));
	_loading->loadImage("collectibleChip_blue", "tex/resource/Collectible_Chip2.bmp", 40, 36, true, RGB(255, 0, 255));
	_loading->loadImage("collectibleChip_purple", "tex/resource/Collectible_Chip3.bmp", 40, 36, true, RGB(255, 0, 255));
	_loading->loadImage("collectibleChip_white", "tex/resource/Collectible_Chip4.bmp", 40, 36, true, RGB(255, 0, 255));
	_loading->loadImage("heart_red", "tex/resource/Heart_red_01.bmp", 18, 16, true, RGB(255, 0, 255));
	_loading->loadImage("heart_yellow", "tex/resource/Heart_yellow_01.bmp", 18, 16, true, RGB(255, 0, 255));
	_loading->loadImage("resource_yellowMineral", "tex/resource/Resource_Multi1.bmp", 78, 88, true, RGB(255, 0, 255));
	_loading->loadImage("resource_yellowMineral_hit", "tex/resource/Resource_Multi1_hit.bmp", 78, 88, true, RGB(255, 0, 255));
	_loading->loadImage("resource_yellowMineral_shadow", "tex/resource/Resource_Multi1_shadow.bmp", 78, 88, true, RGB(255, 0, 255));
	_loading->loadImage("resource_blueFlowers", "tex/resource/Resource_Multi4.bmp", 80, 82, true, RGB(255, 0, 255));
	_loading->loadImage("resource_blueFlowers_hit", "tex/resource/Resource_Multi4_hit.bmp", 80, 82, true, RGB(255, 0, 255));
	_loading->loadImage("resource_blueFlowers_shadow", "tex/resource/Resource_Multi4_shadow.bmp", 80, 82, true, RGB(255, 0, 255));
	_loading->loadImage("resource_redFlower", "tex/resource/Resource_BloomFlower5.bmp", 60, 60, true, RGB(255, 0, 255));
	_loading->loadImage("resource_redFlower_hit", "tex/resource/Resource_BloomFlower5_hit.bmp", 60, 60, true, RGB(255, 0, 255));

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
	_loading->loadSound("UI_collect_bloomflower", "audio/ui_gen_collect_bloomflower.wav");
	_loading->loadSound("UI_collect_common", "audio/ui_gen_collect_common.wav");
	_loading->loadSound("UI_menu_close", "audio/ui_menu_close.wav");
	_loading->loadSound("UI_menu_open", "audio/ui_menu_open.wav");
	_loading->loadSound("UI_pause", "audio/ui_pause.wav");
	_loading->loadSound("IMP_explo_medium1", "audio/imp_explo_medium_01.wav");
	_loading->loadSound("IMP_explo_medium2", "audio/imp_explo_medium_02.wav");
	_loading->loadSound("IMP_explo_medium3", "audio/imp_explo_medium_03.wav");
	_loading->loadSound("IMP_explo_medium4", "audio/imp_explo_medium_04.wav");
	_loading->loadSound("UI_button_highlight1", "audio/ui_button_highlight_01.wav");
	_loading->loadSound("UI_button_highlight2", "audio/ui_button_highlight_02.wav");
	_loading->loadSound("UI_button_main", "audio/ui_button_main.wav");
}

void loadingOpenScene::loadingEffect()
{
}
