#pragma once
#include "gameNode.h"
#include "zeldaTileMap.h"
#include "camera.h"
#include "enemyManager.h"


class zeldaTileMapScene : public gameNode
{
private:
	zeldaTileMap* _map;
	camera* _camera;

private:

	int _count;
	int _i;
	bool isFull;

	int _nIdxX;
	int _nIdxY;

	enemyManager* _em;


public:
	zeldaTileMapScene();
	virtual ~zeldaTileMapScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void testMove(int idx);
};

