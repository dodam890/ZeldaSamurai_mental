#include "stdafx.h"
#include "camera.h"

camera::camera() :
	_cameraX(0.F),
	_cameraY(0.F),
	_startX(0.F),
	_startY(0.F)
{
}

camera::~camera()
{
}

HRESULT camera::init()
{
	_cameraX = 0.F;
	_cameraY = 0.F;
	_startX = 0.F;
	_startY = 0.F;
	return S_OK;
}

void camera::release()
{
}

void camera::update(int mapWidth, int mapHeight)
{
	_mapWidth = mapWidth;
	_mapHeight = mapHeight;

	_startX = _cameraX * (-1.F);
	_startY = _cameraY * (-1.F);
}

void camera::render()
{
}

void camera::resetCamera()
{
	_cameraX = 0.F;
	_cameraY = 0.F;
	_startX = 0.F;
	_startY = 0.F;
}

void camera::drawCameraPos()
{
	char str[128] = "";

	//sprintf_s(str, "[startX : %1.f, startY : %1.f]", _startX, _startY);
	//TextOut(getMemDC(), WINSIZEX / 2 + 50, 0, str, strlen(str));
	//sprintf_s(str, "[cameraX : %1.f, cameraY : %1.f]", _cameraX, _cameraY);
	//TextOut(getMemDC(), WINSIZEX / 2 + 50, 30, str, strlen(str));

}

bool camera::isCameraXEndSide()
{
	if (_cameraX < (float)_mapWidth - (float)WINSIZEX) return true;
	else return false;
}

bool camera::isCameraXZeroSide()
{
	if (_cameraX >= 2.F) return true;
	else return false;
}

bool camera::isCameraYEndSide()
{
	if (_cameraY < (float)_mapHeight - (float)WINSIZEY) return true;
	else return false;
}

bool camera::isCameraYZeroSide()
{
	if (_cameraY >= 2.F) return true;
	else return false;
}
