#include "stdafx.h"
#include "RenderManager.h"
#include "backgroundElements.h"
#include "foregroundElements.h"

HRESULT renderManager::init()
{
	return S_OK;
}

void renderManager::release()
{
}

void renderManager::render(HDC hdc)
{
}

void renderManager::backgroundRender(HDC hdc)
{
	multimap<float, backgroundElements*>::iterator iter;
	float centerX = CAMERAMANAGER->getCamera().left + WINSIZEX / 2, centerY = CAMERAMANAGER->getCamera().top + WINSIZEY / 2;
	float x, y, z;
	float width, height;
	if (!backgroundList.empty())
	{
		for (iter = backgroundList.begin(); iter != backgroundList.end(); ++iter)
		{
			iter->second->update();
			width = iter->second->getImage()->getWidth();
			height = iter->second->getImage()->getHeight();
			z = iter->second->getZ();

			x = WINSIZEX / 2 + (iter->second->getX() - centerX) / (5 - z);
			y = WINSIZEY / 2 + (iter->second->getY() - centerY) / (5 - z);

			if (CAMERAMANAGER->CameraIn(iter->second->getRect()))
			{
				iter->second->render(x, y);
			}
		}
	}
}

void renderManager::foregroundRender(HDC hdc)
{
	multimap<float, backgroundElements*>::iterator iter;
	float centerX = CAMERAMANAGER->getCamera().left + WINSIZEX / 2, centerY = CAMERAMANAGER->getCamera().top + WINSIZEY / 2;
	float x, y, z;
	float width, height;
	if (!backgroundList.empty())
	{
		for (iter = backgroundList.begin(); iter != backgroundList.end(); ++iter)
		{
			iter->second->update();
			width = iter->second->getImage()->getWidth();
			height = iter->second->getImage()->getHeight();
			z = iter->second->getZ();

			x = WINSIZEX / 2 + (iter->second->getX() - centerX) * (5 - z);
			y = WINSIZEY / 2 + (iter->second->getY() - centerY) * (5 - z);

			if (CAMERAMANAGER->CameraIn(iter->second->getRect()))
			{
				iter->second->render(x, y);
			}
		}
	}
}

void renderManager::addBackground(float z, backgroundElements * backElements)
{
	backgroundList.insert(make_pair(z, backElements));
}

void renderManager::addForeground(float z, foregroundElements * foreElements)
{
	foregroundList.insert(make_pair(z, foreElements));
}

void renderManager::clearBackground()
{
	multimap<float, backgroundElements *>::iterator iter;
	if (!backgroundList.empty())
	{
		for (iter = backgroundList.begin(); iter != backgroundList.end(); ++iter)
		{
			SAFE_DELETE(iter->second);
		}
	}

	backgroundList.clear();
}

void renderManager::clearForeground()
{
	multimap<float, foregroundElements *>::iterator iter;
	if (!foregroundList.empty())
	{
		for (iter = foregroundList.begin(); iter != foregroundList.end(); ++iter)
		{
			SAFE_DELETE(iter->second);
		}
	}

	foregroundList.clear();
}
