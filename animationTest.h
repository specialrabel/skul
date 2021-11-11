#pragma once
#include "gameNode.h"

class animationTest : public gameNode
{
private:
	image* _camel;

	animation* _ani1;
	animation* _ani2;
	animation* _ani3;

public:
	animationTest();
	~animationTest();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();


};

