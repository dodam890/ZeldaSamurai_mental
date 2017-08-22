#include "stdafx.h"
#include "c_zeldaTileMap.h"
#include "player.h"

// ----------------------------------------------------------------------------------------------------

HRESULT zeldaTileMap1::init(player* player, camera * camera, const CHAR* pMapSaveFileName, int mapWidth, int mapHeight)
{
	zeldaTileMap::init(player, camera, pMapSaveFileName, mapWidth, mapHeight);

	int j = 0;

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].obj2 == OBJ_POT)
		{
			_potTile[j].rc = _tiles[i].rc;

			j++;
		}
	}

	_em = new enemyManager;
	_em->init(_player, _camera, this);

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].obj == OBJ_OCTOPUS)
		{
			_em->setOcto(_tiles[i].rc.left, _tiles[i].rc.top);
		}
		else if (_tiles[i].obj == OBJ_SNAIL)
		{
			_em->setSnail(_tiles[i].rc.left, _tiles[i].rc.top);
		}
		else if (_tiles[i].obj == OBJ_SLIME)
		{
			_em->setSlime(_tiles[i].rc.left, _tiles[i].rc.top);
		}
	}

	_emZorder = new emZorder;
	_emZorder->init(_em, _player);

	_door[UP].rc = RectMake(720, 150, 80, 30);
	_door[UP].nextMap = TILEMAP_TWO;
	_door[UP].x = 630;
	_door[UP].y = 1200;
	_door[UP].cameraX = 145;
	_door[UP].cameraY = 800;

	_door[DOWN].rc = RectMake(720, 1400, 80, 30);
	_door[DOWN].x = 1250;
	_door[DOWN].y = 790;
	_door[DOWN].cameraX = 790;
	_door[DOWN].cameraY = 510;

	_door[LEFT].rc = RectMake(320, 480, 80, 30);
	_door[LEFT].nextMap = TILEMAP_FOUR;
	_door[LEFT].x = 220;
	_door[LEFT].y = 500;
	_door[LEFT].cameraX = 0;
	_door[LEFT].cameraY = 200;
	
	_door[RIGHT].rc = RectMake(1200, 480, 80, 30);
	_door[RIGHT].nextMap = TILEMAP_FOUR;
	_door[RIGHT].x = 1100;
	_door[RIGHT].y = 500;
	_door[RIGHT].cameraX = 400;
	_door[RIGHT].cameraY = 200;

	return S_OK;
}

void zeldaTileMap1::release()
{
	zeldaTileMap::release();

	_em->release();
}

void zeldaTileMap1::update()
{
	zeldaTileMap::update();

	_door[UP].rc = RectMake(_camera->getStartX() + 720, _camera->getStartY() + 150, 80, 30);
	_door[DOWN].rc = RectMake(_camera->getStartX() + 720, _camera->getStartY() + 1400, 80, 30);
	_door[LEFT].rc = RectMake(_camera->getStartX() + 320, _camera->getStartY() + 480, 80, 30);
	_door[RIGHT].rc = RectMake(_camera->getStartX() + 1200, _camera->getStartY() + 480, 80, 30);

	int j = 0;

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].obj2 == OBJ_POT)
		{
			_potTile[j].rc = _tiles[i].rc;
			
			j++;
		}
	}

	_emZorder->update();
	_em->update();

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		RECT rcTmp;
		if (_tiles[i].obj2 == OBJ_POT)
		{
			if (IntersectRect(&rcTmp, &_tiles[i].rc, &_player->getCrushRect()))
			{
				_tiles[i].obj2 = OBJ_NONE;
				_tiles[i].objFrameX = 0;
				_tiles[i].objFrameY = 0;
				item_option* temp;
				temp = new item_option;

				temp->ATK = 0;
				temp->ATK_SPEED = 0;
				temp->DEF = 0;
				temp->Price = 0;
				temp->Upgrade = 0;

				_rndItem = RND->getFromIntTo(1, 4);

				if (_rndItem == 1)
				{
					temp->Price = 10;
					_im->add_items_init(_tiles[i].rc.left + _camera->getCameraX() + 20, _tiles[i].rc.top + _camera->getCameraY(), 10, 1, false, (*temp));
				}
				if (_rndItem == 2)
				{
					temp->Price = 50;
					_im->add_items_init(_tiles[i].rc.left + _camera->getCameraX() + 20, _tiles[i].rc.top + _camera->getCameraY(), 11, 1, false, (*temp));
				}
				if (_rndItem == 3)
				{
					temp->Price = 100;
					_im->add_items_init(_tiles[i].rc.left + _camera->getCameraX() + 20, _tiles[i].rc.top + _camera->getCameraY(), 12, 1, false, (*temp));
				}
				if (_rndItem == 4)
				{
					_im->add_items_init(_tiles[i].rc.left + _camera->getCameraX() + 20, _tiles[i].rc.top + _camera->getCameraY(), 9, 1, false, (*temp));
				}
			}
		}
	}

}

