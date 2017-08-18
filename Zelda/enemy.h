#pragma once
#include "gameNode.h"
#include "aStar.h"

class camera;

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
	vector<aStarTile*> _vPath;
	vector<aStarTile*> _viPath;

protected:
	tagEnemy _imgInfo[DIRECTION_END];
	DIRECTION _direction;

	RECT _rc;
	RECT _moveRc;
	RECT _collisionRc;

	float _distanceX, _distanceY;
	float _centerX, _centerY;

	int _indexX, _indexY;

	int _frameCount;

	int _moveCount;

	aStar* _aStar;

	camera* _camera;

	int _rangeWidth;
	int _rangeHeight;

public:
	virtual HRESULT init(camera* camera, int idxX, int idxY);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void move();
	virtual void addFrame();
	virtual void draw();

	virtual void addImage();

	enemy();
	virtual ~enemy();
};

