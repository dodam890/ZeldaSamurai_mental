#include "stdafx.h"
#include "item_class_manager.h"


item_class_manager::item_class_manager()
{
}


item_class_manager::~item_class_manager()
{
}


HRESULT item_class_manager::init()
{
	return S_OK;
}

void item_class_manager::release()
{
}

void item_class_manager::update()
{
	for (_vit = _vt.begin(); _vit != _vt.end(); ++_vit)
	{
		(*_vit)->update();
	}
}

void item_class_manager::render()
{
	for (_vit = _vt.begin(); _vit != _vt.end(); ++_vit)
	{
		(*_vit)->render();
	}
}

void item_class_manager::add_items_init(float x, float y, int numbering, int vol, bool equip)
{
	item_class* temp = new item_class;
	item_search(temp, numbering, x, y, vol, equip);
	_vt.push_back(temp);
}
void item_class_manager::eraser(int arr)
{
	_vt.erase(_vt.begin() + arr);
}

void item_class_manager::item_search(item_class* calling, int num, float init_x, float init_y, int vol, bool equip)
{
	switch (num)
	{
		//검
	case 0:
		calling->setting_items(IMAGEMANAGER->findImage("검"),
			"검", "명검이다. 매우 아프다.",
			0,
			init_x,
			init_y,
			vol,
			weapon,
			inventory_item,
			equip);
		break;
		//방패
	case 1:
		calling->setting_items(IMAGEMANAGER->findImage("방패"),
			"방패", "방패이다. 매우 견고하다.",
			1,
			init_x,
			init_y,
			vol,
			Armor,
			inventory_item,
			equip
		);
		break;
		//항아리
	case 2:
		calling->setting_items(IMAGEMANAGER->findImage("마법항아리"),
			"마법항아리", "모든지 흡수한 후 다시 뱉어낸다",
			2,
			init_x,
			init_y,
			vol,
			special_item,
			inventory_item,
			equip
		);
		break;
		//지팡이
	case 3:
		calling->setting_items(IMAGEMANAGER->findImage("지팡이"),
			"지팡이", "요술 지팡이, 모든지 반대로 뒤집니다.",
			3,
			init_x,
			init_y,
			vol,
			special_item,
			inventory_item,
			equip
		);
		break;
		//빈병
	case 4:
		calling->setting_items(IMAGEMANAGER->findImage("빈병"),
			"빈병", "무언가를 담을 수 있다",
			4,
			init_x,
			init_y,
			vol,
			Interaction_item,
			inventory_item,
			equip
		);
		break;
		//요정병
	case 5:
		calling->setting_items(IMAGEMANAGER->findImage("요정병"),
			"요정병", "요정이 들어 있다. 위험할때 도와주는 친구",
			5,
			init_x,
			init_y,
			vol,
			Interaction_item,
			inventory_item,
			equip
		);
		break;
		//폭탄
	case 6:
		calling->setting_items(IMAGEMANAGER->findImage("폭탄"),
			"폭탄", "폭탄이다. 매우 강하다.",
			6,
			init_x,
			init_y,
			vol,
			using_item,
			inventory_item,
			equip
		);
		break;
		//키
	case 7:
		calling->setting_items(IMAGEMANAGER->findImage("키"),
			"키", "잠긴 문을 열수 있는 열쇠이다.",
			7,
			init_x,
			init_y,
			vol,
			using_item,
			inventory_item,
			equip
		);
		break;
		//보스방키
	case 8:
		calling->setting_items(IMAGEMANAGER->findImage("보스방키"),
			"보스방키", "보스 방문을 열수 있는 키이다.",
			8,
			init_x,
			init_y,
			vol,
			using_item,
			inventory_map,
			equip
		);
		break;
		//하트추가
	case 9:
		calling->setting_items(IMAGEMANAGER->findImage("하트추가"),
			"하트", "생명력을 올려준다.",
			9,
			init_x,
			init_y,
			vol,
			using_item,
			inventory_item,
			equip
		);
		break;
		//초록루비
	case 10:
		calling->setting_items(IMAGEMANAGER->findImage("초록루비"),
			"초록색 루비", " 1 루비 가치 이다.",
			10,
			init_x,
			init_y,
			vol,
			using_item,
			inventory_item,
			equip
		);
		break;
		//파란루비
	case 11:
		calling->setting_items(IMAGEMANAGER->findImage("파란루비"),
			"파란색 루비", " 5 루비의 가치이다. ",
			11,
			init_x,
			init_y,
			vol,
			using_item,
			inventory_item,
			equip
		);
		break;
		//빨간루비
	case 12:
		calling->setting_items(IMAGEMANAGER->findImage("빨강루비"),
			"빨강색 루비", " 10 루비의 가치이다. ",
			12,
			init_x,
			init_y,
			vol,
			using_item,
			inventory_item,
			equip
		);
		break;
	}
}
