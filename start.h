#pragma once
#include "gameNode.h"

class start : public gameNode
{
private:
	image* _startImg;
	animation* _startAni;

	image* _startKeyImg;

	bool _fadeIn, _fadeOut, _anyKey;

	int _fade;
	int _time;

	int _cameraSpeedX, _cameraSpeedY, _startX, _startY, _endX, _endY;
public:
	start() {};
	~start() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};