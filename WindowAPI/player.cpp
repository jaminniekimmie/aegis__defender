#include "stdafx.h"
#include "player.h"

HRESULT player::init(void)
{
	_player_clu[AIM_DIAGONAL].img = IMAGEMANAGER->findImage("Clu_aim_diagonal");
	_player_clu[AIM_DIAGONAL].shadow = IMAGEMANAGER->findImage("Clu_aim_diagonal_shadow");
	_player_clu[AIM_DIAGONAL_FULLCHARGE].img = IMAGEMANAGER->findImage("Clu_aim_diagonal_fullCharge");
	_player_clu[AIM_DIAGONAL_FULLCHARGE].shadow = IMAGEMANAGER->findImage("Clu_aim_diagonal_fullCharge_shadow");
	_player_clu[AIM_DIAGONAL_FULLCHARGE_IDLE].img = IMAGEMANAGER->findImage("Clu_aim_diagonal_fullCharge_idle");
	_player_clu[AIM_DIAGONAL_FULLCHARGE_IDLE].shadow = IMAGEMANAGER->findImage("Clu_aim_diagonal_fullCharge_idle_shadow");
	_player_clu[AIM_DIAGONALFIRE].img = IMAGEMANAGER->findImage("Clu_aim_diagonalFire");
	_player_clu[AIM_DIAGONALFIRE].shadow = IMAGEMANAGER->findImage("Clu_aim_diagonalFire_shadow");
	_player_clu[AIM_FIRE].img = IMAGEMANAGER->findImage("Clu_aim_fire");
	_player_clu[AIM_FIRE].shadow = IMAGEMANAGER->findImage("Clu_aim_fire_shadow");
	_player_clu[AIM_IDLE].img = IMAGEMANAGER->findImage("Clu_aim_idle");
	_player_clu[AIM_IDLE].shadow = IMAGEMANAGER->findImage("Clu_aim_idle_shadow");
	_player_clu[BACKSTEP].img = IMAGEMANAGER->findImage("Clu_backStep");
	_player_clu[BACKSTEP].shadow = IMAGEMANAGER->findImage("Clu_backStep_shadow");
	_player_clu[BORED].img = IMAGEMANAGER->findImage("Clu_bored");
	_player_clu[BORED].shadow = IMAGEMANAGER->findImage("Clu_bored_shadow");
	_player_clu[BORED_IDLE].img = IMAGEMANAGER->findImage("Clu_bored_idle");
	_player_clu[BORED_IDLE].shadow = IMAGEMANAGER->findImage("Clu_bored_idle_shadow");
	_player_clu[CHARGE].img = IMAGEMANAGER->findImage("Clu_charge");
	_player_clu[CHARGE].shadow = IMAGEMANAGER->findImage("Clu_charge_shadow");
	_player_clu[FAINT].img = IMAGEMANAGER->findImage("Clu_faint");
	_player_clu[FAINT].shadow = IMAGEMANAGER->findImage("Clu_faint_shadow");
	_player_clu[FAINT_IDLE].img = IMAGEMANAGER->findImage("Clu_faint_idle");
	_player_clu[FAINT_IDLE].shadow = IMAGEMANAGER->findImage("Clu_faint_idle_shadow");
	_player_clu[FULLCHARGE].img = IMAGEMANAGER->findImage("Clu_fullCharge");
	_player_clu[FULLCHARGE].shadow = IMAGEMANAGER->findImage("Clu_fullCharge_shadow");
	_player_clu[FULLCHARGE_IDLE].img = IMAGEMANAGER->findImage("Clu_fullCharge_idle");
	_player_clu[FULLCHARGE_IDLE].shadow = IMAGEMANAGER->findImage("Clu_fullCharge_idle_shadow");
	_player_clu[HIT].img = IMAGEMANAGER->findImage("Clu_hit");
	_player_clu[HIT].shadow = IMAGEMANAGER->findImage("Clu_hit_shadow");
	_player_clu[IDLE].img = IMAGEMANAGER->findImage("Clu_idle");
	_player_clu[IDLE].shadow = IMAGEMANAGER->findImage("Clu_idle_shadow");
	_player_clu[JUMP_FALL].img = IMAGEMANAGER->findImage("Clu_jump_fall");
	_player_clu[JUMP_FALL].shadow = IMAGEMANAGER->findImage("Clu_jump_fall_shadow");
	_player_clu[JUMP_RISE].img = IMAGEMANAGER->findImage("Clu_jump_rise");
	_player_clu[JUMP_RISE].shadow = IMAGEMANAGER->findImage("Clu_jump_rise_shadow");
	_player_clu[JUMPFIRE_FALL].img = IMAGEMANAGER->findImage("Clu_jumpFire_fall");
	_player_clu[JUMPFIRE_FALL].shadow = IMAGEMANAGER->findImage("Clu_jumpFire_fall_shadow");
	_player_clu[JUMPFIRE_RISE].img = IMAGEMANAGER->findImage("Clu_jumpFire_rise");
	_player_clu[JUMPFIRE_RISE].shadow = IMAGEMANAGER->findImage("Clu_jumpFire_rise_shadow");
	_player_clu[JUMPFIREDIAGONAL_FALL].img = IMAGEMANAGER->findImage("Clu_jumpFireDiagonal_fall");
	_player_clu[JUMPFIREDIAGONAL_FALL].shadow = IMAGEMANAGER->findImage("Clu_jumpFireDiagonal_fall_shadow");
	_player_clu[JUMPFIREDIAGONAL_RISE].img = IMAGEMANAGER->findImage("Clu_jumpFireDiagonal_rise");
	_player_clu[JUMPFIREDIAGONAL_RISE].shadow = IMAGEMANAGER->findImage("Clu_jumpFireDiagonal_rise_shadow");
	_player_clu[LAND].img = IMAGEMANAGER->findImage("Clu_land");
	_player_clu[LAND].shadow = IMAGEMANAGER->findImage("Clu_land_shadow");
	_player_clu[LAUGH].img = IMAGEMANAGER->findImage("Clu_laugh");
	_player_clu[LAUGH].shadow = IMAGEMANAGER->findImage("Clu_laugh_shadow");
	_player_clu[LAUGH_IDLE].img = IMAGEMANAGER->findImage("Clu_laugh_idle");
	_player_clu[LAUGH_IDLE].shadow = IMAGEMANAGER->findImage("Clu_laugh_idle_shadow");
	_player_clu[LEDGEGRAB].img = IMAGEMANAGER->findImage("Clu_ledgeGrab");
	_player_clu[LEDGEGRAB].shadow = IMAGEMANAGER->findImage("Clu_ledgeGrab_shadow");
	_player_clu[LOOKUP].img = IMAGEMANAGER->findImage("Clu_lookup");
	_player_clu[LOOKUP].shadow = IMAGEMANAGER->findImage("Clu_lookup_shadow");
	_player_clu[PUSH].img = IMAGEMANAGER->findImage("Clu_push");
	_player_clu[PUSH].shadow = IMAGEMANAGER->findImage("Clu_push_shadow");
	_player_clu[RUN].img = IMAGEMANAGER->findImage("Clu_run");
	_player_clu[RUN].shadow = IMAGEMANAGER->findImage("Clu_run_shadow");
	_player_clu[THINK].img = IMAGEMANAGER->findImage("Clu_think");
	_player_clu[THINK].shadow = IMAGEMANAGER->findImage("Clu_think_shadow");
	_player_clu[THINK_IDLE].img = IMAGEMANAGER->findImage("Clu_think_idle");
	_player_clu[THINK_IDLE].shadow = IMAGEMANAGER->findImage("Clu_think_idle_shadow");

	_gun_clu[AIM_DIAGONAL].img = IMAGEMANAGER->findImage("Clu_gun_aim_diagonal");
	_gun_clu[AIM_DIAGONAL_FULLCHARGE].img = IMAGEMANAGER->findImage("Clu_gun_aim_diagonal_fullCharge");
	_gun_clu[AIM_DIAGONAL_FULLCHARGE_IDLE].img = IMAGEMANAGER->findImage("Clu_gun_aim_diagonal_fullCharge_idle");
	_gun_clu[AIM_DIAGONALFIRE].img = IMAGEMANAGER->findImage("Clu_gun_aim_diagonalFire");
	_gun_clu[AIM_FIRE].img = IMAGEMANAGER->findImage("Clu_gun_aim_fire");
	_gun_clu[AIM_IDLE].img = IMAGEMANAGER->findImage("Clu_gun_aim_idle");
	_gun_clu[CHARGE].img = IMAGEMANAGER->findImage("Clu_gun_charge");
	_gun_clu[FULLCHARGE].img = IMAGEMANAGER->findImage("Clu_gun_fullCharge");
	_gun_clu[FULLCHARGE_IDLE].img = IMAGEMANAGER->findImage("Clu_gun_fullCharge_idle");
	_gun_clu[JUMPFIRE_FALL].img = IMAGEMANAGER->findImage("Clu_gun_jumpFire_fall");
	_gun_clu[JUMPFIRE_RISE].img = IMAGEMANAGER->findImage("Clu_gun_jumpFire_rise");

	_player_weapon[0].img = IMAGEMANAGER->findImage("clu_gun");
	_player_weapon[1].img = IMAGEMANAGER->findImage("clu_bow");

	for (int i = 0; i < 2; i++)
	{
		_player_weapon[i].alpha = 0;
		_player_weapon[i].isActive = false;
	}

	for (int i = 0; i < MAXPLAYERSTATE; i++)
		_player_clu[i].alpha = 70;

	//체력바 클래스 생성후 초기화
	_hpBar = new progressBar;
	_hpBar->init("progressBarFront", "progressBarBack", _x, _y - 20, 50, 10);
	//피통 초기화
	_maxHp = 100;
	_currentHp = 100;
	_hpBar->setGauge(_currentHp, _maxHp);
	_playerState = IDLE;
	_isLeft = RIGHT;

	_x = WINSIZEX / 2;
	_y = TILESIZEY - WINSIZEY;

	_frameSpeed = 10;
	_count = _index = _weaponCount = 0;
	_gravity = 0.0f;
	_angle = -PI_2;
	_speed = 8.0f;

	_isFall = _isJump = _isBackstep = _isFaceDown = _isFired = _weaponSwitch = false;
	_onLand = true;

	_rc = RectMake(_x + _player_clu[_playerState].img->getFrameWidth() / 3, _y, _player_clu[_playerState].img->getFrameWidth() / 3, _player_clu[_playerState].img->getFrameHeight() / 3);

	return S_OK;
}

