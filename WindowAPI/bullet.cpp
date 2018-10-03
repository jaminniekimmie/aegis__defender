#include "stdafx.h"
#include "bullet.h"
//=============================================================
//	## bullet ## (공용총알 - 너희들이 만들면 된다)
//=============================================================
HRESULT bullet::init(const char * imageName, int bulletMax, float range)
{
	//총알 이미지 초기화
	_imageName = imageName;
	//총알갯수 및 사거리 초기화
	_bulletMax = bulletMax;
	_range = range;

	return S_OK;
}

void bullet::release(void)
{
}

void bullet::update(void)
{
	this->move();
	this->collision();
}

void bullet::render(void)
{
	_viMagazine = _vMagazine.begin();
	for (_viMagazine; _viMagazine != _vMagazine.end(); ++_viMagazine)
	{
		if (!CAMERAMANAGER->CameraIn(_viMagazine->rc)) continue;
		_viMagazine->bulletImage->alphaRender(getMemDC(), _viMagazine->rc.left - CAMERAMANAGER->getCamera().left, _viMagazine->rc.top - CAMERAMANAGER->getCamera().top, _viMagazine->alpha);
	}

	_viParticle = _vParticle.begin();
	for (_viParticle; _viParticle != _vParticle.end(); ++_viParticle)
	{
		if (!_viParticle->fire) continue;
		if (!CAMERAMANAGER->CameraIn(_viParticle->rc)) continue;
		_viParticle->bulletImage->alphaRender(getMemDC(), _viParticle->rc.left - CAMERAMANAGER->getCamera().left, _viParticle->rc.top - CAMERAMANAGER->getCamera().top, _viParticle->alpha);
	}

	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!CAMERAMANAGER->CameraIn(_viBullet->rc)) continue;
		_viBullet->bulletImage->render(getMemDC(), _viBullet->rc.left - CAMERAMANAGER->getCamera().left, _viBullet->rc.top - CAMERAMANAGER->getCamera().top);
	}
}

void bullet::fire(float x, float y, float angle, float speed)
{
	//총알 벡터에 담는것을 제한하자
	if (_bulletMax < _vBullet.size() + 1) return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = IMAGEMANAGER->findImage(_imageName);
	bullet.speed = speed;
	bullet.angle = angle;
	bullet.alpha = 255;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->getWidth(),
		bullet.bulletImage->getHeight());

	//벡터에 담기
	_vBullet.push_back(bullet);


	int randNo = RND->getFromIntTo(8, 15);

	for (int i = 0; i < randNo / 3; i++)
	{
		tagBullet particle;
		ZeroMemory(&particle, sizeof(tagBullet));
		particle.bulletImage = IMAGEMANAGER->findImage("dot_teal");
		particle.speed = speed;
		particle.angle = angle;
		particle.alpha = 255;
		particle.x = particle.fireX = x;
		particle.y = particle.fireY = y;
		particle.fire = false;
		particle.rc = RectMakeCenter(particle.x, particle.y,
			particle.bulletImage->getWidth(),
			particle.bulletImage->getHeight());

		//벡터에 담기
		_vParticle.push_back(particle);
	}


	for (int i = 0; i < randNo; i++)
	{
		tagBullet particle;
		ZeroMemory(&particle, sizeof(tagBullet));
		particle.bulletImage = IMAGEMANAGER->findImage("dot_white");
		particle.speed = speed;
		particle.angle = angle;
		particle.alpha = 255;
		particle.x = particle.fireX = x;
		particle.y = particle.fireY = y;
		particle.fire = false;
		particle.rc = RectMakeCenter(particle.x, particle.y,
			particle.bulletImage->getWidth(),
			particle.bulletImage->getHeight());

		//벡터에 담기
		_vParticle.push_back(particle);
	}

	tagBullet magazine;
	ZeroMemory(&magazine, sizeof(tagBullet));
	magazine.bulletImage = IMAGEMANAGER->findImage("magazine");
	magazine.speed = RND->getFromFloatTo(8.0f, 12.0f);
	magazine.angle = RND->getFromIntTo(0, 1) ? PI / 3 : PI - PI / 3;
	magazine.alpha = 255;
	magazine.x = magazine.fireX = x;
	magazine.y = magazine.fireY = y;
	magazine.rc = RectMakeCenter(magazine.x, magazine.y,
		magazine.bulletImage->getWidth(),
		magazine.bulletImage->getHeight());

	//벡터에 담기
	_vMagazine.push_back(magazine);
}

