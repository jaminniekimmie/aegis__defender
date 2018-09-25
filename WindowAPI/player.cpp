#include "stdafx.h"
#include "player.h"

HRESULT player::init(PLAYERCHARACTER playerCharacter)
{
	_playerCharacter = playerCharacter;

	if (_playerCharacter == CLU)
	{
		string str = "Clu";
	
		_player[AIM_DIAGONAL].img = IMAGEMANAGER->findImage(str + "_aim_diagonal");
		_player[AIM_DIAGONAL].shadow = IMAGEMANAGER->findImage("Clu_aim_diagonal_shadow");
		_player[AIM_DIAGONAL_FULLCHARGE].img = IMAGEMANAGER->findImage("Clu_aim_diagonal_fullCharge");
		_player[AIM_DIAGONAL_FULLCHARGE].shadow = IMAGEMANAGER->findImage("Clu_aim_diagonal_fullCharge_shadow");
		_player[AIM_DIAGONAL_FULLCHARGE_IDLE].img = IMAGEMANAGER->findImage("Clu_aim_diagonal_fullCharge_idle");
		_player[AIM_DIAGONAL_FULLCHARGE_IDLE].shadow = IMAGEMANAGER->findImage("Clu_aim_diagonal_fullCharge_idle_shadow");
		_player[AIM_DIAGONALFIRE].img = IMAGEMANAGER->findImage("Clu_aim_diagonalFire");
		_player[AIM_DIAGONALFIRE].shadow = IMAGEMANAGER->findImage("Clu_aim_diagonalFire_shadow");
		_player[AIM_FIRE].img = IMAGEMANAGER->findImage("Clu_aim_fire");
		_player[AIM_FIRE].shadow = IMAGEMANAGER->findImage("Clu_aim_fire_shadow");
		_player[AIM_IDLE].img = IMAGEMANAGER->findImage("Clu_aim_idle");
		_player[AIM_IDLE].shadow = IMAGEMANAGER->findImage("Clu_aim_idle_shadow");
		_player[BACKSTEP].img = IMAGEMANAGER->findImage("Clu_backStep");
		_player[BACKSTEP].shadow = IMAGEMANAGER->findImage("Clu_backStep_shadow");
		_player[BORED].img = IMAGEMANAGER->findImage("Clu_bored");
		_player[BORED].shadow = IMAGEMANAGER->findImage("Clu_bored_shadow");
		_player[BORED_IDLE].img = IMAGEMANAGER->findImage("Clu_bored_idle");
		_player[BORED_IDLE].shadow = IMAGEMANAGER->findImage("Clu_bored_idle_shadow");
		_player[CHARGE].img = IMAGEMANAGER->findImage("Clu_charge");
		_player[CHARGE].shadow = IMAGEMANAGER->findImage("Clu_charge_shadow");
		_player[FAINT].img = IMAGEMANAGER->findImage("Clu_faint");
		_player[FAINT].shadow = IMAGEMANAGER->findImage("Clu_faint_shadow");
		_player[FAINT_IDLE].img = IMAGEMANAGER->findImage("Clu_faint_idle");
		_player[FAINT_IDLE].shadow = IMAGEMANAGER->findImage("Clu_faint_idle_shadow");
		_player[FULLCHARGE].img = IMAGEMANAGER->findImage("Clu_fullCharge");
		_player[FULLCHARGE].shadow = IMAGEMANAGER->findImage("Clu_fullCharge_shadow");
		_player[FULLCHARGE_IDLE].img = IMAGEMANAGER->findImage("Clu_fullCharge_idle");
		_player[FULLCHARGE_IDLE].shadow = IMAGEMANAGER->findImage("Clu_fullCharge_idle_shadow");
		_player[HIT].img = IMAGEMANAGER->findImage("Clu_hit");
		_player[HIT].shadow = IMAGEMANAGER->findImage("Clu_hit_shadow");
		_player[IDLE].img = IMAGEMANAGER->findImage("Clu_idle");
		_player[IDLE].shadow = IMAGEMANAGER->findImage("Clu_idle_shadow");
		_player[JUMP_FALL].img = IMAGEMANAGER->findImage("Clu_jump_fall");
		_player[JUMP_FALL].shadow = IMAGEMANAGER->findImage("Clu_jump_fall_shadow");
		_player[JUMP_RISE].img = IMAGEMANAGER->findImage("Clu_jump_rise");
		_player[JUMP_RISE].shadow = IMAGEMANAGER->findImage("Clu_jump_rise_shadow");
		_player[JUMPFIRE_FALL].img = IMAGEMANAGER->findImage("Clu_jumpFire_fall");
		_player[JUMPFIRE_FALL].shadow = IMAGEMANAGER->findImage("Clu_jumpFire_fall_shadow");
		_player[JUMPFIRE_RISE].img = IMAGEMANAGER->findImage("Clu_jumpFire_rise");
		_player[JUMPFIRE_RISE].shadow = IMAGEMANAGER->findImage("Clu_jumpFire_rise_shadow");
		_player[JUMPFIREDIAGONAL_FALL].img = IMAGEMANAGER->findImage("Clu_jumpFireDiagonal_fall");
		_player[JUMPFIREDIAGONAL_FALL].shadow = IMAGEMANAGER->findImage("Clu_jumpFireDiagonal_fall_shadow");
		_player[JUMPFIREDIAGONAL_RISE].img = IMAGEMANAGER->findImage("Clu_jumpFireDiagonal_rise");
		_player[JUMPFIREDIAGONAL_RISE].shadow = IMAGEMANAGER->findImage("Clu_jumpFireDiagonal_rise_shadow");
		_player[LAND].img = IMAGEMANAGER->findImage("Clu_land");
		_player[LAND].shadow = IMAGEMANAGER->findImage("Clu_land_shadow");
		_player[LAUGH].img = IMAGEMANAGER->findImage("Clu_laugh");
		_player[LAUGH].shadow = IMAGEMANAGER->findImage("Clu_laugh_shadow");
		_player[LAUGH_IDLE].img = IMAGEMANAGER->findImage("Clu_laugh_idle");
		_player[LAUGH_IDLE].shadow = IMAGEMANAGER->findImage("Clu_laugh_idle_shadow");
		_player[LEDGEGRAB].img = IMAGEMANAGER->findImage("Clu_ledgeGrab");
		_player[LEDGEGRAB].shadow = IMAGEMANAGER->findImage("Clu_ledgeGrab_shadow");
		_player[LEDGEGRAB_IDLE].img = IMAGEMANAGER->findImage("Clu_ledgeGrab_idle");
		_player[LEDGEGRAB_IDLE].shadow = IMAGEMANAGER->findImage("Clu_ledgeGrab_idle_shadow");
		_player[LEDGEGRAB_RISE].img = IMAGEMANAGER->findImage("Clu_ledgeGrab_rise");
		_player[LEDGEGRAB_RISE].shadow = IMAGEMANAGER->findImage("Clu_ledgeGrab_rise_shadow");
		_player[LOOKUP].img = IMAGEMANAGER->findImage("Clu_lookup");
		_player[LOOKUP].shadow = IMAGEMANAGER->findImage("Clu_lookup_shadow");
		_player[PUSH].img = IMAGEMANAGER->findImage("Clu_push");
		_player[PUSH].shadow = IMAGEMANAGER->findImage("Clu_push_shadow");
		_player[RUN].img = IMAGEMANAGER->findImage("Clu_run");
		_player[RUN].shadow = IMAGEMANAGER->findImage("Clu_run_shadow");
		_player[THINK].img = IMAGEMANAGER->findImage("Clu_think");
		_player[THINK].shadow = IMAGEMANAGER->findImage("Clu_think_shadow");
		_player[THINK_IDLE].img = IMAGEMANAGER->findImage("Clu_think_idle");
		_player[THINK_IDLE].shadow = IMAGEMANAGER->findImage("Clu_think_idle_shadow");
		_player[UPSET].img = IMAGEMANAGER->findImage("Clu_upset");
		_player[UPSET].shadow = IMAGEMANAGER->findImage("Clu_upset_shadow");

		_weapon[AIM_DIAGONAL].img = IMAGEMANAGER->findImage("Clu_gun_aim_diagonal");
		_weapon[AIM_DIAGONAL_FULLCHARGE].img = IMAGEMANAGER->findImage("Clu_gun_aim_diagonal_fullCharge");
		_weapon[AIM_DIAGONAL_FULLCHARGE_IDLE].img = IMAGEMANAGER->findImage("Clu_gun_aim_diagonal_fullCharge_idle");
		_weapon[AIM_DIAGONALFIRE].img = IMAGEMANAGER->findImage("Clu_gun_aim_diagonalFire");
		_weapon[AIM_FIRE].img = IMAGEMANAGER->findImage("Clu_gun_aim_fire");
		_weapon[AIM_IDLE].img = IMAGEMANAGER->findImage("Clu_gun_aim_idle");
		_weapon[CHARGE].img = IMAGEMANAGER->findImage("Clu_gun_charge");
		_weapon[FULLCHARGE].img = IMAGEMANAGER->findImage("Clu_gun_fullCharge");
		_weapon[FULLCHARGE_IDLE].img = IMAGEMANAGER->findImage("Clu_gun_fullCharge_idle");
		_weapon[JUMPFIRE_FALL].img = IMAGEMANAGER->findImage("Clu_gun_jumpFire_fall");
		_weapon[JUMPFIRE_RISE].img = IMAGEMANAGER->findImage("Clu_gun_jumpFire_rise");

		_weaponIcon[0].img = IMAGEMANAGER->findImage("Clu_gun");
		_weaponIcon[1].img = IMAGEMANAGER->findImage("Clu_bow");
	}
	else if (_playerCharacter == BART)
	{

	}

	for (int i = 0; i < 2; i++)
	{
		_weaponIcon[i].alpha = 0;
		_weaponIcon[i].isActive = false;
	}

	for (int i = 0; i < MAXPLAYERSTATE; i++)
	{
		_player[i].alpha = 80;
	}
	
	//ü�¹� Ŭ���� ������ �ʱ�ȭ
	_hpBar = new progressBar;
	_hpBar->init("progressBarFront", "progressBarBack", _x, _y - 20, 50, 10);

	//���� �ʱ�ȭ
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
	_speed = 15.0f;

	_isFall = _isJump = _isBackstep = _isFaceDown = _isFired = _weaponSwitch = _isLedgeGrab = false;
	_onLand = true;

	_rc = RectMakeCenter(_x, _y, _player[_playerState].img->getFrameWidth() / 3, _player[_playerState].img->getFrameHeight());
	_rcLedge[0] = RectMake(_rc.left - 10, _rc.top + _player[_playerState].img->getFrameHeight() / 4, 10, 10);
	_rcLedge[1] = RectMake(_rc.right, _rc.top + _player[_playerState].img->getFrameHeight() / 4, 10, 10);

	return S_OK;
}

