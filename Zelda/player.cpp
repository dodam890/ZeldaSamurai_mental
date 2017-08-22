#include "stdafx.h"
#include "player.h"
#include "camera.h"
#include "zeldaTileMap.h"
#include "c_zeldaTileMap.h"
#include "enemy.h"

player::player() {}
player::~player() {}

HRESULT player::init(camera* camera)
{
	loadImage();
	L_Motion = LINK_MOTION_DOWN;

	_cam = camera;
	_angle = PI;
	_moveSpeed = 5;
	_move = true;
	_isStore = false;
	_isPush = false;
	_isPlayerInTileMap = false;

	_hurt = false;

	_sword = false;
	_shield = false;
	_magicpot = false;
	_rollingAttack = false;

	_damage = 0;
	_frameX = 0;
	_keyCount = 0;
	_isCollision = 0;
	_linkIdx = _linkIdxX = _linkIdxY = 0;
	_currentFrameX = _currentFrameY = 0;
	_count = _hurtCount = 0;
	_probeX = _probeY = 0;

	_rcCrushCenX = -100000;
	_rcCrushCenY = -100000;
	_rcCrush = RectMakeCenter(_rcCrushCenX, _rcCrushCenY, 1, 1);

	_disX = WINSIZEX / 2 - 135;
	_disY = WINSIZEY / 2 + 100;

	_X = _cam->getStartX() + _disX;
	_Y = _cam->getStartY() + _disY;

	_playerRc = RectMake(_X + 102, _Y + 100, 66, 70);

	_curHeart = HEART_COUNT - 1;

	setHpImage();

	//음악카운트
	_soundCount = 0;

	return S_OK;
}

void player::release(void) {}

void player::update(zeldaTileMap* tileMap)
{
	if (_sword == false || _shield == false || _magicpot == false || _rollingAttack == false)
	{
		if (_ia->get_vi().size() > 0)
		{
			for (int i = 0; i < _ia->get_vi().size(); i++)
			{
				if (_ia->get_vi()[i]->get_item_num() == 0) _sword = true;
				if (_ia->get_vi()[i]->get_item_num() == 1) _shield = true;
				if (_ia->get_vi()[i]->get_item_num() == 2) _magicpot = true;
				if (_ia->get_vi()[i]->get_item_num() == 14) _rollingAttack = true;
			}
		}
	}



	if (_isPlayerInTileMap)
	{
		_zeldaTileMap = tileMap;
		dectectionTileMap();
	}
	else
	{

	}

	if (_hurt)
	{
		_hurtCount++;
		if (_hurtCount % 50 == 0)
		{

			_hurt = false;
			_hurtCount = 0;
		}
	}

	if (_move)
	{
		motionChange();
		move();
	}

	_X = _cam->getStartX() + _disX;
	_Y = _cam->getStartY() + _disY;
	_playerRc = RectMake(_X + 102, _Y + 100, 66, 70);

	makeCrushRc();
	frameCount();
}

void player::render(void)
{
	draw();
	drawHpImage();
	//_hp[2].hpImg[LINK_HP_MAX]->render(getMemDC(), 500, 500);
}

void player::draw(void)
{
	if (_rectView)
	{
		Rectangle(getMemDC(), _playerRc.left, _playerRc.top, _playerRc.right, _playerRc.bottom);
		Rectangle(getMemDC(), _rcCrush.left, _rcCrush.top, _rcCrush.right, _rcCrush.bottom);
	}

	if (_rectView)
	{
		Rectangle(getMemDC(), _playerRc.left, _playerRc.top, _playerRc.right, _playerRc.bottom);
		Rectangle(getMemDC(), _rcCrush.left, _rcCrush.top, _rcCrush.right, _rcCrush.bottom);
	}
	if (L_Motion == LINK_MOTION_UP_GRAB)
	{
		_link[L_Motion]._linkImg->frameRender(getMemDC(), _X - 5, _Y - 15, _currentFrameX, 0);
	}
	else if (L_Motion == LINK_MOTION_RIGHT_GRAB)
	{
		_link[L_Motion]._linkImg->frameRender(getMemDC(), _X, _Y - 10, _currentFrameX, 0);
	}
	else if (L_Motion == LINK_MOTION_LEFT_GRAB)
	{
		_link[L_Motion]._linkImg->frameRender(getMemDC(), _X, _Y - 10, _currentFrameX, 0);
	}
	else if (L_Motion == LINK_MOTION_DOWN_GRAB)
	{
		_link[L_Motion]._linkImg->frameRender(getMemDC(), _X, _Y - 15, _currentFrameX, 0);
	}
	else
	{
		_link[L_Motion]._linkImg->frameRender(getMemDC(), _X, _Y, _currentFrameX, 0);
	}
}

