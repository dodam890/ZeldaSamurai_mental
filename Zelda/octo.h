#pragma once
#include "enemy.h"

class octo : public enemy
{
public:
	octo();
	virtual ~octo();

	virtual HRESULT init(camera* camera, int idxX, int idxY);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void move();
	virtual void addFrame();
	virtual void draw();

	virtual void addImage();
};

