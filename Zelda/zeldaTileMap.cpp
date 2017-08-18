#include "stdafx.h"
#include "zeldaTileMap.h"

zeldaTileMap::zeldaTileMap() :
	_tiles(),
	_attribute()
{
}


zeldaTileMap::~zeldaTileMap()
{
}

HRESULT zeldaTileMap::init(camera* camera, const CHAR* pSaveMapFileName, int mapWidth, int mapHeight)
{
	_camera = camera;
	_mapWidth = mapWidth;
	_mapHeight = mapHeight;

	IMAGEMANAGER->addFrameImage("mapTiles_ter", "image/sample80_ter.bmp", 0, 0, 480, 320, SAMPLETILEX, SAMPLETILEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mapTiles_obj_1", "image/sample_obj_80_1.bmp", 0, 0, 1120, 800, SAMPLETILEX2, SAMPLETILEY2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mapTiles_obj_2", "image/sample_obj_80_2.bmp", 0, 0, 1200, 880, SAMPLETILEX3, SAMPLETILEY3, true, RGB(255, 0, 255));

<<<<<<< HEAD
	loadMap(pSaveMapFileName);

=======
	loadMap();
>>>>>>> db2adc7fdf40581292384cf1cd049df19defbce3
	return S_OK;
}

void zeldaTileMap::release()
{
}

void zeldaTileMap::update()
{
<<<<<<< HEAD
=======
	//controlCamera();
>>>>>>> db2adc7fdf40581292384cf1cd049df19defbce3
}

void zeldaTileMap::render()
{
	//IMAGEMANAGER->render("mapTiles", getMemDC(), WINSIZEX - IMAGEMANAGER->findImage("mapTiles")->getWidth(), 0);

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].rc.left >= WINSIZEX ||
			_tiles[i].rc.right <= 0 ||
			_tiles[i].rc.bottom <= 0 ||
			_tiles[i].rc.top >= WINSIZEY)
		{
			continue;
		}
		if (_tiles[i].tileKind == KIND_TERRAIN)
		{
			IMAGEMANAGER->frameRender("mapTiles_ter", getMemDC(),
				_tiles[i].rc.left, _tiles[i].rc.top,
				_tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
		}
		if (_tiles[i].tileKind == KIND_OBJ1)
		{
			IMAGEMANAGER->frameRender("mapTiles_obj_1", getMemDC(),
				_tiles[i].rc.left, _tiles[i].rc.top,
				_tiles[i].objFrameX, _tiles[i].objFrameY);
		}
		if (_tiles[i].tileKind == KIND_OBJ2)
		{
			IMAGEMANAGER->frameRender("mapTiles_obj_2", getMemDC(),
				_tiles[i].rc.left, _tiles[i].rc.top,
				_tiles[i].objFrameX, _tiles[i].objFrameY);
		}
	}
}

void zeldaTileMap::loadMap(const CHAR* pSaveMapFileName)
{
	HANDLE file;
	DWORD read;

<<<<<<< HEAD
	file = CreateFile(pSaveMapFileName, GENERIC_READ, 0, NULL,
=======
	file = CreateFile("mapSave00.map", GENERIC_READ, 0, NULL,
>>>>>>> db2adc7fdf40581292384cf1cd049df19defbce3
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);
	memset(_attribute, 0, sizeof(BOOL) * TILEX * TILEY);



	for (int i = 0; i < E_ATR_END; i++)
	{
		for (int j = 0; j < TILETOTAL; j++)
		{
			_attribute[i][j] = TRUE;
		}
	}

	for (int i = 0; i < TILETOTAL; i++)
	{
		if (_tiles[i].terrain == TR_DESERT)
		{
			_attribute[E_ATR_SLOW][i] = FALSE;
		}
		
		if (_tiles[i].obj == OBJ_WALL)
		{
			_attribute[E_ATR_MOVE][i] = FALSE;
		}

		if (_tiles[i].obj2 == OBJ_COLUMN1)
		{
			_attribute[E_ATR_SLIDE][i] = FALSE;
		}
	}

	CloseHandle(file);
}