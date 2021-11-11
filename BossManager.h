#pragma once
#include "gameNode.h"
#include "Boss.h"
#include <vector>

class BossManager : public gameNode
{
private:
	BossManager* _bm;
	Boss* _boss;

public:
	BossManager() {};
	~BossManager() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void BossSet();
	void BossPattern(); // 업데이트에 들어갈 녀석.

	BossManager* getTagBossManager() { return _bm; }

	void setPlayerAdressLink(Boss* boss) { _boss = boss; }
};

