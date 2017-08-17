#pragma once
#include "gameNode.h"
#include "mapTool.h"

class mapToolScene : public gameNode
{
private:
	mapTool* _mt;

public:

	HRESULT init();
	void release();
	void update();
	void render();

	mapToolScene();
	~mapToolScene();
};

