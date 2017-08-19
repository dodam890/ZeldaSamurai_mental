#pragma once
#include "enemy.h"

class snail : public enemy
{
public:
	snail();
	virtual ~snail();

	virtual HRESULT init(player* player, camera* camera, zeldaTileMap* map, int idxX, int idxY);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void aStarMove(int index);
	virtual void normalMove();
	virtual void addFrame();
	virtual void draw();

	virtual void aStarPathFind();
	virtual void getMapAttribute();

	virtual void addImage();
};

