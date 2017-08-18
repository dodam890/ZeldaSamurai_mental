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
#define SAMPLETILEY2 10
#define SAMPLETOTAL2 SAMPLETILEX2 * SAMPLETILEY2

#define SAMPLETILEX3 15
#define SAMPLETILEY3 11
#define SAMPLETOTAL3 SAMPLETILEX3 * SAMPLETILEY3

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
	//벽(이동불가), 버튼1(눌렀을때 불켜지기), 버튼2(눌렀을때 다리 열기), 항아리(던질것),
	//다리1,2(버튼2동작시 생김), 불1(불꺼진상태), 불2(버튼동작시 켜짐) , 기둥1(위), 기둥2(아래), 작은박스1, 작은박스2
	//박스1,2 (1 위 2 아래), 작은문 위쪽 닫힘, 작은문 위쪽 열림, 작은문 아래쪽 닫힘, 작은문 아래쪽 열림
	//큰문 위쪽 닫힘, 큰문 위쪽 열림, 큰문 아래쪽 닫힘, 큰문 아래쪽 열림

	OBJ_WALL, OBJ_BUTTON1_UP, OBJ_BUTTON1_DOWN, OBJ_BUTTON2_UP, OBJ_BUTTON2_DOWN, OBJ_POT,
	OBJ_BRIDGE1, OBJ_BRIDGE2, OBJ_FIRE1, OBJ_FIRE2, OBJ_COLUMN1, OBJ_COLUMN2, OBJ_SMALL_BOX1, OBJ_SMALL_BOX2,
	OBJ_BOX1, OBJ_BOX2, OBJ_DOOR_UP_CLOSE, OBJ_DOOR_UP_OPEN, OBJ_DOOR_DOWN_CLOSE, OBJ_DOOR_DOWN_OPEN,
	OBJ_DOOR2_UP_CLOSE, OBJ_DOOR2_UP_OPEN, OBJ_DOOR2_DOWN_CLOSE, OBJ_DOOR2_DOWN_OPEN, OBJ_NONE
};
enum TILE_KIND
{
	KIND_TERRAIN,
	KIND_OBJ1,
	KIND_OBJ2,
	END = 3
};

struct tagTile
{
	TERRAIN terrain;
	OBJECT obj;
	OBJECT obj2;
	TILE_KIND tileKind;
	
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