void player::motionChange(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		switch (L_Motion)
		{
		case player::LINK_MOTION_RIGHT:
		case player::LINK_MOTION_LEFT:
		case player::LINK_MOTION_UP:
		case player::LINK_MOTION_DOWN:
		case player::LINK_MOTION_RIGHT_WALK:
		case player::LINK_MOTION_UP_WALK:
		case player::LINK_MOTION_DOWN_WALK:

			_currentFrameX = 0;
			L_Motion = LINK_MOTION_LEFT_WALK;

			if (_cam->isCameraXZeroSide())
			{
				if (_playerRc.left <= WINSIZEX / 2 - 35 && !_isStore)
				{
					_cam->setCameraX(_cam->getCameraX() - _moveSpeed);
					_disX -= _moveSpeed;
				}
				else
				{
					_disX -= _moveSpeed;
				}
			}
			else
			{
				if (_playerRc.left >= 0) _disX -= _moveSpeed;
			}

			break;
		case player::LINK_MOTION_UP_TUMBLE:
		case player::LINK_MOTION_DOWN_TUMBLE:
		case player::LINK_MOTION_LEFT_TUMBLE:
		case player::LINK_MOTION_RIGHT_TUMBLE:
			break;
		case player::LINK_MOTION_RIGHT_SWORD_ATTACK:
		case player::LINK_MOTION_LEFT_SWORD_ATTACK:
		case player::LINK_MOTION_UP_SWORD_ATTACK:
		case player::LINK_MOTION_DOWN_SWORD_ATTACK:
			break;
		case player::LINK_MOTION_RIGHT_SHIELD_OPEN:
		case player::LINK_MOTION_LEFT_SHIELD_OPEN:
		case player::LINK_MOTION_UP_SHIELD_OPEN:
		case player::LINK_MOTION_DOWN_SHIELD_OPEN:
			break;
		case player::LINK_MOTION_RIGHT_ROLLING_ATTACK:
		case player::LINK_MOTION_LEFT_ROLLING_ATTACK:
		case player::LINK_MOTION_UP_ROLLING_ATTACK:
		case player::LINK_MOTION_DOWN_ROLLING_ATTACK:
			break;
		case player::LINK_MOTION_RIGHT_GRAB:
		case player::LINK_MOTION_LEFT_GRAB:
		case player::LINK_MOTION_UP_GRAB:
		case player::LINK_MOTION_DOWN_GRAB:
			break;
		case player::LINK_MOTION_RIGHT_SHIELD_STAND:
		case player::LINK_MOTION_LEFT_SHIELD_STAND:
		case player::LINK_MOTION_UP_SHIELD_STAND:
		case player::LINK_MOTION_DOWN_SHIELD_STAND:
		case player::LINK_MOTION_RIGHT_SHIELD_MOVE:
		case player::LINK_MOTION_UP_SHIELD_MOVE:
		case player::LINK_MOTION_DOWN_SHIELD_MOVE:

			_currentFrameX = 0;
			L_Motion = LINK_MOTION_LEFT_SHIELD_MOVE;

			if (_cam->isCameraXZeroSide())
			{
				if (_playerRc.left <= WINSIZEX / 2 - 35 && !_isStore)
				{
					_cam->setCameraX(_cam->getCameraX() - _moveSpeed);
					_disX -= _moveSpeed;
				}
				else
				{
					_disX -= _moveSpeed;
				}
			}
			else
			{
				if (_playerRc.left >= 0) _disX -= _moveSpeed;
			}

			break;
		case player::LINK_MOTION_RIGHT_MAGICPOT_ABSORB:
		case player::LINK_MOTION_UP_MAGICPOT_ABSORB:
		case player::LINK_MOTION_DOWN_MAGICPOT_ABSORB:

			L_Motion = LINK_MOTION_LEFT_MAGICPOT_ABSORB;

			if (_cam->isCameraXZeroSide())
			{
				if (_playerRc.left <= WINSIZEX / 2 - 35 && !_isStore)
				{
					_cam->setCameraX(_cam->getCameraX() - _moveSpeed);
					_disX -= _moveSpeed;
				}
				else
				{
					_disX -= _moveSpeed;
				}
			}
			else
			{
				if (_playerRc.left >= 0) _disX -= _moveSpeed;
			}

			break;
		case player::LINK_MOTION_RIGHT_MAGICPOT_FIRE:
		case player::LINK_MOTION_UP_MAGICPOT_FIRE:
		case player::LINK_MOTION_DOWN_MAGICPOT_FIRE:

			L_Motion = LINK_MOTION_LEFT_MAGICPOT_FIRE;

			if (_cam->isCameraXZeroSide())
			{
				if (_playerRc.left <= WINSIZEX / 2 - 35 && !_isStore)
				{
					_cam->setCameraX(_cam->getCameraX() - _moveSpeed);
					_disX -= _moveSpeed;
				}
				else
				{
					_disX -= _moveSpeed;
				}
			}
			else
			{
				if (_playerRc.left >= 0) _disX -= _moveSpeed;
			}

			break;
		default:
			if (_cam->isCameraXZeroSide())
			{
				if (_playerRc.left <= WINSIZEX / 2 - 35 && !_isStore)
				{
					_cam->setCameraX(_cam->getCameraX() - _moveSpeed);
					_disX -= _moveSpeed;
				}
				else
				{
					_disX -= _moveSpeed;
				}
			}
			else
			{
				if (_playerRc.left >= 0) _disX -= _moveSpeed;
			}
			break;
		}
	}
	else if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		switch (L_Motion)
		{
		case player::LINK_MOTION_RIGHT:
		case player::LINK_MOTION_LEFT:
		case player::LINK_MOTION_UP:
		case player::LINK_MOTION_DOWN:
		case player::LINK_MOTION_LEFT_WALK:
		case player::LINK_MOTION_UP_WALK:
		case player::LINK_MOTION_DOWN_WALK:

			_currentFrameX = 0;
			L_Motion = LINK_MOTION_RIGHT_WALK;

			if (_cam->isCameraXEndSide())
			{
				if (_playerRc.right >= WINSIZEX / 2 + 35 && !_isStore)
				{
					_cam->setCameraX(_cam->getCameraX() + _moveSpeed);
					_disX += _moveSpeed;
				}
				else
				{
					_disX += _moveSpeed;
				}
			}
			else
			{
				if (_playerRc.right <= WINSIZEX) _disX += _moveSpeed;
			}

			break;
		case player::LINK_MOTION_UP_TUMBLE:
		case player::LINK_MOTION_DOWN_TUMBLE:
		case player::LINK_MOTION_LEFT_TUMBLE:
		case player::LINK_MOTION_RIGHT_TUMBLE:
			break;
		case player::LINK_MOTION_RIGHT_SWORD_ATTACK:
		case player::LINK_MOTION_LEFT_SWORD_ATTACK:
		case player::LINK_MOTION_UP_SWORD_ATTACK:
		case player::LINK_MOTION_DOWN_SWORD_ATTACK:
			break;
		case player::LINK_MOTION_RIGHT_SHIELD_OPEN:
		case player::LINK_MOTION_LEFT_SHIELD_OPEN:
		case player::LINK_MOTION_UP_SHIELD_OPEN:
		case player::LINK_MOTION_DOWN_SHIELD_OPEN:
			break;
		case player::LINK_MOTION_RIGHT_ROLLING_ATTACK:
		case player::LINK_MOTION_LEFT_ROLLING_ATTACK:
		case player::LINK_MOTION_UP_ROLLING_ATTACK:
		case player::LINK_MOTION_DOWN_ROLLING_ATTACK:
			break;
		case player::LINK_MOTION_RIGHT_GRAB:
		case player::LINK_MOTION_LEFT_GRAB:
		case player::LINK_MOTION_UP_GRAB:
		case player::LINK_MOTION_DOWN_GRAB:
			break;
		case player::LINK_MOTION_RIGHT_SHIELD_STAND:
		case player::LINK_MOTION_LEFT_SHIELD_STAND:
		case player::LINK_MOTION_UP_SHIELD_STAND:
		case player::LINK_MOTION_DOWN_SHIELD_STAND:
		case player::LINK_MOTION_LEFT_SHIELD_MOVE:
		case player::LINK_MOTION_UP_SHIELD_MOVE:
		case player::LINK_MOTION_DOWN_SHIELD_MOVE:

			_currentFrameX = 0;
			L_Motion = LINK_MOTION_RIGHT_SHIELD_MOVE;

			if (_cam->isCameraXEndSide())
			{
				if (_playerRc.right >= WINSIZEX / 2 + 35 && !_isStore)
				{
					_cam->setCameraX(_cam->getCameraX() + _moveSpeed);
					_disX += _moveSpeed;
				}
				else
				{
					_disX += _moveSpeed;
				}
			}
			else
			{
				if (_playerRc.right <= WINSIZEX) _disX += _moveSpeed;
			}

			break;
		case player::LINK_MOTION_LEFT_MAGICPOT_ABSORB:
		case player::LINK_MOTION_UP_MAGICPOT_ABSORB:
		case player::LINK_MOTION_DOWN_MAGICPOT_ABSORB:

			L_Motion = LINK_MOTION_RIGHT_MAGICPOT_ABSORB;

			if (_cam->isCameraXEndSide())
			{
				if (_playerRc.right >= WINSIZEX / 2 + 35 && !_isStore)
				{
					_cam->setCameraX(_cam->getCameraX() + _moveSpeed);
					_disX += _moveSpeed;
				}
				else
				{
					_disX += _moveSpeed;
				}
			}
			else
			{
				if (_playerRc.right <= WINSIZEX) _disX += _moveSpeed;
			}

			break;
		case player::LINK_MOTION_LEFT_MAGICPOT_FIRE:
		case player::LINK_MOTION_UP_MAGICPOT_FIRE:
		case player::LINK_MOTION_DOWN_MAGICPOT_FIRE:

			L_Motion = LINK_MOTION_RIGHT_MAGICPOT_FIRE;

			if (_cam->isCameraXEndSide())
			{
				if (_playerRc.right >= WINSIZEX / 2 + 35 && !_isStore)
				{
					_cam->setCameraX(_cam->getCameraX() + _moveSpeed);
					_disX += _moveSpeed;
				}
				else
				{
					_disX += _moveSpeed;
				}
			}
			else
			{
				if (_playerRc.right <= WINSIZEX) _disX += _moveSpeed;
			}

			break;
		default:
			if (_cam->isCameraXEndSide())
			{
				if (_playerRc.right >= WINSIZEX / 2 + 35 && !_isStore)
				{
					_cam->setCameraX(_cam->getCameraX() + _moveSpeed);
					_disX += _moveSpeed;
				}
				else
				{
					_disX += _moveSpeed;
				}
			}
			else
			{
				if (_playerRc.right <= WINSIZEX) _disX += _moveSpeed;
			}
			break;
		}
	}
	else if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		switch (L_Motion)
		{
		case player::LINK_MOTION_RIGHT:
		case player::LINK_MOTION_LEFT:
		case player::LINK_MOTION_UP:
		case player::LINK_MOTION_DOWN:
		case player::LINK_MOTION_RIGHT_WALK:
		case player::LINK_MOTION_LEFT_WALK:
		case player::LINK_MOTION_DOWN_WALK:

			_currentFrameX = 0;
			L_Motion = LINK_MOTION_UP_WALK;

			if (_cam->isCameraYZeroSide())
			{
				if (_playerRc.top <= WINSIZEY / 2 - 35 && !_isStore)
				{
					_cam->setCameraY(_cam->getCameraY() - _moveSpeed);
					_disY -= _moveSpeed;
				}
				else
				{
					_disY -= _moveSpeed;
				}
			}
			else
			{
				if (_playerRc.top >= 0) _disY -= _moveSpeed;
			}

			break;
		case player::LINK_MOTION_UP_TUMBLE:
		case player::LINK_MOTION_DOWN_TUMBLE:
		case player::LINK_MOTION_LEFT_TUMBLE:
		case player::LINK_MOTION_RIGHT_TUMBLE:
			break;
		case player::LINK_MOTION_RIGHT_SWORD_ATTACK:
		case player::LINK_MOTION_LEFT_SWORD_ATTACK:
		case player::LINK_MOTION_UP_SWORD_ATTACK:
		case player::LINK_MOTION_DOWN_SWORD_ATTACK:
			break;
		case player::LINK_MOTION_RIGHT_SHIELD_OPEN:
		case player::LINK_MOTION_LEFT_SHIELD_OPEN:
		case player::LINK_MOTION_UP_SHIELD_OPEN:
		case player::LINK_MOTION_DOWN_SHIELD_OPEN:
			break;
		case player::LINK_MOTION_RIGHT_ROLLING_ATTACK:
		case player::LINK_MOTION_LEFT_ROLLING_ATTACK:
		case player::LINK_MOTION_UP_ROLLING_ATTACK:
		case player::LINK_MOTION_DOWN_ROLLING_ATTACK:
			break;
		case player::LINK_MOTION_RIGHT_GRAB:
		case player::LINK_MOTION_LEFT_GRAB:
		case player::LINK_MOTION_UP_GRAB:
		case player::LINK_MOTION_DOWN_GRAB:
			break;
		case player::LINK_MOTION_RIGHT_SHIELD_STAND:
		case player::LINK_MOTION_LEFT_SHIELD_STAND:
		case player::LINK_MOTION_UP_SHIELD_STAND:
		case player::LINK_MOTION_DOWN_SHIELD_STAND:
		case player::LINK_MOTION_RIGHT_SHIELD_MOVE:
		case player::LINK_MOTION_LEFT_SHIELD_MOVE:
		case player::LINK_MOTION_DOWN_SHIELD_MOVE:

			_currentFrameX = 0;
			L_Motion = LINK_MOTION_UP_SHIELD_MOVE;

			if (_cam->isCameraYZeroSide())
			{
				if (_playerRc.top <= WINSIZEY / 2 - 35 && !_isStore)
				{
					_cam->setCameraY(_cam->getCameraY() - _moveSpeed);
					_disY -= _moveSpeed;
				}
				else
				{
					_disY -= _moveSpeed;
				}
			}
			else
			{
				if (_playerRc.top >= 0) _disY -= _moveSpeed;
			}
			break;
		case player::LINK_MOTION_RIGHT_MAGICPOT_ABSORB:
		case player::LINK_MOTION_LEFT_MAGICPOT_ABSORB:
		case player::LINK_MOTION_DOWN_MAGICPOT_ABSORB:

			L_Motion = LINK_MOTION_UP_MAGICPOT_ABSORB;

			if (_cam->isCameraYZeroSide())
			{
				if (_playerRc.top <= WINSIZEY / 2 - 35 && !_isStore)
				{
					_cam->setCameraY(_cam->getCameraY() - _moveSpeed);
					_disY -= _moveSpeed;
				}
				else
				{
					_disY -= _moveSpeed;
				}
			}
			else
			{
				if (_playerRc.top >= 0) _disY -= _moveSpeed;
			}

			break;
		case player::LINK_MOTION_RIGHT_MAGICPOT_FIRE:
		case player::LINK_MOTION_LEFT_MAGICPOT_FIRE:
		case player::LINK_MOTION_DOWN_MAGICPOT_FIRE:

			L_Motion = LINK_MOTION_UP_MAGICPOT_FIRE;

			if (_cam->isCameraYZeroSide())
			{
				if (_playerRc.top <= WINSIZEY / 2 - 35 && !_isStore)
				{
					_cam->setCameraY(_cam->getCameraY() - _moveSpeed);
					_disY -= _moveSpeed;
				}
				else
				{
					_disY -= _moveSpeed;
				}
			}
			else
			{
				if (_playerRc.top >= 0) _disY -= _moveSpeed;
			}

			break;
		default:

			if (_cam->isCameraYZeroSide())
			{
				if (_playerRc.top <= WINSIZEY / 2 - 35 && !_isStore)
				{
					_cam->setCameraY(_cam->getCameraY() - _moveSpeed);
					_disY -= _moveSpeed;
				}
				else
				{
					_disY -= _moveSpeed;
				}
			}
			else
			{
				if (_playerRc.top >= 0) _disY -= _moveSpeed;
			}

			break;
		}
	}
	else if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		switch (L_Motion)
		{
		case player::LINK_MOTION_RIGHT:
		case player::LINK_MOTION_LEFT:
		case player::LINK_MOTION_UP:
		case player::LINK_MOTION_DOWN:
		case player::LINK_MOTION_RIGHT_WALK:
		case player::LINK_MOTION_LEFT_WALK:
		case player::LINK_MOTION_UP_WALK:

			_currentFrameX = 0;
			L_Motion = LINK_MOTION_DOWN_WALK;

			if (_cam->isCameraYEndSide())
			{
				if (_playerRc.bottom >= WINSIZEY / 2 + 35 && !_isStore)
				{
					_cam->setCameraY(_cam->getCameraY() + _moveSpeed);
					_disY += _moveSpeed;
				}
				else
				{
					_disY += _moveSpeed;
				}
			}
			else
			{
				if (_playerRc.bottom <= WINSIZEY) _disY += _moveSpeed;
			}

			break;
		case player::LINK_MOTION_UP_TUMBLE:
		case player::LINK_MOTION_DOWN_TUMBLE:
		case player::LINK_MOTION_LEFT_TUMBLE:
		case player::LINK_MOTION_RIGHT_TUMBLE:
			break;
		case player::LINK_MOTION_RIGHT_SWORD_ATTACK:
		case player::LINK_MOTION_LEFT_SWORD_ATTACK:
		case player::LINK_MOTION_UP_SWORD_ATTACK:
		case player::LINK_MOTION_DOWN_SWORD_ATTACK:
			break;
		case player::LINK_MOTION_RIGHT_SHIELD_OPEN:
		case player::LINK_MOTION_LEFT_SHIELD_OPEN:
		case player::LINK_MOTION_UP_SHIELD_OPEN:
		case player::LINK_MOTION_DOWN_SHIELD_OPEN:
			break;
		case player::LINK_MOTION_RIGHT_ROLLING_ATTACK:
		case player::LINK_MOTION_LEFT_ROLLING_ATTACK:
		case player::LINK_MOTION_UP_ROLLING_ATTACK:
		case player::LINK_MOTION_DOWN_ROLLING_ATTACK:
			break;
		case player::LINK_MOTION_RIGHT_GRAB:
		case player::LINK_MOTION_LEFT_GRAB:
		case player::LINK_MOTION_UP_GRAB:
		case player::LINK_MOTION_DOWN_GRAB:
			break;
		case player::LINK_MOTION_RIGHT_SHIELD_STAND:
		case player::LINK_MOTION_LEFT_SHIELD_STAND:
		case player::LINK_MOTION_UP_SHIELD_STAND:
		case player::LINK_MOTION_DOWN_SHIELD_STAND:
		case player::LINK_MOTION_RIGHT_SHIELD_MOVE:
		case player::LINK_MOTION_LEFT_SHIELD_MOVE:
		case player::LINK_MOTION_UP_SHIELD_MOVE:

			_currentFrameX = 0;
			L_Motion = LINK_MOTION_DOWN_SHIELD_MOVE;

			if (_cam->isCameraYEndSide())
			{
				if (_playerRc.bottom >= WINSIZEY / 2 + 35 && !_isStore)
				{
					_cam->setCameraY(_cam->getCameraY() + _moveSpeed);
					_disY += _moveSpeed;
				}
				else
				{
					_disY += _moveSpeed;
				}
			}
			else
			{
				if (_playerRc.bottom <= WINSIZEY) _disY += _moveSpeed;
			}
			break;
		case player::LINK_MOTION_RIGHT_MAGICPOT_ABSORB:
		case player::LINK_MOTION_LEFT_MAGICPOT_ABSORB:
		case player::LINK_MOTION_UP_MAGICPOT_ABSORB:

			L_Motion = LINK_MOTION_DOWN_MAGICPOT_ABSORB;

			if (_cam->isCameraYEndSide())
			{
				if (_playerRc.bottom >= WINSIZEY / 2 + 35 && !_isStore)
				{
					_cam->setCameraY(_cam->getCameraY() + _moveSpeed);
					_disY += _moveSpeed;
				}
				else
				{
					_disY += _moveSpeed;
				}
			}
			else
			{
				if (_playerRc.bottom <= WINSIZEY) _disY += _moveSpeed;
			}

			break;
		case player::LINK_MOTION_RIGHT_MAGICPOT_FIRE:
		case player::LINK_MOTION_LEFT_MAGICPOT_FIRE:
		case player::LINK_MOTION_UP_MAGICPOT_FIRE:

			L_Motion = LINK_MOTION_DOWN_MAGICPOT_FIRE;

			if (_cam->isCameraYEndSide())
			{
				if (_playerRc.bottom >= WINSIZEY / 2 + 35 && !_isStore)
				{
					_cam->setCameraY(_cam->getCameraY() + _moveSpeed);
					_disY += _moveSpeed;
				}
				else
				{
					_disY += _moveSpeed;
				}
			}
			else
			{
				if (_playerRc.bottom <= WINSIZEY) _disY += _moveSpeed;
			}

			break;
		default:

			if (_cam->isCameraYEndSide())
			{
				if (_playerRc.bottom >= WINSIZEY / 2 + 35 && !_isStore)
				{
					_cam->setCameraY(_cam->getCameraY() + _moveSpeed);
					_disY += _moveSpeed;
				}
				else
				{
					_disY += _moveSpeed;
				}
			}
			else
			{
				if (_playerRc.bottom <= WINSIZEY) _disY += _moveSpeed;
			}

			break;
		}
	}

	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		if (L_Motion == LINK_MOTION_LEFT_WALK)
		{
			_currentFrameX = 0;
			L_Motion = LINK_MOTION_LEFT;
		}
		if (L_Motion == LINK_MOTION_LEFT_SHIELD_MOVE)
		{
			_currentFrameX = 0;
			L_Motion = LINK_MOTION_LEFT_SHIELD_STAND;
		}
		if (L_Motion == LINK_MOTION_RIGHT_SHIELD_MOVE)
		{
			_currentFrameX = 0;
			L_Motion = LINK_MOTION_RIGHT_SHIELD_STAND;
		}
		if (L_Motion == LINK_MOTION_UP_SHIELD_MOVE)
		{
			_currentFrameX = 0;
			L_Motion = LINK_MOTION_UP_SHIELD_STAND;
		}
		if (L_Motion == LINK_MOTION_DOWN_SHIELD_MOVE)
		{
			_currentFrameX = 0;
			L_Motion = LINK_MOTION_DOWN_SHIELD_STAND;
		}
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		if (L_Motion == LINK_MOTION_RIGHT_WALK)
		{
			_currentFrameX = 0;
			L_Motion = LINK_MOTION_RIGHT;
		}
		if (L_Motion == LINK_MOTION_LEFT_SHIELD_MOVE)
		{
			_currentFrameX = 0;
			L_Motion = LINK_MOTION_LEFT_SHIELD_STAND;
		}
		if (L_Motion == LINK_MOTION_RIGHT_SHIELD_MOVE)
		{
			_currentFrameX = 0;
			L_Motion = LINK_MOTION_RIGHT_SHIELD_STAND;
		}
		if (L_Motion == LINK_MOTION_UP_SHIELD_MOVE)
		{
			_currentFrameX = 0;
			L_Motion = LINK_MOTION_UP_SHIELD_STAND;
		}
		if (L_Motion == LINK_MOTION_DOWN_SHIELD_MOVE)
		{
			_currentFrameX = 0;
			L_Motion = LINK_MOTION_DOWN_SHIELD_STAND;
		}
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_UP))
	{
		if (L_Motion == LINK_MOTION_UP_WALK)
		{
			_currentFrameX = 0;
			L_Motion = LINK_MOTION_UP;
		}
		if (L_Motion == LINK_MOTION_LEFT_SHIELD_MOVE)
		{
			_currentFrameX = 0;
			L_Motion = LINK_MOTION_LEFT_SHIELD_STAND;
		}
		if (L_Motion == LINK_MOTION_RIGHT_SHIELD_MOVE)
		{
			_currentFrameX = 0;
			L_Motion = LINK_MOTION_RIGHT_SHIELD_STAND;
		}
		if (L_Motion == LINK_MOTION_UP_SHIELD_MOVE)
		{
			_currentFrameX = 0;
			L_Motion = LINK_MOTION_UP_SHIELD_STAND;
		}
		if (L_Motion == LINK_MOTION_DOWN_SHIELD_MOVE)
		{
			_currentFrameX = 0;
			L_Motion = LINK_MOTION_DOWN_SHIELD_STAND;
		}
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{
		if (L_Motion == LINK_MOTION_DOWN_WALK)
		{
			_currentFrameX = 0;
			L_Motion = LINK_MOTION_DOWN;
		}
		if (L_Motion == LINK_MOTION_LEFT_SHIELD_MOVE)
		{
			_currentFrameX = 0;
			L_Motion = LINK_MOTION_LEFT_SHIELD_STAND;
		}
		if (L_Motion == LINK_MOTION_RIGHT_SHIELD_MOVE)
		{
			_currentFrameX = 0;
			L_Motion = LINK_MOTION_RIGHT_SHIELD_STAND;
		}
		if (L_Motion == LINK_MOTION_UP_SHIELD_MOVE)
		{
			_currentFrameX = 0;
			L_Motion = LINK_MOTION_UP_SHIELD_STAND;
		}
		if (L_Motion == LINK_MOTION_DOWN_SHIELD_MOVE)
		{
			_currentFrameX = 0;
			L_Motion = LINK_MOTION_DOWN_SHIELD_STAND;
		}
	}

	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		SOUNDMANAGER->play("젤다구르기", 0.5f);

		switch (L_Motion)
		{
		case player::LINK_MOTION_RIGHT:

			_currentFrameX = 0;
			L_Motion = LINK_MOTION_RIGHT_GRAB;

			break;
		case player::LINK_MOTION_LEFT:

			_currentFrameX = 0;
			L_Motion = LINK_MOTION_LEFT_GRAB;

			break;
		case player::LINK_MOTION_UP:

			_currentFrameX = 0;
			L_Motion = LINK_MOTION_UP_GRAB;

			break;
		case player::LINK_MOTION_DOWN:

			_currentFrameX = 0;
			L_Motion = LINK_MOTION_DOWN_GRAB;

			break;
		case player::LINK_MOTION_RIGHT_WALK:

			_currentFrameX = 0;
			L_Motion = LINK_MOTION_RIGHT_TUMBLE;

			break;
		case player::LINK_MOTION_LEFT_WALK:

			_currentFrameX = 0;
			L_Motion = LINK_MOTION_LEFT_TUMBLE;

			break;
		case player::LINK_MOTION_UP_WALK:

			_currentFrameX = 0;
			L_Motion = LINK_MOTION_UP_TUMBLE;

			break;
		case player::LINK_MOTION_DOWN_WALK:

			_currentFrameX = 0;
			L_Motion = LINK_MOTION_DOWN_TUMBLE;

			break;
		}
	}
	if (_sword)
	{
		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			SOUNDMANAGER->play("젤다검기본소리", 0.5f);
			SOUNDMANAGER->play("젤다기본베기기합", 0.5f);

			switch (L_Motion)
			{
			case player::LINK_MOTION_RIGHT:
			case player::LINK_MOTION_RIGHT_WALK:

				_currentFrameX = 0;
				L_Motion = LINK_MOTION_RIGHT_SWORD_ATTACK;

				break;
			case player::LINK_MOTION_LEFT:
			case player::LINK_MOTION_LEFT_WALK:

				_currentFrameX = 0;
				L_Motion = LINK_MOTION_LEFT_SWORD_ATTACK;

				break;
			case player::LINK_MOTION_UP:
			case player::LINK_MOTION_UP_WALK:

				_currentFrameX = 0;
				L_Motion = LINK_MOTION_UP_SWORD_ATTACK;

				break;
			case player::LINK_MOTION_DOWN:
			case player::LINK_MOTION_DOWN_WALK:

				_currentFrameX = 0;
				L_Motion = LINK_MOTION_DOWN_SWORD_ATTACK;

				break;
			}
		}
	}
	if (_shield)
	{
		if (KEYMANAGER->isStayKeyDown('X'))
		{
			if (!SOUNDMANAGER->isPlaySound("젤다방패들기"))
				SOUNDMANAGER->play("젤다방패들기", 0.5f);

			switch (L_Motion)
			{
			case player::LINK_MOTION_RIGHT:
			case player::LINK_MOTION_RIGHT_WALK:

				L_Motion = LINK_MOTION_RIGHT_SHIELD_OPEN;

				break;
			case player::LINK_MOTION_LEFT:
			case player::LINK_MOTION_LEFT_WALK:

				L_Motion = LINK_MOTION_LEFT_SHIELD_OPEN;

				break;
			case player::LINK_MOTION_UP:
			case player::LINK_MOTION_UP_WALK:

				L_Motion = LINK_MOTION_UP_SHIELD_OPEN;

				break;
			case player::LINK_MOTION_DOWN:
			case player::LINK_MOTION_DOWN_WALK:

				L_Motion = LINK_MOTION_DOWN_SHIELD_OPEN;

				break;
			}
		}
	}
	if (KEYMANAGER->isOnceKeyUp('X'))
	{
		switch (L_Motion)
		{
		case player::LINK_MOTION_RIGHT_SHIELD_STAND:
		case player::LINK_MOTION_RIGHT_SHIELD_MOVE:
		case player::LINK_MOTION_RIGHT_SHIELD_OPEN:

			_currentFrameX = 0;
			L_Motion = LINK_MOTION_RIGHT;
			_rcCrushCenX = -100000;
			_rcCrushCenY = -100000;
			_rcCrush = RectMakeCenter(_rcCrushCenX, _rcCrushCenY, 50, 50);

			break;
		case player::LINK_MOTION_LEFT_SHIELD_STAND:
		case player::LINK_MOTION_LEFT_SHIELD_MOVE:
		case player::LINK_MOTION_LEFT_SHIELD_OPEN:

			_currentFrameX = 0;
			L_Motion = LINK_MOTION_LEFT;
			_rcCrushCenX = -100000;
			_rcCrushCenY = -100000;
			_rcCrush = RectMakeCenter(_rcCrushCenX, _rcCrushCenY, 50, 50);

			break;
		case player::LINK_MOTION_UP_SHIELD_STAND:
		case player::LINK_MOTION_UP_SHIELD_MOVE:
		case player::LINK_MOTION_UP_SHIELD_OPEN:

			_currentFrameX = 0;
			L_Motion = LINK_MOTION_UP;
			_rcCrushCenX = -100000;
			_rcCrushCenY = -100000;
			_rcCrush = RectMakeCenter(_rcCrushCenX, _rcCrushCenY, 50, 50);

			break;
		case player::LINK_MOTION_DOWN_SHIELD_STAND:
		case player::LINK_MOTION_DOWN_SHIELD_MOVE:
		case player::LINK_MOTION_DOWN_SHIELD_OPEN:

			_currentFrameX = 0;
			L_Motion = LINK_MOTION_DOWN;
			_rcCrushCenX = -100000;
			_rcCrushCenY = -100000;
			_rcCrush = RectMakeCenter(_rcCrushCenX, _rcCrushCenY, 50, 50);

			break;
		}
	}
	if (_rollingAttack && _sword)
	{
		if (KEYMANAGER->isOnceKeyDown('A'))
		{
			SOUNDMANAGER->play("젤다검회전소리", 0.5f);
			SOUNDMANAGER->play("젤다회전베기기합", 0.5f);

			switch (L_Motion)
			{
			case player::LINK_MOTION_RIGHT:
			case player::LINK_MOTION_RIGHT_WALK:

				_currentFrameX = 0;
				L_Motion = LINK_MOTION_RIGHT_ROLLING_ATTACK;

				break;
			case player::LINK_MOTION_LEFT:
			case player::LINK_MOTION_LEFT_WALK:

				_currentFrameX = 0;
				L_Motion = LINK_MOTION_LEFT_ROLLING_ATTACK;

				break;
			case player::LINK_MOTION_UP:
			case player::LINK_MOTION_UP_WALK:

				_currentFrameX = 0;
				L_Motion = LINK_MOTION_UP_ROLLING_ATTACK;

				break;
			case player::LINK_MOTION_DOWN:
			case player::LINK_MOTION_DOWN_WALK:

				_currentFrameX = 0;
				L_Motion = LINK_MOTION_DOWN_ROLLING_ATTACK;

				break;
			}
		}
	}
	if (_magicpot)
	{
		if (KEYMANAGER->isStayKeyDown('C'))
		{
			switch (L_Motion)
			{
			case player::LINK_MOTION_RIGHT:
			case player::LINK_MOTION_RIGHT_WALK:

				L_Motion = LINK_MOTION_RIGHT_MAGICPOT_ABSORB;

				break;
			case player::LINK_MOTION_LEFT:
			case player::LINK_MOTION_LEFT_WALK:

				L_Motion = LINK_MOTION_LEFT_MAGICPOT_ABSORB;

				break;
			case player::LINK_MOTION_UP:
			case player::LINK_MOTION_UP_WALK:

				L_Motion = LINK_MOTION_UP_MAGICPOT_ABSORB;

				break;
			case player::LINK_MOTION_DOWN:
			case player::LINK_MOTION_DOWN_WALK:

				L_Motion = LINK_MOTION_DOWN_MAGICPOT_ABSORB;

				break;
			case player::LINK_MOTION_RIGHT_MAGICPOT_FIRE:

				_rcCrushCenX = -100000;
				_rcCrushCenY = -100000;
				_rcCrush = RectMakeCenter(_rcCrushCenX, _rcCrushCenY, 1, 1);

				break;
			case player::LINK_MOTION_LEFT_MAGICPOT_FIRE:

				_rcCrushCenX = -100000;
				_rcCrushCenY = -100000;
				_rcCrush = RectMakeCenter(_rcCrushCenX, _rcCrushCenY, 1, 1);

				break;
			case player::LINK_MOTION_UP_MAGICPOT_FIRE:

				_rcCrushCenX = -100000;
				_rcCrushCenY = -100000;
				_rcCrush = RectMakeCenter(_rcCrushCenX, _rcCrushCenY, 1, 1);

				break;
			case player::LINK_MOTION_DOWN_MAGICPOT_FIRE:

				_rcCrushCenX = -100000;
				_rcCrushCenY = -100000;
				_rcCrush = RectMakeCenter(_rcCrushCenX, _rcCrushCenY, 1, 1);

				break;
			}
		}
	}
	if (KEYMANAGER->isOnceKeyUp('C'))
	{
		switch (L_Motion)
		{
		case player::LINK_MOTION_RIGHT_MAGICPOT_ABSORB:

			_currentFrameX = 0;
			L_Motion = LINK_MOTION_RIGHT_MAGICPOT_FIRE;
			_rcCrushCenX = -100000;
			_rcCrushCenY = -100000;
			_rcCrush = RectMakeCenter(_rcCrushCenX, _rcCrushCenY, 1, 1);

			break;
		case player::LINK_MOTION_LEFT_MAGICPOT_ABSORB:

			_currentFrameX = 0;
			L_Motion = LINK_MOTION_LEFT_MAGICPOT_FIRE;
			_rcCrushCenX = -100000;
			_rcCrushCenY = -100000;
			_rcCrush = RectMakeCenter(_rcCrushCenX, _rcCrushCenY, 1, 1);

			break;
		case player::LINK_MOTION_UP_MAGICPOT_ABSORB:

			_currentFrameX = 0;
			L_Motion = LINK_MOTION_UP_MAGICPOT_FIRE;
			_rcCrushCenX = -100000;
			_rcCrushCenY = -100000;
			_rcCrush = RectMakeCenter(_rcCrushCenX, _rcCrushCenY, 1, 1);

			break;
		case player::LINK_MOTION_DOWN_MAGICPOT_ABSORB:

			_currentFrameX = 0;
			L_Motion = LINK_MOTION_DOWN_MAGICPOT_FIRE;
			_rcCrushCenX = -100000;
			_rcCrushCenY = -100000;
			_rcCrush = RectMakeCenter(_rcCrushCenX, _rcCrushCenY, 1, 1);

			break;
		}
	}

	if (_isPush)
	{
		switch (L_Motion)
		{
		case player::LINK_MOTION_RIGHT_WALK:
			_currentFrameX = 0;

			L_Motion = LINK_MOTION_RIGHT_PUSH;
			break;
		case player::LINK_MOTION_LEFT_WALK:
			_currentFrameX = 0;

			L_Motion = LINK_MOTION_LEFT_PUSH;
			break;
		case player::LINK_MOTION_UP_WALK:
			_currentFrameX = 0;

			L_Motion = LINK_MOTION_UP_PUSH;
			break;
		case player::LINK_MOTION_DOWN_WALK:
			_currentFrameX = 0;

			L_Motion = LINK_MOTION_DOWN_PUSH;
			break;



		case player::LINK_MOTION_RIGHT_TUMBLE:
			break;
		case player::LINK_MOTION_LEFT_TUMBLE:
			break;
		case player::LINK_MOTION_UP_TUMBLE:
			break;
		case player::LINK_MOTION_DOWN_TUMBLE:
			break;
		case player::LINK_MOTION_RIGHT_SHIELD_MOVE:
			break;
		case player::LINK_MOTION_LEFT_SHIELD_MOVE:
			break;
		case player::LINK_MOTION_UP_SHIELD_MOVE:
			break;
		case player::LINK_MOTION_DOWN_SHIELD_MOVE:
			break;
		case player::LINK_MOTION_RIGHT_MAGICPOT_ABSORB:
			break;
		case player::LINK_MOTION_LEFT_MAGICPOT_ABSORB:
			break;
		case player::LINK_MOTION_UP_MAGICPOT_ABSORB:
			break;
		case player::LINK_MOTION_DOWN_MAGICPOT_ABSORB:
			break;
		case player::LINK_MOTION_RIGHT_MAGICPOT_FIRE:
			break;
		case player::LINK_MOTION_LEFT_MAGICPOT_FIRE:
			break;
		case player::LINK_MOTION_UP_MAGICPOT_FIRE:
			break;
		case player::LINK_MOTION_DOWN_MAGICPOT_FIRE:
			break;

		}
	}

}

