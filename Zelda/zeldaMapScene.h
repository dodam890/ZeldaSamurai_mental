#pragma once
#include "gameNode.h"
#include "c_zeldaMap.h"
#include "zeldaTileMap.h"
#include "camera.h"
#include "player.h"
#include "inven_all.h"
#include "shop_class.h"
#include "up_grade_complete.h"
#include "item_class_manager.h"
#include "sceneEffect.h"
#include "c_zeldaTileMap.h"

class zeldaMapScene : public gameNode
{
public:
	enum TILEMAP_KIND
	{
		TILEMAP_ONE,
		TILEMAP_TWO,
		TILEMAP_THREE,
		TILEMAP_FOUR,
		TILEMAP_BOSS,
		TILEMAP_END = 5
	};

private:
	camera* _camera;
	player* _link;
	inven_all* _inven;
	shop_class* _sc;
	up_grade_complete* _ugc;
	image* _imgTmpBackbuffer;
	MAP_KIND _curMap;
	zeldaMap* _zeldaMap[MAP_KIND_END];
	sceneEffect* _sceneEffect;

	item_class_manager* _im;

	bool _isCameraMove;
	bool _isLeft;

	bool _is_inven;
	bool _tile_inven;
	int effect_alpha;

private:
	zeldaTileMap* _zeldaTileMap[TILEMAP_END];
	TILEMAP_KIND _tileMapKind;

	bool _isTileMap;

	RECT _rcGoTileMap;

public:
	zeldaMapScene();
	virtual ~zeldaMapScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void createMap();
	void rectCollision();
	void setScene(int num);

	void changeTileScene();

	void setCurMap(MAP_KIND curMap) { _curMap = curMap; }
	void returnToMainMenu();
};

