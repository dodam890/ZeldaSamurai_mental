#include "stdafx.h"
#include "c_zeldaTileMap.h"

// ----------------------------------------------------------------------------------------------------

HRESULT zeldaTileMap1::init(player* player, camera * camera, const CHAR* pMapSaveFileName, int mapWidth, int mapHeight)
{
	zeldaTileMap::init(player, camera, pMapSaveFileName, mapWidth, mapHeight);
	
	_em = new enemyManager;
	//_em->init(_player, _camera, );

	return S_OK;
}

void zeldaTileMap1::release()
{
}

void zeldaTileMap1::update()
{
}

void zeldaTileMap1::render()
{
}

void zeldaTileMap1::loadMap()
{
}

// ----------------------------------------------------------------------------------------------------

HRESULT zeldaTileMap2::init(player* player, camera * camera, const CHAR* pMapSaveFileName, int mapWidth, int mapHeight)
{
	zeldaTileMap::init(player, camera, pMapSaveFileName, mapWidth, mapHeight);
	return S_OK;
}

void zeldaTileMap2::release()
{
}

void zeldaTileMap2::update()
{
}

void zeldaTileMap2::render()
{
}

void zeldaTileMap2::loadMap()
{
}

// ----------------------------------------------------------------------------------------------------

HRESULT zeldaTileMap3::init(player* player, camera * camera, const CHAR* pMapSaveFileName, int mapWidth, int mapHeight)
{
	zeldaTileMap::init(player, camera, pMapSaveFileName, mapWidth, mapHeight);
	return S_OK;
}

void zeldaTileMap3::release()
{
}

void zeldaTileMap3::update()
{
}

void zeldaTileMap3::render()
{
}

void zeldaTileMap3::loadMap()
{
}

// ----------------------------------------------------------------------------------------------------
