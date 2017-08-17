#include "stdafx.h"
#include "aStarTile.h"
#include "camera.h"

aStarTile::aStarTile() :
	m_nIdxX(0),
	m_nIdxY(0),
	m_posCenter(),
	m_rc(),
	m_fTotalCost(0.F),
	m_fCostFromStart(0.F),
	m_fCostToGoal(0.F),
	m_bIsOpen(true),
	m_pParentNode(NULL),
	m_strAttribute(""),
	m_color(RGB(0, 0, 0)),
	m_hBrush(NULL),
	m_hPen()
{
}


aStarTile::~aStarTile()
{
}

HRESULT aStarTile::init(camera* camera, int nIdxX, int nIdxY)
{
	_camera = camera;

	m_fTotalCost = 0.F;
	m_fCostFromStart = 0.F;
	m_fCostToGoal = 0.F;
	m_bIsOpen = true;
	m_pParentNode = NULL;
	m_strAttribute = "";

	m_nIdxX = nIdxX;
	m_nIdxY = nIdxY;

	m_color = RGB(255, 255, 255);
	m_hBrush = CreateSolidBrush(m_color);
	m_hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));

	m_nDisX = m_nIdxX * TILEWIDTH + (TILEWIDTH / 2);
	m_nDisY = m_nIdxY * TILEHEIGHT + (TILEHEIGHT / 2);

	m_posCenter.x = _camera->getStartX() + m_nDisX;
	m_posCenter.y = _camera->getStartY() + m_nDisY;

	m_rc = RectMakeCenter(m_posCenter.x, m_posCenter.y, TILEWIDTH, TILEHEIGHT);

	return S_OK;
}

void aStarTile::release()
{
	DeleteObject(m_hBrush);
	DeleteObject(m_hPen);
}

void aStarTile::update()
{
	m_posCenter.x = _camera->getStartX() + m_nDisX;
	m_posCenter.y = _camera->getStartY() + m_nDisY;

	m_rc = RectMakeCenter(m_posCenter.x, m_posCenter.y, TILEWIDTH, TILEHEIGHT);
}

void aStarTile::render()
{
	SelectObject(getMemDC(), m_hBrush);
	FillRect(getMemDC(), &m_rc, m_hBrush);

	SelectObject(getMemDC(), m_hPen);
	Rectangle(getMemDC(), m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);
}

void aStarTile::resetTile()
{
	m_fTotalCost = 0.F;
	m_fCostFromStart = 0.F;
	m_fCostToGoal = 0.F;
	m_bIsOpen = true;
	m_pParentNode = NULL;
	m_strAttribute = "";

	m_color = RGB(255, 255, 255);
	m_hBrush = CreateSolidBrush(m_color);
	m_hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));

}
