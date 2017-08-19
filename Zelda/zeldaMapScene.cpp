#include "stdafx.h"
#include "zeldaMapScene.h"

zeldaMapScene::zeldaMapScene() :
	_camera(NULL)
{
}

zeldaMapScene::~zeldaMapScene()
{
}

HRESULT zeldaMapScene::init()
{
	_camera = new camera;
	_camera->init();

	_link = new player;
	_link->init(_camera);

	_inven = new inven_all;
	_inven->init();
	_is_inven = false;
	effect_alpha = 0;

	_sceneEffect = new sceneEffect;
	_sceneEffect->init();

	_isCameraMove = false;
	_isLeft = true;

	createMap();

	_tileMapKind = TILEMAP_ONE;
	_isTileMap = false;

	_rcGoTileMap = RectMakeCenter(_camera->getStartX() + 3480, _camera->getStartY() + 2130, 50, 50);
	_sc = new shop_class;
	_sc->init();


	return S_OK;
}

void zeldaMapScene::release()
{
	_camera->release();
	_zeldaMap[_curMap]->release();
}

void zeldaMapScene::update()
{
	changeTileScene();

	if (_isTileMap)
	{
		_zeldaTileMap[_tileMapKind]->update();
		_link->update(_zeldaTileMap[_tileMapKind]);
	}
	else
	{
		if (_zeldaMap[_curMap]->get_is_talk_shop_npc_who(0) == false)
		{
			_link->update(NULL);
		}

		//타일맵으로 이동 실험.
		_rcGoTileMap = RectMakeCenter(_camera->getStartX() + 3480, _camera->getStartY() + 2130, 50, 50);
		RECT rcTmp;
		if (IntersectRect(&rcTmp, &_rcGoTileMap, &_link->getRect()))
		{
			_isTileMap = true;		
			_camera->setCameraX(0);
			_camera->setCameraY(0);
			_link->setDisX(500);
			_link->setDisY(500);
			_link->setIsInTileMap(true);
		}
	
		if (_is_inven == false)
		{
			_zeldaMap[_curMap]->update();
			_camera->update(_zeldaMap[_curMap]->getMapWidth(), _zeldaMap[_curMap]->getMapHeight());
			rectCollision();

			_link->pixelCollision(_zeldaMap[_curMap]->getPixelImg());

			_sceneEffect->update();

			if (_zeldaMap[STORE]->get_is_talk_shop_npc_who(0) == true)
			{
				_sc->update();
			}

			if (_sc->get_give_item_is_true() == true)
			{
				if (_sc->get_ic()->get_itemtype() != using_item)
				{
					if (_sc->get_ic()->get_itemtype() != Interaction_item)
					{
						if (_inven->get_temp_item12_vol() < 12)
						{
							_inven->add_to_inven(
								_sc->get_ic()->get_image(),
								_sc->get_ic()->get_item_name(),
								_sc->get_ic()->get_item_sub_text(),
								_sc->get_ic()->get_item_num(),
								_sc->get_ic()->get_volume(),
								_sc->get_ic()->get_itemtype(),
								_sc->get_ic()->get_item_where(),
								_sc->get_ic()->get_is_equip()
							);
							_inven->get_vi()[_inven->get_vi().size() - 1]->set_numbering_where(_inven->get_temp_item12_vol());
							_inven->get_iit()->set_inven_v(_inven->get_vi());
							_inven->up_temp_item12_vol();
						}
					}
					else if (_inven->get_temp_item12_vol() == Interaction_item)
					{
						if (_inven->get_temp_Sitem4_vol() < 4)
						{
							_inven->add_to_inven(
								_sc->get_ic()->get_image(),
								_sc->get_ic()->get_item_name(),
								_sc->get_ic()->get_item_sub_text(),
								_sc->get_ic()->get_item_num(),
								_sc->get_ic()->get_volume(),
								_sc->get_ic()->get_itemtype(),
								_sc->get_ic()->get_item_where(),
								_sc->get_ic()->get_is_equip()
							);
							_inven->get_vi()[_inven->get_vi().size() - 1]->set_numbering_where(12 + _inven->get_temp_Sitem4_vol());
							_inven->get_iit()->set_inven_v(_inven->get_vi());
							_inven->up_temp_Sitem4_vol();
						}
					}
				}
				_sc->set_give_item_is_true(false);
			}

			effect_alpha -= 20;
			if (effect_alpha < 0) effect_alpha = 0;
			if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
			{
				effect_alpha = 255;
				_is_inven = true;
			}
		}
		else if (_is_inven == true)
		{
			effect_alpha -= 20;
			if (effect_alpha < 0) effect_alpha = 0;
			if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
			{
				effect_alpha = 255;
				_is_inven = false;
			}
			_inven->update();
		}
	}
}

