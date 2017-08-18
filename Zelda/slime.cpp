#include "stdafx.h"
#include "slime.h"

slime::slime()
{
}

slime::~slime()
{
}

HRESULT slime::init(camera * camera, int idxX, int idxY)
{
	enemy::init(camera, idxX, idxY);

	_rangeWidth = 500;

	_rangeHeight = 500;

	_rc = RectMakeCenter(_centerX, _centerY, _imgInfo[_direction].image->getFrameWidth(), _imgInfo[_direction].image->getFrameHeight());
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

	_centerX = _camera->getStartX() + _distanceX;
	_centerY = _camera->getStartY() + _distanceY;

	_rc = RectMakeCenter(_centerX, _centerY, _imgInfo[_direction].image->getFrameWidth(), _imgInfo[_direction].image->getFrameHeight());
	_moveRc = RectMakeCenter(_centerX, _centerY, _rangeWidth, _rangeHeight);
	_collisionRc = RectMakeCenter(_centerX, _centerY, 800, 800);
}

void slime::render()
{
	enemy::render();
}

void slime::move()
{
	enemy::move();
}

void slime::addFrame()
{
	enemy::addFrame();
}

void slime::draw()
{
	enemy::draw();
}

void slime::addImage()
{
	enemy::addImage();

	_imgInfo[DIRECTION_DOWN].image = IMAGEMANAGER->addFrameImage("slimeDown", "image/enemys/enemy/슬라임-이동(1600,130).bmp", 1600, 130, 16, 1, true, RGB(255, 0, 255));
	_imgInfo[DIRECTION_RIGHT].image = IMAGEMANAGER->addFrameImage("slimeRight", "image/enemys/enemy/슬라임-이동(1600,130).bmp", 1600, 130, 16, 1, true, RGB(255, 0, 255));
	_imgInfo[DIRECTION_LEFT].image = IMAGEMANAGER->addFrameImage("slimeLeft", "image/enemys/enemy/슬라임-이동(1600,130).bmp", 1600, 130, 16, 1, true, RGB(255, 0, 255));
	_imgInfo[DIRECTION_UP].image = IMAGEMANAGER->addFrameImage("slimeUp", "image/enemys/enemy/슬라임-이동(1600.130),bmp", 1600, 130, 16, 1, true, RGB(255, 0, 255));
}
