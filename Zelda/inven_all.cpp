#include "stdafx.h"
#include "inven_ALL.h"


inven_all::inven_all()
{
}


inven_all::~inven_all()
{
}

HRESULT inven_all::init()
{
	temp_item12_vol = 0;
	temp_Sitem4_vol = 0;

	_iit = new inven_item;
	_iit->init();
	_icl = new inven_collect;
	_icl->init();
	_im = new inven_map;
	_im->init();
	_item_m = new item_class_manager;
	_item_m->init();

	_item_m->add_items_init(100, 200, 12, 1, false);
	_item_m->add_items_init(100, 300, 12, 1, false);
	_item_m->add_items_init(100, 400, 12, 1, false);
	_item_m->add_items_init(100, 500, 12, 1, false);

	count = 0;
	index = 0;

	inven_change_A_x = 10;
	inven_change_A_y = 320;

	inven_change_B_x = 1085;
	inven_change_B_y = 320;

	count_inven_change = 0;
	change_bo = false;

	key_A = false;
	key_B = false;

	change_view_I = 0;

	equip_z = 0;
	equip_x = 0;

	change_view = collect_part;

	switch (change_view)
	{
	case item_part:
		inven_change_effect_x1 = 0;
		inven_change_effect_y1 = 10;

		inven_change_effect_x2 = 0;
		inven_change_effect_y2 = -120;

		inven_change_effect_x3 = 0;
		inven_change_effect_y3 = -120;

		ZX_B_UP = 80;
		ZX_I_UP = 25;
		break;

	case collect_part:
		inven_change_effect_x1 = 0;
		inven_change_effect_y1 = -120;

		inven_change_effect_x2 = 0;
		inven_change_effect_y2 = 10;

		inven_change_effect_x3 = 0;
		inven_change_effect_y3 = -120;

		ZX_B_UP = -120;
		ZX_I_UP = -120;
		break;

	case map_part:
		inven_change_effect_x1 = 0;
		inven_change_effect_y1 = -120;

		inven_change_effect_x2 = 0;
		inven_change_effect_y2 = -120;

		inven_change_effect_x3 = 0;
		inven_change_effect_y3 = 10;

		ZX_B_UP = -120;
		ZX_I_UP = -120;
		break;
	}

	return S_OK;
}

HRESULT inven_all::init(inven_tory_type call_type)
{

	change_view = call_type;

	return S_OK;
}

void inven_all::release()
{

}

void inven_all::update()
{
	//test
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < _item_m->get_vt().size(); i++)
		{
			if (PtInRect(&_item_m->get_vt()[i]->get_rc(), _ptMouse))
			{
				if (_item_m->get_vt()[i]->get_itemtype() != using_item)
				{
					if (_item_m->get_vt()[i]->get_itemtype() != Interaction_item)
					{
						if (temp_item12_vol < 12)
						{
							add_to_inven(_item_m->get_vt()[i]->get_image(),
								_item_m->get_vt()[i]->get_item_name(),
								_item_m->get_vt()[i]->get_item_sub_text(),
								_item_m->get_vt()[i]->get_item_num(),
								1,
								_item_m->get_vt()[i]->get_itemtype(),
								_item_m->get_vt()[i]->get_item_where(),
								false);
							_vi[_vi.size() - 1]->set_numbering_where(temp_item12_vol);
							_iit->set_inven_v(get_vi());
							temp_item12_vol++;
						}
					}
					else if (_item_m->get_vt()[i]->get_itemtype() == Interaction_item)
					{
						if (temp_Sitem4_vol < 4)
						{
							add_to_inven(_item_m->get_vt()[i]->get_image(),
								_item_m->get_vt()[i]->get_item_name(),
								_item_m->get_vt()[i]->get_item_sub_text(),
								_item_m->get_vt()[i]->get_item_num(),
								1,
								_item_m->get_vt()[i]->get_itemtype(),
								_item_m->get_vt()[i]->get_item_where(),
								false);
							_vi[_vi.size() - 1]->set_numbering_where(12 + temp_Sitem4_vol);
							_iit->set_inven_v(get_vi());
							temp_Sitem4_vol++;
						}
					}
				}
			}
		}
	}

	count++;
	if (count % 20 == 0)
	{
		index++;
		if (index >= 2) index = 0;
		count = 0;
	}

	if (change_view == item_part)
	{
		_iit->update();
	}
	else if (change_view == collect_part)
	{
		_icl->update();
	}
	else if (change_view == map_part)
	{
		_im->update();
	}
	inven_controll();
	_item_m->update();
}

