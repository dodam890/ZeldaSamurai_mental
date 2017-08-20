#include "stdafx.h"
#include "main_scene.h"


main_scene::main_scene()
{
}


main_scene::~main_scene()
{
}

HRESULT main_scene::init()
{
	carrentX = 0;
	count = 0;
	logo_Y = 1000;
	islogo = false;
	ready_to_push_button = false;
	ready_to_change = false;
	sub_logo_x = -800;
	alpha_num = 255;
	change_alpha = 0;
	SOUNDMANAGER->play("메인메뉴음악", 1.F);
	return S_OK;
}

void main_scene::release()
{
}

void main_scene::update()
{
	if (logo_Y >= 50)
	{
		logo_Y -= 2;
	}
	else
	{
		islogo = true;
	}


	if (islogo == true && sub_logo_x < 250)
	{
		sub_logo_x += 16;
	}
	else if (islogo == true && sub_logo_x >= 250)
	{
		ready_to_push_button = true;
	}

	count++;
	if (count % 12 == 0)
	{
		carrentX++;
		if (carrentX > IMAGEMANAGER->findImage("햇살")->getMaxFrameX()) carrentX = 0;
		count = 0;

		alpha_num -= 200;
		if (ready_to_change == false)
		{
			if (alpha_num <= 0) alpha_num = 255;
		}
	}

	// skip
	if (KEYMANAGER->isStayKeyDown(VK_SPACE))
	{
		if (islogo == false)
		{
			logo_Y -= 20;
		}
		else
		{
			if (sub_logo_x < 250)
			{
				sub_logo_x += 20;
			}
		}
	}

	//change another scene
	if (islogo == true && ready_to_push_button == true)
	{
		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			ready_to_change = true;
			SOUNDMANAGER->play("메뉴선택", 1.f);
			SOUNDMANAGER->stop("메인메뉴음악");
		}
	}

	if (ready_to_change == true)
	{
		if (change_alpha >= 255)
		{
			SCENEMANAGER->changeScene("select_scene");
		}
		else
		{
			change_alpha += 20;
		}
	}

}

void main_scene::render()
{
	IMAGEMANAGER->findImage("배경화면")->render(getMemDC(), 0, 0);

	IMAGEMANAGER->findImage("햇살")->alphaRender(getMemDC(), 0, 0, carrentX, 0, 180);

	IMAGEMANAGER->findImage("로고")->render(getMemDC(), 150, logo_Y);
	if (islogo == true)
	{
		IMAGEMANAGER->findImage("로고1")->render(getMemDC(), 440, logo_Y);
		IMAGEMANAGER->findImage("로고2")->render(getMemDC(), sub_logo_x, 90);

		IMAGEMANAGER->findImage("로고텍스트")->alphaRender(getMemDC(), 400, 620, alpha_num);
	}

	IMAGEMANAGER->findImage("하얀화면")->alphaRender(getMemDC(), 0, 0, change_alpha);
}
