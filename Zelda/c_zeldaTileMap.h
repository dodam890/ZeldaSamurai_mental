#pragma once
#include "zeldaTileMap.h"

class zeldaTileMap1 : public zeldaTileMap
{
private:
public:
	zeldaTileMap1() {}
	virtual ~zeldaTileMap1() {}

	virtual HRESULT init(camera* camera, const CHAR* pMapSaveFileName, int mapWidth, int mapHeight);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void loadMap();
};

class zeldaTileMap2 : public zeldaTileMap
{
private:
public:
	zeldaTileMap2() {}
	virtual ~zeldaTileMap2() {}

	virtual HRESULT init(camera* camera, const CHAR* pMapSaveFileName, int mapWidth, int mapHeight);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void loadMap();
};

class zeldaTileMap3 : public zeldaTileMap
{
private:
public:
	zeldaTileMap3() {}
	virtual ~zeldaTileMap3() {}

	virtual HRESULT init(camera* camera, const CHAR* pMapSaveFileName, int mapWidth, int mapHeight);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void loadMap();
};

