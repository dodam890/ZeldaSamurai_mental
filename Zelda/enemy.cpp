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
	_isFindPlayer(false),
	_distanceMoveX(0.F),
	_distanceMoveY(0.F),
	_centerMoveX(0.F),
	_centerMoveY(0.F)
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

	_distanceMoveX = _distanceX;
	_distanceMoveY = _distanceY;

	_centerMoveX = _centerX;
	_centerMoveY = _centerY;

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
	_aStar->tilesUpdate();

	if (_isFindPlayer)
	{
		this->aStarPathFind();
		_distanceMoveX = _distanceX;
		_distanceMoveY = _distanceY;
	}
	else
	{
		normalMove();
		getMapAttribute();
	}

	RECT sour;
	if (IntersectRect(&sour, &_collisionRc, &_player->getRect()))
	{
		_isFindPlayer = true;
	}
	else
	{
		_isFindPlayer = false;
	}

	_centerX = _camera->getStartX() + _distanceX;
	_centerY = _camera->getStartY() + _distanceY;

	_centerMoveX = _camera->getStartX() + _distanceMoveX;
	_centerMoveY = _camera->getStartY() + _distanceMoveY;
<<<<<<< HEAD

	//_aStar->update();
=======
>>>>>>> 64aea2e0a62f0969fe01d4ced1fb1a0c6d72e97c
}

void enemy::render()
{
	this->draw();
	if (_isFindPlayer)
	{
		TextOut(getMemDC(), 500, 500, "발견!", strlen("발견!"));
	}
	else
	{
		TextOut(getMemDC(), 500, 500, "노발견!", strlen("노발견!"));
	}
	//Rectangle(getMemDC(), rcCollision.left, rcCollision.top, rcCollision.right, rcCollision.bottom);
}

void enemy::aStarMove(int index)
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

void enemy::normalMove()
{
	_moveCount += TIMEMANAGER->getElapsedTime() * 100;

	if (_moveCount > 100.f)
	{
		int rndNum = RND->getFromIntTo(0, 3);
		_direction = (DIRECTION)rndNum;
		_moveCount = 0.f;
	}

	switch (_direction)
	{
	case enemy::DIRECTION_DOWN:
		if (_rc.bottom < _moveRc.bottom)
			_distanceY += 5.f;
		break;
	case enemy::DIRECTION_LEFT:
		if (_rc.left > _moveRc.left)
			_distanceX -= 5.f;
		break;
	case enemy::DIRECTION_RIGHT:
		if (_rc.right < _moveRc.right)
			_distanceX += 5.f;
		break;
	case enemy::DIRECTION_UP:
		if (_rc.top > _moveRc.top)
			_distanceY -= 5.f;
		break;
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
	//if (_aStar) _aStar->render();

	//Rectangle(getMemDC(), _collisionRc.left, _collisionRc.top, _collisionRc.right, _collisionRc.bottom);
	//Rectangle(getMemDC(), _moveRc.left, _moveRc.top, _moveRc.right, _moveRc.bottom);
	//Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);

	char str[128] = "";
	sprintf_s(str, "eTileX : %d, eTileY : %d", tileX, tileY);
	TextOut(getMemDC(), 400, 200, str, strlen(str));

	sprintf_s(str, "eObX : %d, eObY : %d, eTotal : %d", tileIndex[0], tileIndex[1], tileTotalIdx);
	TextOut(getMemDC(), 400, 230, str, strlen(str));
}

void enemy::addImage()
{
}

void enemy::aStarPathFind()
{
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
		else this->aStarMove(_currentTileIndex);
	}
}

void enemy::getMapAttribute()
{
	BOOL* attribute = _map->getAttribute(E_ATR_MOVE);

	rcCollision = RectMakeCenter(_centerX, _centerY, _imgInfo[_direction].image->getFrameWidth() - 52, _imgInfo[_direction].image->getFrameHeight() - 2);
	
	tileX = _distanceX / TILESIZE;
	tileY = _distanceY / TILESIZE;

	tileTotalIdx = tileX + tileY * TILEX;

	switch (_direction)
	{
	case enemy::DIRECTION_DOWN:

		tileIndex[0] = tileTotalIdx + TILEX;
		if (_rc.left > _map->getTiles()[tileIndex[0]].rc.left) tileIndex[1] = tileIndex[0] + 1;
		else tileIndex[1] = tileIndex[0] - 1;

		break;
	case enemy::DIRECTION_LEFT:

		tileIndex[0] = tileTotalIdx - 1;
		if (_rc.bottom > _map->getTiles()[tileIndex[0]].rc.bottom) tileIndex[1] = tileIndex[0] + TILEX;
		else tileIndex[1] = tileIndex[0] - TILEX;

		break;
	case enemy::DIRECTION_RIGHT:

		tileIndex[0] = tileTotalIdx + 1;
		if (_rc.bottom > _map->getTiles()[tileIndex[0]].rc.bottom) tileIndex[1] = tileIndex[0] + TILEX;
		else tileIndex[1] = tileIndex[0] - TILEX;

		break;
	case enemy::DIRECTION_UP:

		tileIndex[0] = tileTotalIdx - TILEX;
		if (_rc.left > _map->getTiles()[tileIndex[0]].rc.left) tileIndex[1] = tileIndex[0] + 1;
		else tileIndex[1] = tileIndex[0] - 1;

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

				_distanceY -= 5.F;

				break;
			case enemy::DIRECTION_LEFT:

				_distanceX += 5.F;

				break;
			case enemy::DIRECTION_RIGHT:

				_distanceX -= 5.F;

				break;
			case enemy::DIRECTION_UP:

				_distanceY += 5.F;

				break;
			}
		}
	}

}
