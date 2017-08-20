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

void enemyManager::setOcto(int num)
{
	enemy* enemyOcto;

	for (int i = 0; i < num; i++)
	{
		for (int j = 0; j < num; j++)
		{
			enemyOcto = new octo;
			enemyOcto->init(_player, _camera, _map, 3 + (13 * i), 7 + (9 * j));
			_vEm.push_back(enemyOcto);
		}
	}
}

void enemyManager::setSlime(int num)
{
	enemy* enemySlime;

	enemySlime = new slime;
	enemySlime->init(_player, _camera, _map, 5, 7);
	_vEm.push_back(enemySlime);
}

void enemyManager::setSnail(int num)
{
	enemy* enemySnail;
	enemySnail = new snail;
	enemySnail->init(_player, _camera, _map, 8, 7);
	_vEm.push_back(enemySnail);
}
