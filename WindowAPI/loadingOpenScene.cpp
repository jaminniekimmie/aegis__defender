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
		{
			SCENEMANAGER->getCurrentScene()->release();
			SCENEMANAGER->loadScene("타이틀화면");
		}
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
	_loading->loadFrameImage("scene_gameOver", "tex/UI/gameOver_01.bmp", WINSIZEX * 2, WINSIZEY, 2, 1, true, RGB(255, 0, 255));
	_loading->loadImage("scene_victory", "tex/UI/victory_01.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	//GUI
	_loading->loadImage("solid_red", "tex/background/redSolid_01.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("solid_black", "tex/background/blackSolid_01.bmp", WINSIZEX, WINSIZEY);
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
	_loading->loadImage("g_bubble", "tex/resource/G_Bubble3.bmp", 16, 20, true, RGB(255, 0, 255));
	_loading->loadImage("resource_yellowMineral", "tex/resource/Resource_Multi1.bmp", 78, 88, true, RGB(255, 0, 255));
	_loading->loadImage("resource_yellowMineral_hit", "tex/resource/Resource_Multi1_hit.bmp", 78, 88, true, RGB(255, 0, 255));
	_loading->loadImage("resource_yellowMineral_shadow", "tex/resource/Resource_Multi1_shadow.bmp", 78, 88, true, RGB(255, 0, 255));
	_loading->loadImage("resource_blueFlowers", "tex/resource/Resource_Multi4.bmp", 80, 82, true, RGB(255, 0, 255));
	_loading->loadImage("resource_blueFlowers_hit", "tex/resource/Resource_Multi4_hit.bmp", 80, 82, true, RGB(255, 0, 255));
	_loading->loadImage("resource_blueFlowers_shadow", "tex/resource/Resource_Multi4_shadow.bmp", 80, 82, true, RGB(255, 0, 255));
	_loading->loadImage("resource_redFlower", "tex/resource/Resource_BloomFlower5.bmp", 60, 60, true, RGB(255, 0, 255));
	_loading->loadImage("resource_redFlower_hit", "tex/resource/Resource_BloomFlower5_hit.bmp", 60, 60, true, RGB(255, 0, 255));
	_loading->loadImage("item_blueFlower", "tex/resource/item_blueFlower.bmp", 36, 32, true, RGB(255, 0, 255));
	_loading->loadImage("item_mineral", "tex/resource/item_mineral.bmp", 36, 34, true, RGB(255, 0, 255));

	for (int i = 0; i < 9; i++)
	{
		str = "tex/objects/Debris_Single4_" + to_string(i) + ".bmp";
		_loading->loadImage("object_bluePlant" + to_string(i), str.c_str(), 40, 60, true, RGB(255, 0, 255));
		str = "tex/objects/Debris_Single5_" + to_string(i) + ".bmp";
		_loading->loadImage("object_mushrooms" + to_string(i), str.c_str(), 40, 60, true, RGB(255, 0, 255));
		str = "tex/objects/Debris_Single6_" + to_string(i) + ".bmp";
		_loading->loadImage("object_whitePlant" + to_string(i), str.c_str(), 40, 60, true, RGB(255, 0, 255));
	}

	//////////////////////////////////////
	
	_loading->loadFrameImage("menu_main", "tex/UI/menu_main.bmp", 476, 114, 4, 1, true, RGB(255, 0, 255));
	_loading->loadImage("menu_sound_frame", "tex/UI/menu_sound_frame_01.bmp", 111, 108, true, RGB(255, 0, 255));
	_loading->loadImage("menu_pressAnyButton", "tex/UI/menu_pressAnyButton_01.bmp", 261, 19, true, RGB(255, 0, 255));
	_loading->loadImage("menu_sound", "tex/UI/title_sound.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	//for (int i = 1; i <= 203; i++)
	//{
	//	string str = "tex/_title/aegis_title_" + to_string(i) + ".bmp";
	//	_loading->loadImage("titleScene" + to_string(i), str.c_str(), WINSIZEX, WINSIZEY);
	//}
	_loading->loadImage("titleScene0", "tex/_title/aegis_title_0.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene1", "tex/_title/aegis_title_1.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene2", "tex/_title/aegis_title_2.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene3", "tex/_title/aegis_title_3.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene4", "tex/_title/aegis_title_4.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene5", "tex/_title/aegis_title_5.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene6", "tex/_title/aegis_title_6.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene7", "tex/_title/aegis_title_7.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene8", "tex/_title/aegis_title_8.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene9", "tex/_title/aegis_title_9.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene10", "tex/_title/aegis_title_10.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene11", "tex/_title/aegis_title_11.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene12", "tex/_title/aegis_title_12.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene13", "tex/_title/aegis_title_13.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene14", "tex/_title/aegis_title_14.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene15", "tex/_title/aegis_title_15.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene16", "tex/_title/aegis_title_16.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene17", "tex/_title/aegis_title_17.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene18", "tex/_title/aegis_title_18.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene19", "tex/_title/aegis_title_19.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene20", "tex/_title/aegis_title_20.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene21", "tex/_title/aegis_title_21.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene22", "tex/_title/aegis_title_22.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene23", "tex/_title/aegis_title_23.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene24", "tex/_title/aegis_title_24.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene25", "tex/_title/aegis_title_25.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene26", "tex/_title/aegis_title_26.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene27", "tex/_title/aegis_title_27.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene28", "tex/_title/aegis_title_28.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene29", "tex/_title/aegis_title_29.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene30", "tex/_title/aegis_title_30.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene31", "tex/_title/aegis_title_31.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene32", "tex/_title/aegis_title_32.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene33", "tex/_title/aegis_title_33.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene34", "tex/_title/aegis_title_34.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene35", "tex/_title/aegis_title_35.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene36", "tex/_title/aegis_title_36.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene37", "tex/_title/aegis_title_37.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene38", "tex/_title/aegis_title_38.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene39", "tex/_title/aegis_title_39.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene40", "tex/_title/aegis_title_40.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene41", "tex/_title/aegis_title_41.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene42", "tex/_title/aegis_title_42.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene43", "tex/_title/aegis_title_43.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene44", "tex/_title/aegis_title_44.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene45", "tex/_title/aegis_title_45.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene46", "tex/_title/aegis_title_46.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene47", "tex/_title/aegis_title_47.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene48", "tex/_title/aegis_title_48.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene49", "tex/_title/aegis_title_49.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene50", "tex/_title/aegis_title_50.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene51", "tex/_title/aegis_title_51.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene52", "tex/_title/aegis_title_52.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene53", "tex/_title/aegis_title_53.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene54", "tex/_title/aegis_title_54.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene55", "tex/_title/aegis_title_55.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene56", "tex/_title/aegis_title_56.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene57", "tex/_title/aegis_title_57.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene58", "tex/_title/aegis_title_58.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene59", "tex/_title/aegis_title_59.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene60", "tex/_title/aegis_title_60.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene61", "tex/_title/aegis_title_61.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene62", "tex/_title/aegis_title_62.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene63", "tex/_title/aegis_title_63.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene64", "tex/_title/aegis_title_64.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene65", "tex/_title/aegis_title_65.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene66", "tex/_title/aegis_title_66.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene67", "tex/_title/aegis_title_67.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene68", "tex/_title/aegis_title_68.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene69", "tex/_title/aegis_title_69.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene70", "tex/_title/aegis_title_70.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene71", "tex/_title/aegis_title_71.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene72", "tex/_title/aegis_title_72.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene73", "tex/_title/aegis_title_73.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene74", "tex/_title/aegis_title_74.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene75", "tex/_title/aegis_title_75.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene76", "tex/_title/aegis_title_76.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene77", "tex/_title/aegis_title_77.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene78", "tex/_title/aegis_title_78.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene79", "tex/_title/aegis_title_79.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene80", "tex/_title/aegis_title_80.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene81", "tex/_title/aegis_title_81.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene82", "tex/_title/aegis_title_82.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene83", "tex/_title/aegis_title_83.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene84", "tex/_title/aegis_title_84.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene85", "tex/_title/aegis_title_85.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene86", "tex/_title/aegis_title_86.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene87", "tex/_title/aegis_title_87.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene88", "tex/_title/aegis_title_88.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene89", "tex/_title/aegis_title_89.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene90", "tex/_title/aegis_title_90.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene91", "tex/_title/aegis_title_91.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene92", "tex/_title/aegis_title_92.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene93", "tex/_title/aegis_title_93.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene94", "tex/_title/aegis_title_94.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene95", "tex/_title/aegis_title_95.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene96", "tex/_title/aegis_title_96.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene97", "tex/_title/aegis_title_97.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene98", "tex/_title/aegis_title_98.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene99", "tex/_title/aegis_title_99.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene100", "tex/_title/aegis_title_100.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene101", "tex/_title/aegis_title_101.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene102", "tex/_title/aegis_title_102.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene103", "tex/_title/aegis_title_103.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene104", "tex/_title/aegis_title_104.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene105", "tex/_title/aegis_title_105.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene106", "tex/_title/aegis_title_106.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene107", "tex/_title/aegis_title_107.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene108", "tex/_title/aegis_title_108.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene109", "tex/_title/aegis_title_109.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene110", "tex/_title/aegis_title_110.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene111", "tex/_title/aegis_title_111.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene112", "tex/_title/aegis_title_112.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene113", "tex/_title/aegis_title_113.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene114", "tex/_title/aegis_title_114.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene115", "tex/_title/aegis_title_115.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene116", "tex/_title/aegis_title_116.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene117", "tex/_title/aegis_title_117.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene118", "tex/_title/aegis_title_118.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene119", "tex/_title/aegis_title_119.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene120", "tex/_title/aegis_title_120.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene121", "tex/_title/aegis_title_121.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene122", "tex/_title/aegis_title_122.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene123", "tex/_title/aegis_title_123.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene124", "tex/_title/aegis_title_124.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene125", "tex/_title/aegis_title_125.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene126", "tex/_title/aegis_title_126.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene127", "tex/_title/aegis_title_127.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene128", "tex/_title/aegis_title_128.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene129", "tex/_title/aegis_title_129.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene130", "tex/_title/aegis_title_130.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene131", "tex/_title/aegis_title_131.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene132", "tex/_title/aegis_title_132.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene133", "tex/_title/aegis_title_133.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene134", "tex/_title/aegis_title_134.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene135", "tex/_title/aegis_title_135.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene136", "tex/_title/aegis_title_136.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene137", "tex/_title/aegis_title_137.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene138", "tex/_title/aegis_title_138.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene139", "tex/_title/aegis_title_139.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene140", "tex/_title/aegis_title_140.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene141", "tex/_title/aegis_title_141.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene142", "tex/_title/aegis_title_142.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene143", "tex/_title/aegis_title_143.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene144", "tex/_title/aegis_title_144.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene145", "tex/_title/aegis_title_145.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene146", "tex/_title/aegis_title_146.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene147", "tex/_title/aegis_title_147.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene148", "tex/_title/aegis_title_148.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene149", "tex/_title/aegis_title_149.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene150", "tex/_title/aegis_title_150.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene151", "tex/_title/aegis_title_151.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene152", "tex/_title/aegis_title_152.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene153", "tex/_title/aegis_title_153.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene154", "tex/_title/aegis_title_154.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene155", "tex/_title/aegis_title_155.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene156", "tex/_title/aegis_title_156.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene157", "tex/_title/aegis_title_157.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene158", "tex/_title/aegis_title_158.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene159", "tex/_title/aegis_title_159.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene160", "tex/_title/aegis_title_160.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene161", "tex/_title/aegis_title_161.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene162", "tex/_title/aegis_title_162.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene163", "tex/_title/aegis_title_163.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene164", "tex/_title/aegis_title_164.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene165", "tex/_title/aegis_title_165.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene166", "tex/_title/aegis_title_166.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene167", "tex/_title/aegis_title_167.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene168", "tex/_title/aegis_title_168.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene169", "tex/_title/aegis_title_169.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene170", "tex/_title/aegis_title_170.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene171", "tex/_title/aegis_title_171.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene172", "tex/_title/aegis_title_172.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene173", "tex/_title/aegis_title_173.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene174", "tex/_title/aegis_title_174.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene175", "tex/_title/aegis_title_175.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene176", "tex/_title/aegis_title_176.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene177", "tex/_title/aegis_title_177.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene178", "tex/_title/aegis_title_178.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene179", "tex/_title/aegis_title_179.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene180", "tex/_title/aegis_title_180.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene181", "tex/_title/aegis_title_181.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene182", "tex/_title/aegis_title_182.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene183", "tex/_title/aegis_title_183.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene184", "tex/_title/aegis_title_184.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene185", "tex/_title/aegis_title_185.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene186", "tex/_title/aegis_title_186.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene187", "tex/_title/aegis_title_187.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene188", "tex/_title/aegis_title_188.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene189", "tex/_title/aegis_title_189.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene190", "tex/_title/aegis_title_190.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene191", "tex/_title/aegis_title_191.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene192", "tex/_title/aegis_title_192.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene193", "tex/_title/aegis_title_193.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene194", "tex/_title/aegis_title_194.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene195", "tex/_title/aegis_title_195.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene196", "tex/_title/aegis_title_196.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene197", "tex/_title/aegis_title_197.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene198", "tex/_title/aegis_title_198.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("titleScene199", "tex/_title/aegis_title_199.bmp", WINSIZEX, WINSIZEY);

}

//로딩사운드 함수(이곳에 사운드를 전부 넣어라)
void loadingOpenScene::loadingSound()
{
	_loading->loadSound("BGM_gameOver", "audio/mus_gameover_interstitial.wav", true, true);
	_loading->loadSound("BGM_title", "audio/mus_title.wav", true, true);
	_loading->loadSound("BGM_ClusTheme", "audio/mus_clustheme.wav", true, true);
	_loading->loadSound("BGM_BartsTheme", "audio/mus_bartstheme.wav", true, true);
	_loading->loadSound("UI_collect_bloomflower", "audio/ui_gen_collect_bloomflower.wav");
	_loading->loadSound("UI_collect_common", "audio/ui_gen_collect_common.wav");
	_loading->loadSound("UI_menu_close", "audio/ui_menu_close.wav");
	_loading->loadSound("UI_menu_open", "audio/ui_menu_open.wav");
	_loading->loadSound("UI_pause", "audio/ui_pause.wav");
	_loading->loadSound("UI_button_highlight1", "audio/ui_button_highlight_01.wav");
	_loading->loadSound("UI_button_highlight2", "audio/ui_button_highlight_02.wav");
	_loading->loadSound("UI_button_main", "audio/ui_button_main.wav");
	_loading->loadSound("UI_button_sub", "audio/ui_button_sub.wav");
	_loading->loadSound("UI_button_press", "audio/prop_button_press.wav");
}

void loadingOpenScene::loadingEffect()
{
}
