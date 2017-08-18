#include "stdafx.h"
#include "aStar.h"
#include "zeldaTileMap.h"

aStar::aStar() :
	m_pStartTile(NULL),
	m_pEndTile(NULL),
	m_pCurTile(NULL),
	m_nCount(0),
	m_bIsStart(false),
	m_bIsEnd(false)
{
}

aStar::~aStar()
{
}

HRESULT aStar::init(camera* camera)
{
	_camera = camera;

	m_nCount = m_bIsStart = m_bIsEnd = 0;
	m_vTotalList.reserve(5000);
	m_vOpenList.reserve(200);
	m_vCloseList.reserve(200);
	m_vPathList.reserve(200);
	return S_OK;
}

void aStar::release()
{
	SAFE_RELEASE(m_pStartTile);
	SAFE_DELETE(m_pStartTile);

	SAFE_RELEASE(m_pEndTile);
	SAFE_DELETE(m_pEndTile);

	m_pCurTile = NULL;

	for (m_viTotalList = m_vTotalList.begin(); m_viTotalList != m_vTotalList.end();)
	{
		if (*m_viTotalList)
		{
			SAFE_RELEASE(*m_viTotalList);
			SAFE_DELETE(*m_viTotalList);
			m_viTotalList = m_vTotalList.erase(m_viTotalList);
		}
		else m_viTotalList++;
	}
	m_vTotalList.clear();

	for (m_viOpenList = m_vOpenList.begin(); m_viOpenList != m_vOpenList.end();)
	{
		m_viOpenList = m_vOpenList.erase(m_viOpenList);
	}
	m_vOpenList.clear();

	for (m_viCloseList = m_vCloseList.begin(); m_viCloseList != m_vCloseList.end();)
	{
		m_viCloseList = m_vCloseList.erase(m_viCloseList);
	}
	m_vCloseList.clear();

	for (m_viPathList = m_vPathList.begin(); m_viPathList != m_vPathList.end();)
	{
		m_viPathList = m_vPathList.erase(m_viPathList);
	}
	m_vPathList.clear();

	m_nCount = 0;
	m_bIsStart = 0;
	m_bIsEnd = 0;
}

void aStar::update()
{
	pathFinder(m_pCurTile);
}

void aStar::render()
{
	if (m_vTotalList.size() == 0) return;

	char str[128] = "";

	for (int i = 0; i < m_vTotalList.size(); i++)
	{
		m_vTotalList[i]->render();
		TextOut(getMemDC(), m_vTotalList[i]->getRect().left, m_vTotalList[i]->getRect().top, m_vTotalList[i]->getAttribute().c_str(),
			strlen(m_vTotalList[i]->getAttribute().c_str()));

		sprintf(str, "[%d, %d]", m_vTotalList[i]->getIdxX(), m_vTotalList[i]->getIdxY());
		TextOut(getMemDC(), m_vTotalList[i]->getRect().left, m_vTotalList[i]->getRect().top + 20, str, strlen(str));
	}
}

void aStar::setTile(zeldaTileMap* pZeldaMap, int nStartIdxX, int nStartIdxY, int nEndIdxX, int nEndIdxY)
{
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			aStarTile* node = new aStarTile;
			node->init(_camera, j, i);
			node->setAttribute("normal");
			//node->setColor(RGB(0, 255, 255));
			m_vTotalList.push_back(node);
		}
	}

	for (int i = 0; i < m_vTotalList.size(); i++)
	{
		if (m_vTotalList[i]->getIdxX() == nStartIdxX && m_vTotalList[i]->getIdxY() == nStartIdxY)
		{
			m_pStartTile = m_vTotalList[i];
			m_pStartTile->setColor(RGB(0, 255, 255));
			m_pStartTile->setAttribute("start");
		}

		if (m_vTotalList[i]->getIdxX() == nEndIdxX && m_vTotalList[i]->getIdxY() == nEndIdxY)
		{
			m_pEndTile = m_vTotalList[i];
			m_pEndTile->setColor(RGB(0, 255, 255));
			m_pEndTile->setAttribute("end");
		}
	}

	m_pCurTile = m_pStartTile;


	BOOL* pAttributeMove = pZeldaMap->getAttribute(E_ATR_MOVE);

	for (int i = 0; i < TILETOTAL; i++)
	{
		if (pAttributeMove[i] == FALSE)
		{
			m_vTotalList[i]->setColor(RGB(255, 0, 0));
			m_vTotalList[i]->setAttribute("wall");
		}
	}

}

std::vector<aStarTile*> aStar::addOpenList(aStarTile * pCurTile)
{
	int startX = pCurTile->getIdxX() - 1;
	int startY = pCurTile->getIdxY() - 1;

	int findMaxX = 3;
	int findMaxY = 3;
	int findMinX = 0;
	int findMinY = 0;

	if (startX == -1) findMinX = 1;
	else if (startX == TILEX - 2) findMaxX--;

	if (startY == -1) findMinY = 1;
	else if (startY == TILEY - 2) findMaxY--;

	for (int i = findMinY; i < findMaxY; i++)
	{
		for (int j = findMinX; j < findMaxX; j++)
		{
			aStarTile* node = m_vTotalList[(startY * TILEX) + startX + j + (i * TILEX)];

			if (!node->getIsOpen()) continue;
			if (node->getAttribute() == "start") continue;
			if (node->getAttribute() == "wall") continue;

			node->setParentNode(m_pCurTile);

			bool addObj = true;
			for (m_viOpenList = m_vOpenList.begin(); m_viOpenList != m_vOpenList.end(); ++m_viOpenList)
			{
				if (*m_viOpenList == node)
				{
					addObj = false;
					break;
				}
			}

			if (node->getAttribute() != "end") node->setColor(RGB(128, 64, 28));

			if (!addObj) continue;

			m_vOpenList.push_back(node);
		}
	}
	return m_vOpenList;
}

