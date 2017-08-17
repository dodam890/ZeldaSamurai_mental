#pragma once
#include "gameNode.h"

class main_scene : public gameNode
{
private:
	int count;
	int carrentX;

	int logo_Y;

	bool islogo;

	int sub_logo_x;

	int alpha_num;


	bool ready_to_change;
	bool ready_to_push_button;
	int change_alpha;

public:
	main_scene();
	~main_scene();

	HRESULT init();
	void release();
	void update();
	void render();

};

