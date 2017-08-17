#pragma once
#include "gameNode.h"

#define TILESIZE 80

#define TILEWIDTH 80
#define TILEHEIGHT 80

#define TILEX 30
#define TILEY 30
#define TILETOTAL TILEX * TILEY

#define TILESIZEX TILESIZE * TILEX
#define TILESIZEY TILESIZE * TILEY

#define SAMPLETILEX 6
#define SAMPLETILEY 4
#define SAMPLETOTAL SAMPLETILEX * SAMPLETILEY

#define SAMPLETILEX2 14
#define SAMPLETILEY2 17
#define SAMPLETOTAL2 SAMPLETILEX2 * SAMPLETILEY2

#define SAMPLETILEX3 14
#define SAMPLETILEY3 10

#define SAMPLETILESIZE 30
#define SAMPLETILEWIDTH 30
#define SAMPLETILEHEIGHT 30

enum ATTRIBUTE
{
	E_ATR_MOVE,
	E_ATR_SLOW,
	E_ATR_SLIDE,
	E_ATR_END = 3
};

enum TERRAIN
{
	TR_BASE, TR_GRASS, TR_DESERT, TR_WATER, TR_END
};

enum OBJECT
{
	//��(�̵��Ұ�), ��ư1(�������� ��������), ��ư2(�������� �ٸ� ����),
	//�ٸ�1,2(��ư2���۽� ����), ��1(�Ҳ�������), ��2(��ư���۽� ����) 
	//�ڽ�1234 (12 �� 34 �Ʒ�)
	//�׾Ƹ�(������)
	OBJ_WALL, OBJ_BUTTON1_UP, OBJ_BUTTON1_DOWN, OBJ_BUTTON2_UP, OBJ_BUTTON2_DOWN,
	OBJ_BRIDGE1, OBJ_BRIDGE2, OBJ_FIRE1, OBJ_FIRE2, OBJ_COLUMN1, OBJ_COLUMN2,
	OBJ_BOX1, OBJ_BOX2, OBJ_BOX3, OBJ_BOX4,
	OBJ_POT, OBJ_NONE
};

struct tagTile
{
	TERRAIN terrain;
	OBJECT obj;
	POINT posCenter;
	RECT rc;
	int terrainFrameX;
	int terrainFrameY;
	int objFrameX;
	int objFrameY;
	int imgKind;
	float disX;
	float disY;
};

struct tagSampleTile
{
	RECT rcTile;
	int terrainFrameX;
	int terrainFrameY;
	int objFrameX;
	int objFrameY;
	int imgKind;
};

struct tagCurrentTile
{
	int terFrameX;
	int terFrameY;
	int objFrameX;
	int objFrameY;
};
