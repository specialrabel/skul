#pragma once
#include "singletonBase.h"

struct UI
{
	image* hpBar;
	int hp;

	image* BosshpBar;
	image* BosshpBarBack;
	int Bosshp;
};

class PlayerUI : public singletonBase<PlayerUI>
{
private:
	UI _ui;

	int avavavv;

public:
	PlayerUI();
	~PlayerUI();

	HRESULT init();
	void release();
	void update();
	void playerHPrender(HDC hdc, int x, int y);
	void bossHPrender(HDC hdc, int x, int y, bool boss, float bossHp);

	void hpCalcul(int x);
	void BosshpCalcul(float x);

	UI getClassUi() { return _ui; }

};

