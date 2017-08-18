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
	enemyOcto->init(_camera, _map, 10, 10);
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
