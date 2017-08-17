#pragma once
#include "gameNode.h"

class player;
class npc;

struct tagZorder
{
	string key;
	void* randomClass;
};
class npcZorder : public gameNode
{
private:
	vector<tagZorder> _vZorder;
	vector<tagZorder>::iterator _viZorder;
	int _zOrderCount;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void setTownNpcByZorder(player* player, npc** townNpc, int townNpcNum);
	void setStoreNpcByZorder(player* player, npc** storeNpc, int storeNpcNum);
	void sortNpcByZorder();
	void drawNpcByZorder();

	npcZorder();
	~npcZorder();
};

