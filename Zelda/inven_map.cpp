#include "stdafx.h"
#include "inven_map.h"


inven_map::inven_map()
{
}


inven_map::~inven_map()
{
}

HRESULT inven_map::init()
{
	return S_OK;
}

void inven_map::release()
{
}

void inven_map::update()
{
}

void inven_map::render()
{
	IMAGEMANAGER->findImage("�κ��丮����3")->render(getMemDC(), 38, 14);
	IMAGEMANAGER->findImage("town_map")->render(getMemDC(), 480, 250);
}
