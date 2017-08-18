#include "stdafx.h"
#include "enemyManager.h"
#include "octo.h"
#include "slime.h"
#include "snail.h"
#include "camera.h"

enemyManager::enemyManager()
{
}


enemyManager::~enemyManager()
{
}

HRESULT enemyManager::init(camera* camera, zeldaTileMap* map)
{
	_camera = camera;
	_map = map;

	return S_OK;
}

void enemyManager::release()
{
}

void enemyManager::update()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _camera->isCameraXZeroSide())
	{

		_camera->setCameraX(_camera->getCameraX() - 10);
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _camera->isCameraXEndSide())
	{
		_camera->setCameraX(_camera->getCameraX() + 10);
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP) && _camera->isCameraYZeroSide())
	{
		_camera->setCameraY(_camera->getCameraY() - 10);
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _camera->isCameraYEndSide())
	{
		_camera->setCameraY(_camera->getCameraY() + 10);
	}

	_camera->update(5000, 5000);

	for (_viEm = _vEm.begin(); _viEm != _vEm.end(); ++_viEm)
	{
		(*_viEm)->update();
	}
}

void enemyManager::render()
{
	for (_viEm = _vEm.begin(); _viEm != _vEm.end(); ++_viEm)
	{
		(*_viEm)->render();
	}
}

void enemyManager::setOcto()
{
	enemy* enemyOcto;

	enemyOcto = new octo;
	enemyOcto->init(_camera, _map, 5, 5);
	_vEm.push_back(enemyOcto);
}

void enemyManager::setSlime()
{
	enemy* enemySlime;

	enemySlime = new slime;
//	enemySlime->init(_camera, 0, 0);
	_vEm.push_back(enemySlime);
}

void enemyManager::setSnail()
{
	enemy* enemySnail;
	enemySnail = new snail;
	//enemySnail->init(_camera, 0, 0);
	_vEm.push_back(enemySnail);
}
