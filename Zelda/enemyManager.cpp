#include "stdafx.h"
#include "enemyManager.h"
#include "octo.h"
#include "slime.h"
#include "snail.h"
#include "camera.h"
#include "player.h"

enemyManager::enemyManager()
{
}


enemyManager::~enemyManager()
{
}

HRESULT enemyManager::init(player* player, camera* camera, zeldaTileMap* map)
{
	_camera = camera;
	_map = map;
	_player = player;

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

void enemyManager::setOcto(float distanceX, float distanceY)
{
	enemy* enemyOcto;

	enemyOcto = new octo;
	enemyOcto->init(_player, _camera, _map, distanceX / TILESIZE, distanceY / TILESIZE);
	_vEm.push_back(enemyOcto);
}

void enemyManager::setSlime(float distanceX, float distanceY)
{
	enemy* enemySlime;

	enemySlime = new slime;
	enemySlime->init(_player, _camera, _map, distanceX / TILESIZE, distanceY / TILESIZE);
	_vEm.push_back(enemySlime);
}

void enemyManager::setSnail(float distanceX, float distanceY)
{
	enemy* enemySnail;
	enemySnail = new snail;
	enemySnail->init(_player, _camera, _map, distanceX / TILESIZE, distanceY / TILESIZE);
	_vEm.push_back(enemySnail);
}
