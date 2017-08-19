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

	_rc = RectMakeCenter(_centerX, _centerY, _imgInfo[_direction].image->getFrameWidth(), _imgInfo[_direction].image->getFrameHeight());
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

	_centerX = _camera->getStartX() + _distanceX;
	_centerY = _camera->getStartY() + _distanceY;

	_rc = RectMakeCenter(_centerX, _centerY, _imgInfo[_direction].image->getFrameWidth(), _imgInfo[_direction].image->getFrameHeight());
	_moveRc = RectMakeCenter(_centerX, _centerY, _rangeWidth, _rangeHeight);
	_collisionRc = RectMakeCenter(_centerX, _centerY, 800, 800);
}

void snail::render()
{
	enemy::render();
}

void snail::move(int index)
{
	enemy::move(index);
}

void snail::addFrame()
{
	enemy::addFrame();
}

void snail::draw()
{
	enemy::draw();
}

void snail::addImage()
{
	enemy::addImage();

	_imgInfo[DIRECTION_DOWN].image = IMAGEMANAGER->addFrameImage("snailDown", "image/enemys/enemy/������-�̵�-�Ʒ���(560.135).bmp", 560, 135, 4, 1, true, RGB(255, 0, 255));
	_imgInfo[DIRECTION_RIGHT].image = IMAGEMANAGER->addFrameImage("snailRight", "image/enemys/enemy/������-�̵�-������(560.135).bmp", 560, 135, 4, 1, true, RGB(255, 0, 255));
	_imgInfo[DIRECTION_LEFT].image = IMAGEMANAGER->addFrameImage("snailLeft", "image/enemys/enemy/������-�̵�-����(560.135).bmp", 560, 135, 4, 1, true, RGB(255, 0, 255));
	_imgInfo[DIRECTION_UP].image = IMAGEMANAGER->addFrameImage("snailUp", "image/enemys/enemy/������-�̵�-����(560.135).bmp", 560, 135, 4, 1, true, RGB(255, 0, 255));
}