void player::release(void)
{
	//체력바 클래스 해제
	//_hpBar->release();
	SAFE_DELETE(_hpBar);
}

void player::update(void)
{
	_rc = RectMake(_x + _player_clu[_playerState].img->getFrameWidth() / 3, _y + _player_clu[_playerState].img->getFrameHeight() / 3, _player_clu[_playerState].img->getFrameWidth() / 3, _player_clu[_playerState].img->getFrameHeight() / 3 * 2);

	//체력 저장
	//if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	//{
	//	SAVEDATA->setHp(_currentHp);
	//}
	////체력 로드
	//if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	//{
	//	_currentHp = SAVEDATA->getHp();
	//}

	/*
	HANDLE file;
	file = CreateFile()
	ReadFile()
	WriteFile()
	//현재체력, 로켓의 위치만 세이브 로드 시켜라
	*/

	this->frameChangeLoop();
	this->weaponSwitch(_weaponSwitch);
}

void player::render(void)
{

	this->frameChangeLoop();

	if (CAMERAMANAGER->CameraIn(_rc))
	{
		if (_isFired)
			_gun_clu[_playerState].img->frameRender(getMemDC(), _x - CAMERAMANAGER->getCamera().left, _y - CAMERAMANAGER->getCamera().top);

		_player_clu[_playerState].shadow->alphaFrameRender(getMemDC(), _x - CAMERAMANAGER->getCamera().left, _y - CAMERAMANAGER->getCamera().top, _player_clu[_playerState].alpha);
		_player_clu[_playerState].img->frameRender(getMemDC(), _x - CAMERAMANAGER->getCamera().left, _y - CAMERAMANAGER->getCamera().top);

		if (_player_weapon[_weaponSwitch].isActive)
			_player_weapon[_weaponSwitch].img->alphaRender(getMemDC(), _x + 30 - CAMERAMANAGER->getCamera().left, _y - 8 - CAMERAMANAGER->getCamera().top, _player_weapon[_weaponSwitch].alpha);
	}

	if (KEYMANAGER->isToggleKey('R'))
	{
		Rectangle(getMemDC(), _rc.left - CAMERAMANAGER->getCamera().left, _rc.top - CAMERAMANAGER->getCamera().top, _rc.right - CAMERAMANAGER->getCamera().left, _rc.bottom - CAMERAMANAGER->getCamera().top);
	}

	//체력바 렌더
	_hpBar->render();

	char str[64];
	sprintf(str, "%d", _player_weapon[_weaponSwitch].alpha);
	TextOut(getMemDC(), 100, 100, str, strlen(str));

}

