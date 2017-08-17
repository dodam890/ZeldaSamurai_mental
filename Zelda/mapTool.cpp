#include "stdafx.h"
#include "mapTool.h"


mapTool::mapTool() :
	_camera(NULL),
	_rc(),
	_interFaceRc(SET_TERRAIN_RC),
	_tiles(),
	_sampleTiles(),
	_sampleTiles2(),
	_imgTile(NULL),
	_imgTile2(NULL),
	_currentTile(),
	_cameraRc(),
	_showWidth(0),
	_showHeight(0),
	_showCamera(false)
{
}

mapTool::~mapTool()
{
}

HRESULT mapTool::init()
{
	_camera = new camera;
	_camera->init();


	_showWidth = TILEWIDTH;
	_showHeight = TILEHEIGHT;
	_showCamera = true;
	_interFaceRc = SET_TERRAIN_RC;

	//이클래스에서 활용할 타일 전체 이미지 로드합니다.
	loadImage();

	//맵툴의 버튼그리기
	createButton();

	//타일맵, 샘플타일의 초기화
	setupTiles();

	//카메라 위치조절하는 렉트셋팅
	setCameraRect();

	return S_OK;
}

void mapTool::release()
{
}

void mapTool::update()
{
	//멥툴의 카메라 조정
	controlCamera();

	nowDrawInterFaceKind();

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		crashInterFaceRc();
		selectTile();
		setMap();
	}

	showDefault();
}

void mapTool::render()
{
	//현재 내가 선택한 버튼의 정보를 텍스트아웃해줍니다.
	//drawNowInterfaceRect();

	//현재 맵툴의 실제 타일맵과 샘플타일을 그려줍니다.
	drawTileAndSample();

	drawGrid();
	//인터페이스 버튼을 그려줍니다.
	drawButton();

	//카메라 조정 렉트
	//drawCameraRect();
	drawTileName();

	//적당히 알아서 순서 넣어라
	//배경
	IMAGEMANAGER->findImage("MAPTOOL_BACKGROUND")->render(getMemDC(), 0, 0);
	//카메라 조정 화살
	IMAGEMANAGER->findImage("MAPTOOL_ARROW")->render(getMemDC(), 0, 0);
	//프레임
	IMAGEMANAGER->findImage("MAPTOOL_FRAME")->render(getMemDC(), 0, 0);
}

void mapTool::setupTiles(void)
{
	_interFaceRc = SET_TERRAIN_RC;

	for (int i = 0; i < SAMPLETILEY; i++)
	{
		for (int j = 0; j < SAMPLETILEX; j++)
		{
			_sampleTiles[i * SAMPLETILEX + j].terrainFrameX = j;
			_sampleTiles[i * SAMPLETILEX + j].terrainFrameY = i;
			_sampleTiles[i * SAMPLETILEX + j].objFrameX = j;
			_sampleTiles[i * SAMPLETILEX + j].objFrameY = i;
			_sampleTiles[i * SAMPLETILEX + j].imgKind = 0;
			_sampleTiles[i * SAMPLETILEX + j].rcTile = RectMake(WINSIZEX + (j * SAMPLETILEWIDTH), (i * SAMPLETILEHEIGHT), SAMPLETILESIZE, SAMPLETILESIZE);
		}
	}

	for (int i = 0; i < SAMPLETILEY2; i++)
	{
		for (int j = 0; j < SAMPLETILEX2; j++)
		{
			_sampleTiles2[i*SAMPLETILEX2 + j].terrainFrameX = j;
			_sampleTiles2[i*SAMPLETILEX2 + j].terrainFrameY = i;
			_sampleTiles2[i*SAMPLETILEX2 + j].objFrameX = j;
			_sampleTiles2[i*SAMPLETILEX2 + j].objFrameY = i;
			_sampleTiles2[i*SAMPLETILEX2 + j].imgKind = 1;
			_sampleTiles2[i*SAMPLETILEX2 + j].rcTile = RectMake(WINSIZEX + (j * SAMPLETILESIZE), (i * SAMPLETILESIZE) + 250, SAMPLETILESIZE, SAMPLETILESIZE);
		}
	}

	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			_tiles[i * TILEX + j].disX = TILESIZE / 2 + j * TILESIZE + 81;
			_tiles[i * TILEX + j].disY = TILESIZE / 2 + i * TILESIZE + 132;

			_tiles[i * TILEX + j].posCenter.x = _camera->getStartX() + _tiles[i * TILEX + j].disX;
			_tiles[i * TILEX + j].posCenter.y = _camera->getStartY() + _tiles[i * TILEX + j].disY;

			_tiles[i * TILEX + j].rc = RectMakeCenter(_tiles[i * TILEX + j].posCenter.x, _tiles[i * TILEX + j].posCenter.y, TILESIZE, TILESIZE);
		}
	}

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		_tiles[i].terrainFrameX = 0;
		_tiles[i].terrainFrameY = 0;
		_tiles[i].objFrameX = 0;
		_tiles[i].objFrameY = 0;
		_tiles[i].terrain = terrainSelect(_tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
		_tiles[i].obj = OBJ_NONE;
	}
}

