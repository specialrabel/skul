#pragma once
#include "gameNode.h"
#include "NormalTree.h"
#include "monster.h"
#include <vector>

class MonsterManager : public gameNode
{
private:
	typedef vector<monster*>			vMonster;
	typedef vector<monster*>::iterator	viMonster;

private:
	monster* _monster;

	vMonster _vNormalTree;
	viMonster _viNormalTree;

public:
	MonsterManager() {};
	~MonsterManager() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void SetMonster(int stageNum);
	void monsterMove();

	vector<monster*> getVNormalTree() { return _vNormalTree; }
	vector<monster*>::iterator getVINormalTree() { return _viNormalTree; }

	void setPlayerAdressLink(monster* ms) { _monster = ms; }
};
