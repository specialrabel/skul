#include "stdafx.h"
#include "testScene2.h"


testScene2::testScene2()
{
}


testScene2::~testScene2()
{
}

HRESULT testScene2::init()
{
	IMAGEMANAGER->addImage("말", "말.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	return S_OK;
}

void testScene2::release()
{
}

void testScene2::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_F2)) SCENEMANAGER->changeScene("테스트씬1");
}

void testScene2::render()
{
	IMAGEMANAGER->findImage("말")->render(getMemDC());
}
