#include "stdafx.h"
#include "mapTool.h"


mapTool::mapTool() :
	_camera(NULL),
	_rc(),
	_interFaceRc(SET_TERRAIN_RC),
	_tiles(),
	_sampleTiles(),
	_sampleTiles2(),
	_sampleTiles3(),
	_imgTile(NULL),
	_imgTile2(NULL),
	_imgTile3(NULL),
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

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		crashInterFaceRc();
		selectTile();
		
	}
	if (KEYMANAGER->isStayKeyDown(VK_RBUTTON))
	{
		setMap();
	}

	showDefault();
}

void mapTool::render()
{
	//현재 내가 선택한 버튼의 정보를 텍스트아웃해줍니다.
	drawNowInterfaceRect();

	//현재 맵툴의 실제 타일맵과 샘플타일을 그려줍니다.
	drawTile();
	
	//격자
	//drawGrid();


	//카메라 조정 렉트
	//drawCameraRect();

	// 타일속성 그려주기
	//	drawTileName();

	//배경
	IMAGEMANAGER->findImage("MAPTOOL_BACKGROUND")->render(getMemDC(), 0, 0);
	//카메라 조정 화살
	IMAGEMANAGER->findImage("MAPTOOL_ARROW")->render(getMemDC(), 0, 0);
	//샘플타일 그려주기
	drawSampleTile();
	
	//샘플타일배경
	drawSampleBack();

	//프레임
	IMAGEMANAGER->findImage("MAPTOOL_FRAME")->render(getMemDC(), 0, 0);

	//drawButton();

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
			_sampleTiles[i * SAMPLETILEX + j].rcTile = RectMake(WINSIZEX + (j * SAMPLETILEWIDTH), (i * SAMPLETILEHEIGHT)+120, SAMPLETILESIZE, SAMPLETILESIZE);
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

	for (int i = 0; i < SAMPLETILEY3; i++)
	{
		for (int j = 0; j < SAMPLETILEX3; j++)
		{
			_sampleTiles3[i*SAMPLETILEX3 + j].terrainFrameX = j;
			_sampleTiles3[i*SAMPLETILEX3 + j].terrainFrameY = i;
			_sampleTiles3[i*SAMPLETILEX3 + j].objFrameX = j;
			_sampleTiles3[i*SAMPLETILEX3 + j].objFrameY = i;
			_sampleTiles3[i*SAMPLETILEX3 + j].imgKind = 1;
			_sampleTiles3[i*SAMPLETILEX3 + j].rcTile = RectMake(WINSIZEX + (j * SAMPLETILESIZE), (i * SAMPLETILESIZE) + 400, SAMPLETILESIZE, SAMPLETILESIZE);
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
		_tiles[i].obj2 = OBJ_NONE;
	}
}

void mapTool::setMap(void)
{

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].rc.left >= WINSIZEX - 519) continue;
		if (PtInRect(&_tiles[i].rc, _ptMouse))
		{
			switch (_interFaceRc)
			{
			case SET_TERRAIN_RC:
				_tiles[i].terrainFrameX = _currentTile.terFrameX;
				_tiles[i].terrainFrameY = _currentTile.terFrameY;
				_tiles[i].terrain = terrainSelect(_tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
				_tiles[i].tileKind = KIND_TERRAIN;
				break;

			case SET_OBJECT1_RC:
				_tiles[i].objFrameX = _currentTile.objFrameX;
				_tiles[i].objFrameY = _currentTile.objFrameY;
				_tiles[i].obj = objSelect(_tiles[i].objFrameX, _tiles[i].objFrameY);
				_tiles[i].tileKind = KIND_OBJ1;
				break;

			case SET_OBJECT2_RC:
				_tiles[i].objFrameX = _currentTile.objFrameX;
				_tiles[i].objFrameY = _currentTile.objFrameY;
				_tiles[i].obj2 = objSelect2(_tiles[i].objFrameX, _tiles[i].objFrameY);
				_tiles[i].tileKind = KIND_OBJ2;
				break;

			case SET_ERASER_RC:
				_tiles[i].objFrameX = 0;
				_tiles[i].objFrameY = 0;
				_tiles[i].obj = OBJ_NONE;
				_tiles[i].obj2 = OBJ_NONE;
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


	//뭐가 문젠지 모르겠지만 리셋해줌!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
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
		_bSample3In = TRUE;
		_bSample3Out = FALSE;

		if (_sampleTiles2[0].rcTile.left < WINSIZEX)
		{
			for (int i = 0; i < SAMPLETOTAL2; i++)
			{
				_sampleTiles2[i].rcTile.left += 10;
				_sampleTiles2[i].rcTile.right += 10;
			}
		}

		if (_sampleTiles[0].rcTile.left > WINSIZEX - _imgTile->getWidth() - 100)
		{
			for (int i = 0; i < SAMPLETOTAL; i++)
			{
				_sampleTiles[i].rcTile.left -= 10;
				_sampleTiles[i].rcTile.right -= 10;
			}
		}

		if (_sampleTiles3[0].rcTile.left < WINSIZEX)
		{
			for (int i = 0; i < SAMPLETOTAL3; i++)
			{
				_sampleTiles3[i].rcTile.left += 10;
				_sampleTiles3[i].rcTile.right += 10;
			}
		}
		break;
	
	case SET_OBJECT1_RC:
		_bSample1In = TRUE;
		_bSample1IsOut = FALSE;
		_bSample2In = FALSE;
		_bSample2Out = TRUE;
		_bSample3In = TRUE;
		_bSample3Out = FALSE;
		if (_sampleTiles[0].rcTile.left < WINSIZEX)
		{
			for (int i = 0; i < SAMPLETOTAL; i++)
			{
				_sampleTiles[i].rcTile.left += 10;
				_sampleTiles[i].rcTile.right += 10;
			}
		}

		if (_sampleTiles2[0].rcTile.left > WINSIZEX - _imgTile2->getWidth() - 75)
		{
			for (int i = 0; i < SAMPLETOTAL2; i++)
			{
				_sampleTiles2[i].rcTile.left -= 10;
				_sampleTiles2[i].rcTile.right -= 10;
			}
		}

		if (_sampleTiles3[0].rcTile.left < WINSIZEX)
		{
			for (int i = 0; i < SAMPLETOTAL3; i++)
			{
				_sampleTiles3[i].rcTile.left += 10;
				_sampleTiles3[i].rcTile.right += 10;
			}
		}
		break;

	case SET_OBJECT2_RC:
		_bSample1In = TRUE;
		_bSample1IsOut = FALSE;
		_bSample2In = TRUE;
		_bSample2Out = FALSE;
		_bSample3In = FALSE;
		_bSample3Out = TRUE;

		if (_sampleTiles3[0].rcTile.left > WINSIZEX - _imgTile3->getWidth()- 25)
		{
			for (int i = 0; i < SAMPLETOTAL3; i++)
			{
				_sampleTiles3[i].rcTile.left -= 10;
				_sampleTiles3[i].rcTile.right -= 10;
			}
		}

		if (_sampleTiles[0].rcTile.left < WINSIZEX)
		{
			for (int i = 0; i < SAMPLETOTAL; i++)
			{
				_sampleTiles[i].rcTile.left += 10;
				_sampleTiles[i].rcTile.right += 10;
			}
		}

		if (_sampleTiles2[0].rcTile.left < WINSIZEX)
		{
			for (int i = 0; i < SAMPLETOTAL2; i++)
			{
				_sampleTiles2[i].rcTile.left += 10;
				_sampleTiles2[i].rcTile.right += 10;
			}
		}

		break;

	
	}
}

void mapTool::drawGrid()
{
	if (!_showCamera)
	{
		_grid->render(getMemDC(), _camera->getStartX(), _camera->getStartY());
	}
}

void mapTool::drawSampleBack()
{
	switch (_interFaceRc)
	{
		case SET_TERRAIN_RC:
			_imgSample1->render(getMemDC(), _sampleTiles[0].rcTile.left - 5, _sampleTiles[0].rcTile.top - 5);
		break;
		
		case SET_OBJECT1_RC:
			_imgSample2->render(getMemDC(), _sampleTiles2[0].rcTile.left - 5, _sampleTiles2[0].rcTile.top - 5);
		break;
		
		case SET_OBJECT2_RC:
			_imgSample3->render(getMemDC(), _sampleTiles3[0].rcTile.left - 5, _sampleTiles3[0].rcTile.top - 5);
		break;
	
		case SET_ENEMY_RC:
		break;
	
		default:
			break;
	}
}

void mapTool::createButton()
{
	for (int i = 0; i < INTERFACE_END; i++)
	{
		_rc[i] = RectMake(112 + (144 * i), 67, 120, 48);
	}
}

void mapTool::drawButton()
{
	for (int i = 0; i < INTERFACE_END; i++)
	{
		Rectangle(getMemDC(), _rc[i].left, _rc[i].top, _rc[i].right, _rc[i].bottom);
	}
}

void mapTool::drawTile()
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

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].rc.left >= WINSIZEX - WINSIZEX / 3 + 50) continue;
		if (_tiles[i].obj2 == OBJ_NONE)continue;
		if (_showCamera) _imgTile6->frameRender(getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].objFrameX, _tiles[i].objFrameY);
		else _imgTile5->frameRender(getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].objFrameX, _tiles[i].objFrameY);
	}
}