void player::move(void)
{
	if (_isCollision) return;

	switch (L_Motion)
	{
	case player::LINK_MOTION_RIGHT:

		break;
	case player::LINK_MOTION_LEFT:

		break;
	case player::LINK_MOTION_UP:

		break;
	case player::LINK_MOTION_DOWN:

		break;
	case player::LINK_MOTION_RIGHT_WALK:

		_moveSpeed = 5;

		_soundCount++;
		if (_soundCount % 20 == 0)
		{
			SOUNDMANAGER->play("젤다걷기", 0.5f);
			_soundCount = 0;
		}

		break;
	case player::LINK_MOTION_LEFT_WALK:

		_moveSpeed = 5;

		_soundCount++;
		if (_soundCount % 20 == 0)
		{
			SOUNDMANAGER->play("젤다걷기", 0.5f);
			_soundCount = 0;
		}

		break;
	case player::LINK_MOTION_UP_WALK:

		_moveSpeed = 5;

		_soundCount++;
		if (_soundCount % 20 == 0)
		{
			SOUNDMANAGER->play("젤다걷기", 0.5f);
			_soundCount = 0;
		}

		break;
	case player::LINK_MOTION_DOWN_WALK:

		_moveSpeed = 5;

		_soundCount++;
		if (_soundCount % 20 == 0)
		{
			SOUNDMANAGER->play("젤다걷기", 0.5f);
			_soundCount = 0;
		}

		break;
	case player::LINK_MOTION_RIGHT_TUMBLE:

		_moveSpeed = 15;

		if (_cam->isCameraXEndSide())
		{
			if (_playerRc.right >= WINSIZEX / 2 + 35 && !_isStore)
			{
				_cam->setCameraX(_cam->getCameraX() + _moveSpeed);
				_disX += _moveSpeed;
			}
			else
			{
				_disX += _moveSpeed;
			}
		}
		else
		{
			if (_playerRc.right <= WINSIZEX) _disX += _moveSpeed;
		}

		break;
	case player::LINK_MOTION_LEFT_TUMBLE:

		_moveSpeed = 15;

		if (_cam->isCameraXZeroSide())
		{
			if (_playerRc.left <= WINSIZEX / 2 - 35 && !_isStore)
			{
				_cam->setCameraX(_cam->getCameraX() - _moveSpeed);
				_disX -= _moveSpeed;
			}
			else
			{
				_disX -= _moveSpeed;
			}
		}
		else
		{
			if (_playerRc.left >= 0) _disX -= _moveSpeed;
		}

		break;
	case player::LINK_MOTION_UP_TUMBLE:

		_moveSpeed = 15;

		if (_cam->isCameraYZeroSide())
		{
			if (_playerRc.top <= WINSIZEY / 2 - 35 && !_isStore)
			{
				_cam->setCameraY(_cam->getCameraY() - _moveSpeed);
				_disY -= _moveSpeed;
			}
			else
			{
				_disY -= _moveSpeed;
			}
		}
		else
		{
			if (_playerRc.top >= 0) _disY -= _moveSpeed;
		}

		break;
	case player::LINK_MOTION_DOWN_TUMBLE:

		_moveSpeed = 15;

		if (_cam->isCameraYEndSide())
		{
			if (_playerRc.bottom >= WINSIZEY / 2 + 35 && !_isStore)
			{
				_cam->setCameraY(_cam->getCameraY() + _moveSpeed);
				_disY += _moveSpeed;
			}
			else
			{
				_disY += _moveSpeed;
			}
		}
		else
		{
			if (_playerRc.bottom <= WINSIZEY) _disY += _moveSpeed;
		}

		break;
	}
}

