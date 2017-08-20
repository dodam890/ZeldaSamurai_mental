#pragma once
#include "gameNode.h"
#include "inven_item.h"
#include "inven_collect.h"
#include "inven_map.h"
#include "item_class.h"
#include <vector>

enum inven_tory_type
{
	item_part,
	collect_part,
	map_part
};

class inven_all : public gameNode
{
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

	inven_tory_type change_view;
	inven_item* _iit;
	inven_collect* _icl;
	inven_map* _im;

	//	equip_item


	int temp_item12_vol;
	int temp_Sitem4_vol;

	int count;
	int index;

	int inven_change_effect_x1;
	int	inven_change_effect_y1;

	int	inven_change_effect_x2;
	int	inven_change_effect_y2;

	int	inven_change_effect_x3;
	int	inven_change_effect_y3;

	int inven_change_A_x;
	int inven_change_A_y;

	int inven_change_B_x;
	int inven_change_B_y;


	int count_inven_change;
	bool change_bo;
	bool key_A;
	bool key_B;

	int equip_0;
	int equip_1;
	int equip_2;
	int equip_3;

	int change_view_I;

	int ZX_B_UP;
	int ZX_I_UP;

	int P_money;
	int key_vol;

public:
	inven_all();
	~inven_all();

	HRESULT init();
	HRESULT init(inven_tory_type call_type);
	void release();
	void update();
	void render();

	//플레이어가 item을 부딪힌것에 대해서 가져와서 인벤에 적재하는 함수 맵에 떨어진 함수에 대해서 얻는다.
	void add_to_inven(image* img, string name, string text, int num, int vol, item_type type, item_where _where, bool equip, item_option _io);
	void eraser(int arr);

	void change_bowl(int vol);

	// 0 :red, 1: green
	void select_render(int type, float left, float top, float right, float bottom, int carrent_x, int carrent_y);

	void select_item(void);

	void up_temp_item12_vol() { temp_item12_vol++; }
	void up_temp_Sitem4_vol() { temp_Sitem4_vol++; }

	int get_temp_item12_vol() { return temp_item12_vol; }
	int get_temp_Sitem4_vol() { return temp_Sitem4_vol; }
	int get_P_money() { return P_money; }
	void set_P_money(int _set) { P_money = _set; }
	void set_M_P_money(int _set) { P_money -= _set; }
	void set_P_P_money(int _set) { P_money += _set; }

	vector<item_class*> get_vi() { return _vi; }
	vector<item_class*>::iterator get_vii() { return _vii; }

	inven_item* get_iit() { return _iit; }
	inven_map* get_iim() { return _im; }

	void M_key_vol(int M) { key_vol -= M; }
	void P_key_vol(int P) { key_vol += P; }

	void inven_controll();

	void loadNumberImg();
	void scoreRender();
};