void player::hitDamage(float damage)
{
	_currentHp -= damage;
}

void player::frameChangeLoop()
{
	_count++;

	_player_clu[_playerState].img->setFrameY(_isLeft);
	_player_clu[_playerState].shadow->setFrameY(_isLeft);
	if (_isFired)
		_gun_clu[_playerState].img->setFrameY(_isLeft);

	if (_isLeft)
	{
		if (_count % _frameSpeed == 0)
		{
			_player_clu[_playerState].img->setFrameX(_index);
			_player_clu[_playerState].shadow->setFrameX(_index);
			if (_isFired)
				_gun_clu[_playerState].img->setFrameX(_index);

			_index--;
			
			if (_index < 0)
			{
				_index = _player_clu[_playerState].img->getMaxFrameX();
			}
		}
	}
	else
	{
		if (_count % _frameSpeed == 0)
		{
			_player_clu[_playerState].shadow->setFrameX(_index);
			if (_isFired)
				_gun_clu[_playerState].img->setFrameX(_index);
			_player_clu[_playerState].img->setFrameX(_index);
			
			_index++;
			
			if (_index > _player_clu[_playerState].img->getMaxFrameX())
			{
				_index = 0;
			}
		}
	}
}

void player::frameChangeOnce()
{
}

void player::weaponSwitch(bool weaponSwitch)
{
	if (weaponSwitch)
	{
		if (_player_weapon[weaponSwitch].isActive)
		{
			if (_weaponCount < 50)
			{
				if (_player_weapon[weaponSwitch].alpha < 255)
					_player_weapon[weaponSwitch].alpha += 15;
				else
					_weaponCount++;
			}
			else
			{
				if (_player_weapon[weaponSwitch].alpha > 0)
					_player_weapon[weaponSwitch].alpha -= 15;
				else
					_player_weapon[weaponSwitch].isActive = false;
			}
			
		}
		else
		{
			_player_weapon[weaponSwitch].alpha = 0;
			_weaponCount = 0;
		}
	}
	else
	{
		_player_weapon[weaponSwitch].isActive = false;
		_weaponCount = 0;
	}
}