void player::frameCount(void)
{
	_count++;
	if (_count % _link[L_Motion]._maxFrameCount == 0)
	{
		_link[L_Motion]._linkImg->setFrameX(_currentFrameX);
		_currentFrameX++;

		switch (L_Motion)
		{
		case player::LINK_MOTION_RIGHT_TUMBLE:

			if (_currentFrameX > _link[L_Motion]._linkImg->getMaxFrameX())
			{
				_currentFrameX = 0;
				L_Motion = LINK_MOTION_RIGHT;
			}

			break;
		case player::LINK_MOTION_LEFT_TUMBLE:

			if (_currentFrameX > _link[L_Motion]._linkImg->getMaxFrameX())
			{
				_currentFrameX = 0;
				L_Motion = LINK_MOTION_LEFT;
			}

			break;
		case player::LINK_MOTION_UP_TUMBLE:

			if (_currentFrameX > _link[L_Motion]._linkImg->getMaxFrameX())
			{
				_currentFrameX = 0;
				L_Motion = LINK_MOTION_UP;
			}

			break;
		case player::LINK_MOTION_DOWN_TUMBLE:

			if (_currentFrameX > _link[L_Motion]._linkImg->getMaxFrameX())
			{
				_currentFrameX = 0;
				L_Motion = LINK_MOTION_DOWN;
			}

			break;
		case player::LINK_MOTION_RIGHT_GRAB:

			if (_currentFrameX > _link[L_Motion]._linkImg->getMaxFrameX())
			{
				_currentFrameX = 0;
				L_Motion = LINK_MOTION_RIGHT;
			}

			break;
		case player::LINK_MOTION_LEFT_GRAB:

			if (_currentFrameX > _link[L_Motion]._linkImg->getMaxFrameX())
			{
				_currentFrameX = 0;
				L_Motion = LINK_MOTION_LEFT;
			}

			break;
		case player::LINK_MOTION_UP_GRAB:

			if (_currentFrameX > _link[L_Motion]._linkImg->getMaxFrameX())
			{
				_currentFrameX = 0;
				L_Motion = LINK_MOTION_UP;
			}

			break;
		case player::LINK_MOTION_DOWN_GRAB:

			if (_currentFrameX > _link[L_Motion]._linkImg->getMaxFrameX())
			{
				_currentFrameX = 0;
				L_Motion = LINK_MOTION_DOWN;
			}

			break;
		case player::LINK_MOTION_RIGHT_PUSH:

			if (_currentFrameX > _link[L_Motion]._linkImg->getMaxFrameX())
			{
				_currentFrameX = 0;
				L_Motion = LINK_MOTION_RIGHT;
			}

			break;
		case player::LINK_MOTION_LEFT_PUSH:

			if (_currentFrameX > _link[L_Motion]._linkImg->getMaxFrameX())
			{
				_currentFrameX = 0;
				L_Motion = LINK_MOTION_LEFT;
			}

			break;
		case player::LINK_MOTION_UP_PUSH:

			if (_currentFrameX > _link[L_Motion]._linkImg->getMaxFrameX())
			{
				_currentFrameX = 0;
				L_Motion = LINK_MOTION_UP;
			}

			break;
		case player::LINK_MOTION_DOWN_PUSH:

			if (_currentFrameX > _link[L_Motion]._linkImg->getMaxFrameX())
			{
				_currentFrameX = 0;
				L_Motion = LINK_MOTION_DOWN;
			}

			break;
		case player::LINK_MOTION_RIGHT_SWORD_ATTACK:

			if (_currentFrameX > _link[L_Motion]._linkImg->getMaxFrameX())
			{
				_currentFrameX = 0;
				L_Motion = LINK_MOTION_RIGHT;
			}

			break;
		case player::LINK_MOTION_LEFT_SWORD_ATTACK:

			if (_currentFrameX > _link[L_Motion]._linkImg->getMaxFrameX())
			{
				_currentFrameX = 0;
				L_Motion = LINK_MOTION_LEFT;
			}

			break;
		case player::LINK_MOTION_UP_SWORD_ATTACK:

			if (_currentFrameX > _link[L_Motion]._linkImg->getMaxFrameX())
			{
				_currentFrameX = 0;
				L_Motion = LINK_MOTION_UP;
			}

			break;
		case player::LINK_MOTION_DOWN_SWORD_ATTACK:

			if (_currentFrameX > _link[L_Motion]._linkImg->getMaxFrameX())
			{
				_currentFrameX = 0;
				L_Motion = LINK_MOTION_DOWN;
			}

			break;
		case player::LINK_MOTION_RIGHT_SHIELD_OPEN:

			if (_currentFrameX > _link[L_Motion]._linkImg->getMaxFrameX())
			{
				_currentFrameX = 0;
				L_Motion = LINK_MOTION_RIGHT_SHIELD_STAND;
			}

			break;
		case player::LINK_MOTION_LEFT_SHIELD_OPEN:

			if (_currentFrameX > _link[L_Motion]._linkImg->getMaxFrameX())
			{
				_currentFrameX = 0;
				L_Motion = LINK_MOTION_LEFT_SHIELD_STAND;
			}

			break;
		case player::LINK_MOTION_UP_SHIELD_OPEN:

			if (_currentFrameX > _link[L_Motion]._linkImg->getMaxFrameX())
			{
				_currentFrameX = 0;
				L_Motion = LINK_MOTION_UP_SHIELD_STAND;
			}

			break;
		case player::LINK_MOTION_DOWN_SHIELD_OPEN:

			if (_currentFrameX > _link[L_Motion]._linkImg->getMaxFrameX())
			{
				_currentFrameX = 0;
				L_Motion = LINK_MOTION_DOWN_SHIELD_STAND;
			}

			break;
		case player::LINK_MOTION_RIGHT_SHIELD_STAND:

			if (_currentFrameX > _link[L_Motion]._linkImg->getMaxFrameX())
			{
				_currentFrameX = 1;
				L_Motion = LINK_MOTION_RIGHT_SHIELD_STAND;
			}

			break;
		case player::LINK_MOTION_LEFT_SHIELD_STAND:

			if (_currentFrameX > _link[L_Motion]._linkImg->getMaxFrameX())
			{
				_currentFrameX = 1;
				L_Motion = LINK_MOTION_LEFT_SHIELD_STAND;
			}

			break;
		case player::LINK_MOTION_UP_SHIELD_STAND:

			if (_currentFrameX > _link[L_Motion]._linkImg->getMaxFrameX())
			{
				_currentFrameX = 0;
				L_Motion = LINK_MOTION_UP_SHIELD_STAND;
			}

			break;
		case player::LINK_MOTION_DOWN_SHIELD_STAND:

			if (_currentFrameX > _link[L_Motion]._linkImg->getMaxFrameX())
			{
				_currentFrameX = 1;
				L_Motion = LINK_MOTION_DOWN_SHIELD_STAND;
			}

			break;
		case player::LINK_MOTION_RIGHT_MAGICPOT_ABSORB:

			if (_currentFrameX > _link[L_Motion]._linkImg->getMaxFrameX())
			{
				_currentFrameX = 0;
				L_Motion = LINK_MOTION_RIGHT_MAGICPOT_FIRE;
			}

			break;
		case player::LINK_MOTION_LEFT_MAGICPOT_ABSORB:

			if (_currentFrameX > _link[L_Motion]._linkImg->getMaxFrameX())
			{
				_currentFrameX = 0;
				L_Motion = LINK_MOTION_LEFT_MAGICPOT_FIRE;
			}

			break;
		case player::LINK_MOTION_UP_MAGICPOT_ABSORB:

			if (_currentFrameX > _link[L_Motion]._linkImg->getMaxFrameX())
			{
				_currentFrameX = 0;
				L_Motion = LINK_MOTION_UP_MAGICPOT_FIRE;
			}

			break;
		case player::LINK_MOTION_DOWN_MAGICPOT_ABSORB:

			if (_currentFrameX > _link[L_Motion]._linkImg->getMaxFrameX())
			{
				_currentFrameX = 0;
				L_Motion = LINK_MOTION_DOWN_MAGICPOT_FIRE;
			}

			break;
		case player::LINK_MOTION_RIGHT_MAGICPOT_FIRE:

			if (_currentFrameX > _link[L_Motion]._linkImg->getMaxFrameX())
			{
				_currentFrameX = 0;
				L_Motion = LINK_MOTION_RIGHT;
			}

			break;
		case player::LINK_MOTION_LEFT_MAGICPOT_FIRE:

			if (_currentFrameX > _link[L_Motion]._linkImg->getMaxFrameX())
			{
				_currentFrameX = 0;
				L_Motion = LINK_MOTION_LEFT;
			}

			break;
		case player::LINK_MOTION_UP_MAGICPOT_FIRE:

			if (_currentFrameX > _link[L_Motion]._linkImg->getMaxFrameX())
			{
				_currentFrameX = 0;
				L_Motion = LINK_MOTION_UP;
			}

			break;
		case player::LINK_MOTION_DOWN_MAGICPOT_FIRE:

			if (_currentFrameX > _link[L_Motion]._linkImg->getMaxFrameX())
			{
				_currentFrameX = 0;
				L_Motion = LINK_MOTION_DOWN;
			}

			break;
		case player::LINK_MOTION_RIGHT_ROLLING_ATTACK:

			if (_currentFrameX > _link[L_Motion]._linkImg->getMaxFrameX())
			{
				_currentFrameX = 0;
				L_Motion = LINK_MOTION_RIGHT;
			}

			break;
		case player::LINK_MOTION_LEFT_ROLLING_ATTACK:

			if (_currentFrameX > _link[L_Motion]._linkImg->getMaxFrameX())
			{
				_currentFrameX = 0;
				L_Motion = LINK_MOTION_LEFT;
			}

			break;
		case player::LINK_MOTION_UP_ROLLING_ATTACK:

			if (_currentFrameX > _link[L_Motion]._linkImg->getMaxFrameX())
			{
				_currentFrameX = 0;
				L_Motion = LINK_MOTION_UP;
			}

			break;
		case player::LINK_MOTION_DOWN_ROLLING_ATTACK:

			if (_currentFrameX > _link[L_Motion]._linkImg->getMaxFrameX())
			{
				_currentFrameX = 0;
				L_Motion = LINK_MOTION_DOWN;
			}

			break;
		default:

			if (_currentFrameX > _link[L_Motion]._linkImg->getMaxFrameX())
			{
				_currentFrameX = 0;
			}

			break;
		}
		_count = 0;
	}
}

