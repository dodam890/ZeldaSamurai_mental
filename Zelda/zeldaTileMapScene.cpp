#include "stdafx.h"
#include "zeldaTileMapScene.h"


zeldaTileMapScene::zeldaTileMapScene() :
	_map(NULL),
	_camera(NULL),
	_em(NULL)
{
}

zeldaTileMapScene::~zeldaTileMapScene()
{
}

HRESULT zeldaTileMapScene::init()
{
	_camera = new camera;
	_camera->init();

	_map = new zeldaTileMap;
	_map->init(_camera, 5000, 1000);

	//_em = new enemyManager;
	//_em->init(_camera, _map);
	//_em->setOcto();
	//_em->setSlime();
	//_em->setSnail();


	_i = 0;
	_nIdxX = 1;
	_nIdxY = 1;

	isFull = false;
	_i = 0;

	return S_OK;
}

void zeldaTileMapScene::release()
{
	_camera->release();
	_map->release();
}

void zeldaTileMapScene::update()
{
	_camera->update(_map->getMapWidth(), _map->getMapHeight());
	_map->update();

	/*if (_ast->getIsFindEnd())
	{
		_ast->setCharacterPath(_test.vTankTile, &isFull);
		_i = 0;
	}
	else _ast->update();

	if (_i < _test.vTankTile.size())
	{
		if (((_test.vTankTile[_i]->getRect().left == _test.rc.left) &&
			(_test.vTankTile[_i]->getRect().right == _test.rc.right) &&
			(_test.vTankTile[_i]->getRect().top == _test.rc.top) &&
			(_test.vTankTile[_i]->getRect().bottom == _test.rc.bottom)))
		{
			_ast->resetAstar(_map, _test.vTankTile[_i]->getIdxX(), _test.vTankTile[_i]->getIdxY(),
				18, 18);
			_i++;
		}
		else testMove(_i);
	}*/

	//_em->update();

}

void zeldaTileMapScene::render()
{
	//_camera->drawCameraPos();
	_map->render();
	//if (_ast) _ast->render();
	//_test.image->render(getMemDC(), _test.rc.left, _test.rc.top);

	//_em->render();
}

void zeldaTileMapScene::testMove(int index)
{
	/*if (_test.vTankTile[index]->getRect().left > _test.rc.left)
	{
		_test.rc.left++;
	}
	else if (_test.vTankTile[index]->getRect().left < _test.rc.left)
	{
		_test.rc.left--;
	}


	if (_test.vTankTile[index]->getRect().right > _test.rc.right)
	{
		_test.rc.right++;
	}
	else if (_test.vTankTile[index]->getRect().right < _test.rc.right)
	{
		_test.rc.right--;
	}


	if (_test.vTankTile[index]->getRect().top > _test.rc.top)
	{
		_test.rc.top++;
	}
	else if (_test.vTankTile[index]->getRect().top < _test.rc.top)
	{
		_test.rc.top--;
	}


	if (_test.vTankTile[index]->getRect().bottom > _test.rc.bottom)
	{
		_test.rc.bottom++;
	}
	else if (_test.vTankTile[index]->getRect().bottom < _test.rc.bottom)
	{
		_test.rc.bottom--;
	}*/
}
