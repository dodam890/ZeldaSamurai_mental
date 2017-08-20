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
	P_x = 0;
	P_y = 0;

	m_x = 0;
	m_y = 0;

	is_town = false;

	return S_OK;
}

void inven_map::release()
{
}

void inven_map::update()
{
	m_x = P_x / 9.5;
	m_y = P_y / 9.5;
}

void inven_map::render()
{
	IMAGEMANAGER->findImage("인벤토리내용3")->render(getMemDC(), 38, 14);

	if (is_town == false)
	{
		IMAGEMANAGER->findImage("town_map")->render(getMemDC(), 480, 250);
		IMAGEMANAGER->findImage("zelda_map_icon")->render(getMemDC(), 480 + m_x, 250 + m_y);
	}
}
