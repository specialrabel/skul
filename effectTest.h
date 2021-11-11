#pragma once
#include "gameNode.h"
#include "effect.h"

class effectTest : public gameNode
{
private:
	effect* _effectSample;

public:
	effectTest();
	~effectTest();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