void inven_all::render()
{
	IMAGEMANAGER->findImage("인벤토리배경화면")->render(getMemDC(), 0, 0);
	if (change_view == item_part)
	{
		_iit->render();

		int tmep_numbering = _iit->get_num_x() + (4 * _iit->get_num_y());

		if (tmep_numbering <= 11)
		{
			select_render(0,
				_iit->get_item_part_12()[tmep_numbering]._rc.left - 8,
				_iit->get_item_part_12()[tmep_numbering]._rc.top - 8,
				_iit->get_item_part_12()[tmep_numbering]._rc.right + 8,
				_iit->get_item_part_12()[tmep_numbering]._rc.bottom + 8,
				index,
				0);
		}
		else if (tmep_numbering > 11 && tmep_numbering <= 15)
		{
			select_render(0,
				_iit->get_item_special_4()[_iit->get_num_x()]._rc.left - 8,
				_iit->get_item_special_4()[_iit->get_num_x()]._rc.top - 8,
				_iit->get_item_special_4()[_iit->get_num_x()]._rc.right + 8,
				_iit->get_item_special_4()[_iit->get_num_x()]._rc.bottom + 8,
				index,
				0);
		}
		else if (tmep_numbering > 15)
		{
			select_render(1,
				_iit->get_button()._rc.left - 8,
				_iit->get_button()._rc.top - 8,
				_iit->get_button()._rc.right + 8,
				_iit->get_button()._rc.bottom + 8,
				index,
				0);
		}
		_item_m->render();
		select_item();
	}
	else if (change_view == collect_part)
	{
		_icl->render();

		int tmep_numbering = _icl->get_num_x() + (5 * _icl->get_num_y());

		if (tmep_numbering == 0 ||
			tmep_numbering == 1 ||
			tmep_numbering == 6 ||
			tmep_numbering == 7)
		{
			if (tmep_numbering == 6)
			{
				select_render(1,
					_icl->get_collect_m()[_icl->get_num_x() + 1]._rc.left - 8,
					_icl->get_collect_m()[_icl->get_num_x() + 1]._rc.top - 8,
					_icl->get_collect_m()[_icl->get_num_x() + 1]._rc.right + 8,
					_icl->get_collect_m()[_icl->get_num_x() + 1]._rc.bottom + 8,
					index,
					0);
			}
			else if (tmep_numbering == 7)
			{
				select_render(0,
					_icl->get_collect_m()[_icl->get_num_x() + 1]._rc.left - 8,
					_icl->get_collect_m()[_icl->get_num_x() + 1]._rc.top - 8,
					_icl->get_collect_m()[_icl->get_num_x() + 1]._rc.right + 8,
					_icl->get_collect_m()[_icl->get_num_x() + 1]._rc.bottom + 8,
					index,
					0);
			}
			else if (tmep_numbering == 0)
			{
				select_render(1,
					_icl->get_collect_m()[_icl->get_num_x()]._rc.left - 8,
					_icl->get_collect_m()[_icl->get_num_x()]._rc.top - 8,
					_icl->get_collect_m()[_icl->get_num_x()]._rc.right + 8,
					_icl->get_collect_m()[_icl->get_num_x()]._rc.bottom + 8,
					index,
					0);
			}
			else if (tmep_numbering == 1)
			{
				select_render(0,
					_icl->get_collect_m()[_icl->get_num_x()]._rc.left - 8,
					_icl->get_collect_m()[_icl->get_num_x()]._rc.top - 8,
					_icl->get_collect_m()[_icl->get_num_x()]._rc.right + 8,
					_icl->get_collect_m()[_icl->get_num_x()]._rc.bottom + 8,
					index,
					0);
			}
		}
		else if (tmep_numbering == 2 ||
			tmep_numbering == 3 ||
			tmep_numbering == 4 ||
			tmep_numbering == 5)
		{
			select_render(0,
				_icl->get_collect_o4()[_icl->get_num_x() - 2]._rc.left - 8,
				_icl->get_collect_o4()[_icl->get_num_x() - 2]._rc.top - 8,
				_icl->get_collect_o4()[_icl->get_num_x() - 2]._rc.right + 8,
				_icl->get_collect_o4()[_icl->get_num_x() - 2]._rc.bottom + 8,
				index,
				0);
		}
		else if (tmep_numbering == 8 ||
			tmep_numbering == 9 ||
			tmep_numbering == 10)
		{
			select_render(0,
				_icl->get_collect_o3()[_icl->get_num_x() - 3]._rc.left - 8,
				_icl->get_collect_o3()[_icl->get_num_x() - 3]._rc.top - 8,
				_icl->get_collect_o3()[_icl->get_num_x() - 3]._rc.right + 8,
				_icl->get_collect_o3()[_icl->get_num_x() - 3]._rc.bottom + 8,
				index,
				0);
		}
		else if (tmep_numbering == 11 ||
			tmep_numbering == 12 ||
			tmep_numbering == 13)
		{
			select_render(0,
				_icl->get_collect_s()[_icl->get_num_x() - 1]._rc.left - 8,
				_icl->get_collect_s()[_icl->get_num_x() - 1]._rc.top - 8,
				_icl->get_collect_s()[_icl->get_num_x() - 1]._rc.right + 8,
				_icl->get_collect_s()[_icl->get_num_x() - 1]._rc.bottom + 8,
				index,
				0);
		}
		else if (tmep_numbering == 14)
		{
			select_render(1,
				_icl->get_sleep_b()._rc.left - 8,
				_icl->get_sleep_b()._rc.top - 8,
				_icl->get_sleep_b()._rc.right + 8,
				_icl->get_sleep_b()._rc.bottom + 8,
				index,
				0);
		}
		else if (tmep_numbering == 15)
		{
			select_render(1,
				_icl->get_save_b()._rc.left - 8,
				_icl->get_save_b()._rc.top - 8,
				_icl->get_save_b()._rc.right + 8,
				_icl->get_save_b()._rc.bottom + 8,
				index,
				0);
		}
	}
	else if (change_view == map_part)
	{
		_im->render();
	}
	IMAGEMANAGER->findImage("인벤토리배경화면")->alphaRender(getMemDC(), 0, 0, change_view_I);

	IMAGEMANAGER->findImage("인벤토리타이틀1")->render(getMemDC(), inven_change_effect_x1, inven_change_effect_y1);
	IMAGEMANAGER->findImage("인벤토리타이틀2")->render(getMemDC(), inven_change_effect_x2, inven_change_effect_y2);
	IMAGEMANAGER->findImage("인벤토리타이틀3")->render(getMemDC(), inven_change_effect_x3, inven_change_effect_y3);

	IMAGEMANAGER->findImage("인벤토리변경키1")->render(getMemDC(), inven_change_A_x, inven_change_A_y);
	IMAGEMANAGER->findImage("인벤토리변경키2")->render(getMemDC(), inven_change_B_x, inven_change_B_y);

	IMAGEMANAGER->findImage("버튼z")->render(getMemDC(), 900, ZX_B_UP);
	IMAGEMANAGER->findImage("버튼x")->render(getMemDC(), 1000, ZX_B_UP);

	if (_vi.size() > 0)
	{
		_vi[equip_z]->get_image()->render(getMemDC(), 895, ZX_I_UP);
		_vi[equip_x]->get_image()->render(getMemDC(), 995, ZX_I_UP);
	}
	//char str[128];
	//sprintf(str, "%d", _vi.size());
	//TextOut(getMemDC(), 20, 20, str, strlen(str));
}