void mapTool::drawSampleTile()
{
	_imgTile->render(getMemDC(), _sampleTiles[0].rcTile.left, _sampleTiles[0].rcTile.top);
	_imgTile2->render(getMemDC(), _sampleTiles2[0].rcTile.left, _sampleTiles2[0].rcTile.top);
	_imgTile5->render(getMemDC(), _sampleTiles3[0].rcTile.left, _sampleTiles3[0].rcTile.top);
}

void mapTool::drawNowInterfaceRect()
{
	switch (_interFaceRc)
	{
	case SAVE_RC:

		TextOut(getMemDC(), WINSIZEX - 200, 700, "세이브입니다", strlen("세이브입니다"));

		break;
	case LOAD_RC:

		TextOut(getMemDC(), WINSIZEX - 200, 700, "로드입니다", strlen("로드입니다"));

		break;
	case SET_TERRAIN_RC:

		TextOut(getMemDC(), WINSIZEX - 200, 700, "지형입니다", strlen("지형입니다"));

		break;
	case SET_OBJECT1_RC:

		TextOut(getMemDC(), WINSIZEX - 200, 700, "오브젝트1입니다", strlen("오브젝트1입니다"));

		break;
	case SET_OBJECT2_RC:
		TextOut(getMemDC(), WINSIZEX - 200, 700, "오브젝트2입니다", strlen("오브젝트2입니다"));

		break;
	}
}

