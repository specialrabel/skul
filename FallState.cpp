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

State* FallState::inputHandle(player* player)
{
    if (player->_isLanding && !KEYMANAGER->isStayKeyDown(VK_RIGHT) && !player->_direction) {
        return new IdleState();
    }
    if (player->_isLanding && !KEYMANAGER->isStayKeyDown(VK_LEFT) && player->_direction) {
        return new IdleState();
    }

    if (player->_isLanding && KEYMANAGER->isStayKeyDown(VK_RIGHT)) {
        player->_direction = false;
        return new RunState();
    }
    if (player->_isLanding && KEYMANAGER->isStayKeyDown(VK_LEFT)) {
        player->_direction = true;
        return new RunState();
    }
    if (player->_doubleJumpCount >= 1 && KEYMANAGER->isOnceKeyDown('C')) {
        return new JumpState();
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

    return nullptr;
}

void FallState::update(player* player)
{

    //======================================
    //       �������� �� �����̱� ����
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
    if (player->_jumpPower > -30)
    player->_jumpPower -= player->_gravity;
    player->_player.y -= player->_jumpPower;
    //======================================
    //            ������ �̹���
    //======================================
    if (!player->_direction)
    {
        frameCount++;
        if (frameCount >= 4) {
            frameCount = 0;
            if (player->_player_img->getFrameX() == player->_player_img->getMaxFrameX()) {
                player->_player_img->setFrameX(2);
            }
            player->_player_img->setFrameX(player->_player_img->getFrameX() + 1);
            player->_player_img->setFrameY(0);
        }
    }
    else if (player->_direction)
    {
        frameCount++;
        if (frameCount >= 4) {
            frameCount = 0;
            if (player->_player_img->getFrameX() == 0) {
                player->_player_img->setFrameX(3);
            }
            player->_player_img->setFrameX(player->_player_img->getFrameX() - 1);
            player->_player_img->setFrameY(1);
        }
    }
}

void FallState::enter(player* player)
{
    player->_player_img = IMAGEMANAGER->findImage("LITTLEBONE_FALL");
    //�浹��Ʈ ����
    player->_player.weight = 50;
    //fall ����Ȯ��
    player->_isFall = true;
    //�̹��������� ���� �ʱ�ȭ
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
    player->_player_attack.weight = 0;
    player->_player_attack.height = 0;
    return;
}

void FallState::exit(player* player)
{
}
