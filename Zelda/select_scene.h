#pragma once
#include "gameNode.h"

class select_scene : public gameNode
{
public:
	enum E_SELECT_RC
	{
		E_SELECT_MAPTOOL,
		E_SELECT_GAMESTART,
		E_SELECT_END = 2
	};

	struct S_SELECT_RC_INFO
	{
		image* img;
		RECT rc;
		string strSceneKey;
		int alpha;
	};

private:
	int count;
	int carrentX;
	S_SELECT_RC_INFO _rcSelect[E_SELECT_END];

public:

	HRESULT init();
	void release();
	void update();
	void render();

	select_scene();
	~select_scene();
};

