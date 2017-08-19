#pragma once
#include "gameNode.h"
#include "zeldaTileNode.h"
#include "camera.h"
#include "enemyManager.h"

class player;

class zeldaTileMap : public gameNode
{
protected:
	camera* _camera;
	image* _imgTmpBackbuffer;

	int _mapWidth;
	int _mapHeight;

protected:
	tagTile _tiles[TILEX * TILEY];
	BOOL _attribute[E_ATR_END][TILEX * TILEY];

protected:
	enemyManager* _em;
	player* _player;

public:
	zeldaTileMap();
	virtual ~zeldaTileMap();

	virtual HRESULT init(player* player, camera* camera, const CHAR* pSaveMapFileName, int mapWidth, int mapHeight);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void loadMap(const CHAR* pSaveMapFileName);

	void cameraSetTile();

	int getMapWidth() { return _mapWidth; }
	int getMapHeight() { return _mapHeight; }

	BOOL* getAttribute(ATTRIBUTE attribute) { return _attribute[attribute]; }
	tagTile* getTiles() { return _tiles; }
};

