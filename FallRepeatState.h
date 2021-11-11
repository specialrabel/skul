#pragma once
#include "State.h"
class player; // 전방선언 왜이렇게 안외워질까

class FallRepeatState :
    public State
{
public:
    int frameCount;
    virtual State* inputHandle(player* player);
    virtual void update(player* player);
    virtual void enter(player* player);
    virtual void exit(player* player);
};

