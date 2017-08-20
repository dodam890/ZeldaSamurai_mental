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
	loadNumberImg();

	message_x = 650;
	message_y = 150;

	corcer_x = message_x + 120;
	corcer_y = message_y + 406;

	temp_now_pick = 0;
	pick_where = 0;
	click_now = true;

	_rc[0] = RectMake(message_x, message_y, IMAGEMANAGER->findImage("�����̹���1")->getWidth(), IMAGEMANAGER->findImage("�����̹���1")->getHeight());
	_rc[1] = RectMake(message_x + 150, message_y + 400, 51, 33);
	_rc[2] = RectMake(message_x + 250, message_y + 400, 105, 33);

	for (int i = 0; i < 6; i++)
	{
		item_rc[i] = RectMake(message_x + 34, message_y + 26 + i * 46, 412, 40);
	}

	give_item_is_true = false;

	shop_exit = false;

	_ic = new item_class;

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
			corcer_x = message_x + 220;
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
			if (pick_where == 0)
			{
				give_item_is_true = true;

				_ic = buy_what(temp_now_pick);
			}
			if (pick_where == 1)
			{
				shop_exit = true;
			}
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

	scoreRender();
}

void shop_class::select_render(float left, float top, float right, float bottom, int carrent_x, int carrent_y)
{
	IMAGEMANAGER->findImage("��������1")->frameRender(getMemDC(), left, top, carrent_x, carrent_y);
	IMAGEMANAGER->findImage("��������2")->frameRender(getMemDC(), right - IMAGEMANAGER->findImage("��������2")->getFrameWidth() / 6, top, carrent_x, carrent_y);
	IMAGEMANAGER->findImage("��������3")->frameRender(getMemDC(), left, bottom - IMAGEMANAGER->findImage("��������3")->getFrameHeight() / 6, carrent_x, carrent_y);
	IMAGEMANAGER->findImage("��������4")->frameRender(getMemDC(), right - IMAGEMANAGER->findImage("��������4")->getFrameWidth() / 6, bottom - IMAGEMANAGER->findImage("��������4")->getFrameHeight() / 6, carrent_x, carrent_y);
}

item_class* shop_class::buy_what(int arry)
{
	item_class* temp;
	temp = new item_class;

	item_option _io_temp;

	switch (arry)
	{
	case 0:

		_io_temp.ATK = 10;
		_io_temp.ATK_SPEED = 1;
		_io_temp.DEF = 0;
		_io_temp.Price = 200;
		_io_temp.Upgrade = 0;

		temp->setting_items(IMAGEMANAGER->findImage("��"),
			"��", "����̴�. �ſ� ������.",
			0,
			NULL,
			NULL,
			1,
			weapon,
			inventory_item,
			false, _io_temp);
		break;
		//����
	case 1:

		_io_temp.ATK = 0;
		_io_temp.ATK_SPEED = 1;
		_io_temp.DEF = 10;
		_io_temp.Price = 200;
		_io_temp.Upgrade = 0;

		temp->setting_items(IMAGEMANAGER->findImage("����"),
			"����", "�����̴�. �ſ� �߰��ϴ�.",
			1,
			NULL,
			NULL,
			1,
			Armor,
			inventory_item,
			false, _io_temp);
		break;
		//�׾Ƹ�
	case 2:

		_io_temp.ATK = 0;
		_io_temp.ATK_SPEED = 1;
		_io_temp.DEF = 0;
		_io_temp.Price = 250;
		_io_temp.Upgrade = 0;

		temp->setting_items(IMAGEMANAGER->findImage("�����׾Ƹ�"),
			"�����׾Ƹ�", "����� ����� �� �ٽ� ����",
			2,
			NULL,
			NULL,
			1,
			special_item,
			inventory_item,
			false, _io_temp
		);
		break;
		//������
	case 3:

		_io_temp.ATK = 0;
		_io_temp.ATK_SPEED = 1;
		_io_temp.DEF = 0;
		_io_temp.Price = 250;
		_io_temp.Upgrade = 0;

		temp->setting_items(IMAGEMANAGER->findImage("������"),
			"������", "��� ������, ����� �ݴ�� �����ϴ�.",
			3,
			NULL,
			NULL,
			1,
			special_item,
			inventory_item,
			false, _io_temp
		);
		break;
		//��
	case 4:

		_io_temp.ATK = 0;
		_io_temp.ATK_SPEED = 1;
		_io_temp.DEF = 0;
		_io_temp.Price = 70;
		_io_temp.Upgrade = 0;

		temp->setting_items(IMAGEMANAGER->findImage("��"),
			"��", "���𰡸� ���� �� �ִ�",
			4,
			NULL,
			NULL,
			1,
			Interaction_item,
			inventory_item,
			false, _io_temp
		);
		break;
		//��Ʈ�߰�
	case 5:

		_io_temp.ATK = 0;
		_io_temp.ATK_SPEED = 1;
		_io_temp.DEF = 0;
		_io_temp.Price = 60;
		_io_temp.Upgrade = 0;

		temp->setting_items(IMAGEMANAGER->findImage("��Ʈ�߰�"),
			"��Ʈ", "������� �÷��ش�.",
			9,
			NULL,
			NULL,
			1,
			using_item,
			inventory_item,
			false, _io_temp
		);
		break;
	}
	return temp;
}

void shop_class::loadNumberImg()
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

void shop_class::scoreRender()
{
	IMAGEMANAGER->findImage("�ʷϷ��")->render(getMemDC(), WINSIZEX - 1100, 98);

	for (int i = 0; i < 5; i++)
	{
		int nScoreIdx = 0;
		nScoreIdx = P_mon / m_arScore[i].nDiv % m_arScore[i].nRest;
		m_arScore[i].pImg[nScoreIdx]->render(getMemDC(), -i * 40 + WINSIZEX - 900, 104);
	}
}
