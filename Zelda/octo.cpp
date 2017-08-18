#include "stdafx.h"
#include "octo.h"

octo::octo()
{
}

octo::~octo()
{
}

HRESULT octo::init(camera * camera, int idxX, int idxY)
{
	enemy::init(camera, idxX, idxY);

	_rangeWidth = 400;
	_rangeHeight = 400;

	_rc = RectMakeCenter(_centerX, _centerY, _imgInfo[_direction].image->getFrameWidth(), _imgInfo[_direction].image->getFrameHeight());
	_moveRc = RectMakeCenter(_centerX, _centerY, _rangeWidth, _rangeHeight);
	_collisionRc = RectMakeCenter(_centerX, _centerY, 800, 800);

	return S_OK;
}

void octo::release()
{
	enemy::release();
}

void octo::update()
{
	enemy::update();

	_centerX = _camera->getStartX() + _distanceX;
	_centerY = _camera->getStartY() + _distanceY;

	_rc = RectMakeCenter(_centerX, _centerY, _imgInfo[_direction].image->getFrameWidth(), _imgInfo[_direction].image->getFrameHeight());
	_moveRc = RectMakeCenter(_centerX, _centerY, _rangeWidth, _rangeHeight);
	_collisionRc = RectMakeCenter(_centerX, _centerY, 800, 800);
}

void octo::render()
{
	enemy::render();
}

void octo::move()
{
	enemy::move();
}

void octo::addFrame()
{
	enemy::addFrame();
}

void octo::draw()
{
	enemy::draw();
}

void octo::addImage()
{
	enemy::addImage();

	_imgInfo[DIRECTION_DOWN].image = IMAGEMANAGER->addFrameImage("octoDown", "image/enemys/enemy/문어-이동-아래쪽(260.80).bmp", 260, 80, 2, 1, true, RGB(255, 0, 255));
	_imgInfo[DIRECTION_RIGHT].image = IMAGEMANAGER->addFrameImage("octoRight", "image/enemys/enemy/문어-이동-오른쪽(260.80).bmp", 260, 80, 2, 1, true, RGB(255, 0, 255));
	_imgInfo[DIRECTION_LEFT].image = IMAGEMANAGER->addFrameImage("octoLeft", "image/enemys/enemy/문어-이동-왼쪽(260.80).bmp", 260, 80, 2, 1, true, RGB(255, 0, 255));
	_imgInfo[DIRECTION_UP].image = IMAGEMANAGER->addFrameImage("octoUp", "image/enemys/enemy/문어-이동-위쪽(260.80).bmp", 260, 80, 2, 1, true, RGB(255, 0, 255));
}

