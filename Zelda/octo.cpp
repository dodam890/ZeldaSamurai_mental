#include "stdafx.h"
#include "octo.h"

octo::octo()
{
}

octo::~octo()
{
}

HRESULT octo::init(player* player, camera* camera, zeldaTileMap* map, int idxX, int idxY)
{
	enemy::init(player, camera, map, idxX, idxY);

	_rangeWidth = 400;
	_rangeHeight = 400;

	_moveRc = RectMakeCenter(_centerMoveX, _centerMoveY, _rangeWidth, _rangeHeight);
	_collisionRc = RectMakeCenter(_centerX, _centerY, 800, 800);

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

	_moveRc = RectMakeCenter(_centerMoveX, _centerMoveY, _rangeWidth, _rangeHeight);
	_collisionRc = RectMakeCenter(_centerX, _centerY, 800, 800);
	_rc = RectMakeCenter(_centerX, _centerY, _imgInfo[_direction].image->getFrameWidth() - 50, _imgInfo[_direction].image->getFrameHeight());
}

void octo::render()
{
	enemy::render();
}

void octo::aStarMove(int index)
{
	enemy::aStarMove(index);
}

void octo::normalMove()
{
	enemy::normalMove();
}

void octo::addFrame()
{
	enemy::addFrame();
}

void octo::draw()
{
	enemy::draw();

	if (!_imgInfo[_direction].image) return;

	_imgInfo[_direction].image->frameRender(getMemDC(), _rc.left - 25, _rc.top, _imgInfo[_direction].currentFrameX, 0);
}

void octo::aStarPathFind()
{
	enemy::aStarPathFind();
}

void octo::getMapAttribute()
{
	enemy::getMapAttribute();
}

void octo::addImage()
{
	enemy::addImage();

	_imgInfo[DIRECTION_DOWN].image = IMAGEMANAGER->addFrameImage("octoDown", "image/enemys/enemy/문어-이동-아래쪽(260.80).bmp", 260, 80, 2, 1, true, RGB(255, 0, 255));
	_imgInfo[DIRECTION_RIGHT].image = IMAGEMANAGER->addFrameImage("octoRight", "image/enemys/enemy/문어-이동-오른쪽(260.80).bmp", 260, 80, 2, 1, true, RGB(255, 0, 255));
	_imgInfo[DIRECTION_LEFT].image = IMAGEMANAGER->addFrameImage("octoLeft", "image/enemys/enemy/문어-이동-왼쪽(260.80).bmp", 260, 80, 2, 1, true, RGB(255, 0, 255));
	_imgInfo[DIRECTION_UP].image = IMAGEMANAGER->addFrameImage("octoUp", "image/enemys/enemy/문어-이동-위쪽(260.80).bmp", 260, 80, 2, 1, true, RGB(255, 0, 255));
}

