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
#include "Skill1State.h"

State* JumpState::inputHandle(player* player)
{
    if (player->_isLanding && KEYMANAGER->isStayKeyDown(VK_RIGHT)) {
        return new RunState();
    }
    if (player->_isLanding && KEYMANAGER->isStayKeyDown(VK_LEFT)) {
        return new RunState();
    }

    if (player->_isLanding && !KEYMANAGER->isStayKeyDown(VK_RIGHT)) {
        return new IdleState();
    }
    if (player->_isLanding && !KEYMANAGER->isStayKeyDown(VK_LEFT)) {
        return new IdleState();
    }
    if (KEYMANAGER->isStayKeyDown('X')) {
        return new JumpAttackState();
    }
    if (KEYMANAGER->isOnceKeyDown('Z')) {
        return new DashState();
    }
    if (KEYMANAGER->isOnceKeyDown('A')) {
        return new Skill1State();
    }

    if (player->_jumpPower <= 0) {
        return new FallState();
    }
    return nullptr;
}

void JumpState::update(player* player)
{

    //======================================
    //       점프상태 때 움직이기 위함
    //======================================
    if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
    {
        player->_player_img->setFrameY(0);
    }
    if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
    {
        player->_direction = false;
        player->_player.x += player->_speed;
    }

    if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
    {
        player->_player_img->setFrameY(1);
    }
    if (KEYMANAGER->isStayKeyDown(VK_LEFT))
    {
        player->_direction = true;
        player->_player.x -= player->_speed;
    }

    //======================================
    //             더블점프 기능
    //======================================
    if (KEYMANAGER->isOnceKeyDown('C') && player->_doubleJumpCount >= 1)
    {
        player->_jumpPower = 16.0f;
        player->_gravity = 0.8f;
        player->_doubleJumpCount -= 1;
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
            player->_player_img->setFrameX(player->_player_img->getFrameX() + 1);
            player->_player_img->setFrameY(0);
            if (player->_player_img->getFrameX() == player->_player_img->getMaxFrameX()) {
                player->_player_img->setFrameX(0);
            }
        }
    }
    else if (player->_direction)
    {
        frameCount++;
        if (frameCount >= 10) {
            frameCount = 0;
            player->_player_img->setFrameX(player->_player_img->getFrameX() + 1);
            player->_player_img->setFrameY(1);
            if (player->_player_img->getFrameX() == player->_player_img->getMaxFrameX()) {
                player->_player_img->setFrameX(0);
            }
        }
    }
}

void JumpState::enter(player* player)
{
    //이미지 불러오기
    player->_player_img = IMAGEMANAGER->findImage("LITTLEBONE_JUMP");
    //점프 기본값
    player->_jumpPower = 16.0f;
    player->_gravity = 0.8f;
    player->_doubleJumpCount -= 1;
    //fall 상태확인
    player->_isFall = false;
    player->_isLanding = false;
    //충돌렉트 조정
    player->_player.weight = 50;
    //이미지 프레임 초기화
    player->_player_img->setFrameX(0);
    //이미지프레임 방향 초기화
    if (!player->_direction) player->_player_img->setFrameY(0);
    if (player->_direction) player->_player_img->setFrameY(1);
    
    return;
}

void JumpState::exit(player* player)
{
}
