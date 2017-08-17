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

	_rc[0] = RectMake(message_x, message_y, IMAGEMANAGER->findImage("�����̹���1")->getWidth(), IMAGEMANAGER->findImage("�����̹���1")->getHeight());
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
	IMAGEMANAGER->findImage("�����̹���1")->render(getMemDC(), message_x, message_y);

	if (click_now == true)
	{
		select_render(item_rc[temp_now_pick].left - 16, item_rc[temp_now_pick].top - 10, item_rc[temp_now_pick].right - 18, item_rc[temp_now_pick].bottom - 20, 1, 0);
		IMAGEMANAGER->findImage("���1���")->render(getMemDC(), message_x + 150, message_y + 400);
		IMAGEMANAGER->findImage("���1�׸��д�")->render(getMemDC(), message_x + 250, message_y + 400);
		IMAGEMANAGER->findImage("���Ŀ��")->render(getMemDC(), corcer_x, corcer_y);
	}
	for (int i = 0; i < 6; i++)
	{
		if (i == 0)IMAGEMANAGER->findImage("���ڰ�")->render(getMemDC(), item_rc[i].left + 20, item_rc[i].top + 15),
			IMAGEMANAGER->findImage("200���")->render(getMemDC(), item_rc[i].left + 340, item_rc[i].top + 15);
		if (i == 1)IMAGEMANAGER->findImage("���ڹ���")->render(getMemDC(), item_rc[i].left + 20, item_rc[i].top + 15),
			IMAGEMANAGER->findImage("200���")->render(getMemDC(), item_rc[i].left + 340, item_rc[i].top + 15);
		if (i == 2)IMAGEMANAGER->findImage("���ڸ����׾Ƹ�")->render(getMemDC(), item_rc[i].left + 20, item_rc[i].top + 15),
			IMAGEMANAGER->findImage("250���")->render(getMemDC(), item_rc[i].left + 340, item_rc[i].top + 15);
		if (i == 3)IMAGEMANAGER->findImage("���ڿ��������")->render(getMemDC(), item_rc[i].left + 20, item_rc[i].top + 15),
			IMAGEMANAGER->findImage("250���")->render(getMemDC(), item_rc[i].left + 340, item_rc[i].top + 15);
		if (i == 4)IMAGEMANAGER->findImage("���ں�")->render(getMemDC(), item_rc[i].left + 20, item_rc[i].top + 15),
			IMAGEMANAGER->findImage("70���")->render(getMemDC(), item_rc[i].left + 340, item_rc[i].top + 15);
		if (i == 5)IMAGEMANAGER->findImage("������Ʈ")->render(getMemDC(), item_rc[i].left + 20, item_rc[i].top + 15),
			IMAGEMANAGER->findImage("60���")->render(getMemDC(), item_rc[i].left + 340, item_rc[i].top + 15);
	}
}

void shop_class::select_render(float left, float top, float right, float bottom, int carrent_x, int carrent_y)
{
	IMAGEMANAGER->findImage("��������1")->frameRender(getMemDC(), left, top, carrent_x, carrent_y);
	IMAGEMANAGER->findImage("��������2")->frameRender(getMemDC(), right - IMAGEMANAGER->findImage("��������2")->getFrameWidth() / 6, top, carrent_x, carrent_y);
	IMAGEMANAGER->findImage("��������3")->frameRender(getMemDC(), left, bottom - IMAGEMANAGER->findImage("��������3")->getFrameHeight() / 6, carrent_x, carrent_y);
	IMAGEMANAGER->findImage("��������4")->frameRender(getMemDC(), right - IMAGEMANAGER->findImage("��������4")->getFrameWidth() / 6, bottom - IMAGEMANAGER->findImage("��������4")->getFrameHeight() / 6, carrent_x, carrent_y);
}


