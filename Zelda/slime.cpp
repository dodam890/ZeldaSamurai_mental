#include "stdafx.h"
#include "slime.h"

slime::slime()
{
}

slime::~slime()
{
}

HRESULT slime::init(player* player, camera* camera, zeldaTileMap* map, int idxX, int idxY)
{
	enemy::init(player, camera, map, idxX, idxY);

	_rangeWidth = 300;
	_rangeHeight = 300;

	_moveRc = RectMakeCenter(_centerX, _centerY, _rangeWidth, _rangeHeight);
	_collisionRc = RectMakeCenter(_centerX, _centerY, 800, 800);

	return S_OK;
}

void slime::release()
{
	enemy::release();
}

void slime::update()
{
	enemy::update();

	_moveRc = RectMakeCenter(_centerX, _centerY, _rangeWidth, _rangeHeight);
	_collisionRc = RectMakeCenter(_centerX, _centerY, 800, 800);
	_rc = RectMakeCenter(_centerX, _centerY, _imgInfo[_direction].image->getFrameWidth() - 20, _imgInfo[_direction].image->getFrameHeight() - 50);
}

void slime::render()
{
	enemy::render();
}

void slime::aStarMove(int index)
{
	enemy::aStarMove(index);
}

void slime::normalMove()
{
	enemy::normalMove();
}

void slime::addFrame()
{
	enemy::addFrame();
}

void slime::draw()
{
	enemy::draw();

	if (!_imgInfo[_direction].image) return;
	_imgInfo[_direction].image->frameRender(getMemDC(), _rc.left - 15, _rc.top - 50, _imgInfo[_direction].currentFrameX, 0);
}

void slime::aStarPathFind()
{
	enemy::aStarPathFind();
}

void slime::getMapAttribute()
{
	enemy::getMapAttribute();
}

void slime::addImage()
{
	enemy::addImage();

	_imgInfo[DIRECTION_DOWN].image = IMAGEMANAGER->addFrameImage("slimeDown", "image/enemys/enemy/슬라임-이동(1600,130).bmp", 1600, 130, 16, 1, true, RGB(255, 0, 255));
	_imgInfo[DIRECTION_RIGHT].image = IMAGEMANAGER->addFrameImage("slimeRight", "image/enemys/enemy/슬라임-이동(1600,130).bmp", 1600, 130, 16, 1, true, RGB(255, 0, 255));
	_imgInfo[DIRECTION_LEFT].image = IMAGEMANAGER->addFrameImage("slimeLeft", "image/enemys/enemy/슬라임-이동(1600,130).bmp", 1600, 130, 16, 1, true, RGB(255, 0, 255));
	_imgInfo[DIRECTION_UP].image = IMAGEMANAGER->addFrameImage("slimeUp", "image/enemys/enemy/슬라임-이동(1600,130).bmp", 1600, 130, 16, 1, true, RGB(255, 0, 255));
}
