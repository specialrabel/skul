#include "stdafx.h"
#include "stage2.h"

//===========================
//		   ���� �Ա�
//===========================

HRESULT stage2::init()
{
	_player = new player;
	_player->init();

	_pu = new PlayerUI;
	_pu->init();

	CAMERAMANAGER->fadeIn_Init();

	//�̹��� �ҷ�����
	_portalImg = IMAGEMANAGER->addImage("portal2", "image/stage2_portal.bmp", 2928, 250, true, RGB(255, 0, 255));

	_portalAni = new animation;
	_portalAni->init(_portalImg->getWidth(), _portalImg->getHeight(), 366, 250);
	_portalAni->setPlayFrame(0, 8, false, true);
	_portalAni->setFPS(1.7f);

	_portalAni->start();

	IMAGEMANAGER->addImage("stage2_ground", "image/stage2_ground.bmp", 2000, 180, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("stage2_backGround", "image/stage2_backGround.bmp", 2000, 720, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("stage2_sky", "image/stage2_sky.bmp", 2000, 556, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("stage2_portalToggle", "image/Fbutton.bmp", 450, 48, true, RGB(15, 39, 39));

	_map1 = IMAGEMANAGER->findImage("stage2_backGround");
	_ground = IMAGEMANAGER->findImage("stage2_ground");
	_sky = IMAGEMANAGER->findImage("stage2_sky");
	_portalToggleImg = IMAGEMANAGER->findImage("stage2_portalToggle");

	//object[0]�� ground
	_object[0].x = 0;
	_object[0].y = 550;
	//object[1]�� ��Ż
	_object[1].x = 1580;
	_object[1].y = 350;

	//���ռ� ���� ��ġ
	_player->_player.x = 550;
	_player->_player.y = -250;

	//���ռ����� ������������ �ӵ��� ��������ó�� ���̰�
	_player->_jumpPower = -15;

	//ó�� ��������
	_player->_isLanding = false;

	//ī�޶� ����(�ʱ�ȭ)
	_startX = 0;
	_startY = 0;
	_endX = 2000;
	_endY = 720;

	return S_OK;
}

void stage2::release()
{

}

void stage2::update()
{
	_object[0].rc = RectMake(_object[0].x, _object[0].y, 4050, 720);
	_object[1].rc = RectMake(_object[1].x, _object[1].y, 155, 200);

	_player->update();
	_pu->update();

	_portalToggle = false;

	//=============================
	//       ������Ʈ �浹
	//=============================
	RECT temp;
	//ground ���� ��
	if (IntersectRect(&temp, &_player->_player.rc, &_object[0].rc))
	{
		//���� ����.
		if (temp.right - temp.left > temp.bottom - temp.top && _player->_player.rc.bottom - 35 < temp.top
			&& _player->_jumpPower < 0)
		{
			_player->_isLanding = true;
			_player->_jumpPower = 0;
			_player->_player.y = _object[0].y - 45;
		}
		//���� ������.
		if (temp.right - temp.left < temp.bottom - temp.top && _player->_player.rc.left > temp.right - 50)
		{
			_player->_player.x = _object[0].rc.right + 20;
		}
		//���� ����.
		if (temp.right - temp.left < temp.bottom - temp.top && _player->_player.rc.right < temp.left + 50)
		{
			_player->_player.x = _object[0].rc.left - 20;
		}
	}
	//portal
	if(IntersectRect(&temp, &_player->_player.rc, &_object[1].rc))
	{
		_portalToggle = true;

		if (KEYMANAGER->isOnceKeyDown('F'))
		{
			SCENEMANAGER->changeScene("�̴Ͼ���1");
		}
	}
	//ȭ��ٱ� ����
	{
		if (_player->_player.rc.left < 0)
		{
			_player->_player.x = 30;
		}
		if (_player->_player.rc.right > 2000)
		{
			_player->_player.x = 1970;
		}
	}

	CAMERAMANAGER->updateScreen(_player->_player.x, _player->_player.y, _startX, _startY, _endX, _endY);

	_portalAni->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
}

void stage2::render()
{
	//=====================================================

// Rectangle(getMemDC(), _rc); //����1
	
	_sky->render(getMemDC(), 0, 0);
	_map1->render(getMemDC(), 0, 0);
	_ground->render(getMemDC(), 0, 535);
	_portalImg->aniRender(getMemDC(), 1480, 302, _portalAni);

	_player->render();
	_pu->playerHPrender(getMemDC(), _player->_player.x, _player->_player.y);

	if (_portalToggle)
	{
		_portalToggleImg->render(getMemDC(), 1430, 600);
	}

	//object TEST
	//Rectangle(getMemDC(), _object[0].rc);
	//Rectangle(getMemDC(), _object[1].rc);

	//====================================================

	CAMERAMANAGER->fadeIn(getMemDC());
}