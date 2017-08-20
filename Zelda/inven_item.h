#pragma once
#include "gameNode.h"
#include "item_class.h"
#include <vector>

class inven_item : public gameNode
{
	struct inven_item_part_struct
	{
		RECT _rc;
	};
	struct save_button_type
	{
		RECT _rc;
	};

private:

	vector<item_class*> _vi;
	vector<item_class*>::iterator _vii;

	inven_item_part_struct item_12[12];
	inven_item_part_struct special_item_4[4];
	save_button_type it_save_button;

	int num_x;
	int num_y;

public:
	inven_item();
	~inven_item();

	HRESULT init();
	void release();
	void update();
	void render();

	void keypad();

	vector<item_class*> get_inven_v() { return _vi; }
	void set_inven_v(vector<item_class*> _VI) { _vi = _VI; }

	inven_item_part_struct* get_item_part_12() { return item_12; }
	inven_item_part_struct* get_item_special_4() { return special_item_4; }
	save_button_type get_button(void) { return it_save_button; }

	int get_num_x(void) { return num_x; }
	int get_num_y(void) { return num_y; }

};