void player::loadImage(void)
{
	FILE* pFile = NULL;

	pFile = fopen("image/Link/txtData/playerMotion.txt", "rt");

	int nMotionCount = 0;
	fscanf(pFile, "motionCount = %d\n", &nMotionCount);

	int nIdx = 0;
	const char strKey[300] = "";
	const char strFileName[300] = "";
	int nWidth = 0;
	int nHeight = 0;
	int nFrameX = 0;
	int nFrameY = 0;
	int nFrameCount = 0;

	for (int i = 0; i < nMotionCount; i++)
	{
		fscanf(pFile, "%d\t	%s\t	%s\t	%d\t	%d\t	%d\t	%d\t	%d\n", &nIdx, strKey, strFileName, &nWidth, &nHeight, &nFrameX, &nFrameY, &nFrameCount);
		_link[i]._linkImg = IMAGEMANAGER->addFrameImage(strKey, strFileName, nWidth, nHeight, nFrameX, nFrameY, true, RGB(255, 0, 255));
		_link[i]._maxFrameCount = nFrameCount;
	}
}

void player::pixelCollision(image* pixelImg)
{
	//오른쪽 픽셀 충돌
	_probeX = (int)_disX + _link[L_Motion]._linkImg->getFrameWidth() / 2 + 35;
	_probeY = (int)_disY + 130;

	for (int i = _probeX; i < _probeX + 10; i++)
	{
		for (int j = _probeY; j < _probeY + 20; j++)
		{
			COLORREF color = GetPixel(pixelImg->getMemDC(), i, j);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (!(r == 255 && g == 0 && b == 255))
			{
				switch (L_Motion)
				{
				case player::LINK_MOTION_RIGHT_WALK:
				case player::LINK_MOTION_LEFT_WALK:
				case player::LINK_MOTION_UP_WALK:
				case player::LINK_MOTION_DOWN_WALK:
					_disX = (float)i - 184;
					break;
				case player::LINK_MOTION_RIGHT_TUMBLE:
				case player::LINK_MOTION_LEFT_TUMBLE:
				case player::LINK_MOTION_UP_TUMBLE:
				case player::LINK_MOTION_DOWN_TUMBLE:
					_disX = (float)i - 194.5;
					break;
				case player::LINK_MOTION_RIGHT_SHIELD_MOVE:
				case player::LINK_MOTION_LEFT_SHIELD_MOVE:
				case player::LINK_MOTION_UP_SHIELD_MOVE:
				case player::LINK_MOTION_DOWN_SHIELD_MOVE:
					_disX = (float)i - 184;
					break;
				case player::LINK_MOTION_RIGHT_MAGICPOT_ABSORB:
				case player::LINK_MOTION_LEFT_MAGICPOT_ABSORB:
				case player::LINK_MOTION_UP_MAGICPOT_ABSORB:
				case player::LINK_MOTION_DOWN_MAGICPOT_ABSORB:
					_disX = (float)i - 184;
					break;
				case player::LINK_MOTION_RIGHT_MAGICPOT_FIRE:
				case player::LINK_MOTION_LEFT_MAGICPOT_FIRE:
				case player::LINK_MOTION_UP_MAGICPOT_FIRE:
				case player::LINK_MOTION_DOWN_MAGICPOT_FIRE:
					_disX = (float)i - 184;
					break;
				case player::LINK_MOTION_RIGHT_ROLLING_ATTACK:
				case player::LINK_MOTION_LEFT_ROLLING_ATTACK:
				case player::LINK_MOTION_UP_ROLLING_ATTACK:
				case player::LINK_MOTION_DOWN_ROLLING_ATTACK:
					_disX = (float)i - 184;
					break;
				}
			}
		}
	}

	//왼쪽 픽셀 충돌
	_probeX = (int)_disX + _link[L_Motion]._linkImg->getFrameWidth() / 2 - 35;
	_probeY = (int)_disY + 130;

	for (int i = _probeX; i < _probeX + 10; i++)
	{
		for (int j = _probeY; j < _probeY + 20; j++)
		{
			COLORREF color = GetPixel(pixelImg->getMemDC(), i, j);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (!(r == 255 && g == 0 && b == 255))
			{
				switch (L_Motion)
				{
				case player::LINK_MOTION_RIGHT_WALK:
				case player::LINK_MOTION_LEFT_WALK:
				case player::LINK_MOTION_UP_WALK:
				case player::LINK_MOTION_DOWN_WALK:
					_disX = (float)i - 95;
					break;
				case player::LINK_MOTION_RIGHT_TUMBLE:
				case player::LINK_MOTION_LEFT_TUMBLE:
				case player::LINK_MOTION_UP_TUMBLE:
				case player::LINK_MOTION_DOWN_TUMBLE:
					_disX = (float)i - 85;
					break;
				case player::LINK_MOTION_RIGHT_SHIELD_MOVE:
				case player::LINK_MOTION_LEFT_SHIELD_MOVE:
				case player::LINK_MOTION_UP_SHIELD_MOVE:
				case player::LINK_MOTION_DOWN_SHIELD_MOVE:
					_disX = (float)i - 95;
					break;
				case player::LINK_MOTION_RIGHT_MAGICPOT_ABSORB:
				case player::LINK_MOTION_LEFT_MAGICPOT_ABSORB:
				case player::LINK_MOTION_UP_MAGICPOT_ABSORB:
				case player::LINK_MOTION_DOWN_MAGICPOT_ABSORB:

					_disX = (float)i - 95;
					break;
				case player::LINK_MOTION_RIGHT_MAGICPOT_FIRE:
				case player::LINK_MOTION_LEFT_MAGICPOT_FIRE:
				case player::LINK_MOTION_UP_MAGICPOT_FIRE:
				case player::LINK_MOTION_DOWN_MAGICPOT_FIRE:
					_disX = (float)i - 95;
					break;
				case player::LINK_MOTION_RIGHT_ROLLING_ATTACK:
				case player::LINK_MOTION_LEFT_ROLLING_ATTACK:
				case player::LINK_MOTION_UP_ROLLING_ATTACK:
				case player::LINK_MOTION_DOWN_ROLLING_ATTACK:
					_disX = (float)i - 95;
					break;
				}
			}
		}
	}

	//위쪽 픽셀 충돌
	_probeX = (int)_disX + 130;
	_probeY = (int)_disY + _link[L_Motion]._linkImg->getFrameHeight() / 2 - 45;

	for (int i = _probeX; i < _probeX + 20; i++)
	{
		for (int j = _probeY; j < _probeY + 10; j++)
		{
			COLORREF color = GetPixel(pixelImg->getMemDC(), i, j);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (!(r == 255 && g == 0 && b == 255))
			{
				switch (L_Motion)
				{
				case player::LINK_MOTION_RIGHT_WALK:
				case player::LINK_MOTION_LEFT_WALK:
				case player::LINK_MOTION_UP_WALK:
				case player::LINK_MOTION_DOWN_WALK:
					_disY = (float)j - 95;
					break;
				case player::LINK_MOTION_RIGHT_TUMBLE:
				case player::LINK_MOTION_LEFT_TUMBLE:
				case player::LINK_MOTION_UP_TUMBLE:
				case player::LINK_MOTION_DOWN_TUMBLE:
					_disY = (float)j - 85;
					break;
				case player::LINK_MOTION_RIGHT_SHIELD_MOVE:
				case player::LINK_MOTION_LEFT_SHIELD_MOVE:
				case player::LINK_MOTION_UP_SHIELD_MOVE:
				case player::LINK_MOTION_DOWN_SHIELD_MOVE:
					_disY = (float)j - 95;
					break;
				case player::LINK_MOTION_RIGHT_MAGICPOT_ABSORB:
				case player::LINK_MOTION_LEFT_MAGICPOT_ABSORB:
				case player::LINK_MOTION_UP_MAGICPOT_ABSORB:
				case player::LINK_MOTION_DOWN_MAGICPOT_ABSORB:
					_disY = (float)j - 95;
					break;
				case player::LINK_MOTION_RIGHT_MAGICPOT_FIRE:
				case player::LINK_MOTION_LEFT_MAGICPOT_FIRE:
				case player::LINK_MOTION_UP_MAGICPOT_FIRE:
				case player::LINK_MOTION_DOWN_MAGICPOT_FIRE:
					_disY = (float)j - 95;
					break;
				case player::LINK_MOTION_RIGHT_ROLLING_ATTACK:
				case player::LINK_MOTION_LEFT_ROLLING_ATTACK:
				case player::LINK_MOTION_UP_ROLLING_ATTACK:
				case player::LINK_MOTION_DOWN_ROLLING_ATTACK:
					_disY = (float)j - 95;
					break;
				}
			}
		}
	}

	//아래쪽 픽셀 충돌
	_probeX = (int)_disX + 130;
	_probeY = (int)_disY + _link[L_Motion]._linkImg->getFrameHeight() / 2 + 35;

	for (int i = _probeX; i < _probeX + 20; i++)
	{
		for (int j = _probeY; j < _probeY + 10; j++)
		{
			COLORREF color = GetPixel(pixelImg->getMemDC(), i, j);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (!(r == 255 && g == 0 && b == 255))
			{
				switch (L_Motion)
				{
				case player::LINK_MOTION_RIGHT_WALK:
				case player::LINK_MOTION_LEFT_WALK:
				case player::LINK_MOTION_UP_WALK:
				case player::LINK_MOTION_DOWN_WALK:
					_disY = (float)j - 186;
					break;
				case player::LINK_MOTION_RIGHT_TUMBLE:
				case player::LINK_MOTION_LEFT_TUMBLE:
				case player::LINK_MOTION_UP_TUMBLE:
				case player::LINK_MOTION_DOWN_TUMBLE:
					_disY = (float)j - 197;
					break;
				case player::LINK_MOTION_RIGHT_SHIELD_MOVE:
				case player::LINK_MOTION_LEFT_SHIELD_MOVE:
				case player::LINK_MOTION_UP_SHIELD_MOVE:
				case player::LINK_MOTION_DOWN_SHIELD_MOVE:
					_disY = (float)j - 186;
					break;
				case player::LINK_MOTION_RIGHT_MAGICPOT_ABSORB:
				case player::LINK_MOTION_LEFT_MAGICPOT_ABSORB:
				case player::LINK_MOTION_UP_MAGICPOT_ABSORB:
				case player::LINK_MOTION_DOWN_MAGICPOT_ABSORB:
					_disY = (float)j - 186;
					break;
				case player::LINK_MOTION_RIGHT_MAGICPOT_FIRE:
				case player::LINK_MOTION_LEFT_MAGICPOT_FIRE:
				case player::LINK_MOTION_UP_MAGICPOT_FIRE:
				case player::LINK_MOTION_DOWN_MAGICPOT_FIRE:
					_disY = (float)j - 186;
					break;
				case player::LINK_MOTION_RIGHT_ROLLING_ATTACK:
				case player::LINK_MOTION_LEFT_ROLLING_ATTACK:
				case player::LINK_MOTION_UP_ROLLING_ATTACK:
				case player::LINK_MOTION_DOWN_ROLLING_ATTACK:
					_disY = (float)j - 186;
					break;
				}
			}
		}
	}
}

