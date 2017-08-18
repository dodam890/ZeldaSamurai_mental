#include "stdafx.h"
#include "npc.h"
#include "camera.h"
#include "player.h"

npc::npc()
{
}

npc::~npc()
{
}

HRESULT npc::init(camera* camera, string npcName, DIRECTION direction, float drawX, float drawY, int widthRange, int heightRange)
{
	_camera = camera;

	for (int i = 0; i < DIRECTION_END; i++)
	{
		_npc[i].currentFrameX = 0;
		_npc[i].count = 0;
	}

	_moveCount = 0;
	_stopCount = 0;

	_distanceX = drawX;
	_distanceY = drawY;

	_drawX = drawX;
	_drawY = drawY;

	_centerX = _camera->getStartX() + _distanceX;
	_centerY = _camera->getStartY() + _distanceY;

	_moveCenterX = _camera->getStartX() + _drawX;
	_moveCenterY = _camera->getStartY() + _drawY;

	_direction = direction;

	_widthRange = widthRange;
	_heightRange = heightRange;

	_moveRc = RectMakeCenter(_moveCenterX, _moveCenterY, _widthRange, _heightRange);
	_rc = RectMake(_centerX, _centerY, NPCWIDTH, NPCHEIGHT);

	if (npcName == "npcUncle")
	{
		setImages("npcUncleDown", "npcUncleLeft", "npcUncleRight", "npcUncleUp");
	}
	else if (npcName == "npcBand")
	{
		setImages("npcBandDown", "npcBandLeft", "npcBandRight", "npcBandUp");
	}
	else if (npcName == "npcBrown")
	{
		setImages("npcBrownDown", "npcBrownLeft", "npcBrownRight", "npcBrownUp");
	}
	else if (npcName == "npcElf")
	{
		setImages("npcElfDown", "npcElfLeft", "npcElfRight", "npcElfUp");
	}
	else if (npcName == "npcGold")
	{
		setImages("npcGoldDown", "npcGoldLeft", "npcGoldRight", "npcGoldUp");
	}
	else if (npcName == "npcGrandFa")
	{
		setImages("npcGrandFaDown", "npcGrandFaLeft", "npcGrandFaRight", "npcGrandFaUp");
	}
	else if (npcName == "npcGrandMa")
	{
		setImages("npcGrandMaDown", "npcGrandMaLeft", "npcGrandMaRight", "npcGrandMaUp");
	}
	else if (npcName == "npcGuardLeft")
	{
		setImages("npcGuardDown", "npcGuardLeft", "npcGuardRight", "npcGuardUp");
		_moveRc = RectMakeCenter(_moveCenterX + 180, _moveCenterY, _widthRange, _heightRange);
	}
	else if (npcName == "npcGuardRight")
	{
		setImages("npcGuardDown", "npcGuardLeft", "npcGuardRight", "npcGuardUp");
		_moveRc = RectMakeCenter(_moveCenterX - 100, _moveCenterY, _widthRange, _heightRange);
	}
	else if (npcName == "npcGuardTop")
	{
		setImages("npcGuardDown", "npcGuardLeft", "npcGuardRight", "npcGuardUp");
		_moveRc = RectMakeCenter(_moveCenterX, _moveCenterY + 300, _widthRange, _heightRange);
	}
	else if (npcName == "npcShop")
	{
		setImages("npcShopDown", "npcShopDown", "npcShopDown", "npcShopTalk");
		_moveRc = RectMakeCenter(_moveCenterX + 70, _moveCenterY + 100, _widthRange, _heightRange);
	}
	else if (npcName == "npcLink")
	{
		setImages("npcLinkDown", "npcLinkDown", "npcLinkDown", "npcLinkTalk");
		_moveRc = RectMakeCenter(_moveCenterX + 70, _moveCenterY + 100, _widthRange, _heightRange);
	}
	else if (npcName == "npcMaster")
	{
		setImages("npcMasterDown", "npcMasterDown", "npcMasterDown", "npcMasterTalk");
		_moveRc = RectMakeCenter(_moveCenterX + 35, _moveCenterY + 70, _widthRange, _heightRange);
	}
	setMapWords(npcName);

	return S_OK;
}

void npc::release()
{
}