void mapTool::setMap(void)
{

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].rc.left >= WINSIZEX - WINSIZEX / 3 + 50) continue;
		if (PtInRect(&_tiles[i].rc, _ptMouse))
		{
			switch (_interFaceRc)
			{
			case SET_TERRAIN_RC:
				_tiles[i].terrainFrameX = _currentTile.terFrameX;
				_tiles[i].terrainFrameY = _currentTile.terFrameY;
				_tiles[i].terrain = terrainSelect(_tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
				break;

			case SET_OBJECT1_RC:
				_tiles[i].objFrameX = _currentTile.objFrameX;
				_tiles[i].objFrameY = _currentTile.objFrameY;
				_tiles[i].obj = objSelect(_tiles[i].objFrameX, _tiles[i].objFrameY);

				break;

			case SET_OBJECT2_RC:
				_tiles[i].objFrameX = _currentTile.objFrameX;
				_tiles[i].objFrameY = _currentTile.objFrameY;
				_tiles[i].obj = objSelect(_tiles[i].objFrameX, _tiles[i].objFrameY);

				break;

			case SET_ERASER_RC:
				_tiles[i].objFrameX = 0;
				_tiles[i].objFrameY = 0;
				_tiles[i].obj = OBJ_NONE;

				break;

			}
			InvalidateRect(_hWnd, NULL, false);
			break;
		}
	}
}

void mapTool::save(void)
{
	HANDLE file;
	DWORD write;

	file = CreateFile("mapSave00.map", GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &write, NULL);

	CloseHandle(file);
}

void mapTool::load(void)
{
	HANDLE file;
	DWORD read;

	file = CreateFile("mapSave00.map", GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);

	CloseHandle(file);
}

