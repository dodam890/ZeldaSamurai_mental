#include "stdafx.h"
#include "enemy.h"
#include "camera.h"
#include "player.h"
#include "zeldaTileMap.h"

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
	_aStar->setTile(_map, idxX, idxY, _player->getIndexX(), _player->getIndexY());

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

	//if (_isFindPlayer)
	//{
		this->aStarPathFind();
	//}

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

	//getMapAttribute();
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
			_aStar->resetAstar(_map, _vPath[_currentTileIndex]->getIdxX(), _vPath[_currentTileIndex]->getIdxY(), _player->getIndexX(), _player->getIndexY());
			_currentTileIndex++;
		}
		else this->move(_currentTileIndex);
	}
}

void enemy::getMapAttribute()
{
	BOOL* attribute = _map->getAttribute(E_ATR_MOVE);

	RECT rcCollision = _rc;

	int tileIndex[2];
	int tileX, tileY;

	tileX = rcCollision.left / TILESIZE;
	tileY = rcCollision.top / TILESIZE;

	switch (_direction)
	{
	case enemy::DIRECTION_DOWN:
		tileIndex[0] = (tileX + tileY * TILEX) + TILEX;
		tileIndex[1] = (tileX + 1 + tileY * TILEX) + TILEX;
		break;
	case enemy::DIRECTION_LEFT:
		tileIndex[0] = tileX + TILEX * tileY;
		tileIndex[1] = tileX + (tileY + 1) * TILEX;
		break;
	case enemy::DIRECTION_RIGHT:
		tileIndex[0] = (tileX + TILEX * tileY) + 1;
		tileIndex[1] = (tileX + (tileY + 1) * TILEX) + 1;
		break;
	case enemy::DIRECTION_UP:
		tileIndex[0] = tileX + TILEX * tileY;
		tileIndex[1] = tileX + 1 + TILEX * tileY;
		break;
	}

	for (int i = 0; i < 2; i++)
	{
		RECT rc;
		if ((attribute[tileIndex[i]] == FALSE) && 
			IntersectRect(&rc, &rcCollision, &_map->getTiles()[tileIndex[i]].rc))
		{
			switch (_direction)
			{
			case enemy::DIRECTION_DOWN:
				_rc.bottom = _map->getTiles()[tileIndex[i]].rc.top;
				_rc.top = _rc.bottom - _imgInfo[_direction].image->getFrameHeight();

				_distanceY = _rc.top + (_rc.bottom - _rc.top) / 2;
				break;
			case enemy::DIRECTION_LEFT:
				_rc.left = _map->getTiles()[tileIndex[i]].rc.right;
				_rc.right = _rc.left + (_imgInfo[_direction].image->getFrameWidth() - 50);

				_distanceX = _rc.left + (_rc.right - _rc.left) / 2;
				break;
			case enemy::DIRECTION_RIGHT:
				_rc.right = _map->getTiles()[tileIndex[i]].rc.left;
				_rc.left = _rc.right - (_imgInfo[_direction].image->getFrameWidth() - 50);

				_distanceX = _rc.left + (_rc.right - _rc.left) / 2;
				break;
			case enemy::DIRECTION_UP:
				_rc.top = _map->getTiles()[tileIndex[i]].rc.bottom;
				_rc.bottom = _rc.top + _imgInfo[_direction].image->getFrameHeight();

				_distanceY = _rc.top + (_rc.bottom - _rc.top) / 2;
				break;
			case enemy::DIRECTION_END:
				break;
			default:
				break;
			}
		}
	}
}