void bullet::move()
{
	RECT rcTemp;

	_viBullet = _vBullet.begin();
	for (; _viBullet != _vBullet.end();)
	{
		_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->y += -sinf(_viBullet->angle) * _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getWidth(),
			_viBullet->bulletImage->getHeight());

		//총알이 사거리보다 커졌을때
		float distance = getDistance(_viBullet->fireX, _viBullet->fireY,
			_viBullet->x, _viBullet->y);
		if (_range < distance)
		{
			//EFFECTMANAGER->play("bulletPuff" + to_string(RND->getFromIntTo(1, 5)), _viBullet->rc.left, _viBullet->rc.top);
			_viBullet = _vBullet.erase(_viBullet);
		}
		else
		{
			++_viBullet;
		}
	}

	for (int i = 0; i < _vParticle.size(); i++)
	{
		if (_vParticle[i].fire)
		{
			_vParticle[i].count++;

			if (_vParticle[i].count > 20)
			{
				_vParticle[i].alpha -= 15;

				if (_vParticle[i].alpha <= 0)
					_vParticle.erase(_vParticle.begin() + i);
			}
		}
		else
		{
			_vParticle[i].x = _vParticle[i].fireX + cosf(_vParticle[i].angle) * RND->getFloat(_range) + RND->getFloat(10) - 5;
			_vParticle[i].y = _vParticle[i].fireY - sinf(_vParticle[i].angle) * RND->getFloat(_range) + RND->getFloat(10) - 5;

			_vParticle[i].rc = RectMakeCenter(_vParticle[i].x, _vParticle[i].y,
				_vParticle[i].bulletImage->getWidth(),
				_vParticle[i].bulletImage->getHeight());

			for (int j = 0; j < _vBullet.size(); j++)
			{
				if (IntersectRect(&rcTemp, &_vParticle[i].rc, &_vBullet[j].rc))
					_vParticle[i].fire = true;
			}
		}
	}

	_viMagazine = _vMagazine.begin();
	for (; _viMagazine != _vMagazine.end();)
	{
		_viMagazine->gravity += 0.55f;
		_viMagazine->x += cosf(_viMagazine->angle) * _viMagazine->speed;
		_viMagazine->y += -sinf(_viMagazine->angle) * _viMagazine->speed + _viMagazine->gravity;
		_viMagazine->rc = RectMakeCenter(_viMagazine->x, _viMagazine->y,
			_viMagazine->bulletImage->getWidth(),
			_viMagazine->bulletImage->getHeight());

		//총알이 사거리보다 커졌을때
		float distance = getDistance(_viMagazine->fireX, _viMagazine->fireY,
			_viMagazine->x, _viMagazine->y);

		if (_range < distance || _viMagazine->speed <= 1.0f)
		{
			_viMagazine->alpha -= 15;

			if (_viMagazine->alpha <= 0)
				_viMagazine = _vMagazine.erase(_viMagazine);
		}
		else
		{
			++_viMagazine;
		}
	}
}

void bullet::collision()
{
	for (int i = 0; i < _vMagazine.size(); i++)
	{
		float x = _vMagazine[i].x;
		float y = _vMagazine[i].y;

		if (COLLISIONMANAGER->pixelCollision(_vMagazine[i].rc, x, y, _vMagazine[i].speed, _vMagazine[i].gravity, BOTTOM))
		{
			_vMagazine[i].gravity = 0.0f;
			_vMagazine[i].speed *= 0.8;
			//_vMagazine[i].x = x;
			//_vMagazine[i].y = y;
		}
		else if (COLLISIONMANAGER->pixelCollision(_vMagazine[i].rc, x, y, _vMagazine[i].speed, _vMagazine[i].gravity, TOP))
		{
			_vMagazine[i].angle = PI_2 - _vMagazine[i].angle;
			_vMagazine[i].speed *= 0.8;
			//_vMagazine[i].x = x;
			//_vMagazine[i].y = y;
		}

		if (COLLISIONMANAGER->pixelCollision(_vMagazine[i].rc, x, y, _vMagazine[i].speed, _vMagazine[i].gravity, LEFT))
		{
			_vMagazine[i].angle = PI - _vMagazine[i].angle;
			_vMagazine[i].speed *= 0.8;
			//_vMagazine[i].x = x;
			//_vMagazine[i].y = y;
		}
		else if (COLLISIONMANAGER->pixelCollision(_vMagazine[i].rc, x, y, _vMagazine[i].speed, _vMagazine[i].gravity, RIGHT))
		{
			_vMagazine[i].angle = PI - _vMagazine[i].angle;
			_vMagazine[i].speed *= 0.8;
			//_vMagazine[i].x = x;
			//_vMagazine[i].y = y;
		}
	}

	for (int i = 0; i < _vBullet.size(); i++)
	{
		float x = _vBullet[i].x;
		float y = _vBullet[i].y;

		//if (COLLISIONMANAGER->pixelCollision(_vBullet[i].rc, x, y, _vBullet[i].speed, _vBullet[i].gravity, BOTTOM) ||
		//COLLISIONMANAGER->pixelCollision(_vBullet[i].rc, x, y, _vBullet[i].speed, _vBullet[i].gravity, TOP) ||
		if (COLLISIONMANAGER->pixelCollision(_vBullet[i].rc, x, y, _vBullet[i].speed, _vBullet[i].gravity, LEFT) ||
			COLLISIONMANAGER->pixelCollision(_vBullet[i].rc, x, y, _vBullet[i].speed, _vBullet[i].gravity, RIGHT) ||
			COLLISIONMANAGER->pixelCollision(_vBullet[i].rc, x, y, _vBullet[i].speed, _vBullet[i].gravity, LEFT) == BLUE ||
			COLLISIONMANAGER->pixelCollision(_vBullet[i].rc, x, y, _vBullet[i].speed, _vBullet[i].gravity, RIGHT) == BLUE)
		{
			EFFECTMANAGER->play("bulletPuff" + to_string(RND->getFromIntTo(1, 5)), _vBullet[i].rc.left, _vBullet[i].rc.top);
			_vBullet[i].x = _vBullet[i].fireX;
			_vBullet[i].y = _vBullet[i].fireY;
			_vBullet.erase(_vBullet.begin() + i);
		}
	}
}

void bullet::removeBullet(int index)
{
	_vBullet.erase(_vBullet.begin() + index);
}


//=============================================================
//	## triBullet ## (triBullet[0] -> 배열처럼 미리 장전해두고 총알발사)
//=============================================================
HRESULT triBullet::init(const char * imageName, int bulletMax, float range)
{
	//총알 이미지 초기화
	_imageName = imageName;
	//총알갯수 및 사거리 초기화
	_bulletMax = bulletMax;
	_range = range;

	//총알의 갯수만큼 구조체를 초기화 한 후 벡터에 담기
	for (int i = 0; i < bulletMax; i++)
	{
		//총알 구조체 선언
		tagBullet bullet;
		//제로메모리 또는 멤셋
		//구조체의 변수들의 값을 한번에 0으로 초기화 시켜준다
		ZeroMemory(&bullet, sizeof(tagBullet));
		bullet.bulletImage = IMAGEMANAGER->findImage(_imageName);
		bullet.fire = false;

		//벡터에 담기
		_vBullet.push_back(bullet);
	}

	return S_OK;
}

