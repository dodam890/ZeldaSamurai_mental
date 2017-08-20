#include "stdafx.h"
#include "c_zeldaTileMap.h"
#include "player.h"

// ----------------------------------------------------------------------------------------------------

HRESULT zeldaTileMap1::init(player* player, camera * camera, const CHAR* pMapSaveFileName, int mapWidth, int mapHeight)
{
	zeldaTileMap::init(player, camera, pMapSaveFileName, mapWidth, mapHeight);

	//int j = 0;
	//int k = 0;

	//for (int i = 0; i < TILEX * TILEY; i++)
	//{
	//	if (_tiles[i].terrain == TR_ROCK)
	//	{
	//		_rockTile[j].image = IMAGEMANAGER->findImage("TILE_ROCK");
	//		_rockTile[j].rc = RectMake(_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].rc.right - _tiles[i].rc.left - 5, _tiles[i].rc.bottom - _tiles[i].rc.top - 5);

	//		j++;
	//	}
	//	else if (_tiles[i].obj2 == OBJ_POT)
	//	{
	//		_potTile[k].rc = _tiles[i].rc;

	//		k++;
	//	}
	//}

	_em = new enemyManager;
	_em->init(_player, _camera, this);


	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].obj == OBJ_OCTOPUS)
		{
			_em->setOcto(_tiles[i].rc.left, _tiles[i].rc.top);
		}
	}

	_emZorder = new emZorder;
	_emZorder->init(_em, _player);

	_door[UP].rc = RectMake(720, 150, 80, 30);
	_door[UP].nextMap = TILEMAP_TWO;
	_door[UP].x = 630;
	_door[UP].y = 1200;
	_door[UP].cameraX = 145;
	_door[UP].cameraY = 800;

	_door[DOWN].rc = RectMake(720, 1400, 80, 30);
	_door[DOWN].x = 1250;
	_door[DOWN].y = 790;
	_door[DOWN].cameraX = 790;
	_door[DOWN].cameraY = 510;

	return S_OK;
}

void zeldaTileMap1::release()
{
	zeldaTileMap::release();

	_em->release();
}

void zeldaTileMap1::update()
{
	zeldaTileMap::update();

	_door[UP].rc = RectMake(_camera->getStartX() + 720, _camera->getStartY() + 150, 80, 30);
	_door[DOWN].rc = RectMake(_camera->getStartX() + 720, _camera->getStartY() + 1400, 80, 30);

	//int j = 0;
	//int k = 0;

	//for (int i = 0; i < TILEX * TILEY; i++)
	//{
	//	if (_tiles[i].terrain == TR_ROCK)
	//	{
	//		_rockTile[j].rc = RectMake(_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].rc.right - _tiles[i].rc.left - 10, _tiles[i].rc.bottom - _tiles[i].rc.top - 10);
	//		//_rockTile[j].rc = RectMake(_rockTile[j].rc.left + _camera->getStartX(), _rockTile[j].rc.top + _camera->getStartY(), 70, 70);

	//		_rockTile[j].tileIndex = i;
	//		j++;
	//	}
	//	else if (_tiles[i].obj2 == OBJ_POT)
	//	{
	//		_potTile[k].rc = _tiles[i].rc;

	//		k++;
	//	}
	//}

	//RECT temp;

	//for (int i = 0; i < 3; i++)
	//{
	//	if (IntersectRect(&temp, &_rockTile[i].rc, &_player->getRect()))
	//	{
	//		//_tiles[_rockTile[i].tileIndex].terrain = TR_BASE;
	//		_tiles[_rockTile[i].tileIndex].terrainFrameX = 0;
	//		_tiles[_rockTile[i].tileIndex].terrainFrameY = 0;

	//		_player->setPush(true);

	//		for (int j = 0; j < TILEX * TILEY; j++)
	//		{
	//			if (IntersectRect(&temp, &_rockTile[i].rc, &_tiles[j].rc))
	//			{	
	//				if (_tiles[j].obj == OBJ_WALL)
	//				{
	//				//	if(_rockTile[i].rc.left <= 
	//					_rockTile[i].rc.left = _player->getRect().left - 80;
	//					_rockTile[i].rc.right = _player->getRect().right - 80;

	//				}
	//			}
	//		}

	//	}
	//}

	_emZorder->update();
	_em->update();

}

void zeldaTileMap1::render()
{
	zeldaTileMap::render();

	//for (int i = 0; i < 3; i++)
	//{
	//	_rockTile[i].image->render(getMemDC(), _rockTile[i].rc.left, _rockTile[i].rc.top);
	//}

	_emZorder->render();
}

// ----------------------------------------------------------------------------------------------------

HRESULT zeldaTileMap2::init(player* player, camera * camera, const CHAR* pMapSaveFileName, int mapWidth, int mapHeight)
{
	zeldaTileMap::init(player, camera, pMapSaveFileName, mapWidth, mapHeight);

	_em = new enemyManager;
	_em->init(_player, _camera, this);

	_emZorder = new emZorder;
	_emZorder->init(_em, _player);

	_door[UP].rc = RectMake(720, 150, 80, 30);
	_door[UP].nextMap = TILEMAP_THREE;
	_door[UP].x = 630;
	_door[UP].y = 1200;
	_door[UP].cameraX = 145;
	_door[UP].cameraY = 800;

	_door[DOWN].rc = RectMake(720, 1400, 80, 30);
	_door[DOWN].nextMap = TILEMAP_ONE;
	_door[DOWN].x = 625;
	_door[DOWN].y = 142;
	_door[DOWN].cameraX = 165;
	_door[DOWN].cameraY = 0;

	return S_OK;
}

void zeldaTileMap2::release()
{
	zeldaTileMap::release();

	_em->release();
}

void zeldaTileMap2::update()
{
	zeldaTileMap::update();

	_door[UP].rc = RectMake(_camera->getStartX() + 720, _camera->getStartY() + 150, 80, 30);
	_door[DOWN].rc = RectMake(_camera->getStartX() + 720, _camera->getStartY() + 1400, 80, 30);

	_emZorder->update();
	_em->update();

}

void zeldaTileMap2::render()
{
	zeldaTileMap::render();

	_emZorder->render();
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
