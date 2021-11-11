#pragma once
#include "State.h"
class player;

class Skill1State :
    public State
{
    int frameCount;
    virtual State* inputHandle(player* player);
    virtual void update(player* player);
    virtual void enter(player* player);
    virtual void exit(player* player);
};

