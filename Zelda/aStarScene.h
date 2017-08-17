#pragma once
#include "aStar.h"
#include "gameNode.h"
#include "zeldaTileMap.h"
#include "camera.h"

class aStarScene : public gameNode
{
private:
	aStar* _aStar;
	zeldaTileMap* _map;
	camera* _ca;
public:
	aStarScene();
	virtual ~aStarScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