void mapTool::nowDrawInterFaceKind()
{
	switch (_interFaceRc)
	{
	case SAVE_RC:
		if (_bSample1In)
		{
			if (_sampleTiles[0].rcTile.left < WINSIZEX)
			{
				for (int i = 0; i < SAMPLETOTAL; i++)
				{
					_sampleTiles[i].rcTile.left += 10;
					_sampleTiles[i].rcTile.right += 10;
				}
			}

			if (_sampleTiles2[0].rcTile.left > WINSIZEX - _imgTile2->getWidth() - 10)
			{
				for (int i = 0; i < SAMPLETOTAL2; i++)
				{
					_sampleTiles2[i].rcTile.left -= 10;
					_sampleTiles2[i].rcTile.right -= 10;
				}
			}
		}
		else
		{
			if (_sampleTiles2[0].rcTile.left < WINSIZEX)
			{
				for (int i = 0; i < SAMPLETOTAL2; i++)
				{
					_sampleTiles2[i].rcTile.left += 10;
					_sampleTiles2[i].rcTile.right += 10;
				}
			}

			if (_sampleTiles[0].rcTile.left > WINSIZEX - _imgTile->getWidth() - 10)
			{
				for (int i = 0; i < SAMPLETOTAL; i++)
				{
					_sampleTiles[i].rcTile.left -= 10;
					_sampleTiles[i].rcTile.right -= 10;
				}
			}
		}
		break;
	case LOAD_RC:
		if (_bSample1In)
		{
			if (_sampleTiles[0].rcTile.left < WINSIZEX)
			{
				for (int i = 0; i < SAMPLETOTAL; i++)
				{
					_sampleTiles[i].rcTile.left += 10;
					_sampleTiles[i].rcTile.right += 10;
				}
			}

			if (_sampleTiles2[0].rcTile.left > WINSIZEX - _imgTile2->getWidth() - 10)
			{
				for (int i = 0; i < SAMPLETOTAL2; i++)
				{
					_sampleTiles2[i].rcTile.left -= 10;
					_sampleTiles2[i].rcTile.right -= 10;
				}
			}
		}
		else
		{
			if (_sampleTiles2[0].rcTile.left < WINSIZEX)
			{
				for (int i = 0; i < SAMPLETOTAL2; i++)
				{
					_sampleTiles2[i].rcTile.left += 10;
					_sampleTiles2[i].rcTile.right += 10;
				}
			}

			if (_sampleTiles[0].rcTile.left > WINSIZEX - _imgTile->getWidth() - 10)
			{
				for (int i = 0; i < SAMPLETOTAL; i++)
				{
					_sampleTiles[i].rcTile.left -= 10;
					_sampleTiles[i].rcTile.right -= 10;
				}
			}
		}
		break;
	case SET_TERRAIN_RC:
		_bSample1In = FALSE;
		_bSample1IsOut = TRUE;
		_bSample2In = TRUE;
		_bSample2Out = FALSE;

		if (_sampleTiles2[0].rcTile.left < WINSIZEX)
		{
			for (int i = 0; i < SAMPLETOTAL2; i++)
			{
				_sampleTiles2[i].rcTile.left += 10;
				_sampleTiles2[i].rcTile.right += 10;
			}
		}

		if (_sampleTiles[0].rcTile.left > WINSIZEX - _imgTile->getWidth() - 10)
		{
			for (int i = 0; i < SAMPLETOTAL; i++)
			{
				_sampleTiles[i].rcTile.left -= 10;
				_sampleTiles[i].rcTile.right -= 10;
			}
		}

		break;
	//case SET_OBJECT_RC:
	//	_bSample1In = TRUE;
	//	_bSample1IsOut = FALSE;
	//	_bSample2In = FALSE;
	//	_bSample2Out = TRUE;

	//	if (_sampleTiles[0].rcTile.left < WINSIZEX)
	//	{
	//		for (int i = 0; i < SAMPLETOTAL; i++)
	//		{
	//			_sampleTiles[i].rcTile.left += 10;
	//			_sampleTiles[i].rcTile.right += 10;
	//		}
	//	}

	//	if (_sampleTiles2[0].rcTile.left > WINSIZEX - _imgTile2->getWidth() - 10)
	//	{
	//		for (int i = 0; i < SAMPLETOTAL2; i++)
	//		{
	//			_sampleTiles2[i].rcTile.left -= 10;
	//			_sampleTiles2[i].rcTile.right -= 10;
	//		}
	//	}

	//	break;

	}
}

void mapTool::drawGrid()
{
	if (!_showCamera)
	{
		_grid->render(getMemDC(), _camera->getStartX(), _camera->getStartY());
	}
	//_imgInterface->render(getMemDC(), WINSIZEX - _imgInterface->getWidth(), 0);
}

void mapTool::createButton()
{
	for (int i = 0; i < INTERFACE_END; i++)
	{
		//_imgButton[i] = IMAGEMANAGER->addImage("interfaceButton", "image/button.bmp", 70, 30, FALSE, FALSE);
		//_rc[i] = RectMake(WINSIZEX - _imgInterface->getWidth(), i * 50, 70, 30);

		_rc[i] = RectMake(112 + (144 * i), 67, 120, 48);
	}
}

