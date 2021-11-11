#include "stdafx.h"
#include "stage6.h"

//===========================
//		   보스존 1
//===========================

HRESULT stage6::init()
{
	_player = new player;
	_player->init();

	_bs = new Boss;
	_bs->init();

	_pu = new PlayerUI;
	_pu->init();


	CAMERAMANAGER->fadeIn_Init();

	//이미지 불러오기
	IMAGEMANAGER->addImage("stage6_backGround", "image/stage6_backGround.bmp", 2880, 1512, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("stage6_backbackGround", "image/boss_backGround.bmp", 1280, 720, true, RGB(255, 0, 255));

	_map1 = IMAGEMANAGER->findImage("stage6_backGround");
	_background = IMAGEMANAGER->findImage("stage6_backbackGround");

	//object[0~10]은 지형object
	//0~2 ground
	_object[0].x = 0;
	_object[0].y = 1241;

	//스폰 위치
	_player->_player.x = 1440;
	_player->_player.y = 1137;

	//처음 랜딩상태
	_player->_isLanding = false;

	//카메라 제한(초기화)
	_startX = 0;
	_startY = 0;
	_endX = 2880;
	_endY = 1512;

	return S_OK;
}

void stage6::release()
{
}

void stage6::update()
{
	_object[0].rc = RectMake(_object[0].x, _object[0].y, 2880, 272);

	_player->update();
	_bs->update();
	_pu->update();

	_pu->hpCalcul(_player->_hp);
	_pu->BosshpCalcul(_bs->getTagBoss()->hp);

	RECT temp;
	RECT boss_attackScale = _bs->getTagBoss()->scale_rc;
	if (IntersectRect(&temp, &boss_attackScale, &_player->_player.rc))
	{
		_player->_hp -= 3;
	}

	//보스타격여부
	_bs->getTagBoss()->isHit = false;

	RECT boss_head = _bs->getTagBoss()->head_rc;
	RECT boss_body = _bs->getTagBoss()->body_rc;
	RECT boss_leftHand = _bs->getTagBoss()->leftHand_rc;
	RECT boss_rightHand = _bs->getTagBoss()->rightHand_rc;
	if (IntersectRect(&temp, &boss_head, &_player->_player_attack.rc))
	{
		_bs->getTagBoss()->isHit = true;
		_bs->getTagBoss()->hp -= 0.3f;
	}
	else if (IntersectRect(&temp, &boss_body, &_player->_player_attack.rc))
	{
		_bs->getTagBoss()->isHit = true;
		_bs->getTagBoss()->hp -= 0.3f;
	}
	else if (IntersectRect(&temp, &boss_leftHand, &_player->_player_attack.rc))
	{
		_bs->getTagBoss()->isHit = true;
		_bs->getTagBoss()->hp -= 0.3f;
	}
	else if (IntersectRect(&temp, &boss_rightHand, &_player->_player_attack.rc))
	{
		_bs->getTagBoss()->isHit = true;
		_bs->getTagBoss()->hp -= 0.3f;
	}

	//=============================
	//       오브젝트 충돌
	//=============================
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
	//보스몸통 rect와 충돌
	RECT boss_body1 = _bs->getTagBoss()->body1_rc;
	RECT boss_body2 = _bs->getTagBoss()->body2_rc;
	if (IntersectRect(&temp, &_player->_player.rc, &boss_body1))
	{
		//지형 위쪽.
		if (temp.right - temp.left > temp.bottom - temp.top && _player->_player.rc.bottom - 35 < temp.top
			&& _player->_jumpPower < 0)
		{
			if (_player->_isFall)
			{
				_player->_isLanding = true;
				_player->_jumpPower = 0;
				_player->_player.y = boss_body1.top - 45;
			}
		}
	}
	if (IntersectRect(&temp, &_player->_player.rc, &boss_body2))
	{
		//지형 위쪽.
		if (temp.right - temp.left > temp.bottom - temp.top && _player->_player.rc.bottom - 35 < temp.top
			&& _player->_jumpPower < 0)
		{
			if (_player->_isFall)
			{
				_player->_isLanding = true;
				_player->_jumpPower = 0;
				_player->_player.y = boss_body2.top - 45;
			}
		}
	}

	CAMERAMANAGER->updateScreen(_player->_player.x, _player->_player.y, _startX, _startY, _endX, _endY);
}

void stage6::render()
{
	//=====================================================

	CAMERAMANAGER->ui(_background, getMemDC(), 0, 0);

	_map1->render(getMemDC(), 0, 0);

	_bs->render();
	_player->render();
	_pu->playerHPrender(getMemDC(), _player->_player.x, _player->_player.y);
	_pu->bossHPrender(getMemDC(), _player->_player.x, _player->_player.y, _isBoss, _bs->getTagBoss()->hp*7.98f);


	//object TEST
	//Rectangle(getMemDC(), _object[0].rc);

	//====================================================

	CAMERAMANAGER->fadeIn(getMemDC());
}
