#include "stdafx.h"
#include "item_class.h"


HRESULT item_class::init()
{
	_x = 0;
	_y = 0;

	carmeraX = 0;
	carmeraY = 0;

	renderX = 0;
	renderY = 0;

	numbering_where = 0;

	return S_OK;
}

void item_class::release()
{
}

void item_class::update()
{
	renderX = _x - carmeraX;
	renderY = _y - carmeraY;

	_rc = RectMakeCenter(_x, _y, _image->getWidth(), _image->getHeight());
}

void item_class::render()
{
	_image->render(getMemDC(), _rc.left, _rc.top);
}

void item_class::trow_move(float angle)
{
	float before_X = 0;
	float before_Y = 0;

	before_X = _x;
	before_Y = _y;

	while (0)
	{
		_x += cosf(angle) * 5;
		_y += -sinf(angle) * 5;
		if (getDistance(before_X, before_Y, _x, _y) > 100) break;
	}
}

void item_class::setting_items(image* img, string name, string text, int num, float x, float y, int vol, item_type type, item_where _where, bool equip, item_option _io)
{

	_item_where = _where;
	_image = img;
	_item_num = num;
	_x = x;
	_y = y;
	_item_name = name;
	_item_sub_text = text;
	_itemtype = type;
	_volume = vol;
	is_equip = equip;
	_item_option = _io;
}


item_class::item_class()
{
}


item_class::~item_class()
{
}
