#pragma once
#include "gameNode.h"


enum // 보스 공격패턴
{
	IDLESTATE = 1,
	LEFTATTACK,
	RIGHTATTACK,
	HEADATTACK,
	STAMPHAND
};

struct BOSS
{
	//공격범위
	RECT scale_rc;
	int scale_x, scale_y;
	int scale_width, scale_height;

	RECT head_rc;
	image* head_image;
	float head_x, head_y;
	int head_width, head_height;
	int head_speed;

	RECT body_rc;
	image* body_image;
	float body_x, body_y;
	float body_width, body_height;
	float body_speed;

	RECT leftHand_rc;
	image* leftHand_image;
	float leftHand_x, leftHand_y;
	float leftHand_width, leftHand_height;
	float leftHand_speed;

	RECT rightHand_rc;
	image* rightHand_image;
	float rightHand_x, rightHand_y;
	float rightHand_width, rightHand_height;
	float rightHand_speed;

	RECT body1_rc;
	float body1_x, body1_y;
	float body1_width, body1_height;
	RECT body2_rc;
	float body2_x, body2_y;
	float body2_width, body2_height;

	float hp;
	int time;
	int pattern;

	//가만히있는 시간측정(/찾기 WOLRD TIME...)
	int IDLE_COUNT;
	//왼쪽쓸기패턴
	int LPATTERN_COUNT;
	float LEFTHAND_SPEED, LEFTHAND_SPEEDPOWER;
	//오른쪽쓸기패턴
	int RPATTERN_COUNT;
	float RIGHTHAND_SPEED, RIGHTHAND_SPEEDPOWER;
	//머리찍기패턴
	int HPATTERN_COUNT;
	float HEAD_SPEED, HEAD_SPEEDPOWER;
	int HEAD_TIMECOUNT;
	//스탬프패턴
	int SPATTERN_COUNT;
	float S_LHAND_SPEED, S_LHAND_SPEEDPOWER;
	float S_RHAND_SPEED, S_RHAND_SPEEDPOWER;	
	int STAMP_TIMECOUNT;

	//타격받고있는지 아닌지
	bool isHit;
	//타격받은 후 시간(타격받은 직후만 하얘지게하기위해...)
	int hitCount;
};

class Boss : public gameNode
{
private:
	BOSS _boss;


public:
	Boss();
	~Boss();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	BOSS* getTagBoss() { return &_boss; }
};