void zeldaTileMap1::render()
{
	zeldaTileMap::render();

	//for (int i = 0; i < 3; i++)
	//{
	//	_rockTile[i].image->render(getMemDC(), _rockTile[i].rc.left, _rockTile[i].rc.top);
	//}
	//_em->render();

	_emZorder->render();
}

// ----------------------------------------------------------------------------------------------------

HRESULT zeldaTileMap2::init(player* player, camera * camera, const CHAR* pMapSaveFileName, int mapWidth, int mapHeight)
{
	zeldaTileMap::init(player, camera, pMapSaveFileName, mapWidth, mapHeight);

	_em = new enemyManager;
	_em->init(_player, _camera, this);

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].obj == OBJ_OCTOPUS)
		{
			_em->setOcto(_tiles[i].rc.left, _tiles[i].rc.top);
		}
		else if (_tiles[i].obj == OBJ_SNAIL)
		{
			_em->setSnail(_tiles[i].rc.left, _tiles[i].rc.top);
		}
		else if (_tiles[i].obj == OBJ_SLIME)
		{
			_em->setSlime(_tiles[i].rc.left, _tiles[i].rc.top);
		}
	}

	_emZorder = new emZorder;
	_emZorder->init(_em, _player);

	_door[UP].rc = RectMake(720, 150, 80, 30);
	_door[UP].nextMap = TILEMAP_THREE;
	_door[UP].x = 630;
	_door[UP].y = 1200;
	_door[UP].cameraX = 145;
	_door[UP].cameraY = 800;

	_door[DOWN].rc = RectMake(720, 1400, 80, 30);
	_door[DOWN].nextMap = TILEMAP_ONE;
	_door[DOWN].x = 625;
	_door[DOWN].y = 142;
	_door[DOWN].cameraX = 165;
	_door[DOWN].cameraY = 0;

	int j = 0;
	int k = 0;

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].obj2 == OBJ_FIRE2)
		{
			_fireTile[j].image = IMAGEMANAGER->findImage("TILE_FIRE");
			_fireTile[j].rc = RectMake(_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].rc.right - _tiles[i].rc.left - 5, _tiles[i].rc.bottom - _tiles[i].rc.top - 5);

			j++;
		}
		else if (_tiles[i].obj2 == OBJ_BUTTON1_UP)
		{
			_buttonTile[k].image = IMAGEMANAGER->findImage("TILE_BUTTON_DOWN");
			_buttonTile[k].rc = RectMake(_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].rc.right - _tiles[i].rc.left - 5, _tiles[i].rc.bottom - _tiles[i].rc.top - 5);

			k++;
		}
		else if (_tiles[i].obj2 == OBJ_SMALL_BOX1)
		{
			
			_chestTile.image = IMAGEMANAGER->findImage("OPEN_CHEST");
			_chestTile.rc = RectMake(_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].rc.right - _tiles[i].rc.left - 5, _tiles[i].rc.bottom - _tiles[i].rc.top - 5);		
		}
	}

	_frameCount = 0;
	for (int i = 0; i < 4; i++)
	{
		_currentFrameX[i] = 0;
	}

	_alphaValue = 200;
	_count = 0;
	_isChest = false;

	return S_OK;
}