void mapTool::loadImage()
{
	//sample1 -> 이미지 작은것 + 큰것
	_imgTile = IMAGEMANAGER->addFrameImage("mapTiles", "image/sample_ter.bmp", 0, 0, 180, 120, SAMPLETILEX, SAMPLETILEY, true, RGB(255, 0, 255));
	_imgTile3 = IMAGEMANAGER->addFrameImage("mapTiles3", "image/sample80_ter.bmp", 0, 0, 480, 320, SAMPLETILEX, SAMPLETILEY, true, RGB(255, 0, 255));

	_imgTile2 = IMAGEMANAGER->addFrameImage("mapTiles2", "image/sample_obj_30_1.bmp", 0, 0, 420, 300, SAMPLETILEX2, SAMPLETILEY2, true, RGB(255, 0, 255));
	_imgTile4 = IMAGEMANAGER->addFrameImage("mapTIles4", "image/sample_obj_80_1.bmp", 0, 0, 1120, 800, SAMPLETILEX2, SAMPLETILEY2, true, RGB(255, 0, 255));

	_imgTile5 = IMAGEMANAGER->addFrameImage("mapTiles5", "image/sample_obj_30_2.bmp", 0, 0, 450, 330, SAMPLETILEX3, SAMPLETILEY3, true, RGB(255, 0, 255));
	_imgTile6 = IMAGEMANAGER->addFrameImage("mapTiles6", "image/sample_obj_80_2.bmp", 0, 0, 1200, 880, SAMPLETILEX3, SAMPLETILEY3, true, RGB(255, 0, 255));

	_imgSample1 = IMAGEMANAGER->addImage("sample1", "image/MAPTOOL_SAMPLE_TER_1.bmp", 190, 130, true, RGB(255, 0, 255));
	_imgSample2 = IMAGEMANAGER->addImage("sample2", "image/MAPTOOL_SAMPLE_OBJ_1.bmp", 430, 310, true, RGB(255, 0, 255));
	_imgSample3 = IMAGEMANAGER->addImage("sample3", "image/MAPTOOL_SAMPLE_OBJ_2.bmp", 460, 340, true, RGB(255, 0, 255));

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

	for (int i = 0; i < SAMPLETILEX3 * SAMPLETILEY3; i++)
	{
		if (PtInRect(&_sampleTiles3[i].rcTile, _ptMouse))
		{
			_currentTile.objFrameX = _sampleTiles3[i].objFrameX;
			_currentTile.objFrameY = _sampleTiles3[i].objFrameY;
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
		switch (_tiles[i].terrain)
		{
		case TR_BASE:
			TextOut(getMemDC(), _tiles[i].rc.left + 10, _tiles[i].rc.top + 10, "기본", strlen("기본"));
			break;
		case TR_GRASS:
			TextOut(getMemDC(), _tiles[i].rc.left + 10, _tiles[i].rc.top + 10, "잔디", strlen("잔디"));
			break;
		case TR_DESERT:
			TextOut(getMemDC(), _tiles[i].rc.left + 10, _tiles[i].rc.top + 10, "모래", strlen("모래"));
			break;
		case TR_WATER:
			TextOut(getMemDC(), _tiles[i].rc.left + 10, _tiles[i].rc.top + 10, "물", strlen("물"));
			break;

		}
		switch (_tiles[i].obj)
		{
			case OBJ_WALL:
			TextOut(getMemDC(), _tiles[i].rc.left + 10, _tiles[i].rc.top + 10, "벽", strlen("벽"));
			break;

			default:
				TextOut(getMemDC(), _tiles[i].rc.left + 10, _tiles[i].rc.top + 10, "?", strlen("?"));
			break;

		}

		switch (_tiles[i].obj2)
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
		case OBJ_POT:

			TextOut(getMemDC(), _tiles[i].rc.left + 10, _tiles[i].rc.top + 10, "항아리", strlen("항아리"));

			break;

		case OBJ_SMALL_BOX1:

			TextOut(getMemDC(), _tiles[i].rc.left + 10, _tiles[i].rc.top + 10, "작은박1", strlen("항아리1"));

			break;

		case OBJ_SMALL_BOX2:

			TextOut(getMemDC(), _tiles[i].rc.left + 10, _tiles[i].rc.top + 10, "작은박2", strlen("항아리1"));

			break;

		case OBJ_DOOR_UP_CLOSE:

			TextOut(getMemDC(), _tiles[i].rc.left + 10, _tiles[i].rc.top + 10, "문위닫힘", strlen("항아리1"));

			break;

		case OBJ_DOOR_UP_OPEN:

			TextOut(getMemDC(), _tiles[i].rc.left + 10, _tiles[i].rc.top + 10, "문위열림", strlen("항아리1"));

			break;

		case OBJ_DOOR_DOWN_CLOSE:

			TextOut(getMemDC(), _tiles[i].rc.left + 10, _tiles[i].rc.top + 10, "문밑닫힘", strlen("항아리1"));

			break;

		case OBJ_DOOR_DOWN_OPEN:

			TextOut(getMemDC(), _tiles[i].rc.left + 10, _tiles[i].rc.top + 10, "문밑열림", strlen("항아리1"));

			break;

		case OBJ_DOOR2_UP_CLOSE:

			TextOut(getMemDC(), _tiles[i].rc.left + 10, _tiles[i].rc.top + 10, "문2위닫", strlen("항아리1"));

			break;

		case OBJ_DOOR2_UP_OPEN:

			TextOut(getMemDC(), _tiles[i].rc.left + 10, _tiles[i].rc.top + 10, "문2위열", strlen("항아리1"));

			break;

		case OBJ_DOOR2_DOWN_CLOSE:

			TextOut(getMemDC(), _tiles[i].rc.left + 10, _tiles[i].rc.top + 10, "문2밑닫", strlen("항아리1"));

			break;

		case OBJ_DOOR2_DOWN_OPEN:

			TextOut(getMemDC(), _tiles[i].rc.left + 10, _tiles[i].rc.top + 10, "문2밑열", strlen("항아리1"));

			break;

		default:

			TextOut(getMemDC(), _tiles[i].rc.left + 10, _tiles[i].rc.top + 10, "?", strlen("?"));

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
		for (int j = 0; j < 10; j++)
		{
			if (frameX == i && frameY == j)
			{
				return OBJ_WALL;
			}
		}
	}
	
}

OBJECT mapTool::objSelect2(int frameX, int frameY)
{
	if (frameX == 0 && frameY == 0)
	{
		return OBJ_BUTTON1_UP;
	}

	else if (frameX == 0 && frameY == 1)
	{
		return OBJ_BUTTON1_DOWN;
	}

	else if (frameX == 1 && frameY == 0)
	{
		return OBJ_BUTTON2_UP;
	}

	else if (frameX == 1 && frameY == 1)
	{
		return OBJ_BUTTON2_DOWN;
	}

	else if (frameX == 2 && frameY == 0)
	{
		return OBJ_BRIDGE1;
	}

	else if (frameX == 2 && frameY == 1)
	{
		return OBJ_BRIDGE2;
	}

	else if (frameX == 3 && frameY == 0)
	{
		return OBJ_FIRE1;
	}

	else if (frameX == 3 && frameY == 1)
	{
		return OBJ_FIRE2;
	}

	else if (frameX == 4 && frameY == 0)
	{
		return OBJ_COLUMN1;
	}

	else if (frameX == 4 && frameY == 1)
	{
		return OBJ_COLUMN2;
	}

	else if (frameX == 5 && frameY == 0)
	{
		return OBJ_SMALL_BOX1;
	}

	else if (frameX == 5 && frameY == 1)
	{
		return OBJ_SMALL_BOX2;
	}

	else if (frameX == 6 && frameY == 0)
	{
		return OBJ_BOX1;
	}

	else if (frameX == 6 && frameY == 1)
	{
		return OBJ_BOX2;
	}

	else if (frameX == 7 && frameY == 0)
	{
		return OBJ_BOX1;
	}

	else if (frameX == 7 && frameY == 1)
	{
		return OBJ_BOX2;
	}

	else if (frameX == 8 && frameY == 1)
	{
		return OBJ_POT;
	}

	else if (frameX == 1 && frameY == 3)
	{
		return OBJ_DOOR_UP_CLOSE;
	}

	else if (frameX == 1 && frameY == 4)
	{
		return OBJ_DOOR_UP_OPEN;
	}

	else if (frameX == 4 && frameY == 2)
	{
		return OBJ_DOOR_DOWN_OPEN;
	}

	else if (frameX == 4 && frameY == 3)
	{
		return OBJ_DOOR_DOWN_CLOSE;
	}

	else if (frameX == 1 && frameY == 6)
	{
		return OBJ_DOOR2_UP_CLOSE;
	}

	else if (frameX == 2 && frameY == 6)
	{
		return OBJ_DOOR2_UP_CLOSE;
	}

	else if (frameX == 3 && frameY == 6)
	{
		return OBJ_DOOR2_UP_CLOSE;
	}

	else if (frameX == 1 && frameY == 7)
	{
		return OBJ_DOOR2_UP_CLOSE;
	}

	else if (frameX == 2 && frameY == 7)
	{
		return OBJ_DOOR2_UP_CLOSE;
	}

	else if (frameX == 3 && frameY == 7)
	{
		return OBJ_DOOR2_UP_CLOSE;
	}

	else if (frameX == 11 && frameY == 6)
	{
		return OBJ_DOOR2_UP_OPEN;
	}

	else if (frameX == 12 && frameY == 6)
	{
		return OBJ_DOOR2_UP_OPEN;
	}

	else if (frameX == 13 && frameY == 6)
	{
		return OBJ_DOOR2_UP_OPEN;
	}

	else if (frameX == 11 && frameY == 7)
	{
		return OBJ_DOOR2_UP_OPEN;
	}

	else if (frameX == 12 && frameY == 7)
	{
		return OBJ_DOOR2_UP_OPEN;
	}

	else if (frameX == 13 && frameY == 7)
	{
		return OBJ_DOOR2_UP_OPEN;
	}

	else if (frameX == 1 && frameY == 8)
	{
		return OBJ_DOOR2_DOWN_CLOSE;
	}

	else if (frameX == 2 && frameY == 8)
	{
		return OBJ_DOOR2_DOWN_CLOSE;
	}

	else if (frameX == 3 && frameY == 8)
	{
		return OBJ_DOOR2_DOWN_CLOSE;
	}

	else if (frameX == 1 && frameY == 9)
	{
		return OBJ_DOOR2_DOWN_CLOSE;
	}

	else if (frameX == 2 && frameY == 9)
	{
		return OBJ_DOOR2_DOWN_CLOSE;
	}

	else if (frameX == 3 && frameY == 9)
	{
		return OBJ_DOOR2_DOWN_CLOSE;
	}

	else if (frameX == 11 && frameY == 8)
	{
		return OBJ_DOOR2_DOWN_OPEN;
	}

	else if (frameX == 12 && frameY == 8)
	{
		return OBJ_DOOR2_DOWN_OPEN;
	}

	else if (frameX == 13 && frameY == 8)
	{
		return OBJ_DOOR2_DOWN_OPEN;
	}

	else if (frameX == 11 && frameY == 9)
	{
		return OBJ_DOOR2_DOWN_OPEN;
	}

	else if (frameX == 12 && frameY == 9)
	{
		return OBJ_DOOR2_DOWN_OPEN;
	}

	else if (frameX == 13 && frameY == 9)
	{
		return OBJ_DOOR2_DOWN_OPEN;
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

	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
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
