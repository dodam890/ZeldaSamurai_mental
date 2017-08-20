#pragma once
#include "gameNode.h"
#include "npcZorder.h"
#include "npc.h"

class camera;
class player;

enum MAP_KIND
{
	TOWN,
	STORE,
	MAP_KIND_END
};

enum MAP_EVENT_RECT
{
	TOWN_STAGE,
	TOWN_STORE,
	STORE_TOWN,
	STORE_NEXTDOOR,
	MAP_RECT_END
};

struct tagEventRect
{
	RECT rc;
	MAP_KIND nextMap;		
	int x, y;				// 상하좌우 넘어갈때 다음맵에 생성되는 플레이어 위치 좌표
	int cameraX, cameraY;
};

class zeldaMap : public gameNode
{
private:
	npcZorder* _npcZorder;

protected:
	player* _link;

	camera* _camera;
	int _mapWidth;
	int _mapHeight;

	tagEventRect _eventRectInfo[MAP_RECT_END];

	MAP_KIND _kind;
	npc* _townNpc[10];
	npc* _storeNpc[3];

protected:
	image* _mapImg;
	image* _mapPixelImg;

public:
	zeldaMap();
	virtual ~zeldaMap();

	virtual HRESULT init(string strMapImageKey, string strPixelMapImageKey, camera* camera, player* player);
	virtual void release();
	virtual void update();
	virtual void render();

	void setAllNpcOnMap();

	inline image* getPixelImg() { return _mapPixelImg; }

	inline int getMapWidth() { return _mapWidth; }
	inline int getMapHeight() { return _mapHeight; }

	tagEventRect& getEventRect(int mapNum) { return _eventRectInfo[mapNum]; }

	bool get_is_talk_shop_npc_who(int arry);
	void set_is_talk_shop_npc_who(int arry, bool bo);
};

