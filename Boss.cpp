#include "stdafx.h"
#include "Boss.h"

Boss::Boss()
{
}

Boss::~Boss()
{
}

HRESULT Boss::init()
{
	IMAGEMANAGER->addImage("BOSS_HEAD", "image/BOSS_HEAD.bmp", 482, 336, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BOSS_HEAD2", "image/BOSS_HEAD2.bmp", 336, 490, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BOSS_BODY", "image/BOSS_BODY.bmp", 836, 682, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BOSS_LEFTHAND", "image/BOSS_LEFTHAND.bmp", 328, 294, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BOSS_LEFTHAND2", "image/BOSS_LEFTHAND2.bmp", 384, 224, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BOSS_LEFTHAND3", "image/BOSS_LEFTHAND3.bmp", 348, 302, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BOSS_RIGHTHAND", "image/BOSS_RIGHTHAND.bmp", 328, 294, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BOSS_RIGHTHAND2", "image/BOSS_RIGHTHAND2.bmp", 384, 224, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BOSS_RIGHTHAND3", "image/BOSS_RIGHTHAND3.bmp", 348, 302, true, RGB(255, 0, 255));

	_boss.head_image = IMAGEMANAGER->findImage("BOSS_HEAD"); 
	_boss.body_image = IMAGEMANAGER->findImage("BOSS_BODY");
	_boss.leftHand_image = IMAGEMANAGER->findImage("BOSS_LEFTHAND2");
	_boss.rightHand_image = IMAGEMANAGER->findImage("BOSS_RIGHTHAND2");

	IMAGEMANAGER->addImage("BOSS_HEAD_HIT", "image/BOSS_HEAD_HIT.bmp", 482, 336, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BOSS_HEAD2_HIT", "image/BOSS_HEAD2_HIT.bmp", 336, 490, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BOSS_BODY_HIT", "image/BOSS_BODY_HIT.bmp", 836, 682, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BOSS_LEFTHAND_HIT", "image/BOSS_LEFTHAND_HIT.bmp", 328, 294, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BOSS_LEFTHAND2_HIT", "image/BOSS_LEFTHAND2_HIT.bmp", 384, 224, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BOSS_LEFTHAND3_HIT", "image/BOSS_LEFTHAND3_HIT.bmp", 348, 302, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BOSS_RIGHTHAND_HIT", "image/BOSS_RIGHTHAND_HIT.bmp", 328, 294, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BOSS_RIGHTHAND2_HIT", "image/BOSS_RIGHTHAND2_HIT.bmp", 384, 224, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BOSS_RIGHTHAND3_HIT", "image/BOSS_RIGHTHAND3_HIT.bmp", 348, 302, true, RGB(255, 0, 255));

	//공격범위 초기값
	_boss.scale_x = 0;
	_boss.scale_y = 0;
	_boss.scale_width = 0;
	_boss.scale_height = 0;

	//머리부분 타격범위
	_boss.head_x = 1550;
	_boss.head_y = 1100;
	_boss.head_width = 482;
	_boss.head_height = 386;

	//몸부분 타격범위
	_boss.body_x = 1000;
	_boss.body_y = 550;
	_boss.body_width = 836;
	_boss.body_height = 682;

	//왼손부분 타격범위
	_boss.leftHand_x = 1050;
	_boss.leftHand_y = 1150;
	_boss.leftHand_width = 384;
	_boss.leftHand_height = 224;

	//오른손부분 타격범위
	_boss.rightHand_x = 1890;
	_boss.rightHand_y = 1150;
	_boss.rightHand_width = 384;
	_boss.rightHand_height = 224;

	//보스몸통 착지가능한 부분
	_boss.body1_x = 1290;
	_boss.body1_y = 1030;
	_boss.body1_width = 150;
	_boss.body1_height = 30;

	_boss.body2_x = 1610;
	_boss.body2_y = 970;
	_boss.body2_width = 150;
	_boss.body2_height = 30;

	//idle상태일때의 시간카운트를 위한 초기값
	_boss.IDLE_COUNT = 0;
	
	//패턴초기화
	_boss.pattern = IDLESTATE;

	//보스 체력
	_boss.hp = 100;

	return S_OK;
}

void Boss::release()
{
}

