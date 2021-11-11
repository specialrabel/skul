#pragma once

class monster;
class MonsterState
{
public:
	virtual MonsterState* inputHandle(monster* monster) = 0;
	virtual void update(monster* monster) = 0;
	virtual void enter(monster* monster) = 0;
	virtual void exit(monster* monster) = 0;
};
