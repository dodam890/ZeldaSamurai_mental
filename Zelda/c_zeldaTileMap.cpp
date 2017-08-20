#include "stdafx.h"
#include "c_zeldaTileMap.h"
#include "player.h"

// ----------------------------------------------------------------------------------------------------

HRESULT zeldaTileMap1::init(player* player, camera * camera, const CHAR* pMapSaveFileName, int mapWidth, int mapHeight)
{
	zeldaTileMap::init(player, camera, pMapSaveFileName, mapWidth, mapHeight);

	_em = new enemyManager;
	_em->init(_player, _camera, this);
	//_em->setOcto();

	int j = 0;
	int k = 0;

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].terrain == TR_ROCK)
		{
			_rockTile[j].image = IMAGEMANAGER->findImage("TILE_ROCK");
			_rockTile[j].rc = _tiles[i].rc;

			j++;
		}
		else if (_tiles[i].obj2 == OBJ_POT)
		{
			_potTile[k].rc = _tiles[i].rc;

			k++;
		}
	}

	return S_OK;
}

void zeldaTileMap1::release()
{
	zeldaTileMap::release();
}

void zeldaTileMap1::update()
{
	zeldaTileMap::update();

	int j = 0;
	int k = 0;

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].terrain == TR_ROCK)
		{
			_rockTile[j].image = IMAGEMANAGER->findImage("TILE_ROCK");
			_rockTile[j].rc = _tiles[i].rc;

			j++;
		}
		else if (_tiles[i].obj2 == OBJ_POT)
		{
			_potTile[k].rc = _tiles[i].rc;

			k++;
		}
	}

	RECT temp;

	for (int i = 0; i < 3; i++)
	{
		if (IntersectRect(&temp, &_rockTile[i].rc, &_player->getRect()))
		{

		}
	}

	//_em->update();
}

void zeldaTileMap1::render()
{
	zeldaTileMap::render();

	for (int i = 0; i < 3; i++)
	{
		_rockTile[i].image->render(getMemDC(), _rockTile[i].rc.left, _rockTile[i].rc.top);

		//Rectangle(getMemDC(), _potTile[i].rc.left + _camera->getStartX(), _potTile[i].rc.top + _camera->getStartY(), _potTile[i].rc.right + _camera->getStartX(), _potTile[i].rc.bottom + _camera->getStartY());
	}


	//_em->render();
}

// ----------------------------------------------------------------------------------------------------

HRESULT zeldaTileMap2::init(player* player, camera * camera, const CHAR* pMapSaveFileName, int mapWidth, int mapHeight)
{
	zeldaTileMap::init(player, camera, pMapSaveFileName, mapWidth, mapHeight);
	return S_OK;
}

void zeldaTileMap2::release()
{
	zeldaTileMap::release();
}

void zeldaTileMap2::update()
{
	zeldaTileMap::update();
}

void zeldaTileMap2::render()
{
	zeldaTileMap::render();
}

// ----------------------------------------------------------------------------------------------------

HRESULT zeldaTileMap3::init(player* player, camera * camera, const CHAR* pMapSaveFileName, int mapWidth, int mapHeight)
{
	zeldaTileMap::init(player, camera, pMapSaveFileName, mapWidth, mapHeight);
	return S_OK;
}

void zeldaTileMap3::release()
{
	zeldaTileMap::release();
}

void zeldaTileMap3::update()
{
	zeldaTileMap::update();
}

void zeldaTileMap3::render()
{
	zeldaTileMap::render();
}

// ----------------------------------------------------------------------------------------------------

HRESULT zeldaTileMap4::init(player* player, camera * camera, const CHAR* pMapSaveFileName, int mapWidth, int mapHeight)
{
	zeldaTileMap::init(player, camera, pMapSaveFileName, mapWidth, mapHeight);
	return S_OK;
}

void zeldaTileMap4::release()
{
	zeldaTileMap::release();
}

void zeldaTileMap4::update()
{
	zeldaTileMap::update();
}

void zeldaTileMap4::render()
{
	zeldaTileMap::render();
}

// ----------------------------------------------------------------------------------------------------

HRESULT zeldaTileMap5::init(player* player, camera * camera, const CHAR* pMapSaveFileName, int mapWidth, int mapHeight)
{
	zeldaTileMap::init(player, camera, pMapSaveFileName, mapWidth, mapHeight);
	return S_OK;
}

void zeldaTileMap5::release()
{
	zeldaTileMap::release();
}

void zeldaTileMap5::update()
{
	zeldaTileMap::update();
}

void zeldaTileMap5::render()
{
	zeldaTileMap::render();
}

// ----------------------------------------------------------------------------------------------------
