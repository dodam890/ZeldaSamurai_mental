#include "stdafx.h"
#include "shop_class.h"


shop_class::shop_class()
{
}


shop_class::~shop_class()
{
}

HRESULT shop_class::init()
{
	message_x = 650;
	message_y = 150;

	corcer_x = message_x + 120;
	corcer_y = message_y + 406;

	temp_now_pick = 0;
	click_now = true;

	_rc[0] = RectMake(message_x, message_y, IMAGEMANAGER->findImage("상점이미지1")->getWidth(), IMAGEMANAGER->findImage("상점이미지1")->getHeight());
	_rc[1] = RectMake(message_x + 150, message_y + 400, 51, 33);
	_rc[2] = RectMake(message_x + 250, message_y + 400, 105, 33);

	for (int i = 0; i < 6; i++)
	{
		item_rc[i] = RectMake(message_x + 34, message_y + 26 + i * 46, 412, 40);
	}
	return S_OK;
}

void shop_class::release()
{
}

void shop_class::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		bool temp_B = false;

		for (int i = 0; i < 6; i++)
		{
			if (PtInRect(&item_rc[i], _ptMouse))
			{
				temp_B = true;
				temp_now_pick = i;
			}
		}

		if (temp_B == true)
		{
			click_now = true;
			corcer_x = message_x + 120;
			corcer_y = message_y + 406;
		}
		else
		{
			click_now = false;
			corcer_x = 0;
			corcer_y = 0;
		}
	}

	if (click_now == true)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			if (corcer_x > (message_x + 120))
			{
				corcer_x -= 100;
			}
			else
			{
				corcer_x = message_x + 120;
			}
			pick_where = 0;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			if (corcer_x < (message_x + 120 + 100))
			{
				corcer_x += 100;
			}
			else
			{
				corcer_x = message_x + 220;
			}
			pick_where = 1;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			if (temp_now_pick > 0) temp_now_pick--;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			if (temp_now_pick < 5) temp_now_pick++;
		}

		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
		}
	}
}

void shop_class::render()
{
	IMAGEMANAGER->findImage("상점이미지1")->render(getMemDC(), message_x, message_y);

	if (click_now == true)
	{
		select_render(item_rc[temp_now_pick].left - 16, item_rc[temp_now_pick].top - 10, item_rc[temp_now_pick].right - 18, item_rc[temp_now_pick].bottom - 20, 1, 0);
		IMAGEMANAGER->findImage("대답1산다")->render(getMemDC(), message_x + 150, message_y + 400);
		IMAGEMANAGER->findImage("대답1그만둔다")->render(getMemDC(), message_x + 250, message_y + 400);
		IMAGEMANAGER->findImage("대답커서")->render(getMemDC(), corcer_x, corcer_y);
	}
	for (int i = 0; i < 6; i++)
	{
		if (i == 0)IMAGEMANAGER->findImage("글자검")->render(getMemDC(), item_rc[i].left + 20, item_rc[i].top + 15),
			IMAGEMANAGER->findImage("200루비")->render(getMemDC(), item_rc[i].left + 340, item_rc[i].top + 15);
		if (i == 1)IMAGEMANAGER->findImage("글자방패")->render(getMemDC(), item_rc[i].left + 20, item_rc[i].top + 15),
			IMAGEMANAGER->findImage("200루비")->render(getMemDC(), item_rc[i].left + 340, item_rc[i].top + 15);
		if (i == 2)IMAGEMANAGER->findImage("글자마법항아리")->render(getMemDC(), item_rc[i].left + 20, item_rc[i].top + 15),
			IMAGEMANAGER->findImage("250루비")->render(getMemDC(), item_rc[i].left + 340, item_rc[i].top + 15);
		if (i == 3)IMAGEMANAGER->findImage("글자요술지팡이")->render(getMemDC(), item_rc[i].left + 20, item_rc[i].top + 15),
			IMAGEMANAGER->findImage("250루비")->render(getMemDC(), item_rc[i].left + 340, item_rc[i].top + 15);
		if (i == 4)IMAGEMANAGER->findImage("글자병")->render(getMemDC(), item_rc[i].left + 20, item_rc[i].top + 15),
			IMAGEMANAGER->findImage("70루비")->render(getMemDC(), item_rc[i].left + 340, item_rc[i].top + 15);
		if (i == 5)IMAGEMANAGER->findImage("글자하트")->render(getMemDC(), item_rc[i].left + 20, item_rc[i].top + 15),
			IMAGEMANAGER->findImage("60루비")->render(getMemDC(), item_rc[i].left + 340, item_rc[i].top + 15);
	}
}

