#include "stdafx.h"
#include "player.h"
#include "camera.h"

player::player() {}
player::~player() {}

HRESULT player::init(camera* camera)
{
	loadImage();
	L_Motion = LINK_MOTION_DOWN;

	_currentFrameX = _currentFrameY = 0;
	_count = 0;

	_cam = camera;
	_angle = PI;
	_moveSpeed = 5;
	_move = true;
	_isStore = false;

	_probeX = _probeY = 0;

	_disX = WINSIZEX / 2 - 135;
	_disY = WINSIZEY / 2 + 100;

	_X = _cam->getStartX() + _disX;
	_Y = _cam->getStartY() + _disY;

	_playerRc = RectMake(_X + 100, _Y + 110, 70, 70);

	_isCollision = 0;

	return S_OK;
}

void player::release(void) {}

void player::update(void)
{
	if (_move)
	{
		motionChange();
		move();
	}

	_X = _cam->getStartX() + _disX;
	_Y = _cam->getStartY() + _disY;
	_playerRc = RectMake(_X + 100, _Y + 110, 70, 70);

	frameCount();
}

void player::render(void)
{
	draw();
}

void player::draw(void)
{
	char str[128] = "";

	sprintf(str, "[_probeX : %d _probeY : %d]", _probeX, _probeY);
	TextOut(getMemDC(), 400, 30, str, strlen(str));
	sprintf_s(str, "[player _X : %1.f, player _Y : %1.f]", _X, _Y);
	TextOut(getMemDC(), 400, 50, str, strlen(str));
	sprintf_s(str, "[disX : %1.f, disY : %1.f]", _disX, _disY);
	TextOut(getMemDC(), 400, 70, str, strlen(str));

	sprintf(str, "[frameX : %d]", _currentFrameX);
	TextOut(getMemDC(), 400, 90, str, strlen(str));

	switch (L_Motion)
	{
	case player::LINK_MOTION_RIGHT:
		TextOut(getMemDC(), 500, 10, "�����ʱ⺻", strlen("�����ʱ⺻"));
		break;
	case player::LINK_MOTION_LEFT:
		TextOut(getMemDC(), 500, 10, "���ʱ⺻", strlen("���ʱ⺻"));
		break;
	case player::LINK_MOTION_UP:
		TextOut(getMemDC(), 500, 10, "���ʱ⺻", strlen("���ʱ⺻"));
		break;
	case player::LINK_MOTION_DOWN:
		TextOut(getMemDC(), 500, 10, "�Ʒ��ʱ⺻", strlen("�Ʒ��ʱ⺻"));
		break;
	case player::LINK_MOTION_RIGHT_WALK:
		TextOut(getMemDC(), 500, 10, "�����ʰȱ�", strlen("�����ʰȱ�"));
		break;
	case player::LINK_MOTION_LEFT_WALK:
		TextOut(getMemDC(), 500, 10, "���ʰȱ�", strlen("���ʰȱ�"));
		break;
	case player::LINK_MOTION_UP_WALK:
		TextOut(getMemDC(), 500, 10, "���ʰȱ�", strlen("���ʰȱ�"));
		break;
	case player::LINK_MOTION_DOWN_WALK:
		TextOut(getMemDC(), 500, 10, "�Ʒ��ʰȱ�", strlen("�Ʒ��ʰȱ�"));
		break;
	case player::LINK_MOTION_RIGHT_TUMBLE:
		TextOut(getMemDC(), 500, 10, "�����ʱ�����", strlen("�����ʱ�����"));
		break;
	case player::LINK_MOTION_LEFT_TUMBLE:
		TextOut(getMemDC(), 500, 10, "���ʱ�����", strlen("���ʱ�����"));
		break;
	case player::LINK_MOTION_UP_TUMBLE:
		TextOut(getMemDC(), 500, 10, "���ʱ�����", strlen("���ʱ�����"));
		break;
	case player::LINK_MOTION_DOWN_TUMBLE:
		TextOut(getMemDC(), 500, 10, "�Ʒ��ʱ�����", strlen("�Ʒ��ʱ�����"));
		break;
	case player::LINK_MOTION_RIGHT_GRAB:
		TextOut(getMemDC(), 500, 10, "���������", strlen("���������"));
		break;
	case player::LINK_MOTION_LEFT_GRAB:
		TextOut(getMemDC(), 500, 10, "�������", strlen("�������"));
		break;
	case player::LINK_MOTION_UP_GRAB:
		TextOut(getMemDC(), 500, 10, "�������", strlen("�������"));
		break;
	case player::LINK_MOTION_DOWN_GRAB:
		TextOut(getMemDC(), 500, 10, "�Ʒ������", strlen("�Ʒ������"));
		break;
	case player::LINK_MOTION_RIGHT_PUSH:
		TextOut(getMemDC(), 500, 10, "�����ʹб�", strlen("�����ʹб�"));
		break;
	case player::LINK_MOTION_LEFT_PUSH:
		TextOut(getMemDC(), 500, 10, "���ʹб�", strlen("���ʹб�"));
		break;
	case player::LINK_MOTION_UP_PUSH:
		TextOut(getMemDC(), 500, 10, "���ʹб�", strlen("���ʹб�"));
		break;
	case player::LINK_MOTION_DOWN_PUSH:
		TextOut(getMemDC(), 500, 10, "�Ʒ��ʹб�", strlen("�Ʒ��ʹб�"));
		break;
	case player::LINK_MOTION_RIGHT_SWORD_ATTACK:
		TextOut(getMemDC(), 500, 10, "������Į����", strlen("������Į����"));
		break;
	case player::LINK_MOTION_LEFT_SWORD_ATTACK:
		TextOut(getMemDC(), 500, 10, "����Į����", strlen("����Į����"));
		break;
	case player::LINK_MOTION_UP_SWORD_ATTACK:
		TextOut(getMemDC(), 500, 10, "����Į����", strlen("����Į����"));
		break;
	case player::LINK_MOTION_DOWN_SWORD_ATTACK:
		TextOut(getMemDC(), 500, 10, "�Ʒ���Į����", strlen("�Ʒ���Į����"));
		break;
	case player::LINK_MOTION_RIGHT_SHIELD_OPEN:
		TextOut(getMemDC(), 500, 10, "�����ʽ��岨����", strlen("�����ʽ��岨����"));
		break;
	case player::LINK_MOTION_LEFT_SHIELD_OPEN:
		TextOut(getMemDC(), 500, 10, "���ʽ��岨����", strlen("���ʽ��岨����"));
		break;
	case player::LINK_MOTION_UP_SHIELD_OPEN:
		TextOut(getMemDC(), 500, 10, "���ʽ��岨����", strlen("���ʽ��岨����"));
		break;
	case player::LINK_MOTION_DOWN_SHIELD_OPEN:
		TextOut(getMemDC(), 500, 10, "�Ʒ��ʽ��岨����", strlen("�Ʒ��ʽ��岨����"));
		break;
	case player::LINK_MOTION_RIGHT_SHIELD_STAND:
		TextOut(getMemDC(), 500, 10, "�����ʽ���⺻", strlen("�����ʽ���⺻"));
		break;
	case player::LINK_MOTION_LEFT_SHIELD_STAND:
		TextOut(getMemDC(), 500, 10, "���ʽ���⺻", strlen("���ʽ���⺻"));
		break;
	case player::LINK_MOTION_UP_SHIELD_STAND:
		TextOut(getMemDC(), 500, 10, "���ʽ���⺻", strlen("���ʽ���⺻"));
		break;
	case player::LINK_MOTION_DOWN_SHIELD_STAND:
		TextOut(getMemDC(), 500, 10, "�Ʒ��ʽ���⺻", strlen("�Ʒ��ʽ���⺻"));
		break;
	case player::LINK_MOTION_RIGHT_SHIELD_MOVE:
		TextOut(getMemDC(), 500, 10, "�����ʽ��幫��", strlen("�����ʽ��幫��"));
		break;
	case player::LINK_MOTION_LEFT_SHIELD_MOVE:
		TextOut(getMemDC(), 500, 10, "���ʽ��幫��", strlen("���ʽ��幫��"));
		break;
	case player::LINK_MOTION_UP_SHIELD_MOVE:
		TextOut(getMemDC(), 500, 10, "���ʽ��幫��", strlen("���ʽ��幫��"));
		break;
	case player::LINK_MOTION_DOWN_SHIELD_MOVE:
		TextOut(getMemDC(), 500, 10, "�Ʒ��ʽ��幫��", strlen("�Ʒ��ʽ��幫��"));
		break;
	case player::LINK_MOTION_RIGHT_MAGICPOT_ABSORB:
		TextOut(getMemDC(), 500, 10, "�������׾Ƹ����", strlen("�������׾Ƹ����"));
		break;
	case player::LINK_MOTION_LEFT_MAGICPOT_ABSORB:
		TextOut(getMemDC(), 500, 10, "�����׾Ƹ����", strlen("�����׾Ƹ����"));
		break;
	case player::LINK_MOTION_UP_MAGICPOT_ABSORB:
		TextOut(getMemDC(), 500, 10, "�����׾Ƹ����", strlen("�����׾Ƹ����"));
		break;
	case player::LINK_MOTION_DOWN_MAGICPOT_ABSORB:
		TextOut(getMemDC(), 500, 10, "�Ʒ����׾Ƹ����", strlen("�Ʒ����׾Ƹ����"));
		break;
	case player::LINK_MOTION_RIGHT_MAGICPOT_FIRE:
		TextOut(getMemDC(), 500, 10, "�������׾Ƹ��߽�", strlen("�������׾Ƹ��߽�"));
		break;
	case player::LINK_MOTION_LEFT_MAGICPOT_FIRE:
		TextOut(getMemDC(), 500, 10, "�����׾Ƹ��߽�", strlen("�����׾Ƹ��߽�"));
		break;
	case player::LINK_MOTION_UP_MAGICPOT_FIRE:
		TextOut(getMemDC(), 500, 10, "�����׾Ƹ��߽�", strlen("�����׾Ƹ��߽�"));
		break;
	case player::LINK_MOTION_DOWN_MAGICPOT_FIRE:
		TextOut(getMemDC(), 500, 10, "�Ʒ����׾Ƹ��߽�", strlen("�Ʒ����׾Ƹ��߽�"));
		break;
	case player::LINK_MOTION_RIGHT_ROLLING_ATTACK:
		TextOut(getMemDC(), 500, 10, "�����ʷѸ����", strlen("�����ʷѸ����"));
		break;
	case player::LINK_MOTION_LEFT_ROLLING_ATTACK:
		TextOut(getMemDC(), 500, 10, "���ʷѸ����", strlen("���ʷѸ����"));
		break;
	case player::LINK_MOTION_UP_ROLLING_ATTACK:
		TextOut(getMemDC(), 500, 10, "���ʷѸ����", strlen("���ʷѸ����"));
		break;
	case player::LINK_MOTION_DOWN_ROLLING_ATTACK:
		TextOut(getMemDC(), 500, 10, "�Ʒ��ʷѸ����", strlen("�Ʒ��ʷѸ����"));
		break;
	}

	Rectangle(getMemDC(), _playerRc.left, _playerRc.top, _playerRc.right, _playerRc.bottom);
	_link[L_Motion]._linkImg->frameRender(getMemDC(), _X, _Y, _currentFrameX, 0);
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

			_currentFrameX = 0;
			L_Motion = LINK_MOTION_LEFT_WALK;
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

			_currentFrameX = 0;
			L_Motion = LINK_MOTION_RIGHT_SHIELD_MOVE;

			break;
		case player::LINK_MOTION_LEFT_SHIELD_STAND:
			
			_currentFrameX = 0;
			L_Motion = LINK_MOTION_LEFT_SHIELD_MOVE;
			
			break;
		case player::LINK_MOTION_UP_SHIELD_STAND:
			
			_currentFrameX = 0;
			L_Motion = LINK_MOTION_UP_SHIELD_MOVE;
			
			break;
		case player::LINK_MOTION_DOWN_SHIELD_STAND:
			
			_currentFrameX = 0;
			L_Motion = LINK_MOTION_DOWN_SHIELD_MOVE;
			
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
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		switch (L_Motion)
		{
		case player::LINK_MOTION_RIGHT:
		case player::LINK_MOTION_LEFT:
		case player::LINK_MOTION_UP:
		case player::LINK_MOTION_DOWN:

			_currentFrameX = 0;
			L_Motion = LINK_MOTION_RIGHT_WALK;

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
			
			_currentFrameX = 0;
			L_Motion = LINK_MOTION_RIGHT_SHIELD_MOVE;
			
			break;
		case player::LINK_MOTION_LEFT_SHIELD_STAND:
			
			_currentFrameX = 0;
			L_Motion = LINK_MOTION_LEFT_SHIELD_MOVE;
			
			break;
		case player::LINK_MOTION_UP_SHIELD_STAND:
			
			_currentFrameX = 0;
			L_Motion = LINK_MOTION_UP_SHIELD_MOVE;
			
			break;
		case player::LINK_MOTION_DOWN_SHIELD_STAND:
			
			_currentFrameX = 0;
			L_Motion = LINK_MOTION_DOWN_SHIELD_MOVE;
			
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
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		switch (L_Motion)
		{
		case player::LINK_MOTION_RIGHT:
		case player::LINK_MOTION_LEFT:
		case player::LINK_MOTION_UP:
		case player::LINK_MOTION_DOWN:

			_currentFrameX = 0;
			L_Motion = LINK_MOTION_UP_WALK;

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
			
			_currentFrameX = 0;
			L_Motion = LINK_MOTION_RIGHT_SHIELD_MOVE;
			
			break;
		case player::LINK_MOTION_LEFT_SHIELD_STAND:
			
			_currentFrameX = 0;
			L_Motion = LINK_MOTION_LEFT_SHIELD_MOVE;
			
			break;
		case player::LINK_MOTION_UP_SHIELD_STAND:
			
			_currentFrameX = 0;
			L_Motion = LINK_MOTION_UP_SHIELD_MOVE;
			
			break;
		case player::LINK_MOTION_DOWN_SHIELD_STAND:
			
			_currentFrameX = 0;
			L_Motion = LINK_MOTION_DOWN_SHIELD_MOVE;
			
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
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		switch (L_Motion)
		{
		case player::LINK_MOTION_RIGHT:
		case player::LINK_MOTION_LEFT:
		case player::LINK_MOTION_UP:
		case player::LINK_MOTION_DOWN:

			_currentFrameX = 0;
			L_Motion = LINK_MOTION_DOWN_WALK;

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
			
			_currentFrameX = 0;
			L_Motion = LINK_MOTION_RIGHT_SHIELD_MOVE;
			
			break;
		case player::LINK_MOTION_LEFT_SHIELD_STAND:
			
			_currentFrameX = 0;
			L_Motion = LINK_MOTION_LEFT_SHIELD_MOVE;
			
			break;
		case player::LINK_MOTION_UP_SHIELD_STAND:
			
			_currentFrameX = 0;
			L_Motion = LINK_MOTION_UP_SHIELD_MOVE;
			
			break;
		case player::LINK_MOTION_DOWN_SHIELD_STAND:
			
			_currentFrameX = 0;
			L_Motion = LINK_MOTION_DOWN_SHIELD_MOVE;
			
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
	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
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
	if (KEYMANAGER->isStayKeyDown('X'))
	{
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
	if (KEYMANAGER->isOnceKeyUp('X'))
	{
		switch (L_Motion)
		{
		case player::LINK_MOTION_RIGHT_SHIELD_STAND:
		case player::LINK_MOTION_RIGHT_SHIELD_MOVE:
		case player::LINK_MOTION_RIGHT_SHIELD_OPEN:

			_currentFrameX = 0;
			L_Motion = LINK_MOTION_RIGHT;

			break;
		case player::LINK_MOTION_LEFT_SHIELD_STAND:
		case player::LINK_MOTION_LEFT_SHIELD_MOVE:
		case player::LINK_MOTION_LEFT_SHIELD_OPEN:

			_currentFrameX = 0;
			L_Motion = LINK_MOTION_LEFT;

			break;
		case player::LINK_MOTION_UP_SHIELD_STAND:
		case player::LINK_MOTION_UP_SHIELD_MOVE:
		case player::LINK_MOTION_UP_SHIELD_OPEN:

			_currentFrameX = 0;
			L_Motion = LINK_MOTION_UP;

			break;
		case player::LINK_MOTION_DOWN_SHIELD_STAND:
		case player::LINK_MOTION_DOWN_SHIELD_MOVE:
		case player::LINK_MOTION_DOWN_SHIELD_OPEN:

			_currentFrameX = 0;
			L_Motion = LINK_MOTION_DOWN;

			break;
		}
	}
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
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
		}
	}
	if (KEYMANAGER->isOnceKeyUp('C'))
	{
		switch (L_Motion)
		{
		case player::LINK_MOTION_RIGHT_MAGICPOT_ABSORB:
			
			_currentFrameX = 0;
			L_Motion = LINK_MOTION_RIGHT_MAGICPOT_FIRE;

			break;
		case player::LINK_MOTION_LEFT_MAGICPOT_ABSORB:

			_currentFrameX = 0;
			L_Motion = LINK_MOTION_LEFT_MAGICPOT_FIRE;

			break;
		case player::LINK_MOTION_UP_MAGICPOT_ABSORB:

			_currentFrameX = 0;
			L_Motion = LINK_MOTION_UP_MAGICPOT_FIRE;

			break;
		case player::LINK_MOTION_DOWN_MAGICPOT_ABSORB:

			_currentFrameX = 0;
			L_Motion = LINK_MOTION_DOWN_MAGICPOT_FIRE;

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

		break;
	case player::LINK_MOTION_LEFT_WALK:

		_moveSpeed = 5;

		break;
	case player::LINK_MOTION_UP_WALK:

		_moveSpeed = 5;

		break;
	case player::LINK_MOTION_DOWN_WALK:

		_moveSpeed = 5;

		break;
	case player::LINK_MOTION_RIGHT_TUMBLE:

		_moveSpeed = 15;

		if (_cam->isCameraXEndSide())
		{
			if (_playerRc.right >= WINSIZEX / 2 + 35)
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
			if (_playerRc.left <= WINSIZEX / 2 - 35)
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
			if (_playerRc.top <= WINSIZEY / 2 - 35)
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
			if (_playerRc.bottom >= WINSIZEY / 2 + 35)
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
				_currentFrameX = 1;
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
	//������ �ȼ� �浹
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

	//���� �ȼ� �浹
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

	//���� �ȼ� �浹
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

	//�Ʒ��� �ȼ� �浹
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
					_disY = (float)j- 186;
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
	//if (!(r == 255 && g == 0 && b == 255))
	//{
	//	_moveSpeed = 0;
	//	_disX -= 1;
	//}

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