void npc::update(string npcSort)
{
	_centerX = _camera->getStartX() + _distanceX;
	_centerY = _camera->getStartY() + _distanceY;

	_moveCenterX = _camera->getStartX() + _drawX;
	_moveCenterY = _camera->getStartY() + _drawY;

	_rc = RectMake(_centerX, _centerY, NPCWIDTH, NPCHEIGHT);

	if (npcSort == "normal")
	{
		_moveRc = RectMakeCenter(_moveCenterX, _moveCenterY, _widthRange, _heightRange);

		_moveCount += TIMEMANAGER->getElapsedTime() * 100;

		if (_moveCount > 100.f)
		{
			changeDirection(npcSort);
			_moveCount = 0.f;
		}

		addFrame(npcSort, _direction, 20);
	}

	if (npcSort == "guardLeft")
		_moveRc = RectMakeCenter((int)_moveCenterX + 100, (int)_moveCenterY + 50, _widthRange, _heightRange);
	if (npcSort == "guardRight")
		_moveRc = RectMakeCenter((int)_moveCenterX - 100, (int)_moveCenterY + 50, _widthRange, _heightRange);
	if (npcSort == "guardTop")
		_moveRc = RectMakeCenter((int)_moveCenterX, (int)_moveCenterY + 200, _widthRange, _heightRange);

	else if (npcSort == "npcShop")
	{
		addFrame(npcSort, _direction, 10);
		_moveRc = RectMakeCenter((int)_moveCenterX + 70, (int)_moveCenterY + 150, _widthRange, _heightRange);
	}
	else if (npcSort == "npcLink")
	{
		addFrame(npcSort, _direction, 10);
		_moveRc = RectMakeCenter((int)_moveCenterX, (int)_moveCenterY + 150, _widthRange, _heightRange);
	}
	else if (npcSort == "npcMaster")
	{
		addFrame(npcSort, _direction, 10);
		_moveRc = RectMakeCenter((int)_moveCenterX + 35, (int)_moveCenterY + 150, _widthRange, _heightRange);
	}

	npcMove(npcSort);

	talkOn();
}

void npc::render()
{
	//Rectangle(getMemDC(), _moveRc.left, _moveRc.top, _moveRc.right, _moveRc.bottom);
	Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
	_npc[_direction].image->frameRender(getMemDC(), _rc.left, _rc.top, _npc[_direction].currentFrameX, 0);

	TextOut(getMemDC(), _moveRc.left, _moveRc.top, "무브렉트", strlen("무브렉트"));

	/*if(_talkOn)
		drawTextBox();*/
}

void npc::setImages(string imageKeyNameDown, string imageKeyNameLeft, string imageKeyNameRight, string imageKeyNameUp)
{
	_npc[DIRECTION_DOWN].image = IMAGEMANAGER->findImage(imageKeyNameDown);
	_npc[DIRECTION_LEFT].image = IMAGEMANAGER->findImage(imageKeyNameLeft);
	_npc[DIRECTION_RIGHT].image = IMAGEMANAGER->findImage(imageKeyNameRight);
	_npc[DIRECTION_UP].image = IMAGEMANAGER->findImage(imageKeyNameUp);
}