void shop_class::select_render(float left, float top, float right, float bottom, int carrent_x, int carrent_y)
{
	IMAGEMANAGER->findImage("빨간선택1")->frameRender(getMemDC(), left, top, carrent_x, carrent_y);
	IMAGEMANAGER->findImage("빨간선택2")->frameRender(getMemDC(), right - IMAGEMANAGER->findImage("빨간선택2")->getFrameWidth() / 6, top, carrent_x, carrent_y);
	IMAGEMANAGER->findImage("빨간선택3")->frameRender(getMemDC(), left, bottom - IMAGEMANAGER->findImage("빨간선택3")->getFrameHeight() / 6, carrent_x, carrent_y);
	IMAGEMANAGER->findImage("빨간선택4")->frameRender(getMemDC(), right - IMAGEMANAGER->findImage("빨간선택4")->getFrameWidth() / 6, bottom - IMAGEMANAGER->findImage("빨간선택4")->getFrameHeight() / 6, carrent_x, carrent_y);
}


//void item_class_manager::item_search(item_class* calling, int num, float init_x, float init_y, int vol, bool equip)
//{
//
//	item_state temp;
//
//	switch (num)
//	{
//		//검
//	case 0:
//
//		temp.ATK = 1;
//		temp.ATK_SPEED = 1.0;
//		temp.critical = 1.5;
//		temp.DEF = 0;
//		temp.price = 100;
//		temp.upgrade = 0;
//
//		calling->setting_items(IMAGEMANAGER->findImage("검"),
//			"검", "명검이다. 매우 아프다.",
//			0,
//			init_x,
//			init_y,
//			vol,
//			weapon,
//			inventory_item,
//			equip,
//			temp);
//		break;
//		//방패
//	case 1:
//
//		temp.ATK = 0;
//		temp.ATK_SPEED = 0;
//		temp.critical = 0;
//		temp.DEF = 10;
//		temp.price = 80;
//		temp.upgrade = 0;
//
//		calling->setting_items(IMAGEMANAGER->findImage("방패"),
//			"방패", "방패이다. 매우 견고하다.",
//			1,
//			init_x,
//			init_y,
//			vol,
//			Armor,
//			inventory_item,
//			equip,
//			temp);
//		break;
//		//항아리
//	case 2:
//
//		temp.ATK = 0;
//		temp.ATK_SPEED = 0;
//		temp.critical = 0;
//		temp.DEF = 0;
//		temp.price = 150;
//		temp.upgrade = 0;
//
//		calling->setting_items(IMAGEMANAGER->findImage("마법항아리"),
//			"마법항아리", "모든지 흡수한 후 다시 뱉어낸다",
//			2,
//			init_x,
//			init_y,
//			vol,
//			special_item,
//			inventory_item,
//			equip,
//			temp);
//		break;
//		//지팡이
//	case 3:
//
//		temp.ATK = 0;
//		temp.ATK_SPEED = 0;
//		temp.critical = 0;
//		temp.DEF = 0;
//		temp.price = 150;
//		temp.upgrade = 0;
//
//		calling->setting_items(IMAGEMANAGER->findImage("지팡이"),
//			"지팡이", "요술 지팡이, 모든지 반대로 뒤집니다.",
//			3,
//			init_x,
//			init_y,
//			vol,
//			special_item,
//			inventory_item,
//			equip,
//			temp);
//		break;
//		//빈병
//	case 4:
//
//		temp.ATK = 0;
//		temp.ATK_SPEED = 0;
//		temp.critical = 0;
//		temp.DEF = 0;
//		temp.price = 50;
//		temp.upgrade = 0;
//
//		calling->setting_items(IMAGEMANAGER->findImage("빈병"),
//			"빈병", "무언가를 담을 수 있다",
//			4,
//			init_x,
//			init_y,
//			vol,
//			Interaction_item,
//			inventory_item,
//			equip,
//			temp);
//		break;
//		//요정병
//	case 5:
//
//		temp.ATK = 0;
//		temp.ATK_SPEED = 0;
//		temp.critical = 0;
//		temp.DEF = 0;
//		temp.price = 250;
//		temp.upgrade = 0;
//
//		calling->setting_items(IMAGEMANAGER->findImage("요정병"),
//			"요정병", "요정이 들어 있다. 위험할때 도와주는 친구",
//			5,
//			init_x,
//			init_y,
//			vol,
//			Interaction_item,
//			inventory_item,
//			equip,
//			temp);
//		break;
//		//폭탄
//	case 6:
//
//		temp.ATK = 0;
//		temp.ATK_SPEED = 0;
//		temp.critical = 0;
//		temp.DEF = 0;
//		temp.price = 50;
//		temp.upgrade = 0;
//
//		calling->setting_items(IMAGEMANAGER->findImage("폭탄"),
//			"폭탄", "폭탄이다. 매우 강하다.",
//			6,
//			init_x,
//			init_y,
//			vol,
//			using_item,
//			inventory_item,
//			equip,
//			temp);
//		break;
//		//키
//	case 7:
//
//		temp.ATK = 0;
//		temp.ATK_SPEED = 0;
//		temp.critical = 0;
//		temp.DEF = 0;
//		temp.price = 70;
//		temp.upgrade = 0;
//
//		calling->setting_items(IMAGEMANAGER->findImage("키"),
//			"키", "잠긴 문을 열수 있는 열쇠이다.",
//			7,
//			init_x,
//			init_y,
//			vol,
//			using_item,
//			inventory_item,
//			equip,
//			temp);
//		break;
//		//보스방키
//	case 8:
//
//		temp.ATK = 0;
//		temp.ATK_SPEED = 0;
//		temp.critical = 0;
//		temp.DEF = 0;
//		temp.price = 200;
//		temp.upgrade = 0;
//
//		calling->setting_items(IMAGEMANAGER->findImage("보스방키"),
//			"보스방키", "보스 방문을 열수 있는 키이다.",
//			8,
//			init_x,
//			init_y,
//			vol,
//			using_item,
//			inventory_map,
//			equip,
//			temp);
//		break;
//		//하트추가
//	case 9:
//
//		temp.ATK = 0;
//		temp.ATK_SPEED = 0;
//		temp.critical = 0;
//		temp.DEF = 0;
//		temp.price = 60;
//		temp.upgrade = 0;
//
//		calling->setting_items(IMAGEMANAGER->findImage("하트추가"),
//			"하트", "생명력을 올려준다.",
//			9,
//			init_x,
//			init_y,
//			vol,
//			using_item,
//			inventory_item,
//			equip,
//			temp);
//		break;
//		//초록루비
//	case 10:
//
//		temp.ATK = 0;
//		temp.ATK_SPEED = 0;
//		temp.critical = 0;
//		temp.DEF = 0;
//		temp.price = 1;
//		temp.upgrade = 0;
//
//		calling->setting_items(IMAGEMANAGER->findImage("초록루비"),
//			"초록색 루비", " 1 루비 가치 이다.",
//			10,
//			init_x,
//			init_y,
//			vol,
//			using_item,
//			inventory_item,
//			equip,
//			temp);
//		break;
//		//파란루비
//	case 11:
//
//		temp.ATK = 0;
//		temp.ATK_SPEED = 0;
//		temp.critical = 0;
//		temp.DEF = 0;
//		temp.price = 5;
//		temp.upgrade = 0;
//
//		calling->setting_items(IMAGEMANAGER->findImage("파란루비"),
//			"파란색 루비", " 5 루비의 가치이다. ",
//			11,
//			init_x,
//			init_y,
//			vol,
//			using_item,
//			inventory_item,
//			equip,
//			temp);
//		break;
//		//빨간루비
//	case 12:
//
//		temp.ATK = 0;
//		temp.ATK_SPEED = 0;
//		temp.critical = 0;
//		temp.DEF = 0;
//		temp.price = 10;
//		temp.upgrade = 0;
//
//		calling->setting_items(IMAGEMANAGER->findImage("빨강루비"),
//			"빨강색 루비", " 10 루비의 가치이다. ",
//			12,
//			init_x,
//			init_y,
//			vol,
//			using_item,
//			inventory_item,
//			equip,
//			temp);
//		break;
//	}
//}