void inven_all::add_to_inven(image * img, string name, string text, int num, int vol, item_type type, item_where _where, bool equip)
{
	item_class* temp = new item_class;
	temp->setting_items(img, name, text, num, 0, 0, vol, type, _where, equip);
	_vi.push_back(temp);
}

void inven_all::eraser(int arr)
{
	_vi.erase(_vi.begin() + arr);
}

void inven_all::inven_controll()
{
	if (change_bo == true)
	{
		count_inven_change++;

		switch (change_view)
		{

		case item_part:
		{
			if (count_inven_change < 15)
			{
				inven_change_effect_y1 -= 10;
				ZX_B_UP -= 15;
				ZX_I_UP -= 15;

				inven_change_A_x -= 8;
				inven_change_B_x += 8;
				change_view_I += 15;
			}
			else if (count_inven_change >= 15)
			{
				if (key_A == true) inven_change_effect_y3 += 10;
				if (key_B == true) inven_change_effect_y2 += 10;

				inven_change_A_x += 8;
				inven_change_B_x -= 8;
				change_view_I -= 15;

				if (inven_change_A_x >= 10)
				{
					inven_change_effect_x1 = 0;
					inven_change_effect_y1 = -120;
					ZX_B_UP = -120;
					ZX_I_UP = -120;

					if (key_A == true)
					{
						inven_change_effect_x3 = 0;
						inven_change_effect_y3 = 10;
						change_view = map_part;
						key_A = false;
					}

					else if (key_B == true)
					{
						inven_change_effect_x2 = 0;
						inven_change_effect_y2 = 10;
						change_view = collect_part;
						key_B = false;
					}

					inven_change_A_x = 10;
					inven_change_B_x = 1085;
					count_inven_change = 0;
					change_view_I = 0;
					change_bo = false;

				}
			}
		}
		break;

		case collect_part:
		{
			if (count_inven_change < 15)
			{
				inven_change_effect_y2 -= 10;
				inven_change_A_x -= 8;
				inven_change_B_x += 8;
				change_view_I += 15;
			}
			else if (count_inven_change >= 15)
			{
				if (key_A == true) inven_change_effect_y1 += 10, ZX_B_UP += 10, ZX_I_UP += 10;
				if (key_B == true) inven_change_effect_y3 += 10;

				inven_change_A_x += 8;
				inven_change_B_x -= 8;
				change_view_I -= 15;

				if (inven_change_A_x >= 10)
				{
					inven_change_effect_x2 = 0;
					inven_change_effect_y2 = -120;

					if (key_A == true)
					{
						inven_change_effect_x1 = 0;
						inven_change_effect_y1 = 10;
						change_view = item_part;
						ZX_B_UP = 80;
						ZX_I_UP = 25;
						key_A = false;
					}

					else if (key_B == true)
					{
						inven_change_effect_x3 = 0;
						inven_change_effect_y3 = 10;
						change_view = map_part;
						key_B = false;
					}

					inven_change_A_x = 10;
					inven_change_B_x = 1085;
					count_inven_change = 0;
					change_view_I = 0;
					change_bo = false;
				}
			}
		}
		break;

		case map_part:
		{
			if (count_inven_change < 15)
			{
				inven_change_effect_y3 -= 10;
				inven_change_A_x -= 8;
				inven_change_B_x += 8;
				change_view_I += 15;
			}
			else if (count_inven_change >= 15)
			{
				if (key_A == true) inven_change_effect_y2 += 10;
				if (key_B == true) inven_change_effect_y1 += 10, ZX_B_UP += 10, ZX_I_UP += 10;

				inven_change_A_x += 8;
				inven_change_B_x -= 8;
				change_view_I -= 15;
				if (inven_change_A_x >= 10)
				{
					inven_change_effect_x3 = 0;
					inven_change_effect_y3 = -120;

					if (key_A == true)
					{
						inven_change_effect_x2 = 0;
						inven_change_effect_y2 = 10;
						change_view = collect_part;
						key_A = false;
					}

					else if (key_B == true)
					{
						inven_change_effect_x1 = 0;
						inven_change_effect_y1 = 10;
						change_view = item_part;
						ZX_B_UP = 80;
						ZX_I_UP = 25;
						key_B = false;
					}

					inven_change_A_x = 10;
					inven_change_B_x = 1085;
					count_inven_change = 0;
					change_view_I = 0;
					change_bo = false;
				}
			}
		}
		break;
		}
	}

	if (KEYMANAGER->isOnceKeyDown('V'))
	{
		change_bo = true;
		key_A = true;
	}
	if (KEYMANAGER->isOnceKeyDown('B'))
	{
		change_bo = true;
		key_B = true;
	}
}