void player::release(void)
{
	//ü�¹� Ŭ���� ����
	//_hpBar->release();
	SAFE_DELETE(_hpBar);
}

void player::update(void)
{
	_rc = RectMakeCenter(_x, _y, _player[_playerState].img->getFrameWidth() / 3, _player[_playerState].img->getFrameHeight());
	_rcLedge[0] = RectMake(_rc.left - 10, _rc.top + _player[_playerState].img->getFrameHeight() / 4 , 10, 10);
	_rcLedge[1] = RectMake(_rc.right, _rc.top + _player[_playerState].img->getFrameHeight() / 4 , 10, 10);

	if (_playerState != AIM_FIRE &&
		_playerState != AIM_IDLE &&
		_playerState != CHARGE &&
		_playerState != FULLCHARGE &&
		_playerState != FULLCHARGE_IDLE &&
		_playerState != JUMPFIRE_FALL &&
		_playerState != JUMPFIRE_RISE &&
		_playerState != AIM_DIAGONAL &&
		_playerState != AIM_DIAGONAL_FULLCHARGE &&
		_playerState != AIM_DIAGONAL_FULLCHARGE_IDLE &&
		_playerState != AIM_DIAGONALFIRE)
		_isFired = false;

	this->frameChangeLoop();
	this->weaponSwitch(_weaponSwitch);
}

