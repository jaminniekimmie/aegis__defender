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

		for (int i = 0; i < MAXPLAYERSTATE; i++)
		{
			_weapon[GUN][i].img = IMAGEMANAGER->addImage("blank", 116, 116);
			_weapon[BOW][i].img = IMAGEMANAGER->addImage("blank", 116, 116);
		}

		_weapon[GUN][AIM_DIAGONAL].img = IMAGEMANAGER->findImage("Clu_gun_aim_diagonal");
		_weapon[GUN][AIM_DIAGONAL_FULLCHARGE].img = IMAGEMANAGER->findImage("Clu_gun_aim_diagonal_fullCharge");
		_weapon[GUN][AIM_DIAGONAL_FULLCHARGE_IDLE].img = IMAGEMANAGER->findImage("Clu_gun_aim_diagonal_fullCharge_idle");
		_weapon[GUN][AIM_DIAGONALFIRE].img = IMAGEMANAGER->findImage("Clu_gun_aim_diagonalFire");
		_weapon[GUN][AIM_FIRE].img = IMAGEMANAGER->findImage("Clu_gun_aim_fire");
		_weapon[GUN][AIM_IDLE].img = IMAGEMANAGER->findImage("Clu_gun_aim_idle");
		_weapon[GUN][CHARGE].img = IMAGEMANAGER->findImage("Clu_gun_charge");
		_weapon[GUN][FULLCHARGE].img = IMAGEMANAGER->findImage("Clu_gun_fullCharge");
		_weapon[GUN][FULLCHARGE_IDLE].img = IMAGEMANAGER->findImage("Clu_gun_fullCharge_idle");
		_weapon[GUN][JUMPFIRE_FALL].img = IMAGEMANAGER->findImage("Clu_gun_jumpFire_fall");
		_weapon[GUN][JUMPFIRE_RISE].img = IMAGEMANAGER->findImage("Clu_gun_jumpFire_rise");

		_weapon[BOW][AIM_DIAGONAL].img = IMAGEMANAGER->findImage("Clu_bow_aim_diagonal");
		_weapon[BOW][AIM_DIAGONAL_FULLCHARGE].img = IMAGEMANAGER->findImage("Clu_bow_aim_diagonal_fullCharge");
		_weapon[BOW][AIM_DIAGONAL_FULLCHARGE_IDLE].img = IMAGEMANAGER->findImage("Clu_bow_aim_diagonal_fullCharge_idle");
		_weapon[BOW][AIM_DIAGONALFIRE].img = IMAGEMANAGER->findImage("Clu_bow_aim_diagonalFire");
		_weapon[BOW][AIM_FIRE].img = IMAGEMANAGER->findImage("Clu_bow_aim_fire");
		_weapon[BOW][AIM_IDLE].img = IMAGEMANAGER->findImage("Clu_bow_aim_idle");
		_weapon[BOW][CHARGE].img = IMAGEMANAGER->findImage("Clu_bow_charge");
		_weapon[BOW][FULLCHARGE].img = IMAGEMANAGER->findImage("Clu_bow_fullCharge");
		_weapon[BOW][FULLCHARGE_IDLE].img = IMAGEMANAGER->findImage("Clu_bow_fullCharge_idle");
		_weapon[BOW][JUMPFIRE_FALL].img = IMAGEMANAGER->findImage("Clu_bow_jumpFire_fall");
		_weapon[BOW][JUMPFIRE_RISE].img = IMAGEMANAGER->findImage("Clu_bow_jumpFire_rise");

		_weaponIcon[GUN].img = IMAGEMANAGER->findImage("Clu_gun");
		_weaponIcon[BOW].img = IMAGEMANAGER->findImage("Clu_bow");
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

		_weaponIcon[GUN].img = IMAGEMANAGER->findImage("Clu_gun");
		_weaponIcon[BOW].img = IMAGEMANAGER->findImage("Clu_bow");
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
	
	_hpBar_red = new pHpBar;
	_hpBar_red->init("GUI_heart_red", "GUI_heart_shadow", 22, 25);

	_hpBar_yellow = new pHpBar;
	_hpBar_yellow->init("GUI_heart_yellow", "GUI_heart_shadow", 22, 64);

	//피통 초기화
	_maxHp = _currentHp = 6;
	_currentMp = 4;
	_hpBar_red->setGauge(_currentHp, _maxHp);
	_hpBar_yellow->setGauge(_currentMp, _maxHp);
	_state = IDLE;
	_currentWeapon = GUN;
	_isLeft = RIGHT;
	_weaponSwitch = false;

	_x = WINSIZEX / 2;
	_y = TILESIZEY - WINSIZEY;

	_frameSpeed = 10;
	_count = _index = _weaponCount = 0;
	_gravity = 0.0f;
	_angle = -PI_2;
	_speed = 16.0f;

	_isFall = _isJump = _isBackstep = _isFaceDown = _isFired = _currentWeapon = _isLedgeGrab = false;
	_onLand = true;
	_isActive = true;

	_rc = RectMakeCenter(_x, _y + _player[_state].img->getFrameHeight() / 6, _player[_state].img->getFrameWidth() / 3, _player[_state].img->getFrameHeight() / 3 * 2);
	//_rc = RectMakeCenter(_x, _y, _player[_state].img->getFrameWidth() / 3, _player[_state].img->getFrameHeight());
	_rcLedge[0] = RectMake(_rc.left - 10, _rc.top + _player[_state].img->getFrameHeight() / 4, 10, 10);
	_rcLedge[1] = RectMake(_rc.right, _rc.top + _player[_state].img->getFrameHeight() / 4, 10, 10);

	if (_character == BART)
	{
		if (_isLeft)
			_rcHammer = RectMake(_x - _player[_state].img->getFrameWidth() * 0.5f, _y - _player[_state].img->getFrameHeight() * 0.5f, _player[_state].img->getFrameWidth(), _player[_state].img->getFrameHeight());
		else
			_rcHammer = RectMake(_x, _y - _player[_state].img->getFrameHeight() * 0.5f, _player[_state].img->getFrameWidth(), _player[_state].img->getFrameHeight());
	}

	return S_OK;
}

