#include "stdafx.h"
#include "animationTest.h"


animationTest::animationTest()
{
}


animationTest::~animationTest()
{
}

HRESULT animationTest::init()
{
	_camel = IMAGEMANAGER->addImage("camel", "camel.bmp", 300, 267, true, RGB(255, 0, 255));

	//디폴트 애니메이션
	_ani1 = new animation;
	_ani1->init(_camel->getWidth(), _camel->getHeight(), 75, 89);
	_ani1->setDefPlayFrame(true, true);
	_ani1->setFPS(1);

	//구간반복
	_ani2 = new animation;
	_ani2->init(_camel->getWidth(), _camel->getHeight(), 75, 89);
	_ani2->setPlayFrame(4, 9, false, true);
	_ani2->setFPS(1);


	int arrAni[] = { 0, 2, 4, 6, 8, 10 };
	_ani3 = new animation;
	_ani3->init(_camel->getWidth(), _camel->getHeight(), 75, 89);
	_ani3->setPlayFrame(arrAni, 6, false);
	_ani3->setFPS(1);

	return S_OK;
}

void animationTest::release()
{
}

void animationTest::update()
{
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		_ani1->start();
	}
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		_ani2->start();
	}
	if (KEYMANAGER->isStayKeyDown('E'))
	{
		_ani3->start();
	}

	_ani1->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
	_ani2->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
	_ani3->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);

}

void animationTest::render()
{
	_camel->aniRender(getMemDC(), 100, 200, _ani1);

	_camel->aniRender(getMemDC(), 300, 200, _ani2);

	_camel->aniRender(getMemDC(), 500, 200, _ani3);

}