void triBullet::release(void)
{
}

void triBullet::update(void)
{
	this->move();
	this->collision();
}

void triBullet::render(void)
{
	_viMagazine = _vMagazine.begin();
	for (_viMagazine; _viMagazine != _vMagazine.end(); ++_viMagazine)
	{
		if (!CAMERAMANAGER->CameraIn(_viMagazine->rc)) continue;
		_viMagazine->bulletImage->alphaRender(getMemDC(), _viMagazine->rc.left - CAMERAMANAGER->getCamera().left, _viMagazine->rc.top - CAMERAMANAGER->getCamera().top, _viMagazine->alpha);
	}

	_viParticle = _vParticle.begin();
	for (_viParticle; _viParticle != _vParticle.end(); ++_viParticle)
	{
		if (!CAMERAMANAGER->CameraIn(_viParticle->rc)) continue;
		_viParticle->bulletImage->alphaRender(getMemDC(), _viParticle->rc.left - CAMERAMANAGER->getCamera().left, _viParticle->rc.top - CAMERAMANAGER->getCamera().top, _viParticle->alpha);
	}

	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->fire) continue;
		if (!CAMERAMANAGER->CameraIn(_viBullet->rc)) continue;
		_viBullet->bulletImage->render(getMemDC(), _viBullet->rc.left - CAMERAMANAGER->getCamera().left, _viBullet->rc.top - CAMERAMANAGER->getCamera().top);
	}
}

void triBullet::fire(float x, float y, float angle, float speed)
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_viBullet->fire) continue;

		_viBullet->fire = true;
		_viBullet->speed = speed;
		_viBullet->angle = angle;
		_viBullet->alpha = 255;
		_viBullet->count = 0;
		_viBullet->x = _viBullet->fireX = x;
		_viBullet->y = _viBullet->fireY = y;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getWidth(),
			_viBullet->bulletImage->getHeight());
	}

	int randNo = RND->getFromIntTo(10, 20);

	for (int i = 0; i < randNo; i++)
	{
		tagBullet particle;
		ZeroMemory(&particle, sizeof(tagBullet));
		particle.bulletImage = IMAGEMANAGER->findImage("dot_teal");
		particle.speed = speed;
		particle.angle = angle;
		particle.alpha = 255;
		particle.x = particle.fireX = x;
		particle.y = particle.fireY = y;
		particle.fire = false;
		particle.rc = RectMakeCenter(particle.x, particle.y,
			particle.bulletImage->getWidth(),
			particle.bulletImage->getHeight());

		//벡터에 담기
		_vParticle.push_back(particle);
	}


	for (int i = 0; i < randNo * 3; i++)
	{
		tagBullet particle;
		ZeroMemory(&particle, sizeof(tagBullet));
		particle.bulletImage = IMAGEMANAGER->findImage("dot_white");
		particle.speed = speed;
		particle.angle = angle;
		particle.alpha = 255;
		particle.x = particle.fireX = x;
		particle.y = particle.fireY = y;
		particle.fire = false;
		particle.rc = RectMakeCenter(particle.x, particle.y,
			particle.bulletImage->getWidth(),
			particle.bulletImage->getHeight());

		//벡터에 담기
		_vParticle.push_back(particle);
	}

	tagBullet magazine;
	ZeroMemory(&magazine, sizeof(tagBullet));
	magazine.bulletImage = IMAGEMANAGER->findImage("magazine");
	magazine.speed = RND->getFromFloatTo(8.0f, 12.0f);
	magazine.angle = RND->getFromIntTo(0, 1) ? PI / 3 : PI - PI / 3;
	magazine.alpha = 255;
	magazine.x = magazine.fireX = x;
	magazine.y = magazine.fireY = y;
	magazine.rc = RectMakeCenter(magazine.x, magazine.y,
		magazine.bulletImage->getWidth(),
		magazine.bulletImage->getHeight());

	//벡터에 담기
	_vMagazine.push_back(magazine);
}

void triBullet::move()
{
	RECT rcTemp;

	for (int i = 0; i < _vBullet.size(); ++i)
	{
		if (!_vBullet[i].fire) continue;
		_vBullet[i].count += (i + 1) * 2;
		if (_vBullet[i].count >= _vBullet.size() * _vBullet.size() * 2)
		{
			_vBullet[i].x += cosf(_vBullet[i].angle) * _vBullet[i].speed;
			_vBullet[i].y += -sinf(_vBullet[i].angle) * _vBullet[i].speed;
		}
		_vBullet[i].rc = RectMakeCenter(_vBullet[i].x, _vBullet[i].y,
			_vBullet[i].bulletImage->getWidth(),
			_vBullet[i].bulletImage->getHeight());

		//총알이 사거리보다 커졌을때 
		float distance = getDistance(_vBullet[i].fireX, _vBullet[i].fireY,
			_vBullet[i].x, _vBullet[i].y);
		if (_range < distance)
		{
			//EFFECTMANAGER->play("bulletPuff" + to_string(RND->getFromIntTo(1, 5)), _vBullet[i].rc.left, _vBullet[i].rc.top);
			_vBullet[i].x = _vBullet[i].fireX;
			_vBullet[i].y = _vBullet[i].fireY;
			_vBullet[i].fire = false;
		}
	}

	for (int i = 0; i < _vParticle.size(); i++)
	{
		if (_vParticle[i].fire)
		{
			_vParticle[i].count++;

			if (_vParticle[i].count > 20)
			{
				_vParticle[i].alpha -= 15;

				if (_vParticle[i].alpha <= 0)
					_vParticle.erase(_vParticle.begin() + i);
			}
		}
		else
		{
			_vParticle[i].x = _vParticle[i].fireX + cosf(_vParticle[i].angle) * RND->getFloat(_range) + RND->getFloat(10) - 5;
			_vParticle[i].y = _vParticle[i].fireY - sinf(_vParticle[i].angle) * RND->getFloat(_range) + RND->getFloat(10) - 5;

			_vParticle[i].rc = RectMakeCenter(_vParticle[i].x, _vParticle[i].y,
				_vParticle[i].bulletImage->getWidth(),
				_vParticle[i].bulletImage->getHeight());

			for (int j = 0; j < _vBullet.size(); j++)
			{
				if (IntersectRect(&rcTemp, &_vParticle[i].rc, &_vBullet[j].rc))
					_vParticle[i].fire = true;
			}
		}
	}

	for (int i = 0; i < _vMagazine.size(); ++i)
	{
		_vMagazine[i].count++;
		_vMagazine[i].gravity += 0.55f;
		_vMagazine[i].x += cosf(_vMagazine[i].angle) * _vMagazine[i].speed;
		_vMagazine[i].y += -sinf(_vMagazine[i].angle) * _vMagazine[i].speed + _vMagazine[i].gravity;
		_vMagazine[i].rc = RectMakeCenter(_vMagazine[i].x, _vMagazine[i].y,
			_vMagazine[i].bulletImage->getWidth(),
			_vMagazine[i].bulletImage->getHeight());

		//총알이 사거리보다 커졌을때 
		float distance = getDistance(_vMagazine[i].fireX, _vMagazine[i].fireY,
			_vMagazine[i].x, _vMagazine[i].y);
		if (_range < distance || _vMagazine[i].speed <= 1)
		{
			_vMagazine[i].alpha -= 15;

			if (_vMagazine[i].alpha <= 0)
				_vMagazine.erase(_vMagazine.begin() + i);
		}
	}
}

