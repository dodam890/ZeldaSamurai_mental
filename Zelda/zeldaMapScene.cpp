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
	_tile_inven = false;
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
	_sc->set_inven_money(_inven->get_P_money());
	_sc->set_P_mon(_inven->get_P_money());

	_ugc = new up_grade_complete;
	_ugc->init();
	_ugc->set_my_in(_inven);
	_ugc->set_inven_money(_inven->get_P_money());
	_ugc->set_P_mon(_inven->get_P_money());

	_im = new item_class_manager;
	_im->init();

	return S_OK;
}

void zeldaMapScene::release()
{
	/*SAFE_RELEASE(_camera);
	SAFE_DELETE(_camera);

	SAFE_RELEASE(_inven);
	SAFE_DELETE(_inven);

	SAFE_RELEASE(_sc);
	SAFE_DELETE(_sc);

	SAFE_RELEASE(_sceneEffect);
	SAFE_DELETE(_sceneEffect);

	for (int i = 0; i < MAP_KIND_END; i++)
	{
		SAFE_RELEASE(_zeldaMap[i]);
		SAFE_DELETE(_zeldaMap[i]);
	}*/

	//SAFE_RELEASE(_link);
	//SAFE_DELETE(_link);
	//_zeldaMap[_curMap]->release();
}

void zeldaMapScene::update()
{
	returnToMainMenu();

	changeTileScene();

	if (_isTileMap)
	{
		_zeldaTileMap[_tileMapKind]->update();
		_link->update(_zeldaTileMap[_tileMapKind]);

		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			if (_tile_inven == true)
			{
				_tile_inven = false;
			}
			else if (_tile_inven == false)
			{
				_tile_inven = true;
			}
		}

		if (_tile_inven == true)
		{
			_inven->update();
		}
	}
	else
	{
		if (_zeldaMap[_curMap]->get_is_talk_shop_npc_who(0) == false && _zeldaMap[_curMap]->get_is_talk_shop_npc_who(1) == false)
		{
			_link->update(NULL);
		}

		//if (_curMap == TOWN)
		//{
			//RECT temp;
			//if (IntersectRect(&temp, &_zeldaMap[_curMap]->getEventRect(TOWN_STAGE).rc, &_link->getRect()))
			//{
			//	_isTileMap = true;
			//	_camera->setCameraX(0);
			//	_camera->setCameraY(0);
			//	_link->setDisX(500);
			//	_link->setDisY(500);
			//	_link->setIsInTileMap(true);
			//}
		//}
		
		//_eventRectInfo[TOWN_STAGE].rc = RectMake(1349, 851, 80, 30);
		//_eventRectInfo[TOWN_STAGE].cameraX = 790;
		//_eventRectInfo[TOWN_STAGE].cameraY = 490;
		//_eventRectInfo[TOWN_STAGE].x = 490;
		//_eventRectInfo[TOWN_STAGE].y = 370;

		//Å¸ÀÏ¸ÊÀ¸·Î ÀÌµ¿ ½ÇÇè.
		_rcGoTileMap = RectMakeCenter(_camera->getStartX() + 1370, _camera->getStartY() + 851, 80, 30);

		RECT rcTmp;
		if (IntersectRect(&rcTmp, &_rcGoTileMap, &_link->getRect()))
		{
			_link->setMove(false);
			_sceneEffect->setFadeOUT(true);

			//¾À ÀüÈ¯ ³¡³ª¸é ¾À Ã¼ÀÎÁö
			if (!_sceneEffect->getChangeScene())
			{
				_camera->setCameraX(145);
				_camera->setCameraY(800);
				_link->setDisX(630);
				_link->setDisY(1200);
				_link->setIsInTileMap(true);
				_isTileMap = true;

				//_sceneEffect->init();
				_link->setMove(true);
			}
		}
	
		if (_is_inven == false)
		{
			_zeldaMap[_curMap]->update();
			_camera->update(_zeldaMap[_curMap]->getMapWidth(), _zeldaMap[_curMap]->getMapHeight());
			rectCollision();

			_link->pixelCollision(_zeldaMap[_curMap]->getPixelImg());

			_sceneEffect->update();

			if (_zeldaMap[STORE]->get_is_talk_shop_npc_who(0) == false && _zeldaMap[STORE]->get_is_talk_shop_npc_who(1) == false)
			{
				_ugc->set_P_mon(_inven->get_P_money());
				_sc->set_P_mon(_inven->get_P_money());
			}


			if (_zeldaMap[STORE]->get_is_talk_shop_npc_who(1) == true && _ugc->get_confirm_reset() == false)
			{
				_ugc->set_vi(_inven->get_vi());
				_ugc->set_upgrade_exit(false);
				_ugc->set_confirm_reset(true);
			}
			else if (_zeldaMap[STORE]->get_is_talk_shop_npc_who(1) == false && _ugc->get_confirm_reset() == true)
			{
				_ugc->set_confirm_reset(false);
				_ugc->set_invens_view(upgrade_state_view_standard);
			}
			else if (_zeldaMap[STORE]->get_is_talk_shop_npc_who(1) == true && _ugc->get_confirm_reset() == true)
			{
				_ugc->update();

				if (_ugc->get_upgrade_exit() == true)
				{
					_zeldaMap[STORE]->set_is_talk_shop_npc_who(1, false);
				}
			}


			if (_zeldaMap[STORE]->get_is_talk_shop_npc_who(0) == true)
			{
				_sc->set_shop_exit(false);
				_sc->update();

				if (_sc->get_shop_exit() == true)
				{
					_zeldaMap[STORE]->set_is_talk_shop_npc_who(0, false);
				}
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
								_sc->get_ic()->get_is_equip(),
								_sc->get_ic()->get_item_option());
							_inven->get_vi()[_inven->get_vi().size() - 1]->set_numbering_where(_inven->get_temp_item12_vol());
							_inven->get_iit()->set_inven_v(_inven->get_vi());
							_inven->up_temp_item12_vol();

							_inven->set_M_P_money(_sc->get_ic()->get_item_option().Price);
							_sc->set_inven_money(_inven->get_P_money());
						}
					}
					else if (_sc->get_ic()->get_itemtype() == Interaction_item)
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
								_sc->get_ic()->get_is_equip(),
								_sc->get_ic()->get_item_option()
							);
							_inven->get_vi()[_inven->get_vi().size() - 1]->set_numbering_where(12 + _inven->get_temp_Sitem4_vol());
							_inven->get_iit()->set_inven_v(_inven->get_vi());
							_inven->up_temp_Sitem4_vol();

							_inven->set_M_P_money(_sc->get_ic()->get_item_option().Price);
							_sc->set_inven_money(_inven->get_P_money());
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
	_im->update();

	//À½¾ÇÀç»ý
	if (_curMap == TOWN)
	{
		if (!SOUNDMANAGER->isPlaySound("¸¶À»À½¾Ç"))
			SOUNDMANAGER->play("¸¶À»À½¾Ç", 1.f);
	}
	else if (_curMap == STORE)
	{
		if (!SOUNDMANAGER->isPlaySound("»óÁ¡À½¾Ç"))
			SOUNDMANAGER->play("»óÁ¡À½¾Ç", 1.f);
	}
}

