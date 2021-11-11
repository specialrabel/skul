#include "stdafx.h"
#include "effectTest.h"


effectTest::effectTest()
{
}


effectTest::~effectTest()
{
}

HRESULT effectTest::init()
{
	IMAGEMANAGER->addImage("explosion", "explosion.bmp", 832, 62, true, RGB(255, 0, 255));

	_effectSample = new effect;
	_effectSample->init(IMAGEMANAGER->findImage("explosion"), 32, 62, 1, 1.0f);

	EFFECTMANAGER->addEffect("explostion2", "explosion.bmp", 832, 62, 32, 62, 1, 0.5f, 2000);

	return S_OK;
}

void effectTest::release()
{

}

void effectTest::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		_effectSample->startEffect(_ptMouse.x, _ptMouse.y);
	}

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		EFFECTMANAGER->play("explostion2", _ptMouse.x, _ptMouse.y);
	}

	EFFECTMANAGER->play("explostion2", RND->getFromIntTo(200, 400), RND->getFromIntTo(200, 400));


	_effectSample->update();
	EFFECTMANAGER->update();
}

void effectTest::render()
{
	_effectSample->render();
	EFFECTMANAGER->render();
}
