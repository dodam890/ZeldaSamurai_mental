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
		//��
	case 0:
		calling->setting_items(IMAGEMANAGER->findImage("��"),
			"��", "����̴�. �ſ� ������.",
			0,
			init_x,
			init_y,
			vol,
			weapon,
			inventory_item,
			equip);
		break;
		//����
	case 1:
		calling->setting_items(IMAGEMANAGER->findImage("����"),
			"����", "�����̴�. �ſ� �߰��ϴ�.",
			1,
			init_x,
			init_y,
			vol,
			Armor,
			inventory_item,
			equip
		);
		break;
		//�׾Ƹ�
	case 2:
		calling->setting_items(IMAGEMANAGER->findImage("�����׾Ƹ�"),
			"�����׾Ƹ�", "����� ����� �� �ٽ� ����",
			2,
			init_x,
			init_y,
			vol,
			special_item,
			inventory_item,
			equip
		);
		break;
		//������
	case 3:
		calling->setting_items(IMAGEMANAGER->findImage("������"),
			"������", "��� ������, ����� �ݴ�� �����ϴ�.",
			3,
			init_x,
			init_y,
			vol,
			special_item,
			inventory_item,
			equip
		);
		break;
		//��
	case 4:
		calling->setting_items(IMAGEMANAGER->findImage("��"),
			"��", "���𰡸� ���� �� �ִ�",
			4,
			init_x,
			init_y,
			vol,
			Interaction_item,
			inventory_item,
			equip
		);
		break;
		//������
	case 5:
		calling->setting_items(IMAGEMANAGER->findImage("������"),
			"������", "������ ��� �ִ�. �����Ҷ� �����ִ� ģ��",
			5,
			init_x,
			init_y,
			vol,
			Interaction_item,
			inventory_item,
			equip
		);
		break;
		//��ź
	case 6:
		calling->setting_items(IMAGEMANAGER->findImage("��ź"),
			"��ź", "��ź�̴�. �ſ� ���ϴ�.",
			6,
			init_x,
			init_y,
			vol,
			using_item,
			inventory_item,
			equip
		);
		break;
		//Ű
	case 7:
		calling->setting_items(IMAGEMANAGER->findImage("Ű"),
			"Ű", "��� ���� ���� �ִ� �����̴�.",
			7,
			init_x,
			init_y,
			vol,
			using_item,
			inventory_item,
			equip
		);
		break;
		//������Ű
	case 8:
		calling->setting_items(IMAGEMANAGER->findImage("������Ű"),
			"������Ű", "���� �湮�� ���� �ִ� Ű�̴�.",
			8,
			init_x,
			init_y,
			vol,
			using_item,
			inventory_map,
			equip
		);
		break;
		//��Ʈ�߰�
	case 9:
		calling->setting_items(IMAGEMANAGER->findImage("��Ʈ�߰�"),
			"��Ʈ", "������� �÷��ش�.",
			9,
			init_x,
			init_y,
			vol,
			using_item,
			inventory_item,
			equip
		);
		break;
		//�ʷϷ��
	case 10:
		calling->setting_items(IMAGEMANAGER->findImage("�ʷϷ��"),
			"�ʷϻ� ���", " 1 ��� ��ġ �̴�.",
			10,
			init_x,
			init_y,
			vol,
			using_item,
			inventory_item,
			equip
		);
		break;
		//�Ķ����
	case 11:
		calling->setting_items(IMAGEMANAGER->findImage("�Ķ����"),
			"�Ķ��� ���", " 5 ����� ��ġ�̴�. ",
			11,
			init_x,
			init_y,
			vol,
			using_item,
			inventory_item,
			equip
		);
		break;
		//�������
	case 12:
		calling->setting_items(IMAGEMANAGER->findImage("�������"),
			"������ ���", " 10 ����� ��ġ�̴�. ",
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
