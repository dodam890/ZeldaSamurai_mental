#pragma once
#include "gameNode.h"

class inven_map : public gameNode
{
public:
	inven_map();
	~inven_map();

	HRESULT init();
	void release();
	void update();
	void render();
};

