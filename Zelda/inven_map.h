#pragma once
#include "gameNode.h"

class inven_map : public gameNode
{
private:

	float P_x;
	float P_y;

	float m_x;
	float m_y;

	bool is_town;

public:
	inven_map();
	~inven_map();

	HRESULT init();
	void release();
	void update();
	void render();

	void set_is_town(bool bo) { is_town = bo; }
	void set_P_x(float _x) { P_x = _x; }
	void set_P_y(float _y) { P_y = _y; }

	void set_m_x(float _x) { m_x = _x; }
	void set_m_y(float _y) { m_y = _y; }

};

