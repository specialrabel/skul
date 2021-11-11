#pragma once
#include "gameNode.h"

class testScene2 : public gameNode
{
public:
	testScene2();
	~testScene2();

	HRESULT init();
	void release();
	void update();
	void render();
};