void player::makeCrushRc()
{
	switch (L_Motion)
	{
	case player::LINK_MOTION_RIGHT_GRAB:

		_frameX = _link[L_Motion]._linkImg->getFrameX();
		if (_frameX == 1)
		{
			_rcCrushCenX = _X + 190;
			_rcCrushCenY = _Y + 135;
			_rcCrush = RectMakeCenter(_rcCrushCenX, _rcCrushCenY, 50, 80);
			_damage = 1.F;
			_linkCrushRc = { _rcCrush, _damage };
			_rcAtr = RC_ATR_GRAB;
		}
		if (_frameX == 2)
		{
			_rcCrushCenX = -100000;
			_rcCrushCenY = -100000;
			_rcCrush = RectMakeCenter(_rcCrushCenX, _rcCrushCenY, 1, 1);
		}

		break;
	case player::LINK_MOTION_LEFT_GRAB:

		_frameX = _link[L_Motion]._linkImg->getFrameX();
		if (_frameX == 1)
		{
			_rcCrushCenX = _X + 80;
			_rcCrushCenY = _Y + 135;
			_rcCrush = RectMakeCenter(_rcCrushCenX, _rcCrushCenY, 50, 80);
			_damage = 1.F;
			_linkCrushRc = { _rcCrush, _damage };
			_rcAtr = RC_ATR_GRAB;
		}
		if (_frameX == 2)
		{
			_rcCrushCenX = -100000;
			_rcCrushCenY = -100000;
			_rcCrush = RectMakeCenter(_rcCrushCenX, _rcCrushCenY, 1, 1);
		}

		break;
	case player::LINK_MOTION_UP_GRAB:

		_frameX = _link[L_Motion]._linkImg->getFrameX();
		if (_frameX == 1)
		{
			_rcCrushCenX = _X + 135;
			_rcCrushCenY = _Y + 70;
			_rcCrush = RectMakeCenter(_rcCrushCenX, _rcCrushCenY, 80, 50);
			_damage = 1.F;
			_linkCrushRc = { _rcCrush, _damage };
			_rcAtr = RC_ATR_GRAB;
		}
		if (_frameX == 2)
		{
			_rcCrushCenX = -100000;
			_rcCrushCenY = -100000;
			_rcCrush = RectMakeCenter(_rcCrushCenX, _rcCrushCenY, 1, 1);
		}

		break;
	case player::LINK_MOTION_DOWN_GRAB:

		_frameX = _link[L_Motion]._linkImg->getFrameX();
		if (_frameX == 1)
		{
			_rcCrushCenX = _X + 135;
			_rcCrushCenY = _Y + 190;
			_rcCrush = RectMakeCenter(_rcCrushCenX, _rcCrushCenY, 80, 50);
			_damage = 1.F;
			_linkCrushRc = { _rcCrush, _damage };
			_rcAtr = RC_ATR_GRAB;
		}
		if (_frameX == 2)
		{
			_rcCrushCenX = -100000;
			_rcCrushCenY = -100000;
			_rcCrush = RectMakeCenter(_rcCrushCenX, _rcCrushCenY, 1, 1);
		}

		break;
	case player::LINK_MOTION_RIGHT_SWORD_ATTACK:

		_frameX = _link[L_Motion]._linkImg->getFrameX();
		if (_frameX >= 2 && _frameX <= 5)
		{
			_rcCrushCenX = _X + 210;
			_rcCrushCenY = _Y + 125;
			_rcCrush = RectMakeCenter(_rcCrushCenX, _rcCrushCenY, 120, 150);
			_damage = 1.F;
			_linkCrushRc = { _rcCrush, _damage };
			_rcAtr = RC_ATR_ATT;
		}
		if (_frameX == 7)
		{
			_rcCrushCenX = -100000;
			_rcCrushCenY = -100000;
			_rcCrush = RectMakeCenter(_rcCrushCenX, _rcCrushCenY, 120, 150);
		}

		break;
	case player::LINK_MOTION_LEFT_SWORD_ATTACK:

		_frameX = _link[L_Motion]._linkImg->getFrameX();
		if (_frameX >= 2 && _frameX <= 5)
		{
			_rcCrushCenX = _X + 60;
			_rcCrushCenY = _Y + 125;
			_rcCrush = RectMakeCenter(_rcCrushCenX, _rcCrushCenY, 120, 150);
			_damage = 1.F;
			_linkCrushRc = { _rcCrush, _damage };
			_rcAtr = RC_ATR_ATT;
		}
		if (_frameX == 7)
		{
			_rcCrushCenX = -100000;
			_rcCrushCenY = -100000;
			_rcCrush = RectMakeCenter(_rcCrushCenX, _rcCrushCenY, 120, 150);
		}

		break;
	case player::LINK_MOTION_UP_SWORD_ATTACK:

		_frameX = _link[L_Motion]._linkImg->getFrameX();
		if (_frameX >= 2 && _frameX <= 5)
		{
			_rcCrushCenX = _X + 120;
			_rcCrushCenY = _Y + 60;
			_rcCrush = RectMakeCenter(_rcCrushCenX, _rcCrushCenY, 170, 120);
			_damage = 1.F;
			_linkCrushRc = { _rcCrush, _damage };
			_rcAtr = RC_ATR_ATT;
		}
		if (_frameX == 7)
		{
			_rcCrushCenX = -100000;
			_rcCrushCenY = -100000;
			_rcCrush = RectMakeCenter(_rcCrushCenX, _rcCrushCenY, 120, 150);
		}

		break;
	case player::LINK_MOTION_DOWN_SWORD_ATTACK:

		_frameX = _link[L_Motion]._linkImg->getFrameX();
		if (_frameX >= 2 && _frameX <= 5)
		{
			_rcCrushCenX = _X + 150;
			_rcCrushCenY = _Y + 195;
			_rcCrush = RectMakeCenter(_rcCrushCenX, _rcCrushCenY, 170, 120);
			_damage = 1.F;
			_linkCrushRc = { _rcCrush, _damage };
			_rcAtr = RC_ATR_ATT;
		}
		if (_frameX == 7)
		{
			_rcCrushCenX = -100000;
			_rcCrushCenY = -100000;
			_rcCrush = RectMakeCenter(_rcCrushCenX, _rcCrushCenY, 120, 150);
		}

		break;
	case player::LINK_MOTION_RIGHT_SHIELD_STAND:

		_rcCrushCenX = _X + 175;
		_rcCrushCenY = _Y + 125;
		_rcCrush = RectMakeCenter(_rcCrushCenX, _rcCrushCenY, 20, 100);
		_rcAtr = RC_ATR_DEF;

		break;
	case player::LINK_MOTION_LEFT_SHIELD_STAND:

		_rcCrushCenX = _X + 95;
		_rcCrushCenY = _Y + 125;
		_rcCrush = RectMakeCenter(_rcCrushCenX, _rcCrushCenY, 20, 100);
		_rcAtr = RC_ATR_DEF;

		break;
	case player::LINK_MOTION_UP_SHIELD_STAND:

		_rcCrushCenX = _X + 130;
		_rcCrushCenY = _Y + 70;
		_rcCrush = RectMakeCenter(_rcCrushCenX, _rcCrushCenY, 100, 20);
		_rcAtr = RC_ATR_DEF;

		break;
	case player::LINK_MOTION_DOWN_SHIELD_STAND:

		_rcCrushCenX = _X + 135;
		_rcCrushCenY = _Y + 185;
		_rcCrush = RectMakeCenter(_rcCrushCenX, _rcCrushCenY, 100, 20);
		_rcAtr = RC_ATR_DEF;

		break;
	case player::LINK_MOTION_RIGHT_SHIELD_MOVE:

		_rcCrushCenX = _X + 175;
		_rcCrushCenY = _Y + 125;
		_rcCrush = RectMakeCenter(_rcCrushCenX, _rcCrushCenY, 20, 100);
		_rcAtr = RC_ATR_DEF;

		break;
	case player::LINK_MOTION_LEFT_SHIELD_MOVE:

		_rcCrushCenX = _X + 95;
		_rcCrushCenY = _Y + 125;
		_rcCrush = RectMakeCenter(_rcCrushCenX, _rcCrushCenY, 20, 100);
		_rcAtr = RC_ATR_DEF;

		break;
	case player::LINK_MOTION_UP_SHIELD_MOVE:

		_rcCrushCenX = _X + 130;
		_rcCrushCenY = _Y + 70;
		_rcCrush = RectMakeCenter(_rcCrushCenX, _rcCrushCenY, 100, 20);
		_rcAtr = RC_ATR_DEF;

		break;
	case player::LINK_MOTION_DOWN_SHIELD_MOVE:

		_rcCrushCenX = _X + 135;
		_rcCrushCenY = _Y + 185;
		_rcCrush = RectMakeCenter(_rcCrushCenX, _rcCrushCenY, 100, 20);
		_rcAtr = RC_ATR_DEF;

		break;
	case player::LINK_MOTION_RIGHT_MAGICPOT_ABSORB:

		_rcCrushCenX = _X + 425;
		_rcCrushCenY = _Y + 125;
		_rcCrush = RectMakeCenter(_rcCrushCenX, _rcCrushCenY, 500, 150);
		_damage = 1.F;
		_linkCrushRc = { _rcCrush, _damage };
		_rcAtr = RC_ATR_ABSORB;

		break;
	case player::LINK_MOTION_LEFT_MAGICPOT_ABSORB:

		_rcCrushCenX = _X - 145;
		_rcCrushCenY = _Y + 125;
		_rcCrush = RectMakeCenter(_rcCrushCenX, _rcCrushCenY, 500, 150);
		_damage = 1.F;
		_linkCrushRc = { _rcCrush, _damage };
		_rcAtr = RC_ATR_ABSORB;

		break;
	case player::LINK_MOTION_UP_MAGICPOT_ABSORB:

		_rcCrushCenX = _X + 130;
		_rcCrushCenY = _Y - 155;
		_rcCrush = RectMakeCenter(_rcCrushCenX, _rcCrushCenY, 150, 500);
		_damage = 1.F;
		_linkCrushRc = { _rcCrush, _damage };
		_rcAtr = RC_ATR_ABSORB;

		break;
	case player::LINK_MOTION_DOWN_MAGICPOT_ABSORB:

		_rcCrushCenX = _X + 140;
		_rcCrushCenY = _Y + 425;
		_rcCrush = RectMakeCenter(_rcCrushCenX, _rcCrushCenY, 150, 500);
		_damage = 1.F;
		_linkCrushRc = { _rcCrush, _damage };
		_rcAtr = RC_ATR_ABSORB;

		break;
	case player::LINK_MOTION_RIGHT_ROLLING_ATTACK:

		_frameX = _link[L_Motion]._linkImg->getFrameX();
		if (_frameX >= 2 && _frameX <= 11)
		{
			_rcCrushCenX = _X + 135;
			_rcCrushCenY = _Y + 135;
			_rcCrush = RectMakeCenter(_rcCrushCenX, _rcCrushCenY, 250, 250);
			_damage = 1.F;
			_linkCrushRc = { _rcCrush, _damage };
			_rcAtr = RC_ATR_ATT;
		}
		if (_frameX == 12)
		{
			_rcCrushCenX = -100000;
			_rcCrushCenY = -100000;
			_rcCrush = RectMakeCenter(_rcCrushCenX, _rcCrushCenY, 1, 1);
		}

		break;
	case player::LINK_MOTION_LEFT_ROLLING_ATTACK:

		_frameX = _link[L_Motion]._linkImg->getFrameX();
		if (_frameX >= 2 && _frameX <= 11)
		{
			_rcCrushCenX = _X + 135;
			_rcCrushCenY = _Y + 135;
			_rcCrush = RectMakeCenter(_rcCrushCenX, _rcCrushCenY, 250, 250);
			_damage = 1.F;
			_linkCrushRc = { _rcCrush, _damage };
			_rcAtr = RC_ATR_ATT;
		}
		if (_frameX == 12)
		{
			_rcCrushCenX = -100000;
			_rcCrushCenY = -100000;
			_rcCrush = RectMakeCenter(_rcCrushCenX, _rcCrushCenY, 1, 1);
		}

		break;
	case player::LINK_MOTION_UP_ROLLING_ATTACK:

		_frameX = _link[L_Motion]._linkImg->getFrameX();
		if (_frameX >= 2 && _frameX <= 11)
		{
			_rcCrushCenX = _X + 135;
			_rcCrushCenY = _Y + 135;
			_rcCrush = RectMakeCenter(_rcCrushCenX, _rcCrushCenY, 250, 250);
			_damage = 1.F;
			_linkCrushRc = { _rcCrush, _damage };
			_rcAtr = RC_ATR_ATT;
		}
		if (_frameX == 12)
		{
			_rcCrushCenX = -100000;
			_rcCrushCenY = -100000;
			_rcCrush = RectMakeCenter(_rcCrushCenX, _rcCrushCenY, 1, 1);
		}

		break;
	case player::LINK_MOTION_DOWN_ROLLING_ATTACK:

		_frameX = _link[L_Motion]._linkImg->getFrameX();
		if (_frameX >= 2 && _frameX <= 11)
		{
			_rcCrushCenX = _X + 135;
			_rcCrushCenY = _Y + 135;
			_rcCrush = RectMakeCenter(_rcCrushCenX, _rcCrushCenY, 250, 250);
			_damage = 1.F;
			_linkCrushRc = { _rcCrush, _damage };
			_rcAtr = RC_ATR_ATT;
		}
		if (_frameX == 12)
		{
			_rcCrushCenX = -100000;
			_rcCrushCenY = -100000;
			_rcCrush = RectMakeCenter(_rcCrushCenX, _rcCrushCenY, 1, 1);
		}

		break;
	}

}

