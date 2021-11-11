#pragma once
#include "State.h"
class player;

class JumpAttackState :
    public State
{
public:
    int frameCount;
    virtual State* inputHandle(player* player);
    virtual void update(player* player);
    virtual void enter(player* player);
    virtual void exit(player* player);
};
