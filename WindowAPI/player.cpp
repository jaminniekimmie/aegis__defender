#include "stdafx.h"
#include "player.h"

HRESULT player::init(void)
{
	_player_clu[AIM_DIAGONAL].img = IMAGEMANAGER->findImage("Clu_aim_diagonal");
	_player_clu[AIM_DIAGONAL].shadow = IMAGEMANAGER->findImage("Clu_aim_diagonal_shadow");
	_player_clu[AIM_DIAGONAL_FULLCHARGE].img = IMAGEMANAGER->findImage("Clu_aim_diagonal_fullCharge");
	_player_clu[AIM_DIAGONAL_FULLCHARGE].shadow = IMAGEMANAGER->findImage("Clu_aim_diagonal_fullCharge_shadow");
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
	_player_clu[CHARGE].img = IMAGEMANAGER->findImage("Clu_charge");
	_player_clu[CHARGE].shadow = IMAGEMANAGER->findImage("Clu_charge_shadow");
	_player_clu[FAINT].img = IMAGEMANAGER->findImage("Clu_faint");
	_player_clu[FAINT].shadow = IMAGEMANAGER->findImage("Clu_faint_shadow");
	_player_clu[FAINT_IDLE].img = IMAGEMANAGER->findImage("Clu_faint_idle");
	_player_clu[FAINT_IDLE].shadow = IMAGEMANAGER->findImage("Clu_faint_idle_shadow");
	_player_clu[FULLCHARGE].img = IMAGEMANAGER->findImage("Clu_fullCharge");
	_player_clu[FULLCHARGE].shadow = IMAGEMANAGER->findImage("Clu_fullCharge_shadow");
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
	_player_clu[LEDGEGRAB].img = IMAGEMANAGER->findImage("Clu_ledgeGrab");
	_player_clu[LEDGEGRAB].shadow = IMAGEMANAGER->findImage("Clu_ledgeGrab_shadow");
	_player_clu[LOOKUP].img = IMAGEMANAGER->findImage("Clu_lookup");
	_player_clu[LOOKUP].shadow = IMAGEMANAGER->findImage("Clu_lookup_shadow");
	_player_clu[PUSH].img = IMAGEMANAGER->findImage("Clu_push");
	_player_clu[PUSH].shadow = IMAGEMANAGER->findImage("Clu_push_shadow");
	_player_clu[RUN].img = IMAGEMANAGER->findImage("Clu_run");
	_player_clu[RUN].shadow = IMAGEMANAGER->findImage("Clu_run_shadow");

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
	_y = TILESIZEY - WINSIZEY / 2;

	_animationSpeed = 10;
	_count = _index = 0;
	_gravity = 0.0f;
	_angle = -PI_2;
	_speed = 8.0f;

	_isFall = _isJump = false;
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
	_rc = RectMake(_x + _player_clu[_playerState].img->getFrameWidth() / 3, _y, _player_clu[_playerState].img->getFrameWidth() / 3, _player_clu[_playerState].img->getFrameHeight() / 3);

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
}

void player::render(void)
{
	_player_clu[_playerState].shadow->alphaFrameRender(getMemDC(), _x - CAMERAMANAGER->getCamera().left, _y - CAMERAMANAGER->getCamera().top, _player_clu[_playerState].alpha);
	_player_clu[_playerState].img->frameRender(getMemDC(), _x - CAMERAMANAGER->getCamera().left, _y - CAMERAMANAGER->getCamera().top);

	//체력바 렌더
	_hpBar->render();

	char str[64];
	sprintf(str, "%f", ANGLE);
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

	if (_isLeft)
	{
		if (_count % _animationSpeed == 0)
		{
			_index--;
			if (_index < 0)
			{
				_index = _player_clu[_playerState].img->getMaxFrameX();
			}
			_player_clu[_playerState].img->setFrameX(_index);
			_player_clu[_playerState].shadow->setFrameX(_index);
		}
	}
	else
	{
		if (_count % _animationSpeed == 0)
		{
			_index++;
			if (_index > _player_clu[_playerState].img->getMaxFrameX())
			{
				_index = 0;
			}
			_player_clu[_playerState].img->setFrameX(_index);
			_player_clu[_playerState].shadow->setFrameX(_index);
		}
	}
}

void player::frameChangeOnce()
{
}