//void item_class_manager::item_search(item_class* calling, int num, float init_x, float init_y, int vol, bool equip)
//{
//
//	item_state temp;
//
//	switch (num)
//	{
//		//��
//	case 0:
//
//		temp.ATK = 1;
//		temp.ATK_SPEED = 1.0;
//		temp.critical = 1.5;
//		temp.DEF = 0;
//		temp.price = 100;
//		temp.upgrade = 0;
//
//		calling->setting_items(IMAGEMANAGER->findImage("��"),
//			"��", "����̴�. �ſ� ������.",
//			0,
//			init_x,
//			init_y,
//			vol,
//			weapon,
//			inventory_item,
//			equip,
//			temp);
//		break;
//		//����
//	case 1:
//
//		temp.ATK = 0;
//		temp.ATK_SPEED = 0;
//		temp.critical = 0;
//		temp.DEF = 10;
//		temp.price = 80;
//		temp.upgrade = 0;
//
//		calling->setting_items(IMAGEMANAGER->findImage("����"),
//			"����", "�����̴�. �ſ� �߰��ϴ�.",
//			1,
//			init_x,
//			init_y,
//			vol,
//			Armor,
//			inventory_item,
//			equip,
//			temp);
//		break;
//		//�׾Ƹ�
//	case 2:
//
//		temp.ATK = 0;
//		temp.ATK_SPEED = 0;
//		temp.critical = 0;
//		temp.DEF = 0;
//		temp.price = 150;
//		temp.upgrade = 0;
//
//		calling->setting_items(IMAGEMANAGER->findImage("�����׾Ƹ�"),
//			"�����׾Ƹ�", "����� ����� �� �ٽ� ����",
//			2,
//			init_x,
//			init_y,
//			vol,
//			special_item,
//			inventory_item,
//			equip,
//			temp);
//		break;
//		//������
//	case 3:
//
//		temp.ATK = 0;
//		temp.ATK_SPEED = 0;
//		temp.critical = 0;
//		temp.DEF = 0;
//		temp.price = 150;
//		temp.upgrade = 0;
//
//		calling->setting_items(IMAGEMANAGER->findImage("������"),
//			"������", "��� ������, ����� �ݴ�� �����ϴ�.",
//			3,
//			init_x,
//			init_y,
//			vol,
//			special_item,
//			inventory_item,
//			equip,
//			temp);
//		break;
//		//��
//	case 4:
//
//		temp.ATK = 0;
//		temp.ATK_SPEED = 0;
//		temp.critical = 0;
//		temp.DEF = 0;
//		temp.price = 50;
//		temp.upgrade = 0;
//
//		calling->setting_items(IMAGEMANAGER->findImage("��"),
//			"��", "���𰡸� ���� �� �ִ�",
//			4,
//			init_x,
//			init_y,
//			vol,
//			Interaction_item,
//			inventory_item,
//			equip,
//			temp);
//		break;
//		//������
//	case 5:
//
//		temp.ATK = 0;
//		temp.ATK_SPEED = 0;
//		temp.critical = 0;
//		temp.DEF = 0;
//		temp.price = 250;
//		temp.upgrade = 0;
//
//		calling->setting_items(IMAGEMANAGER->findImage("������"),
//			"������", "������ ��� �ִ�. �����Ҷ� �����ִ� ģ��",
//			5,
//			init_x,
//			init_y,
//			vol,
//			Interaction_item,
//			inventory_item,
//			equip,
//			temp);
//		break;
//		//��ź
//	case 6:
//
//		temp.ATK = 0;
//		temp.ATK_SPEED = 0;
//		temp.critical = 0;
//		temp.DEF = 0;
//		temp.price = 50;
//		temp.upgrade = 0;
//
//		calling->setting_items(IMAGEMANAGER->findImage("��ź"),
//			"��ź", "��ź�̴�. �ſ� ���ϴ�.",
//			6,
//			init_x,
//			init_y,
//			vol,
//			using_item,
//			inventory_item,
//			equip,
//			temp);
//		break;
//		//Ű
//	case 7:
//
//		temp.ATK = 0;
//		temp.ATK_SPEED = 0;
//		temp.critical = 0;
//		temp.DEF = 0;
//		temp.price = 70;
//		temp.upgrade = 0;
//
//		calling->setting_items(IMAGEMANAGER->findImage("Ű"),
//			"Ű", "��� ���� ���� �ִ� �����̴�.",
//			7,
//			init_x,
//			init_y,
//			vol,
//			using_item,
//			inventory_item,
//			equip,
//			temp);
//		break;
//		//������Ű
//	case 8:
//
//		temp.ATK = 0;
//		temp.ATK_SPEED = 0;
//		temp.critical = 0;
//		temp.DEF = 0;
//		temp.price = 200;
//		temp.upgrade = 0;
//
//		calling->setting_items(IMAGEMANAGER->findImage("������Ű"),
//			"������Ű", "���� �湮�� ���� �ִ� Ű�̴�.",
//			8,
//			init_x,
//			init_y,
//			vol,
//			using_item,
//			inventory_map,
//			equip,
//			temp);
//		break;
//		//��Ʈ�߰�
//	case 9:
//
//		temp.ATK = 0;
//		temp.ATK_SPEED = 0;
//		temp.critical = 0;
//		temp.DEF = 0;
//		temp.price = 60;
//		temp.upgrade = 0;
//
//		calling->setting_items(IMAGEMANAGER->findImage("��Ʈ�߰�"),
//			"��Ʈ", "������� �÷��ش�.",
//			9,
//			init_x,
//			init_y,
//			vol,
//			using_item,
//			inventory_item,
//			equip,
//			temp);
//		break;
//		//�ʷϷ��
//	case 10:
//
//		temp.ATK = 0;
//		temp.ATK_SPEED = 0;
//		temp.critical = 0;
//		temp.DEF = 0;
//		temp.price = 1;
//		temp.upgrade = 0;
//
//		calling->setting_items(IMAGEMANAGER->findImage("�ʷϷ��"),
//			"�ʷϻ� ���", " 1 ��� ��ġ �̴�.",
//			10,
//			init_x,
//			init_y,
//			vol,
//			using_item,
//			inventory_item,
//			equip,
//			temp);
//		break;
//		//�Ķ����
//	case 11:
//
//		temp.ATK = 0;
//		temp.ATK_SPEED = 0;
//		temp.critical = 0;
//		temp.DEF = 0;
//		temp.price = 5;
//		temp.upgrade = 0;
//
//		calling->setting_items(IMAGEMANAGER->findImage("�Ķ����"),
//			"�Ķ��� ���", " 5 ����� ��ġ�̴�. ",
//			11,
//			init_x,
//			init_y,
//			vol,
//			using_item,
//			inventory_item,
//			equip,
//			temp);
//		break;
//		//�������
//	case 12:
//
//		temp.ATK = 0;
//		temp.ATK_SPEED = 0;
//		temp.critical = 0;
//		temp.DEF = 0;
//		temp.price = 10;
//		temp.upgrade = 0;
//
//		calling->setting_items(IMAGEMANAGER->findImage("�������"),
//			"������ ���", " 10 ����� ��ġ�̴�. ",
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
