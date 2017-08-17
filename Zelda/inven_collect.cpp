#include "stdafx.h"
#include "inven_collect.h"


inven_collect::inven_collect()
{
}


inven_collect::~inven_collect()
{
}

HRESULT inven_collect::init()
{
	for (int i = 0; i < 4; i++)
	{
		if (i <= 1)
		{
			collect_main4[i]._rc = RectMake(182 + (i % 2) * 215, 210, 174, 160);
		}
		else if (i > 1)
		{
			collect_main4[i]._rc = RectMake(182 + (i % 2) * 215, 400, 180, 130);
		}
	}
	for (int j = 0; j < 3; j++)
	{
		collect_sub[j]._rc = RectMake(208 + (j % 3) * 125, 555, 100, 100);
	}

	collect_ob4[0]._rc = RectMake(640, 225, 110, 110);
	collect_ob4[1]._rc = RectMake(762, 158, 105, 110);
	collect_ob4[2]._rc = RectMake(882, 225, 110, 110);
	collect_ob4[3]._rc = RectMake(760, 292, 110, 110);

	collect_sub_ob3[0]._rc = RectMake(628, 422, 110, 110);
	collect_sub_ob3[1]._rc = RectMake(762, 422, 110, 110);
	collect_sub_ob3[2]._rc = RectMake(888, 422, 110, 110);


	it_save_button._rc = RectMake(825, 565, 210, 90);
	it_sleep_button._rc = RectMake(605, 565, 210, 90);

	num_x = 0;
	num_y = 0;

	return S_OK;
}

void inven_collect::release()
{
}

void inven_collect::update()
{
	keypad();
}

void inven_collect::render()
{
	IMAGEMANAGER->findImage("인벤토리내용2")->render(getMemDC(), 85, 90);
	IMAGEMANAGER->findImage("인벤토리세이브")->render(getMemDC(), it_save_button._rc.left, it_save_button._rc.top);
	IMAGEMANAGER->findImage("인벤토리sleep")->render(getMemDC(), it_sleep_button._rc.left, it_sleep_button._rc.top);

	//for (int i = 0; i < 4; i++)
	//{
	//	Rectangle(getMemDC(), collect_main4[i]._rc.left, collect_main4[i]._rc.top, collect_main4[i]._rc.right, collect_main4[i]._rc.bottom);
	//	Ellipse(getMemDC(), collect_ob4[i]._rc.left, collect_ob4[i]._rc.top, collect_ob4[i]._rc.right, collect_ob4[i]._rc.bottom);
	//}
	//for (int i = 0; i < 3; i++)
	//{
	//	Rectangle(getMemDC(), collect_sub[i]._rc.left, collect_sub[i]._rc.top, collect_sub[i]._rc.right, collect_sub[i]._rc.bottom);
	//	Ellipse(getMemDC(), collect_sub_ob3[i]._rc.left, collect_sub_ob3[i]._rc.top, collect_sub_ob3[i]._rc.right, collect_sub_ob3[i]._rc.bottom);
	//}
}

void inven_collect::keypad()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		if (num_x + (5 * num_y) == 5)
		{
			num_x -= 3;
		}
		else
		{
			num_x--;
		}


		if (num_x < 0 && num_y == 0)
		{
			num_x = 4;
		}
		else if (num_x < 1 && num_y > 0)
		{
			num_x = 5;
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		if (num_x + (5 * num_y) == 4)
		{
			num_x = 0;
		}
		else if (num_x + (5 * num_y) == 5)
		{
			num_x--;
		}
		else
		{
			num_x++;
		}

		if (num_x > 5 && num_x + (5 * num_y) > 5)
		{
			num_x = 1;
		}
		else if (num_x > 5 && num_x + (5 * num_y) != 5)
		{
			num_x = 0;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{

		if (num_x + (5 * num_y) == 9)
		{
			num_x++;
			num_y--;
		}
		else if (num_x + (5 * num_y) == 5)
		{
			num_x -= 2;
		}
		else if (num_x + (5 * num_y) >= 6 && num_x + (5 * num_y) <= 10 || num_x + (5 * num_y) == 12 || num_x + (5 * num_y) == 13 || num_x + (5 * num_y) == 14)
		{
			num_x--;
			num_y--;
		}
		else
		{
			num_y--;
		}

		if (num_x == 2 && num_y < 0)
		{
			num_y = 2;
			num_x += 2;
		}
		else if (num_x == 1 && num_y < 0)
		{
			num_y = 2;
			num_x += 2;
		}
		else if (num_y < 0)
		{
			num_x++;
			num_y = 2;
		}

	}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		if (num_x + (5 * num_y) == 3)
		{
			num_x += 2;
		}
		else if (num_x + (5 * num_y) == 5)
		{
			num_y++;
			num_x--;
		}
		else if (num_x + (5 * num_y) == 6)
		{
			num_y++;
		}
		else if (num_x + (5 * num_y) == 7 || num_x + (5 * num_y) == 8)
		{
			num_y++;
			num_x++;
		}
		else if (num_x + (5 * num_y) >= 0 && num_x + (5 * num_y) <= 4 && num_x + (5 * num_y) != 3)
		{
			num_y++;
			num_x++;
		}
		else
		{
			num_y++;
		}


		if ((num_y == 3 && num_x == 2) || (num_y == 3 && num_x == 4) || (num_y == 3 && num_x == 3))
		{
			num_y -= 3;
			num_x -= 2;
		}
		else if (num_y > 2)
		{
			num_x--;
			num_y = 0;
		}
	}
}

