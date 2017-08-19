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
	_direction(DIRECTION_DOWN),
	_isFindPlayer(false)
{
}


enemy::~enemy()
{
}


HRESULT enemy::init(player* player, camera* camera, zeldaTileMap* map, int idxX, int idxY)
{
	_player = player;
	_camera = camera;
	_map = map;

	_indexX = idxX;
	_indexY = idxY;

	_aStar = new aStar;
	_aStar->init(_camera);
	_aStar->setTile(_map, idxX, idxY, 14, 8);

	_moveCount = 0;

	this->addImage();

	_distanceX = _aStar->getStartTile()->getDisX();
	_centerX = _camera->getStartX() + _distanceX;

	_distanceY = _aStar->getStartTile()->getDisY();
	_centerY = _camera->getStartY() + _distanceY;

	_rc = RectMakeCenter(_centerX, _centerY, _imgInfo[_direction].image->getFrameWidth(), _imgInfo[_direction].image->getFrameHeight());

	_isFindPlayer = false;

	return S_OK;;
}

void enemy::release()
{
	_aStar->release();
}

void enemy::update()
{
	this->addFrame();

	if (_isFindPlayer)
	{
		this->aStarPathFind();
	}

	_centerX = _camera->getStartX() + _distanceX;
	_centerY = _camera->getStartY() + _distanceY;
	_rc = RectMakeCenter(_centerX, _centerY, _imgInfo[_direction].image->getFrameWidth() - 50, _imgInfo[_direction].image->getFrameHeight());

	//_aStar->update();
}

void enemy::render()
{
	this->draw();
}

void enemy::move(int index)
{
	if (_vPath[index]->getDisX() > _distanceX)
	{
		_direction = DIRECTION_RIGHT;
		_distanceX += 5;
	}

	if (_vPath[index]->getDisX() < _distanceX)
	{
		_direction = DIRECTION_LEFT;
		_distanceX -= 5;
	}

	if (_vPath[index]->getDisY() < _distanceY)
	{
		_direction = DIRECTION_UP;
		_distanceY -= 5;
	}

	if (_vPath[index]->getDisY() > _distanceY)
	{
		_direction = DIRECTION_DOWN;
		_distanceY += 5;
	}
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
	if (_aStar) _aStar->render();

	//Rectangle(getMemDC(), _collisionRc.left, _collisionRc.top, _collisionRc.right, _collisionRc.bottom);
	//Rectangle(getMemDC(), _moveRc.left, _moveRc.top, _moveRc.right, _moveRc.bottom);
	Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);

	if (!_imgInfo[_direction].image) return;

	_imgInfo[_direction].image->frameRender(getMemDC(), _rc.left - 25, _rc.top, _imgInfo[_direction].currentFrameX, 0);
}

void enemy::addImage()
{
}

void enemy::aStarPathFind()
{
	_aStar->tilesUpdate();
	if (_aStar->getIsFindEnd())
	{
		_aStar->setCharacterPath(_vPath, &_isFull);
		_currentTileIndex = 0;
	}
	else _aStar->update();

	if (_currentTileIndex < _vPath.size())
	{
		if (((_vPath[_currentTileIndex]->getRect().left == _rc.left) &&
			(_vPath[_currentTileIndex]->getRect().right == _rc.right) &&
			(_vPath[_currentTileIndex]->getRect().top == _rc.top) &&
			(_vPath[_currentTileIndex]->getRect().bottom == _rc.bottom)))
		{
			_aStar->resetAstar(_map, _vPath[_currentTileIndex]->getIdxX(), _vPath[_currentTileIndex]->getIdxY(), 14, 8);
			_currentTileIndex++;
		}
		else this->move(_currentTileIndex);
	}
}