void triBullet::collision()
{
	for (int i = 0; i < _vMagazine.size(); i++)
	{
		if (!_vMagazine[i].fire) continue;

		float x = _vMagazine[i].x;
		float y = _vMagazine[i].y;

		if (COLLISIONMANAGER->pixelCollision(_vMagazine[i].rc, x, y, _vMagazine[i].speed, _vMagazine[i].gravity, BOTTOM))
		{
			_vMagazine[i].gravity = 0.0f;
			_vMagazine[i].speed *= 0.8;
			//_vMagazine[i].x = x;
			//_vMagazine[i].y = y;
		}
		else if (COLLISIONMANAGER->pixelCollision(_vMagazine[i].rc, x, y, _vMagazine[i].speed, _vMagazine[i].gravity, TOP))
		{
			_vMagazine[i].angle = PI_2 - _vMagazine[i].angle;
			_vMagazine[i].speed *= 0.8;
			//_vMagazine[i].x = x;
			//_vMagazine[i].y = y;
		}

		if (COLLISIONMANAGER->pixelCollision(_vMagazine[i].rc, x, y, _vMagazine[i].speed, _vMagazine[i].gravity, LEFT))
		{
			_vMagazine[i].angle = PI - _vMagazine[i].angle;
			_vMagazine[i].speed *= 0.8;
			//_vMagazine[i].x = x;
			//_vMagazine[i].y = y;
		}
		else if (COLLISIONMANAGER->pixelCollision(_vMagazine[i].rc, x, y, _vMagazine[i].speed, _vMagazine[i].gravity, RIGHT))
		{
			_vMagazine[i].angle = PI - _vMagazine[i].angle;
			_vMagazine[i].speed *= 0.8;
			//_vMagazine[i].x = x;
			//_vMagazine[i].y = y;
		}
	}

	for (int i = 0; i < _vBullet.size(); i++)
	{
		if (!_vBullet[i].fire) continue;

		float x = _vBullet[i].x;
		float y = _vBullet[i].y;

		//if (COLLISIONMANAGER->pixelCollision(_vBullet[i].rc, x, y, _vBullet[i].speed, _vBullet[i].gravity, BOTTOM) ||
		//	COLLISIONMANAGER->pixelCollision(_vBullet[i].rc, x, y, _vBullet[i].speed, _vBullet[i].gravity, TOP) ||
		if (COLLISIONMANAGER->pixelCollision(_vBullet[i].rc, x, y, _vBullet[i].speed, _vBullet[i].gravity, LEFT) ||
			COLLISIONMANAGER->pixelCollision(_vBullet[i].rc, x, y, _vBullet[i].speed, _vBullet[i].gravity, RIGHT) ||
			COLLISIONMANAGER->pixelCollision(_vBullet[i].rc, x, y, _vBullet[i].speed, _vBullet[i].gravity, LEFT) == BLUE ||
			COLLISIONMANAGER->pixelCollision(_vBullet[i].rc, x, y, _vBullet[i].speed, _vBullet[i].gravity, RIGHT) == BLUE)
		{
			EFFECTMANAGER->play("bulletPuff" + to_string(RND->getFromIntTo(1, 5)), _vBullet[i].rc.left, _vBullet[i].rc.top);
			_vBullet[i].x = _vBullet[i].fireX;
			_vBullet[i].y = _vBullet[i].fireY;
			_vBullet[i].fire = false;
		}
	}
}

//=============================================================
//	## arrow ## (공용총알 - 너희들이 만들면 된다)
//=============================================================
HRESULT arrow::init(const char * imageName, int arrowMax, float range)
{
	//총알 이미지 초기화
	_imageName = imageName;
	//총알갯수 및 사거리 초기화
	_arrowMax = arrowMax;
	_range = range;
	_gravity = 0;

	for (int i = 0; i < _arrowMax; i++)
	{
		tagBullet arrow;
		ZeroMemory(&arrow, sizeof(tagBullet));
		arrow.bulletImage = IMAGEMANAGER->findImage(_imageName);
		arrow.fire = false;

		//벡터에 담기
		_vArrow.push_back(arrow);
	}

	return S_OK;
}

void arrow::release(void)
{
}

void arrow::update(void)
{
	this->move();
	this->collision();
}