void player::render(void)
{
	if (_playerState != AIM_FIRE &&
		_playerState != AIM_IDLE &&
		_playerState != CHARGE &&
		_playerState != FULLCHARGE &&
		_playerState != FULLCHARGE_IDLE &&
		_playerState != JUMPFIRE_FALL &&
		_playerState != JUMPFIRE_RISE &&
		_playerState != AIM_DIAGONAL &&
		_playerState != AIM_DIAGONAL_FULLCHARGE &&
		_playerState != AIM_DIAGONAL_FULLCHARGE_IDLE &&
		_playerState != AIM_DIAGONALFIRE)
		_isFired = false;

	this->frameChangeLoop();

	if (CAMERAMANAGER->CameraIn(_rc))
	{
		if (_isFired)
			_weapon[_playerState].img->frameRender(getMemDC(), _x - _player[_playerState].img->getFrameWidth() / 2 - CAMERAMANAGER->getCamera().left, _y - _player[_playerState].img->getFrameHeight() / 2 - CAMERAMANAGER->getCamera().top);

		_player[_playerState].shadow->alphaFrameRender(getMemDC(), _x - _player[_playerState].img->getFrameWidth() / 2 - CAMERAMANAGER->getCamera().left, _y - _player[_playerState].img->getFrameHeight() / 2 - CAMERAMANAGER->getCamera().top, _player[_playerState].alpha);
		_player[_playerState].img->frameRender(getMemDC(), _x - _player[_playerState].img->getFrameWidth() / 2 - CAMERAMANAGER->getCamera().left, _y - _player[_playerState].img->getFrameHeight() / 2 - CAMERAMANAGER->getCamera().top);

		if (_weaponIcon[_weaponSwitch].isActive)
			_weaponIcon[_weaponSwitch].img->alphaRender(getMemDC(), _x + 30 - _player[_playerState].img->getFrameWidth() / 2 - CAMERAMANAGER->getCamera().left, _y - 8 - _player[_playerState].img->getFrameHeight() / 2 - CAMERAMANAGER->getCamera().top, _weaponIcon[_weaponSwitch].alpha);
	}

	if (KEYMANAGER->isToggleKey('R'))
	{
		Rectangle(getMemDC(), _rc.left - CAMERAMANAGER->getCamera().left, _rc.top - CAMERAMANAGER->getCamera().top, _rc.right - CAMERAMANAGER->getCamera().left, _rc.bottom - CAMERAMANAGER->getCamera().top);
		//Rectangle(getMemDC(), _rcLedge[0].left - CAMERAMANAGER->getCamera().left, _rcLedge[0].top - CAMERAMANAGER->getCamera().top, _rcLedge[0].right - CAMERAMANAGER->getCamera().left, _rcLedge[0].bottom - CAMERAMANAGER->getCamera().top);
		//Rectangle(getMemDC(), _rcLedge[1].left - CAMERAMANAGER->getCamera().left, _rcLedge[1].top - CAMERAMANAGER->getCamera().top, _rcLedge[1].right - CAMERAMANAGER->getCamera().left, _rcLedge[1].bottom - CAMERAMANAGER->getCamera().top);
	}

	//ü�¹� ����
	_hpBar->render();

	char str[64];
	sprintf(str, "%d", _weaponIcon[_weaponSwitch].alpha);
	TextOut(getMemDC(), 100, 100, str, strlen(str));
}

