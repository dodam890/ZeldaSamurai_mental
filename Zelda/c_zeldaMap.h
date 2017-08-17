#pragma once
#include "zeldaMap.h"
#include "shop_class.h"

class townMap : public zeldaMap
{
public:
	virtual HRESULT init(string strMapImageKey, string strPixelMapImageKey, camera* camera, player* player);
	virtual void release();
	virtual void update();
	virtual void render();

	void talkToTownNpc();

	void collisionBetweenPlayerAndNpc();

	townMap();
	virtual ~townMap();
};

class storeMap : public zeldaMap
{
private:
	shop_class* _sc;
public:
	virtual HRESULT init(string strMapImageKey, string strPixelMapImageKey, camera* camera, player* player);
	virtual void release();
	virtual void update();
	virtual void render();

	void talkToStoreNpc();

	void collisionBetweenPlayerAndNpc();

	storeMap();
	virtual ~storeMap();
};