#pragma once
#include "gameNode.h"
#include "mapToolScene.h"
#include "zeldaMapScene.h"
#include "main_scene.h"
#include "select_scene.h"
#include "zeldaTileMapScene.h"

#include "aStarScene.h"

class mainGame : public gameNode
{
public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void changeSceneByKeyInput();

	void addItemImage();
	void addNpcImage();
	void addMapImage();

	void addImage();

	mainGame();
	~mainGame();
};

