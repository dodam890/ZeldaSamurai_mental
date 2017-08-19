#include "stdafx.h"
#include "c_zeldaTileMap.h"

// ----------------------------------------------------------------------------------------------------

HRESULT zeldaTileMap1::init(player* player, camera * camera, const CHAR* pMapSaveFileName, int mapWidth, int mapHeight)
{
	zeldaTileMap::init(player, camera, pMapSaveFileName, mapWidth, mapHeight);
	
	_em = new enemyManager;
	_em->init(_player, _camera, this);
	_em->setOcto();

	return S_OK;
}

void zeldaTileMap1::release()
{
	zeldaTileMap::release();
}

void zeldaTileMap1::update()
{
	zeldaTileMap::update();

	_em->update();
}

void zeldaTileMap1::render()
{
	zeldaTileMap::render();

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
