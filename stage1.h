#pragma once
#include "gameNode.h"
#include "player.h"
#include "MonsterManager.h"
#include "PlayerUI.h"

#define OBJECTMAX 5

struct OBJECT0
{
	RECT rc;
	int x, y;
};

class stage1 : public gameNode
{
private:
	player* _player;
	MonsterManager* _mm;
	PlayerUI* _pu;

	image* _map1;
	image* _groundWall;
	image* _ground;
	image* _groundCandle;
	image* _fallWall1;
	image* _fallWall2;
	image* _fallWall3;
	image* _fallWall4;
	image* _outWall;
	image* _inWall;
	image* _skyMove;
	image* _backBillage;
	float skyMove;

	int _cameraSpeedX, _cameraSpeedY, _startX, _startY, _endX, _endY;

	int _time;

	image* _rebornImg;
	animation* _rebornAni;

	bool _playerSTOP;

	OBJECT0 _object[OBJECTMAX];

	int _stageNum = 1;

	bool _isBoss;

public:
	stage1() {};
	~stage1() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};