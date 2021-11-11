#include "stdafx.h"
#include "CameraManger.h"

CameraManager::CameraManager()
{
}

CameraManager::~CameraManager()
{
}

HRESULT CameraManager::init(int width, int height)
{
	//backDC와 frontDC크기 설정
	_backX = width;
	_backY = height;
	
	//보여질 화면의 크기
	_frontX = WINSIZEX;
	_frontY = WINSIZEY;
	
	_fadeIn = IMAGEMANAGER->addImage("fadeScreen1", "image/fade.bmp", WINSIZEX, WINSIZEY, true, RGB(255,0,255));
	_fadeOut = IMAGEMANAGER->addImage("fadeScreen2", "image/fade.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	_stage1_sky = IMAGEMANAGER->addImage("sky", "image/stage1_sky1.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	
	
	//스크린 생성
	_screen.rc = RectMake(0, 0, WINSIZEX, WINSIZEY);

	return S_OK;
}

void CameraManager::release()
{
}

void CameraManager::updateScreen(int standardX, int standardY, int startX, int startY, int endX, int endY)
{
	//좌우(X)
	if (standardX - _frontX / 2 < startX)
		standardX = startX;
	else if (standardX + _frontX / 2 > endX)
		standardX = endX - _frontX;
	else
		standardX -= _frontX / 2;
	//상하(Y)
	if (standardY - 2 * _frontY / 3 < startY)
		standardY = startY;
	else if (standardY + _frontY / 3 > endY)
		standardY = endY - _frontY;
	else
		standardY -= 2 * _frontY / 3;

	//이미지 출력
	_screen.rc = RectMake(standardX, standardY, _frontX, _frontY);
}

void CameraManager::updateScreenStart(int standardX, int standardY, int startX, int startY)
{
	//좌우(X)
	if (standardX - startX < 0)
		standardX = 0;
	else if (standardX + startX > _backX)
		standardX = _backX - _frontX;
	else
		standardX -= startX;
	//상하(Y)
	if (standardY - 2 * startY < 0)
		standardY = 0;
	else if (standardY + startY > _backY)
		standardY = _backY - _frontY;
	else
		standardY -= 2 * startY;

	//이미지 출력
	_screen.rc = RectMake(standardX, standardY, _frontX, _frontY);

}

void CameraManager::render(HDC frontDC, int destX, int destY, HDC backDC, bool mini)
{
	//미니맵 변수가 true면 스크린의 우측상단에 미니맵 출력
	if (mini) {
		SetStretchBltMode(backDC, COLORONCOLOR);
		StretchBlt(
			backDC,
			_screen.rc.right - _frontX / 4,
			_screen.rc.top,
			_frontX / 4,
			_frontY / 5,
			backDC,
			_screen.rc.left,
			_screen.rc.top,
			_frontX,
			_frontY,
			SRCCOPY);
	}

	BitBlt(
		frontDC,				//복사받는 DC
		destX,					//복사받는 좌표(left)
		destY,					//복사받는 좌표(top)
		_frontX,			//복사되는 가로크기
		_frontY,			//복사되는 세로크기
		backDC,					//복사되는 DC
		_screen.rc.left, _screen.rc.top,	//복사되는 시작좌표(left, top)
		SRCCOPY);				//그대로 복사해오기(모드)
	

}

void CameraManager::fadeIn(HDC hdc)
{
	if (_fadeInAlpha > 249)
	{
		_fadeInAlpha -= 0.3;
	}
	else if (_fadeInAlpha > 150 && _fadeInAlpha <= 249)
	{
		_fadeInAlpha -= 5;
	}
	else if (_fadeInAlpha > 10 && _fadeInAlpha <= 150)
	{
		_fadeInAlpha -= 10;
	}

	if (_fadeInAlpha < 0)
		_fadeInAlpha = 0;

	_fadeIn -> alphaRender(hdc, _screen.rc.left, _screen.rc.top, _fadeInAlpha);
}

void CameraManager::fadeIn_Init()
{
	_fadeInAlpha = 255;
}

void CameraManager::fadeOut(HDC hdc)
{
	if (_fadeOutAlpha < 6)
	{
		_fadeOutAlpha += 0.3;
	}
	else if (_fadeOutAlpha < 101 && _fadeOutAlpha >= 6)
	{
		_fadeOutAlpha += 5;
	}
	else if (_fadeOutAlpha < 245 && _fadeOutAlpha >= 101)
	{
		_fadeOutAlpha += 10;
	}

	if (_fadeOutAlpha > 255)
		_fadeOutAlpha = 255;

	_fadeOut->alphaRender(hdc, _screen.rc.left, _screen.rc.top, _fadeOutAlpha);
}

void CameraManager::fadeOut_Init()
{
	_fadeOutAlpha = 0;
}

void CameraManager::backGround(HDC hdc, int stageNum)
{
	if (stageNum == 1)
	{
		_stage1_sky->render(hdc, _screen.rc.left, _screen.rc.top);
	}
}

void CameraManager::ui(image* image, HDC hdc, int x, int y)
{
	image->render(hdc, _screen.rc.left + x, _screen.rc.top + y);
}

void CameraManager::ui(image* image, HDC hdc, int x, int y, float width, float height)
{
	image->render(hdc, _screen.rc.left + x, _screen.rc.top + y, 0, 0, width, height);
}
