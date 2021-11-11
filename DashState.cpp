#include "stdafx.h"
#include "player.h"
#include "IdleState.h"
#include "RunState.h"
#include "JumpState.h"
#include "FallState.h"
#include "FallRepeatState.h"
#include "AttackState.h"
#include "MoveAttackState.h"
#include "DashState.h"

State* DashState::inputHandle(player* player)
{
    if (!player->_doubleDash && player->_time > 10) {
        return new FallState();
    }
    if (player->_doubleDash && player->_time > 20) {
        return new FallState();
    }
	return nullptr;
}

void DashState::update(player* player)
{
    ++player->_time;

    if (!player->_direction)//플레이어에서 방향을 가져옴.
    {
        player->_dashPower -= 3;
        player->_player.x += player->_dashPower;

        frameCount++;
        if (frameCount >= 8) {
            frameCount = 0;
            if (player->_player_img->getFrameX() >= player->_player_img->getMaxFrameX()) {
                player->_player_img->setFrameX(0);
            }
            player->_player_img->setFrameX(player->_player_img->getFrameX());
            player->_player_img->setFrameY(0);
        }
    }
    else if (player->_direction)//플레이어에서 방향을 가져옴.
    {
        player->_dashPower -= 3;
        player->_player.x -= player->_dashPower;

        frameCount++;
        if (frameCount >= 8) {
            frameCount = 0;
            if (player->_player_img->getFrameX() == 0) {
                player->_player_img->setFrameX(player->_player_img->getMaxFrameX());
            }
            player->_player_img->setFrameX(player->_player_img->getFrameX());
            player->_player_img->setFrameY(1);
        }
    }
}

void DashState::enter(player* player)
{
    //이미지 불러오기
    player->_player_img = IMAGEMANAGER->findImage("LITTLEBONE_DASH");
    //이미지 프레임 초기화
    if (!player->_direction)
    {
        player->_player_img->setFrameX(0);
        player->_player_img->setFrameY(0);
    }
    if (player->_direction)
    {
        player->_player_img->setFrameX(player->_player_img->getMaxFrameX());
        player->_player_img->setFrameY(1);
    }
    //대쉬딜레이
    player->_time = 0;
    //대쉬 1 , 2 구분
    player->_doubleDash = false;
    //대쉬일경우 점프파워가 0이됨
    player->_jumpPower = 0;
    //대시가속도
    player->_dashPower = 40;
}

void DashState::exit(player* player)
{
}