void mapTool::drawButton()
{
	//for (int i = 0; i < INTERFACE_END; i++)
	//{
	//	Rectangle(getMemDC(), _rc[i].left, _rc[i].top, _rc[i].right, _rc[i].bottom);
	//	_imgButton[i]->render(getMemDC(), _rc[i].left, _rc[i].top);
	//}

	//TextOut(getMemDC(), _rc[SAVE_RC].left + 1, _rc[SAVE_RC].top + 5, "[세이브으]", strlen("[세이브으]"));
	//TextOut(getMemDC(), _rc[LOAD_RC].left + 1, _rc[LOAD_RC].top + 5, "[로오드으]", strlen("[로오드으]"));
	//TextOut(getMemDC(), _rc[SET_TERRAIN_RC].left + 1, _rc[SET_TERRAIN_RC].top + 5, "[지형이다]", strlen("[지형이다]"));
	//TextOut(getMemDC(), _rc[SET_OBJECT_RC].left + 1, _rc[SET_OBJECT_RC].top + 5, "[오브젝트]", strlen("[오브젝트]"));
}

void mapTool::drawTileAndSample()
{
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].rc.left >= WINSIZEX - WINSIZEX / 3 + 50) continue;

		if (_showCamera) _imgTile3->frameRender(getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
		else _imgTile->frameRender(getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top , _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
	}

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].rc.left >= WINSIZEX - WINSIZEX / 3 + 50) continue;
		if (_tiles[i].obj == OBJ_NONE)continue;
		if (_showCamera) _imgTile4->frameRender(getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].objFrameX, _tiles[i].objFrameY);
		else _imgTile2->frameRender(getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].objFrameX, _tiles[i].objFrameY);
	}

	//_imgInterface->render(getMemDC(), WINSIZEX - _imgInterface->getWidth(), 0);

	_imgTile->render(getMemDC(), _sampleTiles[0].rcTile.left, _sampleTiles[0].rcTile.top);
	_imgTile2->render(getMemDC(), _sampleTiles2[0].rcTile.left, _sampleTiles2[0].rcTile.top);
}

//void mapTool::drawNowInterfaceRect()
//{
//	switch (_interFaceRc)
//	{
//	case SAVE_RC:
//
//		TextOut(getMemDC(), WINSIZEX - 200, 700, "세이브입니다", strlen("세이브입니다"));
//
//		break;
//	case LOAD_RC:
//
//		TextOut(getMemDC(), WINSIZEX - 200, 700, "로드입니다", strlen("로드입니다"));
//
//		break;
//	case SET_TERRAIN_RC:
//
//		TextOut(getMemDC(), WINSIZEX - 200, 700, "지형입니다", strlen("지형입니다"));
//
//		break;
//	case SET_OBJECT_RC:
//
//		TextOut(getMemDC(), WINSIZEX - 200, 700, "오브젝트입니다", strlen("오브젝트입니다"));
//
//		break;
//	}
//}

void mapTool::loadImage()
{
	//sample1 -> 이미지 작은것 + 큰것
	_imgTile = IMAGEMANAGER->addFrameImage("mapTiles", "image/sample_ter.bmp", 0, 0, 180, 120, SAMPLETILEX, SAMPLETILEY, true, RGB(255, 0, 255));
	_imgTile3 = IMAGEMANAGER->addFrameImage("mapTiles3", "image/sample80_ter.bmp", 0, 0, 480, 320, SAMPLETILEX, SAMPLETILEY, true, RGB(255, 0, 255));

	_imgTile2 = IMAGEMANAGER->addFrameImage("mapTiles2", "image/sample_obj.bmp", 0, 0, 420, 510, SAMPLETILEX2, SAMPLETILEY2, true, RGB(255, 0, 255));
	_imgTile4 = IMAGEMANAGER->addFrameImage("mapTIles4", "image/sample80_obj.bmp", 0, 0, 1120, 1360, SAMPLETILEX2, SAMPLETILEY2, true, RGB(255, 0, 255));

	//_imgInterface = IMAGEMANAGER->addImage("inter", "image/interface.bmp", 450, 800, TRUE, RGB(255, 0, 255));

	_grid = IMAGEMANAGER->addImage("grid", "image/grid.bmp", 900, 900, true, RGB(255, 0, 255));
}

