#pragma once
#include "gameNode.h"
#include "item_class.h"
#include <vector>

enum upgrade_state_view
{
	upgrade_state_view_standard,
	upgrade_state_view_select
};

enum upgrade_state_step
{
	upgrade_NONE,
	upgrade_select,
	upgrade_confirm,
	upgrade_fail,
	upgrade_success
};

class inven_all;

class up_grade_complete : public gameNode
{
	struct inven_item_part_struct
	{
		RECT _rc;
	};
	struct save_button_type
	{
		RECT _rc;
	};

	struct S_SCORE
	{
		int nRest;
		int nDiv;
		image* pImg[10];
	};

private:

	S_SCORE m_arScore[10];

	vector<item_class*> _vi;
	vector<item_class*>::iterator _vii;

	int main_x;
	int main_y;

	int corcer_x;
	int corcer_y;

	int temp_now_pick;
	bool click_now;
	int pick_where;

	inven_item_part_struct item_12[12];
	inven_item_part_struct special_item_4[4];

	int num_x;
	int num_y;

	upgrade_state_view invens_view;

	RECT _rc[2];

	bool upgrade_exit;

	int count;
	int index;

	bool confirm_reset;


	int text_count;
	int text_index;

	inven_all* _in;

	upgrade_state_step _uss;

	int P_mon;

	int get_inven_moneny;

public:
	up_grade_complete();
	~up_grade_complete();

	HRESULT init();
	void release();
	void update();
	void render();

	void set_vi(vector<item_class*> set_vi) { _vi = set_vi; }
	void select_render(float left, float top, float right, float bottom, int carrent_x, int carrent_y);


	void set_invens_view(upgrade_state_view USV) { invens_view = USV; }

	void set_upgrade_exit(bool bo) { upgrade_exit = bo; }
	bool get_upgrade_exit() { return upgrade_exit; }

	void set_confirm_reset(bool bo) { confirm_reset = bo; }
	bool get_confirm_reset() { return confirm_reset; }

	void set_my_in(inven_all* it) { _in = it; }

	void set_inven_money(int num) { get_inven_moneny = num; }

	void set_P_mon(int num) { P_mon = num; }

	void loadNumberImg();
	void scoreRender();
};

