#include "stdafx.h"
#include "mainGame.h"

mainGame::mainGame()
{
}

mainGame::~mainGame()
{
}

HRESULT mainGame::init(void)
{
	gameNode::init(true);

	//���⼭ ������ �̹��� add�ϴ� �Լ� ���ư�.
	addImage();
	addSound();

	SCENEMANAGER->addScene("mapToolScene", new mapToolScene);
	SCENEMANAGER->addScene("main_scene", new main_scene);
	SCENEMANAGER->addScene("select_scene", new select_scene);
	SCENEMANAGER->addScene("zeldaMapScene", new zeldaMapScene);

	SCENEMANAGER->changeScene("main_scene");
	return S_OK;
}

void mainGame::release(void)
{
	gameNode::release();
	SCENEMANAGER->release();
}

void mainGame::update(void)
{
	gameNode::update();
	SCENEMANAGER->update();

	if (KEYMANAGER->isStayKeyDown(VK_F9))
	{
		_rectView = true;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_F9))
	{
		_rectView = false;
	}

	if (KEYMANAGER->isStayKeyDown(VK_F7))
	{
		_pixelView = true;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_F7))
	{
		_pixelView = false;
	}
}

void mainGame::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ ���� �ǵ������� ================

	SCENEMANAGER->render();

	//TIMEMANAGER->render(getMemDC());
	//===============�Ʒ��� �ǵ������� =================
	this->getBackBuffer()->render(getHDC(), 0, 0); 
}

