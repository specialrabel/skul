#include "stdafx.h"
#include "stage3.h"

//===========================
//		  �̴Ͼ��� 1
//===========================

HRESULT stage3::init()
{
	_player = new player;
	_player->init();

	_mm = new MonsterManager;
	_mm->SetMonster(3);

	_pu = new PlayerUI;
	_pu->init();

	CAMERAMANAGER->fadeIn_Init();

	//�̹��� �ҷ�����
	_leftPortalOpenImg = IMAGEMANAGER->addImage("openPortal_LEFT", "image/stage3_portalLeftOpen.bmp", 3328, 280, true, RGB(255, 0, 255));

	_leftPortalOpenAni = new animation;
	_leftPortalOpenAni->init(_leftPortalOpenImg->getWidth(), _leftPortalOpenImg->getHeight(), 416, 280);
	_leftPortalOpenAni->setPlayFrame(0, 8, false, true);
	_leftPortalOpenAni->setFPS(1.7f);

	_leftPortalOpenAni->start();

	_rightPortalOpenImg = IMAGEMANAGER->addImage("openPortal_RIGHT1", "image/stage3_portalRightOpen.bmp", 2928, 250, true, RGB(255, 0, 255));

	_rightPortalOpenAni = new animation;
	_rightPortalOpenAni->init(_rightPortalOpenImg->getWidth(), _rightPortalOpenImg->getHeight(), 366, 250);
	_rightPortalOpenAni->setPlayFrame(0, 8, false, true);
	_rightPortalOpenAni->setFPS(1.7f);

	_rightPortalOpenAni->start();

	//�̹��� �ҷ�����
	IMAGEMANAGER->addImage("stage3_backGround", "image/stage3_backGround.bmp", 4104, 1872, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("stage3_portalClose", "image/stage3_portalClose.bmp", 914, 274, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("stage3_portalToggle1", "image/Fbutton.bmp", 450, 48, true, RGB(15, 39, 39));
	IMAGEMANAGER->addImage("stage3_portalToggle2", "image/Fbutton.bmp", 450, 48, true, RGB(15, 39, 39));
	IMAGEMANAGER->addImage("stage3_backbackGround", "image/stage_backGround1.bmp", 1280, 720, true, RGB(255, 0, 255));

	_map1 = IMAGEMANAGER->findImage("stage3_backGround");
	_portalClose = IMAGEMANAGER->findImage("stage3_portalClose");
	_portalToggleImg1 = IMAGEMANAGER->findImage("stage3_portalToggle1");
	_portalToggleImg2 = IMAGEMANAGER->findImage("stage3_portalToggle2");
	_backGround = IMAGEMANAGER->findImage("stage3_backbackGround");


	//object[0~10]�� ����object
	//0~2 ground
	_object[0].x = 0;
	_object[0].y = 1380;
	_object[1].x = 500;
	_object[1].y = 1665;
	_object[2].x = 2310;
	_object[2].y = 1088;
	//3~5 airGround
	_object[3].x = 725;
	_object[3].y = 1370;
	_object[4].x = 1155;
	_object[4].y = 1080;
	_object[5].x = 1950;
	_object[5].y = 1370;
	//6~8 ceiling
	_object[6].x = 1655;
	_object[6].y = 0;
	_object[7].x = 1855;
	_object[7].y = 0;
	_object[8].x = 1945;
	_object[8].y = 0;
	//9~10 portal
	_object[9].x = 2850;
	_object[9].y = 893;
	_object[10].x = 3405;
	_object[10].y = 893;
	//���� ���¿뵵
	{
		//������Ʈ 3����
		_object[11].x = 720;
		_object[11].y = 1178;
		_object[12].x = 1280;
		_object[12].y = 1178;
		//������Ʈ 4����
		_object[13].x = 1150;
		_object[13].y = 890;
		//������Ʈ 5����
		_object[14].x = 1930;
		_object[14].y = 1180;
		//������Ʈ 2����
		_object[15].x = 2310;
		_object[15].y = 892;
	}


	//���� ��ġ
	_player->_player.x = 300;
	_player->_player.y = 1300;
	//ó�� ��������
	_player->_isLanding = false;
	//ī�޶� ����(�ʱ�ȭ)
	_startX = 0;
	_startY = 0;
	_endX = 4104;
	_endY = 1872;

	return S_OK;
}

void stage3::release()
{

}

void stage3::update()
{
	_object[0].rc = RectMake(_object[0].x, _object[0].y, 500, 720);
	_object[1].rc = RectMake(_object[1].x, _object[1].y, 1810, 200);
	_object[2].rc = RectMake(_object[2].x, _object[2].y, 1800, 1000);
	_object[3].rc = RectMake(_object[3].x, _object[3].y, 568, 30);
	_object[4].rc = RectMake(_object[4].x, _object[4].y, 505, 30);
	_object[5].rc = RectMake(_object[5].x, _object[5].y, 370, 30);
	_object[6].rc = RectMake(_object[6].x, _object[6].y, 210, 1150);
	_object[7].rc = RectMake(_object[7].x, _object[7].y, 90, 1070);
	_object[8].rc = RectMake(_object[8].x, _object[8].y, 70, 1000);
	_object[9].rc = RectMake(_object[9].x, _object[9].y, 155, 200);
	_object[10].rc = RectMake(_object[10].x, _object[10].y, 155, 200);
	_object[11].rc = RectMake(_object[11].x, _object[11].y, 20, 200);
	_object[12].rc = RectMake(_object[12].x, _object[12].y, 20, 200);
	_object[13].rc = RectMake(_object[13].x, _object[13].y, 20, 200);
	_object[14].rc = RectMake(_object[14].x, _object[14].y, 20, 200);
	_object[15].rc = RectMake(_object[15].x, _object[15].y, 20, 200);

	//�÷��̾� ������Ʈ
	_player->update();
	//���� ������Ʈ
	_mm->update();

	_pu->update();

	_portalToggle1 = false;
	_portalToggle2 = false;

	_pu->hpCalcul(_player->_hp);

	//=============================
	//   �÷��̾� - �׶��� �浹
	//=============================
	RECT temp;
	//ground ������
	for (int i = 0; i < 3; i++)
	{
		if (IntersectRect(&temp, &_player->_player.rc, &_object[i].rc))
		{
			//���� ����.
			if (temp.right - temp.left > temp.bottom - temp.top && _player->_player.rc.bottom - 35 < temp.top
				&& _player->_jumpPower < 0)
			{
				_player->_isLanding = true;
				_player->_jumpPower = 0;
				_player->_player.y = _object[i].y - 45;
			}
			//���� ������.
			if (temp.right - temp.left < temp.bottom - temp.top && _player->_player.rc.left > temp.right - 50)
			{
				_player->_player.x = _object[i].rc.right + 20;
			}
			//���� ����.
			if (temp.right - temp.left < temp.bottom - temp.top && _player->_player.rc.right < temp.left + 50)
			{
				_player->_player.x = _object[i].rc.left - 20;
			}
		}
	}
	//airGround ������
	for (int i = 3; i < 6; i++)
	{
		if (IntersectRect(&temp, &_player->_player.rc, &_object[i].rc))
		{
			//���� ����.
			if (temp.right - temp.left > temp.bottom - temp.top && _player->_player.rc.bottom - 35 < temp.top
				&& _player->_jumpPower < 0)
			{
				if (_player->_isFall)
				{
					_player->_isLanding = true;
					_player->_jumpPower = 0;
					_player->_player.y = _object[i].y - 45;
				}
			}
			//���� ������.
			if (temp.right - temp.left < temp.bottom - temp.top && _player->_player.rc.left > temp.right - 50)
			{
				_player->_player.x = _object[i].rc.right + 20;
			}
			//���� ����.
			if (temp.right - temp.left < temp.bottom - temp.top && _player->_player.rc.right < temp.left + 50)
			{
				_player->_player.x = _object[i].rc.left - 20;
			}
		}
	}
	//ceiling ������
	for (int i = 6; i < 9; i++) {
		if (IntersectRect(&temp, &_player->_player.rc, &_object[i].rc))
		{
			//���� �Ʒ���.
			if (temp.right - temp.left > temp.bottom - temp.top && _player->_player.rc.top < temp.bottom - 10)
			{
				_player->_jumpPower = -2;
			}
			//���� ������.
			if (temp.right - temp.left < temp.bottom - temp.top && _player->_player.rc.left > temp.right - 50)
			{
				_player->_player.x = _object[i].rc.right + 20;
			}
			//���� ����.
			if (temp.right - temp.left < temp.bottom - temp.top && _player->_player.rc.right < temp.left + 50)
			{
				_player->_player.x = _object[i].rc.left - 20;
			}
		}

	}
	//ȭ��ٱ� ����
	{
		if (_player->_player.rc.left < 0)
		{
			_player->_player.x = 30;
		}
		if (_player->_player.rc.right > 4104)
		{
			_player->_player.x = 4074;
		}
	}


	//=============================
	//        ���� - �浹
	//=============================
	for (int i = 0; i < _mm->getVNormalTree().size(); i++)
	{
		RECT dd = _mm->getVNormalTree()[i]->getTagMonster()->rc;
		RECT ee = _mm->getVNormalTree()[i]->getTagMonster()->sencer_rcL;
		RECT ff = _mm->getVNormalTree()[i]->getTagMonster()->sencer_rcR;
		RECT gg = _mm->getVNormalTree()[i]->getTagMonster()->sencer_rcA;
		RECT hh = _mm->getVNormalTree()[i]->getTagMonster()->monster1_attack_rc;

		//���Ϳ� ���ϴ� �����浹 ��
		for (int j = 0; j < 3; j++)
		{
			if (IntersectRect(&temp, &dd, &_object[j].rc))
			{
				//���� ����.
				if (temp.right - temp.left > temp.bottom - temp.top && _mm->getVNormalTree()[i]->getTagMonster()->rc.bottom - 35 < temp.top)
				{
					_mm->getVNormalTree()[i]->getTagMonster()->jumpPower = 0;
					_mm->getVNormalTree()[i]->getTagMonster()->y = _object[j].y - 70;
				}
				//���� ������.
				if (temp.right - temp.left < temp.bottom - temp.top && _mm->getVNormalTree()[i]->getTagMonster()->rc.left > temp.right - 50)
				{
					_mm->getVNormalTree()[i]->getTagMonster()->dir = 1;
					_mm->getVNormalTree()[i]->getTagMonster()->x = _object[j].rc.right + 50;
				}
				//���� ����.
				if (temp.right - temp.left < temp.bottom - temp.top && _mm->getVNormalTree()[i]->getTagMonster()->rc.right < temp.left + 60)
				{
					_mm->getVNormalTree()[i]->getTagMonster()->dir = 2;
					_mm->getVNormalTree()[i]->getTagMonster()->x = _object[j].rc.left - 40;
				}
			}
		}
		//���Ϳ� ���� �����浹 ��
		for (int j = 3; j < 6; j++)
		{
			if (IntersectRect(&temp, &dd, &_object[j].rc))
			{
				//���� ����.
				if (temp.right - temp.left > temp.bottom - temp.top && _mm->getVNormalTree()[i]->getTagMonster()->rc.bottom - 35 < temp.top)
				{
					_mm->getVNormalTree()[i]->getTagMonster()->jumpPower = 0;
					_mm->getVNormalTree()[i]->getTagMonster()->y = _object[j].y - 70;
				}
			}
		}
		//���Ϳ� õ���� �浹��
		for (int j = 6; j < 9; j++)
		{
			if (IntersectRect(&temp, &dd, &_object[j].rc))
			{
				//���� ������.
				if (temp.right - temp.left < temp.bottom - temp.top && _mm->getVNormalTree()[i]->getTagMonster()->rc.left > temp.right - 50)
				{
					_mm->getVNormalTree()[i]->getTagMonster()->dir = 1;
					_mm->getVNormalTree()[i]->getTagMonster()->x = _object[j].rc.right + 50;
				}
				//���� ����.
				if (temp.right - temp.left < temp.bottom - temp.top && _mm->getVNormalTree()[i]->getTagMonster()->rc.right < temp.left + 60)
				{
					_mm->getVNormalTree()[i]->getTagMonster()->dir = 2;
					_mm->getVNormalTree()[i]->getTagMonster()->x = _object[j].rc.left - 40;
				}
			}
		}
		//���� ���������� ������ �����������ϱ�
		for (int j = 11; j < 16; j++)
		{
			if (IntersectRect(&temp, &dd, &_object[j].rc))
			{
				//���� ������.
				if (temp.right - temp.left < temp.bottom - temp.top && _mm->getVNormalTree()[i]->getTagMonster()->rc.left > temp.right - 50
					&& !_mm->getVNormalTree()[i]->getTagMonster()->hit)
				{
					_mm->getVNormalTree()[i]->getTagMonster()->dir = 1;
					_mm->getVNormalTree()[i]->getTagMonster()->x = _object[j].rc.right + 50;
				}
				//���� ����.
				if (temp.right - temp.left < temp.bottom - temp.top && _mm->getVNormalTree()[i]->getTagMonster()->rc.right < temp.left + 50
					&& !_mm->getVNormalTree()[i]->getTagMonster()->hit)
				{
					_mm->getVNormalTree()[i]->getTagMonster()->dir = 2;
					_mm->getVNormalTree()[i]->getTagMonster()->x = _object[j].rc.left - 40;
				}
			}
		}
		//ȭ��ٱ� ����
		{
			if (dd.left < 0)
			{
				_mm->getVNormalTree()[i]->getTagMonster()->x = 50;
			}
			if (dd.left > 4004)
			{
				_mm->getVNormalTree()[i]->getTagMonster()->x = 4054;
			}
		}




		//�÷��̾��� ���ݷ�Ʈ�� �������.(�ܼ��ϰ�)
		if (IntersectRect(&temp, &dd, &_player->_player_attack.rc))
		{
			_mm->getVNormalTree()[i]->getTagMonster()->hp -= 1;
			if (!_player->_direction) // �÷��̾ �������� ���� ������ ���ݹ����� ������
			{
				_mm->getVNormalTree()[i]->getTagMonster()->time = 0;
				_mm->getVNormalTree()[i]->getTagMonster()->dir = 2;
				_mm->getVNormalTree()[i]->getTagMonster()->hit = true;
			}
			if (_player->_direction) // �÷��̾ ������ ���� ������ ���ݹ����� ������
			{
				_mm->getVNormalTree()[i]->getTagMonster()->time = 0;
				_mm->getVNormalTree()[i]->getTagMonster()->dir = 1;
				_mm->getVNormalTree()[i]->getTagMonster()->hit = true;
			}
		}
		//���Ͱ� ����������Ʈ�� �÷��̾ ����������.(�����ʷ�Ʈ���� ����)
		if (IntersectRect(&temp, &ff, &_player->_player.rc))
		{
			++_mm->getVNormalTree()[i]->getTagMonster()->find;

			_mm->getVNormalTree()[i]->getTagMonster()->dir = 1;

			if (_mm->getVNormalTree()[i]->getTagMonster()->find == 1)
			{
				_mm->getVNormalTree()[i]->getTagMonster()->currentFrameX = 0;
			}
		}
		//���Ͱ� ����������Ʈ�� �÷��̾ ����������.(���ʷ�Ʈ���� ����)
		else if (IntersectRect(&temp, &ee, &_player->_player.rc))
		{
			++_mm->getVNormalTree()[i]->getTagMonster()->find;

			_mm->getVNormalTree()[i]->getTagMonster()->dir = 2;

			if (_mm->getVNormalTree()[i]->getTagMonster()->find == 1)
			{
				_mm->getVNormalTree()[i]->getTagMonster()->currentFrameX = 0;
			}
		}
		//���Ͱ� ����������Ʈ�� �÷��̾ ����������.(�߾ӷ�Ʈ���� ����)
		else if (IntersectRect(&temp, &gg, &_player->_player.rc))
		{
			++_mm->getVNormalTree()[i]->getTagMonster()->find;
			_mm->getVNormalTree()[i]->getTagMonster()->time = 0;

			_mm->getVNormalTree()[i]->getTagMonster()->attack = true;

			if (_mm->getVNormalTree()[i]->getTagMonster()->find == 1)
			{
				_mm->getVNormalTree()[i]->getTagMonster()->currentFrameX = 0;
			}
		}
		// �÷��̾ ��� ������������ ������ ���� �ʾ�����.
		else
		{
			_mm->getVNormalTree()[i]->getTagMonster()->attack = false;
			_mm->getVNormalTree()[i]->getTagMonster()->find = 0;
			_mm->getVNormalTree()[i]->getTagMonster()->monster1_attack_rc_H = 0;
			_mm->getVNormalTree()[i]->getTagMonster()->monster1_attack_rc_W = 0;
		}

		//������ ���ݿ� �÷��̾ �¾�����.
		if (IntersectRect(&temp, &hh, &_player->_player.rc))
		{
			_player->_hp -= 1;
			_player->_hit = true;
		}
		else
		{
			_player->_hit = false;
		}

		if (_mm->getVNormalTree()[0]->getTagMonster()->hp < 0) a1 = true;
		if (_mm->getVNormalTree()[1]->getTagMonster()->hp < 0) a2 = true;
		if (_mm->getVNormalTree()[2]->getTagMonster()->hp < 0) a3 = true;
		if (_mm->getVNormalTree()[3]->getTagMonster()->hp < 0) a4 = true;
		if (_mm->getVNormalTree()[4]->getTagMonster()->hp < 0) a5 = true;
		if (_mm->getVNormalTree()[5]->getTagMonster()->hp < 0) a6 = true;

		if (_mm->getVNormalTree()[i]->getTagMonster()->hp < 0)
		{
			_monsterDEAD += 1;
			_mm->getVNormalTree()[i]->getTagMonster()->x = 20000;
		}
		if (a1 && a2 && a3 && a4 && a5 && a6)
		{
			_isALLDEAD = true;
		}
	}

	//portal ���߿��� ���� ������� �÷��̾ ��ó�� ������ �ִϸ��̼��� ����� ��, ��Ż��Ʈ�� Ȱ��ȭ�ǵ��� ��������.
	if (IntersectRect(&temp, &_player->_player.rc, &_object[9].rc))
	{
		if (_isALLDEAD)
		{
			_portalToggle1 = true;

			if (KEYMANAGER->isOnceKeyDown('F'))
			{
				SCENEMANAGER->changeScene("�̴Ͼ���2-1");
			}
		}
	}
	if (IntersectRect(&temp, &_player->_player.rc, &_object[10].rc))
	{
		if (_isALLDEAD)
		{
			_portalToggle2 = true;

			if (KEYMANAGER->isOnceKeyDown('F'))
			{
				SCENEMANAGER->changeScene("�̴Ͼ���2-2");
			}
		}
	}
	_leftPortalOpenAni->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
	_rightPortalOpenAni->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);

	CAMERAMANAGER->updateScreen(_player->_player.x, _player->_player.y, _startX, _startY, _endX, _endY);
}

void stage3::render()
{
	//=====================================================

	CAMERAMANAGER->ui(_backGround, getMemDC(), 0, 0);

	_map1->render(getMemDC(), 0, 0);
	_portalClose->render(getMemDC(), 2730, 845);
	if(_isALLDEAD){ 
		_leftPortalOpenImg->aniRender(getMemDC(), 2720, 835, _leftPortalOpenAni); 
		_rightPortalOpenImg->aniRender(getMemDC(), 3300, 845, _rightPortalOpenAni);
	}

	_mm->render();
	_player->render();
	_pu->playerHPrender(getMemDC(), _player->_player.x, _player->_player.y);

	if (_portalToggle1)
	{
		_portalToggleImg1->render(getMemDC(), 2710, 1150);
	}
	if (_portalToggle2)
	{
		_portalToggleImg2->render(getMemDC(), 3260, 1150);
	}


	//object TEST
	//Rectangle(getMemDC(), _object[0].rc);
	//Rectangle(getMemDC(), _object[1].rc);
	//Rectangle(getMemDC(), _object[2].rc);
	//Rectangle(getMemDC(), _object[3].rc);
	//Rectangle(getMemDC(), _object[4].rc);
	//Rectangle(getMemDC(), _object[5].rc);
	//Rectangle(getMemDC(), _object[6].rc);
	//Rectangle(getMemDC(), _object[7].rc);
	//Rectangle(getMemDC(), _object[8].rc);
	//Rectangle(getMemDC(), _object[9].rc);
	//Rectangle(getMemDC(), _object[10].rc);
	//�������� ���� ���� ����
	Rectangle(getMemDC(), _object[11].rc);
	Rectangle(getMemDC(), _object[12].rc);
	Rectangle(getMemDC(), _object[13].rc);
	Rectangle(getMemDC(), _object[14].rc);
	Rectangle(getMemDC(), _object[15].rc);

	//====================================================

	CAMERAMANAGER->fadeIn(getMemDC());
}