void npc::addFrame(string npcSort, DIRECTION direction, int frameSpeed)
{
	if (npcSort == "normal")
	{
		_npc[direction].count++;

		if (_npc[direction].count % frameSpeed == 0)
		{
			if (_npc[direction].currentFrameX >= _npc[direction].image->getMaxFrameX()) _npc[direction].currentFrameX = 0;
			else _npc[direction].currentFrameX++;

			_npc[direction].count = 0;
		}
	}

	else if (npcSort == "guardLeft" || npcSort == "guardRight" || npcSort == "guardTop")
	{
		_npc[direction].count++;

		if (_npc[direction].count % frameSpeed == 0)
		{
			if (_npc[direction].currentFrameX >= _npc[direction].image->getMaxFrameX()) _npc[direction].currentFrameX = 0;
			else _npc[direction].currentFrameX++;

			_npc[direction].count = 0;
		}
	}

	else if (npcSort == "npcShop")
	{
		_npc[direction].count++;

		if (_npc[direction].count % frameSpeed == 0)
		{
			if (_npc[direction].currentFrameX >= _npc[direction].image->getMaxFrameX()) _npc[direction].currentFrameX = 0;
			else if (_npc[DIRECTION_DOWN].currentFrameX == 3)
			{
				_stopCount++;
				if (_stopCount >= 10)
				{
					_npc[DIRECTION_DOWN].currentFrameX = 4;
					_stopCount = 0;
				}
			}
			else _npc[direction].currentFrameX++;

			_npc[direction].count = 0;
		}
	}

	else if (npcSort == "npcLink")
	{
		_npc[direction].count++;

		if (_npc[direction].count % frameSpeed == 0)
		{
			if (_npc[direction].currentFrameX >= _npc[direction].image->getMaxFrameX())
			{
				if (direction != DIRECTION_UP)
				{
					_npc[direction].currentFrameX = 0;
					_npc[DIRECTION_UP].currentFrameX = 0;
				}
				else _npc[direction].currentFrameX = _npc[direction].image->getMaxFrameX();
			}

			else _npc[direction].currentFrameX++;

			_npc[direction].count = 0;
		}
	}

	else if (npcSort == "npcMaster")
	{
		_npc[direction].count++;

		if (_npc[direction].count % frameSpeed == 0)
		{
			if (_npc[direction].currentFrameX >= _npc[direction].image->getMaxFrameX())
			{
				_npc[direction].currentFrameX = _npc[direction].image->getMaxFrameX();
			}

			else
			{
				if(direction == DIRECTION_UP)
					_npc[direction].currentFrameX++;
				else _npc[DIRECTION_UP].currentFrameX = 0;
			}

			_npc[direction].count = 0;
		}
	}
}

void npc::changeDirection(string npcSort)
{
	if (npcSort == "normal")
	{
		int rndNum = RND->getFromIntTo(0, 3);
		_direction = (DIRECTION)rndNum;
	}
}

void npc::npcMove(string npcSort)
{
	if (npcSort == "normal")
	{
		if (_talkOn)
		{
			if (_player->getMotion() == player::LINK_MOTION::LINK_MOTION_DOWN || _player->getMotion() == player::LINK_MOTION::LINK_MOTION_DOWN_WALK)
				_direction = DIRECTION_UP;
			if (_player->getMotion() == player::LINK_MOTION::LINK_MOTION_RIGHT || _player->getMotion() == player::LINK_MOTION::LINK_MOTION_RIGHT_WALK)
				_direction = DIRECTION_LEFT;
			if (_player->getMotion() == player::LINK_MOTION::LINK_MOTION_LEFT || _player->getMotion() == player::LINK_MOTION::LINK_MOTION_LEFT_WALK)
				_direction = DIRECTION_RIGHT;
			if (_player->getMotion() == player::LINK_MOTION::LINK_MOTION_UP || _player->getMotion() == player::LINK_MOTION::LINK_MOTION_UP_WALK)
				_direction = DIRECTION_DOWN;
		}
		else
		{
			switch (_direction)
			{
			case DIRECTION_DOWN:
				if (_rc.bottom < _moveRc.bottom)
					_distanceY++;
				break;
			case DIRECTION_LEFT:
				if (_rc.left > _moveRc.left)
					_distanceX--;
				break;
			case DIRECTION_RIGHT:
				if (_rc.right < _moveRc.right)
					_distanceX++;
				break;
			case DIRECTION_UP:
				if (_rc.top > _moveRc.top)
					_distanceY--;
				break;
			}
		}
	}

	else if (npcSort == "guardLeft")
	{
		RECT temp;
		if (IntersectRect(&temp, &_moveRc, &_player->getRect()))
		{
			addFrame(npcSort, _direction, 20);
			_rc.top = _player->getRect().top - 70;
			_rc.bottom = _player->getRect().bottom;
			if (_rc.top <= _moveRc.top)
			{
				_rc.top = _moveRc.top;
				_rc.bottom = _rc.top + NPCHEIGHT;
			}
			if (_rc.bottom >= _moveRc.bottom)
			{
				_rc.bottom = _moveRc.bottom;
				_rc.top = _rc.bottom - NPCHEIGHT;
			}

			if (_player->getMotion() == player::LINK_MOTION::LINK_MOTION_UP_WALK) _direction = DIRECTION_UP;
			else if (_player->getMotion() == player::LINK_MOTION::LINK_MOTION_DOWN_WALK) _direction = DIRECTION_DOWN;
			else  _direction = DIRECTION_RIGHT;
		}
		else
		{
			_direction = DIRECTION_RIGHT;
		}
	}

	else if (npcSort == "guardRight")
	{
		RECT sour;
		if (IntersectRect(&sour, &_moveRc, &_player->getRect()))
		{
			addFrame(npcSort, _direction, 20);
			_rc.top = _player->getRect().top - 70;
			_rc.bottom = _player->getRect().bottom;
			if (_rc.top <= _moveRc.top)
			{
				_rc.top = _moveRc.top;
				_rc.bottom = _rc.top + NPCHEIGHT;
			}
			if (_rc.bottom >= _moveRc.bottom)
			{
				_rc.bottom = _moveRc.bottom;
				_rc.top = _rc.bottom - NPCHEIGHT;
			}
			if (_player->getMotion() == player::LINK_MOTION::LINK_MOTION_UP_WALK) _direction = DIRECTION_UP;
			else if (_player->getMotion() == player::LINK_MOTION::LINK_MOTION_DOWN_WALK) _direction = DIRECTION_DOWN;
			else _direction = DIRECTION_LEFT;
		}
		else
		{
			_direction = DIRECTION_LEFT;
		}
	}

	else if (npcSort == "guardTop")
	{
		RECT dest;
		if (IntersectRect(&dest, &_moveRc, &_player->getRect()))
		{
			addFrame(npcSort, _direction, 20);
			_rc.left = _player->getRect().left;
			_rc.right = _player->getRect().right;
			if (_rc.left <= _moveRc.left)
			{
				_rc.left = _moveRc.left;
				_rc.right = _rc.left + NPCWIDTH;
			}
			if (_rc.right >= _moveRc.right)
			{
				_rc.right = _moveRc.right;
				_rc.left = _rc.right - NPCWIDTH;
			}
			if (_player->getMotion() == player::LINK_MOTION::LINK_MOTION_RIGHT_WALK) _direction = DIRECTION_RIGHT;
			else if (_player->getMotion() == player::LINK_MOTION::LINK_MOTION_LEFT_WALK) _direction = DIRECTION_LEFT;
			else _direction = DIRECTION_DOWN;
		}
		else
		{
			_direction = DIRECTION_DOWN;
		}
	}

	else if (npcSort == "npcShop" || npcSort == "npcLink" || npcSort == "npcMaster")
	{
		RECT talk;
		if (IntersectRect(&talk, &_moveRc, &_player->getRect()))
		{
			if (_talkOn)
			{
				_direction = DIRECTION_UP;
			}
			else _direction = DIRECTION_DOWN;
		}
	}
}

