#include "stdafx.h"
#include "c_zeldaMap.h"
#include "player.h"
#include "camera.h"

HRESULT townMap::init(string strMapImageKey, string strPixelMapImageKey, camera* camera, player* player)
{
	zeldaMap::init(strMapImageKey, strPixelMapImageKey, camera, player);

	_kind = TOWN;

	_mapImg = IMAGEMANAGER->findImage(strMapImageKey);
	_mapPixelImg = IMAGEMANAGER->findImage(strPixelMapImageKey);
	
	_eventRectInfo[TOWN_STORE].rc = RectMake(3228, 1960, 80, 30);
	_eventRectInfo[TOWN_STORE].nextMap = STORE;
	_eventRectInfo[TOWN_STORE].cameraX = 0;
	_eventRectInfo[TOWN_STORE].cameraY = 0;
	_eventRectInfo[TOWN_STORE].x = 465;
	_eventRectInfo[TOWN_STORE].y = 465;

	//_eventRectInfo[TOWN_STAGE].rc = RectMake(1349, 851, 80, 30);
	//_eventRectInfo[TOWN_STAGE].cameraX = 790;
	//_eventRectInfo[TOWN_STAGE].cameraY = 490;
	//_eventRectInfo[TOWN_STAGE].x = 490;
	//_eventRectInfo[TOWN_STAGE].y = 370;

	return S_OK;
}

void townMap::release()
{
	zeldaMap::release();
}

void townMap::update()
{
	zeldaMap::update();

	_link->isStore(false);

	talkToTownNpc();

	_eventRectInfo[TOWN_STORE].rc = RectMake(3228 + _camera->getStartX(), 1960 + _camera->getStartY(), 80, 30);
	//_eventRectInfo[TOWN_STAGE].rc = RectMake(1349 + _camera->getStartX(), 851 + _camera->getStartY(), 80, 30);

	for (int i = 0; i < 7; i++)
	{
		_townNpc[i]->update("normal");
	}
	_townNpc[7]->update("guardLeft");
	_townNpc[8]->update("guardRight");
	_townNpc[9]->update("guardTop");

	collisionBetweenPlayerAndNpc();
}
void townMap::render() 
{
	zeldaMap::render();

	Rectangle(getMemDC(), _eventRectInfo[TOWN_STORE].rc.left, _eventRectInfo[TOWN_STORE].rc.top, _eventRectInfo[TOWN_STORE].rc.right, _eventRectInfo[TOWN_STORE].rc.bottom);

	for (int i = 0; i < 10; i++)
	{
		if(_townNpc[i]->getTalkOn())
			_townNpc[i]->drawTextBox();
	}
}

void townMap::talkToTownNpc()
{
	for (int i = 0; i < 10; i++)
	{
		RECT temp = {};
		if (IntersectRect(&temp, &_townNpc[i]->getMoveRect(), &_link->getRect()))
		{
			if (KEYMANAGER->isOnceKeyDown('D'))
			{
				if (!_townNpc[i]->getTalkOn())
				{
					_townNpc[i]->setTalkOn(true);
				}
				else
					_townNpc[i]->setTalkOn(false);
			}
		}
		else _townNpc[i]->setTalkOn(false);
	}
}

void townMap::collisionBetweenPlayerAndNpc()
{
	RECT temp;
	if (IntersectRect(&temp, &_link->getRect(), &_townNpc[7]->getRect()))
	{
		_link->setIsCollision(true, _townNpc[7]->getRect());
	}

	else if (IntersectRect(&temp, &_link->getRect(), &_townNpc[8]->getRect()))
	{
		_link->setIsCollision(true, _townNpc[8]->getRect());
	}

	else if (IntersectRect(&temp, &_link->getRect(), &_townNpc[9]->getRect()))
	{
		_link->setIsCollision(true, _townNpc[9]->getRect());
	}

	else _link->setIsCollision(false, _townNpc[7]->getRect());

}

townMap::townMap() {}
townMap::~townMap() {}


HRESULT storeMap::init(string strMapImageKey, string strPixelMapImageKey, camera* camera, player* player)
{
	zeldaMap::init(strMapImageKey, strPixelMapImageKey, camera, player);

	_kind = STORE;

	_mapImg = IMAGEMANAGER->findImage(strMapImageKey);
	_mapPixelImg = IMAGEMANAGER->findImage(strPixelMapImageKey);

	_eventRectInfo[STORE_TOWN].rc = RectMake(555, 675, 90, 30);
	_eventRectInfo[STORE_TOWN].nextMap = TOWN;
	_eventRectInfo[STORE_TOWN].cameraX = 2665;
	_eventRectInfo[STORE_TOWN].cameraY = 1665;
	_eventRectInfo[STORE_TOWN].x = _eventRectInfo[STORE_TOWN].cameraX + WINSIZEX / 2 - 135;
	_eventRectInfo[STORE_TOWN].y = _eventRectInfo[STORE_TOWN].cameraY + WINSIZEY / 2 - 135;

	_eventRectInfo[STORE_NEXTDOOR].rc = RectMake(1200, 395, 5, 80);

	SOUNDMANAGER->play("»óÁ¡À½¾Ç", 1.f);

	return S_OK;
}

void storeMap::release() 
{
	zeldaMap::release();
}

void storeMap::update()	 
{
	zeldaMap::update();

	_link->isStore(true);

	_eventRectInfo[STORE_TOWN].rc = RectMake(555 + _camera->getStartX(), 675 + _camera->getStartY(), 90, 30);
	_eventRectInfo[STORE_NEXTDOOR].rc = RectMake(1200 + _camera->getStartX(), 395 + _camera->getStartY(), 5, 80);

	_storeNpc[0]->update("npcShop");
	_storeNpc[1]->update("npcLink");
	_storeNpc[2]->update("npcMaster");

	talkToStoreNpc();
}

void storeMap::render()
{
	zeldaMap::render();

	IMAGEMANAGER->findImage("STORE_DOOR")->render(getMemDC(), _camera->getStartX(), _camera->getStartY());


	for (int i = 0; i < 3; i++)
	{
		if(_storeNpc[i]->getTalkOn())
			_storeNpc[i]->drawTextBox();
	}
}

void storeMap::talkToStoreNpc()
{
	for (int i = 0; i < 3; i++)
	{
		RECT temp = {};
		if (IntersectRect(&temp, &_storeNpc[i]->getMoveRect(), &_link->getRect()))
		{
			if (KEYMANAGER->isOnceKeyDown('D'))
			{
				if (!_storeNpc[i]->getTalkOn())
				{
					_storeNpc[i]->setTalkOn(true);
				}
				else
					_storeNpc[i]->setTalkOn(false);
			}
		}
		else _storeNpc[i]->setTalkOn(false);
	}
}

void storeMap::collisionBetweenPlayerAndNpc()
{
}

storeMap::storeMap() {}
storeMap::~storeMap() {}