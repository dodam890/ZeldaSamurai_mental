//#pragma once
//#include "zeldaTileNode.h"
//#include "gameNode.h"
//#include "camera.h"
//
//enum E_INTERFACE_RECT
//{
//	SAVE_RC,
//	LOAD_RC,
//	SET_TERRAIN_RC,
//	SET_OBJECT1_RC,
//	SET_OBJECT2_RC,
//	SET_ERASER_RC,
//	SET_ENEMY_RC,
//	INTERFACE_END = 7
//};
//
//enum E_CAMERA_RC
//{
//	E_LEFT,
//	E_RIGHT,
//	E_UP,
//	E_DOWN,
//	E_CAMERA_RC_END = 4
//};
//
//struct tagRectCamera
//{
//	RECT rc[E_CAMERA_RC_END];
//
//};
//
//class mapTool : public gameNode
//{
//private:
//	camera* _camera;
//
//private:
//	RECT _rc[INTERFACE_END];
//	E_INTERFACE_RECT _interFaceRc;
//
//	BOOL _bSample1In;
//	BOOL _bSample1IsOut;
//	BOOL _bSample2In;
//	BOOL _bSample2Out;
//	BOOL _bSample3In;
//	BOOL _bSample3Out;
//
//private:
//	tagTile _tiles[TILEX * TILEY];                            //화면에 그려지는 타일
//	tagSampleTile _sampleTiles[SAMPLETILEX * SAMPLETILEY];    // 샘플타일(TERRAIN)
//	tagSampleTile _sampleTiles2[SAMPLETILEX2 * SAMPLETILEY2]; // 샘플타일2(OBJ2)
//	tagSampleTile _sampleTiles3[SAMPLETILEX3 * SAMPLETILEY3]; // 샘플타일3(OBJ3)
//
//	image* _imgTile;       // 샘플타일TERRAIN 이미지
//	image* _imgTile2;       // 샘플타일OBJ이미지
//	image* _imgTile3;       // 샘플타일TERRAIN 80 이미지
//	image* _imgTile4;       // 샘플타일OBJ 80 이미지
//	image* _imgTile5;       // 샘플타일OBJ2 이미지
//	image* _imgTile6;       // 샘플타일OBJ2 80 이미지
//
//
//	image* _imgSample1;       //샘플타일배경
//	image* _imgSample2;        //샘플타일배경
//	image* _imgSample3;      //샘플타일배경
//
//	image* _grid;
//
//	tagCurrentTile _currentTile;
//
//private:
//	tagRectCamera _cameraRc;
//	bool _showCamera;
//	int _showWidth;
//	int _showHeight;
//
//public:
//	mapTool();
//	virtual ~mapTool();
//
//	virtual HRESULT init();
//	virtual void release();
//	virtual void update();
//	virtual void render();
//
//	virtual void setupTiles(void);
//	virtual void setMap(void);
//
//	virtual void save(void);
//	virtual void load(void);
//
//	TERRAIN terrainSelect(int frameX, int frameY);
//	OBJECT objSelect(int frameX, int frameY);
//	OBJECT objSelect2(int frameX, int frameY);
//	void showDefault();
//
//	void loadImage();
//	void createButton();
//	void drawButton();
//
//	void drawTile();
//	void drawSampleTile();
//	void drawNowInterfaceRect();
//	void nowDrawInterFaceKind();
//	void drawGrid();
//
//	void drawSampleBack();
//
//	void crashInterFaceRc();
//	void selectTile();
//
//	//카메라 관련
//	void setCameraRect();
//	void drawCameraRect();
//	void controlCamera();
//
//	void drawTileName();
//};


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
	SET_ENEMY_RC,
	INTERFACE_END = 7
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
	E_INTERFACE_RECT _interFaceRc;

	BOOL _bSample1In;
	BOOL _bSample1IsOut;
	BOOL _bSample2In;
	BOOL _bSample2Out;
	BOOL _bSample3In;
	BOOL _bSample3Out;
	BOOL _bSample4In;
	BOOL _bSample4Out;

private:
	tagTile _tiles[TILEX * TILEY];                            //화면에 그려지는 타일
	tagSampleTile _sampleTiles[SAMPLETILEX * SAMPLETILEY];    // 샘플타일(TERRAIN)
	tagSampleTile _sampleTiles2[SAMPLETILEX2 * SAMPLETILEY2]; // 샘플타일2(OBJ2)
	tagSampleTile _sampleTiles3[SAMPLETILEX3 * SAMPLETILEY3]; // 샘플타일3(OBJ3)
	tagSampleTile _sampleTiles4[SAMPLETILEX4 * SAMPLETILEY4];  // 샘플타일4(OBJ4)

	image* _imgTile;       // 샘플타일TERRAIN 이미지
	image* _imgTile2;       // 샘플타일OBJ이미지
	image* _imgTile3;       // 샘플타일TERRAIN 80 이미지
	image* _imgTile4;       // 샘플타일OBJ 80 이미지
	image* _imgTile5;       // 샘플타일OBJ2 이미지
	image* _imgTile6;       // 샘플타일OBJ2 80 이미지

	image* _imgTile7;         // 샘플타일OBJ4 30이미지
	image* _imgTile8;         // 샘플타일OBJ4 80이미지


	image* _imgSample1;       //샘플타일배경
	image* _imgSample2;        //샘플타일배경
	image* _imgSample3;      //샘플타일배경
	image* _imgSample4;       //샘플타일배경
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
	OBJECT objSelect2(int frameX, int frameY);
	OBJECT objSelect3(int frameX, int frameY);
	void showDefault();

	void loadImage();
	void createButton();
	void drawButton();

	void drawTile();
	void drawSampleTile();
	void drawNowInterfaceRect();
	void nowDrawInterFaceKind();
	void drawGrid();

	void drawSampleBack();

	void crashInterFaceRc();
	void selectTile();

	//카메라 관련
	void setCameraRect();
	void drawCameraRect();
	void controlCamera();

	void drawTileName();
};