void arrow::render(void)
{
	_viParticle = _vParticle.begin();
	for (_viParticle; _viParticle != _vParticle.end(); ++_viParticle)
	{
		if (!CAMERAMANAGER->CameraIn(_viParticle->rc)) continue;
		_viParticle->bulletImage->alphaRender(getMemDC(), _viParticle->rc.left - CAMERAMANAGER->getCamera().left, _viParticle->rc.top - CAMERAMANAGER->getCamera().top, _viParticle->alpha);
	}

	_viArrow = _vArrow.begin();
	for (_viArrow; _viArrow != _vArrow.end(); ++_viArrow)
	{
		if (!_viArrow->fire) continue;
		if (!CAMERAMANAGER->CameraIn(_viArrow->rc)) continue;
		_viArrow->bulletImage->rotateRender(getMemDC(), _viArrow->rc.left - CAMERAMANAGER->getCamera().left, _viArrow->rc.top - CAMERAMANAGER->getCamera().top, _viArrow->angle);// , _viArrow->alpha);
	}
}

void arrow::fire(float x, float y, float angle, float speed)
{
	_viArrow = _vArrow.begin();
	for (_viArrow; _viArrow != _vArrow.end(); ++_viArrow)
	{
		if (_viArrow->fire) continue;

		_viArrow->fire = true;
		_viArrow->speed = speed;
		_viArrow->angle = angle;
		_viArrow->alpha = 255;
		_viArrow->count = 0;
		_viArrow->x = _viArrow->fireX = x;
		_viArrow->y = _viArrow->fireY = y;
		_viArrow->rc = RectMakeCenter(_viArrow->x, _viArrow->y,
			_viArrow->bulletImage->getWidth(),
			_viArrow->bulletImage->getHeight());
	}

	int randNo = RND->getFromIntTo(10, 20);

	for (int i = 0; i < randNo / 3; i++)
	{
		tagBullet particle;
		ZeroMemory(&particle, sizeof(tagBullet));
		particle.bulletImage = IMAGEMANAGER->findImage("dot_red");
		particle.speed = speed;
		particle.angle = angle;
		particle.alpha = 255;
		particle.x = particle.fireX = x;
		particle.y = particle.fireY = y;
		particle.fire = false;
		particle.rc = RectMakeCenter(particle.x, particle.y,
			particle.bulletImage->getWidth(),
			particle.bulletImage->getHeight());

		//벡터에 담기
		_vParticle.push_back(particle);
	}


	for (int i = 0; i < randNo; i++)
	{
		tagBullet particle;
		ZeroMemory(&particle, sizeof(tagBullet));
		particle.bulletImage = IMAGEMANAGER->findImage("dot_white");
		particle.speed = speed;
		particle.angle = angle;
		particle.alpha = 255;
		particle.x = particle.fireX = x;
		particle.y = particle.fireY = y;
		particle.fire = false;
		particle.rc = RectMakeCenter(particle.x, particle.y,
			particle.bulletImage->getWidth(),
			particle.bulletImage->getHeight());

		//벡터에 담기
		_vParticle.push_back(particle);
	}

	_gravity = 0;
}

void arrow::move()
{
	RECT rcTemp;

	_viArrow = _vArrow.begin();

	for (; _viArrow != _vArrow.end();)
	{
		if (!_viArrow->fire) continue;

		_viArrow->gravity += 0.25f;
		_viArrow->x += cosf(_viArrow->angle) * _viArrow->speed;
		_viArrow->y += -sinf(_viArrow->angle) * _viArrow->speed + _viArrow->gravity;
		_viArrow->rc = RectMakeCenter(_viArrow->x, _viArrow->y,
			_viArrow->bulletImage->getWidth(),
			_viArrow->bulletImage->getHeight());

		if (_viArrow->speed == 0)
		{
			_viArrow->count++;

			if (_viArrow->count > 50)
			{
				_viArrow->alpha -= 15;

				if (_viArrow->alpha <= 0)
				{
					_viArrow->fire = false;
					continue;
				}
			}
		}

		//총알이 사거리보다 커졌을때
		float distance = getDistance(_viArrow->fireX, _viArrow->fireY,
			_viArrow->x, _viArrow->y);
		if (_range < distance)
		{
			//EFFECTMANAGER->play("bulletPuff" + to_string(RND->getFromIntTo(1, 5)), _viArrow->rc.left, _viArrow->rc.top);
			_viArrow->fire = false;
			continue;
		}
		else
		{
			++_viArrow;
		}
	}

	for (int i = 0; i < _vParticle.size(); i++)
	{
		if (_vParticle[i].fire)
		{
			_vParticle[i].count++;

			if (_vParticle[i].count > 20)
			{
				_vParticle[i].alpha -= 15;

				if (_vParticle[i].alpha <= 0)
					_vParticle.erase(_vParticle.begin() + i);
			}
		}
		else
		{
			_vParticle[i].gravity = 0.25f;
			_vParticle[i].x = _vParticle[i].fireX + cosf(_vParticle[i].angle) * RND->getFloat(_range) + RND->getFloat(10) - 5;
			_vParticle[i].y = _vParticle[i].fireY - sinf(_vParticle[i].angle) * RND->getFloat(_range) + RND->getFloat(10) - 5;

			_vParticle[i].rc = RectMakeCenter(_vParticle[i].x, _vParticle[i].y,
				_vParticle[i].bulletImage->getWidth(),
				_vParticle[i].bulletImage->getHeight());

			for (int j = 0; j < _vArrow.size(); j++)
			{
				if (IntersectRect(&rcTemp, &_vParticle[i].rc, &_vArrow[j].rc))
				{
					_gravity += 0.25f;
					_vParticle[i].y += _gravity;
					_vParticle[i].fire = true;
				}
			}
		}
	}
}

