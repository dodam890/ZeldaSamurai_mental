#pragma once
#include "gameNode.h"
#include "zeldaTileMap.h"
#include "camera.h"
#include "enemyManager.h"

class aStarScene : public gameNode
{
private:
	zeldaTileMap* _map;
	camera* _ca;

	enemyManager* _em;
public:
	aStarScene();
	virtual ~aStarScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

