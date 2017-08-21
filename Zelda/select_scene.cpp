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

	_rcSelect[E_SELECT_MAPTOOL].img = IMAGEMANAGER->addImage("mapToolMenu", "image/mapTool.bmp", 300, 300, TRUE, RGB(255, 0, 255));
	_rcSelect[E_SELECT_MAPTOOL].rc = RectMakeCenter(WINSIZEX / 2 - 200, WINSIZEY / 2, 300, 300);
	_rcSelect[E_SELECT_MAPTOOL].strSceneKey = "mapToolScene";

	_rcSelect[E_SELECT_GAMESTART].img = IMAGEMANAGER->addImage("gameStartMenu", "image/start.bmp", 300, 300, TRUE, RGB(255, 0, 255));
	_rcSelect[E_SELECT_GAMESTART].rc = RectMakeCenter(WINSIZEX / 2 + 200, WINSIZEY / 2, 300, 300);
	_rcSelect[E_SELECT_GAMESTART].strSceneKey = "zeldaMapScene";
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
		if (carrentX > IMAGEMANAGER->findImage("선택창뒷배경")->getMaxFrameX()) carrentX = 0;
		count = 0;
	}

	for (int i = 0; i < E_SELECT_END; i++)
	{
		if (PtInRect(&_rcSelect[i].rc, _ptMouse))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				SCENEMANAGER->changeScene(_rcSelect[i].strSceneKey);
			}
			else
			{
				_rcSelect[i].alpha = 125;
			}
		}
		else
		{
			_rcSelect[i].alpha = 255;
		}
	}
}
 
void select_scene::render()
{
	IMAGEMANAGER->findImage("선택창뒷배경")->frameRender(getMemDC(), 0, 0, carrentX, 0);
	IMAGEMANAGER->findImage("타이틀")->render(getMemDC(), 10, 0);

	for (int i = 0; i < E_SELECT_END; i++)
	{
		//Rectangle(getMemDC(), _rcSelect[i].rc.left, _rcSelect[i].rc.top, _rcSelect[i].rc.right, _rcSelect[i].rc.bottom);
		_rcSelect[i].img->alphaRender(getMemDC(), _rcSelect[i].rc.left, _rcSelect[i].rc.top, _rcSelect[i].alpha);
	}
}