void zeldaTileMap2::release()
{
	zeldaTileMap::release();

	_em->release();
}

void zeldaTileMap2::update()
{
	zeldaTileMap::update();

	_door[UP].rc = RectMake(_camera->getStartX() + 720, _camera->getStartY() + 150, 80, 30);
	_door[DOWN].rc = RectMake(_camera->getStartX() + 720, _camera->getStartY() + 1400, 80, 30);

	_emZorder->update();
	_em->update();

	int j = 0;
	int k = 0;

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].obj2 == OBJ_FIRE2)
		{
			_fireTile[j].rc = RectMake(_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].rc.right - _tiles[i].rc.left - 5, _tiles[i].rc.bottom - _tiles[i].rc.top - 5);

			j++;
		}
		else if (_tiles[i].obj2 == OBJ_BUTTON1_UP)
		{
			_buttonTile[k].rc = RectMake(_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].rc.right - _tiles[i].rc.left - 5, _tiles[i].rc.bottom - _tiles[i].rc.top - 5);

			k++;
		}
		else if (_tiles[i].obj2 == OBJ_SMALL_BOX1)
		{
			_chestTile.image = IMAGEMANAGER->findImage("OPEN_CHEST");
			_chestTile.rc = RectMake(_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].rc.right - _tiles[i].rc.left - 5, _tiles[i].rc.bottom - _tiles[i].rc.top - 5);
		}
	}

	RECT temp;

	_count = 0;

	for (int i = 0; i < 4; i++)
	{
		if (IntersectRect(&temp, &_buttonTile[i].rc, &_player->getRect()))
		{
			_buttonTile[i].isOn = true;

			if (!SOUNDMANAGER->isPlaySound("불켜짐"))
				SOUNDMANAGER->play("불켜짐");
		}

		if (_buttonTile[i].isOn)
		{
			_count++;

			if (_count >= 4)
			{
				_count = 4;
				_isChest = true;
			}
		}
	}

	//보물상자 충돌
	if (!_chestTile.isOn)
	{
		if (IntersectRect(&temp, &_chestTile.rc, &_player->getRect()) && _isChest)
		{
			if (!SOUNDMANAGER->isPlaySound("작은상자열림"))
				SOUNDMANAGER->play("작은상자열림");

			_chestTile.isOn = true;
			item_option* temp;
			temp = new item_option;

			temp->ATK = 0;
			temp->ATK_SPEED = 0;
			temp->DEF = 0;
			temp->Price = 0;
			temp->Upgrade = 0;

			_im->add_items_init(_chestTile.rc.left + _camera->getCameraX() + 20, _chestTile.rc.top + _camera->getCameraY() - 50, 14, 1, false, (*temp));

		}
	}

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		RECT rcTmp;
		if (_tiles[i].obj2 == OBJ_POT)
		{
			if (IntersectRect(&rcTmp, &_tiles[i].rc, &_player->getCrushRect()))
			{
				_tiles[i].obj2 = OBJ_NONE;
				_tiles[i].objFrameX = 0;
				_tiles[i].objFrameY = 0;
				item_option* temp;
				temp = new item_option;

				temp->ATK = 0;
				temp->ATK_SPEED = 0;
				temp->DEF = 0;
				temp->Price = 0;
				temp->Upgrade = 0;

				_rndItem = RND->getFromIntTo(1, 4);

				if (_rndItem == 1)
				{
					temp->Price = 10;
					_im->add_items_init(_tiles[i].rc.left + _camera->getCameraX() + 20, _tiles[i].rc.top + _camera->getCameraY(), 10, 1, false, (*temp));
				}
				if (_rndItem == 2)
				{
					temp->Price = 50;
					_im->add_items_init(_tiles[i].rc.left + _camera->getCameraX() + 20, _tiles[i].rc.top + _camera->getCameraY(), 11, 1, false, (*temp));
				}
				if (_rndItem == 3)
				{
					temp->Price = 100;
					_im->add_items_init(_tiles[i].rc.left + _camera->getCameraX() + 20, _tiles[i].rc.top + _camera->getCameraY(), 12, 1, false, (*temp));
				}
				if (_rndItem == 4)
				{
					_im->add_items_init(_tiles[i].rc.left + _camera->getCameraX() + 20, _tiles[i].rc.top + _camera->getCameraY(), 9, 1, false, (*temp));
				}
			}
		}
	}
	_frameCount++;
	if (_frameCount % 10 == 0)
	{
		for (int i = 0; i < 4; i++)
		{
			if (_currentFrameX[i] >= _fireTile[i].image->getMaxFrameX()) _currentFrameX[i] = 0;
			else _currentFrameX[i]++;

			_frameCount = 0;
		}
	}
}

