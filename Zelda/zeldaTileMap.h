#pragma once
#include "gameNode.h"
#include "zeldaTileNode.h"
#include "camera.h"
#include "enemyManager.h"
#include "emZorder.h"

class player;

class zeldaTileMap : public gameNode
{
protected:
	struct tagTileRect
	{
		RECT rc;
		image* image;
		bool isOn = false;
		bool setMove = false;

		int tileIndex;
	};

protected:
	emZorder* _emZorder;

protected:
	camera* _camera;
	image* _imgTmpBackbuffer;

	int _mapWidth;
	int _mapHeight;
	int emIdx;
	int testIdx;

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
	
	tagTile* getTile() { return _tiles; }

	BOOL* getAttribute(ATTRIBUTE attribute) { return _attribute[attribute]; }
	tagTile* getTiles() { return _tiles; }

	void playerToEnemyCollision();
	void enemyToPlayerCollision();

};

