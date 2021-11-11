#include "stdafx.h"
#include "player.h"
#include "IdleState.h"

void player::InputHandle()
{
	State* newState = _state->inputHandle(this);
	if (newState != nullptr) 
	{
		SAFE_DELETE(_state);
		_state = newState;
		_state->enter(this);
	}
}

HRESULT player::init()
{
	//======================================
	//           플레이어 초기화
	//======================================
	_player.x = 100;
	_player.y = 100;
	_player.weight = 50;
	_player.height = 90;
	_hp = 100;
	_gravity = 0.4f;
	_speed = 8;
	_player_attack.weight = 0;
	_player_attack.height = 0;

	_player_img = new image();
	IMAGEMANAGER->addFrameImage("LITTLEBONE_IDLE", "image/LITTLEBONE_IDLE.bmp", 1000, 500, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("LITTLEBONE_WALK", "image/LITTLEBONE_WALK.bmp", 2000, 500, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("LITTLEBONE_JUMP", "image/LITTLEBONE_JUMP.bmp", 500, 500, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("LITTLEBONE_FALL", "image/LITTLEBONE_FALL.bmp", 1250, 500, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("LITTLEBONE_REPEATFALL", "image/LITTLEBONE_REPEATFALL.bmp", 250, 500, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("LITTLEBONE_ATTACK1", "image/LITTLEBONE_ATTACK1.bmp", 1250, 500, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("LITTLEBONE_ATTACK2", "image/LITTLEBONE_ATTACK2.bmp", 1000, 500, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("LITTLEBONE_JUMPATTACK", "image/LITTLEBONE_JUMPATTACK.bmp", 1000, 500, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("LITTLEBONE_DASH", "image/LITTLEBONE_DASH.bmp", 250, 500, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("LITTLEBONE_SKILL1", "image/LITTLEBONE_SKILL.bmp", 1000, 500, 4, 2, true, RGB(255, 0, 255));

	_state = new IdleState();
	_state->enter(this);
	return S_OK;
}

void player::release()
{
	_state->exit(this);
}

void player::update()
{
	InputHandle();
	_state->update(this);

	_player.rc = RectMakeCenter(_player.x, _player.y, _player.weight, _player.height);
	_player_attack.rc = RectMakeCenter(_player_attack.x, _player_attack.y, _player_attack.weight, _player_attack.height);
}

void player::render()
{
	//Rectangle(getMemDC(), _player.rc);
	//Rectangle(getMemDC(), _player_attack.rc);

	_player_img->frameRender(getMemDC(), _player.x-125, _player.y-115);

	//char str[128];
	//sprintf_s(str, "X좌표 : %f", _player.x);
	//TextOut(getMemDC(), _player.x + 75, _player.y - 40, str, strlen(str));
	//
	//sprintf_s(str, "Y좌표 : %f", _player.y);
	//TextOut(getMemDC(), _player.x + 75, _player.y - 20, str, strlen(str));
	//
	//sprintf_s(str, "Jump : %d",_doubleJumpCount);
	//TextOut(getMemDC(), _player.x + 75, _player.y + 0, str, strlen(str));
	//
	//sprintf_s(str, "Land : %d", _isLanding);
	//TextOut(getMemDC(), _player.x + 75, _player.y + 20, str, strlen(str));
	//
	//sprintf_s(str, "Direction : %d", _direction);
	//TextOut(getMemDC(), _player.x + 75, _player.y + 40, str, strlen(str));
	//
	//sprintf_s(str, "HP : %d", _hp);
	//TextOut(getMemDC(), _player.x + 75, _player.y + 60, str, strlen(str));
}