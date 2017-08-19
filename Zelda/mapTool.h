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
//	tagTile _tiles[TILEX * TILEY];                            //ȭ�鿡 �׷����� Ÿ��
//	tagSampleTile _sampleTiles[SAMPLETILEX * SAMPLETILEY];    // ����Ÿ��(TERRAIN)
//	tagSampleTile _sampleTiles2[SAMPLETILEX2 * SAMPLETILEY2]; // ����Ÿ��2(OBJ2)
//	tagSampleTile _sampleTiles3[SAMPLETILEX3 * SAMPLETILEY3]; // ����Ÿ��3(OBJ3)
//
//	image* _imgTile;       // ����Ÿ��TERRAIN �̹���
//	image* _imgTile2;       // ����Ÿ��OBJ�̹���
//	image* _imgTile3;       // ����Ÿ��TERRAIN 80 �̹���
//	image* _imgTile4;       // ����Ÿ��OBJ 80 �̹���
//	image* _imgTile5;       // ����Ÿ��OBJ2 �̹���
//	image* _imgTile6;       // ����Ÿ��OBJ2 80 �̹���
//
//
//	image* _imgSample1;       //����Ÿ�Ϲ��
//	image* _imgSample2;        //����Ÿ�Ϲ��
//	image* _imgSample3;      //����Ÿ�Ϲ��
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
//	//ī�޶� ����
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
	tagTile _tiles[TILEX * TILEY];                            //ȭ�鿡 �׷����� Ÿ��
	tagSampleTile _sampleTiles[SAMPLETILEX * SAMPLETILEY];    // ����Ÿ��(TERRAIN)
	tagSampleTile _sampleTiles2[SAMPLETILEX2 * SAMPLETILEY2]; // ����Ÿ��2(OBJ2)
	tagSampleTile _sampleTiles3[SAMPLETILEX3 * SAMPLETILEY3]; // ����Ÿ��3(OBJ3)
	tagSampleTile _sampleTiles4[SAMPLETILEX4 * SAMPLETILEY4];  // ����Ÿ��4(OBJ4)

	image* _imgTile;       // ����Ÿ��TERRAIN �̹���
	image* _imgTile2;       // ����Ÿ��OBJ�̹���
	image* _imgTile3;       // ����Ÿ��TERRAIN 80 �̹���
	image* _imgTile4;       // ����Ÿ��OBJ 80 �̹���
	image* _imgTile5;       // ����Ÿ��OBJ2 �̹���
	image* _imgTile6;       // ����Ÿ��OBJ2 80 �̹���

	image* _imgTile7;         // ����Ÿ��OBJ4 30�̹���
	image* _imgTile8;         // ����Ÿ��OBJ4 80�̹���


	image* _imgSample1;       //����Ÿ�Ϲ��
	image* _imgSample2;        //����Ÿ�Ϲ��
	image* _imgSample3;      //����Ÿ�Ϲ��
	image* _imgSample4;       //����Ÿ�Ϲ��
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

	//ī�޶� ����
	void setCameraRect();
	void drawCameraRect();
	void controlCamera();

	void drawTileName();
};