void mapTool::crashInterFaceRc()
{
	for (int i = 0; i < INTERFACE_END; i++)
	{
		if (PtInRect(&_rc[i], _ptMouse))
		{
			if (i == SAVE_RC) save();
			else if (i == LOAD_RC) load();
			_interFaceRc = (E_INTERFACE_RECT)i;
		}
	}
}

void mapTool::selectTile()
{
	for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
	{
		if (PtInRect(&_sampleTiles[i].rcTile, _ptMouse))
		{

			_currentTile.terFrameX = _sampleTiles[i].terrainFrameX;
			_currentTile.terFrameY = _sampleTiles[i].terrainFrameY;
			break;
		}
	}

	for (int i = 0; i < SAMPLETILEX2 * SAMPLETILEY2; i++)
	{
		if (PtInRect(&_sampleTiles2[i].rcTile, _ptMouse))
		{
			_currentTile.objFrameX = _sampleTiles2[i].objFrameX;
			_currentTile.objFrameY = _sampleTiles2[i].objFrameY;
			break;
		}
	}

}

void mapTool::setCameraRect()
{
	_cameraRc.rc[E_LEFT] = RectMake(78, 408, 30, 57);
	_cameraRc.rc[E_RIGHT] = RectMake(654, 408, 30, 57);

	_cameraRc.rc[E_UP] = RectMake(353, 130, 30, 57);
	_cameraRc.rc[E_DOWN] = RectMake(353, 705, 30, 57);
}

void mapTool::drawCameraRect()
{
	for (int i = 0; i < E_CAMERA_RC_END; i++)
	{
		Rectangle(getMemDC(), _cameraRc.rc[i].left, _cameraRc.rc[i].top, _cameraRc.rc[i].right, _cameraRc.rc[i].bottom);
	}
}

void mapTool::controlCamera()
{

	if (_camera->isCameraXZeroSide() && PtInRect(&_cameraRc.rc[E_LEFT], _ptMouse))
	{
		_camera->setCameraX(_camera->getCameraX() - 20);
	}
	if (_camera->isCameraXEndSide() && PtInRect(&_cameraRc.rc[E_RIGHT], _ptMouse))
	{
		_camera->setCameraX(_camera->getCameraX() + 20);
	}
	if (_camera->isCameraYZeroSide() && PtInRect(&_cameraRc.rc[E_UP], _ptMouse))
	{
		_camera->setCameraY(_camera->getCameraY() - 20);
	}
	if (_camera->isCameraYEndSide() && PtInRect(&_cameraRc.rc[E_DOWN], _ptMouse))
	{
		_camera->setCameraY(_camera->getCameraY() + 20);
	}

	//여기바꿔야ㅑ해야해야해야해ㅑ해얗
	_camera->update(TILEX * _showWidth + 600, TILEY * _showHeight + 200);

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		_tiles[i].posCenter.x = _camera->getStartX() + _tiles[i].disX;
		_tiles[i].posCenter.y = _camera->getStartY() + _tiles[i].disY;
		_tiles[i].rc = RectMakeCenter(_tiles[i].posCenter.x, _tiles[i].posCenter.y, _showWidth, _showHeight);
	}
}

