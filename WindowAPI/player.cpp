#include "stdafx.h"
#include "player.h"

HRESULT player::init(PLAYERCHARACTER character)
{
	_character = character;

	if (_character == CLU)
	{
		_player[AIM_DIAGONAL].img = IMAGEMANAGER->findImage("Clu_aim_diagonal");
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
	else if (_character == BART)
	{
		_player[AIM_DIAGONAL].img = IMAGEMANAGER->findImage("Bart_hammer_idleDiagonal");
		_player[AIM_DIAGONAL].shadow = IMAGEMANAGER->findImage("Bart_hammer_idleDiagonal_shadow");
		_player[AIM_DIAGONAL_FULLCHARGE].img = IMAGEMANAGER->findImage("Bart_fullCharge");
		_player[AIM_DIAGONAL_FULLCHARGE].shadow = IMAGEMANAGER->findImage("Bart_fullCharge_shadow");
		_player[AIM_DIAGONAL_FULLCHARGE_IDLE].img = IMAGEMANAGER->findImage("Bart_fullCharge_idle");
		_player[AIM_DIAGONAL_FULLCHARGE_IDLE].shadow = IMAGEMANAGER->findImage("Bart_fullCharge_idle_shadow");
		_player[AIM_DIAGONALFIRE].img = IMAGEMANAGER->findImage("Bart_hammer_diagonal");
		_player[AIM_DIAGONALFIRE].shadow = IMAGEMANAGER->findImage("Bart_hammer_diagonal_shadow");
		_player[AIM_FIRE].img = IMAGEMANAGER->findImage("Bart_hammer");
		_player[AIM_FIRE].shadow = IMAGEMANAGER->findImage("Bart_hammer_shadow");
		_player[AIM_IDLE].img = IMAGEMANAGER->findImage("Bart_hammer_idle");
		_player[AIM_IDLE].shadow = IMAGEMANAGER->findImage("Bart_hammer_idle_shadow");
		_player[BACKSTEP].img = IMAGEMANAGER->findImage("Bart_block");
		_player[BACKSTEP].shadow = IMAGEMANAGER->findImage("Bart_block_shadow");
		_player[BORED].img = IMAGEMANAGER->findImage("Bart_bored");
		_player[BORED].shadow = IMAGEMANAGER->findImage("Bart_bored_shadow");
		_player[BORED_IDLE].img = IMAGEMANAGER->findImage("Bart_bored_idle");
		_player[BORED_IDLE].shadow = IMAGEMANAGER->findImage("Bart_bored_idle_shadow");
		_player[CHARGE].img = IMAGEMANAGER->findImage("Bart_charge");
		_player[CHARGE].shadow = IMAGEMANAGER->findImage("Bart_charge_shadow");
		_player[FAINT].img = IMAGEMANAGER->findImage("Bart_faint");
		_player[FAINT].shadow = IMAGEMANAGER->findImage("Bart_faint_shadow");
		_player[FAINT_IDLE].img = IMAGEMANAGER->findImage("Bart_faint_idle");
		_player[FAINT_IDLE].shadow = IMAGEMANAGER->findImage("Bart_faint_idle_shadow");
		_player[FULLCHARGE].img = IMAGEMANAGER->findImage("Bart_fullCharge");
		_player[FULLCHARGE].shadow = IMAGEMANAGER->findImage("Bart_fullCharge_shadow");
		_player[FULLCHARGE_IDLE].img = IMAGEMANAGER->findImage("Bart_fullCharge_idle");
		_player[FULLCHARGE_IDLE].shadow = IMAGEMANAGER->findImage("Bart_fullCharge_idle_shadow");
		_player[HIT].img = IMAGEMANAGER->findImage("Bart_hit");
		_player[HIT].shadow = IMAGEMANAGER->findImage("Bart_hit_shadow");
		_player[IDLE].img = IMAGEMANAGER->findImage("Bart_idle");
		_player[IDLE].shadow = IMAGEMANAGER->findImage("Bart_idle_shadow");
		_player[JUMP_FALL].img = IMAGEMANAGER->findImage("Bart_jump_fall");
		_player[JUMP_FALL].shadow = IMAGEMANAGER->findImage("Bart_jump_fall_shadow");
		_player[JUMP_RISE].img = IMAGEMANAGER->findImage("Bart_jump_rise");
		_player[JUMP_RISE].shadow = IMAGEMANAGER->findImage("Bart_jump_rise_shadow");
		_player[JUMPFIRE_FALL].img = IMAGEMANAGER->findImage("Bart_jump_hammer_fall");
		_player[JUMPFIRE_FALL].shadow = IMAGEMANAGER->findImage("Bart_jump_hammer_fall_shadow");
		//_player[JUMPFIRE_RISE].img = IMAGEMANAGER->findImage("Bart_hammerJump");
		//_player[JUMPFIRE_RISE].shadow = IMAGEMANAGER->findImage("Bart_hammerJump_shadow");
		_player[JUMPFIRE_RISE].img = IMAGEMANAGER->findImage("Bart_jump_hammer_rise");
		_player[JUMPFIRE_RISE].shadow = IMAGEMANAGER->findImage("Bart_jump_hammer_rise_shadow");
		_player[JUMPFIREDIAGONAL_FALL].img = IMAGEMANAGER->findImage("Clu_jumpFireDiagonal_fall");
		_player[JUMPFIREDIAGONAL_FALL].shadow = IMAGEMANAGER->findImage("Clu_jumpFireDiagonal_fall_shadow");
		_player[JUMPFIREDIAGONAL_RISE].img = IMAGEMANAGER->findImage("Clu_jumpFireDiagonal_rise");
		_player[JUMPFIREDIAGONAL_RISE].shadow = IMAGEMANAGER->findImage("Clu_jumpFireDiagonal_rise_shadow");
		_player[LAND].img = IMAGEMANAGER->findImage("Bart_land");
		_player[LAND].shadow = IMAGEMANAGER->findImage("Bart_land_shadow");
		_player[LAUGH].img = IMAGEMANAGER->findImage("Bart_laugh");
		_player[LAUGH].shadow = IMAGEMANAGER->findImage("Bart_laugh_shadow");
		_player[LAUGH_IDLE].img = IMAGEMANAGER->findImage("Bart_laugh_idle");
		_player[LAUGH_IDLE].shadow = IMAGEMANAGER->findImage("Bart_laugh_idle_shadow");
		_player[LEDGEGRAB].img = IMAGEMANAGER->findImage("Clu_ledgeGrab");
		_player[LEDGEGRAB].shadow = IMAGEMANAGER->findImage("Clu_ledgeGrab_shadow");
		_player[LEDGEGRAB_IDLE].img = IMAGEMANAGER->findImage("Clu_ledgeGrab_idle");
		_player[LEDGEGRAB_IDLE].shadow = IMAGEMANAGER->findImage("Clu_ledgeGrab_idle_shadow");
		_player[LEDGEGRAB_RISE].img = IMAGEMANAGER->findImage("Clu_ledgeGrab_rise");
		_player[LEDGEGRAB_RISE].shadow = IMAGEMANAGER->findImage("Clu_ledgeGrab_rise_shadow");
		_player[LOOKUP].img = IMAGEMANAGER->findImage("Bart_lookup");
		_player[LOOKUP].shadow = IMAGEMANAGER->findImage("Bart_lookup_shadow");
		_player[PUSH].img = IMAGEMANAGER->findImage("Bart_push");
		_player[PUSH].shadow = IMAGEMANAGER->findImage("Bart_push_shadow");
		_player[RUN].img = IMAGEMANAGER->findImage("Bart_run");
		_player[RUN].shadow = IMAGEMANAGER->findImage("Bart_run_shadow");
		_player[THINK].img = IMAGEMANAGER->findImage("Bart_think");
		_player[THINK].shadow = IMAGEMANAGER->findImage("Bart_think_shadow");
		_player[THINK_IDLE].img = IMAGEMANAGER->findImage("Bart_think_idle");
		_player[THINK_IDLE].shadow = IMAGEMANAGER->findImage("Bart_think_idle_shadow");
		_player[UPSET].img = IMAGEMANAGER->findImage("Bart_upset");
		_player[UPSET].shadow = IMAGEMANAGER->findImage("Bart_upset_shadow");

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

	for (int i = 0; i < 2; i++)
	{
		_weaponIcon[i].alpha = 0;
		_weaponIcon[i].isActive = false;
	}

	for (int i = 0; i < MAXPLAYERSTATE; i++)
	{
		_player[i].alpha = 255;
	}
	
	//체력바 클래스 생성후 초기화
	_hpBar = new progressBar;
	_hpBar->init("progressBarFront", "progressBarBack", _x, _y - 20, 50, 10);

	//피통 초기화
	_maxHp = 100;
	_currentHp = 100;
	_hpBar->setGauge(_currentHp, _maxHp);
	_state = IDLE;
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
	_isActive = true;

	//_rc = RectMakeCenter(_x, _y + _player[_state].img->getFrameHeight() / 6, _player[_state].img->getFrameWidth() / 3, _player[_state].img->getFrameHeight() / 3 * 2);
	_rc = RectMakeCenter(_x, _y, _player[_state].img->getFrameWidth() / 3, _player[_state].img->getFrameHeight());
	_rcLedge[0] = RectMake(_rc.left - 10, _rc.top + _player[_state].img->getFrameHeight() / 4, 10, 10);
	_rcLedge[1] = RectMake(_rc.right, _rc.top + _player[_state].img->getFrameHeight() / 4, 10, 10);

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
	//_rc = RectMakeCenter(_x, _y + _player[_state].img->getFrameHeight() / 6, _player[_state].img->getFrameWidth() / 3, _player[_state].img->getFrameHeight() / 3 * 2);
	_rc = RectMakeCenter(_x, _y, _player[_state].img->getFrameWidth() / 3, _player[_state].img->getFrameHeight());
	_rcLedge[0] = RectMake(_rc.left - 10, _rc.top + _player[_state].img->getFrameHeight() / 4 , 10, 10);
	_rcLedge[1] = RectMake(_rc.right, _rc.top + _player[_state].img->getFrameHeight() / 4 , 10, 10);

	for (int i = 0; i < MAXPLAYERSTATE; i++)
	{
		if (_isActive)
			_player[i].alpha = 255;
		else
			_player[i].alpha = 150;
	}

	if (_isActive)

	if (_state != AIM_FIRE &&
		_state != AIM_IDLE &&
		_state != CHARGE &&
		_state != FULLCHARGE &&
		_state != FULLCHARGE_IDLE &&
		_state != JUMPFIRE_FALL &&
		_state != JUMPFIRE_RISE &&
		_state != AIM_DIAGONAL &&
		_state != AIM_DIAGONAL_FULLCHARGE &&
		_state != AIM_DIAGONAL_FULLCHARGE_IDLE &&
		_state != AIM_DIAGONALFIRE)
		_isFired = false;

	this->frameChangeLoop();
	this->weaponSwitch(_weaponSwitch);
	this->collisionProcess();
}

void player::render(void)
{
	if (_state != AIM_FIRE &&
		_state != AIM_IDLE &&
		_state != CHARGE &&
		_state != FULLCHARGE &&
		_state != FULLCHARGE_IDLE &&
		_state != JUMPFIRE_FALL &&
		_state != JUMPFIRE_RISE &&
		_state != AIM_DIAGONAL &&
		_state != AIM_DIAGONAL_FULLCHARGE &&
		_state != AIM_DIAGONAL_FULLCHARGE_IDLE &&
		_state != AIM_DIAGONALFIRE)
		_isFired = false;

	this->frameChangeLoop();

	if (CAMERAMANAGER->CameraIn(_rc))
	{
		if (_character == CLU && _isFired)
			_weapon[_state].img->frameRender(getMemDC(), _x - _player[_state].img->getFrameWidth() / 2 - CAMERAMANAGER->getCamera().left, _y - _player[_state].img->getFrameHeight() / 2 - CAMERAMANAGER->getCamera().top);

		_player[_state].shadow->alphaFrameRender(getMemDC(), _x - _player[_state].img->getFrameWidth() / 2 - CAMERAMANAGER->getCamera().left, _y - _player[_state].img->getFrameHeight() / 2 - CAMERAMANAGER->getCamera().top, _player[_state].alpha * 0.3f);
		_player[_state].img->alphaFrameRender(getMemDC(), _x - _player[_state].img->getFrameWidth() / 2 - CAMERAMANAGER->getCamera().left, _y - _player[_state].img->getFrameHeight() / 2 - CAMERAMANAGER->getCamera().top, _player[_state].alpha);

		if (_character == CLU && _weaponIcon[_weaponSwitch].isActive)
			_weaponIcon[_weaponSwitch].img->alphaRender(getMemDC(), _x + 30 - _player[_state].img->getFrameWidth() / 2 - CAMERAMANAGER->getCamera().left, _y - 8 - _player[_state].img->getFrameHeight() / 2 - CAMERAMANAGER->getCamera().top, _weaponIcon[_weaponSwitch].alpha);
	}

	if (KEYMANAGER->isToggleKey('R'))
	{
		Rectangle(getMemDC(), _rc.left - CAMERAMANAGER->getCamera().left, _rc.top - CAMERAMANAGER->getCamera().top, _rc.right - CAMERAMANAGER->getCamera().left, _rc.bottom - CAMERAMANAGER->getCamera().top);
		//Rectangle(getMemDC(), _rcLedge[0].left - CAMERAMANAGER->getCamera().left, _rcLedge[0].top - CAMERAMANAGER->getCamera().top, _rcLedge[0].right - CAMERAMANAGER->getCamera().left, _rcLedge[0].bottom - CAMERAMANAGER->getCamera().top);
		//Rectangle(getMemDC(), _rcLedge[1].left - CAMERAMANAGER->getCamera().left, _rcLedge[1].top - CAMERAMANAGER->getCamera().top, _rcLedge[1].right - CAMERAMANAGER->getCamera().left, _rcLedge[1].bottom - CAMERAMANAGER->getCamera().top);
	}

	//체력바 렌더
	_hpBar->render();
}

void player::hitDamage(float damage)
{
	_currentHp -= damage;
}

void player::frameChangeLoop()
{
	_count++;
	
	_player[_state].img->setFrameY(_isLeft);
	_player[_state].shadow->setFrameY(_isLeft);
	if (_isFired)
		_weapon[_state].img->setFrameY(_isLeft);
	
	if (_isLeft) // 1
	{
		if (_count % _frameSpeed == 0)
		{
			_player[_state].img->setFrameX(_index);
			_player[_state].shadow->setFrameX(_index);
			if (_isFired)
				_weapon[_state].img->setFrameX(_index);
	
			_index--;
			
			if (_index < 0)
			{
				_index = _player[_state].img->getMaxFrameX();
			}
		}
	}
	else
	{
		if (_count % _frameSpeed == 0)
		{
			_player[_state].shadow->setFrameX(_index);
			if (_isFired)
				_weapon[_state].img->setFrameX(_index);
			_player[_state].img->setFrameX(_index);
			
			_index++;
			
			if (_index > _player[_state].img->getMaxFrameX())
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

void player::collisionProcess()
{
	if (COLLISIONMANAGER->pixelCollision(_rc, _x, _y, _speed, _gravity, BOTTOM))
	{
		if (-sinf(_angle) * _speed + _gravity >= 0)
		{
			_speed = 0.0f;
			_gravity = 0.0f;
			_angle = -PI_2;
			_isJump = false;
			
			if (!_onLand)
			{
				EFFECTMANAGER->play("landDust", _x, _y + _player[_state].img->getFrameHeight() * 0.35);
				SOUNDMANAGER->play("Clu_land" + to_string(RND->getFromIntTo(1, 3)));
			}
			_onLand = true;
		}
	}
	else if (COLLISIONMANAGER->pixelCollision(_rc, _x, _y, _speed, _gravity, TOP))// == RED)
	{
		_angle = -PI_2;
		_gravity = 0.0f;
	}
	//if (_onLand)
	{
		if (COLLISIONMANAGER->pixelCollision(_rc, _x, _y, _speed, _gravity, LEFT) ||
			COLLISIONMANAGER->pixelCollision(_rc, _x, _y, _speed, _gravity, RIGHT))
		{
			if (!_isJump)
				_state = PUSH;
		}
	}

	if (COLLISIONMANAGER->pixelCollision(_rc, _x, _y, _speed, _gravity, BOTTOM) == BLUE)
	{
		if (-sinf(_angle) * _speed + _gravity >= 0)
		{
			_speed = 0.0f;
			_gravity = 0.0f;
			_angle = -PI_2;
			_isJump = false;
			if (!_onLand)
				EFFECTMANAGER->play("landDust", _x, _y + _player[_state].img->getFrameHeight() * 0.35);
			_onLand = true;
		}
	}
}
