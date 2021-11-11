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

State* Skill1State::inputHandle(player* player)
{
    if (player->_time > 15 && player->_isFall) {
        return new FallState();
    }
    if (player->_time > 15) {
        return new IdleState();
    }

	return nullptr;
}

void Skill1State::update(player* player)
{
    ++player->_time;

    //======================================
    //            ������ �̹���
    //======================================
    if (!player->_direction)
    {
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
    {
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

void Skill1State::enter(player* player)
{
	player->_player_img = IMAGEMANAGER->findImage("LITTLEBONE_SKILL1");
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
    //�ð� �ʱ�ȭ
    player->_time = 0;
    //������ �ʱ�ȭ
    player->_jumpPower = 0;
}

void Skill1State::exit(player* player)
{
}