void player::dectectionTileMap()
{
	_linkIdxX = (((_playerRc.right + _playerRc.left) / 2) - _cam->getStartX()) / TILESIZE;
	_linkIdxY = (((_playerRc.bottom + _playerRc.top) / 2) - _cam->getStartY()) / TILESIZE;

	_linkIdx = _linkIdxX + _linkIdxY * TILEX;

	switch (L_Motion)
	{
	case player::LINK_MOTION_RIGHT_WALK:
	case player::LINK_MOTION_RIGHT_TUMBLE:
	case player::LINK_MOTION_RIGHT_PUSH:
	case player::LINK_MOTION_RIGHT_MAGICPOT_FIRE:
	case player::LINK_MOTION_RIGHT_MAGICPOT_ABSORB:
	case player::LINK_MOTION_RIGHT_SHIELD_MOVE:

	{
		tileIndex[0] = _linkIdx + 1;
		if (_playerRc.bottom < _zeldaTileMap->getTile()[tileIndex[0]].rc.bottom)
		{
			tileIndex[1] = tileIndex[0] - TILEX;
		}
		else
		{
			tileIndex[1] = tileIndex[0] + TILEX;
		}
	}

	break;

	case player::LINK_MOTION_LEFT_WALK:
	case player::LINK_MOTION_LEFT_TUMBLE:
	case player::LINK_MOTION_LEFT_PUSH:
	case player::LINK_MOTION_LEFT_MAGICPOT_FIRE:
	case player::LINK_MOTION_LEFT_MAGICPOT_ABSORB:
	case player::LINK_MOTION_LEFT_SHIELD_MOVE:

	{
		tileIndex[0] = _linkIdx - 1;

		if (_playerRc.bottom < _zeldaTileMap->getTile()[tileIndex[0]].rc.bottom)
		{
			tileIndex[1] = tileIndex[0] - TILEX;
		}
		else
		{
			tileIndex[1] = tileIndex[0] + TILEX;
		}
	}

	break;

	case player::LINK_MOTION_UP_WALK:
	case player::LINK_MOTION_UP_TUMBLE:
	case player::LINK_MOTION_UP_PUSH:
	case player::LINK_MOTION_UP_MAGICPOT_FIRE:
	case player::LINK_MOTION_UP_MAGICPOT_ABSORB:
	case player::LINK_MOTION_UP_SHIELD_MOVE:

	{
		tileIndex[0] = _linkIdx - TILEX;

		if (_playerRc.right < _zeldaTileMap->getTile()[tileIndex[0]].rc.right)
		{
			tileIndex[1] = tileIndex[0] - 1;
		}
		else
		{
			tileIndex[1] = tileIndex[0] + 1;
		}
	}

	break;

	case player::LINK_MOTION_DOWN_WALK:
	case player::LINK_MOTION_DOWN_TUMBLE:
	case player::LINK_MOTION_DOWN_PUSH:
	case player::LINK_MOTION_DOWN_MAGICPOT_FIRE:
	case player::LINK_MOTION_DOWN_MAGICPOT_ABSORB:
	case player::LINK_MOTION_DOWN_SHIELD_MOVE:

	{
		tileIndex[0] = _linkIdx + TILEX;
		if (_playerRc.right < _zeldaTileMap->getTile()[tileIndex[0]].rc.right)
		{
			tileIndex[1] = tileIndex[0] - 1;
		}
		else
		{
			tileIndex[1] = tileIndex[0] + 1;
		}
	}

	break;
	}

	RECT rcTmp = {};

	for (int i = 0; i < 2; i++)
	{
		if (IntersectRect(&rcTmp, &_zeldaTileMap->getTile()[tileIndex[i]].rc, &_playerRc))
		{
			if (_zeldaTileMap->getAttribute(E_ATR_MOVE)[tileIndex[i]] == FALSE)
			{
				switch (L_Motion)
				{
				case player::LINK_MOTION_RIGHT_WALK:
				case player::LINK_MOTION_RIGHT_TUMBLE:
				case player::LINK_MOTION_RIGHT_PUSH:
				case player::LINK_MOTION_RIGHT_MAGICPOT_FIRE:
				case player::LINK_MOTION_RIGHT_MAGICPOT_ABSORB:
				case player::LINK_MOTION_RIGHT_SHIELD_MOVE:

				{
					_disX = _zeldaTileMap->getTile()[tileIndex[i]].rc.left - _cam->getStartX() - 170;
				}

				break;

				case player::LINK_MOTION_LEFT_WALK:
				case player::LINK_MOTION_LEFT_TUMBLE:
				case player::LINK_MOTION_LEFT_PUSH:
				case player::LINK_MOTION_LEFT_MAGICPOT_FIRE:
				case player::LINK_MOTION_LEFT_MAGICPOT_ABSORB:
				case player::LINK_MOTION_LEFT_SHIELD_MOVE:

				{
					_disX = _zeldaTileMap->getTile()[tileIndex[i]].rc.right - _cam->getStartX() - 100;
				}

				break;

				case player::LINK_MOTION_UP_WALK:
				case player::LINK_MOTION_UP_TUMBLE:
				case player::LINK_MOTION_UP_PUSH:
				case player::LINK_MOTION_UP_MAGICPOT_FIRE:
				case player::LINK_MOTION_UP_MAGICPOT_ABSORB:
				case player::LINK_MOTION_UP_SHIELD_MOVE:

				{
					_disY = _zeldaTileMap->getTile()[tileIndex[i]].rc.bottom - _cam->getStartY() - 100;
				}

				break;

				case player::LINK_MOTION_DOWN_WALK:
				case player::LINK_MOTION_DOWN_TUMBLE:
				case player::LINK_MOTION_DOWN_PUSH:
				case player::LINK_MOTION_DOWN_MAGICPOT_FIRE:
				case player::LINK_MOTION_DOWN_MAGICPOT_ABSORB:
				case player::LINK_MOTION_DOWN_SHIELD_MOVE:

				{
					_disY = _zeldaTileMap->getTile()[tileIndex[i]].rc.top - _cam->getStartY() - 170;
				}

				break;
				}
			}
			if (_zeldaTileMap->getAttribute(E_ATR_SLOW)[tileIndex[i]] == FALSE)
			{
				switch (L_Motion)
				{
				case player::LINK_MOTION_RIGHT_WALK:
				case player::LINK_MOTION_RIGHT_MAGICPOT_FIRE:
				case player::LINK_MOTION_RIGHT_MAGICPOT_ABSORB:
				case player::LINK_MOTION_RIGHT_SHIELD_MOVE:
				case player::LINK_MOTION_LEFT_WALK:
				case player::LINK_MOTION_LEFT_MAGICPOT_FIRE:
				case player::LINK_MOTION_LEFT_MAGICPOT_ABSORB:
				case player::LINK_MOTION_LEFT_SHIELD_MOVE:
				case player::LINK_MOTION_UP_WALK:
				case player::LINK_MOTION_UP_MAGICPOT_FIRE:
				case player::LINK_MOTION_UP_MAGICPOT_ABSORB:
				case player::LINK_MOTION_UP_SHIELD_MOVE:
				case player::LINK_MOTION_DOWN_WALK:
				case player::LINK_MOTION_DOWN_MAGICPOT_FIRE:
				case player::LINK_MOTION_DOWN_MAGICPOT_ABSORB:
				case player::LINK_MOTION_DOWN_SHIELD_MOVE:

				{
					_moveSpeed = 2;
				}

				break;
				}
			}
		}
	}
}

