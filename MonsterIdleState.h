#pragma once
#include "MonsterState.h"
class monster;

class MonsterIdleState :
    public MonsterState
{
public:
    int frameCount;
    virtual MonsterState* inputHandle(monster* monster);
    virtual void update(monster* monster);
    virtual void enter(monster* monster);
    virtual void exit(monster* monster);
};

