#pragma once
#include "gameNode.h"
#include "zeldaTileNode.h"

class camera;

class aStarTile : public gameNode
{
private:
	camera* _camera;

private:
	int m_nIdxX;
	int m_nIdxY;
	POINT m_posCenter;
	RECT m_rc;

	int m_nDisX;
	int m_nDisY;

	float m_fTotalCost;
	float m_fCostFromStart;
	float m_fCostToGoal;

	bool m_bIsOpen;

	aStarTile* m_pParentNode;
	string m_strAttribute;

	COLORREF m_color;
	HBRUSH m_hBrush;
	HPEN m_hPen;

public:
	aStarTile();
	virtual ~aStarTile();

	HRESULT init(camera* camera, int nIdxX, int nIdxY);
	void release();
	void update();
	void render();

	int getIdxX() { return m_nIdxX; }
	int getIdxY() { return m_nIdxY; }

	RECT getRect() { return m_rc; }

	POINT getCenter() { return m_posCenter; }
	void setCenter(POINT posCenter) { m_posCenter = posCenter; }

	float getTotalCost() { return m_fTotalCost; }
	void setTotalCost(float fTotalCost) { m_fTotalCost = fTotalCost; }

	float getCostFromStart() { return m_fCostFromStart; }
	void setCostFromStart(float fCostFromStart) { m_fCostFromStart = fCostFromStart; }

	float getCostToGoal() { return m_fCostToGoal; }
	void setCostToGoal(float fCostToGoal) { m_fCostToGoal = fCostToGoal; }

	bool getIsOpen() { return m_bIsOpen; }
	void setIsOpen(bool bIsOpen) { m_bIsOpen = bIsOpen; }

	aStarTile* getParentNode() { return m_pParentNode; }
	void setParentNode(aStarTile* pParentNode) { m_pParentNode = pParentNode; }

	string getAttribute() { return m_strAttribute; }
	void setAttribute(string strAttribute) { m_strAttribute = strAttribute; }

	int getDisX() { return m_nDisX; }
	int getDisY() { return m_nDisY; }

	void setDisX(int disX) { m_nDisX = disX; }
	void setDisY(int disY) { m_nDisY = disY; }

	void setColor(COLORREF color)
	{
		DeleteObject(m_hBrush);
		m_color = color;
		m_hBrush = CreateSolidBrush(m_color);
	}

	void resetTile();
};

