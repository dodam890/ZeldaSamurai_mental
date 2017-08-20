#pragma once
#include "gameNode.h"
#include "inven_all.h"

#define HEART_COUNT 5

class enemy;
class camera;
class zeldaTileMap;

class player : public gameNode
{
public:
	enum LINK_MOTION
	{
		LINK_MOTION_RIGHT,
		LINK_MOTION_LEFT,
		LINK_MOTION_UP,
		LINK_MOTION_DOWN,
		LINK_MOTION_RIGHT_WALK,
		LINK_MOTION_LEFT_WALK,
		LINK_MOTION_UP_WALK,
		LINK_MOTION_DOWN_WALK,
		LINK_MOTION_RIGHT_TUMBLE,
		LINK_MOTION_LEFT_TUMBLE,
		LINK_MOTION_UP_TUMBLE,
		LINK_MOTION_DOWN_TUMBLE,
		LINK_MOTION_RIGHT_GRAB,
		LINK_MOTION_LEFT_GRAB,
		LINK_MOTION_UP_GRAB,
		LINK_MOTION_DOWN_GRAB,
		LINK_MOTION_RIGHT_PUSH,
		LINK_MOTION_LEFT_PUSH,
		LINK_MOTION_UP_PUSH,
		LINK_MOTION_DOWN_PUSH,
		LINK_MOTION_RIGHT_SWORD_ATTACK,
		LINK_MOTION_LEFT_SWORD_ATTACK,
		LINK_MOTION_UP_SWORD_ATTACK,
		LINK_MOTION_DOWN_SWORD_ATTACK,
		LINK_MOTION_RIGHT_SHIELD_OPEN,
		LINK_MOTION_LEFT_SHIELD_OPEN,
		LINK_MOTION_UP_SHIELD_OPEN,
		LINK_MOTION_DOWN_SHIELD_OPEN,
		LINK_MOTION_RIGHT_SHIELD_STAND,
		LINK_MOTION_LEFT_SHIELD_STAND,
		LINK_MOTION_UP_SHIELD_STAND,
		LINK_MOTION_DOWN_SHIELD_STAND,
		LINK_MOTION_RIGHT_SHIELD_MOVE,
		LINK_MOTION_LEFT_SHIELD_MOVE,
		LINK_MOTION_UP_SHIELD_MOVE,
		LINK_MOTION_DOWN_SHIELD_MOVE,
		LINK_MOTION_RIGHT_MAGICPOT_ABSORB,
		LINK_MOTION_LEFT_MAGICPOT_ABSORB,
		LINK_MOTION_UP_MAGICPOT_ABSORB,
		LINK_MOTION_DOWN_MAGICPOT_ABSORB,
		LINK_MOTION_RIGHT_MAGICPOT_FIRE,
		LINK_MOTION_LEFT_MAGICPOT_FIRE,
		LINK_MOTION_UP_MAGICPOT_FIRE,
		LINK_MOTION_DOWN_MAGICPOT_FIRE,
		LINK_MOTION_RIGHT_ROLLING_ATTACK,
		LINK_MOTION_LEFT_ROLLING_ATTACK,
		LINK_MOTION_UP_ROLLING_ATTACK,
		LINK_MOTION_DOWN_ROLLING_ATTACK,
		LINK_MOTION_END = 48
	};
public:
	struct LINK_MOTION_IMAGE_INFO
	{
		image* _linkImg;
		int _maxFrameCount;
		RECT _rc;

	};
	enum RECT_ATTRIBUTE
	{
		RC_ATR_ATT,
		RC_ATR_DEF,
		RC_ATR_GRAB,
		RC_ATR_ABSORB,
		RC_ATR_END = 4,
	};
	struct LINK_CRUSH_RECT
	{
		RECT _crushRc;
		float _damage;
	};
public:
	enum LINK_HP_KIND
	{
		LINK_HP_EMPTY,
		LINK_HP_ONE_FOURTH,
		LINK_HP_TWO_FOURTH,
		LINK_HP_THREE_FOURTH,
		LINK_HP_MAX,
		LINK_HP_END = 5
	};

	struct LINK_HP
	{
		image* hpImg[LINK_HP_END];
		LINK_HP_KIND hpKind;
	};

private:
	zeldaTileMap* _zeldaTileMap;

private:
	RECT_ATTRIBUTE _rcAtr;

private:

	LINK_MOTION_IMAGE_INFO _link[LINK_MOTION_END];
	LINK_MOTION L_Motion;
	LINK_CRUSH_RECT _linkCrushRc;

	LINK_HP_KIND Hp_Kind;

	LINK_HP _hp[HEART_COUNT];
	int _curHeart;

	RECT _playerRc;
	RECT _rcCrush;

	camera* _cam;
	enemy* _enemy;

	int tileIndex[2];

	float _damage;
	int _frameX;

	float _angle;
	float _moveSpeed;

	float _X, _Y;
	float _disX, _disY;
	float _cenX, _cenY;

	int _linkIdx;
	int _linkIdxX;
	int _linkIdxY;

	int _count;
	int _hurtCount;
	int _currentFrameX, _currentFrameY;
	int _probeX, _probeY;
	int _rcCrushCenX;
	int _rcCrushCenY;

	bool _move;
	bool _tumble;
	bool _isStore;
	bool _isCollision;
	bool _isPush;
	bool _isPlayerInTileMap;
	bool _moveTile;
	bool _hurt;

	int _keyCount;

	//À½¾ÇÄ«¿îÆ®
	int _soundCount;

public:

	HRESULT init(camera* camera);
	void release(void);
	void update(zeldaTileMap* _tileMap);
	void render(void);

	void draw(void);
	void motionChange(void);
	void move(void);
	void frameCount(void);
	void loadImage(void);

	void pixelCollision(image* _mapPixelImg);

	void makeCrushRc();

	void dectectionTileMap();

	RECT getRect() { return _playerRc; }
	RECT getCrushRect() { return _rcCrush; }
	LINK_MOTION getMotion() { return L_Motion; }
	RECT_ATTRIBUTE getAtr() { return _rcAtr; }

	void setDisX(float disX) { _disX = disX; }
	void setDisY(float disY) { _disY = disY; }
	float getDisX() { return _disX; }
	float getDisY() { return _disY; }

	int getIndexX() { return _linkIdxX; }
	int getIndexY() { return _linkIdxY; }
	int getIndex() { return _linkIdx; }

	int getCenterX() { return (_playerRc.left + _playerRc.right) / 2; }
	int getCenterY() { return (_playerRc.bottom + _playerRc.top) / 2; }

	void setIsCollision(bool collision, RECT npcRc);

	void setX(float X) { _X = X; }
	void setY(float Y) { _Y = Y; }

	void setMove(bool move) { _move = move; }
	void isStore(bool isStore) { _isStore = isStore; }
	void setPush(bool isPush) { _isPush = isPush; }

	void setIsInTileMap(bool bInTile) { _isPlayerInTileMap = bInTile; }

	int getKeyCount() { return _keyCount; }

	
	void setHpImage();
	void drawHpImage();
	void controlHeart();

	void decreaseHeart();

	player();
	~player();
};