void zeldaMapScene::render()
{
	if (_isTileMap)
	{
		_zeldaTileMap[_tileMapKind]->render();
	}
	else
	{
		if (_is_inven == false)
		{
			_zeldaMap[_curMap]->render();
			_sceneEffect->render();
			if (_zeldaMap[STORE]->get_is_talk_shop_npc_who(0) == true)
			{
				_sc->render();
			}
			IMAGEMANAGER->findImage("하얀화면")->alphaRender(getMemDC(), 0, 0, effect_alpha);
		}
		else if (_is_inven == true)
		{
			_inven->render();
			IMAGEMANAGER->findImage("하얀화면")->alphaRender(getMemDC(), 0, 0, effect_alpha);
		}

		Rectangle(getMemDC(), _rcGoTileMap.left, _rcGoTileMap.top, _rcGoTileMap.right, _rcGoTileMap.bottom);
	}

	_camera->render();
	_camera->drawCameraPos();
}

void zeldaMapScene::createMap()
{
	_curMap = STORE;

	_zeldaMap[TOWN] = new townMap;
	_zeldaMap[TOWN]->init("TOWN_BACKGROUND", "TOWN_BACKGROUND_PIXELCOLLISION", _camera, _link);

	_zeldaMap[STORE] = new storeMap;
	_zeldaMap[STORE]->init("STORE", "STORE_PIXELCOLLISION", _camera, _link);

	_zeldaTileMap[TILEMAP_ONE] = new zeldaTileMap1;
	_zeldaTileMap[TILEMAP_ONE]->init(_link, _camera, "mapSave01.map", TILEX * TILESIZE, TILEY * TILESIZE);
	
	_zeldaTileMap[TILEMAP_TWO] = new zeldaTileMap2;
	_zeldaTileMap[TILEMAP_TWO]->init(_link, _camera, "mapSave02.map", TILEX * TILESIZE, TILEY * TILESIZE);

	_zeldaTileMap[TILEMAP_THREE] = new zeldaTileMap3;
	_zeldaTileMap[TILEMAP_THREE]->init(_link, _camera, "mapSave03.map", TILEX * TILESIZE, TILEY * TILESIZE);

	_zeldaTileMap[TILEMAP_FOUR] = new zeldaTileMap4;
	_zeldaTileMap[TILEMAP_FOUR]->init(_link, _camera, "mapSave04.map", TILEX * TILESIZE, TILEY * TILESIZE);

	_zeldaTileMap[TILEMAP_BOSS] = new zeldaTileMap5;
	_zeldaTileMap[TILEMAP_BOSS]->init(_link, _camera, "mapSave05.map", TILEX * TILESIZE, TILEY * TILESIZE);
}

void zeldaMapScene::rectCollision()
{
	RECT temp;

	for (int i = 0; i < MAP_RECT_END; i++)
	{
		if (IntersectRect(&temp, &_zeldaMap[_curMap]->getEventRect(i).rc, &_link->getRect()))
		{
			if (i == STORE_NEXTDOOR)
			{
				_isCameraMove = true;
			}
			else
			{
				_link->isMove(false);
				_sceneEffect->setFadeOUT(true);

				//씬 전환 끝나면 씬 체인지
				if (!_sceneEffect->getChangeScene())
				{
					setScene(i);
				}
			}
		}
	}

	if (_isCameraMove)
	{
		_link->isMove(false);

		if (_isLeft)
		{
			_camera->setCameraX(_camera->getCameraX() + 10);

			if (_camera->getCameraX() >= 1200)
			{
				_camera->setCameraX(1200);
				_link->setDisX(_link->getDisX() + 5);

				if (_link->getDisX() >= 1250)
				{
					_link->setDisX(1250);
					_isCameraMove = false;
					_link->isMove(true);
					_isLeft = false;
				}
			}
		}
		else
		{
			_camera->setCameraX(_camera->getCameraX() - 10);

			if (_camera->getCameraX() <= 0)
			{
				_camera->setCameraX(0);
				_link->setDisX(_link->getDisX() - 5);

				if (_link->getDisX() <= 850)
				{
					_link->setDisX(850);
					_isCameraMove = false;
					_link->isMove(true);
					_isLeft = true;
				}
			}
		}
	}
}

void zeldaMapScene::setScene(int num)
{
	_link->setDisX(_zeldaMap[_curMap]->getEventRect(num).x);
	_link->setDisY(_zeldaMap[_curMap]->getEventRect(num).y);

	_camera->setCameraX(_zeldaMap[_curMap]->getEventRect(num).cameraX);
	_camera->setCameraY(_zeldaMap[_curMap]->getEventRect(num).cameraY);

	_curMap = _zeldaMap[_curMap]->getEventRect(num).nextMap;

	_sceneEffect->init();
	_link->isMove(true);
}

void zeldaMapScene::changeTileScene()
{
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD1)) _tileMapKind = TILEMAP_ONE;
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD2)) _tileMapKind = TILEMAP_TWO;
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD3)) _tileMapKind = TILEMAP_THREE;
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD4)) _tileMapKind = TILEMAP_FOUR;
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD5)) _tileMapKind = TILEMAP_BOSS;
}