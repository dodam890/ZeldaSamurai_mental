#pragma once
#include "gameNode.h"
#include "mapToolScene.h"
#include "zeldaMapScene.h"
#include "main_scene.h"
#include "select_scene.h"

class mainGame : public gameNode
{
public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void addItemImage();
	void addNpcImage();
	void addMapImage();

	void addImage();

	mainGame();
	~mainGame();
};

