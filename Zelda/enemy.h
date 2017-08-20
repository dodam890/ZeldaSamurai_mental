#pragma once
#include "gameNode.h"
#include "aStar.h"

class camera;
class player;
class zeldaTileMap;

struct tagEnemy
{
	image* image;
	int currentFrameX;
};
class enemy : public gameNode
{
public:
	enum DIRECTION
	{
		DIRECTION_DOWN,
		DIRECTION_LEFT,
		DIRECTION_RIGHT,
		DIRECTION_UP,
		DIRECTION_END = 4
	};
protected:
	player* _player;

protected:
	vector<aStarTile*> _vPath;
	vector<aStarTile*> _viPath;

protected:
	tagEnemy _imgInfo[DIRECTION_END];
	DIRECTION _direction;

	RECT _rc;
	RECT _moveRc;
	RECT _collisionRc;

	float _distanceX, _distanceY;
	float _distanceMoveX, _distanceMoveY;

	float _centerX, _centerY;
	float _centerMoveX, _centerMoveY;

	float _angle;

	int _indexX, _indexY;
	int tileIndex[2];
	int tileX, tileY;
	int tileTotalIdx;
	RECT rcCollision;

	int _frameCount;

	float _moveCount;

	aStar* _aStar;
	int _currentTileIndex;
	bool _isFull;

	bool _isFindPlayer;

	camera* _camera;

	player* _link;

	zeldaTileMap* _map;

	int _rangeWidth;
	int _rangeHeight;

public:
	virtual HRESULT init(player* player, camera* camera, zeldaTileMap* map, int idxX, int idxY);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void aStarMove(int index);
	virtual void normalMove();
	virtual void addFrame();
	virtual void draw();

	virtual void addImage();

	virtual void aStarPathFind();
	virtual void getMapAttribute();

	enemy();
	virtual ~enemy();
};

