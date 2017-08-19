#pragma once
#include "gameNode.h"
#include "item_class.h"

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

	bool give_item_is_true;

	item_class* _ic;

public:
	shop_class();
	~shop_class();

	HRESULT init();
	void release();
	void update();
	void render();

	item_class* get_ic() { return _ic; }
	item_class* buy_what(int arry);

	void select_render(float left, float top, float right, float bottom, int carrent_x, int carrent_y);

	bool get_give_item_is_true() { return give_item_is_true; }
	void set_give_item_is_true(bool bo) { give_item_is_true = bo; }

	int get_pick_where() { return pick_where; }
	int get_now_pick() { return temp_now_pick; }

};