void npc::setMapWords(string npcName)
{
	if (npcName == "npcUncle")
	{
		char words[1000] = "양/쌤/:/ /원/영/아/!/ /포/폴/은/ /안/하/고/ /여/기/서/ /뭐/하/는/거/냐/?!";
		char* token;
		char* separator = "/";

		token = strtok(words, separator);
		_vWords.push_back(token);

		while (NULL != (token = strtok(NULL, separator)))
		{
			_vWords.push_back(token);
		}
	}

	else if (npcName == "npcBand")
	{
		char words[1000] = "대/일/:/ /풍/성/한/ /머/리/숱/의/ /비/결/이/ /궁/금/해/?";
		char* token;
		char* separator = "/";

		token = strtok(words, separator);
		_vWords.push_back(token);

		while (NULL != (token = strtok(NULL, separator)))
		{
			_vWords.push_back(token);
		}
	}

	else if (npcName == "npcBrown")
	{
		char words[1000] = "도/담/:/ /형/!/!/!/ /뭐/해/요/!/!/!/ /악/!/!/!";
		char* token;
		char* separator = "/";

		token = strtok(words, separator);
		_vWords.push_back(token);

		while (NULL != (token = strtok(NULL, separator)))
		{
			_vWords.push_back(token);
		}
	}

	else if (npcName == "npcElf")
	{
		char words[1000] = "범/수/:/ /././네";
		char* token;
		char* separator = "/";

		token = strtok(words, separator);
		_vWords.push_back(token);

		while (NULL != (token = strtok(NULL, separator)))
		{
			_vWords.push_back(token);
		}
	}

	else if (npcName == "npcGold")
	{
		char words[1000] = "예/솔/:/ /원/영/오/빠/ /이/리/와/봐/요/ /--";
		char* token;
		char* separator = "/";

		token = strtok(words, separator);
		_vWords.push_back(token);

		while (NULL != (token = strtok(NULL, separator)))
		{
			_vWords.push_back(token);
		}
	}

	else if (npcName == "npcGrandFa")
	{
		char words[1000] = "촌/장/:/ /어/서/ /가/서/ /엘/리/먼/트/를/ /찾/아/오/게/!";
		char* token;
		char* separator = "/";

		token = strtok(words, separator);
		_vWords.push_back(token);

		while (NULL != (token = strtok(NULL, separator)))
		{
			_vWords.push_back(token);
		}
	}

	else if (npcName == "npcGrandMa")
	{
		char words[1000] = "할/머/니/:/ /우/리/ /똥/깡/아/지/ /원/영/이/로/구/나/~";
		char* token;
		char* separator = "/";

		token = strtok(words, separator);
		_vWords.push_back(token);

		while (NULL != (token = strtok(NULL, separator)))
		{
			_vWords.push_back(token);
		}
	}

	else if (npcName == "npcGuardLeft")
	{
		char words[1000] = "병/사/:/ /안/됩/니/다/.";
		char* token;
		char* separator = "/";

		token = strtok(words, separator);
		_vWords.push_back(token);

		while (NULL != (token = strtok(NULL, separator)))
		{
			_vWords.push_back(token);
		}
	}

	else if (npcName == "npcGuardRight")
	{
		char words[1000] = "병/사/:/ /안/됩/니/다.";
		char* token;
		char* separator = "/";

		token = strtok(words, separator);
		_vWords.push_back(token);

		while (NULL != (token = strtok(NULL, separator)))
		{
			_vWords.push_back(token);
		}
	}

	else if (npcName == "npcGuardTop")
	{
		char words[1000] = "병/사/:/ /안/됩/니/다.";
		char* token;
		char* separator = "/";

		token = strtok(words, separator);
		_vWords.push_back(token);

		while (NULL != (token = strtok(NULL, separator)))
		{
			_vWords.push_back(token);
		}
	}

	else if (npcName == "npcShop")
	{
		char words[1000] = "그/ /물/건/을/ /구/입/하/시/겠/습/니/까/?";
		char* token;
		char* separator = "/";

		token = strtok(words, separator);
		_vWords.push_back(token);

		while (NULL != (token = strtok(NULL, separator)))
		{
			_vWords.push_back(token);
		}
	}

	else if (npcName == "npcLink")
	{
		char words[1000] = "검/을/ /업/그/레/이/드/하/겠/나/?";
		char* token;
		char* separator = "/";

		token = strtok(words, separator);
		_vWords.push_back(token);

		while (NULL != (token = strtok(NULL, separator)))
		{
			_vWords.push_back(token);
		}
	}

	else if (npcName == "npcMaster")
	{
		char words[1000] = "회/전/베/기/를/ /배/우/겠/느/냐/?!";
		char* token;
		char* separator = "/";

		token = strtok(words, separator);
		_vWords.push_back(token);

		while (NULL != (token = strtok(NULL, separator)))
		{
			_vWords.push_back(token);
		}
	}

	_talkOn = false;
	_index = 0;
}

