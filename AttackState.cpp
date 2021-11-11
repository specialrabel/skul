#include "stdafx.h"
#include "player.h"
#include "IdleState.h"
#include "RunState.h"
#include "JumpState.h"
#include "FallState.h"
#include "FallRepeatState.h"
#include "AttackState.h"

State* AttackState::inputHandle(player* player)
{
    if (!player->_doubleAttack && player->_time > 30) {
        return new IdleState();
    }
    if (player->_doubleAttack && player->_time > 50) {
        return new IdleState();
    }
    return nullptr;
}

void AttackState::update(player* player)
{
    ++player->_time;

    //=====================================
    //              ���� ����
    //=====================================
    player->_jumpPower -= player->_gravity;
    player->_player.y -= player->_jumpPower;

    if (KEYMANAGER->isOnceKeyDown('X') && player->_time < 30)
    {
        player->_doubleAttack = true;
    }
    if (player->_doubleAttack && player->_time == 30)
    {
        //player->_time = 0;
        player->_player_img = IMAGEMANAGER->findImage("LITTLEBONE_ATTACK2");
        //player->_doubleAttack = false;
    }
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
    if (!player->_direction && player->_player_img == IMAGEMANAGER->findImage("LITTLEBONE_ATTACK1")) // ������ �������� ��
    {
        if (player->_player_img->getFrameX() == 0) {
            player->_player_attack.x = player->_player.x;
            player->_player_attack.y = player->_player.y;
            player->_player_attack.weight = 0;
            player->_player_attack.height = 0;
        }
        else if (player->_player_img->getFrameX() == 1) {
            player->_player_attack.x = player->_player.x;
            player->_player_attack.y = player->_player.y;
            player->_player_attack.weight = 0;
            player->_player_attack.height = 0;
        }
        else if (player->_player_img->getFrameX() == 2) {
            player->_player_attack.x = player->_player.x+20;
            player->_player_attack.y = player->_player.y-10;
            player->_player_attack.weight = 150;
            player->_player_attack.height = 137;
        }
        else if (player->_player_img->getFrameX() == 3) {
            player->_player_attack.x = player->_player.x+15;
            player->_player_attack.y = player->_player.y+15;
            player->_player_attack.weight = 147;
            player->_player_attack.height = 88;
        }
        else if (player->_player_img->getFrameX() == 4) {
            player->_player_attack.x = player->_player.x;
            player->_player_attack.y = player->_player.y;
            player->_player_attack.weight = 0;
            player->_player_attack.height = 0;
        }
    }
    if (!player->_direction && player->_player_img == IMAGEMANAGER->findImage("LITTLEBONE_ATTACK2")) // ������ �������� ��
    {
        if (player->_player_img->getFrameX() == 0) {
            player->_player_attack.x = player->_player.x;
            player->_player_attack.y = player->_player.y;
            player->_player_attack.weight = 0;
            player->_player_attack.height = 0;
        }
        else if (player->_player_img->getFrameX() == 1) {
            player->_player_attack.x = player->_player.x+10;
            player->_player_attack.y = player->_player.y;
            player->_player_attack.weight = 145;
            player->_player_attack.height = 152;
        }
        else if (player->_player_img->getFrameX() == 2) {
            player->_player_attack.x = player->_player.x + 10;
            player->_player_attack.y = player->_player.y - 20;
            player->_player_attack.weight = 150;
            player->_player_attack.height = 137;
        }
        else if (player->_player_img->getFrameX() == 3) {
            player->_player_attack.x = player->_player.x;
            player->_player_attack.y = player->_player.y;
            player->_player_attack.weight = 0;
            player->_player_attack.height = 0;
        }
    }
    if (player->_direction && player->_player_img == IMAGEMANAGER->findImage("LITTLEBONE_ATTACK1")) // ���� �������� ��
    {
        if (player->_player_img->getFrameX() == 4) {
            player->_player_attack.x = player->_player.x;
            player->_player_attack.y = player->_player.y;
            player->_player_attack.weight = 0;
            player->_player_attack.height = 0;
        }
        else if (player->_player_img->getFrameX() == 3) {
            player->_player_attack.x = player->_player.x;
            player->_player_attack.y = player->_player.y;
            player->_player_attack.weight = 0;
            player->_player_attack.height = 0;
        }
        else if (player->_player_img->getFrameX() == 2) {
            player->_player_attack.x = player->_player.x - 23;
            player->_player_attack.y = player->_player.y - 10;
            player->_player_attack.weight = 150;
            player->_player_attack.height = 137;
        }
        else if (player->_player_img->getFrameX() == 1) {
            player->_player_attack.x = player->_player.x - 18;
            player->_player_attack.y = player->_player.y + 15;
            player->_player_attack.weight = 147;
            player->_player_attack.height = 88;
        }
        else if (player->_player_img->getFrameX() == 0) {
            player->_player_attack.x = player->_player.x;
            player->_player_attack.y = player->_player.y;
            player->_player_attack.weight = 0;
            player->_player_attack.height = 0;
        }
    }
    if (player->_direction && player->_player_img == IMAGEMANAGER->findImage("LITTLEBONE_ATTACK2")) // ���� �������� ��
    {
        if (player->_player_img->getFrameX() == 3) {
            player->_player_attack.x = player->_player.x;
            player->_player_attack.y = player->_player.y;
            player->_player_attack.weight = 0;
            player->_player_attack.height = 0;
        }
        else if (player->_player_img->getFrameX() == 2) {
            player->_player_attack.x = player->_player.x - 10;
            player->_player_attack.y = player->_player.y;
            player->_player_attack.weight = 145;
            player->_player_attack.height = 152;
        }
        else if (player->_player_img->getFrameX() == 1) {
            player->_player_attack.x = player->_player.x - 10;
            player->_player_attack.y = player->_player.y - 20;
            player->_player_attack.weight = 150;
            player->_player_attack.height = 137;
        }
        else if (player->_player_img->getFrameX() == 0) {
            player->_player_attack.x = player->_player.x;
            player->_player_attack.y = player->_player.y;
            player->_player_attack.weight = 0;
            player->_player_attack.height = 0;
        }
    }

}

void AttackState::enter(player* player)
{
    //�̹��� �ҷ�����
    player->_player_img = IMAGEMANAGER->findImage("LITTLEBONE_ATTACK1");
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
    //���ݵ�����
    player->_time = 0;
    //���� 1 , 2 ����
    player->_doubleAttack = false;
}

void AttackState::exit(player* player)
{
}
