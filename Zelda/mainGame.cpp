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

	//여기서 각각의 이미지 add하는 함수 돌아감.
	addImage();

	SCENEMANAGER->addScene("mapToolScene", new mapToolScene);
	SCENEMANAGER->addScene("zeldaMapScene", new zeldaMapScene);
	SCENEMANAGER->addScene("main_scene", new main_scene);
	SCENEMANAGER->addScene("select_scene", new select_scene);
	SCENEMANAGER->addScene("zeldaTileMapScene", new zeldaTileMapScene);
	SCENEMANAGER->addScene("ASTAR", new aStarScene);


	//메인메뉴 클래스 생성할거고.
	//메인메뉴에서 두가지의 씬 전환 할것임.
	//일단 실험

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

	// 메뉴씬, 셀렉트씬, 게임씬, 멥툴씬 실험용
	changeSceneByKeyInput();
}

void mainGame::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ 위에 건들지마라 ================

	SCENEMANAGER->render();

	//	TIMEMANAGER->render(getMemDC());
	//===============아래도 건들지마라 =================
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

