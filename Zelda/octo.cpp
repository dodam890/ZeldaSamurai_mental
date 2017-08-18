#include "stdafx.h"
#include "octo.h"

octo::octo()
{
}

octo::~octo()
{
}

HRESULT octo::init(camera* camera, zeldaTileMap* map, int idxX, int idxY)
{
	enemy::init(camera, map, idxX, idxY);

	_rangeWidth = 400;
	_rangeHeight = 400;

	_rc = RectMakeCenter(_centerX, _centerY, _imgInfo[_direction].image->getFrameWidth(), _imgInfo[_direction].image->getFrameHeight());
	_moveRc = RectMakeCenter(_centerX, _centerY, _rangeWidth, _rangeHeight);
	_collisionRc = RectMakeCenter(_centerX, _centerY, 800, 800);

	_aStar = new aStar;
	_aStar->init(_camera);
	_aStar->setTile(_map, 3, 3, 25, 25);

	return S_OK;
}

void octo::release()
{
	enemy::release();

	_aStar->release();
}

void octo::update()
{
	enemy::update();

	_centerX = _camera->getStartX() + _distanceX;
	_centerY = _camera->getStartY() + _distanceY;

	_rc = RectMakeCenter(_centerX, _centerY, _imgInfo[_direction].image->getFrameWidth(), _imgInfo[_direction].image->getFrameHeight());
	_moveRc = RectMakeCenter(_centerX, _centerY, _rangeWidth, _rangeHeight);
	_collisionRc = RectMakeCenter(_centerX, _centerY, 800, 800);

	_aStar->update();
}

void octo::render()
{
	enemy::render();

	_aStar->render();
}

void octo::move(int index)
{
	enemy::move();

	if (_vPath[index]->getRect().left > _rc.left)
	{
		_rc.left++;
	}
	else if (_vPath[index]->getRect().left < _rc.left)
	{
		_rc.left--;
	}


	if (_vPath[index]->getRect().right > _rc.right)
	{
		_rc.right++;
	}
	else if (_vPath[index]->getRect().right < _rc.right)
	{
		_rc.right--;
	}


	if (_vPath[index]->getRect().top > _rc.top)
	{
		_rc.top++;
	}
	else if (_vPath[index]->getRect().top < _rc.top)
	{
		_rc.top--;
	}


	if (_vPath[index]->getRect().bottom > _rc.bottom)
	{
		_rc.bottom++;
	}
	else if (_vPath[index]->getRect().bottom < _rc.bottom)
	{
		_rc.bottom--;
	}
}

void octo::addFrame()
{
	enemy::addFrame();
}

void octo::draw()
{
	enemy::draw();

	if (_aStar) _aStar->render();
}

void octo::aStarPathFind()
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
			_aStar->resetAstar(_map, _vPath[_currentTileIndex]->getIdxX(), _vPath[_currentTileIndex]->getIdxY(), 25, 25);
			_currentTileIndex++;
		}
		else move(_currentTileIndex);
	}
}

void octo::addImage()
{
	enemy::addImage();

	_imgInfo[DIRECTION_DOWN].image = IMAGEMANAGER->addFrameImage("octoDown", "image/enemys/enemy/문어-이동-아래쪽(260.80).bmp", 260, 80, 2, 1, true, RGB(255, 0, 255));
	_imgInfo[DIRECTION_RIGHT].image = IMAGEMANAGER->addFrameImage("octoRight", "image/enemys/enemy/문어-이동-오른쪽(260.80).bmp", 260, 80, 2, 1, true, RGB(255, 0, 255));
	_imgInfo[DIRECTION_LEFT].image = IMAGEMANAGER->addFrameImage("octoLeft", "image/enemys/enemy/문어-이동-왼쪽(260.80).bmp", 260, 80, 2, 1, true, RGB(255, 0, 255));
	_imgInfo[DIRECTION_UP].image = IMAGEMANAGER->addFrameImage("octoUp", "image/enemys/enemy/문어-이동-위쪽(260.80).bmp", 260, 80, 2, 1, true, RGB(255, 0, 255));
}

