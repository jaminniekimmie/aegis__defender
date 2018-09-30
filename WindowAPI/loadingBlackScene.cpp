#include "stdafx.h"
#include "loadingBlackScene.h"

HRESULT loadingBlackScene::init(void)
{
	//로딩클래스 초기화
	_loading = new loading;
	_loading->init();

	_background = IMAGEMANAGER->findImage("solid_black");
	_alpha = 0;

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
		this->loadingEffect();
		_alpha += 5;
		if (_alpha >= 255)
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

	if (_loading->loadingDone())
		IMAGEMANAGER->alphaRender("solid_black", getMemDC(), _alpha);
}

//로딩이미지 함수(이곳에 이미지를 전부 넣어라)
void loadingBlackScene::loadingImage()
{
	//CLU
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
	_loading->loadFrameImage("Clu_hit", "tex/characters/Clu_hit_01.bmp", 116 * 6, 232, 6, 2, true, RGB(255, 0, 255));
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
	_loading->loadFrameImage("Clu_ledgeGrab", "tex/characters/Clu_ledgeGrab_01.bmp", 116 * 2, 232, 2, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_ledgeGrab_idle", "tex/characters/Clu_ledgeGrab_idle_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_ledgeGrab_rise", "tex/characters/Clu_ledgeGrab_rise_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
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
	_loading->loadFrameImage("Clu_hit_shadow", "tex/characters/Clu_hit_shadow_01.bmp", 116 * 6, 232, 6, 2, true, RGB(255, 0, 255));
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
	_loading->loadFrameImage("Clu_ledgeGrab_shadow", "tex/characters/Clu_ledgeGrab_shadow_01.bmp", 116 * 2, 232, 2, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_ledgeGrab_idle_shadow", "tex/characters/Clu_ledgeGrab_idle_shadow_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_ledgeGrab_rise_shadow", "tex/characters/Clu_ledgeGrab_rise_shadow_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_lookup_shadow", "tex/characters/Clu_lookup_shadow_01.bmp", 116 * 3, 232, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_push_shadow", "tex/characters/Clu_push_shadow_01.bmp", 116 * 6, 232, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_run_shadow", "tex/characters/Clu_run_shadow_01.bmp", 116 * 8, 232, 8, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_think_shadow", "tex/characters/Clu_think_shadow_01.bmp", 116 * 3, 232, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_think_idle_shadow", "tex/characters/Clu_think_idle_shadow_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_upset_shadow", "tex/characters/Clu_upset_shadow_01.bmp", 116 * 9, 232, 9, 2, true, RGB(255, 0, 255));
	
	//CLU weapon
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

	_loading->loadFrameImage("Clu_bow_aim_diagonal", "tex/weapons/Clu_bow_aim_diagonal_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_bow_aim_diagonal_fullCharge", "tex/weapons/Clu_bow_aim_diagonal_fullCharge_01.bmp", 116 * 6, 232, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_bow_aim_diagonal_fullCharge_idle", "tex/weapons/Clu_bow_aim_diagonal_fullCharge_idle_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_bow_aim_diagonalFire", "tex/weapons/Clu_bow_aim_diagonalFire_01.bmp", 116 * 3, 232, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_bow_aim_fire", "tex/weapons/Clu_bow_aim_fire_01.bmp", 116 * 3, 232, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_bow_aim_idle", "tex/weapons/Clu_bow_aim_idle_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_bow_charge", "tex/weapons/Clu_bow_charge_01.bmp", 116 * 6, 232, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_bow_fullCharge", "tex/weapons/Clu_bow_fullCharge_01.bmp", 116 * 5, 232, 5, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_bow_fullCharge_idle", "tex/weapons/Clu_bow_fullCharge_idle_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_bow_jumpFire_fall", "tex/weapons/Clu_bow_jumpFire_fall_01.bmp", 116 * 3, 232, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Clu_bow_jumpFire_rise", "tex/weapons/Clu_bow_jumpFire_rise_01.bmp", 116 * 2, 232, 2, 2, true, RGB(255, 0, 255));

	_loading->loadFrameImage("dynamiteTrap_active", "tex/weapons/DynamiteTrap_active.bmp", 76, 32, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("dynamiteTrap_active_shadow", "tex/weapons/DynamiteTrap_active_shadow.bmp", 76, 32, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("dynamiteTrap_idle", "tex/weapons/DynamiteTrap_idle.bmp", 76, 32, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("dynamiteTrap_idle_shadow", "tex/weapons/DynamiteTrap_idle_shadow.bmp", 76, 32, 2, 1, true, RGB(255, 0, 255));
	
	//BART
	_loading->loadFrameImage("Bart_block", "tex/characters/Bart_block_01.bmp", 116 * 7, 232, 7, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Bart_bored", "tex/characters/Bart_bored_01.bmp", 116 * 3, 232, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Bart_bored_idle", "tex/characters/Bart_bored_01.bmp", 116 * 3, 232, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Bart_charge", "tex/characters/Bart_charge_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Bart_faint", "tex/characters/Bart_faint_01.bmp", 116 * 5, 232, 5, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Bart_faint_idle", "tex/characters/Bart_faint_idle_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Bart_fullCharge", "tex/characters/Bart_fullCharge_01.bmp", 116 * 6, 232, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Bart_fullCharge_idle", "tex/characters/Bart_fullCharge_idle_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Bart_hammer", "tex/characters/Bart_hammer_01.bmp", 116 * 6, 232, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Bart_hammer_diagonal", "tex/characters/Bart_hammer_diagonal_01.bmp", 116 * 6, 232, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Bart_hammer_idle", "tex/characters/Bart_hammer_idle_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Bart_hammer_idleDiagonal", "tex/characters/Bart_hammer_idleDiagonal_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Bart_hammerJump", "tex/characters/Bart_hammerJump_01.bmp", 116 * 7, 232, 7, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Bart_hit", "tex/characters/Bart_hit_01.bmp", 116 * 6, 232, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Bart_idle", "tex/characters/Bart_idle_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Bart_jump_fall", "tex/characters/Bart_jump_fall_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Bart_jump_hammer_fall", "tex/characters/Bart_jump_hammer_fall_01.bmp", 116 * 5, 232, 5, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Bart_jump_hammer_rise", "tex/characters/Bart_jump_hammer_rise_01.bmp", 116 * 3, 232, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Bart_jump_rise", "tex/characters/Bart_jump_rise_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Bart_land", "tex/characters/Bart_land_01.bmp", 116 * 3, 232, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Bart_laugh", "tex/characters/Bart_laugh_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Bart_laugh_idle", "tex/characters/Bart_laugh_idle_01.bmp", 116 * 2, 232, 2, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Bart_lookup", "tex/characters/Bart_lookup_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Bart_push", "tex/characters/Bart_push_01.bmp", 116 * 6, 232, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Bart_run", "tex/characters/Bart_run_01.bmp", 116 * 8, 232, 8, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Bart_think", "tex/characters/Bart_think_01.bmp", 116 * 3, 232, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Bart_think_idle", "tex/characters/Bart_think_idle_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Bart_upset", "tex/characters/Bart_upset_01.bmp", 116 * 9, 232, 9, 2, true, RGB(255, 0, 255));

	_loading->loadFrameImage("Bart_block_shadow", "tex/characters/Bart_block_shadow_01.bmp", 116 * 7, 232, 7, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Bart_bored_shadow", "tex/characters/Bart_bored_shadow_01.bmp", 116 * 3, 232, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Bart_bored_idle_shadow", "tex/characters/Bart_bored_idle_shadow_01.bmp", 116 * 3, 232, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Bart_charge_shadow", "tex/characters/Bart_charge_shadow_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Bart_faint_shadow", "tex/characters/Bart_faint_shadow_01.bmp", 116 * 5, 232, 5, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Bart_faint_idle_shadow", "tex/characters/Bart_faint_idle_shadow_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Bart_fullCharge_shadow", "tex/characters/Bart_fullCharge_shadow_01.bmp", 116 * 6, 232, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Bart_fullCharge_idle_shadow", "tex/characters/Bart_fullCharge_idle_shadow_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Bart_hammer_shadow", "tex/characters/Bart_hammer_shadow_01.bmp", 116 * 6, 232, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Bart_hammer_diagonal_shadow", "tex/characters/Bart_hammer_diagonal_shadow_01.bmp", 116 * 6, 232, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Bart_hammer_idle_shadow", "tex/characters/Bart_hammer_idle_shadow_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Bart_hammer_idleDiagonal_shadow", "tex/characters/Bart_hammer_idleDiagonal_shadow_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Bart_hammerJump_shadow", "tex/characters/Bart_hammerJump_shadow_01.bmp", 116 * 7, 232, 7, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Bart_hit_shadow", "tex/characters/Bart_hit_shadow_01.bmp", 116 * 6, 232, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Bart_idle_shadow", "tex/characters/Bart_idle_shadow_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Bart_jump_fall_shadow", "tex/characters/Bart_jump_fall_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Bart_jump_hammer_fall_shadow", "tex/characters/Bart_jump_hammer_fall_shadow_01.bmp", 116 * 5, 232, 5, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Bart_jump_hammer_rise_shadow", "tex/characters/Bart_jump_hammer_rise_shadow_01.bmp", 116 * 3, 232, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Bart_jump_rise_shadow", "tex/characters/Bart_jump_rise_shadow_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Bart_land_shadow", "tex/characters/Bart_land_shadow_01.bmp", 116 * 3, 232, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Bart_laugh_shadow", "tex/characters/Bart_laugh_shadow_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Bart_laugh_idle_shadow", "tex/characters/Bart_laugh_idle_shadow_01.bmp", 116 * 2, 232, 2, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Bart_lookup_shadow", "tex/characters/Bart_lookup_shadow_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Bart_push_shadow", "tex/characters/Bart_push_shadow_01.bmp", 116 * 6, 232, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Bart_run_shadow", "tex/characters/Bart_run_shadow_01.bmp", 116 * 8, 232, 8, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Bart_think_shadow", "tex/characters/Bart_think_shadow_01.bmp", 116 * 3, 232, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Bart_think_idle_shadow", "tex/characters/Bart_think_idle_shadow_01.bmp", 116 * 4, 232, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Bart_upset_shadow", "tex/characters/Bart_upset_shadow_01.bmp", 116 * 9, 232, 9, 2, true, RGB(255, 0, 255));
	
	//BART Weapon
	_loading->loadImage("defenseBlock", "tex/weapons/B1_Defense7.bmp", 40, 52, true, RGB(255, 0, 255));
	_loading->loadImage("defenseBlock_shadow", "tex/weapons/B1_Defense7_shadow.bmp", 40, 52, true, RGB(255, 0, 255));

	//MONSTERS
	_loading->loadFrameImage("Sandworm_walk", "tex/monsters/Sandworm_01.bmp", 8532, 328, 27, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Sandworm_walk_shadow", "tex/monsters/Sandworm_shadow_01.bmp", 8532, 328, 27, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("SpiderBaby_walk", "tex/monsters/Spider_Baby_walk_01.bmp", 300, 84, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("SpiderBaby_walk_shadow", "tex/monsters/Spider_Baby_walk_shadow_01.bmp", 300, 84, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("SpiderBaby_hit", "tex/monsters/Spider_Baby_hit_01.bmp", 300, 84, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("SpiderBaby_hit_shadow", "tex/monsters/Spider_Baby_hit_shadow_01.bmp", 300, 84, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("firedrinkerFly_fly", "tex/monsters/FiredrinkerFly_fly_01.bmp", 288, 148, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("firedrinkerFly_fly_shadow", "tex/monsters/FiredrinkerFly_fly_shadow_01.bmp", 288, 148, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("firedrinkerFly_hit", "tex/monsters/FiredrinkerFly_hit_01.bmp", 288, 148, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("firedrinkerFly_hit_shadow", "tex/monsters/FiredrinkerFly_hit_shadow_01.bmp", 288, 148, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("FiredrinkerFly_dead", "tex/monsters/FiredrinkerFly_dead_01.bmp", 50, 76, 1, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("bloodBlob", "tex/fx/Blood_Blob_01.bmp", 324, 132, 6, 2, true, RGB(255, 0, 255));
	
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
	_loading->loadFrameImage("fx_ellipsePuff1", "tex/fx/ellipsePuff1.bmp", 640, 80, 8, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_ellipsePuff2", "tex/fx/ellipsePuff2.bmp", 640, 80, 8, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_ellipsePuff3", "tex/fx/ellipsePuff3.bmp", 640, 80, 8, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_ellipsePuff4", "tex/fx/ellipsePuff4.bmp", 640, 80, 8, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_ellipsePuff5", "tex/fx/ellipsePuff5.bmp", 640, 80, 8, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_bulletFire_left", "tex/fx/projectileFire_left.bmp", 328, 40, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_bulletFire_right", "tex/fx/projectileFire_right.bmp", 328, 40, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_bulletFire_diagonal_left", "tex/fx/projectileFire_diagonal_left.bmp", 240, 59, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_bulletFire_diagonal_right", "tex/fx/projectileFire_diagonal_right.bmp", 240, 59, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_triBulletFire_left", "tex/fx/projectileFire2_left.bmp", 328, 40, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_triBulletFire_right", "tex/fx/projectileFire2_right.bmp", 328, 40, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_triBulletFire_diagonal_left", "tex/fx/projectileFire2_diagonal_left.bmp", 464, 117, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_triBulletFire_diagonal_right", "tex/fx/projectileFire2_diagonal_right.bmp", 464, 117, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_arrowFire_left", "tex/fx/projectileFire3_left.bmp", 384, 66, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_arrowFire_right", "tex/fx/projectileFire3_right.bmp", 384, 66, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_arrowFire_diagonal_left", "tex/fx/projectileFire3_diagonal_left.bmp", 308, 76, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_arrowFire_diagonal_right", "tex/fx/projectileFire3_diagonal_right.bmp", 308, 76, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_triArrowFire_left", "tex/fx/projectileFire4_left.bmp", 488, 86, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_triArrowFire_right", "tex/fx/projectileFire4_right.bmp", 488, 86, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_triArrowFire_diagonal_left", "tex/fx/projectileFire4_diagonal_left.bmp", 420, 112, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_triArrowFire_diagonal_right", "tex/fx/projectileFire4_diagonal_right.bmp", 420, 112, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_fullCharge_front", "tex/fx/Attack_FullCharge_Front.bmp", 960, 53, 10, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_fullCharge_back", "tex/fx/Attack_FullCharge_Back.bmp", 960, 53, 10, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_regen", "tex/fx/Status_Regen.bmp", 672, 22, 12, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_blocked_white", "tex/fx/Blocked_Large_01.bmp", 315, 54, 7, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_blocked_yellow", "tex/fx/Blocked_Large_yellow_01.bmp", 315, 54, 7, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_blocked_blue", "tex/fx/Blocked_Large_blue_01.bmp", 315, 54, 7, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_blocked_red", "tex/fx/Blocked_Large_red_01.bmp", 315, 54, 7, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_aerialExplosion1", "tex/fx/SpriteSheet_AerialExplosion_01.bmp", 1200, 120, 10, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_aerialExplosion2", "tex/fx/SpriteSheet_AerialExplosion_02.bmp", 1200, 120, 10, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_aerialExplosion3", "tex/fx/SpriteSheet_AerialExplosion_03.bmp", 1200, 120, 10, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_ellipseExplosion", "tex/fx/SpriteSheetExplosion.bmp", 840, 120, 7, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_number_1_white", "tex/fx/number_1_white_01.bmp", 110, 15, 10, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_number_2_white", "tex/fx/number_2_white_01.bmp", 110, 15, 10, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_number_3_white", "tex/fx/number_3_white_01.bmp", 110, 15, 10, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_number_4_white", "tex/fx/number_4_white_01.bmp", 110, 15, 10, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_number_5_white", "tex/fx/number_5_white_01.bmp", 110, 15, 10, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_number_6_white", "tex/fx/number_6_white_01.bmp", 110, 15, 10, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_number_1_red", "tex/fx/number_1_red_01.bmp", 110, 15, 10, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_number_2_red", "tex/fx/number_2_red_01.bmp", 110, 15, 10, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_number_3_red", "tex/fx/number_3_red_01.bmp", 110, 15, 10, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_number_4_red", "tex/fx/number_4_red_01.bmp", 110, 15, 10, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_number_5_red", "tex/fx/number_5_red_01.bmp", 110, 15, 10, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_number_6_red", "tex/fx/number_6_red_01.bmp", 110, 15, 10, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_number_1_blue", "tex/fx/number_1_blue_01.bmp", 110, 15, 10, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_number_2_blue", "tex/fx/number_2_blue_01.bmp", 110, 15, 10, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_number_3_blue", "tex/fx/number_3_blue_01.bmp", 110, 15, 10, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_number_4_blue", "tex/fx/number_4_blue_01.bmp", 110, 15, 10, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_number_5_blue", "tex/fx/number_5_blue_01.bmp", 110, 15, 10, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_number_6_blue", "tex/fx/number_6_blue_01.bmp", 110, 15, 10, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_number_1_yellow", "tex/fx/number_1_yellow_01.bmp", 110, 15, 10, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_number_2_yellow", "tex/fx/number_2_yellow_01.bmp", 110, 15, 10, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_number_3_yellow", "tex/fx/number_3_yellow_01.bmp", 110, 15, 10, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_number_4_yellow", "tex/fx/number_4_yellow_01.bmp", 110, 15, 10, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_number_5_yellow", "tex/fx/number_5_yellow_01.bmp", 110, 15, 10, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fx_number_6_yellow", "tex/fx/number_6_yellow_01.bmp", 110, 15, 10, 1, true, RGB(255, 0, 255));
	_loading->loadImage("fx_smoke1", "tex/fx/Smoke_01.bmp", 59, 55, true, RGB(255, 0, 255));
	_loading->loadImage("fx_smoke2", "tex/fx/Smoke_02.bmp", 59, 55, true, RGB(255, 0, 255));
	_loading->loadImage("fx_smoke3", "tex/fx/Smoke_03.bmp", 59, 55, true, RGB(255, 0, 255));
	_loading->loadImage("fx_smoke4", "tex/fx/Smoke_04.bmp", 59, 55, true, RGB(255, 0, 255));
	_loading->loadImage("fx_smoke5", "tex/fx/Smoke_05.bmp", 59, 55, true, RGB(255, 0, 255));

	_loading->loadImage("bullet_blue", "tex/weapons/Bullet1.bmp", 16, 16, true, RGB(255, 0, 255));
	_loading->loadImage("bullet_arrow", "tex/weapons/Bullet15.bmp", 56, 10, true, RGB(255, 0, 255));
	_loading->loadImage("Clu_gun", "tex/weapons/clu_gun_float_01.bmp", 58, 56, true, RGB(255, 0, 255));
	_loading->loadImage("Clu_bow", "tex/weapons/clu_bow_float_01.bmp", 58, 56, true, RGB(255, 0, 255));
	_loading->loadImage("magazine", "tex/weapons/magazine_01.bmp", 14, 6);
	_loading->loadImage("dot_teal", "tex/fx/dot_teal_01.bmp", 2, 2);
	_loading->loadImage("dot_red", "tex/fx/dot_red_01.bmp", 2, 2);
	_loading->loadImage("dot_white", "tex/fx/dot_white_01.bmp", 2, 2);
	_loading->loadImage("bomb_selectDot", "tex/UI/bombSelectDot_01.bmp", 44, 44, true, RGB(255, 0, 255));
	_loading->loadImage("bomb_text", "tex/UI/bomb_text_01.bmp", 153, 48, true, RGB(255, 0, 255));
	_loading->loadImage("defenseBlock_text", "tex/UI/defenseBlock_text_01.bmp", 262, 51, true, RGB(255, 0, 255));

	_loading->loadImage("spawner", "tex/objects/spawner_01.bmp", 136, 174, true, RGB(255, 0, 255));
	_loading->loadImage("door_DNA_blue_left", "tex/objects/door_DNA_blue_left_01.bmp", 162, 228, true, RGB(255, 0, 255));
	_loading->loadImage("door_DNA_blue_right", "tex/objects/door_DNA_blue_right_01.bmp", 162, 228, true, RGB(255, 0, 255));
	_loading->loadImage("door_DNA_yellow_left", "tex/objects/door_DNA_yellow_left_01.bmp", 162, 228, true, RGB(255, 0, 255));
	_loading->loadImage("door_DNA_yellow_right", "tex/objects/door_DNA_yellow_right_01.bmp", 162, 228, true, RGB(255, 0, 255));
	_loading->loadImage("bush_spikes_upsideDown", "tex/objects/bush_spikes_upsideDown_01.bmp", 232, 92, true, RGB(255, 0, 255));
	_loading->loadImage("vent", "tex/objects/vent_01.bmp", 160, 80, true, RGB(255, 0, 255));
	_loading->loadFrameImage("door_elevator", "tex/objects/door_elevator_01.bmp", 4752, 80, 9, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("switch_hor", "tex/objects/switch_hor_01.bmp", 462, 56, 7, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("switch_vert", "tex/objects/switch_vert_01.bmp", 392, 66, 7, 1, true, RGB(255, 0, 255));
	//11시간 잤죠 ?/
	_loading->loadImage("sculpture_back_01", "tex/objects/sculpture_back_01.bmp", 520, 384, true, RGB(255, 0, 255));
	_loading->loadImage("sculpture_back_02", "tex/objects/sculpture_back_02.bmp", 238, 224, true, RGB(255, 0, 255));
	_loading->loadImage("sculpture_back_03", "tex/objects/sculpture_back_03.bmp", 176, 306, true, RGB(255, 0, 255));
	_loading->loadImage("sculpture_back_04", "tex/objects/sculpture_back_04.bmp", 176, 324, true, RGB(255, 0, 255));
	_loading->loadImage("sculpture_back_05", "tex/objects/sculpture_back_05.bmp", 170, 228, true, RGB(255, 0, 255));
	_loading->loadImage("sculpture_back_06", "tex/objects/sculpture_back_06.bmp", 352, 266, true, RGB(255, 0, 255));
	_loading->loadImage("sculpture_front_01", "tex/objects/sculpture_front_01.bmp", 176, 306, true, RGB(255, 0, 255));
	_loading->loadImage("sculpture_front_02", "tex/objects/sculpture_front_02.bmp", 108, 210, true, RGB(255, 0, 255));
	_loading->loadImage("sculpture_front_03", "tex/objects/sculpture_front_03.bmp", 170, 228, true, RGB(255, 0, 255));
	_loading->loadImage("sculpture_front_04", "tex/objects/sculpture_front_04.bmp", 352, 266, true, RGB(255, 0, 255));
	_loading->loadImage("sculpture_front_05", "tex/objects/sculpture_front_05.bmp", 178, 126, true, RGB(255, 0, 255));
	_loading->loadImage("sculpture_front_06", "tex/objects/sculpture_front_06.bmp", 190, 384, true, RGB(255, 0, 255));
	_loading->loadImage("sculpture_front_07", "tex/objects/sculpture_front_07.bmp", 176, 324, true, RGB(255, 0, 255));
	_loading->loadImage("stage1_topology", "tex/map/map_topology_01.bmp", 7409, 1760, true, RGB(255, 0, 255));
	_loading->loadImage("stage1_sky", "tex/map/sky_01.bmp", 7409, 1760, true, RGB(255, 0, 255));
	_loading->loadImage("stage1_temp", "tex/map/map_temp_01.bmp", 7409, 1760);

	_loading->loadImage("Cloud1", "tex/map/Cloud1.bmp", 240, 240, true, RGB(255, 0, 255));
	_loading->loadImage("Cloud2", "tex/map/Cloud2.bmp", 240, 240, true, RGB(255, 0, 255));
	_loading->loadImage("Cloud3", "tex/map/Cloud3.bmp", 240, 240, true, RGB(255, 0, 255));
	_loading->loadImage("Cloud4", "tex/map/Cloud4.bmp", 240, 240, true, RGB(255, 0, 255));
	_loading->loadImage("Cloud5", "tex/map/Cloud5.bmp", 240, 240, true, RGB(255, 0, 255));
	_loading->loadImage("Cloud6", "tex/map/Cloud6.bmp", 240, 240, true, RGB(255, 0, 255));
	_loading->loadImage("Cloud7", "tex/map/Cloud7.bmp", 240, 240, true, RGB(255, 0, 255));
	_loading->loadImage("Cloud8", "tex/map/Cloud8.bmp", 240, 240, true, RGB(255, 0, 255));
	_loading->loadImage("Cloud9", "tex/map/Cloud9.bmp", 240, 240, true, RGB(255, 0, 255));
}

//로딩사운드 함수(이곳에 사운드를 전부 넣어라)
void loadingBlackScene::loadingSound()
{
	_loading->loadSound("BGM_nereisdesert", "audio/mus_nereisdesert.wav", true, true);
	_loading->loadSound("Clu_dashback", "audio/char_clu_dashback.wav");
	_loading->loadSound("Clu_jump", "audio/char_clu_jump.wav");
	_loading->loadSound("Clu_land1", "audio/char_clu_land_01.wav");
	_loading->loadSound("Clu_land2", "audio/char_clu_land_02.wav");
	_loading->loadSound("Clu_land3", "audio/char_clu_land_03.wav");
	_loading->loadSound("Wep_Clu_bow_fire1", "audio/wep_clu_bow_fire_01.wav");
	_loading->loadSound("Wep_Clu_bow_fire2", "audio/wep_clu_bow_fire_02.wav");
	_loading->loadSound("Wep_Clu_bow_fire3", "audio/wep_clu_bow_fire_03.wav");
	_loading->loadSound("Wep_Clu_bow_fire4", "audio/wep_clu_bow_fire_04.wav");
	_loading->loadSound("Wep_Clu_rifle1", "audio/wep_clu_rifle_01.wav");
	_loading->loadSound("Wep_Clu_rifle2", "audio/wep_clu_rifle_02.wav");
	_loading->loadSound("Wep_Clu_rifle3", "audio/wep_clu_rifle_03.wav");
	_loading->loadSound("Wep_Clu_rifle4", "audio/wep_clu_rifle_04.wav");
	_loading->loadSound("Wep_Clu_rifle_rof1", "audio/wep_clu_rifle_rof_02.wav");
	_loading->loadSound("Wep_Clu_rifle_rof2", "audio/wep_clu_rifle_rof_03.wav");
	_loading->loadSound("Bart_jump", "audio/char_bart_jump.wav");
	_loading->loadSound("Bart_land1", "audio/char_bart_land_01.wav");
	_loading->loadSound("Bart_land2", "audio/char_bart_land_02.wav");
	_loading->loadSound("Bart_land3", "audio/char_bart_land_03.wav");
	_loading->loadSound("Bart_block", "audio/char_bart_block.wav");
	_loading->loadSound("Mon_Sandworm_hurt1", "audio/en_sandworm_hurt_01.wav");
	_loading->loadSound("Mon_Sandworm_hurt2", "audio/en_sandworm_hurt_02.wav");
	_loading->loadSound("Mon_Sandworm_hurt3", "audio/en_sandworm_hurt_03.wav");
	_loading->loadSound("Prop_Door_DNA_enter", "audio/prop_door_dna_enter.wav");
}

void loadingBlackScene::loadingEffect()
{
	EFFECTMANAGER->addEffect("landDust", "fx_landDust", 0.4f, 5);
	EFFECTMANAGER->addEffect("jumpDust1", "fx_jumpDust1", 0.4f, 5);
	EFFECTMANAGER->addEffect("jumpDust2", "fx_jumpDust2", 0.4f, 5);
	EFFECTMANAGER->addEffect("jumpDust3", "fx_jumpDust3", 0.4f, 5);
	EFFECTMANAGER->addEffect("runDust0", "fx_runDust_right", 0.4f, 5, true, true);
	EFFECTMANAGER->addEffect("runDust1", "fx_runDust_left", 0.4f, 5, true);
	EFFECTMANAGER->addEffect("run1", "fx_run1", 0.4f, 5, true, true);
	EFFECTMANAGER->addEffect("run2", "fx_run2", 0.4f, 5, true, true);
	EFFECTMANAGER->addEffect("run3", "fx_run3", 0.4f, 5, true, true);
	EFFECTMANAGER->addEffect("run4", "fx_run4", 0.4f, 5, true, true);
	EFFECTMANAGER->addEffect("run5", "fx_run5", 0.4f, 5, true, true);
	EFFECTMANAGER->addEffect("blocked_white", "fx_blocked_white", 0.4f, 5, true, true);
	EFFECTMANAGER->addEffect("blocked_yellow", "fx_blocked_yellow", 0.4f, 5, true, true);
	EFFECTMANAGER->addEffect("blocked_blue", "fx_blocked_blue", 0.4f, 5, true, true);
	EFFECTMANAGER->addEffect("blocked_red", "fx_blocked_red", 0.4f, 5, true, true);
	EFFECTMANAGER->addEffect("number_white1", "fx_number_1_white", 0.4f, 5, true, true);
	EFFECTMANAGER->addEffect("number_white2", "fx_number_2_white", 0.4f, 5, true, true);
	EFFECTMANAGER->addEffect("number_white3", "fx_number_3_white", 0.4f, 5, true, true);
	EFFECTMANAGER->addEffect("number_white4", "fx_number_4_white", 0.4f, 5, true, true);
	EFFECTMANAGER->addEffect("number_white5", "fx_number_5_white", 0.4f, 5, true, true);
	EFFECTMANAGER->addEffect("number_white6", "fx_number_6_white", 0.4f, 5, true, true);
	EFFECTMANAGER->addEffect("number_red1", "fx_number_1_red", 0.4f, 5, true, true);
	EFFECTMANAGER->addEffect("number_red2", "fx_number_2_red", 0.4f, 5, true, true);
	EFFECTMANAGER->addEffect("number_red3", "fx_number_3_red", 0.4f, 5, true, true);
	EFFECTMANAGER->addEffect("number_red4", "fx_number_4_red", 0.4f, 5, true, true);
	EFFECTMANAGER->addEffect("number_red5", "fx_number_5_red", 0.4f, 5, true, true);
	EFFECTMANAGER->addEffect("number_red6", "fx_number_6_red", 0.4f, 5, true, true);
	EFFECTMANAGER->addEffect("number_blue1", "fx_number_1_blue", 0.4f, 5, true, true);
	EFFECTMANAGER->addEffect("number_blue2", "fx_number_2_blue", 0.4f, 5, true, true);
	EFFECTMANAGER->addEffect("number_blue3", "fx_number_3_blue", 0.4f, 5, true, true);
	EFFECTMANAGER->addEffect("number_blue4", "fx_number_4_blue", 0.4f, 5, true, true);
	EFFECTMANAGER->addEffect("number_blue5", "fx_number_5_blue", 0.4f, 5, true, true);
	EFFECTMANAGER->addEffect("number_blue6", "fx_number_6_blue", 0.4f, 5, true, true);
	EFFECTMANAGER->addEffect("number_yellow1", "fx_number_1_yellow", 0.4f, 5, true, true);
	EFFECTMANAGER->addEffect("number_yellow2", "fx_number_2_yellow", 0.4f, 5, true, true);
	EFFECTMANAGER->addEffect("number_yellow3", "fx_number_3_yellow", 0.4f, 5, true, true);
	EFFECTMANAGER->addEffect("number_yellow4", "fx_number_4_yellow", 0.4f, 5, true, true);
	EFFECTMANAGER->addEffect("number_yellow5", "fx_number_5_yellow", 0.4f, 5, true, true);
	EFFECTMANAGER->addEffect("number_yellow6", "fx_number_6_yellow", 0.4f, 5, true, true);
	EFFECTMANAGER->addEffect("regen", "fx_regen", 0.4f, 5, true);
	EFFECTMANAGER->addEffect("aerialExplosion1", "fx_aerialExplosion1", 0.4f, 5, true);
	EFFECTMANAGER->addEffect("aerialExplosion2", "fx_aerialExplosion2", 0.4f, 5, true);
	EFFECTMANAGER->addEffect("aerialExplosion3", "fx_aerialExplosion3", 0.4f, 5, true);
	EFFECTMANAGER->addEffect("ellipseExplosion", "fx_ellipseExplosion", 0.4f, 5, true);
	EFFECTMANAGER->addEffect("bulletPuff1", "fx_bulletPuff1", 0.4f, 5);
	EFFECTMANAGER->addEffect("bulletPuff2", "fx_bulletPuff2", 0.4f, 5);
	EFFECTMANAGER->addEffect("bulletPuff3", "fx_bulletPuff3", 0.4f, 5);
	EFFECTMANAGER->addEffect("bulletPuff4", "fx_bulletPuff4", 0.4f, 5);
	EFFECTMANAGER->addEffect("bulletPuff5", "fx_bulletPuff5", 0.4f, 5);
	EFFECTMANAGER->addEffect("ellipsePuff1", "fx_ellipsePuff1", 0.4f, 5);
	EFFECTMANAGER->addEffect("ellipsePuff2", "fx_ellipsePuff2", 0.4f, 5);
	EFFECTMANAGER->addEffect("ellipsePuff3", "fx_ellipsePuff3", 0.4f, 5);
	EFFECTMANAGER->addEffect("ellipsePuff4", "fx_ellipsePuff4", 0.4f, 5);
	EFFECTMANAGER->addEffect("ellipsePuff5", "fx_ellipsePuff5", 0.4f, 5);
	EFFECTMANAGER->addEffect("bulletFire0", "fx_bulletFire_right", 0.4f, 5);
	EFFECTMANAGER->addEffect("bulletFire1", "fx_bulletFire_left", 0.4f, 5);
	EFFECTMANAGER->addEffect("bulletFire2", "fx_bulletFire_diagonal_right", 0.4f, 5);
	EFFECTMANAGER->addEffect("bulletFire3", "fx_bulletFire_diagonal_left", 0.4f, 5);
	EFFECTMANAGER->addEffect("triBulletFire0", "fx_triBulletFire_right", 0.4f, 5);
	EFFECTMANAGER->addEffect("triBulletFire1", "fx_triBulletFire_left", 0.4f, 5);
	EFFECTMANAGER->addEffect("triBulletFire2", "fx_triBulletFire_diagonal_right", 0.4f, 5);
	EFFECTMANAGER->addEffect("triBulletFire3", "fx_triBulletFire_diagonal_left", 0.4f, 5);
	EFFECTMANAGER->addEffect("arrowFire0", "fx_arrowFire_right", 0.4f, 5);
	EFFECTMANAGER->addEffect("arrowFire1", "fx_arrowFire_left", 0.4f, 5);
	EFFECTMANAGER->addEffect("arrowFire2", "fx_arrowFire_diagonal_right", 0.4f, 5);
	EFFECTMANAGER->addEffect("arrowFire3", "fx_arrowFire_diagonal_left", 0.4f, 5);
	EFFECTMANAGER->addEffect("triArrowFire0", "fx_triArrowFire_right", 0.4f, 5);
	EFFECTMANAGER->addEffect("triArrowFire1", "fx_triArrowFire_left", 0.4f, 5);
	EFFECTMANAGER->addEffect("triArrowFire2", "fx_triArrowFire_diagonal_right", 0.4f, 5);
	EFFECTMANAGER->addEffect("triArrowFire3", "fx_triArrowFire_diagonal_left", 0.4f, 5);
	EFFECTMANAGER->addEffect("fullCharge_back", "fx_fullCharge_back", 0.4f, 5);
	EFFECTMANAGER->addEffect("fullCharge_front", "fx_fullCharge_front", 0.4f, 5);
}
