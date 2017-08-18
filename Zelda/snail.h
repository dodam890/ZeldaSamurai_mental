#pragma once
#include "enemy.h"

class snail : public enemy
{
public:
	snail();
	virtual ~snail();

	virtual HRESULT init(camera* camera, zeldaTileMap* map, int idxX, int idxY);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void move();
	virtual void addFrame();
	virtual void draw();

	virtual void addImage();
};

