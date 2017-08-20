#include "stdafx.h"
#include "up_grade_complete.h"
#include "inven_all.h"


up_grade_complete::up_grade_complete()
{
}


up_grade_complete::~up_grade_complete()
{
}

HRESULT up_grade_complete::init()
{
	loadNumberImg();

	IMAGEMANAGER->addImage("검강화", "image/image_pbs/upgrade/검강화.bmp", 70, 19, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("방패강화", "image/image_pbs/upgrade/방패강화.bmp", 90, 19, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("강화비용1", "image/image_pbs/upgrade/R100.bmp", 55, 19, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("강화비용2", "image/image_pbs/upgrade/R200.bmp", 55, 19, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("강화비용3", "image/image_pbs/upgrade/R400.bmp", 55, 19, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("강화비용4", "image/image_pbs/upgrade/R800.bmp", 55, 19, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("강화비용5", "image/image_pbs/upgrade/R1600.bmp", 67, 19, true, RGB(255, 0, 255));

	pick_where = 0;
	click_now = true;
	corcer_x = 650 + 120;
	corcer_y = 150 + 406;
	temp_now_pick = 0;

	main_x = 650;
	main_y = 100;

	invens_view = upgrade_state_view_standard;

	_rc[0] = RectMake(main_x + 42, main_y + 25, 400, 40);
	_rc[1] = RectMake(main_x + 42, main_y + 70, 400, 40);

	upgrade_exit = false;

	count = 0;
	index = 0;

	for (int i = 0; i < 12; i++)
	{
		item_12[i]._rc = RectMakeCenter(335 + (i % 4) * 180, 232 + (i / 4) * 120, 130, 100);
	}

	for (int j = 0; j < 4; j++)
	{
		special_item_4[j]._rc = RectMakeCenter(330 + j * 124, 592, 120, 100);
	}

	num_x = 0;
	num_y = 0;

	confirm_reset = false;

	_uss = upgrade_NONE;

	text_count = 0;
	text_index = 0;

	return S_OK;
}

void up_grade_complete::release()
{
}

void up_grade_complete::update()
{
	if (invens_view == upgrade_state_view_standard)
	{
		_uss = upgrade_NONE;

		if (click_now == true)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
			{
				if (corcer_x > (650 + 120))
				{
					corcer_x -= 100;
				}
				else
				{
					corcer_x = 650 + 120;
				}
				pick_where = 0;
			}
			if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
			{
				if (corcer_x < (650 + 120 + 100))
				{
					corcer_x += 100;
				}
				else
				{
					corcer_x = 650 + 220;
				}
				pick_where = 1;
			}
			if (KEYMANAGER->isOnceKeyDown(VK_UP))
			{
				if (temp_now_pick > 0) temp_now_pick--;
			}
			if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
			{
				if (temp_now_pick < 1) temp_now_pick++;
			}

			if (KEYMANAGER->isOnceKeyDown('Z'))
			{
				if (pick_where == 0)
				{
					invens_view = upgrade_state_view_select;
				}
				else if (pick_where == 1)
				{
					upgrade_exit = true;
				}
			}
		}
	}
	else if (invens_view == upgrade_state_view_select)
	{
		_uss = upgrade_select;

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

			//if (num_x + (4 * num_y) == 16)
			//{
			//	num_x--;
			//	num_y = 0;
			//}
			//else 
			if (num_y > 3)
			{
				num_y = 0;
			}
		}
		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			_uss = upgrade_confirm;

			if (num_x + (4 * num_y) < _vi.size())
			{
				if (_in->get_vi()[num_x + (4 * num_y)]->get_item_option().Price <= _in->get_P_money())
				{
					if (temp_now_pick == 0)
					{
						if (_in->get_vi()[num_x + (4 * num_y)]->get_item_option().Upgrade < 5)
						{
							if (_vi[num_x + (4 * num_y)]->get_itemtype() == weapon)
							{
								_uss = upgrade_success;
								item_option* temp_io;
								temp_io = new item_option;

								if (_in->get_vi()[num_x + (4 * num_y)]->get_item_option().Upgrade == 0)
								{
									temp_io->Upgrade = _in->get_vi()[num_x + (4 * num_y)]->get_item_option().Upgrade + 1;
									temp_io->ATK = _in->get_vi()[num_x + (4 * num_y)]->get_item_option().ATK * 2;
									temp_io->ATK_SPEED = _in->get_vi()[num_x + (4 * num_y)]->get_item_option().ATK_SPEED * 2;
									temp_io->DEF = _in->get_vi()[num_x + (4 * num_y)]->get_item_option().DEF * 2;
									temp_io->Price = _in->get_vi()[num_x + (4 * num_y)]->get_item_option().Price * 2;
								}
								else
								{
									temp_io->Upgrade = _in->get_vi()[num_x + (4 * num_y)]->get_item_option().Upgrade + 1;
									temp_io->ATK = _in->get_vi()[num_x + (4 * num_y)]->get_item_option().ATK * temp_io->Upgrade;
									temp_io->ATK_SPEED = _in->get_vi()[num_x + (4 * num_y)]->get_item_option().ATK_SPEED * temp_io->Upgrade;
									temp_io->DEF = _in->get_vi()[num_x + (4 * num_y)]->get_item_option().DEF * temp_io->Upgrade;
									temp_io->Price = _in->get_vi()[num_x + (4 * num_y)]->get_item_option().Price * temp_io->Upgrade;
								}
								_in->get_vi()[num_x + (4 * num_y)]->set_item_option((*temp_io));

								_in->set_M_P_money(100 + temp_io->Upgrade * 200);

								set_inven_money(_in->get_P_money());

								upgrade_exit = true;
							}
						}
						else
						{
							_uss = upgrade_fail;
						}
					}
					else if (temp_now_pick == 1)
					{
						if (_in->get_vi()[num_x + (4 * num_y)]->get_item_option().Upgrade < 5)
						{
							if (_vi[num_x + (4 * num_y)]->get_itemtype() == Armor)
							{
								_uss = upgrade_success;
								item_option* temp_io;
								temp_io = new item_option;

								if (_in->get_vi()[num_x + (4 * num_y)]->get_item_option().Upgrade == 0)
								{
									temp_io->Upgrade = _in->get_vi()[num_x + (4 * num_y)]->get_item_option().Upgrade + 1;
									temp_io->ATK = _in->get_vi()[num_x + (4 * num_y)]->get_item_option().ATK * 2;
									temp_io->ATK_SPEED = _in->get_vi()[num_x + (4 * num_y)]->get_item_option().ATK_SPEED * 2;
									temp_io->DEF = _in->get_vi()[num_x + (4 * num_y)]->get_item_option().DEF * 2;
									temp_io->Price = _in->get_vi()[num_x + (4 * num_y)]->get_item_option().Price * 2;
								}
								else
								{
									temp_io->Upgrade = _in->get_vi()[num_x + (4 * num_y)]->get_item_option().Upgrade + 1;
									temp_io->ATK = _in->get_vi()[num_x + (4 * num_y)]->get_item_option().ATK * temp_io->Upgrade;
									temp_io->ATK_SPEED = _in->get_vi()[num_x + (4 * num_y)]->get_item_option().ATK_SPEED * temp_io->Upgrade;
									temp_io->DEF = _in->get_vi()[num_x + (4 * num_y)]->get_item_option().DEF * temp_io->Upgrade;
									temp_io->Price = _in->get_vi()[num_x + (4 * num_y)]->get_item_option().Price * temp_io->Upgrade;
								}
								_in->get_vi()[num_x + (4 * num_y)]->set_item_option((*temp_io));

								_in->set_M_P_money(100 + temp_io->Upgrade * 200);

								set_inven_money(_in->get_P_money());

								upgrade_exit = true;
							}
							else
							{
								_uss = upgrade_fail;
							}
						}
						else
						{
							_uss = upgrade_fail;
						}
					}
				}
			}
		}

		count++;
		if (count % 5 == 0)
		{
			index++;
			if (index > 1) index = 0;
			count = 0;
		}

		if (_uss == upgrade_success || _uss == upgrade_fail)
		{

		}
	}

	if (P_mon > get_inven_moneny)
	{
		P_mon -= 8;

		if (get_inven_moneny > P_mon)
		{
			P_mon = get_inven_moneny;
		}
	}
}

void up_grade_complete::render()
{
	char str[128];

	if (invens_view == upgrade_state_view_standard)
	{
		IMAGEMANAGER->findImage("상점이미지1")->render(getMemDC(), main_x, main_y);

		if (click_now == true)
		{
			select_render(_rc[temp_now_pick].left - 16, _rc[temp_now_pick].top - 10, _rc[temp_now_pick].right - 18, _rc[temp_now_pick].bottom - 20, 1, 0);

			IMAGEMANAGER->findImage("검강화")->render(getMemDC(), _rc[0].left + 20, _rc[0].top + 14);
			IMAGEMANAGER->findImage("방패강화")->render(getMemDC(), _rc[1].left + 20, _rc[1].top + 14);

			IMAGEMANAGER->findImage("대답1한다")->render(getMemDC(), 800, 550);
			IMAGEMANAGER->findImage("대답1그만둔다")->render(getMemDC(), 900, 550);
			IMAGEMANAGER->findImage("대답커서")->render(getMemDC(), corcer_x, corcer_y);
		}
	}
	if (invens_view == upgrade_state_view_select)
	{
		IMAGEMANAGER->findImage("인벤토리배경화면")->render(getMemDC(), 0, 0);
		IMAGEMANAGER->findImage("인벤토리내용1")->render(getMemDC(), 85, 90);
		IMAGEMANAGER->findImage("textBox")->render(getMemDC(), 16, 550);

		if (temp_now_pick == 0)
		{
			sprintf(str, "검을 선택해 주세요. ( 5 강 이상은 강화 되지 않습니다. )");
			TextOut(getMemDC(), 80, 600, str, strlen(str));

			if (_in->get_vi().size() > num_x + (4 * num_y))
			{
				sprintf(str, "현재 선택 무기 강화 : %d", _in->get_vi()[num_x + (4 * num_y)]->get_item_option().Upgrade);
				TextOut(getMemDC(), 80, 700, str, strlen(str));

				sprintf(str, "비용은 %d", 100 + _in->get_vi()[num_x + (4 * num_y)]->get_item_option().Upgrade * 200);
				TextOut(getMemDC(), 80, 650, str, strlen(str));

				sprintf(str, "선택 Z 취소 D");
				TextOut(getMemDC(), 700, 700, str, strlen(str));
			}
		}
		else if (temp_now_pick == 1)
		{
			sprintf(str, "방패를 선택해 주세요. ( 5 강 이상은 강화 되지 않습니다. )");
			TextOut(getMemDC(), 80, 600, str, strlen(str));
			if (_in->get_vi().size() > num_x + (4 * num_y))
			{
				sprintf(str, "현재 선택 무기 강화 : %d", _in->get_vi()[num_x + (4 * num_y)]->get_item_option().Upgrade);
				TextOut(getMemDC(), 80, 700, str, strlen(str));

				sprintf(str, "비용은 %d", 100 + _in->get_vi()[num_x + (4 * num_y)]->get_item_option().Upgrade * 200);
				TextOut(getMemDC(), 80, 650, str, strlen(str));

				sprintf(str, "선택 Z 취소 D");
				TextOut(getMemDC(), 700, 700, str, strlen(str));
			}
		}

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

		int tmep_numbering = num_x + (4 * num_y);
		{
			select_render(
				item_12[tmep_numbering]._rc.left - 16,
				item_12[tmep_numbering]._rc.top - 16,
				item_12[tmep_numbering]._rc.right - 12,
				item_12[tmep_numbering]._rc.bottom - 12,
				index,
				0);
		}

		//char str[128];
		//sprintf(str, "%d, %d", num_x, num_y);
		//TextOut(getMemDC(), 500, 500, str, strlen(str));
	}
	//for (int i = 0; i < 2; i++)
	//{
	//	Rectangle(getMemDC(), _rc[i].left, _rc[i].top, _rc[i].right, _rc[i].bottom);
	//}
	scoreRender();
}
void up_grade_complete::select_render(float left, float top, float right, float bottom, int carrent_x, int carrent_y)
{
	IMAGEMANAGER->findImage("빨간선택1")->frameRender(getMemDC(), left, top, carrent_x, carrent_y);
	IMAGEMANAGER->findImage("빨간선택2")->frameRender(getMemDC(), right - IMAGEMANAGER->findImage("빨간선택2")->getFrameWidth() / 6, top, carrent_x, carrent_y);
	IMAGEMANAGER->findImage("빨간선택3")->frameRender(getMemDC(), left, bottom - IMAGEMANAGER->findImage("빨간선택3")->getFrameHeight() / 6, carrent_x, carrent_y);
	IMAGEMANAGER->findImage("빨간선택4")->frameRender(getMemDC(), right - IMAGEMANAGER->findImage("빨간선택4")->getFrameWidth() / 6, bottom - IMAGEMANAGER->findImage("빨간선택4")->getFrameHeight() / 6, carrent_x, carrent_y);
}

void up_grade_complete::loadNumberImg()
{
	int nRest = 10;
	int nDiv = 1;

	for (int i = 0; i < 10; i++)
	{
		m_arScore[i].nDiv = nDiv;
		m_arScore[i].nRest = nRest;
		m_arScore[i].pImg[0] = IMAGEMANAGER->findImage("00");
		m_arScore[i].pImg[1] = IMAGEMANAGER->findImage("11");
		m_arScore[i].pImg[2] = IMAGEMANAGER->findImage("22");
		m_arScore[i].pImg[3] = IMAGEMANAGER->findImage("33");
		m_arScore[i].pImg[4] = IMAGEMANAGER->findImage("44");
		m_arScore[i].pImg[5] = IMAGEMANAGER->findImage("55");
		m_arScore[i].pImg[6] = IMAGEMANAGER->findImage("66");
		m_arScore[i].pImg[7] = IMAGEMANAGER->findImage("77");
		m_arScore[i].pImg[8] = IMAGEMANAGER->findImage("88");
		m_arScore[i].pImg[9] = IMAGEMANAGER->findImage("99");
		nDiv *= 10;
	}
}

void up_grade_complete::scoreRender()
{
	IMAGEMANAGER->findImage("초록루비")->render(getMemDC(), WINSIZEX - 1100, 98);

	for (int i = 0; i < 5; i++)
	{
		int nScoreIdx = 0;
		nScoreIdx = P_mon / m_arScore[i].nDiv % m_arScore[i].nRest;
		m_arScore[i].pImg[nScoreIdx]->render(getMemDC(), -i * 40 + WINSIZEX - 900, 104);
	}
}
