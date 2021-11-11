#include "stdafx.h"
#include "stage5.h"

//===========================
//		 �̴Ͼ��� 2-2
//===========================

HRESULT stage5::init()
{
	_player = new player;
	_player->init();

	_mm = new MonsterManager;
	_mm->SetMonster(5);

	_pu = new PlayerUI;
	_pu->init();

	CAMERAMANAGER->fadeIn_Init();

	//�̹��� �ҷ�����
	_portalImg = IMAGEMANAGER->addImage("portal5", "image/stage6_portal.bmp", 4544, 404, true, RGB(255, 0, 255));

	_portalAni = new animation;
	_portalAni->init(_portalImg->getWidth(), _portalImg->getHeight(), 568, 404);
	_portalAni->setPlayFrame(0, 8, false, true);
	_portalAni->setFPS(1.7f);

	_portalAni->start();

	IMAGEMANAGER->addImage("stage5_backGround", "image/stage5_backGround.bmp", 2520, 2500, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("stage5_portalToggle", "image/Fbutton.bmp", 450, 48, true, RGB(15, 39, 39));
	IMAGEMANAGER->addImage("stage5_backbackGround", "image/stage_backGround3.bmp", 1280, 720, true, RGB(255, 0, 255));

	_map1 = IMAGEMANAGER->findImage("stage5_backGround");
	_portalToggleImg = IMAGEMANAGER->findImage("stage5_portalToggle");
	_backGround = IMAGEMANAGER->findImage("stage5_backbackGround");

	//object[0~10]�� ����object
	//0~2 ground
	_object[0].x = 0;
	_object[0].y = 2073;
	_object[1].x = 496;
	_object[1].y = 2295;
	_object[2].x = 2022;
	_object[2].y = 2078;
	//3~6 airGround
	_object[3].x = 580;
	_object[3].y = 1857;
	_object[4].x = 1516;
	_object[4].y = 1857;
	_object[5].x = 369;
	_object[5].y = 1570;
	_object[6].x = 1086;
	_object[6].y = 1280;
	//���� ���¿뵵
	{
		//������Ʈ 0����
		_object[7].x = 480;
		_object[7].y = 1880;
		_object[8].x = 560;
		_object[8].y = 1662;
		_object[9].x = 1000;
		_object[9].y = 1662;
		_object[10].x = 1500;
		_object[10].y = 1662;
		_object[11].x = 1930;
		_object[11].y = 1662;
		_object[12].x = 2010;
		_object[12].y = 1880;
		_object[13].x = 340;
		_object[13].y = 1370;
		_object[14].x = 2150;
		_object[14].y = 1370;
	}
	//��Ż�Ա�
	_object[15].x = 1180;
	_object[15].y = 2100;

	//���� ��ġ
	_player->_player.x = 200;
	_player->_player.y = 1980;
	//ó�� ��������
	_player->_isLanding = false;
	//ī�޶� ����(�ʱ�ȭ)
	_startX = 0;
	_startY = 0;
	_endX = 2520;
	_endY = 2500;

	return S_OK;
}

void stage5::release()
{

}

void stage5::update()
{
	_object[0].rc = RectMake(_object[0].x, _object[0].y, 496, 420);
	_object[1].rc = RectMake(_object[1].x, _object[1].y, 1527, 201);
	_object[2].rc = RectMake(_object[2].x, _object[2].y, 499, 418);
	_object[3].rc = RectMake(_object[3].x, _object[3].y, 423, 21);
	_object[4].rc = RectMake(_object[4].x, _object[4].y, 424, 26);
	_object[5].rc = RectMake(_object[5].x, _object[5].y, 1787, 18);
	_object[6].rc = RectMake(_object[6].x, _object[6].y, 350, 22);
	_object[7].rc = RectMake(_object[7].x, _object[7].y, 20, 200);
	_object[8].rc = RectMake(_object[8].x, _object[8].y, 20, 200);
	_object[9].rc = RectMake(_object[9].x, _object[9].y, 20, 200);
	_object[10].rc = RectMake(_object[10].x, _object[10].y, 20, 200);
	_object[11].rc = RectMake(_object[11].x, _object[11].y, 20, 200);
	_object[12].rc = RectMake(_object[12].x, _object[12].y, 20, 200);
	_object[13].rc = RectMake(_object[13].x, _object[13].y, 20, 200);
	_object[14].rc = RectMake(_object[14].x, _object[14].y, 20, 200);
	_object[15].rc = RectMake(_object[15].x, _object[15].y, 155, 200);

	//�÷��̾� ������Ʈ
	_player->update();
	//���� ������Ʈ
	_mm->update();
	_pu->update();

	_portalToggle = false;

	_pu->hpCalcul(_player->_hp);

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
	if (IntersectRect(&temp, &_player->_player.rc, &_object[1].rc))
	{
		//���� ����.
		if (temp.right - temp.left > temp.bottom - temp.top && _player->_player.rc.bottom - 35 < temp.top
			&& _player->_jumpPower < 0)
		{
			_player->_isLanding = true;
			_player->_jumpPower = 0;
			_player->_player.y = _object[1].y - 45;
		}
		//���� ������.
		if (temp.right - temp.left < temp.bottom - temp.top && _player->_player.rc.left > temp.right - 50)
		{
			_player->_player.x = _object[1].rc.right + 20;
		}
		//���� ����.
		if (temp.right - temp.left < temp.bottom - temp.top && _player->_player.rc.right < temp.left + 50)
		{
			_player->_player.x = _object[1].rc.left - 20;
		}
	}
	if (IntersectRect(&temp, &_player->_player.rc, &_object[2].rc))
	{
		//���� ����.
		if (temp.right - temp.left > temp.bottom - temp.top && _player->_player.rc.bottom - 35 < temp.top
			&& _player->_jumpPower < 0)
		{
			_player->_isLanding = true;
			_player->_jumpPower = 0;
			_player->_player.y = _object[2].y - 45;
		}
		//���� ������.
		if (temp.right - temp.left < temp.bottom - temp.top && _player->_player.rc.left > temp.right - 50)
		{
			_player->_player.x = _object[2].rc.right + 20;
		}
		//���� ����.
		if (temp.right - temp.left < temp.bottom - temp.top && _player->_player.rc.right < temp.left + 50)
		{
			_player->_player.x = _object[2].rc.left - 20;
		}
	}
	//ceiling ���� ��
	if (IntersectRect(&temp, &_player->_player.rc, &_object[3].rc))
	{
		//���� ����.
		if (temp.right - temp.left > temp.bottom - temp.top && _player->_player.rc.bottom - 35 < temp.top)
		{
			if (_player->_isFall)
			{
				_player->_isLanding = true;
				_player->_jumpPower = 0;
				_player->_player.y = _object[3].y - 45;
			}
		}
		//���� ������.
		if (temp.right - temp.left < temp.bottom - temp.top && _player->_player.rc.left > temp.right - 50)
		{
			_player->_player.x = _object[3].rc.right + 20;
		}
		//���� ����.
		if (temp.right - temp.left < temp.bottom - temp.top && _player->_player.rc.right < temp.left + 50)
		{
			_player->_player.x = _object[3].rc.left - 20;
		}
	}
	if (IntersectRect(&temp, &_player->_player.rc, &_object[4].rc))
	{
		//���� ����.
		if (temp.right - temp.left > temp.bottom - temp.top && _player->_player.rc.bottom - 35 < temp.top)
		{
			if (_player->_isFall)
			{
				_player->_isLanding = true;
				_player->_jumpPower = 0;
				_player->_player.y = _object[4].y - 45;
			}
		}
		//���� ������.
		if (temp.right - temp.left < temp.bottom - temp.top && _player->_player.rc.left > temp.right - 50)
		{
			_player->_player.x = _object[4].rc.right + 20;
		}
		//���� ����.
		if (temp.right - temp.left < temp.bottom - temp.top && _player->_player.rc.right < temp.left + 50)
		{
			_player->_player.x = _object[4].rc.left - 20;
		}
	}
	if (IntersectRect(&temp, &_player->_player.rc, &_object[5].rc))
	{
		//���� ����.
		if (temp.right - temp.left > temp.bottom - temp.top && _player->_player.rc.bottom - 35 < temp.top)
		{
			if (_player->_isFall)
			{
				_player->_isLanding = true;
				_player->_jumpPower = 0;
				_player->_player.y = _object[5].y - 45;
			}
		}
		//���� ������.
		if (temp.right - temp.left < temp.bottom - temp.top && _player->_player.rc.left > temp.right - 50)
		{
			_player->_player.x = _object[5].rc.right + 20;
		}
		//���� ����.
		if (temp.right - temp.left < temp.bottom - temp.top && _player->_player.rc.right < temp.left + 50)
		{
			_player->_player.x = _object[5].rc.left - 20;
		}
	}
	if (IntersectRect(&temp, &_player->_player.rc, &_object[6].rc))
	{
		//���� ����.
		if (temp.right - temp.left > temp.bottom - temp.top && _player->_player.rc.bottom - 35 < temp.top)
		{
			if (_player->_isFall)
			{
				_player->_isLanding = true;
				_player->_jumpPower = 0;
				_player->_player.y = _object[6].y - 45;
			}
		}
		//���� ������.
		if (temp.right - temp.left < temp.bottom - temp.top && _player->_player.rc.left > temp.right - 50)
		{
			_player->_player.x = _object[6].rc.right + 20;
		}
		//���� ����.
		if (temp.right - temp.left < temp.bottom - temp.top && _player->_player.rc.right < temp.left + 50)
		{
			_player->_player.x = _object[6].rc.left - 20;
		}
	}
	//ȭ��ٱ� ����
	{
		if (_player->_player.rc.left < 0)
		{
			_player->_player.x = 30;
		}
		if (_player->_player.rc.right > 2520)
		{
			_player->_player.x = 2490;
		}
	}

	//=============================
	//        ���� �浹
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
		for (int j = 3; j < 7; j++)
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
		//���� ���������� ������ �����������ϱ�
		for (int j = 7; j < 15; j++)
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
			if (dd.left > 2420)
			{
				_mm->getVNormalTree()[i]->getTagMonster()->x = 2470;
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

	//��Ż
	if (IntersectRect(&temp, &_player->_player.rc, &_object[15].rc))
	{
		if (_isALLDEAD)
		{
			_portalToggle = true;

			if (KEYMANAGER->isOnceKeyDown('F'))
			{
				SCENEMANAGER->changeScene("������1");
			}
		}
	}

	CAMERAMANAGER->updateScreen(_player->_player.x, _player->_player.y, _startX, _startY, _endX, _endY);

	_portalAni->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
}

void stage5::render()
{
	//=====================================================

	CAMERAMANAGER->ui(_backGround, getMemDC(), 0, 0);

	_map1->render(getMemDC(), 0, 0);

	_portalImg->aniRender(getMemDC(), 980, 1890, _portalAni);

	_mm->render();
	_player->render();
	_pu->playerHPrender(getMemDC(), _player->_player.x, _player->_player.y);

	if (_portalToggle)
	{
		_portalToggleImg->render(getMemDC(), 1030, 2360);
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
	//Rectangle(getMemDC(), _object[11].rc);
	//Rectangle(getMemDC(), _object[12].rc);
	//Rectangle(getMemDC(), _object[13].rc);
	//Rectangle(getMemDC(), _object[14].rc);
	//Rectangle(getMemDC(), _object[15].rc);

	//====================================================

	CAMERAMANAGER->fadeIn(getMemDC());
}