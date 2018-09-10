#pragma once
#include "singletonBase.h"

class image;

class collisionManager : public singletonBase<collisionManager>
{
	image* _pixelTiles;

public:
	HRESULT init();
	void release();
	
	int pixelCollision(RECT rc, float& x, float& y, float speed, float gravity, int dir);

	void setPixelMap(image* pixelTiles)
	{
		_pixelTiles = pixelTiles;
	}
	
	collisionManager() {}
	~collisionManager() {}
};