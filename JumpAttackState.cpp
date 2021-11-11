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
   //       ������ �� �����̱� ����
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


    //�������̹���
    if (!player->_direction)//�÷��̾�� ������ ������.
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
    else if (player->_direction)//�÷��̾�� ������ ������.
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
    //              ���� ����
    //=====================================
    if (!player->_direction && player->_player_img == IMAGEMANAGER->findImage("LITTLEBONE_JUMPATTACK")) // ������ �������� ��
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
    if (player->_direction && player->_player_img == IMAGEMANAGER->findImage("LITTLEBONE_JUMPATTACK")) // ���� �������� ��
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
    //�̹��� �ҷ�����
    player->_player_img = IMAGEMANAGER->findImage("LITTLEBONE_JUMPATTACK");
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
    //�̹��� ������ �ʱ�ȭ
    player->_player_img->setFrameX(0);
    //���ݵ�����
    player->_time = 0;
}

void JumpAttackState::exit(player* player)
{
}
