#pragma once
#include "gameNode.h"

class testScene : public gameNode
{
private:
	RECT _rc;

public:
	testScene();
	~testScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