void npc::talkOn()
{
	if (_talkOn)
	{
		_count++;

		if (_count % 5 == 0)
		{
			if (_index < _vWords.size())
			{
				_vTextOut.push_back(_vWords[_index]);
				_index++;
				_count = 0;
			}
		}
	}
	else
	{
		_talkOn = false;
		_index = 0;
		_vTextOut.clear();
	}
}

void npc::drawTextBox()
{
	image* img = IMAGEMANAGER->findImage("textBox");
	img->setX(15);
	img->setY(WINSIZEY - (img->getHeight() + 50));
	img->render(getMemDC(), img->getX(), img->getY());

	HFONT font = CreateFont(40, 0, 0, 0, FW_NORMAL, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH, "배달의민족 도현");
	SelectObject(getMemDC(), font);
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	SetBkColor(getMemDC(), RGB(0, 0, 0));

	for (int i = 0; i < _vTextOut.size(); i++)
	{
		const char* str;
		str = _vTextOut[i].c_str();
		//if(i < 13)
			TextOut(getMemDC(), img->getX() + 50 + (40 * i), img->getY() + 50, str, strlen(str));
		//else
		//	TextOut(getMemDC(), img->getX() + 50 + (50 * (i - 10)), img->getY() + 100, str, strlen(str));
	}

	DeleteObject(font);
}
