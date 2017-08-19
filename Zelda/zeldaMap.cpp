#include "stdafx.h"
#include "zeldaMap.h"
#include "camera.h"	
#include "player.h"

zeldaMap::zeldaMap()
{
}

zeldaMap::~zeldaMap()
{
}

HRESULT zeldaMap::init(string strMapImageKey, string strPixelMapImageKey, camera* camera, player* player)
{
	_camera = camera;
	_link = player;

	_mapImg = IMAGEMANAGER->findImage(strMapImageKey);
	_mapPixelImg = IMAGEMANAGER->findImage(strPixelMapImageKey);

	_mapWidth = _mapImg->getWidth();
	_mapHeight = _mapImg->getHeight();

	setAllNpcOnMap();

	//---------- zOrder ----------------
	//せせせせせせせせせせせせせせせせせせせせせせせせせせせせせせせせせせせせせせせせせせせせせせせせせせせせせせせせせせせせせせせせせせせせせせせ
	_npcZorder = new npcZorder;
	_npcZorder->init();

	return S_OK;
}

void zeldaMap::release()   
{

}

void zeldaMap::update()	   
{
	if (get_is_talk_shop_npc_who(0) == false)
	{
		_link->update();
	}
	//---------- zOrder ------------
	if(_kind == TOWN)
		_npcZorder->setTownNpcByZorder(_link, _townNpc, 10);
	else
		_npcZorder->setStoreNpcByZorder(_link, _storeNpc, 3);
}

void zeldaMap::render()	   
{
	_mapImg->render(getMemDC(), _camera->getStartX(), _camera->getStartY());
	//_mapPixelImg->render(getMemDC(), _camera->getStartX(), _camera->getStartY());
	//_link->render();
	_npcZorder->render();
}

void zeldaMap::setAllNpcOnMap()
{
	for (int i = 0; i < 10; i++)
	{
		_townNpc[i] = new npc;
		_townNpc[i]->setPlayerMemoryAdressLink(_link);
	}

	//原聖npc
	_townNpc[0]->init(_camera, "npcUncle", DIRECTION_DOWN, 1748.f, 2068.f, 300, 300);

	_townNpc[1]->init(_camera, "npcBand", DIRECTION_LEFT, 2280.f, 1680.f, 300, 300);

	_townNpc[2]->init(_camera, "npcBrown", DIRECTION_RIGHT, 4070.f, 1570.f, 300, 300);

	_townNpc[3]->init(_camera, "npcElf", DIRECTION_RIGHT, 3900.f, 500.f, 300, 300);

	_townNpc[4]->init(_camera, "npcGold", DIRECTION_RIGHT, 4630.f, 2230.f, 300, 300);

	_townNpc[5]->init(_camera, "npcGrandFa", DIRECTION_RIGHT, 2950.f, 2220.f, 300, 300);

	_townNpc[6]->init(_camera, "npcGrandMa", DIRECTION_RIGHT, 2724.f, 2956.f, 300, 300);

	//井搾佐級
	_townNpc[7]->init(_camera, "npcGuardLeft", DIRECTION_RIGHT, 170.f, 420.f, 400, 400);

	_townNpc[8]->init(_camera, "npcGuardRight", DIRECTION_LEFT, 4860.f, 520.f, 400, 300);

	_townNpc[9]->init(_camera, "npcGuardTop", DIRECTION_DOWN, 2510.f, 300.f, 400, 400);


	for (int i = 0; i < 3; i++)
	{
		_storeNpc[i] = new npc;
		_storeNpc[i]->setPlayerMemoryAdressLink(_link);
	}

	//雌繊
	_storeNpc[0]->init(_camera, "npcShop", DIRECTION_DOWN, 270.f, 260.f, 150, 250);
	_storeNpc[1]->init(_camera, "npcLink", DIRECTION_DOWN, 2050.f, 325.f, 300, 150);
	_storeNpc[2]->init(_camera, "npcMaster", DIRECTION_DOWN, 1500.f, 120.f, 200, 200);
}

bool zeldaMap::get_is_talk_shop_npc_who(int arry)
{
	return _storeNpc[arry]->getTalkOn();
}