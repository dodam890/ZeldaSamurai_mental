#pragma once
#include "gameNode.h"

class shop_class : public gameNode
{
private:

	bool click_now;
	int message_x;
	int message_y;

	int corcer_x;
	int corcer_y;

	RECT item_rc[6];

	RECT _rc[3];

	int temp_now_pick;
	int pick_where;


public:
	shop_class();
	~shop_class();

	HRESULT init();
	void release();
	void update();
	void render();

	void select_render(float left, float top, float right, float bottom, int carrent_x, int carrent_y);

	int get_pick_where() { return pick_where; }

};

