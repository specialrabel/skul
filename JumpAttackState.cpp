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

State* JumpAttackState::inputHandle(player* player)
{
    if (player->_time > 20) {
        return new FallState();
    }
    if (player->_isLanding) {
        return new IdleState();
    }


    return nullptr;
}

void JumpAttackState::update(player* player)
{
    ++player->_time;

    player->_jumpPower -= player->_gravity;
    player->_player.y -= player->_jumpPower;

    if (player->_jumpPower < 0)
    {
        player->_isFall = true;
    }

    //=====================================
   //       점프할 때 움직이기 위함
   //=====================================
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


    //프레임이미지
    if (!player->_direction)//플레이어에서 방향을 가져옴.
    {
        frameCount++;
        if (frameCount >= 8) {
            frameCount = 0;
            if (player->_player_img->getFrameX() >= player->_player_img->getMaxFrameX()) {
                player->_player_img->setFrameX(0);
            }
            player->_player_img->setFrameX(player->_player_img->getFrameX() + 1);
            player->_player_img->setFrameY(0);
        }
    }
    else if (player->_direction)//플레이어에서 방향을 가져옴.
    {
        frameCount++;
        if (frameCount >= 8) {
            frameCount = 0;
            if (player->_player_img->getFrameX() == 0) {
                player->_player_img->setFrameX(player->_player_img->getMaxFrameX());
            }
            player->_player_img->setFrameX(player->_player_img->getFrameX() - 1);
            player->_player_img->setFrameY(1);
        }
    }

    //=====================================
    //              공격 관련
    //=====================================
    if (!player->_direction && player->_player_img == IMAGEMANAGER->findImage("LITTLEBONE_JUMPATTACK")) // 오른쪽 보고있을 때
    {
        if (player->_player_img->getFrameX() == 0) {
            player->_player_attack.x = player->_player.x;
            player->_player_attack.y = player->_player.y;
            player->_player_attack.weight = 0;
            player->_player_attack.height = 0;
        }
        else if (player->_player_img->getFrameX() == 1) {
            player->_player_attack.x = player->_player.x+26;
            player->_player_attack.y = player->_player.y;
            player->_player_attack.weight = 138;
            player->_player_attack.height = 143;
        }
        else if (player->_player_img->getFrameX() == 2) {
            player->_player_attack.x = player->_player.x + 22;
            player->_player_attack.y = player->_player.y + 20;
            player->_player_attack.weight = 136;
            player->_player_attack.height = 108;
        }
        else if (player->_player_img->getFrameX() == 3) {
            player->_player_attack.x = player->_player.x;
            player->_player_attack.y = player->_player.y ;
            player->_player_attack.weight = 0;
            player->_player_attack.height = 0;
        }
    }
    if (player->_direction && player->_player_img == IMAGEMANAGER->findImage("LITTLEBONE_JUMPATTACK")) // 왼쪽 보고있을 때
    {
        if (player->_player_img->getFrameX() == 3) {
            player->_player_attack.x = player->_player.x;
            player->_player_attack.y = player->_player.y;
            player->_player_attack.weight = 0;
            player->_player_attack.height = 0;
        }
        else if (player->_player_img->getFrameX() == 2) {
            player->_player_attack.x = player->_player.x - 28;
            player->_player_attack.y = player->_player.y;
            player->_player_attack.weight = 136;
            player->_player_attack.height = 143;
        }
        else if (player->_player_img->getFrameX() == 1) {
            player->_player_attack.x = player->_player.x - 22;
            player->_player_attack.y = player->_player.y + 20;
            player->_player_attack.weight = 136;
            player->_player_attack.height = 108;
        }
        else if (player->_player_img->getFrameX() == 0) {
            player->_player_attack.x = player->_player.x;
            player->_player_attack.y = player->_player.y;
            player->_player_attack.weight = 0;
            player->_player_attack.height = 0;
        }
    }
}

void JumpAttackState::enter(player* player)
{
    //이미지 불러오기
    player->_player_img = IMAGEMANAGER->findImage("LITTLEBONE_JUMPATTACK");
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
    //이미지 프레임 초기화
    player->_player_img->setFrameX(0);
    //공격딜레이
    player->_time = 0;
}

void JumpAttackState::exit(player* player)
{
}
