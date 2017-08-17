#pragma once
#include "gameNode.h"

#define NPCWIDTH 80
#define NPCHEIGHT 130

class player;
class camera;

enum DIRECTION
{
	DIRECTION_DOWN,
	DIRECTION_LEFT,
	DIRECTION_RIGHT,
	DIRECTION_UP,
	DIRECTION_END = 4
};

struct tagFrameImage
{
	image* image;
	int currentFrameX;
	int count;
};

class npc : public gameNode
{
private:
	vector<string> _vWords;
	vector<string>::iterator _viWords;

	vector<string> _vTextOut;
	vector<string>::iterator _viTextOut;

private:
	RECT _rc;
	RECT _moveRc;
	int _widthRange, _heightRange;
	tagFrameImage _npc[DIRECTION_END];
	DIRECTION _direction;

	float _distanceX, _distanceY;
	float _drawX, _drawY;
	float _centerX, _centerY;
	float _moveCenterX, _moveCenterY;

	float _moveCount;
	int _stopCount;

	int _index;
	int _count;
	bool _talkOn;

	//플레이어
	player* _player;

	//카메라
	camera* _camera;

public:
	virtual HRESULT init(camera* camera, string npcName, DIRECTION direction, float drawX, float drawY, int widthRange, int heightRange);
	virtual void release();
	virtual void update(string npcSort);
	virtual void render();

	virtual void setImages(string imageKeyNameDown, string imageKeyNameLeft, string imageKeyNameRight, string imageKeyNameUp);
	virtual void addFrame(string npcSort, DIRECTION direction, int frameSpeed);

	virtual void changeDirection(string npcSort);
	virtual void npcMove(string npcSort);

	void setTalkOn(bool talkOn) { _talkOn = talkOn; }
	bool getTalkOn() { return _talkOn; }

	void setMapWords(string npcName);
	void talkOn();
	void drawTextBox();

	RECT getRect() { return _rc; }
	RECT getMoveRect() { return _moveRc; }

	float getDisX() { return _distanceX; }
	float getDisY() { return _distanceY; }

	void setPlayerMemoryAdressLink(player* player) { _player = player; }

	npc();
	virtual ~npc();
};

