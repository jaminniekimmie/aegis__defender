#include "stdafx.h"
#include "frameManager.h"


HRESULT frameManager::init()
{
	return S_OK;
}

void frameManager::release()
{
}

void frameManager::frameChange(image* img, int& count, int& index, int &speed, bool isLeft)
{
	count++;

	img->setFrameY(isLeft);
	
	if (isLeft) // 1
	{
		if (count % speed == 0)
		{
			img->setFrameX(index);
			index--;

			if (index < 0)
			{
				index = img->getMaxFrameX();
			}
		}
	}
	else
	{
		if (count % speed == 0)
		{
			img->setFrameX(index);
			index++;

			if (index > img->getMaxFrameX())
			{
				index = 0;
			}
		}
	}
}
