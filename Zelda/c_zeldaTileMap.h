#pragma once
#include "zeldaTileMap.h"

class zeldaTileMap1 : public zeldaTileMap
{
private:
public:
	zeldaTileMap1() {}
	virtual ~zeldaTileMap1() {}

	virtual HRESULT init(player* player, camera* camera, const CHAR* pMapSaveFileName, int mapWidth, int mapHeight);
	virtual void release();
	virtual void update();
	virtual void render();
};

class zeldaTileMap2 : public zeldaTileMap
{
private:
public:
	zeldaTileMap2() {}
	virtual ~zeldaTileMap2() {}

	virtual HRESULT init(player* player, camera* camera, const CHAR* pMapSaveFileName, int mapWidth, int mapHeight);
	virtual void release();
	virtual void update();
	virtual void render();
};

class zeldaTileMap3 : public zeldaTileMap
{
private:
public:
	zeldaTileMap3() {}
	virtual ~zeldaTileMap3() {}

	virtual HRESULT init(player* player, camera* camera, const CHAR* pMapSaveFileName, int mapWidth, int mapHeight);
	virtual void release();
	virtual void update();
	virtual void render();
};

class zeldaTileMap4 : public zeldaTileMap
{
private:
public:
	zeldaTileMap4() {}
	virtual ~zeldaTileMap4() {}

	virtual HRESULT init(player* player, camera* camera, const CHAR* pMapSaveFileName, int mapWidth, int mapHeight);
	virtual void release();
	virtual void update();
	virtual void render();
};

class zeldaTileMap5 : public zeldaTileMap
{
private:
public:
	zeldaTileMap5() {}
	virtual ~zeldaTileMap5() {}

	virtual HRESULT init(player* player, camera* camera, const CHAR* pMapSaveFileName, int mapWidth, int mapHeight);
	virtual void release();
	virtual void update();
	virtual void render();
};

