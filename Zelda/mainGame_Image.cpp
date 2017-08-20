#include "stdafx.h"
#include "mainGame.h"

void mainGame::addImage()
{
	//������ �κ� ���� �̹��� -> ����
	addItemImage();

	//���Ǿ� ���� �̹��� -> ����
	addNpcImage();

	//�� ���� �̹��� -> ����, ����
	addMapImage();

}

void mainGame::addItemImage()
{
	IMAGEMANAGER->addImage("�Ͼ�ȭ��", "image/image_pbs/effect/light_effect.bmp", 1200, 800, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����ȭ��", "image/image_pbs/effect/dark_effect.bmp", 1200, 800, true, RGB(255, 0, 255));

	//����ȭ��
	IMAGEMANAGER->addImage("�ΰ�", "image/image_pbs/main/logo.bmp", 790, 325, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�ΰ�1", "image/image_pbs/main/logo_sub1.bmp", 420, 365, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�ΰ�2", "image/image_pbs/main/logo_sub2.bmp", 800, 475, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���ȭ��", "image/image_pbs/main/main_background.bmp", 1200, 800, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�޻�", "image/image_pbs/main/main.bmp", 4800, 800, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�ΰ��ؽ�Ʈ", "image/image_pbs/main/logo_text.bmp", 440, 70, true, RGB(255, 0, 255));

	//ĳ���� ���� ȭ��
	IMAGEMANAGER->addFrameImage("����â�޹��", "image/image_pbs/select/select_background.bmp", 4800, 800, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Ÿ��Ʋ", "image/image_pbs/select/select1.bmp", 800, 110, true, RGB(255, 0, 255));

	//�κ��丮
	IMAGEMANAGER->addImage("�κ��丮���ȭ��", "image/image_pbs/inven/item_background.bmp", 1200, 800, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�κ��丮Ÿ��Ʋ1", "image/image_pbs/inven/item_title.bmp", 560, 110, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�κ��丮����1", "image/image_pbs/inven/item_view.bmp", 1040, 665, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�κ��丮���̺�", "image/image_pbs/inven/inven_save.bmp", 210, 90, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�κ��丮����2", "image/image_pbs/inven/item_view2.bmp", 1040, 665, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("�κ��丮����2_1", "image/image_pbs/inven/item_view_another_2.bmp", 1040, 665, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("�κ��丮sleep", "image/image_pbs/inven/inven_sleep.bmp", 210, 90, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�κ��丮����Ű1", "image/image_pbs/inven/inven_change_key1.bmp", 105, 105, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�κ��丮����Ű2", "image/image_pbs/inven/inven_change_key2.bmp", 105, 105, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�κ��丮Ÿ��Ʋ2", "image/image_pbs/inven/item_title2.bmp", 560, 110, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�κ��丮�����ۼ���", "image/image_pbs/inven/inven_select_item.bmp", 130, 95, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�κ��丮�����ۼ���2", "image/image_pbs/inven/inven_select_item_small.bmp", 120, 95, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�κ��丮Ÿ��Ʋ3", "image/image_pbs/inven/item_title3.bmp", 160, 110, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�κ��丮����3", "image/image_pbs/inven/item_view3.bmp", 1120, 770, true, RGB(255, 0, 255));

	//�ſ� ������ ���� â �̹���
	IMAGEMANAGER->addFrameImage("��������1", "image/image_pbs/inven/point_image_red1.bmp", 80, 40, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��������2", "image/image_pbs/inven/point_image_red2.bmp", 80, 40, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��������3", "image/image_pbs/inven/point_image_red3.bmp", 80, 40, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��������4", "image/image_pbs/inven/point_image_red4.bmp", 80, 40, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ʷϼ���1", "image/image_pbs/inven/point_image_green1.bmp", 80, 40, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ʷϼ���2", "image/image_pbs/inven/point_image_green2.bmp", 80, 40, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ʷϼ���3", "image/image_pbs/inven/point_image_green3.bmp", 80, 40, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ʷϼ���4", "image/image_pbs/inven/point_image_green4.bmp", 80, 40, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��ưz", "image/image_pbs/inven/butten_z.bmp", 60, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��ưx", "image/image_pbs/inven/butten_x.bmp", 60, 70, true, RGB(255, 0, 255));

	//������
	IMAGEMANAGER->addImage("�ʷϷ��", "image/image_pbs/items/money1.bmp", 35, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�Ķ����", "image/image_pbs/items/money2.bmp", 35, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�������", "image/image_pbs/items/money3.bmp", 35, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��ź", "image/image_pbs/items/bomb.bmp", 60, 80, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��", "image/image_pbs/items/bowl.bmp", 60, 75, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������", "image/image_pbs/items/bowl_in_pin.bmp", 60, 75, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������Ű", "image/image_pbs/items/boss_key.bmp", 80, 80, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Ű", "image/image_pbs/items/key.bmp", 40, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��Ʈ�߰�", "image/image_pbs/items/HP_plus.bmp", 55, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�����׾Ƹ�", "image/image_pbs/items/item_sp.bmp", 80, 75, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����", "image/image_pbs/items/Shield.bmp", 70, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������", "image/image_pbs/items/steak.bmp", 65, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��", "image/image_pbs/items/sword.bmp", 80, 80, true, RGB(255, 0, 255));

	//shop
	//UI
	IMAGEMANAGER->addImage("�����̹���1", "image/image_pbs/shop/shop_inter4.bmp", 477, 327, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���1���", "image/image_pbs/shop/shop_buy_key.bmp", 51, 33, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���1�׸��д�", "image/image_pbs/shop/shop_not_buy_key.bmp", 105, 33, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���1�Ѵ�", "image/image_pbs/shop/shop_upgrade_key.bmp", 51, 33, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���Ŀ��", "image/image_pbs/shop/shop_point1.bmp", 18, 15, true, RGB(255, 0, 255));

	//item_Name
	IMAGEMANAGER->addImage("���ڰ�", "image/image_pbs/shop/����/��.bmp", 16, 19, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���ڹ���", "image/image_pbs/shop/����/����.bmp", 37, 19, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���ڸ����׾Ƹ�", "image/image_pbs/shop/����/�����׾Ƹ�.bmp", 107, 19, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���ڿ��������", "image/image_pbs/shop/����/���������.bmp", 108, 19, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���ں�", "image/image_pbs/shop/����/��.bmp", 15, 19, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������Ʈ", "image/image_pbs/shop/����/��Ʈ.bmp", 40, 19, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���ڹ���", "image/image_pbs/shop/����/����.bmp", 36, 18, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����å", "image/image_pbs/shop/����/å.bmp", 17, 18, true, RGB(255, 0, 255));

	//Rubi
	IMAGEMANAGER->addImage("10000���", "image/image_pbs/shop/����/R10000.bmp", 79, 15, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("5000���", "image/image_pbs/shop/����/R5000.bmp", 67, 15, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("250���", "image/image_pbs/shop/����/250���.bmp", 55, 15, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("200���", "image/image_pbs/shop/����/200���.bmp", 55, 15, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("100���", "image/image_pbs/shop/����/100���.bmp", 55, 15, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("80���", "image/image_pbs/shop/����/80���.bmp", 43, 15, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("70���", "image/image_pbs/shop/����/70���.bmp", 43, 15, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("60���", "image/image_pbs/shop/����/60���.bmp", 43, 15, true, RGB(255, 0, 255));

	//number
	IMAGEMANAGER->addImage("00", "image/image_pbs/UI/0.bmp", 60, 60, TRUE, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("11", "image/image_pbs/UI/1.bmp", 60, 60, TRUE, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("22", "image/image_pbs/UI/2.bmp", 60, 60, TRUE, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("33", "image/image_pbs/UI/3.bmp", 60, 60, TRUE, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("44", "image/image_pbs/UI/4.bmp", 60, 60, TRUE, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("55", "image/image_pbs/UI/5.bmp", 60, 60, TRUE, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("66", "image/image_pbs/UI/6.bmp", 60, 60, TRUE, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("77", "image/image_pbs/UI/7.bmp", 60, 60, TRUE, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("88", "image/image_pbs/UI/8.bmp", 60, 60, TRUE, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("99", "image/image_pbs/UI/9.bmp", 60, 60, TRUE, RGB(255, 0, 255));


	//map

	IMAGEMANAGER->addImage("town_map", "image/image_pbs/map/town.bmp", 528, 360, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("zelda_map_icon", "image/image_pbs/map/zelda_face.bmp", 32, 32, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("����", "image/image_pbs/items/ring.bmp", 56, 46, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("å", "image/image_pbs/items/book.bmp", 56, 64, true, RGB(255, 0, 255));
}

void mainGame::addNpcImage()
{
	//��������npc
	IMAGEMANAGER->addFrameImage("npcUncleDown", "image/npc/npcUncleDown.bmp", 320, 140, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("npcUncleLeft", "image/npc/npcUncleLeft.bmp", 320, 140, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("npcUncleRight", "image/npc/npcUncleRight.bmp", 320, 140, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("npcUncleUp", "image/npc/npcUncleUp.bmp", 320, 140, 4, 1, true, RGB(255, 0, 255));

	//�����npc
	IMAGEMANAGER->addFrameImage("npcBandDown", "image/npc/npcBandDown.bmp", 360, 150, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("npcBandLeft", "image/npc/npcBandLeft.bmp", 360, 150, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("npcBandRight", "image/npc/npcBandRight.bmp", 360, 150, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("npcBandUp", "image/npc/npcBandUp.bmp", 360, 150, 4, 1, true, RGB(255, 0, 255));

	//�����Ӹ�npc
	IMAGEMANAGER->addFrameImage("npcBrownDown", "image/npc/npcManDown.bmp", 320, 130, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("npcBrownLeft", "image/npc/npcManLeft.bmp", 320, 130, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("npcBrownRight", "image/npc/npcManRight.bmp", 320, 130, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("npcBrownUp", "image/npc/npcManUp.bmp", 320, 130, 4, 1, true, RGB(255, 0, 255));

	//������npc
	IMAGEMANAGER->addFrameImage("npcElfDown", "image/npc/npcElfDown.bmp", 320, 130, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("npcElfLeft", "image/npc/npcElfLeft.bmp", 320, 130, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("npcElfRight", "image/npc/npcElfRight.bmp", 320, 130, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("npcElfUp", "image/npc/npcElfUp.bmp", 320, 130, 4, 1, true, RGB(255, 0, 255));

	//�ݹ߿���npc
	IMAGEMANAGER->addFrameImage("npcGoldDown", "image/npc/npcGoldDown.bmp", 320, 125, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("npcGoldLeft", "image/npc/npcGoldLeft.bmp", 320, 125, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("npcGoldRight", "image/npc/npcGoldRight.bmp", 320, 125, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("npcGoldUp", "image/npc/npcGoldUp.bmp", 320, 125, 4, 1, true, RGB(255, 0, 255));

	//�Ҿƹ���npc
	IMAGEMANAGER->addFrameImage("npcGrandFaDown", "image/npc/npcGrandFaDown.bmp", 360, 120, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("npcGrandFaLeft", "image/npc/npcGrandFaLeft.bmp", 360, 120, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("npcGrandFaRight", "image/npc/npcGrandFaRight.bmp", 360, 120, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("npcGrandFaUp", "image/npc/npcGrandFaUp.bmp", 360, 120, 4, 1, true, RGB(255, 0, 255));

	//�ҸӴ�npc
	IMAGEMANAGER->addFrameImage("npcGrandMaDown", "image/npc/npcGrandMaDown.bmp", 320, 110, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("npcGrandMaLeft", "image/npc/npcGrandMaLeft.bmp", 320, 110, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("npcGrandMaRight", "image/npc/npcGrandMaRight.bmp", 320, 110, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("npcGrandMaUp", "image/npc/npcGrandMaUp.bmp", 320, 110, 4, 1, true, RGB(255, 0, 255));

	//����npc
	IMAGEMANAGER->addFrameImage("npcGuardDown", "image/npc/guardDown.bmp", 320, 145, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("npcGuardLeft", "image/npc/guardLeft.bmp", 300, 140, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("npcGuardRight", "image/npc/guardRight.bmp", 300, 140, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("npcGuardUp", "image/npc/guardUp.bmp", 360, 145, 4, 1, true, RGB(255, 0, 255));


	//---------------- ������� ����Ʈ ���� npc ----------------------

	//��������
	IMAGEMANAGER->addFrameImage("npcLinkDown", "image/npc/npcLinkDown.bmp", 1050, 255, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("npcLinkTalk", "image/npc/npcLinkTalk.bmp", 580, 240, 4, 1, true, RGB(255, 0, 255));

	//���
	IMAGEMANAGER->addFrameImage("npcMasterDown", "image/npc/npcMasterDown.bmp", 160, 130, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("npcMasterTalk", "image/npc/npcMasterTalk.bmp", 420, 135, 4, 1, true, RGB(255, 0, 255));

	//����������
	IMAGEMANAGER->addFrameImage("npcShopDown", "image/npc/npcShopDown.bmp", 1265, 150, 11, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("npcShopTalk", "image/npc/npcShopTalk.bmp", 420, 150, 4, 1, true, RGB(255, 0, 255));

	//-------------------- �ؽ�Ʈ ���� ---------------------------
	IMAGEMANAGER->addImage("textBox", "image/npc/textBox.bmp", 1167, 250, true, RGB(255, 0, 255));
}

void mainGame::addMapImage()
{	
	//��� �̹���
	IMAGEMANAGER->addImage("TOWN_BACKGROUND", "image/map/TOWN_BACKGROUND.bmp", 5020, 3440, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("TOWN_BACKGROUND_PIXELCOLLISION", "image/map/TOWN_BACKGROUND_PIXELCOLLISION.bmp", 5020, 3440, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("STORE", "image/map/STORE.bmp", 2400, 800, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("STORE_PIXELCOLLISION", "image/map/STORE_PIXELCOLLISION.bmp", 2400, 800, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("STORE_DOOR", "image/map/STORE_DOOR.bmp", 2400, 800, true, RGB(255, 0, 255));

	//�� ����Ʈ
	IMAGEMANAGER->addImage("BLACK", "image/map/BLACK.bmp", 1200, 800, true, RGB(255, 0, 255));

	//����
	IMAGEMANAGER->addImage("MAPTOOL_BACKGROUND", "image/MAPTOOL_BACKGROUND.bmp", 1200, 800, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("MAPTOOL_ARROW", "image/MAPTOOL_ARROW.bmp", 1200, 800, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("MAPTOOL_FRAME", "image/MAPTOOL_FRAME.bmp", 1200, 800, true, RGB(255, 0, 255));

	//������Ʈ �̹���
	IMAGEMANAGER->addImage("TIL.E_ROCK", "image/map/TILE_ROCK.bmp", 80, 80, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("OPEN_CHEST", "image/map/OPEN_CHEST.bmp", 80, 80, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("TILE_BUTTON_DOWN", "image/map/TILE_BUTTON_DOWN.bmp", 80, 80, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("TILE", "image/map/TILE.bmp", 80, 80, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("OBJECT_BIG_CHEST", "image/map/OBJECT_BIG_CHEST.bmp", 640, 190, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("TILE_FIRE", "image/map/TILE_FIRE.bmp", 320, 80, 4, 1, true, RGB(255, 0, 255));

	//�� ������
	IMAGEMANAGER->addFrameImage("TILE_WATER_B", "image/map/TILE_WATER_B.bmp", 320, 80, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("TILE_WATER_EDGE_LB", "image/map/TILE_WATER_EDGE_LB.bmp", 320, 80, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("TILE_WATER_EDGE_LT", "image/map/TILE_WATER_EDGE_LT.bmp", 320, 80, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("TILE_WATER_EDGE_RB", "image/map/TILE_WATER_EDGE_RB.bmp", 320, 80, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("TILE_WATER_EDGE_RT", "image/map/TILE_WATER_EDGE_RT.bmp", 320, 80, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("TILE_WATER_L", "image/map/TILE_WATER_L.bmp", 320, 80, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("TILE_WATER_LB", "image/map/TILE_WATER_LB.bmp", 320, 80, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("TILE_WATER_LT", "image/map/TILE_WATER_LT.bmp", 320, 80, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("TILE_WATER_R", "image/map/TILE_WATER_R.bmp", 320, 80, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("TILE_WATER_RB", "image/map/TILE_WATER_RB.bmp", 320, 80, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("TILE_WATER_RT", "image/map/TILE_WATER_RT.bmp", 320, 80, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("TILE_WATER_T", "image/map/TILE_WATER_T.bmp", 320, 80, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("TILE_WATER_WAVE_L", "image/map/TILE_WATER_WAVE_L.bmp", 320, 80, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("TILE_WATER_WAVE_R", "image/map/TILE_WATER_WAVE_R.bmp", 320, 80, 4, 1, true, RGB(255, 0, 255));
}

void mainGame::addSound()
{
	SOUNDMANAGER->addSound("���θ޴�����", "sound/���θ޴�.mp3", TRUE, TRUE);

	//�޴����û���
	SOUNDMANAGER->addSound("�޴�Ŀ��", "sound/MC_Menu_Cursor.wav", TRUE, FALSE);
	SOUNDMANAGER->addSound("�޴�Ŀ��2", "sound/MC_Menu_Cursor2.wav", TRUE, FALSE);
	SOUNDMANAGER->addSound("�޴������", "sound/MC_Menu_Erase.wav", TRUE, FALSE);
	SOUNDMANAGER->addSound("�޴�����", "sound/MC_Menu_Select.wav", TRUE, FALSE);
	SOUNDMANAGER->addSound("���þ�����", "sound/MC_Select_Screen.mp3", TRUE, TRUE);

	//�������� ����
	SOUNDMANAGER->addSound("��������", "sound/MC_Syrups_Shop.mp3", TRUE, TRUE);
	SOUNDMANAGER->addSound("��������", "sound/MC_Hyrule_Town.mp3", TRUE, TRUE);
	SOUNDMANAGER->addSound("����������", "sound/MC_Hyrule_Field.mp3", TRUE, TRUE);
	SOUNDMANAGER->addSound("����������", "sound/MC_House.mp3", TRUE, TRUE);

	//���ٰ��û���
	SOUNDMANAGER->addSound("���ٰȱ�", "sound/MC_Link_Run.wav", TRUE, FALSE);
	SOUNDMANAGER->addSound("���ٰ�ȸ���Ҹ�", "sound/MC_Link_Sword_Spin.wav", TRUE, FALSE);
	SOUNDMANAGER->addSound("����ȸ���������", "sound/MC_Link_Sword_Spin2.wav", TRUE, FALSE);
	SOUNDMANAGER->addSound("���ٰ˱⺻�Ҹ�", "sound/MC_Link_Sword.wav", TRUE, FALSE);
	SOUNDMANAGER->addSound("���ٱ⺻�������", "sound/MC_Link_Sword1.wav", TRUE, FALSE);
	SOUNDMANAGER->addSound("���ٹ��йݻ�", "sound/MC_Link_Shield_Deflect.wav", TRUE, FALSE);
	SOUNDMANAGER->addSound("���ٹ��е��", "sound/MC_Link_Shield.wav", TRUE, FALSE);
	SOUNDMANAGER->addSound("���ٱ�����", "sound/MC_Link_Roll.wav", TRUE, FALSE);
	SOUNDMANAGER->addSound("���ٹб�", "sound/MC_Link_Push.wav", TRUE, FALSE);
	SOUNDMANAGER->addSound("���ٴ�ħ", "sound/MC_Link_Hurt.wav", TRUE, FALSE);
	SOUNDMANAGER->addSound("�������", "sound/MC_Link_Grab.wav", TRUE, FALSE);
	SOUNDMANAGER->addSound("����ü�³���", "sound/MC_LowHealth.wav", TRUE, TRUE);
	SOUNDMANAGER->addSound("��������", "sound/MC_Link_Die_Tune.wav", TRUE, FALSE);
	SOUNDMANAGER->addSound("����Į�κ�ĥ��", "sound/MC_Sword_TapBombWall.wav", TRUE, FALSE);
	SOUNDMANAGER->addSound("����ü�¾�", "sound/MC_Heart.wav", TRUE, FALSE);

	//�����۰��û���
	SOUNDMANAGER->addSound("������", "sound/MC_Rupee.wav", TRUE, FALSE);
	SOUNDMANAGER->addSound("��񶳾���", "sound/MC_Rupee_Bounce.wav", TRUE, FALSE);
	SOUNDMANAGER->addSound("ü�¾�����", "sound/MC_Heart_Bounce.wav", TRUE, FALSE);
	SOUNDMANAGER->addSound("���������", "sound/MC_Key_Appear.wav", TRUE, FALSE);

	//��ȭ���û���
	SOUNDMANAGER->addSound("��ȭâ�Ӷ�", "sound/MC_Text_Open.wav", TRUE, FALSE);
	SOUNDMANAGER->addSound("��ȭâ����", "sound/MC_Text_Close.wav", TRUE, FALSE);
	SOUNDMANAGER->addSound("���", "sound/MC_CastleGuard_Hey.wav", TRUE, FALSE);

	//�������û���
	SOUNDMANAGER->addSound("��������", "sound/MC_Inside_a_Cave.mp3", TRUE, TRUE);
	SOUNDMANAGER->addSound("������", "sound/MC_Door2.wav", TRUE, FALSE);
	SOUNDMANAGER->addSound("������", "sound/MC_Door_Close.wav", TRUE, FALSE);
	SOUNDMANAGER->addSound("���ڳ�Ÿ��", "sound/MC_Chest_Appear.wav", TRUE, FALSE);
	SOUNDMANAGER->addSound("���ڿ���", "sound/MC_Chest_Open.wav", TRUE, FALSE);
	SOUNDMANAGER->addSound("�����Ա�����", "sound/MC_DungeonDoor.wav", TRUE, FALSE);
	SOUNDMANAGER->addSound("���ھ����۾���", "sound/MC_Fanfare_Item.wav", TRUE, FALSE);
	SOUNDMANAGER->addSound("������", "sound/MC_FlameLantern_On.wav", TRUE, FALSE);
	SOUNDMANAGER->addSound("�Ҳ���", "sound/MC_FlameLantern_Off.wav", TRUE, FALSE);

	//���ʹ̰��û���
	SOUNDMANAGER->addSound("���ʹ��ǰ�", "sound/MC_Enemy_Hit.wav", TRUE, FALSE);
	SOUNDMANAGER->addSound("���ʹ�����", "sound/MC_Enemy_Jump.wav", TRUE, FALSE);
	SOUNDMANAGER->addSound("���ʹ�����", "sound/MC_Enemy_Kill.wav", TRUE, FALSE);
}
