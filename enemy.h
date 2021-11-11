#pragma once
#include "gameNode.h"

class enemy : public gameNode
{
protected:
	image* _imageName;		//에너미 이미지
	RECT _rc;				//렉트

	int _currentFrameX;		//프레임번호로 사용할 변수
	int _currentFrameY;

	int _count;				//프레임렌더링 용
	int _fireCount;			//발사 카운트 용
	int _rndFireCount;		//랜덤 발사 카운트 용

public:
	enemy() {};
	~enemy() {};

	virtual HRESULT init();
	virtual HRESULT init(const char* imageName, POINT position);
	virtual void release();
	virtual void update();
	virtual void render();

	void move();
	void draw();

	bool bulletCountFire();

	inline RECT getRect() { return _rc; }

};

