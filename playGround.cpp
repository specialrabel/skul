#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{
}

//초기화는 여기다 하세요 제발
HRESULT playGround::init()
{
	gameNode::init(true);

	SCENEMANAGER->addScene("시작화면", new start);
	SCENEMANAGER->addScene("마왕성", new stage1);
	SCENEMANAGER->addScene("던전입구", new stage2);
	SCENEMANAGER->addScene("미니언존1", new stage3);
	SCENEMANAGER->addScene("미니언존2-1", new stage4);
	SCENEMANAGER->addScene("미니언존2-2", new stage5);
	SCENEMANAGER->addScene("보스존1", new stage6);

	SCENEMANAGER->changeScene("시작화면");

	return S_OK;
}

//메모리 해제는 여기다 하세요 제발
void playGround::release()
{
	gameNode::release();

	SCENEMANAGER->release();
}


void playGround::update()
{
	gameNode::update();

	SCENEMANAGER->update();

	//작업용(마지막엔 지울것)
	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		SCENEMANAGER->changeScene("시작화면");
	}
	else if (KEYMANAGER->isOnceKeyDown('2'))
	{
		SCENEMANAGER->changeScene("마왕성");
	}
	else if (KEYMANAGER->isOnceKeyDown('3'))
	{
		SCENEMANAGER->changeScene("던전입구");
	}
	else if (KEYMANAGER->isOnceKeyDown('4'))
	{
		SCENEMANAGER->changeScene("미니언존1");
	}
	else if (KEYMANAGER->isOnceKeyDown('5'))
	{
		SCENEMANAGER->changeScene("미니언존2-1");
	}
	else if (KEYMANAGER->isOnceKeyDown('6'))
	{
		SCENEMANAGER->changeScene("미니언존2-2");
	}
	else if (KEYMANAGER->isOnceKeyDown('7'))
	{
		SCENEMANAGER->changeScene("보스존1");
	}
}


void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, 10000, 10000, BLACKNESS);
	// 위에 건들지마라
	//================제발 이 사이에 좀 그립시다==========================
	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), myBrush);

	HPEN myPen = (HPEN)CreatePen(2, 1, RGB(255, 0, 0));
	SelectObject(getMemDC(), myPen);

	SCENEMANAGER->render();

	TIMEMANAGER->render(getMemDC());

	SelectObject(getMemDC(), oldBrush);
	DeleteObject(myBrush);
	DeleteObject(myPen);
	//==================================================
	//여기도 건들지마라
	// this->getBackBuffer()->render(getHDC(), 0, 0);
	CAMERAMANAGER->render(getHDC(), 0, 0, getMemDC());
	//CAMERAMANAGER->render(getHDC(), 0, 0, getMemDC(),true);
}
