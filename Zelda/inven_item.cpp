#include "stdafx.h"
#include "inven_item.h"


inven_item::inven_item()
{
}


inven_item::~inven_item()
{
}

HRESULT inven_item::init()
{
	//위 12개 정렬

	for (int i = 0; i < 12; i++)
	{
		item_12[i]._rc = RectMakeCenter(335 + (i % 4) * 180, 232 + (i / 4) * 120, 130, 100);
	}

	for (int j = 0; j < 4; j++)
	{
		special_item_4[j]._rc = RectMakeCenter(330 + j * 124, 592, 120, 100);
	}

	////아래
	//it_save_button._rc = RectMake(790, 550, 210, 90);

	num_x = 0;
	num_y = 0;

	return S_OK;
}

void inven_item::release()
{
}

void inven_item::update()
{
	keypad();
}

void inven_item::render()
{
	IMAGEMANAGER->findImage("인벤토리내용1")->render(getMemDC(), 85, 90);
	//IMAGEMANAGER->findImage("인벤토리세이브")->render(getMemDC(), it_save_button._rc.left, it_save_button._rc.top);
	//for (int i = 0; i < 12; i++)
	//{
	//	Rectangle(getMemDC(), item_12[i]._rc.left, item_12[i]._rc.top, item_12[i]._rc.right, item_12[i]._rc.bottom);
	//}
	//for (int j = 0; j < 4; j++)
	//{
	//	Rectangle(getMemDC(), special_item_4[j]._rc.left, special_item_4[j]._rc.top, special_item_4[j]._rc.right, special_item_4[j]._rc.bottom);
	//}
	//Rectangle(getMemDC(), it_save_button._rc.left, it_save_button._rc.top, it_save_button._rc.right, it_save_button._rc.bottom);

	int temp_item_12_vol = 0;
	int temp_s_item_4_vol = 0;

	for (int i = 0; i < _vi.size(); i++)
	{

		if (_vi.size() < 0) break;

		float temp_x = 0;
		float temp_y = 0;

		if (_vi[i]->get_itemtype() != using_item && _vi[i]->get_itemtype() != Interaction_item)
		{
			if (temp_item_12_vol < 12)
			{
				temp_x = item_12[temp_item_12_vol]._rc.left;
				temp_y = item_12[temp_item_12_vol]._rc.top;
				temp_item_12_vol++;
			}
			if (_vi[i]->get_is_equip() == true)
			{
				IMAGEMANAGER->findImage("인벤토리아이템선택")->render(getMemDC(), temp_x, temp_y);
			}
		}
		else if (_vi[i]->get_itemtype() == Interaction_item)
		{
			if (temp_s_item_4_vol < 4)
			{
				temp_x = special_item_4[temp_s_item_4_vol]._rc.left;
				temp_y = special_item_4[temp_s_item_4_vol]._rc.top;
				temp_s_item_4_vol++;
			}
			if (_vi[i]->get_is_equip() == true)
			{
				IMAGEMANAGER->findImage("인벤토리아이템선택2")->render(getMemDC(), temp_x, temp_y);
			}
		}

		_vi[i]->get_image()->render(getMemDC(), temp_x + 20, temp_y + 15);
	}
}
void inven_item::keypad()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		num_x--;

		if (num_x < 0 && num_x + (4 * num_y) == 11)
		{
			num_x = 3;
		}
		else if (num_x < 0 && num_x + (4 * num_y) < 12)
		{
			num_x = 3;
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		num_x++;
		if (num_x > 3 && num_x + (4 * num_y) <= 12)
		{
			num_x = 0;
		}
		else if (num_x > 3 && num_x + (4 * num_y) > 12)
		{
			num_x = 0;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		if (num_x + (4 * num_y) == 14 || num_x + (4 * num_y) == 15 || num_x + (4 * num_y) == 16)
		{
			num_y--;
			num_x--;
		}
		else if (num_x + (4 * num_y) == 2 || num_x + (4 * num_y) == 3)
		{
			num_y--;
			num_x++;
		}
		else
		{
			num_y--;
		}

		if (num_y < 0 && num_x == 4)
		{
			num_x--;
			num_y = 2;
		}
		else if (num_y < 0 && num_x + (4 * num_y) != 14)
		{
			num_y = 3;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		if (num_x + (4 * num_y) == 10 || num_x + (4 * num_y) == 11)
		{
			num_y++;
			num_x++;
		}
		else if (num_x + (4 * num_y) == 14 || num_x + (4 * num_y) == 15 || num_x + (4 * num_y) == 16)
		{
			num_y++;
			num_x--;
		}
		else
		{
			num_y++;
		}

		if (num_x + (4 * num_y) == 16)
		{
			num_x--;
			num_y = 0;
		}
		else if (num_y > 3)
		{
			num_y = 0;
		}
	}
}