void arrow::collision()
{
	for (int i = 0; i < _vArrow.size(); i++)
	{
		if (!_vArrow[i].fire) continue;

		float x = _vArrow[i].x;
		float y = _vArrow[i].y;

		if (COLLISIONMANAGER->pixelCollision(_vArrow[i].rc, x, y, _vArrow[i].speed, _vArrow[i].gravity, BOTTOM) ||
			COLLISIONMANAGER->pixelCollision(_vArrow[i].rc, x, y, _vArrow[i].speed, _vArrow[i].gravity, TOP) ||
			COLLISIONMANAGER->pixelCollision(_vArrow[i].rc, x, y, _vArrow[i].speed, _vArrow[i].gravity, LEFT) ||
			COLLISIONMANAGER->pixelCollision(_vArrow[i].rc, x, y, _vArrow[i].speed, _vArrow[i].gravity, RIGHT) ||
			COLLISIONMANAGER->pixelCollision(_vArrow[i].rc, x, y, _vArrow[i].speed, _vArrow[i].gravity, LEFT) == BLUE ||
			COLLISIONMANAGER->pixelCollision(_vArrow[i].rc, x, y, _vArrow[i].speed, _vArrow[i].gravity, RIGHT) == BLUE)
		{
			if (_vArrow[i].speed != 0)
				EFFECTMANAGER->play("bulletPuff" + to_string(RND->getFromIntTo(1, 5)), _vArrow[i].rc.left, _vArrow[i].rc.top);
			_vArrow[i].speed = 0;
			_vArrow[i].gravity = 0;
		}
	}
}

void arrow::removeArrow(int index)
{
	_vArrow.erase(_vArrow.begin() + index);
}


//=============================================================
//	## triArrow ## (triArrow[0] -> 배열처럼 미리 장전해두고 총알발사)
//=============================================================
HRESULT triArrow::init(const char * imageName, int arrowMax, float range)
{
	//총알 이미지 초기화
	_imageName = imageName;
	//총알갯수 및 사거리 초기화
	_arrowMax = arrowMax;
	_range = range;
	_gravity = 0;

	//총알의 갯수만큼 구조체를 초기화 한 후 벡터에 담기
	for (int i = 0; i < _arrowMax; i++)
	{
		//총알 구조체 선언
		tagBullet bullet;
		//제로메모리 또는 멤셋
		//구조체의 변수들의 값을 한번에 0으로 초기화 시켜준다
		ZeroMemory(&bullet, sizeof(tagBullet));
		bullet.bulletImage = IMAGEMANAGER->findImage(_imageName);
		bullet.fire = false;

		//벡터에 담기
		_vArrow.push_back(bullet);
	}

	return S_OK;
}

void triArrow::release(void)
{
}

void triArrow::update(void)
{
	this->move();
	this->collision();
}

void triArrow::render(void)
{
	_viParticle = _vParticle.begin();
	for (_viParticle; _viParticle != _vParticle.end(); ++_viParticle)
	{
		if (!CAMERAMANAGER->CameraIn(_viParticle->rc)) continue;
		_viParticle->bulletImage->alphaRender(getMemDC(), _viParticle->rc.left - CAMERAMANAGER->getCamera().left, _viParticle->rc.top - CAMERAMANAGER->getCamera().top, _viParticle->alpha);
	}

	_viArrow = _vArrow.begin();
	for (_viArrow; _viArrow != _vArrow.end(); ++_viArrow)
	{
		if (!_viArrow->fire) continue;
		if (!CAMERAMANAGER->CameraIn(_viArrow->rc)) continue;
		_viArrow->bulletImage->rotateAlphaRender(getMemDC(), _viArrow->rc.left - CAMERAMANAGER->getCamera().left, _viArrow->rc.top - CAMERAMANAGER->getCamera().top, _viArrow->angle, _viArrow->alpha);
	}
}

void triArrow::fire(float x, float y, float angle, float speed)
{
	_viArrow = _vArrow.begin();
	for (_viArrow; _viArrow != _vArrow.end(); ++_viArrow)
	{
		if (_viArrow->fire) continue;

		_viArrow->fire = true;
		_viArrow->speed = speed;
		_viArrow->angle = angle;
		_viArrow->alpha = 255;
		_viArrow->count = 0;
		_viArrow->fadeCount = 0;
		_viArrow->x = _viArrow->fireX = x;
		_viArrow->y = _viArrow->fireY = y;
		_viArrow->rc = RectMakeCenter(_viArrow->x, _viArrow->y,
			_viArrow->bulletImage->getWidth(),
			_viArrow->bulletImage->getHeight());
	}

	int randNo = RND->getFromIntTo(10, 20);

	for (int i = 0; i < randNo; i++)
	{
		tagBullet particle;
		ZeroMemory(&particle, sizeof(tagBullet));
		particle.bulletImage = IMAGEMANAGER->findImage("dot_red");
		particle.speed = speed;
		particle.angle = angle;
		particle.alpha = 255;
		particle.x = particle.fireX = x;
		particle.y = particle.fireY = y;
		particle.fire = false;
		particle.rc = RectMakeCenter(particle.x, particle.y,
			particle.bulletImage->getWidth(),
			particle.bulletImage->getHeight());

		//벡터에 담기
		_vParticle.push_back(particle);
	}


	for (int i = 0; i < randNo * 3; i++)
	{
		tagBullet particle;
		ZeroMemory(&particle, sizeof(tagBullet));
		particle.bulletImage = IMAGEMANAGER->findImage("dot_white");
		particle.speed = speed;
		particle.angle = angle;
		particle.alpha = 255;
		particle.x = particle.fireX = x;
		particle.y = particle.fireY = y;
		particle.fire = false;
		particle.rc = RectMakeCenter(particle.x, particle.y,
			particle.bulletImage->getWidth(),
			particle.bulletImage->getHeight());

		//벡터에 담기
		_vParticle.push_back(particle);
	}
}

