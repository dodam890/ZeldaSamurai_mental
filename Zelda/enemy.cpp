#include "stdafx.h"
#include "enemy.h"
#include "camera.h"
#include "player.h"

enemy::enemy() :
	_rc(),
	_moveRc(),
	_collisionRc(),
	_imgInfo(),
	_distanceX(0.f),
	_distanceY(0.f),
	_centerX(0.f),
	_centerY(0.f),
	_indexX(0),
	_indexY(0),
	_frameCount(0),
	_moveCount(0),
	_aStar(NULL),
	_currentTileIndex(0),
	_isFull(0),
	_camera(NULL),
	_rangeWidth(0),
	_rangeHeight(0),
	_direction(DIRECTION_DOWN)
{
}


enemy::~enemy()
{
}


HRESULT enemy::init(camera* camera, zeldaTileMap* map, int idxX, int idxY)
{
	_camera = camera;

	_map = map;

	_distanceX = WINSIZEX / 2;
	_centerX = _camera->getStartX() + _distanceX;

	_distanceY = WINSIZEY / 2;
	_centerY = _camera->getStartY() + _distanceY;

	_indexX = idxX;
	_indexY = idxY;

	_moveCount = 0;

	this->addImage();


	return S_OK;;
}

void enemy::release()
{
}

void enemy::update()
{
	this->addFrame();
}

void enemy::render()
{
	this->draw();
}

void enemy::move()
{
}

void enemy::addFrame()
{
	if (!_imgInfo[_direction].image) return;

	_frameCount++;

	if (_frameCount % 20 == 0)
	{
		if (_imgInfo[_direction].currentFrameX >= _imgInfo[_direction].image->getMaxFrameX()) _imgInfo[_direction].currentFrameX = 0;
		else _imgInfo[_direction].currentFrameX++;

		_frameCount = 0;
	}
}

void enemy::draw()
{
	Rectangle(getMemDC(), _collisionRc.left, _collisionRc.top, _collisionRc.right, _collisionRc.bottom);
	Rectangle(getMemDC(), _moveRc.left, _moveRc.top, _moveRc.right, _moveRc.bottom);
	Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);

	if (!_imgInfo[_direction].image) return;

	_imgInfo[_direction].image->frameRender(getMemDC(), _rc.left, _rc.top, _imgInfo[_direction].currentFrameX, 0);
}

void enemy::addImage()
{
}
