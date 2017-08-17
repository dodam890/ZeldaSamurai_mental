#pragma once
#include "gameNode.h"
#include "zeldaTileNode.h"
#include "camera.h"

class zeldaTileMap : public gameNode
{
private:
	camera* _camera;
	image* _imgTmpBackbuffer;

	int _mapWidth;
	int _mapHeight;

private:
	tagTile _tiles[TILEX * TILEY];
	BOOL _attribute[E_ATR_END][TILEX * TILEY];

public:
	zeldaTileMap();
	virtual ~zeldaTileMap();

	virtual HRESULT init(camera* camera, int mapWidth, int mapHeight);
	virtual void setCameraMemoryAddressLink(camera* camera) { _camera = camera; }
	virtual void release();
	virtual void update();
	virtual void render();

	void loadMap();
	void controlCamera();

	inline int getMapWidth() { return _mapWidth; }
	inline int getMapHeight() { return _mapHeight; }

	BOOL* getAttribute(ATTRIBUTE attribute) { return _attribute[attribute]; }
};

