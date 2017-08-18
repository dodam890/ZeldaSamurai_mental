#include "stdafx.h"
#include "aStarScene.h"

aStarScene::aStarScene()
{
}

aStarScene::~aStarScene()
{
}

HRESULT aStarScene::init()
{
	_ca = new camera;
	_ca->init();

	_map = new zeldaTileMap;
	_map->init(_ca, 2000, 1000);

	/*_aStar = new aStar;
	_aStar->init(_ca);
	_aStar->setTile(_map, 1, 1, 15, 15);*/
	return S_OK;
}

void aStarScene::release()
{
	//_aStar->release();
}

void aStarScene::update()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _ca->isCameraXZeroSide())
	{
		_ca->setCameraX(_ca->getCameraX() - 10);
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _ca->isCameraXEndSide())
	{
		_ca->setCameraX(_ca->getCameraX() + 10);
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP) && _ca->isCameraYZeroSide())
	{
		_ca->setCameraY(_ca->getCameraY() - 10);
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _ca->isCameraYEndSide())
	{
		_ca->setCameraY(_ca->getCameraY() + 10);
	}

	_ca->update(5000, 5000);
	//_aStar->update();
}

void aStarScene::render()
{
	//_aStar->render();
	_ca->drawCameraPos();
}
