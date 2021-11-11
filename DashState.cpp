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

    if (!player->_direction)//�÷��̾�� ������ ������.
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
    else if (player->_direction)//�÷��̾�� ������ ������.
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
    //�̹��� �ҷ�����
    player->_player_img = IMAGEMANAGER->findImage("LITTLEBONE_DASH");
    //�̹��� ������ �ʱ�ȭ
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
    //�뽬������
    player->_time = 0;
    //�뽬 1 , 2 ����
    player->_doubleDash = false;
    //�뽬�ϰ�� �����Ŀ��� 0�̵�
    player->_jumpPower = 0;
    //��ð��ӵ�
    player->_dashPower = 40;
}

void DashState::exit(player* player)
{
}
