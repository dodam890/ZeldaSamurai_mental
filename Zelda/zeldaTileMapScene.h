#pragma once
#include "gameNode.h"
#include "zeldaTileMap.h"
#include "camera.h"

#include "aStar.h"
#include "aStarTile.h"

struct tagTestImage
{
	RECT rc;
	image* image;
	vector<aStarTile*> vTankTile;
	vector<aStarTile*>::iterator viTankTile;
};


class zeldaTileMapScene : public gameNode
{
private:
	zeldaTileMap* _map;
	camera* _camera;

private:
	aStar* _ast;

	int _count;
	int _i;
	bool isFull;

	int _nIdxX;
	int _nIdxY;

	tagTestImage _test;

public:
	zeldaTileMapScene();
	virtual ~zeldaTileMapScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void testMove(int idx);
};