void player::setIsCollision(bool collision, RECT npcRc)
{
	_isCollision = collision;

	if (_isCollision)
	{
		if (L_Motion == LINK_MOTION_LEFT)
		{
			_disX += npcRc.right - _playerRc.left;
		}
		else if (L_Motion == LINK_MOTION_LEFT_WALK)
		{
			_disX += npcRc.right - _playerRc.left;
		}
		else if (L_Motion == LINK_MOTION_LEFT_TUMBLE)
		{
			_disX += npcRc.right - _playerRc.left;
		}
		else if (L_Motion == LINK_MOTION_LEFT_GRAB)
		{
			_disX += npcRc.right - _playerRc.left;
		}
		else if (L_Motion == LINK_MOTION_LEFT_SHIELD_MOVE)
		{
			_disX += npcRc.right - _playerRc.left;
		}
		else if (L_Motion == LINK_MOTION_LEFT_MAGICPOT_ABSORB)
		{
			_disX += npcRc.right - _playerRc.left;
		}
		else if (L_Motion == LINK_MOTION_LEFT_MAGICPOT_FIRE)
		{
			_disX += npcRc.right - _playerRc.left;
		}
		else if (L_Motion == LINK_MOTION_RIGHT)
		{
			_disX -= _playerRc.right - npcRc.left;
		}
		else if (L_Motion == LINK_MOTION_RIGHT_WALK)
		{
			_disX -= _playerRc.right - npcRc.left;
		}
		else if (L_Motion == LINK_MOTION_RIGHT_TUMBLE)
		{
			_disX -= _playerRc.right - npcRc.left;
		}
		else if (L_Motion == LINK_MOTION_RIGHT_GRAB)
		{
			_disX -= _playerRc.right - npcRc.left;
		}
		else if (L_Motion == LINK_MOTION_RIGHT_SHIELD_MOVE)
		{
			_disX -= _playerRc.right - npcRc.left;
		}
		else if (L_Motion == LINK_MOTION_RIGHT_MAGICPOT_ABSORB)
		{
			_disX -= _playerRc.right - npcRc.left;
		}
		else if (L_Motion == LINK_MOTION_RIGHT_MAGICPOT_FIRE)
		{
			_disX -= _playerRc.right - npcRc.left;
		}
		else if (L_Motion == LINK_MOTION_UP)
		{
			_disY += npcRc.bottom - _playerRc.top;
		}
		else if (L_Motion == LINK_MOTION_UP_WALK)
		{
			_disY += npcRc.bottom - _playerRc.top;
		}
		else if (L_Motion == LINK_MOTION_UP_TUMBLE)
		{
			_disY += npcRc.bottom - _playerRc.top;
		}
		else if (L_Motion == LINK_MOTION_UP_GRAB)
		{
			_disY += npcRc.bottom - _playerRc.top;
		}
		else if (L_Motion == LINK_MOTION_UP_SHIELD_MOVE)
		{
			_disY += npcRc.bottom - _playerRc.top;
		}
		else if (L_Motion == LINK_MOTION_UP_MAGICPOT_ABSORB)
		{
			_disY += npcRc.bottom - _playerRc.top;
		}
		else if (L_Motion == LINK_MOTION_UP_MAGICPOT_FIRE)
		{
			_disY += npcRc.bottom - _playerRc.top;
		}
	}
}

void player::setHpImage()
{
	for (int i = 0; i < HEART_COUNT; i++)
	{
		_hp[i].hpImg[LINK_HP_EMPTY] = IMAGEMANAGER->addImage("하트-빈것(78.72)", "image/Link/하트-빈것(78.72).bmp", 78, 72, TRUE, RGB(255, 0, 255));
		_hp[i].hpImg[LINK_HP_ONE_FOURTH] = IMAGEMANAGER->addImage("하트-사분의일(78.72)", "image/Link/하트-사분의일(78.72).bmp", 78, 72, TRUE, RGB(255, 0, 255));
		_hp[i].hpImg[LINK_HP_TWO_FOURTH] = IMAGEMANAGER->addImage("하트-사분의이(78.72)", "image/Link/하트-사분의이(78.72).bmp", 78, 72, TRUE, RGB(255, 0, 255));
		_hp[i].hpImg[LINK_HP_THREE_FOURTH] = IMAGEMANAGER->addImage("하트-사분의삼(78.72)", "image/Link/하트-사분의삼(78.72).bmp", 78, 72, TRUE, RGB(255, 0, 255));
		_hp[i].hpImg[LINK_HP_MAX] = IMAGEMANAGER->addImage("하트-풀(78.72)", "image/Link/하트-풀(78.72).bmp", 78, 72, TRUE, RGB(255, 0, 255));
		_hp[i].hpKind = LINK_HP_MAX;
	}
}

void player::drawHpImage()
{

	for (int i = 0; i <= _curHeart; i++)
	{
		_hp[i].hpImg[_hp[i].hpKind]->render(getMemDC(), 50 + i * 78, 20);
	}
	//controlHeart();
}

void player::controlHeart()
{
	if (_hp[_curHeart].hpKind >= 4)
	{
		if (_curHeart < 4)
		{
			_curHeart++;
		}
	}
	else
	{
		_hp[_curHeart].hpKind = (LINK_HP_KIND)(_hp[_curHeart].hpKind + 1);
	}
}

void player::decreaseHeart()
{
	if (_hurt) return;
	_hurt = true;

	if (_hp[_curHeart].hpKind <= 0)
	{
		_curHeart--;
	}
	else
	{
		_hp[_curHeart].hpKind = (LINK_HP_KIND)(_hp[_curHeart].hpKind - 1);
	}
}
