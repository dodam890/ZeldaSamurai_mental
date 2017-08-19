#pragma once
#include "gameNode.h"

class select_scene : public gameNode
{
private:
	int count;
	int carrentX;

public:

	HRESULT init();
	void release();
	void update();
	void render();

	select_scene();
	~select_scene();
};

