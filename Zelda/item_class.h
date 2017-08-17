#pragma once
#include "gameNode.h"

enum item_where
{
	inventory_item,
	inventory_collect,
	inventory_map
};

enum item_type
{
	weapon,
	Armor,
	special_item,
	Interaction_item,
	using_item
};

class item_class : public gameNode
{
private:
	item_where _item_where;
	item_type _itemtype;
	string _item_name;
	string _item_sub_text;
	image* _image;
	int _item_num;
	RECT _rc;
	float _x;
	float _y;
	int _volume;
	bool is_equip;
	int numbering_where;

	//적용된 X , Y
	float renderX;
	float renderY;

	//카메라
	float carmeraX;
	float carmeraY;

public:

	HRESULT init();
	void release();
	void update();
	void render();

	void trow_move(float angle);

	void set_camera(float cax, float cay) { carmeraX = cax, carmeraY = cay; }
	void setting_items(image* img, string name, string text, int num, float x, float y, int vol, item_type type, item_where _where, bool equip);
	void set_equip(bool bo) { is_equip = bo; }
	void set_numbering_where(int nums) { numbering_where = nums; }


	int get_item_num() { return _item_num; }
	float get_item_X() { return _x; }
	float get_item_Y() { return _y; }

	item_where get_item_where() { return _item_where; }
	item_type get_itemtype() { return _itemtype; }
	string get_item_name() { return _item_name; }
	string get_item_sub_text() { return _item_sub_text; }
	image* get_image() { return _image; }
	RECT get_rc() { return _rc; }
	int get_volume() { return _volume; }
	bool get_is_equip() { return is_equip; }
	int get_numbering_where() { return numbering_where; }

	item_class();
	~item_class();
};