void player::release(void)
{
	//체력바 클래스 해제
	_hpBar_red->release();
	SAFE_DELETE(_hpBar_red);
	_hpBar_yellow->release();
	SAFE_DELETE(_hpBar_yellow);
}

void player::update(void)
{
	_rc = RectMakeCenter(_x, _y + _player[_state].img->getFrameHeight() / 6, _player[_state].img->getFrameWidth() / 3, _player[_state].img->getFrameHeight() / 3 * 2);
	//_rc = RectMakeCenter(_x, _y, _player[_state].img->getFrameWidth() / 3, _player[_state].img->getFrameHeight());
	_rcLedge[0] = RectMake(_rc.left - 10, _rc.top + _player[_state].img->getFrameHeight() / 4 , 10, 10);
	_rcLedge[1] = RectMake(_rc.right, _rc.top + _player[_state].img->getFrameHeight() / 4 , 10, 10);

	if (_character == BART && _isActive && (_state == AIM_FIRE || _state == JUMPFIRE_RISE || _state == AIM_DIAGONALFIRE))
	{
		if (_isLeft)
			_rcHammer = RectMake(_x - _player[_state].img->getFrameWidth() * 0.5f, _y - _player[_state].img->getFrameHeight() * 0.5f, _player[_state].img->getFrameWidth() * 0.33f, _player[_state].img->getFrameHeight());
		else
			_rcHammer = RectMake(_x + _player[_state].img->getFrameWidth() / 6, _y - _player[_state].img->getFrameHeight() * 0.5f, _player[_state].img->getFrameWidth() * 0.33f, _player[_state].img->getFrameHeight());
	}
	else
		_rcHammer = RectMake(_x, _y, 0, 0);

	_hpBar_red->setGauge(_currentHp, _maxHp);
	_hpBar_yellow->setGauge(_currentMp, _maxHp);

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
	this->weaponSwitch();
	this->collisionProcess();
}

