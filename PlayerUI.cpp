#include "stdafx.h"
#include "PlayerUI.h"

PlayerUI::PlayerUI()
{
}

PlayerUI::~PlayerUI()
{
}

HRESULT PlayerUI::init()
{
	IMAGEMANAGER->addImage("hp100", "image/hpBar.bmp", 349, 139, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("hp94", "image/hpBar_94.bmp", 349, 139, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("hp88", "image/hpBar_88.bmp", 349, 139, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("hp82", "image/hpBar_82.bmp", 349, 139, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("hp76", "image/hpBar_76.bmp", 349, 139, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("hp70", "image/hpBar_70.bmp", 349, 139, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("hp64", "image/hpBar_64.bmp", 349, 139, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("hp58", "image/hpBar_58.bmp", 349, 139, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("hp52", "image/hpBar_52.bmp", 349, 139, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("hp46", "image/hpBar_46.bmp", 349, 139, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("hp40", "image/hpBar_40.bmp", 349, 139, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("hp34", "image/hpBar_34.bmp", 349, 139, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("hp28", "image/hpBar_28.bmp", 349, 139, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("hp22", "image/hpBar_22.bmp", 349, 139, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("hp16", "image/hpBar_16.bmp", 349, 139, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("hp10", "image/hpBar_10.bmp", 349, 139, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("hp0", "image/hpBar_0.bmp", 349, 139, true, RGB(255, 0, 255));

	_ui.hpBar = IMAGEMANAGER->findImage("hp100");
	_ui.hp = 100;

	IMAGEMANAGER->addImage("Bosshp100", "image/Bosshp.bmp", 798, 112, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("Bosshp100", "image/BosshpBar_100.bmp", 798, 112, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("Bosshp94", "image/BosshpBar_94.bmp", 798, 112, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("Bosshp88", "image/BosshpBar_88.bmp", 798, 112, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("Bosshp82", "image/BosshpBar_82.bmp", 798, 112, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("Bosshp76", "image/BosshpBar_76.bmp", 798, 112, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("Bosshp70", "image/BosshpBar_70.bmp", 798, 112, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("Bosshp64", "image/BosshpBar_64.bmp", 798, 112, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("Bosshp58", "image/BosshpBar_58.bmp", 798, 112, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("Bosshp52", "image/BosshpBar_52.bmp", 798, 112, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("Bosshp46", "image/BosshpBar_46.bmp", 798, 112, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("Bosshp40", "image/BosshpBar_40.bmp", 798, 112, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("Bosshp34", "image/BosshpBar_34.bmp", 798, 112, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("Bosshp28", "image/BosshpBar_28.bmp", 798, 112, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("Bosshp22", "image/BosshpBar_22.bmp", 798, 112, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("Bosshp16", "image/BosshpBar_16.bmp", 798, 112, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("Bosshp10", "image/BosshpBar_10.bmp", 798, 112, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Bosshp0", "image/BosshpBar_0.bmp",  798, 112, true, RGB(255, 0, 255));

	_ui.BosshpBar = IMAGEMANAGER->findImage("Bosshp100");
	_ui.BosshpBarBack = IMAGEMANAGER->findImage("Bosshp0");
	_ui.Bosshp = 100;

	return S_OK;
}

void PlayerUI::release()
{

}

void PlayerUI::update()
{


}

void PlayerUI::playerHPrender(HDC hdc, int x, int y)
{
	CAMERAMANAGER->ui(_ui.hpBar, hdc, 0, 580);
}

void PlayerUI::bossHPrender(HDC hdc, int x, int y, bool boss, float bossHp)
{
	if (boss == true)
	{
		CAMERAMANAGER->ui(_ui.BosshpBarBack, hdc, 230, 20, 798, 112);
		CAMERAMANAGER->ui(_ui.BosshpBar, hdc, 230, 20, bossHp, 112);
	}
}

void PlayerUI::hpCalcul(int x)
{
	if (x == 100)
	{
		_ui.hpBar = IMAGEMANAGER->findImage("hp100");
	}
	if (x < 100 && x >= 94)
	{
		_ui.hpBar = IMAGEMANAGER->findImage("hp94");
	}
	if (x < 94 && x >= 88)
	{
		_ui.hpBar = IMAGEMANAGER->findImage("hp88");
	}
	if (x < 88 && x >= 82)
	{
		_ui.hpBar = IMAGEMANAGER->findImage("hp82");
	}
	if (x < 82 && x >= 76)
	{
		_ui.hpBar = IMAGEMANAGER->findImage("hp76");
	}
	if (x < 76 && x >= 70)
	{
		_ui.hpBar = IMAGEMANAGER->findImage("hp70");
	}
	if (x < 70 && x >= 64)
	{
		_ui.hpBar = IMAGEMANAGER->findImage("hp64");
	}
	if (x < 64 && x >= 58)
	{
		_ui.hpBar = IMAGEMANAGER->findImage("hp58");
	}
	if (x < 58 && x >= 52)
	{
		_ui.hpBar = IMAGEMANAGER->findImage("hp52");
	}
	if (x < 52 && x >= 46)
	{
		_ui.hpBar = IMAGEMANAGER->findImage("hp46");
	}
	if (x < 46 && x >= 40)
	{
		_ui.hpBar = IMAGEMANAGER->findImage("hp40");
	}
	if (x < 40 && x >= 34)
	{
		_ui.hpBar = IMAGEMANAGER->findImage("hp34");
	}
	if (x < 34 && x >= 28)
	{
		_ui.hpBar = IMAGEMANAGER->findImage("hp28");
	}
	if (x < 28 && x >= 22)
	{
		_ui.hpBar = IMAGEMANAGER->findImage("hp22");
	}
	if (x < 22 && x >= 16)
	{
		_ui.hpBar = IMAGEMANAGER->findImage("hp16");
	}
	if (x < 16 && x >= 0)
	{
		_ui.hpBar = IMAGEMANAGER->findImage("hp10");
	}
	if (x < 0)
	{
		_ui.hpBar = IMAGEMANAGER->findImage("hp0");
	}
}

void PlayerUI::BosshpCalcul(float x)
{
	_ui.BosshpBar = IMAGEMANAGER->findImage("Bosshp100");
	_ui.BosshpBar = IMAGEMANAGER->findImage("Bosshp100");

	/*if (x == 100)
	{
		_ui.BosshpBar = IMAGEMANAGER->findImage("Bosshp100");
	}
	if (x < 100 && x >= 94)
	{
		_ui.BosshpBar = IMAGEMANAGER->findImage("Bosshp94");
	}
	if (x < 94 && x >= 88)
	{
		_ui.BosshpBar = IMAGEMANAGER->findImage("Bosshp88");
	}
	if (x < 88 && x >= 82)
	{
		_ui.BosshpBar = IMAGEMANAGER->findImage("Bosshp82");
	}
	if (x < 82 && x >= 76)
	{
		_ui.BosshpBar = IMAGEMANAGER->findImage("Bosshp76");
	}
	if (x < 76 && x >= 70)
	{
		_ui.BosshpBar = IMAGEMANAGER->findImage("Bosshp70");
	}
	if (x < 70 && x >= 64)
	{
		_ui.BosshpBar = IMAGEMANAGER->findImage("Bosshp64");
	}
	if (x < 64 && x >= 58)
	{
		_ui.BosshpBar = IMAGEMANAGER->findImage("Bosshp58");
	}
	if (x < 58 && x >= 52)
	{
		_ui.BosshpBar = IMAGEMANAGER->findImage("Bosshp52");
	}
	if (x < 52 && x >= 46)
	{
		_ui.BosshpBar = IMAGEMANAGER->findImage("Bosshp46");
	}
	if (x < 46 && x >= 40)
	{
		_ui.BosshpBar = IMAGEMANAGER->findImage("Bosshp40");
	}
	if (x < 40 && x >= 34)
	{
		_ui.BosshpBar = IMAGEMANAGER->findImage("Bosshp34");
	}
	if (x < 34 && x >= 28)
	{
		_ui.BosshpBar = IMAGEMANAGER->findImage("Bosshp28");
	}
	if (x < 28 && x >= 22)
	{
		_ui.BosshpBar = IMAGEMANAGER->findImage("Bosshp22");
	}
	if (x < 22 && x >= 16)
	{
		_ui.BosshpBar = IMAGEMANAGER->findImage("Bosshp16");
	}
	if (x < 16 && x >= 0)
	{
		_ui.BosshpBar = IMAGEMANAGER->findImage("Bosshp10");
	}
	if (x < 0)
	{
		_ui.BosshpBar = IMAGEMANAGER->findImage("Bosshp0");
	}*/
}
