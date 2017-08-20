#include "stdafx.h"
#include "snail.h"

snail::snail()
{
}

snail::~snail()
{
}

HRESULT snail::init(player* player, camera* camera, zeldaTileMap* map, int idxX, int idxY)
{
	enemy::init(player, camera, map, idxX, idxY);

	_rangeWidth = 400;
	_rangeHeight = 300;

	_moveRc = RectMakeCenter(_centerX, _centerY, _rangeWidth, _rangeHeight);
	_collisionRc = RectMakeCenter(_centerX, _centerY, 800, 800);

	return S_OK;
}

void snail::release()
{
	enemy::release();
}

void snail::update()
{
	enemy::update();

	_moveRc = RectMakeCenter(_centerMoveX, _centerMoveY, _rangeWidth, _rangeHeight);
	_collisionRc = RectMakeCenter(_centerX, _centerY, 800, 800);
	_rc = RectMakeCenter(_centerX, _centerY, _imgInfo[_direction].image->getFrameWidth() - 60, _imgInfo[_direction].image->getFrameHeight() - 55);
}

void snail::render()
{
	enemy::render();
}

void snail::aStarMove(int index)
{
	enemy::aStarMove(index);
}

void snail::normalMove()
{
	enemy::normalMove();
}

void snail::addFrame()
{
	enemy::addFrame();
}

void snail::draw()
{
	enemy::draw();

	if (!_imgInfo[_direction].image) return;

	_imgInfo[_direction].image->frameRender(getMemDC(), _rc.left - 30, _rc.top - 50, _imgInfo[_direction].currentFrameX, 0);
}

void snail::aStarPathFind()
{
	enemy::aStarPathFind();
}

void snail::getMapAttribute()
{
	enemy::getMapAttribute();
}

void snail::addImage()
{
	enemy::addImage();

	_imgInfo[DIRECTION_DOWN].image = IMAGEMANAGER->addFrameImage("snailDown", "image/enemys/enemy/달팽이-이동-아래쪽(560.135).bmp", 560, 135, 4, 1, true, RGB(255, 0, 255));
	_imgInfo[DIRECTION_RIGHT].image = IMAGEMANAGER->addFrameImage("snailRight", "image/enemys/enemy/달팽이-이동-오른쪽(560.135).bmp", 560, 135, 4, 1, true, RGB(255, 0, 255));
	_imgInfo[DIRECTION_LEFT].image = IMAGEMANAGER->addFrameImage("snailLeft", "image/enemys/enemy/달팽이-이동-왼쪽(560.135).bmp", 560, 135, 4, 1, true, RGB(255, 0, 255));
	_imgInfo[DIRECTION_UP].image = IMAGEMANAGER->addFrameImage("snailUp", "image/enemys/enemy/달팽이-이동-위쪽(560.135).bmp", 560, 135, 4, 1, true, RGB(255, 0, 255));
}