void inven_all::change_bowl(int vol)
{
	if (vol > 4) return;

	for (int i = 0; i < vol; i++)
	{
		for (_vii = _vi.begin(); _vii != _vi.end();)
		{
			if ((*_vii)->get_item_num() == 4)
			{
				add_to_inven(IMAGEMANAGER->findImage("요정병"),
					"요정병", "요정이 들어 있다. 위험할때 도와주는 친구",
					5,
					1,
					Interaction_item,
					inventory_item,
					false);
				_vii = _vi.erase(_vii);
				break;
			}
			else ++_vii;
		}
	}
}
void inven_all::select_render(int type, float left, float top, float right, float bottom, int carrent_x, int carrent_y)
{
	switch (type)
	{
	case 0:
		IMAGEMANAGER->findImage("빨간선택1")->frameRender(getMemDC(), left, top, carrent_x, carrent_y);
		IMAGEMANAGER->findImage("빨간선택2")->frameRender(getMemDC(), right - IMAGEMANAGER->findImage("빨간선택2")->getFrameWidth(), top, carrent_x, carrent_y);
		IMAGEMANAGER->findImage("빨간선택3")->frameRender(getMemDC(), left, bottom - IMAGEMANAGER->findImage("빨간선택3")->getFrameHeight(), carrent_x, carrent_y);
		IMAGEMANAGER->findImage("빨간선택4")->frameRender(getMemDC(), right - IMAGEMANAGER->findImage("빨간선택4")->getFrameWidth(), bottom - IMAGEMANAGER->findImage("빨간선택4")->getFrameHeight(), carrent_x, carrent_y);
		break;
	case 1:
		IMAGEMANAGER->findImage("초록선택1")->frameRender(getMemDC(), left, top, carrent_x, carrent_y);
		IMAGEMANAGER->findImage("초록선택2")->frameRender(getMemDC(), right - IMAGEMANAGER->findImage("초록선택2")->getFrameWidth(), top, carrent_x, carrent_y);
		IMAGEMANAGER->findImage("초록선택3")->frameRender(getMemDC(), left, bottom - IMAGEMANAGER->findImage("초록선택3")->getFrameHeight(), carrent_x, carrent_y);
		IMAGEMANAGER->findImage("초록선택4")->frameRender(getMemDC(), right - IMAGEMANAGER->findImage("초록선택4")->getFrameWidth(), bottom - IMAGEMANAGER->findImage("초록선택4")->getFrameHeight(), carrent_x, carrent_y);
		break;
	}
}

void inven_all::select_item(void)
{
	if (_vi.size() == 1)
	{
		_vi[equip_z]->set_equip(true);
		_vi[equip_x]->set_equip(true);
	}

	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		if (_vi.size() == 0) return;

		_vi[equip_z]->set_equip(false);

		if (equip_z == equip_x)
		{
			_vi[equip_x]->set_equip(true);
		}

		for (int i = 0; i < _vi.size(); i++)
		{
			if (_vi[i]->get_numbering_where() == _iit->get_num_x() + (4 * _iit->get_num_y()))
			{
				equip_z = i;
			}
		}

		_vi[equip_z]->set_equip(true);
	}
	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		if (_vi.size() == 0) return;

		_vi[equip_x]->set_equip(false);

		if (equip_z == equip_x)
		{
			_vi[equip_z]->set_equip(true);
		}

		for (int i = 0; i < _vi.size(); i++)
		{
			if (_vi[i]->get_numbering_where() == _iit->get_num_x() + (4 * _iit->get_num_y()))
			{
				equip_x = i;
			}
		}
		_vi[equip_x]->set_equip(true);
	}
}