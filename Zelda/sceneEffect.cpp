#include "stdafx.h"
#include "sceneEffect.h"


sceneEffect::sceneEffect() {}
sceneEffect::~sceneEffect() {}

HRESULT sceneEffect::init(void)
{
	_alphaValue = 0;

	_isChangeScene = true;
	_isFadeOUT = _isFadeIN = false;

	return S_OK;
}

void sceneEffect::release(void)
{

}

void sceneEffect::update(void)
{
	if (_isFadeIN) fadeIN();
	if (_isFadeOUT) fadeOUT();
}

void sceneEffect::render(void)
{
	IMAGEMANAGER->findImage("BLACK")->alphaRender(getMemDC(), 0, 0, _alphaValue);
}


void sceneEffect::fadeIN()
{
	_alphaValue -= 10;

	if (_alphaValue <= 0)
	{
		_alphaValue = 0;
		_isFadeIN = false;
	}
}

void sceneEffect::fadeOUT()
{
	_alphaValue += 10;

	if (_alphaValue >= 255)
	{
		_alphaValue = 255;
		_isFadeOUT = false;
		_isFadeIN = true;
		_isChangeScene = false;
	}
}