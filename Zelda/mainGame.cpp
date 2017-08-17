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

	SCENEMANAGER->addScene("mapToolScene", new mapToolScene);
	SCENEMANAGER->addScene("zeldaMapScene", new zeldaMapScene);
	SCENEMANAGER->addScene("main_scene", new main_scene);
	SCENEMANAGER->addScene("select_scene", new select_scene);
	SCENEMANAGER->addScene("zeldaTileMapScene", new zeldaTileMapScene);
	SCENEMANAGER->addScene("ASTAR", new aStarScene);


	//���θ޴� Ŭ���� �����ҰŰ�.
	//���θ޴����� �ΰ����� �� ��ȯ �Ұ���.
	//�ϴ� ����

	//SCENEMANAGER->changeScene("mapToolScene");
	//SCENEMANAGER->changeScene("zeldaMapScene");
	//SCENEMANAGER->changeScene("main_scene");
	//SCENEMANAGER->changeScene("select_scene");

	//SCENEMANAGER->changeScene("main_scene");

	SCENEMANAGER->changeScene("ASTAR");
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

	// �޴���, ����Ʈ��, ���Ӿ�, ������ �����
	changeSceneByKeyInput();
}

void mainGame::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ ���� �ǵ������� ================

	SCENEMANAGER->render();

	//	TIMEMANAGER->render(getMemDC());
	//===============�Ʒ��� �ǵ������� =================
	this->getBackBuffer()->render(getHDC(), 0, 0);
}

void mainGame::changeSceneByKeyInput()
{
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		SCENEMANAGER->changeScene("mapToolScene");
	}
	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		SCENEMANAGER->changeScene("zeldaMapScene");
	}
	if (KEYMANAGER->isOnceKeyDown('E'))
	{
		SCENEMANAGER->changeScene("select_scene");
	}
}