void zeldaTileMap2::render()
{
	zeldaTileMap::render();

	for (int i = 0; i < 4; i++)
	{
		if (_buttonTile[i].isOn)
		{
			_buttonTile[i].image->render(getMemDC(), _buttonTile[i].rc.left, _buttonTile[i].rc.top);
			_fireTile[i].image->frameRender(getMemDC(), _fireTile[i].rc.left, _fireTile[i].rc.top, _currentFrameX[i], _fireTile[i].image->getFrameY());
		}
	}

	if (_isChest)
	{
		if (_chestTile.isOn)
		{
			_chestTile.image->render(getMemDC(), _chestTile.rc.left, _chestTile.rc.top);
		}
	}
	else
	{
		IMAGEMANAGER->findImage("TILE")->render(getMemDC(), _chestTile.rc.left, _chestTile.rc.top);
	}

	_emZorder->render();

	IMAGEMANAGER->findImage("BLACK")->alphaRender(getMemDC(), 0, 0, _alphaValue - (_count * 50));
}

// ----------------------------------------------------------------------------------------------------

HRESULT zeldaTileMap3::init(player* player, camera * camera, const CHAR* pMapSaveFileName, int mapWidth, int mapHeight)
{
	zeldaTileMap::init(player, camera, pMapSaveFileName, mapWidth, mapHeight);

	_em = new enemyManager;
	_em->init(_player, _camera, this);

	_emZorder = new emZorder;
	_emZorder->init(_em, _player);

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].obj == OBJ_OCTOPUS)
		{
			_em->setOcto(_tiles[i].rc.left, _tiles[i].rc.top);
		}
		else if (_tiles[i].obj == OBJ_SNAIL)
		{
			_em->setSnail(_tiles[i].rc.left, _tiles[i].rc.top);
		}
		else if (_tiles[i].obj == OBJ_SLIME)
		{
			_em->setSlime(_tiles[i].rc.left, _tiles[i].rc.top);
		}
	}

	_door[DOWN].rc = RectMake(720, 1400, 80, 30);
	_door[DOWN].nextMap = TILEMAP_TWO;
	_door[DOWN].x = 625;
	_door[DOWN].y = 142;
	_door[DOWN].cameraX = 165;
	_door[DOWN].cameraY = 0;

	return S_OK;
}

void zeldaTileMap3::release()
{
	zeldaTileMap::release();

	_em->release();
}

