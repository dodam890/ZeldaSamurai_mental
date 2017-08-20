#include "stdafx.h"
#include "mainGame.h"

void mainGame::addImage()
{
	//아이템 인벤 관련 이미지 -> 범수
	addItemImage();

	//엔피씨 관련 이미지 -> 영주
	addNpcImage();

	//맵 관련 이미지 -> 대일, 예솔
	addMapImage();

}

void mainGame::addItemImage()
{
	IMAGEMANAGER->addImage("하얀화면", "image/image_pbs/effect/light_effect.bmp", 1200, 800, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("검은화면", "image/image_pbs/effect/dark_effect.bmp", 1200, 800, true, RGB(255, 0, 255));

	//시작화면
	IMAGEMANAGER->addImage("로고", "image/image_pbs/main/logo.bmp", 790, 325, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("로고1", "image/image_pbs/main/logo_sub1.bmp", 420, 365, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("로고2", "image/image_pbs/main/logo_sub2.bmp", 800, 475, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("배경화면", "image/image_pbs/main/main_background.bmp", 1200, 800, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("햇살", "image/image_pbs/main/main.bmp", 4800, 800, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("로고텍스트", "image/image_pbs/main/logo_text.bmp", 440, 70, true, RGB(255, 0, 255));

	//캐릭터 선택 화면
	IMAGEMANAGER->addFrameImage("선택창뒷배경", "image/image_pbs/select/select_background.bmp", 4800, 800, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("타이틀", "image/image_pbs/select/select1.bmp", 800, 110, true, RGB(255, 0, 255));

	//인벤토리
	IMAGEMANAGER->addImage("인벤토리배경화면", "image/image_pbs/inven/item_background.bmp", 1200, 800, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("인벤토리타이틀1", "image/image_pbs/inven/item_title.bmp", 560, 110, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("인벤토리내용1", "image/image_pbs/inven/item_view.bmp", 1040, 665, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("인벤토리세이브", "image/image_pbs/inven/inven_save.bmp", 210, 90, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("인벤토리내용2", "image/image_pbs/inven/item_view2.bmp", 1040, 665, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("인벤토리내용2_1", "image/image_pbs/inven/item_view_another_2.bmp", 1040, 665, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("인벤토리sleep", "image/image_pbs/inven/inven_sleep.bmp", 210, 90, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("인벤토리변경키1", "image/image_pbs/inven/inven_change_key1.bmp", 105, 105, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("인벤토리변경키2", "image/image_pbs/inven/inven_change_key2.bmp", 105, 105, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("인벤토리타이틀2", "image/image_pbs/inven/item_title2.bmp", 560, 110, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("인벤토리아이템선택", "image/image_pbs/inven/inven_select_item.bmp", 130, 95, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("인벤토리아이템선택2", "image/image_pbs/inven/inven_select_item_small.bmp", 120, 95, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("인벤토리타이틀3", "image/image_pbs/inven/item_title3.bmp", 160, 110, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("인벤토리내용3", "image/image_pbs/inven/item_view3.bmp", 1120, 770, true, RGB(255, 0, 255));

	//매우 조잡한 선택 창 이미지
	IMAGEMANAGER->addFrameImage("빨간선택1", "image/image_pbs/inven/point_image_red1.bmp", 80, 40, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("빨간선택2", "image/image_pbs/inven/point_image_red2.bmp", 80, 40, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("빨간선택3", "image/image_pbs/inven/point_image_red3.bmp", 80, 40, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("빨간선택4", "image/image_pbs/inven/point_image_red4.bmp", 80, 40, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("초록선택1", "image/image_pbs/inven/point_image_green1.bmp", 80, 40, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("초록선택2", "image/image_pbs/inven/point_image_green2.bmp", 80, 40, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("초록선택3", "image/image_pbs/inven/point_image_green3.bmp", 80, 40, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("초록선택4", "image/image_pbs/inven/point_image_green4.bmp", 80, 40, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("버튼z", "image/image_pbs/inven/butten_z.bmp", 60, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("버튼x", "image/image_pbs/inven/butten_x.bmp", 60, 70, true, RGB(255, 0, 255));

	//아이템
	IMAGEMANAGER->addImage("초록루비", "image/image_pbs/items/money1.bmp", 35, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("파란루비", "image/image_pbs/items/money2.bmp", 35, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("빨강루비", "image/image_pbs/items/money3.bmp", 35, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("폭탄", "image/image_pbs/items/bomb.bmp", 60, 80, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("빈병", "image/image_pbs/items/bowl.bmp", 60, 75, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("요정병", "image/image_pbs/items/bowl_in_pin.bmp", 60, 75, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("보스방키", "image/image_pbs/items/boss_key.bmp", 80, 80, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("키", "image/image_pbs/items/key.bmp", 40, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("하트추가", "image/image_pbs/items/HP_plus.bmp", 55, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("마법항아리", "image/image_pbs/items/item_sp.bmp", 80, 75, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("방패", "image/image_pbs/items/Shield.bmp", 70, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("지팡이", "image/image_pbs/items/steak.bmp", 65, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("검", "image/image_pbs/items/sword.bmp", 80, 80, true, RGB(255, 0, 255));

	//shop
	//UI
	IMAGEMANAGER->addImage("상점이미지1", "image/image_pbs/shop/shop_inter4.bmp", 477, 327, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("대답1산다", "image/image_pbs/shop/shop_buy_key.bmp", 51, 33, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("대답1그만둔다", "image/image_pbs/shop/shop_not_buy_key.bmp", 105, 33, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("대답1한다", "image/image_pbs/shop/shop_upgrade_key.bmp", 51, 33, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("대답커서", "image/image_pbs/shop/shop_point1.bmp", 18, 15, true, RGB(255, 0, 255));

	//item_Name
	IMAGEMANAGER->addImage("글자검", "image/image_pbs/shop/글자/검.bmp", 16, 19, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("글자방패", "image/image_pbs/shop/글자/방패.bmp", 37, 19, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("글자마법항아리", "image/image_pbs/shop/글자/마법항아리.bmp", 107, 19, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("글자요술지팡이", "image/image_pbs/shop/글자/요술지팡이.bmp", 108, 19, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("글자병", "image/image_pbs/shop/글자/병.bmp", 15, 19, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("글자하트", "image/image_pbs/shop/글자/하트.bmp", 40, 19, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("글자반지", "image/image_pbs/shop/글자/반지.bmp", 36, 18, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("글자책", "image/image_pbs/shop/글자/책.bmp", 17, 18, true, RGB(255, 0, 255));

	//Rubi
	IMAGEMANAGER->addImage("10000루비", "image/image_pbs/shop/글자/R10000.bmp", 79, 15, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("5000루비", "image/image_pbs/shop/글자/R5000.bmp", 67, 15, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("250루비", "image/image_pbs/shop/글자/250루비.bmp", 55, 15, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("200루비", "image/image_pbs/shop/글자/200루비.bmp", 55, 15, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("100루비", "image/image_pbs/shop/글자/100루비.bmp", 55, 15, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("80루비", "image/image_pbs/shop/글자/80루비.bmp", 43, 15, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("70루비", "image/image_pbs/shop/글자/70루비.bmp", 43, 15, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("60루비", "image/image_pbs/shop/글자/60루비.bmp", 43, 15, true, RGB(255, 0, 255));

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

	IMAGEMANAGER->addImage("반지", "image/image_pbs/items/ring.bmp", 56, 46, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("책", "image/image_pbs/items/book.bmp", 56, 64, true, RGB(255, 0, 255));
}

void mainGame::addNpcImage()
{
	//검은모자npc
	IMAGEMANAGER->addFrameImage("npcUncleDown", "image/npc/npcUncleDown.bmp", 320, 140, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("npcUncleLeft", "image/npc/npcUncleLeft.bmp", 320, 140, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("npcUncleRight", "image/npc/npcUncleRight.bmp", 320, 140, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("npcUncleUp", "image/npc/npcUncleUp.bmp", 320, 140, 4, 1, true, RGB(255, 0, 255));

	//헤어밴드npc
	IMAGEMANAGER->addFrameImage("npcBandDown", "image/npc/npcBandDown.bmp", 360, 150, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("npcBandLeft", "image/npc/npcBandLeft.bmp", 360, 150, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("npcBandRight", "image/npc/npcBandRight.bmp", 360, 150, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("npcBandUp", "image/npc/npcBandUp.bmp", 360, 150, 4, 1, true, RGB(255, 0, 255));

	//갈색머리npc
	IMAGEMANAGER->addFrameImage("npcBrownDown", "image/npc/npcManDown.bmp", 320, 130, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("npcBrownLeft", "image/npc/npcManLeft.bmp", 320, 130, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("npcBrownRight", "image/npc/npcManRight.bmp", 320, 130, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("npcBrownUp", "image/npc/npcManUp.bmp", 320, 130, 4, 1, true, RGB(255, 0, 255));

	//뾰족귀npc
	IMAGEMANAGER->addFrameImage("npcElfDown", "image/npc/npcElfDown.bmp", 320, 130, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("npcElfLeft", "image/npc/npcElfLeft.bmp", 320, 130, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("npcElfRight", "image/npc/npcElfRight.bmp", 320, 130, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("npcElfUp", "image/npc/npcElfUp.bmp", 320, 130, 4, 1, true, RGB(255, 0, 255));

	//금발여자npc
	IMAGEMANAGER->addFrameImage("npcGoldDown", "image/npc/npcGoldDown.bmp", 320, 125, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("npcGoldLeft", "image/npc/npcGoldLeft.bmp", 320, 125, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("npcGoldRight", "image/npc/npcGoldRight.bmp", 320, 125, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("npcGoldUp", "image/npc/npcGoldUp.bmp", 320, 125, 4, 1, true, RGB(255, 0, 255));

	//할아버지npc
	IMAGEMANAGER->addFrameImage("npcGrandFaDown", "image/npc/npcGrandFaDown.bmp", 360, 120, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("npcGrandFaLeft", "image/npc/npcGrandFaLeft.bmp", 360, 120, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("npcGrandFaRight", "image/npc/npcGrandFaRight.bmp", 360, 120, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("npcGrandFaUp", "image/npc/npcGrandFaUp.bmp", 360, 120, 4, 1, true, RGB(255, 0, 255));

	//할머니npc
	IMAGEMANAGER->addFrameImage("npcGrandMaDown", "image/npc/npcGrandMaDown.bmp", 320, 110, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("npcGrandMaLeft", "image/npc/npcGrandMaLeft.bmp", 320, 110, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("npcGrandMaRight", "image/npc/npcGrandMaRight.bmp", 320, 110, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("npcGrandMaUp", "image/npc/npcGrandMaUp.bmp", 320, 110, 4, 1, true, RGB(255, 0, 255));

	//병사npc
	IMAGEMANAGER->addFrameImage("npcGuardDown", "image/npc/guardDown.bmp", 320, 145, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("npcGuardLeft", "image/npc/guardLeft.bmp", 300, 140, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("npcGuardRight", "image/npc/guardRight.bmp", 300, 140, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("npcGuardUp", "image/npc/guardUp.bmp", 360, 145, 4, 1, true, RGB(255, 0, 255));


	//---------------- 여기부턴 퀘스트 가능 npc ----------------------

	//대장장이
	IMAGEMANAGER->addFrameImage("npcLinkDown", "image/npc/npcLinkDown.bmp", 1050, 255, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("npcLinkTalk", "image/npc/npcLinkTalk.bmp", 580, 240, 4, 1, true, RGB(255, 0, 255));

	//사부
	IMAGEMANAGER->addFrameImage("npcMasterDown", "image/npc/npcMasterDown.bmp", 160, 130, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("npcMasterTalk", "image/npc/npcMasterTalk.bmp", 420, 135, 4, 1, true, RGB(255, 0, 255));

	//상점아저씨
	IMAGEMANAGER->addFrameImage("npcShopDown", "image/npc/npcShopDown.bmp", 1265, 150, 11, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("npcShopTalk", "image/npc/npcShopTalk.bmp", 420, 150, 4, 1, true, RGB(255, 0, 255));

	//-------------------- 텍스트 관련 ---------------------------
	IMAGEMANAGER->addImage("textBox", "image/npc/textBox.bmp", 1167, 250, true, RGB(255, 0, 255));
}

void mainGame::addMapImage()
{	
	//통맵 이미지
	IMAGEMANAGER->addImage("TOWN_BACKGROUND", "image/map/TOWN_BACKGROUND.bmp", 5020, 3440, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("TOWN_BACKGROUND_PIXELCOLLISION", "image/map/TOWN_BACKGROUND_PIXELCOLLISION.bmp", 5020, 3440, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("STORE", "image/map/STORE.bmp", 2400, 800, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("STORE_PIXELCOLLISION", "image/map/STORE_PIXELCOLLISION.bmp", 2400, 800, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("STORE_DOOR", "image/map/STORE_DOOR.bmp", 2400, 800, true, RGB(255, 0, 255));

	//씬 이펙트
	IMAGEMANAGER->addImage("BLACK", "image/map/BLACK.bmp", 1200, 800, true, RGB(255, 0, 255));

	//맵툴
	IMAGEMANAGER->addImage("MAPTOOL_BACKGROUND", "image/MAPTOOL_BACKGROUND.bmp", 1200, 800, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("MAPTOOL_ARROW", "image/MAPTOOL_ARROW.bmp", 1200, 800, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("MAPTOOL_FRAME", "image/MAPTOOL_FRAME.bmp", 1200, 800, true, RGB(255, 0, 255));

	//오브젝트 이미지
	IMAGEMANAGER->addImage("TIL.E_ROCK", "image/map/TILE_ROCK.bmp", 80, 80, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("OPEN_CHEST", "image/map/OPEN_CHEST.bmp", 80, 80, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("TILE_BUTTON_DOWN", "image/map/TILE_BUTTON_DOWN.bmp", 80, 80, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("TILE", "image/map/TILE.bmp", 80, 80, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("OBJECT_BIG_CHEST", "image/map/OBJECT_BIG_CHEST.bmp", 640, 190, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("TILE_FIRE", "image/map/TILE_FIRE.bmp", 320, 80, 4, 1, true, RGB(255, 0, 255));

	//물 프레임
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
	SOUNDMANAGER->addSound("메인메뉴음악", "sound/메인메뉴.mp3", TRUE, TRUE);

	//메뉴관련사운드
	SOUNDMANAGER->addSound("메뉴커서", "sound/MC_Menu_Cursor.wav", TRUE, FALSE);
	SOUNDMANAGER->addSound("메뉴커서2", "sound/MC_Menu_Cursor2.wav", TRUE, FALSE);
	SOUNDMANAGER->addSound("메뉴지우기", "sound/MC_Menu_Erase.wav", TRUE, FALSE);
	SOUNDMANAGER->addSound("메뉴선택", "sound/MC_Menu_Select.wav", TRUE, FALSE);
	SOUNDMANAGER->addSound("선택씬음악", "sound/MC_Select_Screen.mp3", TRUE, TRUE);

	//마을관련 사운드
	SOUNDMANAGER->addSound("상점음악", "sound/MC_Syrups_Shop.mp3", TRUE, TRUE);
	SOUNDMANAGER->addSound("마을음악", "sound/MC_Hyrule_Town.mp3", TRUE, TRUE);
	SOUNDMANAGER->addSound("마을밖음악", "sound/MC_Hyrule_Field.mp3", TRUE, TRUE);
	SOUNDMANAGER->addSound("젤다집음악", "sound/MC_House.mp3", TRUE, TRUE);

	//젤다관련사운드
	SOUNDMANAGER->addSound("젤다걷기", "sound/MC_Link_Run.wav", TRUE, FALSE);
	SOUNDMANAGER->addSound("젤다검회전소리", "sound/MC_Link_Sword_Spin.wav", TRUE, FALSE);
	SOUNDMANAGER->addSound("젤다회전베기기합", "sound/MC_Link_Sword_Spin2.wav", TRUE, FALSE);
	SOUNDMANAGER->addSound("젤다검기본소리", "sound/MC_Link_Sword.wav", TRUE, FALSE);
	SOUNDMANAGER->addSound("젤다기본베기기합", "sound/MC_Link_Sword1.wav", TRUE, FALSE);
	SOUNDMANAGER->addSound("젤다방패반사", "sound/MC_Link_Shield_Deflect.wav", TRUE, FALSE);
	SOUNDMANAGER->addSound("젤다방패들기", "sound/MC_Link_Shield.wav", TRUE, FALSE);
	SOUNDMANAGER->addSound("젤다구르기", "sound/MC_Link_Roll.wav", TRUE, FALSE);
	SOUNDMANAGER->addSound("젤다밀기", "sound/MC_Link_Push.wav", TRUE, FALSE);
	SOUNDMANAGER->addSound("젤다다침", "sound/MC_Link_Hurt.wav", TRUE, FALSE);
	SOUNDMANAGER->addSound("젤다잡기", "sound/MC_Link_Grab.wav", TRUE, FALSE);
	SOUNDMANAGER->addSound("젤다체력낮음", "sound/MC_LowHealth.wav", TRUE, TRUE);
	SOUNDMANAGER->addSound("젤다죽음", "sound/MC_Link_Die_Tune.wav", TRUE, FALSE);
	SOUNDMANAGER->addSound("젤다칼로벽칠때", "sound/MC_Sword_TapBombWall.wav", TRUE, FALSE);
	SOUNDMANAGER->addSound("젤다체력업", "sound/MC_Heart.wav", TRUE, FALSE);

	//아이템관련사운드
	SOUNDMANAGER->addSound("루비습득", "sound/MC_Rupee.wav", TRUE, FALSE);
	SOUNDMANAGER->addSound("루비떨어짐", "sound/MC_Rupee_Bounce.wav", TRUE, FALSE);
	SOUNDMANAGER->addSound("체력아이템", "sound/MC_Heart_Bounce.wav", TRUE, FALSE);
	SOUNDMANAGER->addSound("열쇠아이템", "sound/MC_Key_Appear.wav", TRUE, FALSE);

	//대화관련사운드
	SOUNDMANAGER->addSound("대화창켤때", "sound/MC_Text_Open.wav", TRUE, FALSE);
	SOUNDMANAGER->addSound("대화창끌때", "sound/MC_Text_Close.wav", TRUE, FALSE);
	SOUNDMANAGER->addSound("경비병", "sound/MC_CastleGuard_Hey.wav", TRUE, FALSE);

	//던전관련사운드
	SOUNDMANAGER->addSound("던전음악", "sound/MC_Inside_a_Cave.mp3", TRUE, TRUE);
	SOUNDMANAGER->addSound("문열림", "sound/MC_Door2.wav", TRUE, FALSE);
	SOUNDMANAGER->addSound("문닫힘", "sound/MC_Door_Close.wav", TRUE, FALSE);
	SOUNDMANAGER->addSound("상자나타남", "sound/MC_Chest_Appear.wav", TRUE, FALSE);
	SOUNDMANAGER->addSound("상자열림", "sound/MC_Chest_Open.wav", TRUE, FALSE);
	SOUNDMANAGER->addSound("던전입구열림", "sound/MC_DungeonDoor.wav", TRUE, FALSE);
	SOUNDMANAGER->addSound("상자아이템얻음", "sound/MC_Fanfare_Item.wav", TRUE, FALSE);
	SOUNDMANAGER->addSound("불켜짐", "sound/MC_FlameLantern_On.wav", TRUE, FALSE);
	SOUNDMANAGER->addSound("불꺼짐", "sound/MC_FlameLantern_Off.wav", TRUE, FALSE);

	//에너미관련사운드
	SOUNDMANAGER->addSound("에너미피격", "sound/MC_Enemy_Hit.wav", TRUE, FALSE);
	SOUNDMANAGER->addSound("에너미점프", "sound/MC_Enemy_Jump.wav", TRUE, FALSE);
	SOUNDMANAGER->addSound("에너미죽음", "sound/MC_Enemy_Kill.wav", TRUE, FALSE);
}
