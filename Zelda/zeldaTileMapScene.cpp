#include "stdafx.h"
#include "zeldaTileMapScene.h"


zeldaTileMapScene::zeldaTileMapScene() :
	_map(NULL),
	_camera(NULL),
	_ast(NULL)
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

	_ast = new aStar;
	_ast->init(_camera);
	_ast->setTile(_map, 1, 1, 18, 18);

	_test.image = IMAGEMANAGER->addImage("ball", "image/ball.bmp", 32, 32, true, RGB(255, 0, 255));
	_test.rc = _ast->getStartTile()->getRect();

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

	if (_ast->getIsFindEnd())
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
	}

}

void zeldaTileMapScene::render()
{
	//_camera->drawCameraPos();
	_map->render();
	//if (_ast) _ast->render();
	_test.image->render(getMemDC(), _test.rc.left, _test.rc.top);
}

void zeldaTileMapScene::testMove(int index)
{
	if (_test.vTankTile[index]->getRect().left > _test.rc.left)
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
	}
}
