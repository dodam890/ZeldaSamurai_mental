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
	//벽(이동불가), 버튼1(눌렀을때 불켜지기), 버튼2(눌렀을때 다리 열기),
	//다리1,2(버튼2동작시 생김), 불1(불꺼진상태), 불2(버튼동작시 켜짐) 
	//박스1234 (12 위 34 아래)
	//항아리(던질것)
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
