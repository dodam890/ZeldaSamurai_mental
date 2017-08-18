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
	//��(�̵��Ұ�), ��ư1(�������� ��������), ��ư2(�������� �ٸ� ����), �׾Ƹ�(������),
	//�ٸ�1,2(��ư2���۽� ����), ��1(�Ҳ�������), ��2(��ư���۽� ����) , ���1(��), ���2(�Ʒ�), �����ڽ�1, �����ڽ�2
	//�ڽ�1,2 (1 �� 2 �Ʒ�), ������ ���� ����, ������ ���� ����, ������ �Ʒ��� ����, ������ �Ʒ��� ����
	//ū�� ���� ����, ū�� ���� ����, ū�� �Ʒ��� ����, ū�� �Ʒ��� ����

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
