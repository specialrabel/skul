#pragma once
#include "gameNode.h"
#include "State.h"

struct PLAYER
{
	RECT rc;				//플레이어 렉트
	float x, y;				//플레이어 좌표
	int weight, height;		//플레이어 너비, 높이	
	int stage;				//플레이어 스테이지
};

struct ATTACK
{
	RECT rc;
	float x, y;
	int weight, height;
	image* image;
};

class player : public gameNode
{
private:

public:
	//=============================================
	//             플레이어 상태관련
	//=============================================
	void InputHandle();		//상태패턴, 상태변화핸들
	State* _state;			//플레이어의 상태

	PLAYER _player;			//플레이어
	image* _player_img;		//플레이어의 이미지
	
	//중력, 가속관련
	float _gravity, _jumpPower, _dashPower;
	//속도, 카운트
	int _speed, _doubleJumpCount, _hp;
	//착지, 방향(false=오른쪽), 하강, 연속키
	bool _isLanding, _direction, _isFall, _doubleAttack, _doubleDash, _hit; 
	//시간
	int _time;

	//=============================================
	//            플레이어 공격, 스킬관련
	//=============================================
	ATTACK _player_attack;


	player() {};
	~player() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};