void mapTool::drawTileName()
{
	char str[128] = "";
	sprintf(str, "[objX : %d, objY : %d]", _currentTile.objFrameX, _currentTile.objFrameY);
	TextOut(getMemDC(), WINSIZEX - 200, WINSIZEY - 200, str, strlen(str));
	sprintf(str, "[terX : %d, terY : %d]", _currentTile.terFrameX, _currentTile.terFrameY);
	TextOut(getMemDC(), WINSIZEX - 200, WINSIZEY - 170, str, strlen(str));


	for (int i = 0; i < TILETOTAL; i++)
	{
		if (_tiles[i].rc.left >= WINSIZEX - WINSIZEX / 3 + 50) continue;

		switch (_tiles[i].obj)
		{
		case OBJ_WALL:

			TextOut(getMemDC(), _tiles[i].rc.left + 10, _tiles[i].rc.top + 10, "벽", strlen("벽"));

			break;
		case OBJ_BUTTON1_UP:

			TextOut(getMemDC(), _tiles[i].rc.left + 10, _tiles[i].rc.top + 10, "버튼1업", strlen("버튼1업"));

			break;
		case OBJ_BUTTON1_DOWN:

			TextOut(getMemDC(), _tiles[i].rc.left + 10, _tiles[i].rc.top + 10, "버튼1밑", strlen("버튼1밑"));

			break;
		case OBJ_BUTTON2_UP:

			TextOut(getMemDC(), _tiles[i].rc.left + 10, _tiles[i].rc.top + 10, "버튼2업", strlen("버튼1밑"));

			break;
		case OBJ_BUTTON2_DOWN:

			TextOut(getMemDC(), _tiles[i].rc.left + 10, _tiles[i].rc.top + 10, "버튼2밑", strlen("버튼1밑"));

			break;
		case OBJ_BRIDGE1:

			TextOut(getMemDC(), _tiles[i].rc.left + 10, _tiles[i].rc.top + 10, "다리1", strlen("다리1"));

			break;
		case OBJ_BRIDGE2:

			TextOut(getMemDC(), _tiles[i].rc.left + 10, _tiles[i].rc.top + 10, "다리2", strlen("다리2"));

			break;
		case OBJ_FIRE1:

			TextOut(getMemDC(), _tiles[i].rc.left + 10, _tiles[i].rc.top + 10, "불1", strlen("불1"));

			break;
		case OBJ_FIRE2:

			TextOut(getMemDC(), _tiles[i].rc.left + 10, _tiles[i].rc.top + 10, "불2", strlen("불1"));

			break;
		case OBJ_COLUMN1:

			TextOut(getMemDC(), _tiles[i].rc.left + 10, _tiles[i].rc.top + 10, "기둥1", strlen("불아1"));

			break;
		case OBJ_COLUMN2:

			TextOut(getMemDC(), _tiles[i].rc.left + 10, _tiles[i].rc.top + 10, "기둥2", strlen("불아1"));

			break;
		case OBJ_BOX1:

			TextOut(getMemDC(), _tiles[i].rc.left + 10, _tiles[i].rc.top + 10, "박스1", strlen("불아1"));

			break;
		case OBJ_BOX2:

			TextOut(getMemDC(), _tiles[i].rc.left + 10, _tiles[i].rc.top + 10, "박스2", strlen("불아1"));

			break;
		case OBJ_BOX3:

			TextOut(getMemDC(), _tiles[i].rc.left + 10, _tiles[i].rc.top + 10, "박스3", strlen("불아1"));

			break;
		case OBJ_BOX4:

			TextOut(getMemDC(), _tiles[i].rc.left + 10, _tiles[i].rc.top + 10, "박스4", strlen("불아1"));

			break;
		case OBJ_POT:

			TextOut(getMemDC(), _tiles[i].rc.left + 10, _tiles[i].rc.top + 10, "항아리", strlen("항아리"));

			break;
		default:

			TextOut(getMemDC(), _tiles[i].rc.left + 10, _tiles[i].rc.top + 10, "???", strlen("???"));

			break;
		}
	}
}

TERRAIN mapTool::terrainSelect(int frameX, int frameY)
{
	if (frameX == 0 & frameY == 0)
	{
		return TR_BASE;
	}
	else if (frameX == 1 && frameY == 0)
	{
		return TR_GRASS;
	}

	else if (frameX == 4 && frameY == 1)
	{
		return TR_DESERT;
	}

	else if (frameX == 3 && frameY == 1)
	{
		return TR_WATER;
	}

	else if (frameX == 5 && frameY == 0)
	{
		return TR_WATER;
	}

	else if (frameX == 5 && frameY == 1)
	{
		return TR_WATER;
	}

	for (int i = 0; i < 6; i++)
	{
		for (int j = 2; j < 4; j++)
		{
			if (frameX == i && frameY == j)
			{
				return TR_WATER;
			}
		}
	}
	return TR_BASE;
}

