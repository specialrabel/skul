#pragma once
#include "singletonBase.h"
#include "image.h"

struct SCREEN
{
	RECT rc;
	int x, y;
};

enum CAMERAFADE {
	FADEOUT = -2,
	NORMAL,
	FADEIN,
	ENDFADE
};

class CameraManager : public singletonBase<CameraManager>
{
private:
	//카메라가 비추는 화면 크기
	SCREEN _screen;
	int _backX, _backY;	//backDC 크기
	int _frontX, _frontY;	//frontDC 크기

	image* _fadeIn;
	image* _fadeOut;
	float _fadeInAlpha;
	float _fadeOutAlpha;

	image* _stage1_sky;
	int _stage;

	int _isFade;
public:
	CameraManager();
	~CameraManager();

	HRESULT init(int width, int height);
	void release();

	void updateScreen(int standardX, int standardY, int startX, int startY, int endX, int endY);
	void updateScreenStart(int standardX, int standardY, int startX, int startY);

	void render(HDC frontDC, int destX, int destY, HDC backDC, bool mini = false);
	
	void fadeIn(HDC hdc);
	void fadeIn_Init();
	void fadeOut(HDC hdc);
	void fadeOut_Init();
	void backGround(HDC hdc, int stageNum);
	void ui(image* image, HDC hdc, int x, int y);
	void ui(image* image, HDC hdc, int x, int y, float width, float height);
};

