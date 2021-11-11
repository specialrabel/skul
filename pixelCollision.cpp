#include "stdafx.h"
#include "pixelCollision.h"


pixelCollision::pixelCollision()
{
}


pixelCollision::~pixelCollision()
{
}

HRESULT pixelCollision::init()
{
	IMAGEMANAGER->addImage("Ãæµ¹¸Ê", "image/collisionMap.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	_reaper = IMAGEMANAGER->addImage("¸®ÆÛ", "image/reaper.bmp", 100, 100, true, RGB(255, 0, 255));

	_x = WINSIZEX / 2 - 150;
	_y = WINSIZEY / 2 + 80;

	_rc = RectMakeCenter(_x, _y, _reaper->getWidth(), _reaper->getHeight());

	_probeY = _y + _reaper->getHeight() / 2;

	_gravity = 0.4f;
	_jumpPower = 0;

	return S_OK;
}

void pixelCollision::release()
{


}

void pixelCollision::update()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) _x -= 3;
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) _x += 3;

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_isJump = true;
		_isLanding = false;
		_jumpPower = 10.0f;
	}

	if(_isJump)
	{
		_jumpPower -= _gravity;
		_y -= _jumpPower;
	}
	if (_isLanding)
	{	
		_jumpPower -= _gravity;
		_y -= _jumpPower;
	}


	_probeY = _y + _reaper->getHeight() / 2;

	for (int i = _probeY - 30; i < _probeY + 10; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("Ãæµ¹¸Ê")->getMemDC(), _x, i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 0))
		{
			_y = i - _reaper->getHeight() / 2;
			_isJump = false;		
			_isLanding = true;
			_jumpPower = 0;

			break;
		}
		if ((r == 0 && g == 255 && b == 0))
		{
			_y = i - _reaper->getHeight() / 2;
			_isJump = false;
			_isLanding = true;
			_jumpPower = 0;

			break;
		}

	}


	_rc = RectMakeCenter(_x, _y, _reaper->getWidth(), _reaper->getHeight());
}

void pixelCollision::render()
{
	IMAGEMANAGER->findImage("Ãæµ¹¸Ê")->render(getMemDC());


	Rectangle(getMemDC(), _rc);

	_reaper->render(getMemDC(), _rc.left, _rc.top);
}