void zeldaTileMap3::update()
{
	zeldaTileMap::update();

	_door[DOWN].rc = RectMake(_camera->getStartX() + 720, _camera->getStartY() + 1400, 80, 30);

	_emZorder->update();
	_em->update();


	for (int i = 0; i < TILEX * TILEY; i++)
	{
		RECT rcTmp;
		if (_tiles[i].obj2 == OBJ_POT)
		{
			if (IntersectRect(&rcTmp, &_tiles[i].rc, &_player->getCrushRect()))
			{
				_tiles[i].obj2 = OBJ_NONE;
				_tiles[i].objFrameX = 0;
				_tiles[i].objFrameY = 0;
			
				item_option* temp;
				temp = new item_option;

				temp->ATK = 0;
				temp->ATK_SPEED = 0;
				temp->DEF = 0;
				temp->Price = 0;
				temp->Upgrade = 0;

				_rndItem = RND->getFromIntTo(1, 4);

				if (_rndItem == 1)
				{
					temp->Price = 10;
					_im->add_items_init(_tiles[i].rc.left + _camera->getCameraX() + 20, _tiles[i].rc.top + _camera->getCameraY(), 10, 1, false, (*temp));
				}
				if (_rndItem == 2)
				{
					temp->Price = 50;
					_im->add_items_init(_tiles[i].rc.left + _camera->getCameraX() + 20, _tiles[i].rc.top + _camera->getCameraY(), 11, 1, false, (*temp));
				}
				if (_rndItem == 3)
				{
					temp->Price = 100;
					_im->add_items_init(_tiles[i].rc.left + _camera->getCameraX() + 20, _tiles[i].rc.top + _camera->getCameraY(), 12, 1, false, (*temp));
				}
				if (_rndItem == 4)
				{
					_im->add_items_init(_tiles[i].rc.left + _camera->getCameraX() + 20, _tiles[i].rc.top + _camera->getCameraY(), 9, 1, false, (*temp));
				}
			}
		}
	}
}

void zeldaTileMap3::render()
{
	zeldaTileMap::render();

	_emZorder->render();
}

// ----------------------------------------------------------------------------------------------------

HRESULT zeldaTileMap4::init(player* player, camera * camera, const CHAR* pMapSaveFileName, int mapWidth, int mapHeight)
{
	zeldaTileMap::init(player, camera, pMapSaveFileName, mapWidth, mapHeight);

	_em = new enemyManager;
	_em->init(_player, _camera, this);

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].obj == OBJ_OCTOPUS)
		{
			_em->setOcto(_tiles[i].rc.left, _tiles[i].rc.top);
		}
		else if (_tiles[i].obj == OBJ_SNAIL)
		{
			_em->setSnail(_tiles[i].rc.left, _tiles[i].rc.top);
		}
		else if (_tiles[i].obj == OBJ_SLIME)
		{
			_em->setSlime(_tiles[i].rc.left, _tiles[i].rc.top);
		}
	}

	_emZorder = new emZorder;
	_emZorder->init(_em, _player);

	_door[UP].rc = RectMake(720, 150, 80, 30);
	_door[UP].nextMap = TILEMAP_BOSS;
	_door[UP].x = 630;
	_door[UP].y = 1200;
	_door[UP].cameraX = 145;
	_door[UP].cameraY = 800;

	_door[LEFT].rc = RectMake(320, 480, 80, 30);
	_door[LEFT].nextMap = TILEMAP_ONE;
	_door[LEFT].x = 220;
	_door[LEFT].y = 500;
	_door[LEFT].cameraX = 0;
	_door[LEFT].cameraY = 200;

	_door[RIGHT].rc = RectMake(1200, 480, 80, 30);
	_door[RIGHT].nextMap = TILEMAP_ONE;
	_door[RIGHT].x = 1100;
	_door[RIGHT].y = 500;
	_door[RIGHT].cameraX = 400;
	_door[RIGHT].cameraY = 200;

	return S_OK;
}

void zeldaTileMap4::release()
{
	zeldaTileMap::release();

	_em->release();
}