void triArrow::move()
{
	RECT rcTemp;

	for (int i = 0; i < _vArrow.size(); ++i)
	{
		if (!_vArrow[i].fire) continue;
		_vArrow[i].count += (i + 1) * 2;
		if (_vArrow[i].count >= _vArrow.size() * _vArrow.size() * 2)
		{
			_vArrow[i].gravity += 0.25f;
			_vArrow[i].x += cosf(_vArrow[i].angle) * _vArrow[i].speed;
			_vArrow[i].y += -sinf(_vArrow[i].angle) * _vArrow[i].speed + _vArrow[i].gravity;
		}
		_vArrow[i].rc = RectMakeCenter(_vArrow[i].x, _vArrow[i].y,
			_vArrow[i].bulletImage->getWidth(),
			_vArrow[i].bulletImage->getHeight());

		if (_vArrow[i].speed == 0)
		{
			_vArrow[i].fadeCount++;

			if (_vArrow[i].fadeCount > 50)
			{
				_vArrow[i].alpha -= 15;

				if (_vArrow[i].alpha <= 0)
				{
					_vArrow[i].x = _vArrow[i].fireX;
					_vArrow[i].y = _vArrow[i].fireY;
					_vArrow[i].fire = false;
				}
			}
		}

		//총알이 사거리보다 커졌을때 
		float distance = getDistance(_vArrow[i].fireX, _vArrow[i].fireY,
			_vArrow[i].x, _vArrow[i].y);
		if (_range < distance)
		{
			//EFFECTMANAGER->play("bulletPuff" + to_string(RND->getFromIntTo(1, 5)), _vArrow[i].rc.left, _vArrow[i].rc.top);
			_vArrow[i].x = _vArrow[i].fireX;
			_vArrow[i].y = _vArrow[i].fireY;
			_vArrow[i].fire = false;
		}
	}

	for (int i = 0; i < _vParticle.size(); i++)
	{
		if (_vParticle[i].fire)
		{
			_vParticle[i].count++;

			if (_vParticle[i].count > 20)
			{
				_vParticle[i].alpha -= 15;

				if (_vParticle[i].alpha <= 0)
					_vParticle.erase(_vParticle.begin() + i);
			}
		}
		else
		{
			_vParticle[i].gravity = 0.25f * (i + 1);
			_vParticle[i].x = _vParticle[i].fireX + cosf(_vParticle[i].angle) * RND->getFloat(_range) + RND->getFloat(10) - 5;
			_vParticle[i].y = _vParticle[i].fireY - sinf(_vParticle[i].angle) * RND->getFloat(_range) + RND->getFloat(10) - 5 + _vParticle[i].gravity;

			_vParticle[i].rc = RectMakeCenter(_vParticle[i].x, _vParticle[i].y,
				_vParticle[i].bulletImage->getWidth(),
				_vParticle[i].bulletImage->getHeight());

			for (int j = 0; j < _vArrow.size(); j++)
			{
				if (IntersectRect(&rcTemp, &_vParticle[i].rc, &_vArrow[j].rc))
					_vParticle[i].fire = true;
			}
		}
	}
}

void triArrow::collision()
{
	for (int i = 0; i < _vArrow.size(); i++)
	{
		if (!_vArrow[i].fire) continue;

		float x = _vArrow[i].x;
		float y = _vArrow[i].y;

		if (COLLISIONMANAGER->pixelCollision(_vArrow[i].rc, x, y, _vArrow[i].speed, _vArrow[i].gravity, BOTTOM) ||
			COLLISIONMANAGER->pixelCollision(_vArrow[i].rc, x, y, _vArrow[i].speed, _vArrow[i].gravity, TOP) ||
			COLLISIONMANAGER->pixelCollision(_vArrow[i].rc, x, y, _vArrow[i].speed, _vArrow[i].gravity, LEFT) ||
			COLLISIONMANAGER->pixelCollision(_vArrow[i].rc, x, y, _vArrow[i].speed, _vArrow[i].gravity, RIGHT) ||
			COLLISIONMANAGER->pixelCollision(_vArrow[i].rc, x, y, _vArrow[i].speed, _vArrow[i].gravity, LEFT) == BLUE ||
			COLLISIONMANAGER->pixelCollision(_vArrow[i].rc, x, y, _vArrow[i].speed, _vArrow[i].gravity, RIGHT) == BLUE)
		{
			if (_vArrow[i].speed != 0)
				EFFECTMANAGER->play("bulletPuff" + to_string(RND->getFromIntTo(1, 5)), _vArrow[i].rc.left, _vArrow[i].rc.top);
			_vArrow[i].gravity = 0;
			_vArrow[i].speed = 0;
		}
	}
}


//=============================================================
//	## block ##
//=============================================================
HRESULT block::init(const char * imageName, const char * shadowName, float speed, bool isFrameImg)
{
	_imageName = imageName;
	_shadowName = shadowName;
	_speed = speed;
	_isFrameImg = isFrameImg;
	_frameSpeed = 5;

	return S_OK;
}

void block::release(void)
{
}

void block::update(void)
{
	this->collision();
	this->frameChange();
}

void block::render(void)
{
	for (int i = 0; i < _vBlock.size(); i++)
	{
		if (!CAMERAMANAGER->CameraIn(_vBlock[i].rc)) continue;
		if (_isFrameImg)
		{
			_vBlock[i].shadowImage->alphaFrameRender(getMemDC(), _vBlock[i].x - _vBlock[i].shadowImage->getFrameWidth() * 0.5f - CAMERAMANAGER->getCamera().left, _vBlock[i].y - _vBlock[i].shadowImage->getFrameHeight() * 0.5f - CAMERAMANAGER->getCamera().top, _vBlock[i].index, 0, 80);
			_vBlock[i].bulletImage->frameRender(getMemDC(), _vBlock[i].x - _vBlock[i].bulletImage->getFrameWidth() * 0.5f - CAMERAMANAGER->getCamera().left, _vBlock[i].y - _vBlock[i].bulletImage->getFrameHeight() * 0.5f - CAMERAMANAGER->getCamera().top, _vBlock[i].index, 0);
		}
		else
		{
			_vBlock[i].shadowImage->alphaRender(getMemDC(), _vBlock[i].x - _vBlock[i].shadowImage->getWidth() * 0.5f - CAMERAMANAGER->getCamera().left, _vBlock[i].y - _vBlock[i].shadowImage->getHeight() * 0.5f - CAMERAMANAGER->getCamera().top, 80);
			_vBlock[i].bulletImage->render(getMemDC(), _vBlock[i].x - _vBlock[i].bulletImage->getWidth() * 0.5f - CAMERAMANAGER->getCamera().left, _vBlock[i].y - _vBlock[i].bulletImage->getHeight() * 0.5f - CAMERAMANAGER->getCamera().top);
		}
	}
}

