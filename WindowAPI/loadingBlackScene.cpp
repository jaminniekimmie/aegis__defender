#include "stdafx.h"
#include "loadingBlackScene.h"

HRESULT loadingBlackScene::init(void)
{
	//로딩클래스 초기화
	_loading = new loading;
	_loading->init();

	_background = IMAGEMANAGER->findImage("solid_black");

	//이미지 및 사운드 로딩
	this->loadingImage();
	this->loadingSound();

	return S_OK;
}

void loadingBlackScene::release(void)
{
	//로딩클래스 해제
	_loading->release();
	SAFE_DELETE(_loading);
}

void loadingBlackScene::update(void)
{
	//로딩클래스 업데이트
	_loading->update();

	//로딩완료후 씬변경
	if (_loading->loadingDone())
	{
		SCENEMANAGER->loadScene("스테이지원");
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

void loadingBlackScene::render(void)
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
	TextOut(getMemDC(), 903, 635, str, strlen(str));
	
	SelectObject(getMemDC(), oldFont);
	DeleteObject(myFont);
}

//로딩이미지 함수(이곳에 이미지를 전부 넣어라)
void loadingBlackScene::loadingImage()
{
	_loading->loadFrameImage("Clu_aim_diagonal", "tex/characters/Clu_aim_diagonal_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_aim_diagonal_fullCharge", "tex/characters/Clu_aim_diagonal_fullCharge_01.bmp", 116 * 6, 232, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_aim_diagonal_fullCharge_idle", "tex/characters/Clu_aim_diagonal_fullCharge_idle_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_aim_diagonalFire", "tex/characters/Clu_aim_diagonalFire_01.bmp", 116 * 3, 232, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_aim_fire", "tex/characters/Clu_aim_fire_01.bmp", 116 * 3, 232, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_aim_idle", "tex/characters/Clu_aim_idle_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_backStep", "tex/characters/Clu_backStep_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_bored", "tex/characters/Clu_bored_01.bmp", 116 * 3, 232, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_bored_idle", "tex/characters/Clu_bored_idle_01.bmp", 116 * 3, 232, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_charge", "tex/characters/Clu_charge_01.bmp", 116 * 6, 232, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_faint", "tex/characters/Clu_faint_01.bmp", 116 * 3, 232, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_faint_idle", "tex/characters/Clu_faint_idle_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_fullCharge", "tex/characters/Clu_fullCharge_01.bmp", 116 * 5, 232, 5, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_fullCharge_idle", "tex/characters/Clu_fullCharge_idle_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_hit", "tex/characters/Clu_hit_01.bmp", 116 * 3, 232, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_idle", "tex/characters/Clu_idle_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_jump_fall", "tex/characters/Clu_jump_fall_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_jump_rise", "tex/characters/Clu_jump_rise_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_jumpFire_fall", "tex/characters/Clu_jumpFire_fall_01.bmp", 116 * 3, 232, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_jumpFire_rise", "tex/characters/Clu_jumpFire_rise_01.bmp", 116 * 2, 232, 2, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_jumpFireDiagonal_fall", "tex/characters/Clu_jumpFireDiagonal_fall_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_jumpFireDiagonal_rise", "tex/characters/Clu_jumpFireDiagonal_rise_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_land", "tex/characters/Clu_land_01.bmp", 116 * 3, 232, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_laugh", "tex/characters/Clu_laugh_01.bmp", 116 * 6, 232, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_laugh_idle", "tex/characters/Clu_laugh_idle_01.bmp", 116 * 2, 232, 2, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_ledgeGrab", "tex/characters/Clu_ledgeGrab_01.bmp", 116 * 9, 232, 9, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_lookup", "tex/characters/Clu_lookup_01.bmp", 116 * 3, 232, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_push", "tex/characters/Clu_push_01.bmp", 116 * 6, 232, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_run", "tex/characters/Clu_run_01.bmp", 116 * 8, 232, 8, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_think", "tex/characters/Clu_think_01.bmp", 116 * 3, 232, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_think_idle", "tex/characters/Clu_think_idle_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_upset", "tex/characters/Clu_upset_01.bmp", 116 * 9, 232, 9, 2, true, RGB(255, 0, 255));

	_loading->loadFrameImage("Clu_aim_diagonal_shadow", "tex/characters/Clu_aim_diagonal_shadow_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_aim_diagonal_fullCharge_shadow", "tex/characters/Clu_aim_diagonal_fullCharge_shadow_01.bmp", 116 * 6, 232, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_aim_diagonal_fullCharge_idle_shadow", "tex/characters/Clu_aim_diagonal_fullCharge_idle_shadow_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_aim_diagonalFire_shadow", "tex/characters/Clu_aim_diagonalFire_shadow_01.bmp", 116 * 3, 232, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_aim_fire_shadow", "tex/characters/Clu_aim_fire_shadow_01.bmp", 116 * 3, 232, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_aim_idle_shadow", "tex/characters/Clu_aim_idle_shadow_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_backStep_shadow", "tex/characters/Clu_backStep_shadow_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_bored_shadow", "tex/characters/Clu_bored_shadow_01.bmp", 116 * 3, 232, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_bored_idle_shadow", "tex/characters/Clu_bored_idle_shadow_01.bmp", 116 * 3, 232, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_charge_shadow", "tex/characters/Clu_charge_shadow_01.bmp", 116 * 6, 232, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_faint_shadow", "tex/characters/Clu_faint_shadow_01.bmp", 116 * 3, 232, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_faint_idle_shadow", "tex/characters/Clu_faint_idle_shadow_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_fullCharge_shadow", "tex/characters/Clu_fullCharge_shadow_01.bmp", 116 * 5, 232, 5, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_fullCharge_idle_shadow", "tex/characters/Clu_fullCharge_idle_shadow_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_hit_shadow", "tex/characters/Clu_hit_shadow_01.bmp", 16 * 3, 232, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_idle_shadow", "tex/characters/Clu_idle_shadow_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_jump_fall_shadow", "tex/characters/Clu_jump_fall_shadow_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_jump_rise_shadow", "tex/characters/Clu_jump_rise_shadow_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_jumpFire_fall_shadow", "tex/characters/Clu_jumpFire_fall_shadow_01.bmp", 116 * 3, 232, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_jumpFire_rise_shadow", "tex/characters/Clu_jumpFire_rise_shadow_01.bmp", 116 * 2, 232, 2, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_jumpFireDiagonal_fall_shadow", "tex/characters/Clu_jumpFireDiagonal_shadow_fall_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_jumpFireDiagonal_rise_shadow", "tex/characters/Clu_jumpFireDiagonal_shadow_rise_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_land_shadow", "tex/characters/Clu_land_shadow_01.bmp", 116 * 3, 232, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_laugh_shadow", "tex/characters/Clu_laugh_shadow_01.bmp", 116 * 6, 232, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_laugh_idle_shadow", "tex/characters/Clu_laugh_idle_shadow_01.bmp", 116 * 2, 232, 2, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_ledgeGrab_shadow", "tex/characters/Clu_ledgeGrab_shadow_01.bmp", 116 * 9, 232, 9, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_lookup_shadow", "tex/characters/Clu_lookup_shadow_01.bmp", 116 * 3, 232, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_push_shadow", "tex/characters/Clu_push_shadow_01.bmp", 116 * 6, 232, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_run_shadow", "tex/characters/Clu_run_shadow_01.bmp", 116 * 8, 232, 8, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_think_shadow", "tex/characters/Clu_think_shadow_01.bmp", 116 * 3, 232, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_think_idle_shadow", "tex/characters/Clu_think_idle_shadow_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_upset_shadow", "tex/characters/Clu_upset_shadow_01.bmp", 116 * 9, 232, 9, 2, true, RGB(255, 0, 255));
	
	_loading->loadFrameImage("Clu_gun_aim_diagonal", "tex/weapons/Clu_gun_aim_diagonal_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_gun_aim_diagonal_fullCharge", "tex/weapons/Clu_gun_aim_diagonal_fullCharge_01.bmp", 116 * 6, 232, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_gun_aim_diagonal_fullCharge_idle", "tex/weapons/Clu_gun_aim_diagonal_fullCharge_idle_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_gun_aim_diagonalFire", "tex/weapons/Clu_gun_aim_diagonalFire_01.bmp", 116 * 3, 232, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_gun_aim_fire", "tex/weapons/Clu_gun_aim_fire_01.bmp", 116 * 3, 232, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_gun_aim_idle", "tex/weapons/Clu_gun_aim_idle_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_gun_charge", "tex/weapons/Clu_gun_charge_01.bmp", 116 * 6, 232, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_gun_fullCharge", "tex/weapons/Clu_gun_fullCharge_01.bmp", 116 * 5, 232, 5, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_gun_fullCharge_idle", "tex/weapons/Clu_gun_fullCharge_idle_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_gun_jumpFire_fall", "tex/weapons/Clu_gun_jumpFire_fall_01.bmp", 116 * 3, 232, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_gun_jumpFire_rise", "tex/weapons/Clu_gun_jumpFire_rise_01.bmp", 116 * 2, 232, 2, 2, true, RGB(255, 0, 255));
	
	_loading->loadFrameImage("fx_jumpDust1", "tex/fx/JumpDust_01.bmp", 1080, 120, 9, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_jumpDust2", "tex/fx/JumpDust_02.bmp", 1080, 120, 9, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_jumpDust3", "tex/fx/JumpDust_03.bmp", 1080, 120, 9, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_jumpDust", "tex/fx/JumpDust.bmp", 1080, 360, 9, 3, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_runDust_left", "tex/fx/RunDust_left.bmp", 216, 24, 6, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_runDust_right", "tex/fx/RunDust_right.bmp", 216, 24, 6, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_landDust", "tex/fx/Land_01.bmp", 928, 42, 8, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_run1", "tex/fx/Run1.bmp", 160, 20, 8, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_run2", "tex/fx/Run2.bmp", 160, 20, 8, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_run3", "tex/fx/Run3.bmp", 160, 20, 8, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_run4", "tex/fx/Run4.bmp", 160, 20, 8, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_run5", "tex/fx/Run5.bmp", 160, 20, 8, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_bulletPuff1", "tex/fx/bulletPuff1.bmp", 640, 80, 8, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_bulletPuff2", "tex/fx/bulletPuff2.bmp", 640, 80, 8, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_bulletPuff3", "tex/fx/bulletPuff3.bmp", 640, 80, 8, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_bulletPuff4", "tex/fx/bulletPuff4.bmp", 640, 80, 8, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_bulletPuff5", "tex/fx/bulletPuff5.bmp", 640, 80, 8, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_bulletFire_left", "tex/fx/projectileFire_left.bmp", 328, 40, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_bulletFire_right", "tex/fx/projectileFire_right.bmp", 328, 40, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_bulletFire_diagonal_left", "tex/fx/projectileFire_diagonal_left.bmp", 240, 59, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_bulletFire_diagonal_right", "tex/fx/projectileFire_diagonal_right.bmp", 240, 59, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_triBulletFire_left", "tex/fx/projectileFire2_left.bmp", 328, 40, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_triBulletFire_right", "tex/fx/projectileFire2_right.bmp", 328, 40, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_triBulletFire_diagonal_left", "tex/fx/projectileFire2_diagonal_left.bmp", 464, 117, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_triBulletFire_diagonal_right", "tex/fx/projectileFire2_diagonal_right.bmp", 464, 117, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_fullCharge_front", "tex/fx/Attack_FullCharge_Front.bmp", 960, 53, 10, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_fullCharge_back", "tex/fx/Attack_FullCharge_Back.bmp", 960, 53, 10, 1, true, RGB(255, 0, 255));
	_loading->loadImage("bullet_blue", "tex/weapons/Bullet1.bmp", 16, 16, true, RGB(255, 0, 255));
	_loading->loadImage("Clu_gun", "tex/weapons/clu_gun_float_01.bmp", 58, 56, true, RGB(255, 0, 255));
	_loading->loadImage("Clu_bow", "tex/weapons/clu_bow_float_01.bmp", 58, 56, true, RGB(255, 0, 255));
	_loading->loadImage("magazine", "tex/weapons/magazine_01.bmp", 14, 6);
	_loading->loadImage("dot_teal", "tex/fx/dot_teal_01.bmp", 2, 2);
	_loading->loadImage("dot_white", "tex/fx/dot_white_01.bmp", 2, 2);
}

//로딩사운드 함수(이곳에 사운드를 전부 넣어라)
void loadingBlackScene::loadingSound()
{
}