void zeldaTileMap4::update()
{
	zeldaTileMap::update();

	_door[UP].rc = RectMake(_camera->getStartX() + 720, _camera->getStartY() + 150, 80, 30);
	_door[LEFT].rc = RectMake(_camera->getStartX() + 320, _camera->getStartY() + 480, 80, 30);
	_door[RIGHT].rc = RectMake(_camera->getStartX() + 1200, _camera->getStartY() + 480, 80, 30);

	_emZorder->update();
	_em->update();


	for (int i = 0; i < TILEX * TILEY; i++)
	{
		RECT rcTmp;
		if (_tiles[i].obj2 == OBJ_POT)
		{
			if (IntersectRect(&rcTmp, &_tiles[i].rc, &_player->getCrushRect()))
			{
				_tiles[i].obj2 = OBJ_NONE;
				_tiles[i].objFrameX = 0;
				_tiles[i].objFrameY = 0;

				item_option* temp;
				temp = new item_option;

				temp->ATK = 0;
				temp->ATK_SPEED = 0;
				temp->DEF = 0;
				temp->Price = 0;
				temp->Upgrade = 0;

				_rndItem = RND->getFromIntTo(1, 4);

				if (_rndItem == 1)
				{
					temp->Price = 10;
					_im->add_items_init(_tiles[i].rc.left + _camera->getCameraX() + 20, _tiles[i].rc.top + _camera->getCameraY(), 10, 1, false, (*temp));
				}
				if (_rndItem == 2)
				{
					temp->Price = 50;
					_im->add_items_init(_tiles[i].rc.left + _camera->getCameraX() + 20, _tiles[i].rc.top + _camera->getCameraY(), 11, 1, false, (*temp));
				}
				if (_rndItem == 3)
				{
					temp->Price = 100;
					_im->add_items_init(_tiles[i].rc.left + _camera->getCameraX() + 20, _tiles[i].rc.top + _camera->getCameraY(), 12, 1, false, (*temp));
				}
				if (_rndItem == 4)
				{
					_im->add_items_init(_tiles[i].rc.left + _camera->getCameraX() + 20, _tiles[i].rc.top + _camera->getCameraY(), 9, 1, false, (*temp));
				}
			}
		}
	}
}

void zeldaTileMap4::render()
{
	zeldaTileMap::render();

	_emZorder->render();
}

// ----------------------------------------------------------------------------------------------------

HRESULT zeldaTileMap5::init(player* player, camera * camera, const CHAR* pMapSaveFileName, int mapWidth, int mapHeight)
{
	zeldaTileMap::init(player, camera, pMapSaveFileName, mapWidth, mapHeight);

	_em = new enemyManager;
	_em->init(_player, _camera, this);

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].obj == OBJ_OCTOPUS)
		{
			_em->setOcto(_tiles[i].rc.left, _tiles[i].rc.top);
		}
		else if (_tiles[i].obj == OBJ_SNAIL)
		{
			_em->setSnail(_tiles[i].rc.left, _tiles[i].rc.top);
		}
		else if (_tiles[i].obj == OBJ_SLIME)
		{
			_em->setSlime(_tiles[i].rc.left, _tiles[i].rc.top);
		}
	}

	_emZorder = new emZorder;
	_emZorder->init(_em, _player);

	_door[DOWN].rc = RectMake(720, 1400, 80, 30);
	_door[DOWN].nextMap = TILEMAP_FOUR;
	_door[DOWN].x = 625;
	_door[DOWN].y = 142;
	_door[DOWN].cameraX = 165;
	_door[DOWN].cameraY = 0;
		
	return S_OK;
}

void zeldaTileMap5::release()
{
	zeldaTileMap::release();

	_em->release();
}

void zeldaTileMap5::update()
{
	zeldaTileMap::update();

	_door[DOWN].rc = RectMake(_camera->getStartX() + 720, _camera->getStartY() + 1400, 80, 30);

	_emZorder->update();
	_em->update();

}

void zeldaTileMap5::render()
{
	zeldaTileMap::render();

	_emZorder->render();
}


// ----------------------------------------------------------------------------------------------------
