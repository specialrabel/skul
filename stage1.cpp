#include "stdafx.h"
#include "stage1.h"

//===========================
//		    마왕성
//===========================

HRESULT stage1::init()
{
	_player = new player;
	_player->init();

	_pu = new PlayerUI;
	_pu->init();

	CAMERAMANAGER->fadeIn_Init();
	CAMERAMANAGER->fadeOut_Init();

	//이미지 불러오기
	_rebornImg = IMAGEMANAGER->addImage("reborn", "image/LITTLEBONE_REBORN.bmp", 13500, 500, true, RGB(255, 0, 255));

	_rebornAni = new animation;
	_rebornAni->init(_rebornImg->getWidth(), _rebornImg->getHeight(), 500, 500);
	_rebornAni->setPlayFrame(0, 27, false, false);
	_rebornAni->setFPS(1.2f);

	_rebornAni->start();

	IMAGEMANAGER->addImage("stage1_backGround", "image/stage1_backGround.bmp", 3658, 599, true, RGB(9, 9, 36));
	IMAGEMANAGER->addImage("stage1_ground", "image/stage1_ground.bmp", 3685, 65, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("stage1_groundCandle", "image/stage1_groundCandle.bmp", 3658, 338, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("stage1_groundWall", "image/stage1_groundWall.bmp", 3759, 90, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("stage1_fallWall1", "image/stage1_fallWall1.bmp", 476, 1349, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("stage1_fallWall2", "image/stage1_fallWall2.bmp", 476, 1427, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("stage1_outWall", "image/stage1_outWall.bmp", 458, 1025, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("stage1_inWall", "image/stage1_inWall.bmp", 457, 648, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("stage1_skyMove", "image/stage1_skyMove.bmp", 1280, 720, true, RGB(58, 55, 89));
	IMAGEMANAGER->addImage("stage1_backBillage", "image/stage1_backBillage.bmp", 1000, 2500, true, RGB(24, 22, 61));

	_map1 = IMAGEMANAGER->findImage("stage1_backGround");
	_ground = IMAGEMANAGER->findImage("stage1_ground");
	_groundCandle = IMAGEMANAGER->findImage("stage1_groundCandle");
	_groundWall = IMAGEMANAGER->findImage("stage1_groundWall");
	_fallWall1 = IMAGEMANAGER->findImage("stage1_fallWall1");
	_fallWall2 = IMAGEMANAGER->findImage("stage1_fallWall2");
	_fallWall3 = IMAGEMANAGER->findImage("stage1_fallWall2");
	_fallWall4 = IMAGEMANAGER->findImage("stage1_fallWall2");
	_outWall = IMAGEMANAGER->findImage("stage1_outWall");
	_inWall = IMAGEMANAGER->findImage("stage1_inWall");
	_skyMove = IMAGEMANAGER->findImage("stage1_skyMove");
	_backBillage = IMAGEMANAGER->findImage("stage1_backBillage");
	

	//지형렉트 위치
	_object[0].x = 0;
	_object[0].y = 600;
	_object[1].x = 0;
	_object[1].y = 515;
	_object[2].x = 0;
	_object[2].y = 470;
	_object[3].x = 0;
	_object[3].y = 440;
	_object[4].x = 125;
	_object[4].y = 390;

	//마왕성 스폰 위치
	_player->_player.x = 800;
	_player->_player.y = 555;

	//처음 랜딩상태
	_player->_isLanding = true;
	_player->_isFall = true;

	//카메라 제한(초기화)
	_startX = 0;
	_startY = 0;
	_endX = 3658;
	_endY = 720;
	_cameraSpeedX = 45;
	_cameraSpeedY = 720;

	//페이드인 하는동안 동작멈추기
	_playerSTOP = true;

	return S_OK;
}

void stage1::release()
{
	_player->release();
}

void stage1::update()
{
	++_time;
	skyMove += 0.6f;

	if (_time > 20)
	{
		_rebornAni->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
	}
	if ( _time >= 160){ _player->update(); }
	_pu->update();


	_object[0].rc = RectMake(_object[0].x, _object[0].y, 4050, 5000);
	_object[1].rc = RectMake(_object[1].x, _object[1].y, 900, 50);
	_object[2].rc = RectMake(_object[2].x, _object[2].y, 780, 50);
	_object[3].rc = RectMake(_object[3].x, _object[3].y, 480, 50);
	_object[4].rc = RectMake(_object[4].x, _object[4].y, 280, 50);

	RECT temp; 
	//ground 정리 끝
	if (IntersectRect(&temp, &_player->_player.rc, &_object[0].rc))
	{
		//지형 위쪽.
		if (temp.right - temp.left > temp.bottom - temp.top && _player->_player.rc.bottom - 35 < temp.top
			&& _player->_jumpPower < 0)
		{
			_player->_isLanding = true;
			_player->_jumpPower = 0;
			_player->_player.y = _object[0].y - 45;
		}
		//지형 오른쪽.
		if (temp.right - temp.left < temp.bottom - temp.top && _player->_player.rc.left > temp.right - 50)
		{
			_player->_player.x = _object[0].rc.right + 20;
		}
		//지형 왼쪽.
		if (temp.right - temp.left < temp.bottom - temp.top && _player->_player.rc.right < temp.left + 50)
		{
			_player->_player.x = _object[0].rc.left - 20;
		}
	}
	//airGround(stage1 용)
	if (IntersectRect(&temp, &_player->_player.rc, &_object[1].rc))
	{
		//지형 위쪽.
		if (temp.right - temp.left > temp.bottom - temp.top && _player->_player.rc.bottom - 35 < temp.top
			&& _player->_jumpPower < 0)
		{
			if (_player->_isFall)
			{
				_player->_isLanding = true;
				_player->_jumpPower = 0;
				_player->_player.y = _object[1].y - 45;
			}
		}
	}
	if (IntersectRect(&temp, &_player->_player.rc, &_object[2].rc))
	{
		//지형 위쪽.
		if (temp.right - temp.left > temp.bottom - temp.top && _player->_player.rc.bottom - 35 < temp.top
			&& _player->_jumpPower < 0)
		{
			if (_player->_isFall)
			{
				_player->_isLanding = true;
				_player->_jumpPower = 0;
				_player->_player.y = _object[2].y - 45;
			}
		}
	}
	if (IntersectRect(&temp, &_player->_player.rc, &_object[3].rc))
	{
		//지형 위쪽.
		if (temp.right - temp.left > temp.bottom - temp.top && _player->_player.rc.bottom - 25 < temp.top
			&& _player->_jumpPower < 0)
		{
			if (_player->_isFall)
			{
				_player->_isLanding = true;
				_player->_jumpPower = 0;
				_player->_player.y = _object[3].y - 45;
			}
		}
	}
	if (IntersectRect(&temp, &_player->_player.rc, &_object[4].rc))
	{
		//지형 위쪽.
		if (temp.right - temp.left > temp.bottom - temp.top && _player->_player.rc.bottom - 25 < temp.top
			&& _player->_jumpPower < 0)
		{
			if (_player->_isFall)
			{
				_player->_isLanding = true;
				_player->_jumpPower = 0;
				_player->_player.y = _object[4].y - 45;
			}
		}
	}
	//화면바깥 막기
	{
		if (_player->_player.rc.left < 0)
		{
			_player->_player.x = 30;
		}
		if (_player->_player.rc.right > 4938)
		{
			_player->_player.x = 4908;
		}
	}



	//====================================================
	//                  카메라 전환설정
	//====================================================
	//오른쪽에서 왼쪽으로 갈 때
	if (_player->_player.x < 3658)
	{
		if (_endX > 3658)
		{
			_startX -= _cameraSpeedX; // 3658에서 0까지
			_endX -= _cameraSpeedX; // 4938에서 3658까지
		}
		else if (_endX <= 3658)
		{
			_startX = 0;
			_endX = 3658;
		}

	}
	//왼쪽에서 오른쪽으로 갈 때 
	else if (_player->_player.x >= 3658)
	{
		if (_endX < 4938)
		{
			_endX += _cameraSpeedX;
			_startX = _endX - WINSIZEX;
		}
		else if (_endX >= 4938)
		{
			_startX = 3658;
			_endX = 4938;
		}

	}
	//낭떠러지
	if (_player->_player.y >= 720)
	{
		if (_cameraSpeedY > 600)
		{
			_cameraSpeedY -= 5;
		}
		_startY = _player->_player.y - _cameraSpeedY;
		if (_endY < 5630) // "연출감 있었다" - 민재씨 2021-06-07
		{
			_endY = _startY + 720;
		}
	}

	CAMERAMANAGER->updateScreen(_player->_player.x, _player->_player.y, _startX, _startY, _endX, _endY);

	if(_player->_player.y > 6200)
	{
		SCENEMANAGER->changeScene("던전입구");
	}
}

void stage1::render()
{
	//=====================================================
	CAMERAMANAGER->backGround(getMemDC(), 1);
	
	RECT rc = RectMakeCenter(0, 0, 7430, 720);
	_skyMove->loopRender(getMemDC(), &rc, skyMove, 300);

	_map1->render(getMemDC(), 0, 0);
	_groundWall->render(getMemDC(), 0, 620);
	_ground->render(getMemDC(), 0, 580);
	_backBillage->render(getMemDC(), 4000, 3300);
	_fallWall1->render(getMemDC(), 3658, 645);
	_fallWall2->render(getMemDC(), 3658, 1994);
	_fallWall3->render(getMemDC(), 3658, 3421);
	_fallWall4->render(getMemDC(), 3658, 4848);
	_inWall->render(getMemDC(), 3658, 0);

	if (_time > 160) { _player->render(); }
	if (_time <= 160) { _rebornImg->aniRender(getMemDC(), 550, 314, _rebornAni); }

	_groundCandle->render(getMemDC(), 0, 500);
	_outWall->render(getMemDC(), 3658, -420);

	_pu->playerHPrender(getMemDC(), _player->_player.x, _player->_player.y);

	//Rectangle(getMemDC(), _object[1].rc); //지형1
	//Rectangle(getMemDC(), _object[2].rc); //지형1
	//Rectangle(getMemDC(), _object[3].rc); //지형1
	//Rectangle(getMemDC(), _object[4].rc); //지형1

	//====================================================
	CAMERAMANAGER->fadeIn(getMemDC());
}