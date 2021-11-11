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
#include "Skill1State.h"

State* RunState::inputHandle(player* player)
{
    if (KEYMANAGER->isOnceKeyUp(VK_RIGHT)) {
        return new IdleState();
    }
    if (KEYMANAGER->isOnceKeyUp(VK_LEFT)) {
        return new IdleState();
    }
    if (KEYMANAGER->isOnceKeyDown('C')){
        return new JumpState();
    }
    if (KEYMANAGER->isOnceKeyDown('X')) {
        return new MoveAttackState();
    }
    if (KEYMANAGER->isOnceKeyDown('Z')) {
        return new DashState();
    }
    if (KEYMANAGER->isOnceKeyDown('A')) {
        return new Skill1State();
    }

    if (!player->_isLanding) {
        return new FallState();
    }

    return nullptr;
}

void RunState::update(player* player)
{
    if (player->_jumpPower < 0)
    {
        player->_isLanding = false;
    }

    player->_jumpPower -= player->_gravity;
    player->_player.y -= player->_jumpPower;
    //======================================
    //            프레임 이미지
    //======================================
    if (!player->_direction)
    {   player->_player.x += player->_speed;
        
        frameCount++;
        if (frameCount >= 6) {
            frameCount = 0;
            if (player->_player_img->getFrameX() == player->_player_img->getMaxFrameX()) {
                player->_player_img->setFrameX(-1);
            }
            player->_player_img->setFrameX(player->_player_img->getFrameX() + 1);
            player->_player_img->setFrameY(0);
        }
    }
    else if (player->_direction)
    {   player->_player.x -= player->_speed;
        
        frameCount++;
        if (frameCount >= 6) {
            frameCount = 0;
            player->_player_img->setFrameX(player->_player_img->getFrameX() - 1);
            player->_player_img->setFrameY(1);
            if (player->_player_img->getFrameX() < 0) {
                player->_player_img->setFrameX(player->_player_img->getMaxFrameX());
            }
        }
    }
}

void RunState::enter(player* player)
{
    //이미지 불러오기
    player->_player_img = IMAGEMANAGER->findImage("LITTLEBONE_WALK");
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

    //더블점프 초기화
    player->_doubleJumpCount = 2;
    return;
}

void RunState::exit(player* player)
{
}
