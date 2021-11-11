#pragma once
#include "gameNode.h"
#include "player.h"
#include "MonsterManager.h"
#include "PlayerUI.h"

#define OBJECTMAX 19

struct OBJECT4
{
	RECT rc;
	int x, y;
};

class stage5 : public gameNode
{
private:
	typedef vector<monster*>			vMonster;
	typedef vector<monster*>::iterator	viMonster;

private:
	vMonster _vNormalTree;
	viMonster _viNormalTree;

private:
	player* _player;
	MonsterManager* _mm;
	PlayerUI* _pu;

	image* _map1;
	image* _backGround;

	image* _portalImg;
	animation* _portalAni;
	image* _portalToggleImg;
	bool _portalToggle;

	int _cameraSpeedX, _cameraSpeedY, _startX, _startY, _endX, _endY;
	bool _playerSTOP;

	image* _fadeInImg;
	float _alpha; // 장면시작시 fadeIn을 위한 알파블랜더
	bool _fadeIn; // 장면시작할 때만 나오게끔

	OBJECT4 _object[OBJECTMAX];

	int _stageNum = 5;

	//몬스터 죽은 마릿수
	int _monsterDEAD = 0;
	bool _isALLDEAD;

	bool a1;
	bool a2;
	bool a3;
	bool a4;
	bool a5;
	bool a6;

	bool _isBoss;

public:

	stage5() {};
	~stage5() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	vector<monster*> setVNormalTree() { return _vNormalTree; }
	vector<monster*>::iterator setVINormalTree() { return _viNormalTree; }
};