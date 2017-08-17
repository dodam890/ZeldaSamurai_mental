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

	return S_OK;
}

void zeldaMapScene::release()
{
	_camera->release();
	_zeldaMap[_curMap]->release();
}

void zeldaMapScene::update()
{
	if (_is_inven == false)
	{
	_zeldaMap[_curMap]->update();
	_camera->update(_zeldaMap[_curMap]->getMapWidth(), _zeldaMap[_curMap]->getMapHeight());
	rectCollision();

	_link->pixelCollision(_zeldaMap[_curMap]->getPixelImg());

	_sceneEffect->update();
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

void zeldaMapScene::render()
{ 
	if (_is_inven == false)
	{
	_zeldaMap[_curMap]->render();

	_camera->render();
	_camera->drawCameraPos();
		
	_sceneEffect->render();
	IMAGEMANAGER->findImage("ÇÏ¾áÈ­¸é")->alphaRender(getMemDC(), 0, 0, effect_alpha);
	}
	else if (_is_inven == true)
	{
		_inven->render();
		IMAGEMANAGER->findImage("ÇÏ¾áÈ­¸é")->alphaRender(getMemDC(), 0, 0, effect_alpha);
	}
}

void zeldaMapScene::createMap()
{
	_curMap = STORE;

	_zeldaMap[TOWN] = new townMap;
	_zeldaMap[TOWN]->init("TOWN_BACKGROUND", "TOWN_BACKGROUND_PIXELCOLLISION", _camera, _link);

	_zeldaMap[STORE] = new storeMap;
	_zeldaMap[STORE]->init("STORE", "STORE_PIXELCOLLISION", _camera, _link);
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

				//¾À ÀüÈ¯ ³¡³ª¸é ¾À Ã¼ÀÎÁö
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