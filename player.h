#pragma once
#include "gameNode.h"
#include "State.h"

struct PLAYER
{
	RECT rc;				//�÷��̾� ��Ʈ
	float x, y;				//�÷��̾� ��ǥ
	int weight, height;		//�÷��̾� �ʺ�, ����	
	int stage;				//�÷��̾� ��������
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
	//             �÷��̾� ���°���
	//=============================================
	void InputHandle();		//��������, ���º�ȭ�ڵ�
	State* _state;			//�÷��̾��� ����

	PLAYER _player;			//�÷��̾�
	image* _player_img;		//�÷��̾��� �̹���
	
	//�߷�, ���Ӱ���
	float _gravity, _jumpPower, _dashPower;
	//�ӵ�, ī��Ʈ
	int _speed, _doubleJumpCount, _hp;
	//����, ����(false=������), �ϰ�, ����Ű
	bool _isLanding, _direction, _isFall, _doubleAttack, _doubleDash, _hit; 
	//�ð�
	int _time;

	//=============================================
	//            �÷��̾� ����, ��ų����
	//=============================================
	ATTACK _player_attack;


	player() {};
	~player() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};
