#pragma once
#include "gameNode.h"
#include "enemy.h"

class camera;
class zeldaTileMap;
class player;

class enemyManager : public gameNode
{
private:
	typedef vector<enemy*> vEnemy;
	typedef vector<enemy*>::iterator viEnemy;

private:
	vEnemy _vEm;
	viEnemy _viEm;

	camera* _camera;
	player* _player;
	zeldaTileMap* _map;

public:
	HRESULT init(player* player, camera* camera, zeldaTileMap* map);
	void release();
	void update();
	void render();

	void setOcto();
	void setSlime();
	void setSnail();

	enemyManager();
	~enemyManager();
};