void player::hitDamage(float damage)
{
	_currentHp -= damage;
}

void player::frameChangeLoop()
{
	_count++;
	
	_player[_playerState].img->setFrameY(_isLeft);
	_player[_playerState].shadow->setFrameY(_isLeft);
	if (_isFired)
		_weapon[_playerState].img->setFrameY(_isLeft);
	
	if (_isLeft) // 1
	{
		if (_count % _frameSpeed == 0)
		{
			_player[_playerState].img->setFrameX(_index);
			_player[_playerState].shadow->setFrameX(_index);
			if (_isFired)
				_weapon[_playerState].img->setFrameX(_index);
	
			_index--;
			
			if (_index < 0)
			{
				_index = _player[_playerState].img->getMaxFrameX();
			}
		}
	}
	else
	{
		if (_count % _frameSpeed == 0)
		{
			_player[_playerState].shadow->setFrameX(_index);
			if (_isFired)
				_weapon[_playerState].img->setFrameX(_index);
			_player[_playerState].img->setFrameX(_index);
			
			_index++;
			
			if (_index > _player[_playerState].img->getMaxFrameX())
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
		if (_weaponIcon[weaponSwitch].isActive)
		{
			if (_weaponCount < 50)
			{
				if (_weaponIcon[weaponSwitch].alpha < 255)
					_weaponIcon[weaponSwitch].alpha += 15;
				else
					_weaponCount++;
			}
			else
			{
				if (_weaponIcon[weaponSwitch].alpha > 0)
					_weaponIcon[weaponSwitch].alpha -= 15;
				else
					_weaponIcon[weaponSwitch].isActive = false;
			}
			
		}
		else
		{
			_weaponIcon[weaponSwitch].alpha = 0;
			_weaponCount = 0;
		}
	}
	else
	{
		_weaponIcon[weaponSwitch].isActive = false;
		_weaponCount = 0;
	}
}