void aStar::pathFinder(aStarTile * pCurTile)
{
	float tempTotalCost = 5000;
	aStarTile* tempTile = NULL;

	for (int i = 0; i < addOpenList(pCurTile).size(); i++)
	{
		m_vOpenList[i]->setCostToGoal((abs(m_pEndTile->getIdxX() - m_vOpenList[i]->getIdxX())
			+ abs(m_pEndTile->getIdxY() - m_vOpenList[i]->getIdxY())) * 10);

		POINT center1 = m_vOpenList[i]->getParentNode()->getCenter();
		POINT center2 = m_vOpenList[i]->getCenter();

		m_vOpenList[i]->setCostFromStart((getDistance(center1.x, center1.y, center2.x, center2.y) > TILEWIDTH) ? 14 : 10);

		m_vOpenList[i]->setTotalCost(m_vOpenList[i]->getCostToGoal() +
			m_vOpenList[i]->getCostFromStart());

		if (tempTotalCost > m_vOpenList[i]->getTotalCost())
		{
			tempTotalCost = m_vOpenList[i]->getTotalCost();
			tempTile = m_vOpenList[i];
		}

		bool addObj = true;
		for (m_viOpenList = m_vOpenList.begin(); m_viOpenList != m_vOpenList.end(); ++m_viOpenList)
		{
			if (*m_viOpenList == tempTile)
			{
				addObj = false;
				break;
			}
		}

		m_vOpenList[i]->setIsOpen(false);
		if (!addObj) continue;
		m_vOpenList.push_back(tempTile);
	}

	if (tempTile->getAttribute() == "end")
	{
		while (m_pCurTile->getParentNode() != NULL)
		{
			m_vPathList.push_back(m_pCurTile);
			m_pCurTile->setColor(RGB(0, 255, 125));
			m_pCurTile = m_pCurTile->getParentNode();
		}

		m_bIsEnd = true;
		return;
	}

	m_vCloseList.push_back(tempTile);
	bool addObj = true;
	for (m_viOpenList = m_vOpenList.begin(); m_viOpenList != m_vOpenList.end(); ++m_viOpenList)
	{
		if (*m_viOpenList == tempTile)
		{
			m_viOpenList = m_vOpenList.erase(m_viOpenList);
			break;
		}
	}

	m_pCurTile = tempTile;
	pathFinder(m_pCurTile);
}

void aStar::resetAstar(zeldaTileMap* pZeldaMap, int nStartIdxX, int nStartIdxY, int nEndIdxX, int nEndIdxY)
{
	if (nStartIdxX == nEndIdxX && nStartIdxY == nEndIdxY) return;
	this->clearAstar();

	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			if (m_vTotalList[i * TILEX + j]->getAttribute() == "wall")
			{
				m_vTotalList[i * TILEX + j]->release();
				m_vTotalList[i * TILEX + j]->resetTile();

				m_vTotalList[i * TILEX + j]->setAttribute("wall");
				m_vTotalList[i * TILEX + j]->setColor(RGB(255, 0, 0));
			}
			else
			{
				m_vTotalList[i * TILEX + j]->release();
				m_vTotalList[i * TILEX + j]->resetTile();

				m_vTotalList[i * TILEX + j]->setAttribute("normal");
				m_vTotalList[i * TILEX + j]->setColor(RGB(255, 255, 255));

				if (m_vTotalList[i * TILEX + j]->getIdxX() == nStartIdxX && m_vTotalList[i * TILEX + j]->getIdxY() == nStartIdxY)
				{
					m_pStartTile = m_vTotalList[i * TILEX + j];
					m_pStartTile->setAttribute("start");
					m_pStartTile->setColor(RGB(255, 0, 0));
				}

				if (m_vTotalList[i * TILEX + j]->getIdxX() == nEndIdxX && m_vTotalList[i * TILEX + j]->getIdxY() == nEndIdxY)
				{
					m_pEndTile = m_vTotalList[i * TILEX + j];
					m_pEndTile->setAttribute("end");
					m_pEndTile->setColor(RGB(255, 0, 0));
				}
			}
		}
	}

	m_pCurTile = m_pStartTile;
	m_bIsEnd = false;
}

void aStar::clearAstar()
{
	m_vOpenList.clear();
	m_vCloseList.clear();
	m_vPathList.clear();

	m_nCount = 0;
	m_bIsStart = 0;
	m_bIsEnd = 0;
}

void aStar::tilesUpdate()
{
	for (int i = 0; i < m_vTotalList.size(); i++)
	{
		m_vTotalList[i]->update();
	}
}

void aStar::setCharacterPath(vector<aStarTile*>& realPath, bool* bIsVFull)
{
	if (m_vPathList.size() <= 0) return;

	for (int i = 0; i < realPath.size(); i++)
	{
		realPath.erase(realPath.begin() + i);
	}
	realPath.clear();
	realPath = m_vPathList;

	for (int i = 0; i < (realPath.size() / 2); i++)
	{
		aStarTile* temp;

		temp = realPath[i];
		realPath[i] = realPath[(realPath.size() - 1) - i];
		realPath[(realPath.size() - 1) - i] = temp;
	}

	(*bIsVFull) = true;
}