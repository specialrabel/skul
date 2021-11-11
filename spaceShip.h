#pragma once
#include "gameNode.h"
#include "bullets.h"
#include "progressBar.h"

#pragma warning(disable:4996)

//1. 컴파일러 무한루프를 빠져나오기 위해
//2. 빌드속도를 높이기 위해
//상호참조를 위한 클라스 전방선언
class enemyManager;

class spaceShip : public gameNode
{
private:
	image* _ship;
	missile* _missile;
	hyunMoo* _hm;

	//얘도 지금은 빈껍데기임
	enemyManager* _em;

	progressBar* _hpBar;
	float _currentHP, _maxHP;

	int _alphaValue;

public:
	spaceShip();
	~spaceShip();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	//충돌함슈
	void collision();

	//플레이어 피통을 깍아줍시다
	void hitDamage(float damage);

	//이름이 모옵시 그럴듯한 설정자 함수
	void setEmMemoryAddressLink(enemyManager* em) { _em = em; }

	//현무에 대한 접근자
	hyunMoo* getHyunMoo() { return _hm; }

	//스페이스쉽 이미지에 대한 접근자
	image* getShipImage() { return _ship; }

};

