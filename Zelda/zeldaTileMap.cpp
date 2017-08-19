#include "stdafx.h"
#include "zeldaTileMap.h"
#include "player.h"

zeldaTileMap::zeldaTileMap() :
	_tiles(),
	_attribute()
{
}


zeldaTileMap::~zeldaTileMap()
{
}

HRESULT zeldaTileMap::init(player* player, camera* camera, const CHAR* pSaveMapFileName, int mapWidth, int mapHeight)
{
	_player = player;
	_camera = camera;
	_mapWidth = mapWidth;
	_mapHeight = mapHeight;

	IMAGEMANAGER->addFrameImage("mapTiles_ter", "image/sample80_ter.bmp", 0, 0, 480, 320, SAMPLETILEX, SAMPLETILEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mapTiles_obj_1", "image/sample_obj_80_1.bmp", 0, 0, 1120, 800, SAMPLETILEX2, SAMPLETILEY2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mapTiles_obj_2", "image/sample_obj_80_2.bmp", 0, 0, 1200, 880, SAMPLETILEX3, SAMPLETILEY3, true, RGB(255, 0, 255));

	loadMap(pSaveMapFileName);

	return S_OK;
}

void zeldaTileMap::release()
{
}

void zeldaTileMap::update()
{

	_player->update();
	cameraSetTile();
	_camera->update(_mapWidth, _mapHeight);

	//controlCamera();
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

		IMAGEMANAGER->frameRender("mapTiles_ter", getMemDC(),
			_tiles[i].rc.left, _tiles[i].rc.top,
			_tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
	}

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].rc.left >= WINSIZEX ||
			_tiles[i].rc.right <= 0 ||
			_tiles[i].rc.bottom <= 0 ||
			_tiles[i].rc.top >= WINSIZEY)
		{
			continue;
		}

		if (_tiles[i].obj == OBJ_NONE) continue;
		IMAGEMANAGER->frameRender("mapTiles_obj_1", getMemDC(),
			_tiles[i].rc.left, _tiles[i].rc.top,
			_tiles[i].objFrameX, _tiles[i].objFrameY);
	}

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].rc.left >= WINSIZEX ||
			_tiles[i].rc.right <= 0 ||
			_tiles[i].rc.bottom <= 0 ||
			_tiles[i].rc.top >= WINSIZEY)
		{
			continue;
		}

		if (_tiles[i].obj2 == OBJ_NONE) continue;
		IMAGEMANAGER->frameRender("mapTiles_obj_2", getMemDC(),
			_tiles[i].rc.left, _tiles[i].rc.top,
			_tiles[i].objFrameX, _tiles[i].objFrameY);
	}

	for (int i = 0; i < TILETOTAL; i++)
	{
		char str[128];
		sprintf(str, "%d , %d", _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
		TextOut(getMemDC(), _tiles[i].rc.left + 10, _tiles[i].rc.top + 20, str, strlen(str));
		sprintf(str, "%d , %d", _tiles[i].objFrameX, _tiles[i].objFrameY);
		TextOut(getMemDC(), _tiles[i].rc.left + 10, _tiles[i].rc.top + 30, str, strlen(str));

		if (_tiles[i].rc.left >= WINSIZEX - WINSIZEX / 3 + 50) continue;
		switch (_tiles[i].terrain)
		{
		case TR_BASE:
			TextOut(getMemDC(), _tiles[i].rc.left + 10, _tiles[i].rc.top + 10, "기본", strlen("기본"));
	

			break;
		case TR_GRASS:
			TextOut(getMemDC(), _tiles[i].rc.left + 10, _tiles[i].rc.top + 10, "잔디", strlen("잔디"));

			break;
		case TR_DESERT:
			TextOut(getMemDC(), _tiles[i].rc.left + 10, _tiles[i].rc.top + 10, "모래", strlen("모래"));

			break;
		case TR_WATER:
			TextOut(getMemDC(), _tiles[i].rc.left + 10, _tiles[i].rc.top + 10, "물", strlen("물"));
		
			break;

		}
		switch (_tiles[i].obj)
		{
		case OBJ_WALL:
			TextOut(getMemDC(), _tiles[i].rc.left + 10, _tiles[i].rc.top + 40, "벽", strlen("벽"));
			break;

		default:
			TextOut(getMemDC(), _tiles[i].rc.left + 10, _tiles[i].rc.top + 40, "?", strlen("?"));
			break;

		}

		switch (_tiles[i].obj2)
		{
		case OBJ_WALL:

			TextOut(getMemDC(), _tiles[i].rc.left + 10, _tiles[i].rc.top + 70, "벽", strlen("벽"));

			break;
		case OBJ_BUTTON1_UP:

			TextOut(getMemDC(), _tiles[i].rc.left + 10, _tiles[i].rc.top + 70, "버튼1업", strlen("버튼1업"));

			break;
		case OBJ_BUTTON1_DOWN:

			TextOut(getMemDC(), _tiles[i].rc.left + 10, _tiles[i].rc.top + 70, "버튼1밑", strlen("버튼1밑"));

			break;
		case OBJ_BUTTON2_UP:

			TextOut(getMemDC(), _tiles[i].rc.left + 10, _tiles[i].rc.top + 70, "버튼2업", strlen("버튼1밑"));

			break;
		case OBJ_BUTTON2_DOWN:

			TextOut(getMemDC(), _tiles[i].rc.left + 10, _tiles[i].rc.top + 70, "버튼2밑", strlen("버튼1밑"));

			break;
		case OBJ_BRIDGE1:

			TextOut(getMemDC(), _tiles[i].rc.left + 10, _tiles[i].rc.top + 70, "다리1", strlen("다리1"));

			break;
		case OBJ_BRIDGE2:

			TextOut(getMemDC(), _tiles[i].rc.left + 10, _tiles[i].rc.top + 70, "다리2", strlen("다리2"));

			break;
		case OBJ_FIRE1:

			TextOut(getMemDC(), _tiles[i].rc.left + 10, _tiles[i].rc.top + 70, "불1", strlen("불1"));

			break;
		case OBJ_FIRE2:

			TextOut(getMemDC(), _tiles[i].rc.left + 10, _tiles[i].rc.top + 70, "불2", strlen("불1"));

			break;
		case OBJ_COLUMN1:

			TextOut(getMemDC(), _tiles[i].rc.left + 10, _tiles[i].rc.top + 70, "기둥1", strlen("불아1"));

			break;
		case OBJ_COLUMN2:

			TextOut(getMemDC(), _tiles[i].rc.left + 10, _tiles[i].rc.top + 70, "기둥2", strlen("불아1"));

			break;
		case OBJ_BOX1:

			TextOut(getMemDC(), _tiles[i].rc.left + 10, _tiles[i].rc.top + 70, "박스1", strlen("불아1"));

			break;
		case OBJ_BOX2:

			TextOut(getMemDC(), _tiles[i].rc.left + 10, _tiles[i].rc.top + 70, "박스2", strlen("불아1"));

			break;
		case OBJ_POT:

			TextOut(getMemDC(), _tiles[i].rc.left + 10, _tiles[i].rc.top + 70, "항아리", strlen("항아리"));

			break;

		case OBJ_SMALL_BOX1:

			TextOut(getMemDC(), _tiles[i].rc.left + 10, _tiles[i].rc.top + 70, "작은박1", strlen("항아리1"));

			break;

		case OBJ_SMALL_BOX2:

			TextOut(getMemDC(), _tiles[i].rc.left + 10, _tiles[i].rc.top + 70, "작은박2", strlen("항아리1"));

			break;

		case OBJ_DOOR_UP_CLOSE:

			TextOut(getMemDC(), _tiles[i].rc.left + 10, _tiles[i].rc.top + 70, "문위닫힘", strlen("항아리1"));

			break;

		case OBJ_DOOR_UP_OPEN:

			TextOut(getMemDC(), _tiles[i].rc.left + 10, _tiles[i].rc.top + 70, "문위열림", strlen("항아리1"));

			break;

		case OBJ_DOOR_DOWN_CLOSE:

			TextOut(getMemDC(), _tiles[i].rc.left + 10, _tiles[i].rc.top + 70, "문밑닫힘", strlen("항아리1"));

			break;

		case OBJ_DOOR_DOWN_OPEN:

			TextOut(getMemDC(), _tiles[i].rc.left + 10, _tiles[i].rc.top + 70, "문밑열림", strlen("항아리1"));

			break;

		case OBJ_DOOR2_UP_CLOSE:

			TextOut(getMemDC(), _tiles[i].rc.left + 10, _tiles[i].rc.top + 70, "문2위닫", strlen("항아리1"));

			break;

		case OBJ_DOOR2_UP_OPEN:

			TextOut(getMemDC(), _tiles[i].rc.left + 10, _tiles[i].rc.top + 70, "문2위열", strlen("항아리1"));

			break;

		case OBJ_DOOR2_DOWN_CLOSE:

			TextOut(getMemDC(), _tiles[i].rc.left + 10, _tiles[i].rc.top + 70, "문2밑닫", strlen("항아리1"));

			break;

		case OBJ_DOOR2_DOWN_OPEN:

			TextOut(getMemDC(), _tiles[i].rc.left + 10, _tiles[i].rc.top + 70, "문2밑열", strlen("항아리1"));

			break;

		default:

			TextOut(getMemDC(), _tiles[i].rc.left + 10, _tiles[i].rc.top + 70, "?", strlen("?"));

			break;
		}
	}
	_player->render();
}

