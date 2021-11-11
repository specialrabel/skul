#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{
}

//�ʱ�ȭ�� ����� �ϼ��� ����
HRESULT playGround::init()
{
	gameNode::init(true);

	SCENEMANAGER->addScene("����ȭ��", new start);
	SCENEMANAGER->addScene("���ռ�", new stage1);
	SCENEMANAGER->addScene("�����Ա�", new stage2);
	SCENEMANAGER->addScene("�̴Ͼ���1", new stage3);
	SCENEMANAGER->addScene("�̴Ͼ���2-1", new stage4);
	SCENEMANAGER->addScene("�̴Ͼ���2-2", new stage5);
	SCENEMANAGER->addScene("������1", new stage6);

	SCENEMANAGER->changeScene("����ȭ��");

	return S_OK;
}

//�޸� ������ ����� �ϼ��� ����
void playGround::release()
{
	gameNode::release();

	SCENEMANAGER->release();
}


void playGround::update()
{
	gameNode::update();

	SCENEMANAGER->update();

	//�۾���(�������� �����)
	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		SCENEMANAGER->changeScene("����ȭ��");
	}
	else if (KEYMANAGER->isOnceKeyDown('2'))
	{
		SCENEMANAGER->changeScene("���ռ�");
	}
	else if (KEYMANAGER->isOnceKeyDown('3'))
	{
		SCENEMANAGER->changeScene("�����Ա�");
	}
	else if (KEYMANAGER->isOnceKeyDown('4'))
	{
		SCENEMANAGER->changeScene("�̴Ͼ���1");
	}
	else if (KEYMANAGER->isOnceKeyDown('5'))
	{
		SCENEMANAGER->changeScene("�̴Ͼ���2-1");
	}
	else if (KEYMANAGER->isOnceKeyDown('6'))
	{
		SCENEMANAGER->changeScene("�̴Ͼ���2-2");
	}
	else if (KEYMANAGER->isOnceKeyDown('7'))
	{
		SCENEMANAGER->changeScene("������1");
	}
}


void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, 10000, 10000, BLACKNESS);
	// ���� �ǵ�������
	//================���� �� ���̿� �� �׸��ô�==========================
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
	//���⵵ �ǵ�������
	// this->getBackBuffer()->render(getHDC(), 0, 0);
	CAMERAMANAGER->render(getHDC(), 0, 0, getMemDC());
	//CAMERAMANAGER->render(getHDC(), 0, 0, getMemDC(),true);
}
