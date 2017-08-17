#pragma once
#include "zeldaTileNode.h"
#include "gameNode.h"
#include "camera.h"

enum E_INTERFACE_RECT
{
	SAVE_RC,
	LOAD_RC,
	SET_TERRAIN_RC,
	SET_OBJECT1_RC,
	SET_OBJECT2_RC,
	SET_ERASER_RC,
	INTERFACE_END = 6
};

enum E_CAMERA_RC
{
	E_LEFT,
	E_RIGHT,
	E_UP,
	E_DOWN,
	E_CAMERA_RC_END = 4
};

struct tagRectCamera
{
	RECT rc[E_CAMERA_RC_END];

};

class mapTool : public gameNode
{
private:
	camera* _camera;

private:
	RECT _rc[INTERFACE_END];
	image* _imgButton[INTERFACE_END];

	image* _imgInterface;

	E_INTERFACE_RECT _interFaceRc;

	BOOL _bSample1In;
	BOOL _bSample1IsOut;
	BOOL _bSample2In;
	BOOL _bSample2Out;

private:
	tagTile _tiles[TILEX * TILEY];
	tagSampleTile _sampleTiles[SAMPLETILEX * SAMPLETILEY];
	tagSampleTile _sampleTiles2[SAMPLETILEX2 * SAMPLETILEY2];

	image* _imgTile;
	image* _imgTile2;
	image* _imgTile3;
	image* _imgTile4;
	image* _grid;

	tagCurrentTile _currentTile;

private:
	tagRectCamera _cameraRc;
	bool _showCamera;
	int _showWidth;
	int _showHeight;

public:
	mapTool();
	virtual ~mapTool();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void setupTiles(void);
	virtual void setMap(void);

	virtual void save(void);
	virtual void load(void);

	TERRAIN terrainSelect(int frameX, int frameY);
	OBJECT objSelect(int frameX, int frameY);

	void showDefault();

	void loadImage();
	void createButton();
	void drawButton();

	void drawTileAndSample();
	void drawNowInterfaceRect();
	void nowDrawInterFaceKind();
	void drawGrid();

	void crashInterFaceRc();
	void selectTile();

	//카메라 관련
	void setCameraRect();
	void drawCameraRect();
	void controlCamera();

	void drawTileName();
};