void zeldaTileMap::loadMap(const CHAR* pSaveMapFileName)
{
	HANDLE file;
	DWORD read;

	file = CreateFile(pSaveMapFileName, GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);

	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			_tiles[i * TILEX + j].disX = TILESIZE / 2 + j * TILESIZE + 81;
			_tiles[i * TILEX + j].disY = TILESIZE / 2 + i * TILESIZE + 132;

			_tiles[i * TILEX + j].posCenter.x = _camera->getStartX() + _tiles[i * TILEX + j].disX;
			_tiles[i * TILEX + j].posCenter.y = _camera->getStartY() + _tiles[i * TILEX + j].disY;

			_tiles[i * TILEX + j].rc = RectMakeCenter(_tiles[i * TILEX + j].posCenter.x, _tiles[i * TILEX + j].posCenter.y, TILESIZE, TILESIZE);
		}
	}
	for (int i = 0; i < TILETOTAL; i++)
	{
		_tiles[i].disX -= 80;
		_tiles[i].disY -= 130;
		_tiles[i].posCenter.x = _camera->getStartX() + _tiles[i].disX;
		_tiles[i].posCenter.y = _camera->getStartY() + _tiles[i].disY;
		_tiles[i].rc = RectMakeCenter(_tiles[i].posCenter.x, _tiles[i].posCenter.y, TILESIZE, TILESIZE);
	}


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

void zeldaTileMap::cameraSetTile()
{
	for (int i = 0; i < TILETOTAL; i++)
	{
		_tiles[i].posCenter.x = _camera->getStartX() + _tiles[i].disX;
		_tiles[i].posCenter.y = _camera->getStartY() + _tiles[i].disY;
		_tiles[i].rc = RectMakeCenter(_tiles[i].posCenter.x, _tiles[i].posCenter.y, TILESIZE, TILESIZE);

	}
}
