#include "stdafx.h"
#include "monster.h"

HRESULT monster::init(const char* imageName, POINT position)
{
	IMAGEMANAGER->addFrameImage("NormalTree_IDLE", "image/MINION1_IDLE.bmp", 2250, 500, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("NormalTree_WALK", "image/MINION1_WALKTEST.bmp", 1500, 500, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("NormalTree_DAMAGE", "image/MINION1_DAMAGE.bmp", 500, 500, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("NormalTree_ATTACK", "image/MINION1_ATTACK.bmp", 1000, 500, 4, 2, true, RGB(255, 0, 255));

	_monster.currentFrameX, _monster.currentFrameY = 0;

	_monster.imageName = IMAGEMANAGER->findImage(imageName);

	_monster.x = position.x;
	_monster.y = position.y;

	if(imageName == "NormalTree_IDLE")
	{
		_monster.rc = RectMakeCenter(position.x-5, position.y+5, 90, 140);
	}

	//초기값
	_monster.hp = 50;
	_monster.speed = 3.7f;
	_monster.gravity = 0.8f;
	_monster.jumpPower = 0;

	//감지범위
	_monster.find = 0;
	_monster.sencer_rcL_W = 300;
	_monster.sencer_rcL_H = 100;
	_monster.sencer_rcR_W = 300;
	_monster.sencer_rcR_H = 100;
	_monster.sencer_rcA_W = 100;
	_monster.sencer_rcA_H = 300;


	return S_OK;
}

HRESULT monster::init()
{
	return S_OK;
}

void monster::update()
{
	//점프는 없지만..(상시중력적용을 위해)
	_monster.jumpPower -= _monster.gravity;
	_monster.y -= _monster.jumpPower;

	_monster.count++;
	_monster.time++;

	_monster.random = RND->getFromIntTo(30, 70);

	{
		if (_monster.dir == IDLE) // 랜덤에서 0을 받았을때
		{
			_monster.currentFrameY = 0;
			_monster.imageName = IMAGEMANAGER->findImage("NormalTree_IDLE");
			_monster.x -= 0; 

			if (_monster.count % 10 == 0)
			{
				if (_monster.currentFrameX > _monster.imageName->getMaxFrameX()) { _monster.currentFrameX = 0; }
				_monster.imageName->setFrameX(_monster.currentFrameX);
				_monster.currentFrameX++;

				_monster.count = 0;
			}
		}
		else if (_monster.dir == RIGHT && !_monster.hit && !_monster.attack) // 랜덤에서 1을 받았을때
		{
			_monster.currentFrameY = 0;
			_monster.imageName = IMAGEMANAGER->findImage("NormalTree_WALK");
			_monster.x += _monster.speed;

			if (_monster.count % 10 == 0)
			{
				if (_monster.currentFrameX > _monster.imageName->getMaxFrameX()) { _monster.currentFrameX = 0; }
				_monster.imageName->setFrameX(_monster.currentFrameX);
				_monster.currentFrameX++;

				_monster.count = 0;
			}
		}
		else if (_monster.dir == LEFT && !_monster.hit && !_monster.attack) // 랜덤에서 2를 받았을때
		{
			_monster.currentFrameY = 1;
			_monster.imageName = IMAGEMANAGER->findImage("NormalTree_WALK");
			_monster.x -= _monster.speed;

			if (_monster.count % 10 == 0)
			{
				if (_monster.currentFrameX > _monster.imageName->getMaxFrameX()) { _monster.currentFrameX = 0; }
				_monster.imageName->setFrameX(_monster.currentFrameX);
				_monster.currentFrameX++;

				_monster.count = 0;
			}
		}
		else if (_monster.dir == RIGHT && _monster.hit )
		{
			_monster.currentFrameY = 0;
			_monster.imageName = IMAGEMANAGER->findImage("NormalTree_DAMAGE");
			_monster.x -= _monster.speed;

			if (_monster.count % 10 == 0)
			{
				if (_monster.currentFrameX > _monster.imageName->getMaxFrameX()) { _monster.currentFrameX = 0; }
				_monster.imageName->setFrameX(_monster.currentFrameX);
				_monster.currentFrameX++;

				_monster.count = 0;
			}
			if (_monster.time > 10)
			{
				IMAGEMANAGER->findImage("NormalTree_IDLE");
				_monster.hit = false;
			}
		}
		else if (_monster.dir == LEFT && _monster.hit )
		{
			_monster.currentFrameY = 1;
			_monster.imageName = IMAGEMANAGER->findImage("NormalTree_DAMAGE");
			_monster.x += _monster.speed;

			if (_monster.count % 10 == 0)
			{
				if (_monster.currentFrameX > _monster.imageName->getMaxFrameX()-1) { _monster.currentFrameX = -1; }
				_monster.imageName->setFrameX(_monster.currentFrameX);
				_monster.currentFrameX++;

				_monster.count = 0;
			}
			if (_monster.time > 10)
			{
				IMAGEMANAGER->findImage("NormalTree_IDLE");
				_monster.hit = false;
			}
		}
		else if (_monster.dir == RIGHT && _monster.attack)
		{
			_monster.currentFrameY = 0;
			_monster.imageName = IMAGEMANAGER->findImage("NormalTree_ATTACK");

			if (_monster.count % 10 == 0)
			{
				if (_monster.currentFrameX > _monster.imageName->getMaxFrameX()-1) { _monster.currentFrameX = -1; }
				_monster.imageName->setFrameX(_monster.currentFrameX);
				_monster.currentFrameX++;

				_monster.count = 0;
			}

			//프레임에 따른 렉트범위
			if (_monster.currentFrameX == 0)
			{
				_monster.monster1_attack_rc_x = _monster.x;
				_monster.monster1_attack_rc_y = _monster.y;
				_monster.monster1_attack_rc_W = 0;
				_monster.monster1_attack_rc_H = 0;
			}
			if (_monster.currentFrameX == 1)
			{
				_monster.monster1_attack_rc_x = _monster.x + 40;
				_monster.monster1_attack_rc_y = _monster.y + 70;
				_monster.monster1_attack_rc_W = 100;
				_monster.monster1_attack_rc_H = 30;
			}
			if (_monster.currentFrameX == 2)
			{
				_monster.monster1_attack_rc_x = _monster.x;
				_monster.monster1_attack_rc_y = _monster.y;
				_monster.monster1_attack_rc_W = 0;
				_monster.monster1_attack_rc_H = 0;
			}
			if (_monster.currentFrameX == 3)
			{
				_monster.monster1_attack_rc_x = _monster.x;
				_monster.monster1_attack_rc_y = _monster.y;
				_monster.monster1_attack_rc_W = 0;
				_monster.monster1_attack_rc_H = 0;
			}
		}
		else if (_monster.dir == LEFT && _monster.attack)
		{
			_monster.currentFrameY = 1;
			_monster.imageName = IMAGEMANAGER->findImage("NormalTree_ATTACK");

			if (_monster.count % 10 == 0)
			{
				if (_monster.currentFrameX > _monster.imageName->getMaxFrameX()-1) { _monster.currentFrameX = -1; }
				_monster.imageName->setFrameX(_monster.currentFrameX);
				_monster.currentFrameX++;

				_monster.count = 0;
			}

			//프레임에 따른 타격범위
			if (_monster.currentFrameX == 0)
			{
				_monster.monster1_attack_rc_x = _monster.x;
				_monster.monster1_attack_rc_y = _monster.y;
				_monster.monster1_attack_rc_W = 0;
				_monster.monster1_attack_rc_H = 0;
			}
			if (_monster.currentFrameX == 1)
			{
				_monster.monster1_attack_rc_x = _monster.x -40;
				_monster.monster1_attack_rc_y = _monster.y +70;
				_monster.monster1_attack_rc_W = 100;
				_monster.monster1_attack_rc_H = 30;
			}
			if (_monster.currentFrameX == 2)
			{
				_monster.monster1_attack_rc_x = _monster.x;
				_monster.monster1_attack_rc_y = _monster.y;
				_monster.monster1_attack_rc_W = 0;
				_monster.monster1_attack_rc_H = 0;
			}
			if (_monster.currentFrameX == 3)
			{
				_monster.monster1_attack_rc_x = _monster.x;
				_monster.monster1_attack_rc_y = _monster.y;
				_monster.monster1_attack_rc_W = 0;
				_monster.monster1_attack_rc_H = 0;
			}
			if (_monster.currentFrameX == 4)
			{
				_monster.monster1_attack_rc_x = _monster.x;
				_monster.monster1_attack_rc_y = _monster.y;
				_monster.monster1_attack_rc_W = 0;
				_monster.monster1_attack_rc_H = 0;
			}

		}

		//방향 랜덤값 받기
		if (_monster.time >= _monster.random && _monster.currentFrameX == _monster.imageName->getMaxFrameX())
		{
			_monster.dir = RND->getFromIntTo(0, 3);
			_monster.currentFrameX = 0;
			_monster.time = 0;
		}

		//몬스터범위 계속 업데이트
		_monster.rc = RectMakeCenter(_monster.x - 5, _monster.y + 5, 90, 140);
		_monster.sencer_rcL = RectMakeCenter(_monster.x-300, _monster.y, _monster.sencer_rcL_W, _monster.sencer_rcL_H);
		_monster.sencer_rcR = RectMakeCenter(_monster.x + 300, _monster.y, _monster.sencer_rcR_W, _monster.sencer_rcR_H);
		_monster.sencer_rcA = RectMakeCenter(_monster.x, _monster.y, _monster.sencer_rcA_W, _monster.sencer_rcA_H);
		_monster.monster1_attack_rc = RectMakeCenter(_monster.monster1_attack_rc_x, _monster.monster1_attack_rc_y, _monster.monster1_attack_rc_W, _monster.monster1_attack_rc_H);
	}
}

void monster::release()
{
}

void monster::render()
{
	Rectangle(getMemDC(), _monster.rc);
	Rectangle(getMemDC(), _monster.sencer_rcL);
	Rectangle(getMemDC(), _monster.sencer_rcR);
	Rectangle(getMemDC(), _monster.sencer_rcA);
	Rectangle(getMemDC(), _monster.monster1_attack_rc);

	_monster.imageName->frameRender(getMemDC(), _monster.x - _monster.imageName->getFrameWidth() / 2 , 
									_monster.y - _monster.imageName->getFrameHeight()/2, 
									_monster.currentFrameX, _monster.currentFrameY);


	//char str1[128];
	//sprintf_s(str1, "currentFrameX : %d", _monster.currentFrameX);
	//TextOut(getMemDC(), _monster.rc.right, _monster.rc.top, str1, strlen(str1));

	//sprintf_s(str1, "Monster Hp : %d", _monster.hp);
	//TextOut(getMemDC(), _monster.rc.right, _monster.rc.top + 20, str1, strlen(str1));

	//sprintf_s(str1, "isHit : %d", _monster.hit);
	//TextOut(getMemDC(), _monster.rc.right, _monster.rc.top + 40, str1, strlen(str1));

	//sprintf_s(str1, "isAttack : %d", _monster.attack);
	//TextOut(getMemDC(), _monster.rc.right, _monster.rc.top + 60, str1, strlen(str1));

	//sprintf_s(str1, "direction : %d", _monster.dir);
	//TextOut(getMemDC(), _monster.rc.right, _monster.rc.top + 80, str1, strlen(str1));
}