OBJECT mapTool::objSelect(int frameX, int frameY)
{
	for (int i = 0; i < 14; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (frameX == i && frameY == j)
			{
				return OBJ_WALL;
			}
		}
	}


	if (frameX == 0 && frameY == 15)
	{
		return OBJ_BUTTON1_UP;
	}

	else if (frameX == 0 && frameY == 16)
	{
		return OBJ_BUTTON1_DOWN;
	}

	else if (frameX == 1 && frameY == 15)
	{
		return OBJ_BUTTON2_UP;
	}

	else if (frameX == 1 && frameY == 16)
	{
		return OBJ_BUTTON2_DOWN;
	}

	else if (frameX == 2 && frameY == 15)
	{
		return OBJ_BRIDGE1;
	}

	else if (frameX == 2 && frameY == 16)
	{
		return OBJ_BRIDGE2;
	}

	else if (frameX == 3 && frameY == 15)
	{
		return OBJ_FIRE1;
	}

	else if (frameX == 3 && frameY == 16)
	{
		return OBJ_FIRE2;
	}

	else if (frameX == 4 && frameY == 15)
	{
		return OBJ_COLUMN1;
	}

	else if (frameX == 4 && frameY == 16)
	{
		return OBJ_COLUMN2;
	}

	else if (frameX == 5 && frameY == 15)
	{
		return OBJ_BOX1;
	}

	else if (frameX == 5 && frameY == 16)
	{
		return OBJ_BOX2;
	}

	else if (frameX == 6 && frameY == 15)
	{
		return OBJ_BOX3;
	}

	else if (frameX == 6 && frameY == 16)
	{
		return OBJ_BOX4;
	}

	else if (frameX == 7 && frameY == 15)
	{
		return OBJ_POT;
	}
	return OBJ_WALL;
}

void mapTool::showDefault()
{
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		_camera->resetCamera();
		_showCamera = true;

		_showWidth = TILEWIDTH;
		_showHeight = TILEHEIGHT;

		for (int i = 0; i < TILEY; i++)
		{
			for (int j = 0; j < TILEX; j++)
			{
				_tiles[i * TILEX + j].disX = TILESIZE / 2 + j * TILESIZE + 81;
				_tiles[i * TILEX + j].disY = TILESIZE / 2 + i * TILESIZE + 132;

				_tiles[i * TILEX + j].posCenter.x = _camera->getStartX() + _tiles[i * TILEX + j].disX;
				_tiles[i * TILEX + j].posCenter.y = _camera->getStartY() + _tiles[i * TILEX + j].disY;

				_tiles[i * TILEX + j].rc = RectMakeCenter(_tiles[i * TILEX + j].posCenter.x, _tiles[i * TILEX + j].posCenter.y, TILESIZE, TILESIZE);
			}
		}
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_camera->resetCamera();
		_showCamera = false;

		_showWidth = SAMPLETILEWIDTH;
		_showHeight = SAMPLETILEHEIGHT;

		for (int i = 0; i < TILEY; i++)
		{
			for (int j = 0; j < TILEX; j++)
			{
				_tiles[i * TILEX + j].disX = SAMPLETILESIZE / 2 + j * SAMPLETILESIZE + 81;
				_tiles[i * TILEX + j].disY = SAMPLETILESIZE / 2 + i * SAMPLETILESIZE + 132;

				_tiles[i * TILEX + j].posCenter.x = _camera->getStartX() + _tiles[i * TILEX + j].disX;
				_tiles[i * TILEX + j].posCenter.y = _camera->getStartY() + _tiles[i * TILEX + j].disY;

				_tiles[i * TILEX + j].rc = RectMakeCenter(_tiles[i * TILEX + j].posCenter.x, _tiles[i * TILEX + j].posCenter.y, SAMPLETILESIZE, SAMPLETILESIZE);
			}
		}
	}

}
