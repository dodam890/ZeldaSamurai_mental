#pragma once
#include "gameNode.h"
#include "aStarTile.h"
#include "zeldaTileNode.h"
#include "camera.h"
#include <vector>

class camera;
class zeldaTileMap;

class aStar : public gameNode
{
private:
	camera* _camera;

private:
	std::vector<aStarTile*> m_vTotalList;
	std::vector<aStarTile*>::iterator m_viTotalList;

	std::vector<aStarTile*> m_vOpenList;
	std::vector<aStarTile*>::iterator m_viOpenList;

	std::vector<aStarTile*> m_vCloseList;
	std::vector<aStarTile*>::iterator m_viCloseList;

	std::vector<aStarTile*> m_vPathList;
	std::vector<aStarTile*>::iterator m_viPathList;

	aStarTile* m_pStartTile;
	aStarTile* m_pEndTile;
	aStarTile* m_pCurTile;

	int m_nCount;
	bool m_bIsStart;
	bool m_bIsEnd;

public:
	aStar();
	virtual ~aStar();

	HRESULT init(camera* camera);
	void release();
	void update();
	void render();

	void setTile(zeldaTileMap* pZeldaMap, int nStartIdxX, int nStartIdxY, int nEndIdxX, int nEndIdxY);
	std::vector<aStarTile*> addOpenList(aStarTile* pCurTile);
	void pathFinder(aStarTile* pCurTile);

	bool getIsFindEnd() { return m_bIsEnd; }
	void setIsFindEnd(bool bIsFindEnd) { m_bIsEnd = bIsFindEnd; }

	aStarTile* getStartTile() { return m_pStartTile; }

	void setCharacterPath(vector<aStarTile*>& vPath, bool* bMove);
	void resetAstar(zeldaTileMap* pZeldaMap, int nStartIdxX, int nStartIdxY, int nEndIdxX, int nEndIdxY);
	void clearAstar();

	void tilesUpdate();

	std::vector<aStarTile*> getVTotalList() { return m_vTotalList; }
};

