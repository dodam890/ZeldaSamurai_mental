#pragma once
#include "gameNode.h"
#include "item_class.h"
#include "camera.h"
#include <vector>

class item_class_manager : public gameNode
{
private:

	vector<item_class*> _vt;
	vector<item_class*>::iterator _vit;

	camera* _ca;

public:
	item_class_manager();
	~item_class_manager();

	HRESULT init();
	void release();
	void update();
	void render();

	//맵이 가져서 쓸 item 함수, 맵에 나타나게 하는 것
	void add_items_init(float x, float y, int numbering, int vol, bool equip, item_option _io);
	void item_search(item_class* calling, int num, float init_x, float init_y, int vol, bool equip, item_option _io);
	void eraser(int arr);


	void set_camera(camera* _cm) { _ca = _cm; }

	vector<item_class*> get_vt() { return _vt; }
	vector<item_class*>::iterator get_vit() { return _vit; }

};

