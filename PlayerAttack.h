#pragma once

class player;
class PlayerAttack
{
public:
	virtual PlayerAttack* inputHandle(player* player) = 0;
	virtual void update(player* player) = 0;
	virtual void enter(player* player) = 0;
	virtual void exit(player* player) = 0;
};
