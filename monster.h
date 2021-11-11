#pragma once
#include "gameNode.h"

enum
{
	IDLE = 0,
	RIGHT,
	LEFT,
};

struct MONSTER
{
	
	RECT rc;
	image* imageName;
	int currentFrameX, currentFrameY;
	int x, y;
	int hp;
	int count;

	float gravity, jumpPower;
	float speed;
	int dir; // 0 idle, 1 right, 2 left
	bool isLanding, isFall;
	bool hit;
	bool attack;

	bool getTime;
	int random, time;

	int find; //찾았는지 못찾았는지, 프레임값 처음만 0주기위해

	RECT sencer_rcL; //왼쪽 감지렉트
	int sencer_rcL_W, sencer_rcL_H;

	RECT sencer_rcR; //오른쪽 감지렉트
	int sencer_rcR_W, sencer_rcR_H;

	RECT sencer_rcA; //중앙 감지렉트
	int sencer_rcA_W, sencer_rcA_H;

	RECT monster1_attack_rc;
	int monster1_attack_rc_x, monster1_attack_rc_y;
	int monster1_attack_rc_W, monster1_attack_rc_H;
};

class monster : public gameNode
{
private:
	MONSTER _monster;

public:

	virtual HRESULT init(const char* imageName, POINT position);
	virtual HRESULT init();
	virtual void update();
	virtual void release();
	virtual void render();

	MONSTER* getTagMonster() { return &_monster; }
	//inline RECT getRect() {return _rc; }
};

