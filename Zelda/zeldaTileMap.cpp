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

HRESULT zeldaTileMap::init(camera* camera, int mapWidth, int mapHeight)
{
	_camera = camera;
	_mapWidth = mapWidth;
	_mapHeight = mapHeight;

	IMAGEMANAGER->addFrameImage("mapTiles", "image/sample_ter.bmp", 0, 0, 180, 120, SAMPLETILEX, SAMPLETILEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mapTiles2", "image/sample_obj_30_1.bmp", 0, 0, 420, 300, SAMPLETILEX2, SAMPLETILEY2, true, RGB(255, 0, 255));


	loadMap();
	return S_OK;
}

void zeldaTileMap::release()
{
}

void zeldaTileMap::update()
{
	controlCamera();
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

		IMAGEMANAGER->frameRender("mapTiles", getMemDC(),
			_tiles[i].rc.left, _tiles[i].rc.top,
			_tiles[i].terrainFrameX, _tiles[i].terrainFrameY);

		IMAGEMANAGER->frameRender("mapTiles2", getMemDC(),
			_tiles[i].rc.left, _tiles[i].rc.top,
			_tiles[i].objFrameX, _tiles[i].objFrameY);

		IMAGEMANAGER->frameRender("mapTiles3", getMemDC(),
			_tiles[i].rc.left, _tiles[i].rc.top,
			_tiles[i].objFrameX, _tiles[i].objFrameY);
	}
}

void zeldaTileMap::loadMap()
{
	HANDLE file;
	DWORD read;

	file = CreateFile("mapSave01.map", GENERIC_READ, 0, NULL,
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
		if (_tiles[i].obj == OBJ_WALL)
		{
			_attribute[E_ATR_MOVE][i] = FALSE;
		}

		if (_tiles[i].terrain == TR_DESERT)
		{
			_attribute[E_ATR_SLOW][i] = FALSE;
		}
	}
	CloseHandle(file);
}

void zeldaTileMap::controlCamera()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _camera->isCameraXZeroSide())
	{
		_camera->setCameraX(_camera->getCameraX() - 20);
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _camera->isCameraXEndSide())
	{
		_camera->setCameraX(_camera->getCameraX() + 20);
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP) && _camera->isCameraYZeroSide())
	{
		_camera->setCameraY(_camera->getCameraY() - 20);
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _camera->isCameraYEndSide())
	{
		_camera->setCameraY(_camera->getCameraY() + 20);
	}

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		_tiles[i].posCenter.x = _camera->getStartX() + _tiles[i].disX;
		_tiles[i].posCenter.y = _camera->getStartY() + _tiles[i].disY;
		_tiles[i].rc = RectMakeCenter(_tiles[i].posCenter.x, _tiles[i].posCenter.y, TILESIZE, TILESIZE);
	}
}