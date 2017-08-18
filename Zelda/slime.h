#pragma once
#include "enemy.h"

class slime : public enemy
{
public:
	slime();
	virtual ~slime();

	virtual HRESULT init(camera* camera, zeldaTileMap* map, int idxX, int idxY);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void move(int index);
	virtual void addFrame();
	virtual void draw();

	virtual void addImage();
};

