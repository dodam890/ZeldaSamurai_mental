#include "stdafx.h"
#include "npcZorder.h"
#include "player.h"
#include "npc.h"

npcZorder::npcZorder()
{
}


npcZorder::~npcZorder()
{
}

HRESULT npcZorder::init()
{
	return S_OK;
}

void npcZorder::release()
{
}

void npcZorder::update()
{
}

void npcZorder::render()
{
	drawNpcByZorder();
}

void npcZorder::setTownNpcByZorder(player* player, npc** townNpc, int townNpcNum)
{
	for (int i = 0; i < _vZorder.size(); i++)
	{
		_vZorder.erase(_vZorder.begin() + i);
	}
	_vZorder.clear();

	tagZorder zOrder;
	zOrder.key = "player";
	zOrder.randomClass = player;
	_vZorder.push_back(zOrder);

	for (int i = 0; i < townNpcNum; i++)
	{
		zOrder.key = "npc";
		zOrder.randomClass = townNpc[i];
		_vZorder.push_back(zOrder);
	}

	sortNpcByZorder();
}

void npcZorder::setStoreNpcByZorder(player * player, npc ** storeNpc, int storeNpcNum)
{
	for (int i = 0; i < _vZorder.size(); i++)
	{
		_vZorder.erase(_vZorder.begin() + i);
	}
	_vZorder.clear();

	tagZorder zOrder;
	zOrder.key = "player";
	zOrder.randomClass = player;
	_vZorder.push_back(zOrder);

	for (int i = 0; i < storeNpcNum; i++)
	{
		zOrder.key = "npc";
		zOrder.randomClass = storeNpc[i];
		_vZorder.push_back(zOrder);
	}

	sortNpcByZorder();
}

void npcZorder::sortNpcByZorder()
{
	RECT destRc;
	RECT sourRc;
	int sourCenterY;

	for (int i = 0; i < _vZorder.size(); i++)
	{
		for (int j = 0; j < _vZorder.size() - 1; j++)
		{
			if (_vZorder[j].key == "player" && _vZorder[j + 1].key == "npc")
			{
				destRc = ((player*)_vZorder[j].randomClass)->getRect();
				sourRc = ((npc*)_vZorder[j + 1].randomClass)->getRect();

				if (destRc.bottom > sourRc.bottom)
				{
					tagZorder temp = _vZorder[j];
					_vZorder[j] = _vZorder[j + 1];
					_vZorder[j + 1] = temp;
				}
			}
			else if(_vZorder[j].key == "npc" && _vZorder[j + 1].key == "player")
			{
				destRc = ((npc*)_vZorder[j].randomClass)->getRect();
				sourRc = ((player*)_vZorder[j + 1].randomClass)->getRect();

				if (destRc.bottom > sourRc.bottom)
				{
					tagZorder temp = _vZorder[j];
					_vZorder[j] = _vZorder[j + 1];
					_vZorder[j + 1] = temp;
				}
			}
			else if (_vZorder[j].key == "npc" && _vZorder[j + 1].key == "npc")
			{
				destRc = ((npc*)_vZorder[j].randomClass)->getRect();
				sourRc = ((npc*)_vZorder[j + 1].randomClass)->getRect();

				if (destRc.bottom > sourRc.bottom)
				{
					tagZorder temp = _vZorder[j];
					_vZorder[j] = _vZorder[j + 1];
					_vZorder[j + 1] = temp;
				}
			}
		}
	}
}

void npcZorder::drawNpcByZorder()
{
	for (int i = 0; i < _vZorder.size(); i++)
	{
		if (_vZorder[i].key == "player")
		{
			((player*)_vZorder[i].randomClass)->render();
		}
		else if (_vZorder[i].key == "npc")
		{
			((npc*)_vZorder[i].randomClass)->render();
		}
	}
}