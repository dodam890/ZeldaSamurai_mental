#include "stdafx.h"
#include "select_scene.h"


select_scene::select_scene()
{
}


select_scene::~select_scene()
{
}

HRESULT select_scene::init()
{
	count = 0;
	carrentX = 0;

	return S_OK;
}

void select_scene::release()
{
}

void select_scene::update()
{
	count++;
	if (count % 60 == 0)
	{
		carrentX++;
		if (carrentX > IMAGEMANAGER->findImage("����â�޹��")->getMaxFrameX()) carrentX = 0;
		count = 0;
	}
}

void select_scene::render()
{
	IMAGEMANAGER->findImage("����â�޹��")->frameRender(getMemDC(), 0, 0, carrentX, 0);
	IMAGEMANAGER->findImage("Ÿ��Ʋ")->render(getMemDC(), 10, 0);
}