void block::build(float x, float y)
{
	//총알 구조체 선언
	tagBullet block;
	//제로메모리 또는 멤셋
	//구조체의 변수들의 값을 한번에 0으로 초기화 시켜준다
	ZeroMemory(&block, sizeof(tagBullet));
	block.bulletImage = IMAGEMANAGER->findImage(_imageName);
	block.shadowImage = IMAGEMANAGER->findImage(_shadowName);
	block.bulletImage->setFrameX(0);
	block.bulletImage->setFrameY(0);
	block.x = x; //CAMERAMANAGER->getCamera().left + 620;
	block.y = y;// CAMERAMANAGER->getCamera().top + 417 - 50;
	block.fire = false;
	if (_isFrameImg)
		block.rc = RectMakeCenter(block.x, block.y, block.bulletImage->getFrameWidth() * 0.75f, block.bulletImage->getFrameHeight() * 0.75f);
	else
		block.rc = RectMakeCenter(block.x, block.y, block.bulletImage->getWidth() * 0.75f, block.bulletImage->getHeight() * 0.75f);

	//벡터에 담기
	_vBlock.push_back(block);
}

void block::move(int dir)
{
	for (int i = 0; i < _vBlock.size(); i++)
	{
		if (_vBlock[i].fire) continue;

		if (dir == RIGHT)
			_vBlock[i].x += _speed;
		else if (dir == LEFT)
			_vBlock[i].x -= _speed;
		else if (dir == TOP)
			_vBlock[i].y -= _speed;
		else if (dir == BOTTOM)
			_vBlock[i].y += _speed;

		if (_isFrameImg)
			_vBlock[i].rc = RectMakeCenter(_vBlock[i].x, _vBlock[i].y, _vBlock[i].bulletImage->getFrameWidth() * 0.75f, _vBlock[i].bulletImage->getFrameHeight() * 0.75f);
		else
			_vBlock[i].rc = RectMakeCenter(_vBlock[i].x, _vBlock[i].y, _vBlock[i].bulletImage->getWidth() * 0.75f, _vBlock[i].bulletImage->getHeight() * 0.75f);

		break;
	}
}

void block::removeBlock(int index)
{
	_vBlock.erase(_vBlock.begin() + index);
}

void block::activate()
{
	for (int i = 0; i < _vBlock.size(); i++)
	{
		if (_vBlock[i].fire) continue;

		_vBlock[i].fire = true;

		break;
	}
}

void block::collision()
{
	RECT rcTemp;

	for (int i = 0; i < _vBlock.size(); i++)
	{
		if (!_vBlock[i].fire) continue;

		if (COLLISIONMANAGER->pixelCollision(_vBlock[i].rc, _vBlock[i].x, _vBlock[i].y, _vBlock[i].speed, _vBlock[i].gravity, BOTTOM) ||
			COLLISIONMANAGER->pixelCollision(_vBlock[i].rc, _vBlock[i].x, _vBlock[i].y, _vBlock[i].speed, _vBlock[i].gravity, BOTTOM) == BLUE)
		{
			_vBlock[i].gravity = 0.0f;
			_vBlock[i].y += (_vBlock[i].rc.bottom - _vBlock[i].rc.top) * 0.25f;
		}
		else
		{
			_vBlock[i].gravity += 0.55f;
			_vBlock[i].y += _vBlock[i].gravity;
		}

		float rcHeight = _vBlock[i].rc.bottom - _vBlock[i].rc.top;

		for (int j = 0; j < _vBlock.size(); j++)
		{
			if (!_vBlock[j].fire) continue;
			if (i == j) continue;

			if (IntersectRect(&rcTemp, &_vBlock[i].rc, &_vBlock[j].rc))
			{
				_vBlock[i].rc.top < _vBlock[j].rc.top ? _vBlock[i].y = _vBlock[j].rc.top - rcHeight * 0.5 + 1 : _vBlock[j].y = _vBlock[i].rc.top - rcHeight * 0.5f + 1;

				break;
			}
		}

		if (_isFrameImg)
			_vBlock[i].rc = RectMakeCenter(_vBlock[i].x, _vBlock[i].y, _vBlock[i].bulletImage->getFrameWidth() * 0.75f, _vBlock[i].bulletImage->getFrameHeight() * 0.75f);
		else
			_vBlock[i].rc = RectMakeCenter(_vBlock[i].x, _vBlock[i].y, _vBlock[i].bulletImage->getWidth() * 0.75f, _vBlock[i].bulletImage->getHeight() * 0.75f);
	}
}

void block::frameChange()
{
	if (_isFrameImg)
	{
		for (int i = 0; i < _vBlock.size(); i++)
		{
			if (!_vBlock[i].fire) continue;

			_vBlock[i].count++;
			if (_vBlock[i].count % _frameSpeed == 0)
			{
				_vBlock[i].index++;
				if (_vBlock[i].index > _vBlock[i].bulletImage->getMaxFrameX())
					_vBlock[i].index = 0;
				_vBlock[i].bulletImage->setFrameX(_vBlock[i].index);
			}
		}
	}
}