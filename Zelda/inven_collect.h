#pragma once
#include "gameNode.h"

class inven_collect : public gameNode
{
	struct inven_collect_part_struct
	{
		RECT _rc;
	};
	struct save_button_type
	{
		RECT _rc;
	};
	struct sleep_button_type
	{
		RECT _rc;
	};

private:
	inven_collect_part_struct collect_main4[4];
	inven_collect_part_struct collect_sub[3];
	inven_collect_part_struct collect_ob4[4];
	inven_collect_part_struct collect_sub_ob3[3];
	save_button_type it_save_button;
	sleep_button_type it_sleep_button;

	int num_x;
	int num_y;

public:
	inven_collect();
	~inven_collect();

	HRESULT init();
	void release();
	void update();
	void render();

	void keypad();

	inven_collect_part_struct* get_collect_m() { return  collect_main4; }
	inven_collect_part_struct* get_collect_s() { return  collect_sub; }
	inven_collect_part_struct* get_collect_o4() { return  collect_ob4; }
	inven_collect_part_struct* get_collect_o3() { return  collect_sub_ob3; }
	save_button_type	get_save_b() { return it_save_button; }
	sleep_button_type	get_sleep_b() { return it_sleep_button; }

	int get_num_x() { return num_x; }
	int get_num_y() { return num_y; }

};

