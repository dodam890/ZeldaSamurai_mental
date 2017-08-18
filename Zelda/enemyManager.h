#pragma once
#include "gameNode.h"
#include "enemy.h"

class camera;

class enemyManager : public gameNode
{
private:
	typedef vector<enemy*> vEnemy;
	typedef vector<enemy*>::iterator viEnemy;

private:
	vEnemy _vEm;
	viEnemy _viEm;

	camera* _camera;

public:
	HRESULT init(camera* camera);
	void release();
	void update();
	void render();

	void setOcto();
	void setSlime();
	void setSnail();

	enemyManager();
	~enemyManager();
};

