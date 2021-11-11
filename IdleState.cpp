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

State* IdleState::inputHandle(player* player)
{
    if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) {
        player->_direction = false;
        return new RunState();
    }
    if (KEYMANAGER->isStayKeyDown(VK_LEFT)) {
        player->_direction = true;
        return new RunState();
    }
    if (KEYMANAGER->isStayKeyDown(VK_DOWN) && KEYMANAGER->isOnceKeyDown('C')) {
        return new FallRepeatState();
    }
    if (KEYMANAGER->isOnceKeyDown('C')) {
        return new JumpState();
    }
    if (KEYMANAGER->isOnceKeyDown('X')) {
        return new AttackState();
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
    if (!player->_isLanding) {
        return new FallState();
    }
    return nullptr;
}

void IdleState::update(player* player)
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
    {
        frameCount++;
        if (frameCount >= 10) {
            frameCount = 0;
            if (player->_player_img->getFrameX() == player->_player_img->getMaxFrameX()) {
                player->_player_img->setFrameX(-1);
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
            player->_player_img->setFrameX(player->_player_img->getFrameX() - 1);
            player->_player_img->setFrameY(1);
            if (player->_player_img->getFrameX() < 0) {
                player->_player_img->setFrameX(player->_player_img->getMaxFrameX());
            }
        }
    }
}

void IdleState::enter(player* player)
{
    player->_player_img = IMAGEMANAGER->findImage("LITTLEBONE_IDLE");
    //이미지프레임 방향 초기화
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

    player->_player_attack.weight = 0;
    player->_player_attack.height = 0;

    return;
}

void IdleState::exit(player* player)
{
}