void Boss::update()
{
	++_boss.time;
	++_boss.hitCount;

	//idle 상태일때 (공격범위 0)
	if (_boss.pattern == IDLESTATE)
	{
		if (_boss.time >= 0 && _boss.time < 50)
		{
			_boss.head_y += 0.4f;
		}
		else if (_boss.time >= 50 && _boss.time < 100)
		{
			_boss.head_y -= 0.4f;
		}
		else if (_boss.time >= 100)
		{
			_boss.time = 0;
			_boss.IDLE_COUNT += 1;
		}

		//숨쉬기 몇번하고 패턴넘어갈건지
		if (_boss.IDLE_COUNT >= 2)
		{
			_boss.pattern = RIGHTATTACK;
			_boss.IDLE_COUNT = 0;
			_boss.time = 0;

			//나름 초기화?
			_boss.LEFTHAND_SPEED = 4.3f;
			_boss.LEFTHAND_SPEEDPOWER = 1.6f;
			_boss.LPATTERN_COUNT = 0;

			_boss.RIGHTHAND_SPEED = 4.3f;
			_boss.RIGHTHAND_SPEEDPOWER = 1.6f;
			_boss.RPATTERN_COUNT = 0;

			_boss.HPATTERN_COUNT = 0;
			_boss.HEAD_TIMECOUNT = 0;
			_boss.HEAD_SPEED = 8.3f;
			_boss.HEAD_SPEEDPOWER = 0.4f;

			_boss.SPATTERN_COUNT = 0;
			_boss.S_LHAND_SPEED = 4.3f;
			_boss.S_LHAND_SPEEDPOWER = 1.6f;
			_boss.S_RHAND_SPEED = 4.3f;
			_boss.S_RHAND_SPEEDPOWER = 1.6f;
			_boss.STAMP_TIMECOUNT = 0;
		}
	}
	//왼쪽에서 오른쪽으로 쓸어담을 때
	if (_boss.pattern == RIGHTATTACK)
	{
		if (_boss.LPATTERN_COUNT == 0)
		{
			if (_boss.HEAD_SPEED > 0)
			{
				_boss.HEAD_SPEED -= _boss.HEAD_SPEEDPOWER;
				_boss.head_x -= _boss.HEAD_SPEED;
			}

			_boss.leftHand_x -= 15.0f;
			if (_boss.leftHand_x < 0)
			{
				_boss.LPATTERN_COUNT = 1;
			}
		}

		if (_boss.LPATTERN_COUNT == 1)
		{
			if (_boss.head_x < 1690)
			{
				_boss.HEAD_SPEED -= _boss.HEAD_SPEEDPOWER;
				_boss.head_x -= _boss.HEAD_SPEED;
			}

			_boss.scale_x = _boss.leftHand_x + 100;
			_boss.scale_y = _boss.leftHand_y;
			_boss.scale_width = _boss.leftHand_width -300;
			_boss.scale_height = _boss.leftHand_height;

			_boss.leftHand_image = IMAGEMANAGER->findImage("BOSS_LEFTHAND3");

			_boss.LEFTHAND_SPEED += _boss.LEFTHAND_SPEEDPOWER;
			_boss.leftHand_x += _boss.LEFTHAND_SPEED;

			if (_boss.leftHand_x > 2800)
			{
				_boss.LPATTERN_COUNT = 2;
			}
		}

		if (_boss.LPATTERN_COUNT == 2)
		{
			if (_boss.head_x > 1550)
			{
				_boss.head_x -= 3.0f;
			}

			_boss.scale_x = 0;
			_boss.scale_y = 0;
			_boss.scale_width = 0;
			_boss.scale_height = 0;

			_boss.leftHand_image = IMAGEMANAGER->findImage("BOSS_LEFTHAND2");

			_boss.leftHand_x -= 20;
			
			if (_boss.leftHand_x <= 1050)
			{
				_boss.leftHand_x = 1050;
				_boss.LPATTERN_COUNT = 0;
				_boss.pattern = LEFTATTACK;

				_boss.HEAD_SPEED = 8.3f;
				_boss.HEAD_SPEEDPOWER = 0.4f;
			}
		}
	}
	//오른쪽에서 왼쪽으로 쓸어담을 때
	if (_boss.pattern == LEFTATTACK)
	{
		if (_boss.RPATTERN_COUNT == 0)
		{
			if (_boss.HEAD_SPEED > 0)
			{
				_boss.HEAD_SPEED -= _boss.HEAD_SPEEDPOWER;
				_boss.head_x += _boss.HEAD_SPEED;
			}

			_boss.rightHand_x += 15.0f;

			if (_boss.rightHand_x > 2800)
			{
				_boss.RPATTERN_COUNT = 1;
			}
		}

		if (_boss.RPATTERN_COUNT == 1)
		{
			if (_boss.head_x > 1480)
			{
				_boss.HEAD_SPEED -= _boss.HEAD_SPEEDPOWER;
				_boss.head_x += _boss.HEAD_SPEED;
			}

			_boss.scale_x = _boss.rightHand_x - 100;
			_boss.scale_y = _boss.rightHand_y;
			_boss.scale_width = _boss.rightHand_width - 300;
			_boss.scale_height = _boss.rightHand_height;

			_boss.rightHand_image = IMAGEMANAGER->findImage("BOSS_RIGHTHAND3");

			_boss.RIGHTHAND_SPEED -= _boss.RIGHTHAND_SPEEDPOWER;
			_boss.rightHand_x += _boss.RIGHTHAND_SPEED;

			if (_boss.rightHand_x < 0)
			{
				_boss.RPATTERN_COUNT = 2;
			}
		}

		if (_boss.RPATTERN_COUNT == 2)
		{
			if (_boss.head_x < 1550)
			{
				_boss.head_x += 3.0f;
			}

			_boss.scale_x = 0;
			_boss.scale_y = 0;
			_boss.scale_width = 0;
			_boss.scale_height = 0;

			_boss.rightHand_image = IMAGEMANAGER->findImage("BOSS_RIGHTHAND2");

			_boss.rightHand_x += 20;

			if (_boss.rightHand_x >= 1890)
			{
				_boss.rightHand_x = 1890;
				_boss.RPATTERN_COUNT = 0;
				_boss.pattern = HEADATTACK;

				_boss.HEAD_SPEED = 8.3f;
				_boss.HEAD_SPEEDPOWER = 0.4f;
			}
		}
	}
	//머리를 땅에 내려찍을 때
	if (_boss.pattern == HEADATTACK)
	{
		++_boss.HEAD_TIMECOUNT;

		if (_boss.HPATTERN_COUNT == 0)
		{
			_boss.head_image = IMAGEMANAGER->findImage("BOSS_HEAD2");

			if (_boss.head_y < 1300)
			{
				_boss.head_x -= 2;
				_boss.head_y += 3;
			}

			if (_boss.head_y >= 1300)
			{
				_boss.scale_x = 0;
				_boss.scale_y = 1230;
				_boss.scale_width = 4800;
				_boss.scale_height = 10;

				_boss.head_y = 1300;

				if (_boss.HEAD_TIMECOUNT > 80)
				{
					_boss.scale_x = 0;
					_boss.scale_y = 0;
					_boss.scale_width = 0;
					_boss.scale_height = 0;
				}

				if (_boss.HEAD_TIMECOUNT > 200)
				{
					_boss.HPATTERN_COUNT = 1;
				}
			}
		}
		if (_boss.HPATTERN_COUNT == 1)
		{
			_boss.head_image = IMAGEMANAGER->findImage("BOSS_HEAD");

			_boss.head_x += 2;
			_boss.head_y -= 3;

			if (_boss.head_y <= 1100)
			{
				_boss.HPATTERN_COUNT = 0;
				_boss.head_y = 1100;
				_boss.pattern = STAMPHAND;
			}
		}
	}
	//양손을 땅에 내려찍을 때
	if (_boss.pattern == STAMPHAND)
	{
		++_boss.STAMP_TIMECOUNT;

		if (_boss.SPATTERN_COUNT == 0)
		{
			_boss.leftHand_y -= 8.0f;
			_boss.rightHand_y -= 8.0f;

			if (_boss.leftHand_y < 100 && _boss.rightHand_y < 100)
			{
				_boss.leftHand_y = 100;
				_boss.rightHand_y = 100;

				_boss.SPATTERN_COUNT = 1;
			}
		}

		if (_boss.SPATTERN_COUNT == 1)
		{
			_boss.S_LHAND_SPEED += _boss.S_LHAND_SPEEDPOWER;
			_boss.leftHand_y += _boss.S_LHAND_SPEED;

			_boss.S_RHAND_SPEED += _boss.S_RHAND_SPEEDPOWER;
			_boss.rightHand_y += _boss.S_RHAND_SPEED;

			if (_boss.leftHand_y >= 1150 && _boss.rightHand_y >= 1150)
			{
				_boss.scale_x = 0;
				_boss.scale_y = 1230;
				_boss.scale_width = 4800;
				_boss.scale_height = 10;

				_boss.leftHand_y = 1150;
				_boss.rightHand_y = 1150;

				if (_boss.STAMP_TIMECOUNT > 170)
				{
					_boss.scale_x = 0;
					_boss.scale_y = 0;
					_boss.scale_width = 0;
					_boss.scale_height = 0;

					_boss.SPATTERN_COUNT = 0;
					_boss.pattern = IDLESTATE;
				}
			}
		}
	}

	//맞았을때
	if (_boss.isHit)
	{
		_boss.head_image = IMAGEMANAGER->findImage("BOSS_HEAD_HIT");
		_boss.body_image = IMAGEMANAGER->findImage("BOSS_BODY_HIT");
		_boss.leftHand_image = IMAGEMANAGER->findImage("BOSS_LEFTHAND2_HIT");
		_boss.rightHand_image = IMAGEMANAGER->findImage("BOSS_RIGHTHAND2_HIT");

		_boss.hitCount = 0;
	}

	//맞은 후 복구
	if (!_boss.isHit && _boss.hitCount == 10)
	{
		_boss.head_image = IMAGEMANAGER->findImage("BOSS_HEAD");
		_boss.body_image = IMAGEMANAGER->findImage("BOSS_BODY");
		_boss.leftHand_image = IMAGEMANAGER->findImage("BOSS_LEFTHAND2");
		_boss.rightHand_image = IMAGEMANAGER->findImage("BOSS_RIGHTHAND2");
	}

	_boss.scale_rc = RectMakeCenter(_boss.scale_x, _boss.scale_y, _boss.scale_width, _boss.scale_height);
	_boss.head_rc = RectMakeCenter(_boss.head_x, _boss.head_y, _boss.head_width, _boss.head_height);
	_boss.head_rc = RectMakeCenter(_boss.body_x, _boss.body_y, _boss.body_width, _boss.body_height);
	_boss.leftHand_rc = RectMakeCenter(_boss.leftHand_x, _boss.leftHand_y, _boss.leftHand_width, _boss.leftHand_height);
	_boss.rightHand_rc = RectMakeCenter(_boss.rightHand_x, _boss.rightHand_y, _boss.rightHand_width, _boss.rightHand_height);
	_boss.body1_rc = RectMakeCenter(_boss.body1_x, _boss.body1_y, _boss.body1_width, _boss.body1_height);
	_boss.body2_rc = RectMakeCenter(_boss.body2_x, _boss.body2_y, _boss.body2_width, _boss.body2_height);
}

