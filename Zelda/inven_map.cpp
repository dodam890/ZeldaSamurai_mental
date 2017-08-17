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
	IMAGEMANAGER->findImage("인벤토리내용3")->render(getMemDC(), 38, 14);
}
