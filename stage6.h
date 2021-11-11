#pragma once
#include "gameNode.h"
#include "player.h"
#include "BossManager.h"
#include "Boss.h"
#include "PlayerUI.h"

#define OBJECTMAX 18

struct OBJECT5
{
	RECT rc;
	int x, y;
};

class stage6 : public gameNode
{
private:
	player* _player;
	//BossManager* _bm;
	Boss* _bs; //옙
	PlayerUI* _pu;

	image* _map1;
	image* _background;

	int _cameraSpeedX, _cameraSpeedY, _startX, _startY, _endX, _endY;
	bool _playerSTOP;

	image* _fadeInImg;
	float _alpha; // 장면시작시 fadeIn을 위한 알파블랜더
	bool _fadeIn; // 장면시작할 때만 나오게끔

	OBJECT5 _object[OBJECTMAX];

	int _stageNum = 5;

	bool _isBoss = true;

public:

	stage6() {};
	~stage6() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setBossAdressLink(Boss* bs) { _bs = bs; }
};
