#include "stdafx.h"
#include "spaceShip.h"
#include "enemyManager.h"
#define _CRT_SECURE_NO_WARNINGS

spaceShip::spaceShip()
{
}


spaceShip::~spaceShip()
{
}

HRESULT spaceShip::init()
{
	_ship = IMAGEMANAGER->addImage("플레이어", "rocket.bmp", 
		52, 64, true, RGB(255, 0, 255));
	_ship->setX(WINSIZEX / 2);
	_ship->setY(WINSIZEY / 2 + 200);

	_missile = new missile;
	_missile->init(30, 400);

	_hm = new hyunMoo;
	_hm->init(3000, WINSIZEY);

	_currentHP = _maxHP = 100;

	_hpBar = new progressBar;
	_hpBar->init(_ship->getX(), _ship->getY() - 20, 52, 10);
	_hpBar->setGauge(_currentHP, _maxHP);

	_alphaValue = 255;


	return S_OK;
}

void spaceShip::release()
{
}

void spaceShip::update()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _ship->getX() > 0)
	{
		_ship->setX(_ship->getX() - 5);
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _ship->getX() + _ship->getWidth() < WINSIZEX)
	{
		_ship->setX(_ship->getX() + 5);
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP) && _ship->getY() > 0)
	{
		_ship->setY(_ship->getY() - 5);
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _ship->getY() + _ship->getHeight() < WINSIZEY)
	{
		_ship->setY(_ship->getY() + 5);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_missile->fire(_ship->getCenterX(), _ship->getCenterY() - 15);
	}

	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		_hm->fire(_ship->getCenterX(), _ship->getCenterY() - 15);
	}

	_missile->update();
	_hm->update();

	//체력바가 스페이스쉽 따라다니라고 이렇게 한 것...
	_hpBar->setX(_ship->getX());
	_hpBar->setY(_ship->getY() - 20);
	_hpBar->setGauge(_currentHP, _maxHP);
	_hpBar->update();

	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		char temp[128];
		vector<string> vStr;

		vStr.push_back(itoa(_currentHP, temp, 10));
		vStr.push_back(itoa(_maxHP, temp, 10));
		vStr.push_back(itoa(_ship->getX(), temp, 10));
		vStr.push_back(itoa(_ship->getY(), temp, 10));

		TXTDATA->txtSave("28기화이팅.txt", vStr);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		vector<string> vStr;
		vStr = TXTDATA->txtLoad("28기화이팅.txt");

		_ship->setX(atoi(vStr[2].c_str()));
		_ship->setY(atoi(vStr[3].c_str()));
		_currentHP = atoi(vStr[0].c_str());
	}
	


	collision();

	_alphaValue--;

	if (_alphaValue <= 0) _alphaValue = 255;


}

void spaceShip::render()
{
	//_ship->render(getMemDC(), _ship->getX(), _ship->getY());
	_ship->alphaRender(getMemDC(), _ship->getX(), _ship->getY(), _alphaValue);
	_missile->render();
	_hm->render();
	_hpBar->render();
}

void spaceShip::collision()
{
	//벡터컨테이너에 
	//reserve()
	//resize()

	//에너미 매니저안에 미니언이 담긴 벡터 사이즈만큼 돕시다 인덱스는 1% 유리합니다
	for (int i = 0; i < _em->getVMinion().size(); i++)
	{
		//현무의 벡터사이즈만큼 돌아서~
		for (int j = 0; j < _hm->getVHyunMoo().size(); j++)
		{
			RECT temp;
			RECT rc = _em->getVMinion()[i]->getRect();

			if (IntersectRect(&temp, &_hm->getVHyunMoo()[j].rc,
				&rc))
			{
				_em->removeMinion(i);
				_hm->removeMissile(j);
				break;
			}
		}
	}
}

void spaceShip::hitDamage(float damage)
{
	_currentHP -= damage;
}

