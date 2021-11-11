#include "stdafx.h"
#include "stage4.h"

//===========================
//		 �̴Ͼ��� 2-1
//===========================

HRESULT stage4::init()
{
	_player = new player;
	_player->init();

	_mm = new MonsterManager;
	_mm->SetMonster(4);

	_pu = new PlayerUI;
	_pu->init();

	CAMERAMANAGER->fadeIn_Init();

	//�̹��� �ҷ�����
	_rightPortalOpenImg = IMAGEMANAGER->addImage("openPortal_RIGHT", "image/stage3_portalLeftOpen.bmp", 3328, 280, true, RGB(255, 0, 255));

	_rightPortalOpenAni = new animation;
	_rightPortalOpenAni->init(_rightPortalOpenImg->getWidth(), _rightPortalOpenImg->getHeight(), 416, 280);
	_rightPortalOpenAni->setPlayFrame(0, 8, false, true);
	_rightPortalOpenAni->setFPS(1.7f);

	_rightPortalOpenAni->start();

	//�̹��� �ҷ�����
	IMAGEMANAGER->addImage("stage4_backGround", "image/stage4_backGround.bmp", 2952, 2016, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("stage4_portalClose", "image/stage4_portalClose.bmp", 799, 276, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("stage4_portalToggle", "image/Fbutton.bmp", 450, 48, true, RGB(15, 39, 39));
	IMAGEMANAGER->addImage("stage4_backbackGround", "image/stage_backGround2.bmp", 1280, 720, true, RGB(255, 0, 255));


	_map1 = IMAGEMANAGER->findImage("stage4_backGround");
	_portalClose = IMAGEMANAGER->findImage("stage4_portalClose");
	_portalToggleImg = IMAGEMANAGER->findImage("stage4_portalToggle");
	_backGround = IMAGEMANAGER->findImage("stage4_backbackGround");

	//object[0~10]�� ����object
	//0~2 ground
	_object[0].x = 0;
	_object[0].y = 1810;
	_object[1].x = 1520;
	_object[1].y = 1595;
	//2~11 ceiling
	_object[2].x = 2530;
	_object[2].y = 0;
	_object[3].x = 2320;
	_object[3].y = 0;
	_object[4].x = 2170;
	_object[4].y = 0;
	_object[5].x = 2100;
	_object[5].y = 0;
	_object[6].x = 0;
	_object[6].y = 0;
	_object[7].x = 202;
	_object[7].y = 0;
	_object[8].x = 663;
	_object[8].y = 0;
	_object[9].x = 738;
	_object[9].y = 0;
	_object[10].x = 915;
	_object[10].y = 0;
	_object[11].x = 1062;
	_object[11].y = 0;
	//12~14 airGround
	_object[12].x = 947;
	_object[12].y = 1365;
	_object[13].x = 1378;
	_object[13].y = 1155;
	_object[14].x = 1164;
	_object[14].y = 866;
	//15~19 �������°� ���¿�
	_object[15].x = 1520;
	_object[15].y = 1395;
	_object[16].x = 1650;
	_object[16].y = 1178;
	_object[17].x = 1358;
	_object[17].y = 963;
	_object[18].x = 1144;
	_object[18].y = 674;
	_object[19].x = 1564;
	_object[19].y = 674;
	_object[20].x = 830;
	_object[20].y = 1620;


	//���� ��ġ
	_player->_player.x = 300;
	_player->_player.y = 1750;
	//ó�� ��������
	_player->_isLanding = false;
	//ī�޶� ����(�ʱ�ȭ)
	_startX = 0;
	_startY = 0;
	_endX = 2952;
	_endY = 2016;

	return S_OK;
}

void stage4::release()
{

}

void stage4::update()
{
	_object[0].rc = RectMake(_object[0].x, _object[0].y, 1520, 720);
	_object[1].rc = RectMake(_object[1].x, _object[1].y, 1010, 720);
	_object[2].rc = RectMake(_object[2].x, _object[2].y, 422, 2016);
	_object[3].rc = RectMake(_object[3].x, _object[3].y, 210, 1210);
	_object[4].rc = RectMake(_object[4].x, _object[4].y, 150, 1135);
	_object[5].rc = RectMake(_object[5].x, _object[5].y, 70, 1060);
	_object[6].rc = RectMake(_object[6].x, _object[6].y, 202, 1054);
	_object[7].rc = RectMake(_object[7].x, _object[7].y, 462, 989);
	_object[8].rc = RectMake(_object[8].x, _object[8].y, 76, 1199);
	_object[9].rc = RectMake(_object[9].x, _object[9].y, 178, 1273);
	_object[10].rc = RectMake(_object[10].x, _object[10].y, 148, 696);
	_object[11].rc = RectMake(_object[11].x, _object[11].y, 75, 263);
	_object[12].rc = RectMake(_object[12].x, _object[12].y, 698, 18);
	_object[13].rc = RectMake(_object[13].x, _object[13].y, 700, 20);
	_object[14].rc = RectMake(_object[14].x, _object[14].y, 412, 19);
	_object[15].rc = RectMake(_object[15].x, _object[15].y, 20, 200);
	_object[16].rc = RectMake(_object[16].x, _object[16].y, 20, 200);
	_object[17].rc = RectMake(_object[17].x, _object[17].y, 20, 200);
	_object[18].rc = RectMake(_object[18].x, _object[18].y, 20, 200);
	_object[19].rc = RectMake(_object[19].x, _object[19].y, 20, 200);
	_object[20].rc = RectMake(_object[20].x, _object[20].y, 155, 200);
	

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
	//ceiling ���� ��
	for (int i = 3; i < 12; i++)
	{
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
	//airGround ���� ��
	for (int i = 12; i < 15; i++)
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
	//ȭ��ٱ� ����
	{
		if (_player->_player.rc.left < 0)
		{
			_player->_player.x = 30;
		}
		if (_player->_player.rc.right > 2952)
		{
			_player->_player.x = 2922;
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
		for (int j = 12; j < 15; j++)
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
		for (int j = 3; j < 12; j++)
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
		for (int j = 15; j < 20; j++)
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
			if (dd.left > 2852)
			{
				_mm->getVNormalTree()[i]->getTagMonster()->x = 2902;
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
	if (IntersectRect(&temp, &_player->_player.rc, &_object[20].rc))
	{
		if (_isALLDEAD)
		{
			_portalToggle = true;

			if (KEYMANAGER->isOnceKeyDown('F'))
			{
				SCENEMANAGER->changeScene("�̴Ͼ���2-2");
			}
		}
	}

	_rightPortalOpenAni->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
	CAMERAMANAGER->updateScreen(_player->_player.x, _player->_player.y, _startX, _startY, _endX, _endY);
}

void stage4::render()
{
	//=====================================================

	CAMERAMANAGER->ui(_backGround, getMemDC(), 0, 0);

	_map1->render(getMemDC(), 0, 0);
	_portalClose->render(getMemDC(), 300, 1563);
	if (_isALLDEAD) {
		_rightPortalOpenImg->aniRender(getMemDC(), 703, 1550, _rightPortalOpenAni);
	}

	_mm->render();
	_player->render();
	_pu->playerHPrender(getMemDC(), _player->_player.x, _player->_player.y);

	if (_portalToggle)
	{
		_portalToggleImg->render(getMemDC(), 683, 1865);
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
	//Rectangle(getMemDC(), _object[16].rc);
	//Rectangle(getMemDC(), _object[17].rc);
	//Rectangle(getMemDC(), _object[18].rc);
	//Rectangle(getMemDC(), _object[19].rc);
	//Rectangle(getMemDC(), _object[20].rc);

	//====================================================

	CAMERAMANAGER->fadeIn(getMemDC());
}