#include "stdafx.h"
#include "mapToolScene.h"

mapToolScene::mapToolScene()
{
}

mapToolScene::~mapToolScene()
{
}

HRESULT mapToolScene::init()
{
	_mt = new mapTool;
	_mt->init();

	return S_OK;
}

void mapToolScene::release()
{
	_mt->release();
}

void mapToolScene::update()
{
	_mt->update();

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		SCENEMANAGER->changeScene("main_scene");
	}
}

void mapToolScene::render()
{
	_mt->render();
}

