#include "stdafx.h"
#include "player.h"
#include "IdleState.h"
#include "RunState.h"
#include "JumpState.h"
#include "FallState.h"
#include "FallRepeatState.h"
#include "AttackState.h"
#include "MoveAttackState.h"
#include "JumpAttackState.h"
#include "DashState.h"

State* FallRepeatState::inputHandle(player* player)
{
    if (player->_time > 10) {
        return new FallState();
    }
    if (KEYMANAGER->isOnceKeyDown('Z')) {
        return new DashState();
    }
	return nullptr;
}

void FallRepeatState::update(player* player)
{
    ++player->_time;

    if(player->_time > 10)
    {
        player->_isFall = true;
    }

    player->_jumpPower -= player->_gravity;
    player->_player.y -= player->_jumpPower;

    //======================================
    //            프레임 이미지
    //======================================
    if (!player->_direction)
    {
        frameCount++;
        if (frameCount >= 10) {
            frameCount = 0;
            if (player->_player_img->getFrameX() == player->_player_img->getMaxFrameX()) {
                player->_player_img->setFrameX(0);
            }
            player->_player_img->setFrameX(player->_player_img->getFrameX() + 1);
            player->_player_img->setFrameY(0);
        }
    }
    else if (player->_direction)
    {
        frameCount++;
        if (frameCount >= 10) {
            frameCount = 0;
            if (player->_player_img->getFrameX() == player->_player_img->getMaxFrameX()) {
                player->_player_img->setFrameX(0);
            }
            player->_player_img->setFrameX(player->_player_img->getFrameX() + 1);
            player->_player_img->setFrameY(1);
        }
    }
}

void FallRepeatState::enter(player* player)
{
    //이미지 불러오기
    player->_player_img = IMAGEMANAGER->findImage("LITTLEBONE_REPEATFALL");
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
    //조건주기
    player->_isLanding = false;
    player->_isFall = false;

    player->_time = 0;
}

void FallRepeatState::exit(player* player)
{
}
