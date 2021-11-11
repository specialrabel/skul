#pragma once
#include "gameNode.h"
#include "player.h"
#include "PlayerUI.h"

#define OBJECTMAX 5

struct OBJECT1
{
	RECT rc;
	int x, y;
};

class stage2 : public gameNode
{
private:
	player* _player;
	PlayerUI* _pu;

	image* _portalImg;
	animation* _portalAni;

	image* _map1;
	image* _ground;
	image* _sky;
	image* _portalToggleImg;
	bool _portalToggle;

	int _cameraSpeedX, _cameraSpeedY, _startX, _startY, _endX, _endY;
	bool _playerSTOP;

	image* _fadeInImg;
	float _alpha; // �����۽� fadeIn�� ���� ���ĺ���
	bool _fadeIn; // �������� ���� �����Բ�

	OBJECT1 _object[OBJECTMAX];

	int _stageNum = 2;

	bool _isBoss;

public:

	stage2() {};
	~stage2() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};