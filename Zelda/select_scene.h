#pragma once
#include "gameNode.h"
#include "player.h"
#include "camera.h"

class select_scene : public gameNode
{
private:
	player* _link;
	camera* _camera;

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