void zeldaMapScene::render()
{
	if (_isTileMap)
	{
		_zeldaTileMap[_tileMapKind]->render();

		if (_tile_inven == true)
		{
			_inven->render();
		}
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
			if (_zeldaMap[STORE]->get_is_talk_shop_npc_who(1) == true)
			{
				_ugc->render();
			}
			IMAGEMANAGER->findImage("ÇÏ¾áÈ­¸é")->alphaRender(getMemDC(), 0, 0, effect_alpha);
		}
		else if (_is_inven == true)
		{
			_inven->render();
			IMAGEMANAGER->findImage("ÇÏ¾áÈ­¸é")->alphaRender(getMemDC(), 0, 0, effect_alpha);
		}

		Rectangle(getMemDC(), _rcGoTileMap.left, _rcGoTileMap.top, _rcGoTileMap.right, _rcGoTileMap.bottom);
	}

	_im->render();

	_camera->render();
	_camera->drawCameraPos();
}

void zeldaMapScene::createMap()
{
	_curMap = TOWN;

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
				_link->setMove(false);
				_sceneEffect->setFadeOUT(true);

				//¾À ÀüÈ¯ ³¡³ª¸é ¾À Ã¼ÀÎÁö
				if (!_sceneEffect->getChangeScene())
				{
					setScene(i);
					//À½¾Ç²¨ÁÜ
					if (SOUNDMANAGER->isPlaySound("¸¶À»À½¾Ç"))
						SOUNDMANAGER->stop("¸¶À»À½¾Ç");
					if (SOUNDMANAGER->isPlaySound("»óÁ¡À½¾Ç"))
						SOUNDMANAGER->stop("»óÁ¡À½¾Ç");
				}
			}
		}
	}

	if (_isCameraMove)
	{
		_link->setMove(false);

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
					_link->setMove(true);
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
					_link->setMove(true);
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
	_link->setMove(true);
}

void zeldaMapScene::changeTileScene()
{
	if (_tileMapKind == TILEMAP_ONE)
	{
		for (int i = 0; i < DOOR_POS_END; i++)
		{
			RECT temp;
			if (IntersectRect(&temp, &_zeldaTileMap[_tileMapKind]->getDoorRect(i).rc, &_link->getRect()))
			{
				setTileScene(i);
			}
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD1)) _tileMapKind = TILEMAP_ONE;
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD2)) _tileMapKind = TILEMAP_TWO;
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD3)) _tileMapKind = TILEMAP_THREE;
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD4)) _tileMapKind = TILEMAP_FOUR;
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD5)) _tileMapKind = TILEMAP_BOSS;
}

void zeldaMapScene::setTileScene(int num)
{
	_link->setDisX(_zeldaTileMap[_tileMapKind]->getDoorRect(num).x);
	_link->setDisY(_zeldaTileMap[_tileMapKind]->getDoorRect(num).y);

	_camera->setCameraX(_zeldaTileMap[_tileMapKind]->getDoorRect(num).cameraX);
	_camera->setCameraY(_zeldaTileMap[_tileMapKind]->getDoorRect(num).cameraY);

	_tileMapKind = _zeldaTileMap[_tileMapKind]->getDoorRect(num).nextMap;

	_sceneEffect->init();
	_link->setMove(true);
}

void zeldaMapScene::returnToMainMenu()
{
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		SCENEMANAGER->changeScene("main_scene");
	}
}
