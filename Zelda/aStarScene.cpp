#include "stdafx.h"
#include "aStarScene.h"

aStarScene::aStarScene()
{
}

aStarScene::~aStarScene()
{
}

HRESULT aStarScene::init()
{
	_ca = new camera;
	_ca->init();

	_map = new zeldaTileMap;
	_map->init(_ca, "mapSave10.map", 2000, 1000);


	_em = new enemyManager;
	_em->init(_ca, _map);
	_em->setOcto();
	/*_aStar = new aStar;
	_aStar->init(_ca);
	_aStar->setTile(_map, 1, 1, 15, 15);*/
	return S_OK;
}

void aStarScene::release()
{
	//_aStar->release();
}

void aStarScene::update()
{

	//_aStar->update();

	_em->update();
}

void aStarScene::render()
{
	//_aStar->render();

	_em->render();
	_ca->drawCameraPos();
}
