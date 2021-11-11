#pragma once
#include "gameNode.h"
#include "start.h"
#include "stage1.h"
#include "stage2.h"
#include "stage3.h"
#include "stage4.h"
#include "stage5.h"
#include "stage6.h"

class playGround : public gameNode
{
private:
	start* _start;
	stage1* _stage1;
	stage2* _stage2;
	stage3* _stage3;
	stage4* _stage4;
	stage5* _stage5;
	stage6* _stage6;

public:
	playGround();
	~playGround();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