void player::render(void)
{
	this->frameChangeLoop();

	if (CAMERAMANAGER->CameraIn(_rc))
	{
		if (_character == CLU && _isFired)
			_weapon[_currentWeapon][_state].img->frameRender(getMemDC(), _x - _player[_state].img->getFrameWidth() / 2 - CAMERAMANAGER->getCamera().left, _y - _player[_state].img->getFrameHeight() / 2 - CAMERAMANAGER->getCamera().top, _index, _isLeft);

		_player[_state].shadow->alphaFrameRender(getMemDC(), _x - _player[_state].img->getFrameWidth() / 2 - CAMERAMANAGER->getCamera().left, _y - _player[_state].img->getFrameHeight() / 2 - CAMERAMANAGER->getCamera().top, _index, _isLeft, _player[_state].alpha * 0.3f);
		_player[_state].img->alphaFrameRender(getMemDC(), _x - _player[_state].img->getFrameWidth() / 2 - CAMERAMANAGER->getCamera().left, _y - _player[_state].img->getFrameHeight() / 2 - CAMERAMANAGER->getCamera().top, _index, _isLeft, _player[_state].alpha);

		if (_character == CLU && _weaponSwitch)
			_weaponIcon[_currentWeapon].img->alphaRender(getMemDC(), _x + 30 - _player[_state].img->getFrameWidth() / 2 - CAMERAMANAGER->getCamera().left, _y - 8 - _player[_state].img->getFrameHeight() / 2 - CAMERAMANAGER->getCamera().top, _weaponIcon[_currentWeapon].alpha);
	}

	if (KEYMANAGER->isToggleKey('R'))
	{
		Rectangle(getMemDC(), _rc.left - CAMERAMANAGER->getCamera().left, _rc.top - CAMERAMANAGER->getCamera().top, _rc.right - CAMERAMANAGER->getCamera().left, _rc.bottom - CAMERAMANAGER->getCamera().top);
		Rectangle(getMemDC(), _rcHammer.left - CAMERAMANAGER->getCamera().left, _rcHammer.top - CAMERAMANAGER->getCamera().top, _rcHammer.right - CAMERAMANAGER->getCamera().left, _rcHammer.bottom - CAMERAMANAGER->getCamera().top);
	}
}

void player::hitDamage(float damage)
{
	_currentHp -= damage;
}

void player::addHp()
{
	_currentHp += 2;
	if (_currentHp > _maxHp)
		_currentHp = _maxHp;
}

void player::addMp()
{
	_currentMp += 2;
	if (_currentMp > _maxHp)
		_currentMp = _maxHp;
}

void player::frameChangeLoop()
{
	_count++;
	
	_player[_state].img->setFrameY(_isLeft);
	_player[_state].shadow->setFrameY(_isLeft);
	if (_isFired)
		_weapon[_currentWeapon][_state].img->setFrameY(_isLeft);
	
	if (_isLeft) // 1
	{
		if (_count % _frameSpeed == 0)
		{
			_player[_state].img->setFrameX(_index);
			_player[_state].shadow->setFrameX(_index);
			if (_isFired)
				_weapon[_currentWeapon][_state].img->setFrameX(_index);
	
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
				_weapon[_currentWeapon][_state].img->setFrameX(_index);
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

void player::weaponSwitch()
{
	if (_weaponSwitch)
	{
		if (_weaponCount < 40)
		{
			if (_weaponIcon[_currentWeapon].alpha < 255)
				_weaponIcon[_currentWeapon].alpha += 15;
			else
				_weaponCount++;
		}
		else
		{
			if (_weaponIcon[_currentWeapon].alpha > 0)
				_weaponIcon[_currentWeapon].alpha -= 15;
			else
				_weaponSwitch = false;
		}

	}
	else
	{
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

	if (COLLISIONMANAGER->pixelCollision(_rc, _x, _y, _speed, _gravity, LEFT) ||
		COLLISIONMANAGER->pixelCollision(_rc, _x, _y, _speed, _gravity, RIGHT))
	{
		if (!_isJump)
			_state = PUSH;
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
