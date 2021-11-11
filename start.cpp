#include "stdafx.h"
#include "start.h"

//===========================
//		   ���� ȭ��
//===========================

HRESULT start::init()
{
	_startImg = IMAGEMANAGER->addImage("start", "image/start.bmp", 28160, 720, true, RGB(255, 0, 255));

	_startAni = new animation;
	_startAni->init(_startImg->getWidth(), _startImg->getHeight(), 1280, 720);
	_startAni->setPlayFrame(0, 22, false, false);
	_startAni->setFPS(1.7f);

	_startAni->start();

	_startKeyImg = IMAGEMANAGER->addImage("startKey", "image/startKey.bmp", 422, 43, true, RGB(255, 0, 255));

	_fade = 0;


	return S_OK;
}

void start::release()
{

}

void start::update()
{
	++_time;

	if (_time > 80) { _anyKey = true; }
		
	if (_anyKey)
	{
		for (int i = 1; i <= 244; i++)
		{
			if (i == 12 || i == 20 || i == 34 || i == 35 || i == 45 || i == 144 || i == 145) continue; // 45insert, 144numlock, 20capital(ĸ����)
			if (KEYMANAGER->isOnceKeyDown(i)) { SCENEMANAGER->changeScene("���ռ�"); }
		}

		//============================
		//      �ؽ�Ʈ ���ĺ���
		//============================
		if (_fade == 0)
		{
			_fadeIn = true;
			_fadeOut = false;
		}
		else if (_fade == 255)
		{
			_fadeIn = false;
			_fadeOut = true;
		}
		else if (_fade > 255)
		{
			_fade = 255;
		}
		else if (_fade < 0)
		{
			_fade = 0;
		}
		//���̵� ������ ����� ����. 255�� �Ѿ�ų�, 0���Ϸ� �������� ������ ���������.. ���߿� ���� �� �Ұ�
		if (_fadeIn)
		{
			_fade += 3;
		}
		else if (_fadeOut)
		{
			_fade -= 3;
		}
	}

	_startAni->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
}

void start::render()
{
	_startImg->aniRender(getMemDC(), 0, 0, _startAni);

	if (_anyKey)
	{
		_startKeyImg->alphaRender(getMemDC(), 427, 480, _fade);
	}
}