void Boss::render()
{
	_boss.body_image->render(getMemDC(), _boss.body_x - (_boss.body_rc.right - _boss.body_rc.left) / 2, _boss.body_y - (_boss.body_rc.bottom - _boss.body_rc.top) / 2);
	_boss.head_image->render(getMemDC(), _boss.head_x - (_boss.head_rc.right-_boss.head_rc.left)/2, _boss.head_y - (_boss.head_rc.bottom - _boss.head_rc.top) / 2);
	_boss.leftHand_image->render(getMemDC(), _boss.leftHand_x - (_boss.leftHand_rc.right - _boss.leftHand_rc.left) / 2, _boss.leftHand_y - (_boss.leftHand_rc.bottom - _boss.leftHand_rc.top) / 2);
	_boss.rightHand_image->render(getMemDC(), _boss.rightHand_x - (_boss.rightHand_rc.right - _boss.rightHand_rc.left) / 2, _boss.rightHand_y - (_boss.rightHand_rc.bottom - _boss.rightHand_rc.top) / 2);

	//Rectangle(getMemDC(), _boss.body_rc);
	//Rectangle(getMemDC(), _boss.leftHand_rc);
	//Rectangle(getMemDC(), _boss.rightHand_rc);
	Rectangle(getMemDC(), _boss.scale_rc);
	//Rectangle(getMemDC(), _boss.body1_rc);
	//Rectangle(getMemDC(), _boss.body2_rc);

	//char str[128];
	//sprintf_s(str, "보스체력 : %f", _boss.hp);
	//TextOut(getMemDC(), 1440, 1000, str, strlen(str));

}
